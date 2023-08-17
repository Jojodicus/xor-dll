#pragma once

typedef struct xor_element
{
    struct xor_element *neighbours;
    int data; // TODO: generalize?
} xor_element;

typedef struct xor_list
{
    xor_element *first;
    xor_element *last;
} xor_list;

xor_list* create_empty_list();
void destroy_list(xor_list *list);

int is_empty(xor_list *list);
int length(xor_list *list);

int add_front(xor_list *list, int value);
int add_back(xor_list *list, int value);

int pop_front(xor_list *list, int *value);
int pop_back(xor_list *list, int *value);
