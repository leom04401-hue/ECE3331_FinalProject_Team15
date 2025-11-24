#include <stdbool.h>
#include "regex.h"

/*
Core pattern matching logic
Core regex-like matching engine. Implements simplified
recursive pattern matching for operators:
^  - anchor at beginning of line
$  - anchor at end of line
*  - zero or more repetitions
?  - optional match
[abc] - character sets
Contains match(), match_here(), and helper functions.
*/

bool match(const char *pattern, const char *text) {
    if (*pattern == '^') {
        return match_here(pattern + 1, text);
    }

    do {
        if (match_here(pattern, text)) return true;
    } while (*text++ != '\0');

    return false;
}

bool match_here(const char *pattern, const char *text) {
    if (*pattern == '\0') return true;

    if (*pattern == '$' && pattern[1] == '\0')
        return *text == '\0';

    if (*text != '\0' && *pattern == *text)
        return match_here(pattern + 1, text + 1);

    return false;
}

// Stubs for future features
bool match_star(char c, const char *pattern, const char *text) {
    return false;
}

bool match_set(const char *pattern, const char *text, const char **next_pat) {
    return false;
}
