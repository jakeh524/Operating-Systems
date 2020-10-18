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
    if(list == NULL || element == NULL) // error check args
    {
        return;
    }
    SortedList_t* iterator;
    SortedList_t* previous;
    for(iterator = list->next, previous = list; iterator != list; previous = iterator, iterator = iterator->next)
    {
        if (strcmp(iterator->key, element->key) > 0) {
            break;
        }
    }
    if (opt_yield & INSERT_YIELD)
    {
        sched_yield();
    }
    element->prev = previous;
    element->next = previous->next;
    element->next->prev = element;
    previous->next = element;
    return; // element inserted
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
    if(list == NULL || list->key != NULL) // error check args
    {
        return(NULL);
    }
    SortedListElement_t *iterator;
    for(iterator = list->next; iterator->next != NULL && iterator != list; iterator = iterator->next)
    {
        if(strcmp(iterator->key, key) == 0) // found a match
        {
            return(iterator);
        }
        if (opt_yield & LOOKUP_YIELD)
        {
            sched_yield();
        }
    }
    return(NULL); // no match found
}

int SortedList_length(SortedList_t *list)
{
    if(list == NULL || list->key != NULL) // error check args
    {
        return(-1);
    }
    int counter = 0;
    SortedListElement_t *iterator;
    for(iterator = list->next; iterator != list; iterator = iterator->next)
    {
        if(iterator->prev->next != iterator || iterator->next->prev != iterator) // check prev next and next prev ptrs
        {
            return(-1); // list corrupted
        }
        if (opt_yield & LOOKUP_YIELD)
        {
            sched_yield();
        }
        counter += 1;
    }
    return(counter); // return list len
}


