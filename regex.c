#include <stdbool.h>        // bool, true, false
#include "regex.h"          // function prototypes shared between files

/*
Core pattern matching logic.

This file contains the simplified recursive regex engine.
It currently supports:
^   - anchor at beginning of line
$   - anchor at end of line
*   - zero or more repetitions  (stub for now)
?   - optional match            (stub for now)
[abc] - character sets          (stub for now)

Functions:
match()      - entry point
match_here() - recursive matching
match_star() - handles "c*"  (stub)
match_set()  - handles "[abc]" (stub)
*/

bool match(const char *pattern, const char *text) {

    if (*pattern == '^') {                   // if pattern begins with ^
        return match_here(pattern + 1, text); // anchor: must match at start of text
    }

    // If no ^ anchor:
    // Try matching the pattern starting at every position in the text.
    do {
        if (match_here(pattern, text))       // recursive attempt to match here
            return true;                     // success at this position
    } while (*text++ != '\0');               // move text pointer forward until end

    return false;                            // no match found anywhere
}

bool match_here(const char *pattern, const char *text) {

    if (*pattern == '\0')                    // if we reached end of pattern
        return true;                         // full match successful

    if (*pattern == '$' && pattern[1] == '\0')  // if pattern ends with $
        return *text == '\0';                   // true only if end of text reached

    // Simple character-by-character match
    if (*text != '\0' && *pattern == *text)     // if current chars match
        return match_here(pattern + 1, text + 1); // continue recursively

    return false;                               // mismatch → fail
}

// Stub for c* (zero or more repetitions)
// Will be implemented later
bool match_star(char c, const char *pattern, const char *text) {
    return false;
}

// Stub for character sets [abc]
// Will be implemented later
bool match_set(const char *pattern, const char *text, const char **next_pat) {
    return false;
}
