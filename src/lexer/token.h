#ifndef TOKENS_H_
#define TOKENS_H_

#include <stdlib.h>


typedef enum Token_type
{
    COMMAND,                      /* including command and it's args */

    LOGIC_AND, LOGIC_OR,          /* `&&` and `||` */
    SEMICOLON, BG_OPERATOR, PIPE, /* `;`, `&` and `|` */

    NIL,                          /* last token */

} Token_type;


typedef enum Return_status
{
    RETURN_SUCCES,
    RETURN_FAILURE,
    UNDEFINED,

} Return_status;


/*
 * Definition of tokens that will be created by the
 * lexer and used by the parser to construct an AST.
 */
typedef struct Token 
{
    Token_type type;

    char **argv;  /* default `NULL` for non-`COMMAND` tokens */
    size_t argc;  /* default `0` for non-`COMMAND` tokens */

    Return_status return_status;  /* default `UNDEFINED` */

} Token;


#endif
