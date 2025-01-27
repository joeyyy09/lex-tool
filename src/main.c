#include "lexer.h"
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }

    analyze_source_file(argv[1]);
    return 0;
} 