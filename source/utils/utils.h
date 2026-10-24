/**
 * This header file declares useful functions for various contexts.
 *
 * @author peppo02
 */

#ifndef UTILS_H_
#define UTILS_H_


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


bool compare_case_insensitive_strings(char *string1, char *string2);

char *substring(char *string, size_t start, size_t end);

char *format_time(time_t time, bool time_zone);

char *format_phone_number(char *phone_number);


#endif /* UTILS_H_ */
