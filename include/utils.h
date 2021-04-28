#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>


void string_copy(char** s1, char* s2);

void safe_free(void* ptr);

char* read_file(const char* fp);

bool check_if_garbage_string(char* string);

#endif