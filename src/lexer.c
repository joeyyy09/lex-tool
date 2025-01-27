#include "lexer.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Keywords in C
static const char* keywords[] = 
{
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

// Global state
static char *raw;        // Input buffer
static char *token;      // Current token
static int type;         // Current token type
size_t line = 1;  // Line counter - exposed for error.c

static void skip_comment(void) 
{
    while (*raw != '\n' && *raw != '\0') 
        raw++;
    if (*raw == '\n')
        line++;
}

static int scan_identifier(void) 
{
    char *start = raw;
    while (isalnum(*raw) || *raw == '_')
        raw++;

    size_t len = raw - start;
    raw--;  // Back up to last char of token

    free(token);
    token = malloc(len + 1);
    if (!token)
        error("Memory allocation failed");
    
    strncpy(token, start, len);
    token[len] = '\0';

    // Check if it's a keyword
    for (size_t i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) 
    {
        if (strcmp(token, keywords[i]) == 0)
            return TOK_KEYWORD;
    }

    return TOK_IDENTIFIER;
}

static int scan_number(void) 
{
    char *start = raw;
    while (isdigit(*raw))
        raw++;
    
    size_t len = raw - start;
    raw--;

    free(token);
    token = malloc(len + 1);
    if (!token)
        error("Memory allocation failed");
    
    strncpy(token, start, len);
    token[len] = '\0';

    return TOK_NUMBER;
}

static int lex(void) 
{
    while (isspace(*raw)) 
    {
        if (*raw == '\n')
            line++;
        raw++;
    }

    if (*raw == '\0')
        return 0;

    if (*raw == '/' && *(raw + 1) == '/') 
    {
        skip_comment();
        return lex();
    }

    if (isalpha(*raw) || *raw == '_')
        return scan_identifier();
    
    if (isdigit(*raw))
        return scan_number();

    char c = *raw;
    if (strchr("+-*/%=<>!&|^", c)) 
    {
        free(token);
        token = malloc(2);
        token[0] = c;
        token[1] = '\0';
        return TOK_OPERATOR;
    }

    if (strchr("(){}[];,.", c)) 
    {
        free(token);
        token = malloc(2);
        token[0] = c;
        token[1] = '\0';
        return TOK_PUNCTUATOR;
    }

    error("Unknown character: %c", c);
    return 0;
}

void analyze_source_file(const char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp) 
        error("Could not open file: %s", filename);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    raw = malloc(size + 1);
    if (!raw) 
        error("Memory allocation failed");
    
    if (fread(raw, 1, size, fp) != (size_t)size)
        error("Could not read file: %s", filename);
    
    raw[size] = '\0';
    fclose(fp);

    char *startp = raw;

    printf("\nLexeme\t\t\tCategory\t\tToken\n");
    printf("------------------------------------------------\n");

    while ((type = lex()) != 0) 
    {
        raw++;
        switch (type) 
        {
            case TOK_KEYWORD:
                printf("%-20s%-20s<KW, %s>\n", token, "Keyword", token);
                break;
            case TOK_IDENTIFIER:
                printf("%-20s%-20s<ID, %s>\n", token, "Identifier", token);
                break;
            case TOK_NUMBER:
                printf("%-20s%-20s<NUM, %s>\n", token, "Number", token);
                break;
            case TOK_OPERATOR:
                printf("%-20s%-20s<OP, %s>\n", token, "Operator", token);
                break;
            case TOK_PUNCTUATOR:
                printf("%-20s%-20s<PUN, %s>\n", token, "Punctuator", token);
                break;
        }
    }

    free(startp);
    free(token);
} 