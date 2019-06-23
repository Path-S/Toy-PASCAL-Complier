#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include"token.h"
#include"geninter.h"
int rnum=0;
int lnum=0;
FILE *INTCODE;
void genc(TOKEN tok,char *ret){
	//ppexpr(tok);
	char lop[1000];
	char rop[1000];
	char top[1000];
	int lfalse,ldefault;
	TOKEN sub;
	if(tok->tokenType==OPERATOR){
		switch (tok->tokenNo){
		case OP_ASSIGN:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"%s = %s\n",lop,rop);			
			break;
		case OP_PLUS:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"t%d =%s + %s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum);
			rnum++;
			return;
			break;			
		case OP_MINUS:
			genc(tok->firstOperand,lop);
			if(tok->firstOperand->next==NULL){
				fprintf(INTCODE,"t%d =0 - %s\n",rnum,lop);
				sprintf(ret,"t%d",rnum);
				rnum++;
			return;
			}
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"t%d =%s - %s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum);
			rnum++;
			return;
			break;
		case OP_MUL:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"t%d =%s * %s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			return;
			break;
		case OP_DIV://DIV_R?
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"t%d =%s / %s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum);
			rnum++;
			return;
			break;
		case OP_FLOAT:
			genc(tok->firstOperand,lop);
			sprintf(ret,"%s",lop);
			return;
		case OP_FIX:
			genc(tok->firstOperand,lop);
			sprintf(ret,"%s",lop);
			return;			
		case OP_AREF:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);//
			fprintf(INTCODE,"t%d =&%s + %s\n",rnum,lop,rop);
			sprintf(ret,"*t%d",rnum++);
			break;
		case OP_IF://至少三个儿子？
			genc(tok->firstOperand,lop);
			lfalse=lnum++;
			fprintf(INTCODE,"if_false %s goto L%d\n",lop,lfalse);
			genc(tok->firstOperand->next,rop);

			if(tok->firstOperand->next->next!=NULL){
				ldefault=lnum++;
				fprintf(INTCODE,"goto L%d\n",ldefault);
			}	
			fprintf(INTCODE,"LABEL L%d\n",lfalse);
			if(tok->firstOperand->next->next!=NULL)
				genc(tok->firstOperand->next->next,top);
			if(tok->firstOperand->next->next!=NULL)			
				fprintf(INTCODE,"LABEL L%d\n",ldefault);
			break;
		case OP_EQ:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s==%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;
		case OP_LT:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s<%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;
		case OP_LE:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s<=%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;			
		case OP_NE:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s!=%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;			
		case OP_GT:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s>%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;
		case OP_GE:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s>=%s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
			break;
		case OP_PROGN:
			sub=tok->firstOperand;
			while(sub){				
				genc(sub,lop);
				sub=sub->next;
			}
			break;
		case OP_LABEL:
			genc(tok->firstOperand,lop);
			fprintf(INTCODE,"LABEL SYS_L%s\n",lop);
			break;
		case OP_GOTO:
			genc(tok->firstOperand,lop);
			fprintf(INTCODE,"goto SYS_L%s\n",lop);
			break;
		case OP_FUNCALL:
			genc(tok->firstOperand,lop);
			genc(tok->firstOperand->next,rop);
			fprintf(INTCODE,"t%d=%s %s\n",rnum,lop,rop);
			sprintf(ret,"t%d",rnum++);
		default:
			break;
		}
	}
	else if(tok->tokenType==TOKEN_ID){		
		sprintf(ret,"%s",tok->val.stringVal);
		return;
	}
	else if(tok->tokenType==TOKEN_NUM){
		if(tok->dataType==TYPE_INT){
			sprintf(ret,"%d",tok->val.intVal);
			return;
		}
		else if(tok->dataType==TYPE_REAL){
			sprintf(ret,"%f",tok->val.floatVal);
			return;
		}		
	}
	else if (tok->tokenType==RESERVED){
		if(strcmp(tok->val.stringVal,"function")==0){
			fprintf(INTCODE,"_FUNCTION");
			sub=tok->firstOperand->next;
			while(sub){
				genc(sub,lop);
				fprintf(INTCODE,"_%s",lop);
				sub=sub->next;
			}
			fprintf(INTCODE,"_\n");
		}
		else
			sprintf(ret,"%s",tok->val.stringVal);
	}
	else if(tok->tokenType==TOKEN_CHAR){
		sprintf(ret,"%c",tok->val.charVal);
	}
	else if(tok->tokenType==TOKEN_STR){
		sprintf(ret,"%s",tok->val.stringVal);
	}
}


void genf(TOKEN tok,char *ret){
	TOKEN func;
	func=tok->firstOperand;
	genc(func,NULL);
	genc(func->next,NULL);

}
void codegenerator(TOKEN pcode){
	TOKEN name, fund, body; // program name, function declear, program body
	name = pcode->firstOperand;
	fund = name->next;
	char fname[1000];
	sprintf(fname,"%s_intercode.txt",name->val.stringVal);
	INTCODE=fopen(fname,"w");
	while (fund->tokenNo == OP_FUNDCL) {
		genf(fund,NULL);
		fund = fund->next;
	}
	fprintf(INTCODE,"__MAIN__\n");
	body = fund;
	genc(body,NULL);
 }