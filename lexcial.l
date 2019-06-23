%{
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "token.h"

int install_tokenVal(int type, int tokenNumber);

int yywrap();
void lexError();

TOKEN yylval;
int lineCount = 1;
%}

/*正则表达式*/
delim           [ \t]
spaces          {delim}+
letter          [A-Za-z]
digit           [0-9]
ID            {letter}(_|{letter}|{digit})*
integer         {digit}+
real            {digit}+(\.{digit}+)?(([E|e])[+|-]?{digit}+)?
annotation      (\{[^}]*\})
annotation_line (\/\/.*\n)
string          (\')
A [Aa]
B [Bb]
C [Cc]
D [Dd]
E [Ee]
F [Ff]
G [Gg]
H [Hh]
I [Ii]
J [Jj]
K [Kk]
L [Ll]
M [Mm]
N [Nn]
O [Oo]
P [Pp]
Q [Qq]
R [Rr]
S [Ss]
T [Tt]
U [Uu]
V [Vv]
W [Ww]
X [Xx]
Y [Yy]
Z [Zz]

/*匹配规则*/
%%

"("			{ return install_tokenVal(DELIMITER,LP); }
")"			{ return install_tokenVal(DELIMITER,RP); }
"["			{ return install_tokenVal(DELIMITER,LB); }
"]"			{ return install_tokenVal(DELIMITER,RB); }
".."		{ return install_tokenVal(DELIMITER,DOTDOT); }
","			{ return install_tokenVal(DELIMITER,COMMA); }
":"			{ return install_tokenVal(DELIMITER,COLON); }
";"			{ return install_tokenVal(DELIMITER,SEMI); }

"."			{ return install_tokenVal(OPERATOR,DOT); }
"+"			{ return install_tokenVal(OPERATOR,PLUS); }
"-"			{ return install_tokenVal(OPERATOR,MINUS); }
"*"			{ return install_tokenVal(OPERATOR,MUL); }
"/"			{ return install_tokenVal(OPERATOR,DIV); }
"<"			{ return install_tokenVal(OPERATOR,LT); }
"<="		{ return install_tokenVal(OPERATOR,LE); }
"="			{ return install_tokenVal(OPERATOR,EQ); }
"<>"		{ return install_tokenVal(OPERATOR,NE); }
">"			{ return install_tokenVal(OPERATOR,GT); }
">="		{ return install_tokenVal(OPERATOR,GE); }
":="		{ return install_tokenVal(OPERATOR,ASSIGN); }
"AND"		{ return install_tokenVal(OPERATOR,AND); }
"OR"        { return install_tokenVal(OPERATOR,OR); }
"NOT"       { return install_tokenVal(OPERATOR,NOT); }
"DIV"       { return install_tokenVal(OPERATOR,DIV); }
"MOD"|"%"	{ return install_tokenVal(OPERATOR,MOD); }

{A}{R}{R}{A}{Y}             { return install_tokenVal(RESERVED,ARRAY); }
{B}{E}{G}{I}{N}             { return install_tokenVal(RESERVED,BEGIN_T); }
{C}{A}{S}{E}                { return install_tokenVal(RESERVED,CASE); }
{C}{O}{N}{S}{T}             { return install_tokenVal(RESERVED,CONST); }
{D}{O}                      { return install_tokenVal(RESERVED,DO); }
{D}{O}{W}{N}{T}{O}          { return install_tokenVal(RESERVED,DOWNTO); }
{E}{L}{S}{E}                { return install_tokenVal(RESERVED,ELSE); }
{E}{N}{D}					{ return install_tokenVal(RESERVED,END); }
{F}{O}{R}					{ return install_tokenVal(RESERVED,FOR); }
{F}{U}{N}{C}{T}{I}{O}{N}	{ return install_tokenVal(RESERVED,FUNCTION); }
{G}{O}{T}{O}				{ return install_tokenVal(RESERVED,GOTO); }
{I}{F}						{ return install_tokenVal(RESERVED,IF); }
{I}{N}						{ return install_tokenVal(RESERVED,IN); }
{O}{F}						{ return install_tokenVal(RESERVED,OF); }
{P}{A}{C}{K}{E}{D}			{ return install_tokenVal(RESERVED,PACKED); }
{P}{R}{O}{C}{E}{D}{U}{R}{E}	{ return install_tokenVal(RESERVED,PROCEDURE); }
{P}{R}{O}{G}{R}{A}{M}		{ return install_tokenVal(RESERVED,PROGRAM); }
{R}{E}{A}{D}				{ return install_tokenVal(RESERVED,READ); }
{R}{E}{C}{O}{R}{D}			{ return install_tokenVal(RESERVED,RECORD); }
{R}{E}{P}{E}{A}{T}			{ return install_tokenVal(RESERVED,REPEAT); }
{S}{E}{T}					{ return install_tokenVal(RESERVED,SET); }
{T}{H}{E}{N}				{ return install_tokenVal(RESERVED,THEN); }
{T}{O}						{ return install_tokenVal(RESERVED,TO); }
{T}{Y}{P}{E}				{ return install_tokenVal(RESERVED,TYPE); }
{U}{N}{T}{I}{L}				{ return install_tokenVal(RESERVED,UNTIL); }
{V}{A}{R}					{ return install_tokenVal(RESERVED,VAR); }
{W}{H}{I}{L}{E}				{ return install_tokenVal(RESERVED,WHILE); }
{W}{I}{T}{H}				{ return install_tokenVal(RESERVED,WITH); }

{spaces}
{annotation}	    
{annotation_line}	lineCount++; 
"\n"		{ lineCount++; }

{T}{R}{U}{E}|{F}{A}{L}{S}{E}|{M}{A}{X}{I}{N}{T}     { return install_tokenVal(RESERVED,SYS_CON);}
{A}{B}{S}|{C}{H}{R}|{O}{D}{D}|{O}{R}{D}             { return install_tokenVal(RESERVED,SYS_FUNCT);}
{P}{R}{E}{D}|{S}{Q}{R}|{S}{Q}{R}{T}|{S}{U}{C}{C}    { return install_tokenVal(RESERVED,SYS_FUNCT);}
{W}{R}{I}{T}{E}|{W}{R}{I}{T}{E}{L}{N}               { return install_tokenVal(RESERVED,SYS_PROC);}
{I}{N}{T}{E}{G}{E}{R}|{B}{O}{O}{L}{E}{A}{N}         { return install_tokenVal(RESERVED,SYS_TYPE);}
{C}{H}{A}{R}|{R}{E}{A}{L}|{S}{T}{R}{I}{N}{G}        { return install_tokenVal(RESERVED,SYS_TYPE);}

{ID}		{
            yylval = (TOKEN)malloc(sizeof(struct tokenstruct));
            yylval->tokenType = TOKEN_ID;
            int i, c, n;
	        n = yyleng;			
            if (n > 15) {
                n = 15;
            }
	
            for (i = 0; i < n; i++) {
                c = yytext[i];
                yylval->val.stringVal[i] = c;
            }
            yylval->val.stringVal[n] = '\0';
            
            return ID;
            }
{string}	{
            /* string max length = 15 */
            yylval = (TOKEN)malloc(sizeof(struct tokenstruct));		/* Make new token, set yylval to point to it */
            
            int len = 0;
            char c;
            while ((c = input()) != '\'') {
                if (len < 15) yylval->val.stringVal[len] = c;
                len++;
            }
            if (len > 15) len = 15;
            
            if (len == 1) {
                yylval->val.charVal = yylval->val.stringVal[0];
                yylval->tokenType = TOKEN_CHAR;
                yylval->dataType = TYPE_CHAR;
                return CONST_CHAR;
            }
            else {
                yylval->val.stringVal[len] = '\0';
                yylval->tokenType = TOKEN_STR;
                yylval->dataType = TYPE_STR;
                return CONST_STR;
            }
	
}
{integer}	{
            yylval = (TOKEN)malloc(sizeof(struct tokenstruct));
            yylval->tokenType = TOKEN_NUM;
            yylval->dataType = TYPE_INT;
            
            int num;
            sscanf(yytext, "%i", &num);
            yylval->val.intVal = num;
            return CONST_INT;
            }
{real}		{
            yylval = (TOKEN)malloc(sizeof(struct tokenstruct));
            yylval->tokenType = TOKEN_NUM;
            yylval->dataType = TYPE_REAL;
            
            float num;
            sscanf(yytext, "%f", &num);
            yylval->val.floatVal = num;
            return CONST_REAL;
            }

.			{lexError(); }

%%

int install_tokenVal(int type, int tokenNumber){
    yylval = (TOKEN)malloc(sizeof(struct tokenstruct));
    yylval->tokenType = type;
    yylval->tokenNo = tokenNumber;
    if (type == RESERVED) {
		yylval->tokenNo = tokenNumber - RESERVED_BIAS;
		/* store those strings */
		int i;
		for (i = 0; i < yyleng; i++) {
			yylval->val.stringVal[i] = tolower(yytext[i]);
		}
		yylval->val.stringVal[yyleng] = '\0';
	}
	else if (type == OPERATOR) {
		yylval->tokenNo = tokenNumber - OPERATOR_BIAS;
	}
	else if (type == DELIMITER) {
		yylval->tokenNo = tokenNumber - DELIMITER_BIAS;
	}
	else {
		yylval->tokenNo = tokenNumber;
	}
    return tokenNumber;
}

void lexError() {
	printf("Lexical Analysis Error at line %d\n", lineCount);
}

int yywrap() {  return 1;  }