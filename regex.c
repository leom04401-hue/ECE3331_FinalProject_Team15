#include <stdbool.h>        // bool, true, false 
#include "regex.h"          // function prototypes shared between files

/*
Core pattern matching logic.

This file contains the simplified recursive regex engine.
It supports:
^      - anchor at beginning of line
$      - anchor at end of line
*      - zero or more repetitions of previous character
?      - optional previous character (zero or one)
[abc]  - simple character sets (no ranges)

Functions:
match()      - entry point (public)
match_here() - recursive matching from current position
match_star() - handles "c*" (zero or more of char c)
match_set()  - handles "[abc]" style sets
*/

// Forward declaration in case of mutual calls
bool match_here(const char *pattern, const char *text);

/* Public API: try to match pattern anywhere in text */
bool match(const char *pattern, const char *text) {

    if (*pattern == '^') {                    // if pattern begins with ^
        return match_here(pattern + 1, text); // anchor: must match at start of text
    }

    // If no ^ anchor:
    // Try matching the pattern starting at every position in the text.
    do {
        if (match_here(pattern, text))        // recursive attempt to match here
            return true;                      // success at this position
    } while (*text++ != '\0');                // move text pointer forward until end

    return false;                             // no match found anywhere
}

/*
 * Recursive matcher that assumes we are already at the correct
 * starting position in the text.
 */
bool match_here(const char *pattern, const char *text) {

    // End of pattern: success
    if (*pattern == '\0')
        return true;

    // Handle "$" at end of pattern: must also be end of text
    if (*pattern == '$' && pattern[1] == '\0')
        return *text == '\0';

    // Handle character set: [abc]
    if (*pattern == '[') {
        const char *next_pat = pattern;  // will be set by match_set

        // If we are at end of text, we can't match any set
        if (*text == '\0')
            return false;

        // Check if text[0] is inside the set, and get pointer after ']'
        if (!match_set(pattern, text, &next_pat))
            return false;                // not in set → fail

        // Move forward one character in text and continue after the set
        return match_here(next_pat, text + 1);
    }

    // Look ahead for "*" (zero or more of previous char)
    if (pattern[1] == '*') {
        return match_star(pattern[0], pattern + 2, text);
    }

    // Look ahead for "?" (zero or one of previous char)
    if (pattern[1] == '?') {
        // If current character matches, we can consume it
        if (*text != '\0' && *text == pattern[0]) {
            // Option 1: use the character
            if (match_here(pattern + 2, text + 1)) return true;
        }
        // Option 2: skip it
        return match_here(pattern + 2, text);
    }

    // Plain character-by-character match
    if (*text != '\0' && *pattern == *text)   // if current chars match
        return match_here(pattern + 1, text + 1); // continue recursively

    // No match at this step
    return false;                             
}

/*
 * Handle c* (zero or more repetitions of character c).
 * pattern: pointer to rest of pattern after "c*"
 * text:    current position in text
 */
bool match_star(char c, const char *pattern, const char *text) {

    const char *t = text;

    // Try zero or more occurrences of 'c'
    // First, try zero occurrences
    if (match_here(pattern, t))
        return true;

    // Then keep consuming 'c' while it matches, checking each time
    while (*t != '\0' && *t == c) {
        t++;
        if (match_here(pattern, t))
            return true;
    }

    return false;
}

/*
 * Handle character sets like [abc].
 * pattern: points to '['
 * text:    current text character
 * next_pat: set to the position in pattern after the closing ']'
 *
 * Returns true if text[0] is inside the set.
 */
bool match_set(const char *pattern, const char *text, const char **next_pat) {

    const char *p = pattern;
    bool found = false;
    char ch = *text;

    // If we're at end of text, can't match anything
    if (ch == '\0') {
        *next_pat = pattern;
        return false;
    }

    p++; // skip '['

    // Collect the set characters until we hit ']'
    while (*p != '\0' && *p != ']') {
        if (ch == *p) {
            found = true;
        }
        p++;
    }

    // If we found ']', move past it; otherwise just stop at '\0'
    if (*p == ']') {
        p++;
    }

    // Return the pattern position after the closing ']'
    *next_pat = p;

    return found;
}
