![build status](https://github.com/Jojodicus/xor-dll/blob/main/.github/workflows/build.yml/badge.svg)

# xor-dll
Space-optimized doubly-linked-list using xor-ed pointers.

See [the Wikipedia entry](https://en.wikipedia.org/wiki/XOR_linked_list) for more information.

## usage/compilation

Include the [xor.h](/src/xor.h) file in your project to use the list. Then either compile against the shared library made by `make build` or simply putting [xor.c](/src/xor.c) itself in the project.

## Testing

Run the tests by executing `run_test.sh`.
