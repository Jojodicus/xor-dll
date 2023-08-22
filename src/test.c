#include "xor.h"

#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define assert(expression) \
    if(!(expression)) { \
        printf("%s%s failed. (line %d)\n%s", RED, __func__, __LINE__, RESET); \
        failed_tests++; \
        return; \
    }

#define test_end() printf("%s%s passed.\n%s", GRN, __func__, RESET)

static int failed_tests = 0;

void test_create_destroy() {
    xor_list *list = xd_create_empty_list();
    assert(list);
    xd_destroy_list(NULL);
    xd_destroy_list(list);

    test_end();
}

void test_add_pop() {
    // []
    xor_list *list = xd_create_empty_list();

    int retval;

    // [3]
    assert(!xd_add_front(list, 3));

    // []
    assert(!xd_pop_back(list, &retval));
    assert(retval == 3);

    // [2]
    assert(!xd_add_back(list, 2));

    // []
    assert(!xd_pop_front(list, &retval));
    assert(retval == 2);

    // [1, 2 | 3, 4]
    assert(!xd_add_front(list, 2));
    assert(!xd_add_back(list, 3));
    assert(!xd_add_front(list, 1));
    assert(!xd_add_back(list, 4));

    // [2, 3]
    assert(!xd_pop_front(list, &retval));
    assert(retval == 1);
    assert(!xd_pop_back(list, &retval));
    assert(retval == 4);

    xd_destroy_list(list);

    test_end();
}

void test_is_empty() {
    xor_list *list = xd_create_empty_list();

    assert(xd_is_empty(list));

    assert(!xd_add_back(list, 1));
    assert(!xd_is_empty(list));

    assert(!xd_pop_back(list, NULL));
    assert(xd_is_empty(list));

    assert(!xd_add_front(list, 1));
    assert(!xd_add_back(list, 1));
    assert(!xd_pop_front(list, NULL));
    assert(!xd_is_empty(list));

    assert(!xd_pop_front(list, NULL));
    assert(xd_is_empty(list));

    xd_destroy_list(list);

    test_end();
}

void test_clear() {
    xor_list *list = xd_create_empty_list();

    assert(!xd_add_back(list, 1));
    assert(!xd_add_back(list, 1));
    assert(!xd_add_front(list, 1));
    assert(!xd_add_front(list, 1));
    assert(!xd_add_back(list, 1));

    xd_clear(list);
    assert(xd_is_empty(list));

    xd_destroy_list(list);

    test_end();
}

void test_length() {
    xor_list *list = xd_create_empty_list();

    assert(xd_length(list) == 0);

    assert(!xd_add_back(list, 1));
    assert(xd_length(list) == 1);

    assert(!xd_add_front(list, 1));
    assert(xd_length(list) == 2);

    assert(!xd_pop_front(list, NULL));
    assert(xd_length(list) == 1);

    assert(!xd_pop_front(list, NULL));
    assert(xd_length(list) == 0);

    xd_destroy_list(list);

    test_end();
}

void test_index() {
    xor_list *list = xd_create_empty_list();

    // [0, 1, 2, 3]
    assert(!xd_add_back(list, 1));
    assert(!xd_add_back(list, 2));
    assert(!xd_add_back(list, 3));
    assert(!xd_add_front(list, 0));

    int retval;

    for (size_t i = 0; i < 4; ++i) {
        assert(!xd_get_index(list, i, &retval));
        assert(retval == i);
    }

    assert(xd_get_index(list, 4, &retval));

    xd_destroy_list(list);

    test_end();
}

void test_array() {
    xor_list *list = xd_create_empty_list();

    // [0, 1, 2, 3]
    assert(!xd_add_back(list, 1));
    assert(!xd_add_back(list, 2));
    assert(!xd_add_back(list, 3));
    assert(!xd_add_front(list, 0));

    int *array = xd_to_array(list);
    assert(array);

    for (size_t i = 0; i < 4; ++i) {
        assert(array[i] == i);
    }

    free(array);
    xd_clear(list);

    array = xd_to_array(list);
    assert(array);

    free(array);
    xd_destroy_list(list);

    test_end();
}

void test_copy() {
    assert(0);
    test_end();
}

void test_concat() {
    assert(0);
    test_end();
}

int main(int argc, char **argv)
{
    // run tests
    test_create_destroy();
    test_add_pop();
    test_is_empty();
    test_clear();
    test_length();
    test_index();
    test_array();
    test_copy();
    test_concat();

    printf("---\n");

    // evaluate
    if (failed_tests) {
        printf(RED "%d tests failed!\n" RESET, failed_tests);
        exit(EXIT_FAILURE);
    } else {
        printf(GRN "All tests passed!\n" RESET);
        exit(EXIT_SUCCESS);
    }
}
