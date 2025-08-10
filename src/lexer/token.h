#ifndef TOKENS_H_
#define TOKENS_H_


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


/* Actual `Token` datastructure */
typedef struct Token 
{
    Token_type type;

    char *arg;  /* default `NULL` for non-`COMMAND` tokens */

    Return_status return_status;  /* default `UNDEFINED` */

} Token;


#endif
