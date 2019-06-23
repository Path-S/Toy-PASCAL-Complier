
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"
#include "lexcial.h"
#include "symtab.h"
#include "parse.h"

#define YYSTYPE TOKEN

TOKEN parseresult;
extern int lineCount;


%}


%token ID CONST_STR CONST_INT CONST_REAL CONST_CHAR   /* token types */

%token LP RP LB RB DOTDOT COMMA COLON SEMI    /* Delimiters */

%token DOT PLUS MINUS MUL DIV_R LT LE EQ NE GT GE ASSIGN
%token AND OR NOT DIV MOD /* Operator */

%token ARRAY BEGIN_T CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO
%token IF IN OF PACKED PROCEDURE PROGRAM READ RECORD REPEAT SET THEN
%token TO TYPE UNTIL VAR WHILE WITH
%token SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE	/* reserved */

%%


program			: program_head routine DOT			{ parseresult = genTokenProgram($1, $2); }
				;
program_head	: PROGRAM ID SEMI					{ $$ = $2; }
				;
routine			: routine_head routine_body			{ $$ = linkBrothers($1, $2); }
				;
sub_routine		: routine_head routine_body			{ $$ = linkBrothers($1, $2); }
				;

routine_head	: label_part const_part type_part var_part routine_part
													{ $$ = afterDecl($5); }	// definitions are not in code tree
				;
label_part		: // empty
				;
// const part
const_part		: CONST const_expr_list				{ $$ = NULL; }
				| // empty
				;
const_expr_list	: const_expr_list ID EQ const_value SEMI
													{ genSymConst($2, $4); }
				| ID EQ const_value SEMI			{ genSymConst($1, $3); }
				;
const_value		: CONST_INT							{ $$ = $1; }
				| CONST_REAL						{ $$ = $1; }
				| CONST_CHAR						{ $$ = $1; }
				| CONST_STR							{ $$ = $1; }
				| SYS_CON							{ $$ = $1; }
				;
// type part
type_part		: TYPE type_decl_list				{ $$ = NULL; }		// no nodes
				| // empty
				;
type_decl_list	: type_decl_list type_definition	{ $$ = NULL; }
				| type_definition					{ $$ = NULL; }
				;
type_definition	: ID EQ type_decl SEMI				{ genSymType($1, $3); }
				;
type_decl		: simple_type_decl					{ $$ = $1; }
				| array_type_decl					{ $$ = $1; }
				| record_type_decl					{ $$ = $1; }
				;
simple_type_decl: SYS_TYPE							{ $$ = findType($1); }
				| ID								{ $$ = findType($1); }
				| LP id_list RP						{ $$ = genSymEnum($2); }
				| const_value DOTDOT const_value	{ $$ = genSymDotdot($1, $2, $3); }
				| ID DOTDOT ID						{ $$ = genSymDotdot($1, $2, $3); }
				;
array_type_decl	: ARRAY LB simple_type_decl RB OF type_decl
													{ $$ = genSymArray($3, $6); }		// instarray
				;
record_type_decl: RECORD field_decl_list END		{ $$ = instRec($1, $2); }		// intrec
				;
field_decl_list	: field_decl_list field_decl		{ $$ = linkBrothers($1, $2); }
				| field_decl						{ $$ = $1; }
				;
field_decl		: id_list COLON type_decl SEMI		{ $$ = instFields($1, $3);; }	// instfields
				;
id_list			: id_list COMMA ID					{ $$ = linkBrothers($1, $3); }
				| ID								{ $$ = $1; }
				;
// var part
var_part		: VAR var_decl_list					{ afterVarDecl(); }
				| /* empty */						{ afterVarDecl(); }
				;
var_decl_list	: var_decl_list var_decl			{ $$ = NULL; }
				| var_decl							{ $$ = NULL; }
				;
var_decl		: id_list COLON type_decl SEMI		{ genSymVars($1, $3); }
				;
// routine part
routine_part	: routine_part function_decl		{ $$ = linkBrothers($1, $2); }
				| routine_part procedure_decl		{ $$ = linkBrothers($1, $2); }
				| function_decl						{ $$ = $1; }
				| procedure_decl					{ $$ = $1; }
				| /* empty */						{ $$ = NULL; }
				;
function_decl	: function_head SEMI sub_routine SEMI
													{ $$ = genTokenFuncDecl($1, $3); }
				;
function_head	: FUNCTION ID parameters COLON simple_type_decl
													{ $$ = genSymFunc(linkBrothers($1, linkBrothers($2, linkBrothers($5, $3)))); } // FUNCTION, ID, type, para
				;
procedure_decl	: procedure_head SEMI sub_routine SEMI
													{ $$ = genTokenFuncDecl($1, $3); }
				;
procedure_head	: PROCEDURE ID parameters			{ $$ = genSymFunc(linkBrothers($1, linkBrothers($2, $3))); }	// PROCEDURE, ID, para
				;
parameters		: LP para_decl_list RP				{ $$ = $2; }
				| /* empty */						{ $$ = NULL; }
				;
para_decl_list	: para_decl_list SEMI para_type_list
													{ $$ = linkBrothers($1, $3); }
				| para_type_list					{ $$ = $1; }
				;
para_type_list	: var_para_list COLON simple_type_decl
													{ $$ = $1, genSymVars($1, $3); }
				| val_para_list COLON simple_type_decl
													{ $$ = $1, genSymVars($1, $3); }
				;
