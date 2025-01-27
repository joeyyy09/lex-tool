# C Lex-Tool

A simple yet powerful lexical analyzer for C programming language, inspired by [Brian Callahan's lexer tutorial](https://briancallahan.net/blog/20210815.html).

## Overview

This lex-tool (lexer) is designed to break down C source code into tokens, making it useful for understanding the basic structure of C programs. It recognizes various elements of the C language including keywords, identifiers, numbers, operators, and punctuators.

## Features

- **Token Recognition**:
  - Keywords (if, while, int, etc.)
  - Identifiers (variable names, function names)
  - Numbers (integer literals)
  - Operators (+, -, *, /, =, etc.)
  - Punctuators ((), {}, [], ;, etc.)

- **Error Handling**:
  - Line-aware error reporting
  - Memory allocation checks
  - File operation validation

- **Comment Handling**:
  - Supports single-line comments (//)
  - Maintains accurate line counting
  
### Usage
        
```bash
./lexer input.c
```

### Example Output
Lexeme Category Token
------------------------------------------------
int Keyword <KW, int>
main Identifier <ID, main>
( Punctuator <PUN, (>
) Punctuator <PUN, )>
...

## Technical Details

### Token Categories
- `TOK_KEYWORD`: C language keywords
- `TOK_IDENTIFIER`: Variable and function names
- `TOK_NUMBER`: Numeric literals
- `TOK_OPERATOR`: Mathematical and logical operators
- `TOK_PUNCTUATOR`: Structural elements

### Memory Management
- Dynamic allocation for token storage
- Proper cleanup of resources
- Error handling for allocation failures