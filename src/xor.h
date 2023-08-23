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

/**
 * \brief Create an empty list.
 *
 * Allocates and creates an empty xor-dll list. To avoid memory-leaks,
 * the returned pointer has to be passed to \ref xd_destroy_list().
 *
 * \return Empty allocated list.
 */
xor_list* xd_create_empty_list();

/**
 * \brief Destroy a list.
 *
 * Deallocates a list which has previously been created by
 * \ref xd_create_empty_list(). This method may abort if the list
 * was created by other means. O(n) runtime.
 *
 * \param list xor-dll list to deallocate.
 */
void xd_destroy_list(xor_list *list);

/**
 * \brief Remove all elements from a list.
 *
 * Clears and deallocates every element in the given list. This method may
 * abort if the list was not created by \ref xd_create_empty_list().
 * O(n) runtime.
 *
 * \param list xor-dll to clear
*/
void xd_clear(xor_list *list);

/**
 * \brief Check if a list is empty.
 *
 * \param list xor-dll list to check for emptiness.
 * \return 1 if \code list is a list with at least one element, 0 otherwise.
*/
int xd_is_empty(xor_list *list);

/**
 * \brief Calculate length of a list.
 *
 * Walks over the list, calculating the length. O(n) runtime.
 *
 * \param list List of which to calculate the length of.
 * \return Number of elements in the list.
*/
size_t xd_length(xor_list *list);

/**
 * \brief Add element to the front of a list
 *
 * Allocates and appends an element to the front of a given list.
 *
 * \param list List to append to.
 * \param value Value which should be appended.
 * \return 0 if operation was successful, 1 otherwise.
*/
int xd_add_front(xor_list *list, int value);

/**
 * \brief Add element to the back of a list
 *
 * Allocates and appends an element to the back of a given list.
 *
 * \param list List to append to.
 * \param value Value which should be appended.
 * \return 0 if operation was successful, 1 otherwise.
*/
int xd_add_back(xor_list *list, int value);

/**
 * \brief Remove an element from the front of a list.
 *
 * Deallocates and removes the first element in a list. The popped
 * value will be written to the provided \p value pointer.
 * If NULL is passed instead, the value will be discarded.
 *
 * \param list List to pop from.
 * \param value Where to store the popped value.
 * \return 0 if operation was successful, 1 otherwise.
*/
int xd_pop_front(xor_list *list, int *value);

/**
 * \brief Remove an element from the back of a list.
 *
 * Deallocates and removes the last element in a list. The popped
 * value will be written to the provided \p value pointer.
 * If NULL is passed instead, the value will be discarded.
 *
 * \param list List to pop from.
 * \param value Where to store the popped value.
 * \return 0 if operation was successful, 1 otherwise.
*/
int xd_pop_back(xor_list *list, int *value);

/**
 * \brief Get the element at a specific index.
 *
 * If possible, retrieve the value stored at position \p index
 * and write it to \p value. Indexing starts at 0. O(n) runtime.
 *
 * \param list List to operate on.
 * \param index Index of the element to retrieve.
 * \param value Where to store the data, required to be non-NULL.
 * \return 0 if operation was successful, 1 otherwise.
*/
int xd_get_index(xor_list *list, size_t index, int *value);

/**
 * \brief Convert a list to an array.
 *
 * Allocates space for an array and copies every value in \p list into it.
 * The returned array is malloc'ed, so it has to be freed by the user.
 * Length of the array is the length provided by \ref xd_length(). O(n) runtime.
 *
 * \param list List to convert.
 * \return allocated array of values, has to be passed to \ref free().
*/
int* xd_to_array(xor_list *list);

/**
 * \brief Create a deep copy of a list.
 *
 * Allocates space for a new list and copies every element to said list.
 * The returned list has to be passed to \ref xd_destroy_list(). O(n) runtime.
 *
 * \param list The list to copy.
 * \return Deep copy of \p list or NULL on failure.
*/
xor_list* xd_deep_copy(xor_list *list);

/**
 * \brief Concatenate two lists.
 *
 * Allocates space for a list and adds both the data from \p list1 and \p list2.
 * The returned list has to be passed to \ref xd_destroy_list().
 * If either list is NULL, a deep copy of the non-NULL list is created.
 * O(n+m) runtime.
 *
 * \param list1 First list.
 * \param list1 Second list.
 * \return Concatenation in the form [list1, list2] or NULL on failure.
*/
xor_list* xd_concat(xor_list *list1, xor_list *list2);
