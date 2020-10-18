// NAME: Jake Herron
// EMAIL: jakeh524@gmail.com
// ID: 005113997

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <string.h>

#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
    if(list == NULL || element == NULL)
    {
        return;
    }
    if(list->key != NULL)
    {
        return;
    }
    SortedList_t* iterator;
    SortedList_t* previous;
    if (opt_yield & INSERT_YIELD)
    {
        sched_yield();
    }
    for(iterator = list->next, previous = list; iterator != list; previous = iterator, iterator = iterator->next)
    {
//        if(iterator->key != NULL && (iterator->next != list || iterator->prev != list) && iterator->next == iterator->prev) // just the head
//        {
//            printf("Corrupted List. Next and prev pointers corrupted.\n");
//            exit(2);
//        }
        if(iterator == previous)
        {
            printf("Corrupted.\n");
            exit(2);
        }
        if(iterator->prev->next != iterator || iterator->next->prev != iterator) // check prev next and next prev ptrs
        {
            printf("Corrupted.\n"); // list corrupted
            exit(2);
        }
        if(iterator->prev != previous)
        {
            printf("Corrupted.\n");
            exit(2);
        }
        if(iterator->key == NULL)
        {
            break;
        }
        if (strcmp(iterator->key, element->key) > 0) {
            break;
        }
    }

    element->prev = previous;
    element->next = previous->next;
    element->next->prev = element;
    previous->next = element;
    
    return;
}

int SortedList_delete(SortedListElement_t *element)
{
    if(element == NULL || element->key == NULL) // values shouldnt be NULL
    {
        return(1); // corrupted list
    }
    if(element->next->prev != element || element->prev->next != element) // check the next prev and prev next ptrs for corrupted list
    {
        return(1); // corrupted list
    }
    if (opt_yield & DELETE_YIELD)
    {
        sched_yield();
    }
    element->next->prev = element->prev;
    element->prev->next = element->next;
    return(0); // element successfully deleted
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
    if(list == NULL || list->key != NULL)
    {
        return(NULL);
    }
    SortedListElement_t *iterator;
    if (opt_yield & LOOKUP_YIELD)
    {
        sched_yield();
    }
    for(iterator = list->next; iterator->next != NULL && iterator != list; iterator = iterator->next)
    {
//        if(iterator->key != NULL && (iterator->next != list || iterator->prev != list) && iterator->next == iterator->prev) // just the head
//        {
//            printf("Corrupted List. Next and prev pointers corrupted.\n");
//            exit(2);
//        }
        if(iterator->key == NULL)
        {
            return(NULL);
        }
        if(strcmp(iterator->key, key) == 0)
        {
            return(iterator);
        }
    }
    return(NULL);
}

int SortedList_length(SortedList_t *list)
{
    if(list == NULL || list->key != NULL)
    {
        return(-1);
    }
    int counter = 0;
    SortedListElement_t *iterator;
    if (opt_yield & LOOKUP_YIELD)
    {
        sched_yield();
    }
    for(iterator = list->next; iterator != list; iterator = iterator->next)
    {
//        if(iterator->key != NULL && (iterator->next != list || iterator->prev != list) && iterator->next == iterator->prev) // just the head
//        {
//            printf("Corrupted List. Next and prev pointers corrupted.\n");
//            exit(2);
//        }
        if(iterator == iterator->prev)
        {
            printf("Corrupted.\n");
            exit(2);
        }
        if(iterator->prev->next != iterator || iterator->next->prev != iterator) // check prev next and next prev ptrs
        {
            printf("Corrupted.\n"); // list corrupted
            exit(2);
        }
        if(iterator->prev->next != iterator || iterator->next->prev != iterator) // check prev next and next prev ptrs
        {
            return(-1); // list corrupted
        }
        counter += 1;
//        if (opt_yield & LOOKUP_YIELD)
//        {
//            sched_yield();
//        }
    }
    return(counter);
}


