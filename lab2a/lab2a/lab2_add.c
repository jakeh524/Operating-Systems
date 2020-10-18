// NAME: Jake Herron
// EMAIL: jakeh524@gmail.com
// ID: 005113997

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>

void add(long long *pointer, long long value);
void *add_subtract(void*);
void add_mutex(long long *pointer, long long value);
void *add_subtract_mutex(void*);
void add_spin(long long *pointer, long long value);
void *add_subtract_spin(void*);
void add_compare(long long *pointer, long long value);
void *add_subtract_compare(void*);


long long counter = 0;
int threads_num = 1;
int iterations_num = 1;
int opt_yield = 0;
char sync_option = 'x';
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
int spin_lock = 0;


int main(int argc, char * argv[]) {

    //ARGUMENT PARSING
    
    extern char *optarg;

    
    static struct option long_options[] = {
        {"threads", required_argument, 0, 't'},
        {"iterations", required_argument, 0, 'i'},
        {"yield", no_argument, 0, 'y'},
        {"sync", required_argument, 0, 's'},
        {0, 0, 0, 0}
    };
    
    char c;
    
    while((c=getopt_long(argc,argv,"t:i:ys",long_options,NULL)) != -1) {
        switch(c){
            case 't': // threads
                threads_num = atoi(optarg); // change string to int
                break;
            case 'i': // iterations
                iterations_num = atoi(optarg); // change string to int
                break;
            case 'y': // yield
                opt_yield = 1;
                break;
            case 's':
                sync_option = *optarg;
                break;
            case '?': //unknown arg
                fprintf(stderr, "Unrecognized argument present.\n");
                exit(1);
                break;
        }
    }
    
    // START CLOCK
    
    struct timespec start_time;
    int clock_error = clock_gettime(CLOCK_MONOTONIC, &start_time);
    if(clock_error != 0)
    {
        fprintf(stderr, "Error on clock_gettime system call.\n");
        exit(1);
    }
    
    // THREADS
    
    pthread_t *thread_array = (pthread_t*) malloc(threads_num*sizeof(pthread_t)); //allocate enough space for threads_num number of threads
    if(thread_array == NULL)
    {
        fprintf(stderr, "Error on malloc system call.\n");
        exit(1);
    }
    
    int i;
    for(i = 0; i < threads_num; i++) // create threads
    {
        if(sync_option == 'x') // no sync
        {
            int thread_error = pthread_create(&thread_array[i], NULL, &add_subtract, &iterations_num);
            if(thread_error != 0)
            {
                fprintf(stderr, "Error on pthread_create system call.\n");
                exit(1);
            }
        }
        else if(sync_option == 'm') // mutex
        {
            int thread_error = pthread_create(&thread_array[i], NULL, &add_subtract_mutex, &iterations_num);
            if(thread_error != 0)
            {
                fprintf(stderr, "Error on pthread_create system call.\n");
                exit(1);
            }
        }
        else if(sync_option == 's') // spin lock
        {
            int thread_error = pthread_create(&thread_array[i], NULL, &add_subtract_spin, &iterations_num);
            if(thread_error != 0)
            {
                fprintf(stderr, "Error on pthread_create system call.\n");
                exit(1);
            }
        }
        else if(sync_option == 'c') // compare and swap
        {
            int thread_error = pthread_create(&thread_array[i], NULL, &add_subtract_compare, &iterations_num);
            if(thread_error != 0)
            {
                fprintf(stderr, "Error on pthread_create system call.\n");
                exit(1);
            }
        }

    }
    
    for(i = 0; i < threads_num; i++) // join threads
    {
        int thread_error = pthread_join(thread_array[i], NULL);
        if(thread_error != 0)
        {
            fprintf(stderr, "Error on pthread_join system call.\n");
            exit(1);
        }
    }
    int destroy_error = pthread_mutex_destroy(&mymutex);
    if(destroy_error != 0)
    {
        fprintf(stderr, "Error on pthread_mutex_destroy system call.\n");
        exit(1);
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
    
    int total_operations = threads_num * iterations_num * 2;
    long total_time = (end_time.tv_sec - start_time.tv_sec)*1000000 + (end_time.tv_nsec - start_time.tv_nsec); //idk if this is how to calculate time
    long average_operation_time = total_time/total_operations;
    
    if(sync_option == 'x') // no sync options
    {
        if(opt_yield == 0)
        {
            fprintf(stdout, "add-none,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
        if(opt_yield == 1)
        {
            fprintf(stdout, "add-yield-none,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
    }
    
    else if(sync_option == 'm') // mutexes
    {
        if(opt_yield == 0)
        {
            fprintf(stdout, "add-m,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
        if(opt_yield == 1)
        {
            fprintf(stdout, "add-yield-m,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
    }
    
    else if(sync_option == 's') // spin-locks
    {
        if(opt_yield == 0)
        {
            fprintf(stdout, "add-s,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
        if(opt_yield == 1)
        {
            fprintf(stdout, "add-yield-s,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
    }
    
    else if(sync_option == 'c') // compare-and-swap
    {
        if(opt_yield == 0)
        {
            fprintf(stdout, "add-c,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
        if(opt_yield == 1)
        {
            fprintf(stdout, "add-yield-c,%d,%d,%d,%ld,%ld,%lld\n", threads_num, iterations_num, total_operations, total_time, average_operation_time, counter);
        }
    }
    
    // FREE DYNAMIC MEM
    free(thread_array);


    
    return 0;
}
                       

void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
    if (opt_yield)
    {
        sched_yield();
    }
    *pointer = sum;
}

void* add_subtract(__attribute__((unused)) void* arg) { // attribute unused was the only way to get rid of unused arg warning
    int i;
    for(i = 0; i < iterations_num; i++)
    {
        add(&counter, 1);
    }
    for(i = 0; i < iterations_num; i++)
    {
        add(&counter, -1);
    }
    pthread_exit(NULL);
}

void add_mutex(long long *pointer, long long value) {
    int lock_error = pthread_mutex_lock(&mymutex);
    if(lock_error != 0)
    {
        fprintf(stderr, "Error on pthread_mutex_lock system call.\n");
        exit(1);
    }
    long long sum = *pointer + value;
    if (opt_yield)
    {
        sched_yield();
    }
    *pointer = sum;
    int unlock_error = pthread_mutex_unlock(&mymutex);
    if(unlock_error != 0)
    {
        fprintf(stderr, "Error on pthread_mutex_unlock system call.\n");
        exit(1);
    }
}

void* add_subtract_mutex(__attribute__((unused)) void* arg) { // attribute unused was the only way to get rid of unused arg warning
    int i;
    for(i = 0; i < iterations_num; i++)
    {
        add_mutex(&counter, 1);
    }
    for(i = 0; i < iterations_num; i++)
    {
        add_mutex(&counter, -1);
    }
    pthread_exit(NULL);
}

void add_spin(long long *pointer, long long value) { // spin lock
    while(__sync_lock_test_and_set(&spin_lock, 1));
    long long sum = *pointer + value;
    if (opt_yield)
    {
        sched_yield();
    }
    *pointer = sum;
    __sync_lock_release(&spin_lock);
    
}

void* add_subtract_spin(__attribute__((unused)) void* arg) { // attribute unused was the only way to get rid of unused arg warning
    int i;
    for(i = 0; i < iterations_num; i++)
    {
        add_spin(&counter, 1);
    }
    for(i = 0; i < iterations_num; i++)
    {
        add_spin(&counter, -1);
    }
    pthread_exit(NULL);
}

void add_compare(long long *pointer, long long value) { // compare and swap
//    int oldval = (int)&pointer;
//    long long sum = *pointer + value;
//    if (opt_yield)
//    {
//        sched_yield();
//    }
//    __sync_val_compare_and_swap(pointer, oldval, sum);
    long long oldval;
    //long long sum;
    do{
        oldval = counter;
//        sum = *pointer + value;
        if (opt_yield)
        {
            sched_yield();
        }
    } while(__sync_val_compare_and_swap(pointer, oldval, oldval+value) != oldval);
}

void* add_subtract_compare(__attribute__((unused)) void* arg) { // attribute unused was the only way to get rid of unused arg warning
    int i;
    for(i = 0; i < iterations_num; i++)
    {
        add_compare(&counter, 1);
    }
    for(i = 0; i < iterations_num; i++)
    {
        add_compare(&counter, -1);
    }
    pthread_exit(NULL);
}
