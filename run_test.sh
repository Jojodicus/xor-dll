#! /bin/bash

# helper script for running tests outside of CI/CD

check_command () {
    if ! which $1 > /dev/null 2>&1
    then
        echo "$1 not found, install it first."
        exit 1
    fi
}

check_command valgrind
check_command make
check_command gcc

if ! [ -e build/test ]
then
    make test
fi

valgrind --leak-check=full ./build/test
