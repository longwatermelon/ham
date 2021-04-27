#include "../include/utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void string_copy(char** s1, char* s2)
{
    *s1 = malloc((strlen(s2) + 1) * sizeof(char));
    memcpy(*s1, s2, strlen(s2));
    (*s1)[strlen(s2)] = '\0';
}


void safe_free(void* ptr)
{
    if (ptr) free(ptr);
    ptr = (void*)0;
}


char* read_file(const char* fp)
{
    char* buf = 0;
    long long length;

    FILE* f = fopen(fp, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buf = malloc(sizeof(char) * length + 1);

        if (buf)
        {
            fread(buf, 1, length, f);
        }

        buf[sizeof(char) * length] = '\0';

        fclose(f);
        return buf;
    }

    printf("couldnt open file %s\n", fp);
    exit(1);
}