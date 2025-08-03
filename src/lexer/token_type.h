#ifndef TOKENS_H_
#define TOKENS_H_

typedef enum Token_type
{
    COMMAND,                      /* including command and it's args */

    LOGIC_AND, LOGIC_OR,          /* `&&` and `||` */

    SEMICOLON, BG_OPERATOR, PIPE, /* `;`, `&` and `|` */

    NIL,                          /* last token */

} Token_type;

#endif
