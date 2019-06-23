#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "lexcial.h"

int main()          /* Calls yylex repeatedly to test */
  { 
    int res, done;
    extern TOKEN yylval;
    printf("Started scanner test.\n");
    done = 0;
    while (done == 0)
      {
        res = yylex();    /* yylex is the entry point to the lex program */
        if (res != 0)
           {
             printf("yylex() = %4d   ", res);
             printtoken(yylval);
           }
           else done = 1;
      }
    return 0;
  }
