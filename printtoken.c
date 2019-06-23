#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"


static char* delprnt[] = { " ", "(", ")", "[", "]", "..", ",", ":", ";"} ;
static char* opprnt[]  = {" ", ".", "+", "-", "*", "/", "<", "<=", "=", "<>", ">", ">=", ":=",
    "and", "or", "not", "div", "mod"
};
static char* resprnt[] = { " ", "array", "begin", "case", "const", "do",
                           "downto", "else", "end", "for",
		                  "function", "goto", "if", "in",
                           "of", "packed", "procedure", "program", "read", "record",
                           "repeat", "set", "then", "to", "type",
		                  "until", "var", "while", "with",
                          "SYS_CON", "SYS_FUNCT", "SYS_PROC", "SYS_TYPE" };
/* allocate a new token record */
TOKEN talloc() {
    TOKEN tok;
    tok = (TOKEN) calloc(1,sizeof(struct tokenstruct));
    if ( tok != NULL ) return (tok);
       else {
        printf("talloc failed.");
        exit(-1);
    }
}

void printtoken(TOKEN tok) {
    switch (tok->tokenType) {
        case OPERATOR:
            printf ("tokenType: %2d  which: %4d   %10s\n",
                tok->tokenType, tok->tokenNo,
                opprnt[tok->tokenNo] );
            break;
        case DELIMITER:
            printf ("tokenType: %2d  which: %4d   %10s\n",
                tok->tokenType, tok->tokenNo,
                delprnt[tok->tokenNo] );
           break;
        case RESERVED:
           printf ("tokenType: %2d  which: %4d   %10s\n",
                tok->tokenType, tok->tokenNo,
                resprnt[tok->tokenNo] );
           break;
        case TOKEN_ID:
        case TOKEN_STR:
           printf ("tokenType: %2d  value:  %16s\n",
             tok->tokenType, tok->val.stringVal);
           break;
        case TOKEN_CHAR:
           printf ("tokenType: %2d  value:  %16c\n",
             tok->tokenType, tok->val.charVal);
           break;
        case TOKEN_NUM:
            switch (tok->dataType) {
              case TYPE_INT:
                printf ("tokenType: %2d  type:  %4d %12d\n",
                  tok->tokenType, tok->dataType, tok->val.intVal);
                break;
              case  TYPE_REAL:
                printf ("tokenType: %2d  type:  %4d %12e\n",
                  tok->tokenType, tok->dataType, tok->val.floatVal);
                break;
            }
          break;
            
	 }
  }
