#include "xor.h"

#include <stdlib.h>
#include <stdint.h>

#define XOR(a, b) (xor_element*)((uintptr_t)a ^ (uintptr_t)b)

// template for iterating over the list
#define LIST_ITERATION(list, current_expression) \
    xor_element *current = list->first; \
    xor_element *drag = 0; \
    if (current) { \
        while (drag != list->last) { \
            xor_element *next = XOR(current->neighbours, drag); \
            drag = current; \
            current_expression; \
            current = next; \
        } \
    }

xor_list* xd_create_empty_list() {
    return calloc(1, sizeof(xor_list));
    // first and last are implicitly zeroed
}

void xd_destroy_list(xor_list *list) {
    if (!list) {
        return;
    }

    LIST_ITERATION(list, free(current))
    free(list);
}

int xd_is_empty(xor_list *list) {
    return list && list->first;
}

size_t xd_length(xor_list *list) {
    if (!list) {
        return 0;
    }

    size_t length = 0;
    LIST_ITERATION(list, length++);
    return length;
}

int xd_add_front(xor_list *list, int value) {
    // reserve space
    xor_element *new_element = malloc(sizeof(xor_element));
    if (!new_element) {
        return -1;
    }

    // create element
    new_element->neighbours = list->first;
    new_element->data = value;

    if (!list->last) {
        // empty list
        list->first = new_element;
        list->last = new_element;
    } else {
        // non-empty list
        list->first->neighbours = XOR(list->first->neighbours, new_element);
        list->first = new_element;
    }

    return 0;
}

int xd_add_back(xor_list *list, int value) { // TODO: DRY with add_front
    // reserve space
    xor_element *new_element = malloc(sizeof(xor_element));
    if (!new_element) {
        return -1;
    }

    // create element
    new_element->neighbours = list->last;
    new_element->data = value;

    if (!list->first) {
        // empty list
        list->first = new_element;
        list->last = new_element;
    } else {
        // non-empty list
        list->last->neighbours = XOR(list->last->neighbours, new_element);
        list->last = new_element;
    }

    return 0;
}

int xd_pop_front(xor_list *list, int *value) {
    if (!list || !list->first) {
        return -1;
    }

    xor_element *popping = list->first;
    list->first = popping->neighbours;
    list->first->neighbours = XOR(list->first->neighbours, popping);

    *value = popping->data;
    free(popping);
    return 0;
}

int xd_pop_back(xor_list *list, int *value) {
    if (!list || !list->last) {
        return -1;
    }

    xor_element *popping = list->last;
    list->last = popping->neighbours;
    list->last->neighbours = XOR(list->last->neighbours, popping);

    *value = popping->data;
    free(popping);
    return 0;
}

int xd_get_index(xor_list *list, size_t index, int *value) {
    if (!list) {
        return -1;
    }

    // count down index, return when zero is reached
    LIST_ITERATION(list,
        if(!index--) {
            *value = current->data;
            return 0;
        }
    )

    // index too large
    return -1;
}

int* xd_to_array(xor_list *list) {
    if (!list) {
        return NULL;
    }

    // create array
    size_t length = xd_length(list);
    int *array = calloc(length, sizeof(int));
    if (!*array) {
        return NULL;
    }

    // fill array
    size_t running_index = 0;
    LIST_ITERATION(list, array[running_index++] = current->data);

    return array;
}
