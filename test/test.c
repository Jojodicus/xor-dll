#include "../src/xor.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    xor_list *list1 = xd_create_empty_list();

    printf("length %d\n", xd_length(list1));
    xd_add_back(list1, 1);
    xd_add_back(list1, 1);
    xd_add_back(list1, 1);
    printf("length %d\n", xd_length(list1));
}
