#include <stdio.h>
#include <string.h>
#include "regex.h"

#define MAX_LINE 1024
/*
File reading + line printing

Contains the function search_file(), which opens the input
text file, reads it line-by-line, strips newlines, and
calls match() to test each line against the regex pattern.
Matching lines are printed with line numbers.
*/


void search_file(const char *filename, const char *pattern) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE];
    int line_num = 1;

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0'; // remove newline

        if (match(pattern, line)) {
            printf("%d: %s\n", line_num, line);
        }

        line_num++;
    }

    fclose(f);
}
