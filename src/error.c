#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lexer.h"   // Include for line variable

void error(const char *fmt, ...) 
{
    va_list ap;
    fprintf(stderr, "Error on line %lu: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
} 