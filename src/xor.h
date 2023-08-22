#pragma once

#include <stdlib.h>

typedef struct xor_element {
    struct xor_element *neighbours;
    int data; // TODO: generalize?
} xor_element;

typedef struct xor_list {
    xor_element *first;
    xor_element *last;
} xor_list;

// TODO: doc

xor_list* xd_create_empty_list();
void xd_destroy_list(xor_list *list);

void xd_clear(xor_list *list);

int xd_is_empty(xor_list *list);

size_t xd_length(xor_list *list);

int xd_add_front(xor_list *list, int value);
int xd_add_back(xor_list *list, int value);

int xd_pop_front(xor_list *list, int *value);
int xd_pop_back(xor_list *list, int *value);

int xd_get_index(xor_list *list, size_t index, int *value);

int* xd_to_array(xor_list *list);

// TODO: implement these

xor_list* xd_deep_copy(xor_list *list);

xor_list* xd_concat(xor_list *list1, xor_list *list2);
