#include "xor.h"

#include <stdlib.h>
#include <stdint.h>

#define xor(a, b) (xor_element*)((uintptr_t)a ^ (uintptr_t)b)

xor_list* create_empty_list()
{
    return calloc(1, sizeof(xor_list));
    // first and last are implicitly zeroed
}

void destroy_list(xor_list *list)
{
    if (!list) {
        // NULL list
        return;
    }

    xor_element *current = list->first;
    xor_element *drag = 0;

    if (current) {
        // non-empty list
        while (drag != list->last)
        {
            xor_element *next = xor(current->neighbours, drag);
            free(current);
            drag = current; // yes, this is a dangling pointer
            current = next;
        }
    }

    free(list);
}

int is_empty(xor_list *list)
{
    return list && list->first;
}

int length(xor_list *list)
{
    return 0; // TODO
}

int add_front(xor_list *list, int value)
{
    // reserve space
    xor_element *new_element = malloc(sizeof(xor_element));
    if (!new_element)
    {
        return -1;
    }

    // create element
    new_element->neighbours = list->first;
    new_element->data = value;

    if (!list->last)
    {
        // empty list
        list->first = new_element;
        list->last = new_element;
    } else {
        // non-empty list
        list->first->neighbours = xor(list->first->neighbours, new_element);
        list->first = new_element;
    }

    return 0;
}

int add_back(xor_list *list, int value)
{ // TODO: DRY with add_front
    // reserve space
    xor_element *new_element = malloc(sizeof(xor_element));
    if (!new_element)
    {
        return -1;
    }

    // create element
    new_element->neighbours = list->last;
    new_element->data = value;

    if (!list->first)
    {
        // empty list
        list->first = new_element;
        list->last = new_element;
    }
    else
    {
        // non-empty list
        list->last->neighbours = xor(list->last->neighbours, new_element);
        list->last = new_element;
    }

    return 0;
}

int pop_front(xor_list *list, int *value)
{
    return 0; // TODO
}

int pop_back(xor_list *list, int *value)
{
    return 0; // TODO
}
