#include <stdio.h>
#include <stdlib.h>
#include "regex.h"

/*
argument handling   
Entry point of the program. Handles command-line arguments
and calls search_file() to perform regex-like pattern matching
on the input file provided by the user.
*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <pattern>\n", argv[0]);
        return 1;
    }

    search_file(argv[1], argv[2]);
    return 0;
}
