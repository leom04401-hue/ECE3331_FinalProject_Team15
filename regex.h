#ifndef REGEX_H
#define REGEX_H

#include <stdbool.h>

/*
function declarations + build system

File reading + line printing
Header file containing function declarations shared
between main.c, search.c, and regex.c. Defines the public
interface for the simplified regex-matching engine.
*/

// Core matcher
bool match(const char *pattern, const char *text);
bool match_here(const char *pattern, const char *text);

// Special pattern helpers
bool match_star(char c, const char *pattern, const char *text);
bool match_set(const char *pattern, const char *text, const char **next_pat);

// File search
void search_file(const char *filename, const char *pattern);

#endif
