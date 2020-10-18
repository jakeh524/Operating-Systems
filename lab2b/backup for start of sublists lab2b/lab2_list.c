//
//  lab2_list.c
//  lab2a
//
//  Created by Jake Herron on 2/12/20.
//  Copyright © 2020 Jake Herron. All rights reserved.
//

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include "SortedList.h"

char* generate_rand_key();
void *list_thread_func(void*);
void segfault_handler();

int threads_num = 1;
int iterations_num = 1;
int opt_yield = 0;
char* yield_option = "x"; // x is default for no yield
char sync_option = 'x'; // x is default for no sync
SortedList_t *head; // head of list to be sorted
SortedList_t *list; // elements to be inserted
struct thread_info{ // each thread needs its own struct to keep track of which index it is. Thanks to someone on Piazza!!
    int index_of_thread;
    long long thread_lock_wait_time;
};
struct thread_info *thread_array_info;
int list_elements_num = 1;
int thread_iter;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
int spin_lock = 0;
pthread_t *thread_array;
int lists_num = 1;


int main(int argc, char * argv[]) {

    //ARGUMENT PARSING

    extern char *optarg;

    static struct option long_options[] = {
    {"threads", required_argument, 0, 't'},
    {"iterations", required_argument, 0, 'i'},
    {"yield", required_argument, 0, 'y'},
    {"sync", required_argument, 0, 's'},
    {"lists", required_argument, 0, 'l'},
    {0, 0, 0, 0}
    };

    char c;

    while((c=getopt_long(argc,argv,"t:i:y:s:",long_options,NULL)) != -1) {
    switch(c){
        case 't': // threads
            threads_num = atoi(optarg); // change string to int
            break;
        case 'i': // iterations
            iterations_num = atoi(optarg); // change string to int
            break;
        case 'y': // yield
            yield_option = optarg;
            unsigned long i;
            for(i = 0; i < strlen(optarg); i++)
            {
                if(optarg[i] == 'i')
                {
                    opt_yield |= INSERT_YIELD;
                    break;
                }
                else if(optarg[i] == 'd')
                {
                    opt_yield |= DELETE_YIELD;
                    break;
                }
                else if(optarg[i] == 'l')
                {
                    opt_yield |= LOOKUP_YIELD;
                    break;
                }
            }
            break;
        case 's':
            sync_option = *optarg;
            break;
        case 'l':
            lists_num = atoi(optarg);
            break;
        case '?': //unknown arg
            fprintf(stderr, "Unrecognized argument present.\n");
            exit(1);
            break;
        }
    }
    
    // REGISTER SEG FAULT HANDLER
    
    signal(SIGSEGV, segfault_handler);
    
    // INIT SORTED LIST
    
    head = (SortedList_t*)malloc(sizeof(SortedList_t));
    head->next = head;
    head->prev = head;
    head->key = NULL;
    list_elements_num = threads_num * iterations_num;
    list = (SortedList_t*)malloc(list_elements_num*sizeof(SortedListElement_t));
    srand(time(NULL));
    int i;
    for(i = 0; i < list_elements_num; i++)
    {
        list[i].key = generate_rand_key();
    }
    
    // START CLOCK

    struct timespec start_time;
    int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time);
    if(clock_error != 0)
    {
        fprintf(stderr, "Error on clock_gettime system call.\n");
        exit(1);
    }


    // THREADS SETUP
    
    thread_array = (pthread_t*) malloc(threads_num*sizeof(pthread_t)); //allocate enough space for threads_num number of threads
    if(thread_array == NULL)
    {
        fprintf(stderr, "Error on malloc system call.\n");
        exit(1);
    }
    thread_array_info = (struct thread_info*)malloc(threads_num * sizeof(struct thread_info));
    int j;
    for(j = 0; j < threads_num; j++)
    {
        thread_array_info[j].index_of_thread = j;
    }
    
    // CREATE THREADS

    for(thread_iter = 0; thread_iter < threads_num; thread_iter++) //create threads
    {
        int thread_error = pthread_create(&thread_array[thread_iter], NULL, list_thread_func, (void*)&thread_array_info[thread_iter]);
        if(thread_error != 0)
        {
            fprintf(stderr, "Error on pthread_create system call.\n");
            exit(1);
        }
    }
    
    // JOIN THREADS

    for(thread_iter = 0; thread_iter < threads_num; thread_iter++) // join threads
    {
        int thread_error = pthread_join(thread_array[thread_iter], NULL);
        if(thread_error != 0)
        {
            fprintf(stderr, "Error on pthread_join system call.\n");
            exit(1);
        }
    }

    // END CLOCK

    struct timespec end_time;
    int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time);
    if(clock_error2 != 0)
    {
        fprintf(stderr, "Error on clock_gettime system call.\n");
        exit(1);
    }

    
    // OUTPUTTING
    
    int total_operations = threads_num * iterations_num * 3;
    long long total_time = (end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec);
    long long average_operation_time = total_time/total_operations;
    
    long long total_lock_time = 0;
    int k;
    for (k = 0; k < threads_num; k++) {
        total_lock_time += thread_array_info[k].thread_lock_wait_time;
    }
    
    int lock_ops_num = (1 + (2 * iterations_num)) * threads_num;
    
    long long average_wait_for_lock_time = total_lock_time / lock_ops_num;
    
    int list_len = SortedList_length(head);
    if(list_len != 0)
    {
        fprintf(stderr, "List length is not 0.\n");
        exit(2);
    }
    if(sync_option == 'x')
    {
        if(strcmp(yield_option, "x") == 0) // no yield
        {
            fprintf(stdout, "list-none-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, 0);
        }
        else if(strcmp(yield_option, "i") == 0)
        {
            fprintf(stdout, "list-i-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, 0);
        }
        else if(strcmp(yield_option, "d") == 0)
        {
            fprintf(stdout, "list-d-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
        else if(strcmp(yield_option, "l") == 0)
        {
            fprintf(stdout, "list-l-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
        else if((strcmp(yield_option, "id") == 0) || (strcmp(yield_option, "di") == 0))
        {
            fprintf(stdout, "list-id-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
        else if((strcmp(yield_option, "il") == 0) || (strcmp(yield_option, "li") == 0))
        {
            fprintf(stdout, "list-il-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
        else if((strcmp(yield_option, "dl") == 0) || (strcmp(yield_option, "ld") == 0))
        {
            fprintf(stdout, "list-dl-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
        else if((strcmp(yield_option, "idl") == 0) || (strcmp(yield_option, "ild") == 0) || (strcmp(yield_option, "lid") == 0) || (strcmp(yield_option, "ldi") == 0) || (strcmp(yield_option, "dil") == 0) || (strcmp(yield_option, "dli") == 0))
        {
            fprintf(stdout, "list-idl-none,%d,%d,%d,%d,%lld,%lld,%d\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time,0);
        }
    }
    
    
    else if(sync_option == 'm')
    {
        if(strcmp(yield_option, "x") == 0) // no yield
        {
            fprintf(stdout, "list-none-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "i") == 0)
        {
            fprintf(stdout, "list-i-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "d") == 0)
        {
            fprintf(stdout, "list-d-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "l") == 0)
        {
            fprintf(stdout, "list-l-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "id") == 0) || (strcmp(yield_option, "di") == 0))
        {
            fprintf(stdout, "list-id-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "il") == 0) || (strcmp(yield_option, "li") == 0))
        {
            fprintf(stdout, "list-il-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "dl") == 0) || (strcmp(yield_option, "ld") == 0))
        {
            fprintf(stdout, "list-dl-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "idl") == 0) || (strcmp(yield_option, "ild") == 0) || (strcmp(yield_option, "lid") == 0) || (strcmp(yield_option, "ldi") == 0) || (strcmp(yield_option, "dil") == 0) || (strcmp(yield_option, "dli") == 0))
        {
            fprintf(stdout, "list-idl-m,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
    }
    
    else if(sync_option == 's')
    {
        if(strcmp(yield_option, "x") == 0) // no yield
        {
            fprintf(stdout, "list-none-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "i") == 0)
        {
            fprintf(stdout, "list-i-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "d") == 0)
        {
            fprintf(stdout, "list-d-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if(strcmp(yield_option, "l") == 0)
        {
            fprintf(stdout, "list-l-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "id") == 0) || (strcmp(yield_option, "di") == 0))
        {
            fprintf(stdout, "list-id-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "il") == 0) || (strcmp(yield_option, "li") == 0))
        {
            fprintf(stdout, "list-il-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "dl") == 0) || (strcmp(yield_option, "ld") == 0))
        {
            fprintf(stdout, "list-dl-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
        else if((strcmp(yield_option, "idl") == 0) || (strcmp(yield_option, "ild") == 0) || (strcmp(yield_option, "lid") == 0) || (strcmp(yield_option, "ldi") == 0) || (strcmp(yield_option, "dil") == 0) || (strcmp(yield_option, "dli") == 0))
        {
            fprintf(stdout, "list-idl-s,%d,%d,%d,%d,%lld,%lld,%lld\n", threads_num, iterations_num, 1, total_operations, total_time, average_operation_time, average_wait_for_lock_time);
        }
    }

    
    // FREE ALL DYNAMIC MEM
    free(thread_array);
    free(list);
    free(head);

    
    return(0);
}

char* generate_rand_key()
{
    char* return_key = malloc(4*sizeof(char));
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    int i;
    for(i = 0; i < 3; i++)
    {
        return_key[i] = letters[rand() % 25];
    }
    return_key[4] = '\0';
    return(return_key);
}

void* list_thread_func(void* arg) {
    long long thread_wait_lock_time = 0;
    struct timespec start_time_thread;
    struct timespec end_time_thread;
    
    struct thread_info *this_thread_info = (struct thread_info*)arg;
    int elements_num = threads_num * iterations_num;
    if(sync_option == 'x')
    {
        int i;
        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            SortedList_insert(head, &list[i]);
            i += threads_num;
        }
        int list_len = SortedList_length(head);
        if(list_len == -1)
        {
            fprintf(stderr, "Corrupted list. Found in length function.\n");
            exit(2);
        }
        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            SortedListElement_t *lookup = SortedList_lookup(head, list[i].key);
            if(lookup == NULL)
            {
                fprintf(stderr, "Corrupted list. Inserted element not found in lookup function.\n");
                exit(2);
            }
            int delete_error = SortedList_delete(lookup);
            if(delete_error == 1)
            {
                fprintf(stderr, "Corrupted list found in delete function.\n");
                exit(2);
            }
            i += threads_num;
        }
        pthread_exit(NULL);
    }
    
    else if(sync_option == 'm')
    {
        int i;
        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
            
            int lock_error = pthread_mutex_lock(&mymutex);
            
            int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
            
            if(lock_error != 0)
            {
                fprintf(stderr, "Error on pthread_mutex_lock system call.\n");
                exit(1);
            }
            if(clock_error != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            if(clock_error2 != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            
            SortedList_insert(head, &list[i]);
            
            int unlock_error = pthread_mutex_unlock(&mymutex);
            if(unlock_error != 0)
            {
                fprintf(stderr, "Error on pthread_mutex_unlock system call.\n");
                exit(1);
            }

            thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);
            
            i += threads_num;
        }
        
        int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
        
        int lock_error = pthread_mutex_lock(&mymutex);
        
        int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
        
        if(lock_error != 0)
        {
            fprintf(stderr, "Error on pthread_mutex_lock system call.\n");
            exit(1);
        }
        if(clock_error != 0)
        {
            fprintf(stderr, "Error on clock_gettime system call.\n");
            exit(1);
        }

        if(clock_error2 != 0)
        {
            fprintf(stderr, "Error on clock_gettime system call.\n");
            exit(1);
        }
        
        int list_len = SortedList_length(head);
        if(list_len < 0)
        {
            fprintf(stderr, "Corrupted list. Found in length function.\n");
            exit(2);
        }
        
        int unlock_error = pthread_mutex_unlock(&mymutex);
        if(unlock_error != 0)
        {
            fprintf(stderr, "Error on pthread_mutex_unlock system call.\n");
            exit(1);
        }
        
        thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);

        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
            
            int lock_error = pthread_mutex_lock(&mymutex);
            
            int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
            
            if(lock_error != 0)
            {
                fprintf(stderr, "Error on pthread_mutex_lock system call.\n");
                exit(1);
            }
            if(clock_error != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            if(clock_error2 != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            
            SortedListElement_t *lookup = SortedList_lookup(head, list[i].key);
            if(lookup == NULL)
            {
                fprintf(stderr, "Corrupted list. Inserted element not found in lookup function.\n");
                exit(2);
            }
            int delete_error = SortedList_delete(lookup);
            if(delete_error == 1)
            {
                fprintf(stderr, "Corrupted list found in delete function.\n");
                exit(2);
            }
            
            int unlock_error = pthread_mutex_unlock(&mymutex);
            if(unlock_error != 0)
            {
                fprintf(stderr, "Error on pthread_mutex_unlock system call.\n");
                exit(1);
            }
            
            thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);
            
            i += threads_num;
        }
        this_thread_info->thread_lock_wait_time = thread_wait_lock_time;
        pthread_exit(NULL);
    }
    
    else if(sync_option == 's')
    {
        int i;
        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
            
            while(__sync_lock_test_and_set(&spin_lock, 1));
            
            int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
            
            if(clock_error != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            if(clock_error2 != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            
            SortedList_insert(head, &list[i]);
            
            __sync_lock_release(&spin_lock);
            
            thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);
            
            i += threads_num;
        }
        
        int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
        
        while(__sync_lock_test_and_set(&spin_lock, 1));
        
        int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
        
        if(clock_error != 0)
        {
            fprintf(stderr, "Error on clock_gettime system call.\n");
            exit(1);
        }
        if(clock_error2 != 0)
        {
            fprintf(stderr, "Error on clock_gettime system call.\n");
            exit(1);
        }
        
        int list_len = SortedList_length(head);
        if(list_len < 0)
        {
            fprintf(stderr, "Corrupted list. Found in length function.\n");
            exit(2);
        }
        
        __sync_lock_release(&spin_lock);
        
        thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);

        for(i = this_thread_info->index_of_thread; i < elements_num; )
        {
            int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time_thread);
            
            while(__sync_lock_test_and_set(&spin_lock, 1));
            
            int clock_error2 = clock_gettime(CLOCK_MONOTONIC, &end_time_thread);
            
            if(clock_error != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            if(clock_error2 != 0)
            {
                fprintf(stderr, "Error on clock_gettime system call.\n");
                exit(1);
            }
            
            SortedListElement_t *lookup = SortedList_lookup(head, list[i].key);
            if(lookup == NULL)
            {
                fprintf(stderr, "Corrupted list. Inserted element not found in lookup function.\n");
                exit(2);
            }
            int delete_error = SortedList_delete(lookup);
            if(delete_error == 1)
            {
                fprintf(stderr, "Corrupted list found in delete function.\n");
                exit(2);
            }
            
            __sync_lock_release(&spin_lock);
            
            thread_wait_lock_time += (end_time_thread.tv_sec - start_time_thread.tv_sec)*1000000000 + (end_time_thread.tv_nsec - start_time_thread.tv_nsec);
            
            i += threads_num;
        }
        this_thread_info->thread_lock_wait_time = thread_wait_lock_time;
        pthread_exit(NULL);
    }
    pthread_exit(NULL);
}

void segfault_handler()
{
    write(2, "Segmentation Fault detected.\n", 29);
    exit(2);
}
