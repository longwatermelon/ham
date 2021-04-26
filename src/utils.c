#include "../include/utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void string_copy(char* s1, char* s2)
{
    s1 = malloc(strlen(s2) * sizeof(char) + 1);
    memcpy(s1, s2, strlen(s2));
    s1[strlen(s2)] = '\0';
}


void safe_free(void* ptr)
{
    free(ptr);
    ptr = (void*)0;
}