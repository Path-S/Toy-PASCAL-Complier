#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "lexcial.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"

#define COLMAX 100
#define ROWMAX 20
#define INFOMAX 100
char* opprint[]  = {
	" ", ".", "+", "-", "*", "/",
	"<", "<=", "=", "<>", ">", ">=", ":=",
    "and", "or", "not", "div", "mod", "^",
    "in", "if", "goto", "progn", "label", "funcall",
    "aref", "program", "float", "fix", "fundcl",
};

int opsize[] = {
	1, 1, 1, 1, 1, 1,
	1, 2, 1, 2, 1, 2, 2,
	3, 2, 3, 3, 3, 1,
	2, 2, 4, 5, 5, 7,
	4, 7, 5, 3, 6,
};
char tree[ROWMAX][COLMAX][INFOMAX];
int COL[ROWMAX]={0};
/* print a token for debugging */

/* find length of a string */
int strlength(char str[]) {
	int i, n;
	n = 16;
	for (i = 0; i < 16; i++)
		if ( str[i] == '\0' && n == 16 ) n = i;
	return n;
}

void Printtok(char *dad,TOKEN tok,int row) {
	switch (tok->tokenType) {
		case TOKEN_ID:
			sprintf (tree[row][COL[row]++],"%s%s ",dad,tok->val.stringVal);
			break;
    	case TOKEN_STR:
    	  	sprintf (tree[row][COL[row]++],"%s'%s' ",dad,tok->val.stringVal);
      		break;
		case RESERVED: 
			sprintf (tree[row][COL[row]++],"%s%s ",dad,tok->val.stringVal);
			break;
    	case TOKEN_CHAR:
			sprintf (tree[row][COL[row]++],"%s'%c' ",dad,tok->val.charVal);
      		break;
		case TOKEN_NUM:
			switch (tok->dataType) {
			case TYPE_INT:
				sprintf (tree[row][COL[row]++],"%s%d ", dad,tok->val.intVal);
				break;
			case  TYPE_REAL:
				sprintf (tree[row][COL[row]++],"%s%e ",dad,tok->val.floatVal);
				break;
			}
		break;
		case DELIMITER: case OPERATOR:
			break;
	}
	return;
}



void Printexpr(char *dad,TOKEN tok,int row) {
	TOKEN opnds; int i;
	char dname[1000];

	if (strcmp(tok->val.stringVal,"function")==0||strcmp(tok->val.stringVal,"procedure")==0) {
		if(strcmp(tok->val.stringVal,"function")==0){
			sprintf(tree[row][COL[row]],"%s%s ",dad,"function");
			sprintf(dname,"[col%d %s]",COL[row],"function");
			//printf ("[%d,%d]:function \n",row,COL[row]);
		}
		else{
			sprintf(tree[row][COL[row]],"%s%s ",dad,"procedure");
			sprintf(dname,"[col%d %s]",COL[row],"procedure");
			//printf("[%d,%d]:procedure \n",row,COL[row]);
		}
		COL[row]++;
		opnds = tok->firstOperand;
		row++;
		while (opnds != NULL) {		
			Printexpr(dname,opnds,row);
			opnds = opnds->next;
			sprintf(dname,"%s"," ");
		}
	}

	else if (tok->tokenType == OPERATOR) {
		sprintf(tree[row][COL[row]],"%s%s ",dad,opprint[tok->tokenNo]);
		sprintf(dname,"[col%d %s]",COL[row],opprint[tok->tokenNo]);
		//printf ("[%d,%d]:%s\n", row,COL[row],opprint[tok->tokenNo]);
		//printf("dname is%s\n",dname);
		COL[row]++;
		opnds = tok->firstOperand;
		row++;
		while (opnds != NULL) {					
			Printexpr(dname,opnds,row);
			opnds = opnds->next;
			sprintf(dname,"%s","");

		}
	}
	else {
		sprintf(dname,"%s",dad);
		Printtok(dname,tok,row);
		}
}
void Ppexpr(TOKEN tok) {
	char ini[]="";
	if ( (long) tok <= 0 ) {
		printf("token invaid! %ld\n", (long)tok);
		return;
	}
	else
		printf("--------------print AST------------------\n");
	
	for(int i=0;i<ROWMAX;i++){
		for(int j=0;j<COLMAX;j++)
			sprintf(tree[i][j],"%s","NONE");
	}
	Printexpr(ini,tok,0);
	for(int i=0;i<ROWMAX;i++){
		if(strcmp(tree[i][0],"NONE")==0)
			break;
		for(int j=0;j<COLMAX;j++){
			if(strcmp(tree[i][j],"NONE")!=0){
				printf("%s",tree[i][j]);
				}
			else
				break;
			
		}
		printf("\n");
	}
}