var_para_list	: VAR id_list						{ $$ = $2; }
				;
val_para_list	: id_list							{ $$ = $1; }
				;

// routine body
routine_body	: compound_stmt						{ $$ = $1; }
				;
compound_stmt	: BEGIN_T stmt_list END				{ $$ = genTokenProgn($1, $2); }
				;
stmt_list		: stmt_list stmt SEMI				{ $$ = linkBrothers($1, $2); }
				| /* empty*/						{ $$ = NULL; }
				;
stmt			: CONST_INT COLON non_label_stmt	{ $$ = doLabel($1, $2, $3); }	// TODO: bug
				| non_label_stmt					{ $$ = $1; }
				;
non_label_stmt	: assign_stmt						{ $$ = $1; }
				| proc_stmt							{ $$ = $1; }
				| compound_stmt						{ $$ = $1; }
				| if_stmt							{ $$ = $1; }
				| repeat_stmt						{ $$ = $1; }
				| while_stmt						{ $$ = $1; }
				| for_stmt							{ $$ = $1; }
				| case_stmt							{ $$ = $1; }
				| goto_stmt							{ $$ = $1; }
				;
assign_stmt		: ID ASSIGN expression				{ $$ = genTokenBinOperator($2, findId($1), $3); }
				| ID LB expression RB ASSIGN expression	// array[i], index from 1 defaut
													{ $$ = genTokenBinOperator($5, arrayRef($1, NULL, $3, NULL), $6); }
				| ID DOT ID ASSIGN expression		{ $$ = genTokenBinOperator($4, reduceDot($1, $2, $3), $5); }
				;
proc_stmt		: ID								{ $$ = genTokenFuncall($1, NULL, NULL); }
				| ID LP args_list RP				{ $$ = genTokenFuncall($2, $1, $3); }
				//| SYS_PROC						{ $$ = NULL; }	// what is it ???
				| SYS_PROC LP expression_list RP	{ $$ = genTokenFuncall($2, $1, $3); }
				| READ LP factor RP					{ $$ = genTokenFuncall($2, $1, $3); }
				;
if_stmt			: IF expression THEN stmt else_clause		
													{ $$ = genTokenIF($1, $2, $4, $5); }
				;
else_clause		: ELSE stmt							{ $$ = $2; }
				| // empty
				;
repeat_stmt		: REPEAT stmt_list UNTIL expression	{ $$ = genTokenRepeat($2, $4); }
				;
while_stmt		: WHILE expression DO stmt			{ $$ = genTokenWhile($2, $4); }
				;
for_stmt		: FOR ID ASSIGN expression direction expression DO stmt
													{ $$ = genTokenFor(genTokenBinOperator($3, $2, $4), $5, $6, $8); }
				;
direction		: TO								{ $$ = $1; }
				| DOWNTO							{ $$ = $1; }
				;
case_stmt		: CASE expression OF case_expr_list END
													{ $$ = NULL; }	// TODO
				;
case_expr_list	: case_expr_list case_expr			{ $$ = NULL; }
				| case_expr							{ $$ = NULL; }
				;
case_expr		: const_value COLON stmt SEMI		{ $$ = NULL; }
				| ID COLON stmt SEMI				{ $$ = NULL; }
				;
goto_stmt		: GOTO CONST_INT					{ $$ = doGoto($1, $2); }	// useless
				;
expression_list	: expression_list COMMA expression	{ $$ = linkBrothers($1, $2); }
				| expression						{ $$ = $1; }
				;
expression		: expression GE expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expression GT expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expression LE expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expression LT expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expression EQ expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expression NE expr				{ $$ = genTokenBinOperator($2, $1, $3); }
				| expr								{ $$ = $1; }
				;
expr			: expr PLUS term					{ $$ = genTokenBinOperator($2, $1, $3); }
				| expr MINUS term					{ $$ = genTokenBinOperator($2, $1, $3); }
				| expr OR term						{ $$ = genTokenBinOperator($2, $1, $3); }
				| term								{ $$ = $1; }
				;
term			: term MUL factor					{ $$ = genTokenBinOperator($2, $1, $3); }
				| term DIV factor					{ $$ = genTokenBinOperator($2, $1, $3); }
				| term MOD factor					{ $$ = genTokenBinOperator($2, $1, $3); }
				| term AND factor					{ $$ = genTokenBinOperator($2, $1, $3); }
				| factor							{ $$ = $1; }
				;
factor			: ID								{ $$ = findId($1); }
				| ID LP args_list RP				{ $$ = genTokenFuncall($2, $1, $3); }
				//| SYS_FUNCT						{ $$ = NULL; }	// what is it ???
				| SYS_FUNCT LP args_list RP			{ $$ = genTokenFuncall($2, $1, $3); }
				| const_value						{ $$ = $1; }
				| LP expression RP					{ $$ = $2; }
				| NOT factor						{ $$ = genTokenUnaryOp($1, $2); }
				| MINUS factor						{ $$ = genTokenUnaryOp($1, $2); }
				| ID LB expression RB				{ $$ = arrayRef($1, NULL, $3, NULL); }
				| ID DOT ID							{ $$ = reduceDot($1, $2, $3); }
				;
args_list		: args_list COMMA expression		{ $$ = linkBrothers($1, $3); }
				| expression						{ $$ = $1; }

%%
int yyerror(s) char *s; {
	fprintf(stderr, "Parser Error at line %d: %s\n", lineCount, s);
	return 0;
}

