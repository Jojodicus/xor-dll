#include "xor.h"

#include <stdlib.h>
#include <stdint.h>

#define XOR(a, b) (xor_element*)((uintptr_t)a ^ (uintptr_t)b)

#define LIST_ITERATION(list, current_expression) \
    xor_element *current = list->first; \
    xor_element *drag = 0; \
    if (current) { \
        while (drag != list->last) { \
            xor_element *next = XOR(current->neighbours, drag); \
            current_expression; \
            drag = current; \
            current = next; \
        } \
    }

xor_list* xd_create_empty_list() {
    return calloc(1, sizeof(xor_list));
    // first and last are implicitly zeroed
}

void xd_destroy_list(xor_list *list) {
    if (!list) {
        // NULL list
        return;
    }

    xor_element *current = list->first;
    xor_element *drag = 0;

    if (current) {
        // non-empty list
        while (drag != list->last) {
            xor_element *next = XOR(current->neighbours, drag);
            free(current);
            drag = current; // yes, this is a dangling pointer
            current = next;
        }
    }

    free(list);
}

int xd_is_empty(xor_list *list) {
    return list && list->first;
}

size_t xd_length(xor_list *list) {
    if (!list) {
        return -1;
    }

    size_t length = 0;
    LIST_ITERATION(list, length = length + 1);
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
        list->first->neighbours = xor(list->first->neighbours, new_element);
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
        list->last->neighbours = xor(list->last->neighbours, new_element);
        list->last = new_element;
    }

    return 0;
}

int xd_pop_front(xor_list *list, int *value) {
    return 0; // TODO
}

int xd_pop_back(xor_list *list, int *value) {
    return 0; // TODO
}

int xd_get_index(xor_list *list, int *value) {
    return 0; // TODO
}

int xd_to_array(xor_list *list, int **array) {
    return 0; // TODO
}
