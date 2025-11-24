#include <stdio.h>      // Standard I/O library (printf, fprintf)
#include <stdlib.h>     // Standard library (exit codes, general utilities)
#include "regex.h"      // Our custom header containing search_file() and match() prototypes

/*
argument handling   
Entry point of the program. Handles command-line arguments
and calls search_file() to perform regex-like pattern matching
on the input file provided by the user.
*/

int main(int argc, char *argv[]) {
    // argc = argument count
    // argv = argument vector (array of strings)
    // Example: ./regex-lite input.txt "pattern"
    //          argv[0]      argv[1]     argv[2]

    if (argc != 3) {  
        // If the user did NOT provide exactly 2 arguments (file + pattern),
        // print an error message showing the correct usage.

        fprintf(stderr, "Usage: %s <file> <pattern>\n", argv[0]);
        // fprintf with stderr prints the message to the error stream.

        return 1;  
        // Exit with status code 1 (general error).
    }

    // If we reach here, the user provided correct number of arguments.
    // Now we call search_file() using:
    // argv[1] → the filename
    // argv[2] → the regex pattern

    search_file(argv[1], argv[2]);

    return 0;
    // Return 0 to signal successful program execution.
}
