#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

// Token categories
#define TOK_KEYWORD    'K'
#define TOK_IDENTIFIER 'I'
#define TOK_NUMBER     'N'
#define TOK_OPERATOR   'O'
#define TOK_RELOP      'R'
#define TOK_PUNCTUATOR 'P'

// Global line counter
extern size_t line;

// Public interface
void analyze_source_file(const char *filename);

#endif 