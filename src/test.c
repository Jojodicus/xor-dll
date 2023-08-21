#include "../src/xor.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    xor_list *list1 = xd_create_empty_list();

    printf("length %d\n", xd_length(list1));
    xd_add_back(list1, 1);
    xd_add_back(list1, 2);
    xd_add_back(list1, 3);
    printf("length %d\n", xd_length(list1));

    int storage;
    xd_get_index(list1, 0, &storage);
    printf("0 %d\n", storage);
    xd_get_index(list1, 1, &storage);
    printf("1 %d\n", storage);
    xd_get_index(list1, 2, &storage);
    printf("2 %d\n", storage);
    int ret = xd_get_index(list1, 3, &storage);
    printf("3 %d (but returned %d)\n", storage, ret);

    xd_destroy_list(list1);
}
