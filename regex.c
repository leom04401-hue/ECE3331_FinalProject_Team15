/***************************************************************
 * File: regex.c
 * Project: Regex-Lite (ECE 3331 Final Project)
 * Description:
 *    Core regex-like matching engine. Implements simplified
 *    recursive pattern matching for operators:
 *        ^  - anchor at beginning of line
 *        $  - anchor at end of line
 *        *  - zero or more repetitions
 *        ?  - optional match
 *     [abc] - character sets
 *
 *    Contains match(), match_here(), and helper functions.
 *
 * Team 15
 * Date: Fall 2025
 ***************************************************************/
