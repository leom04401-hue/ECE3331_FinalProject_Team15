#include <stdio.h>      // file I/O: fopen, fgets, fclose, printf
#include <string.h>     // string functions: strcspn (used to remove newline)
#include "regex.h"      // header with match() and search_file() prototypes

#define MAX_LINE 1024   // set maximum line length (prevents overflow)

/*
File reading + line printing

Contains the function search_file(), which:
- opens the input text file
- reads it line-by-line
- strips newline characters
- calls match() to test each line against the regex pattern
- prints matching lines with line numbers
*/

void search_file(const char *filename, const char *pattern) {

    FILE *f = fopen(filename, "r");     // open the file for reading ("r")
    if (!f) {                           // if fopen() returned NULL → file failed to open
        perror("Error opening file");   // print system error message
        return;                         // exit the function (can't continue without file)
    }

    char line[MAX_LINE];                // buffer to hold each line from the file
    int line_num = 1;                   // keeps track of line numbers (start at 1)

    while (fgets(line, sizeof(line), f)) {     // read each line until EOF
        line[strcspn(line, "\n")] = '\0';      // remove newline at end of line

        if (match(pattern, line)) {            // call regex engine to test this line
            printf("%d: %s\n", line_num, line); // if it matches → print line number + content
        }

        line_num++;                             // move to next line number
    }

    fclose(f);                                  // close the file after finishing
}
