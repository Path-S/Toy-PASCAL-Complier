
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexcial.h"
#include "symtab.h"
#include "parse.h"

extern int lineCount;
extern int blocknumber;

int labelCount = 1; //label0 is the statr pos of program
void semanticError(char* s) {
	fprintf(stderr, "semantic Error at line %d: %s\n", lineCount, s);
    exit(0);
}
void semanticWarning(char* s) {
	fprintf(stderr, "semantic Warning at line %d: %s\n", lineCount, s);
}


TOKEN genTokenProgram(TOKEN programHead, TOKEN routine)
{
    if(DEBUG){
        printf("start genProgramToken\n");
    }

    TOKEN out = genOperatorToken(OP_PROGRAM);
    if(!out){
        printf("genOprator failed at genProgramToken().\n");
        return NULL;
    }

    //create the root of the parsetree
    out->firstOperand = programHead;
    programHead->next = routine;
    if(DEBUG){
        printf("end genProgramToken\n");
    }
    return out;
}

TOKEN genOperatorToken(int whichOp)
{
    if(DEBUG){
        printf("start genOperatorToken\n");
    }
    TOKEN out = talloc();
    if(!out){
        printf("Failed to alloc TOKEN at genOperatorToken().\n");
        return NULL;
    }

    out->tokenType = OPERATOR;
    out->tokenNo = whichOp;
    if(DEBUG){
        printf("end genOperatorToken\n");
    }
    return out;
}

TOKEN linkBrothers(TOKEN origin, TOKEN newSon)
{
    if(DEBUG){
        printf("start linkBrothers\n");
    }
    if(origin == NULL) return newSon;   //if there is no origin, newSon will be the first son
    TOKEN tok = origin;
    while (tok->next != NULL)
        tok = tok->next;

    tok->next = newSon;
    if(DEBUG){
        printf("end linkBrothers\n");
    }
    return origin;
}

TOKEN afterDecl(TOKEN decl)
{
    if(DEBUG){
        printf("start afterDecl\n");
    }
    blocknumber = contblock[blocknumber];

    if(DEBUG){
        printf("end afterDecl\n");
    }
    return decl;
}


void genSymConst(TOKEN IDtoken, TOKEN constToken)
{
    if(DEBUG){
        printf("start genSymConst\n");
    }    
    SYMBOL sym;

    sym = insertsym(IDtoken->val.stringVal);
    sym->kind = SYM_CONST;
    sym->basicType = constToken->dataType;
    
    //if SYS_CON
    if(constToken->tokenType == RESERVED && constToken->tokenNo == SYS_CON-RESERVED_BIAS)
    {
        if(strcmp(constToken->val.stringVal,"true")==0){
            sym->basicType = TYPE_BOOL;
            sym->constval.intNum = 1;
            sym->size = basicsizes[TYPE_BOOL];
        }
        else if(strcmp(constToken->val.stringVal, "false")==0){
            sym->basicType = TYPE_BOOL;
            sym->constval.intNum = 0;
            sym->size = basicsizes[TYPE_BOOL];
        }
        else if(strcmp(constToken->val.stringVal, "maxint")==0){
            sym->basicType = TYPE_INT;
            sym->constval.intNum = INT_MAX;
            sym->size = basicsizes[TYPE_INT];
        }
    }
    //if integer
    else if(sym->basicType == TYPE_INT){
        sym->constval.intNum = constToken->val.intVal;
        sym->size = basicsizes[TYPE_INT];
    }
    else if(sym->basicType == TYPE_FLOAT){
        sym->constval.realNum = constToken->val.floatVal;
        sym->size = basicsizes[TYPE_FLOAT];
    }
    else if(sym->basicType == TYPE_STRING){
        strncpy(sym->constval.stringConst,constToken->val.stringVal,16);
        sym->size = basicsizes[TYPE_STRING];        
    }
    else if(sym->basicType == TYPE_CHAR){
        sym->constval.charConst = constToken->val.charVal;
        sym->size = basicsizes[TYPE_CHAR];
    }
    if(DEBUG){
        printf("end genSymConst\n");
    }   
}
void genSymType(TOKEN typeName, TOKEN typeToken)
{
    if(DEBUG){
        printf("start genSymType\n");
    }       
    SYMBOL sym, typeOfSym;
    typeOfSym = typeToken->symType;

    //ensure the sym is unique
    sym = searchst(typeName->val.stringVal);
    if(sym){
        char s[32];
        sprintf(s,"type \"%s\" redefinition",typeName->val.stringVal);
        semanticError("type \"%s\" redefinition");
        return;
    }

    sym = insertsym(typeName->val.stringVal);
    sym->kind = SYM_TYPE;
    sym->size = typeOfSym->size;
    sym->dataType = typeOfSym;
    sym->basicType = typeOfSym->basicType;
    if(DEBUG){
        printf("end genSymType\n");
    }   
}

TOKEN genSymEnum(TOKEN IDs)
{
    if(DEBUG){
        printf("start genSymEnum\n");
    }  
    int size;
    TOKEN temp = IDs;
    while(temp){
        genSymConst(temp, genTokenConstInt(size++));
        temp = temp->next;
    }

    TOKEN subrangeToken = genTokenSubrange(IDs,0,size-1);
    if(DEBUG){
        printf("end genSymEnum\n");
    }  
    return subrangeToken;
}

TOKEN genTokenConstInt(int num)
{
    if(DEBUG){
        printf("start genTokenConstInt\n");
    }  
    TOKEN out = talloc();
    if(!out){
        printf("Failed to alloc TOKEN at genConstIntToken().\n");
        return NULL;
    }
    out->tokenType = TOKEN_NUM;
    out->dataType = TYPE_INT;
    out->val.intVal = num;
    if(DEBUG){
        printf("end genTokenConstInt\n");
    }  
    return out;
}

TOKEN findType(TOKEN tok)
{
    if(DEBUG){
        printf("start findType\n");
    }      
    SYMBOL foundSym;
    foundSym = searchst(tok->val.stringVal);

    //if the type is not defied
    if(!foundSym){
        char s[32];
        sprintf(s,"type \"%s\" not defined",tok->val.stringVal);
        semanticError(s);
		return NULL;
    }

    if(foundSym->kind == SYM_BASIC){
        tok->dataType = foundSym->basicType;
        tok->symType = foundSym;
    }
    else
        tok->symType = foundSym->dataType;
    if(DEBUG){
        printf("end findType\n");
    }    
    return tok;
}

TOKEN genTokenSubrange(TOKEN tok, int low, int high)
{
    if(DEBUG){
        printf("start genTokenSubrange\n");
    }    
    TOKEN out = TokenCopyConstruct(tok);

    SYMBOL subrangeSym = symalloc();
    subrangeSym->kind = SYM_SUBRANGE;
    subrangeSym->basicType = TYPE_INT;
    subrangeSym->lowBound = low;
    subrangeSym->highBound = high;
    subrangeSym->size = basicsizes[TYPE_INT];

    out->symType = subrangeSym;
    if(DEBUG){
        printf("end genTokenSubrange\n");
    }
    return out;
}

TOKEN TokenCopyConstruct(TOKEN origin)
{
    if(DEBUG){
        printf("start TokenCopyConstruct\n");
    }
    TOKEN out = talloc();
    if(origin == NULL){
        printf(" Failed to alloc TOKEN at TokenCopyConstruct().\n");
		return NULL;
    }

    out->tokenType = origin->tokenType;
    out->dataType = origin->dataType;
    out->symType = origin->symType;
    out->symEntry = origin->symEntry;
    out->firstOperand = origin->firstOperand;
    out->next = origin->next;

    if(origin->val.stringVal[0]!= 0){   
        strncpy(out->val.stringVal,origin->val.stringVal,16);
    }
    else if(origin->tokenNo != -1){
        out->tokenNo = origin->tokenNo;
    }
    else if(origin->val.floatVal != -DBL_MIN){
        out->val.floatVal = origin->val.floatVal;
    }
    else{
        out->val.intVal = origin->val.intVal;
    }
    if(DEBUG){
        printf("end TokenCopyConstruct\n");
    }
    return out;

}

TOKEN genSymDotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok)
{
    if(DEBUG){
        printf("start genSymDotdot\n");
    }    
    int lowb,highb;
    if(lowtok->tokenType == TOKEN_ID && hightok->tokenType == TOKEN_ID){
        SYMBOL sym1 = searchst(lowtok->val.stringVal);
        SYMBOL sym2 = searchst(hightok->val.stringVal);
      if (sym1->kind == SYM_CONST && sym2->kind == SYM_CONST &&
			sym1->basicType == TYPE_INT && sym2->basicType == TYPE_INT) {
			lowb = sym1->constval.intNum;
			highb = sym2->constval.intNum;
		}
		else {
			semanticError("wrong type for DOTDOT");
			return NULL;
		}
    }
	else if (lowtok->tokenType == TOKEN_NUM && hightok->tokenType == TOKEN_NUM &&
		lowtok->dataType == TYPE_INT && hightok->dataType == TYPE_INT) {
		lowb = lowtok->val.intVal;
		highb = hightok->val.intVal;
	}
	else {
		semanticError("wrong type for DOTDOT");
		return NULL;
	}

    TOKEN out = genTokenSubrange(dottok,lowtok->val.intVal,hightok->val.intVal);
    if(DEBUG){
        printf("end genSymDotdot\n");
    }       
    return out;
}

TOKEN genSymArray(TOKEN bounds, TOKEN typetok)
{
	if (DEBUG) {
        printf("begin genSymArray\n");
	}
	
	// bounds->symType->[low/highBound]
	
	TOKEN curr_bound = bounds;
	SYMBOL prev_sym = NULL;
	
	SYMBOL typesym = searchst(typetok->val.stringVal);
	int low, high;
	
	if (!typesym) {
		char s[64];
		sprintf(s, "type \"%s\" not defined", typetok->val.stringVal);
		semanticError(s);
		return NULL;
	}
	
	while (curr_bound) {
		SYMBOL arrsym = symalloc();
		arrsym->kind = SYM_ARRAY;
		
		if (typesym) {
			arrsym->dataType = typesym;
		}
		else {
			//       arrsym->basicType = typetok->dataType;
		}
		
		low = curr_bound->symType->lowBound;
		high = curr_bound->symType->highBound;
		
		if (!prev_sym) {
			arrsym->size = (high - low + 1) * typesym->size;
		}
		else {
			arrsym->dataType = typetok->symType;
			arrsym->size = (high - low + 1) * prev_sym->size;
		}
		
		typetok->symType = arrsym;
		prev_sym = arrsym;
		
		arrsym->lowBound = low;
		arrsym->highBound = high;
		
		curr_bound = curr_bound->next;
	}
	
	if (DEBUG) {
		printf(" Finished instArray().\n");
	}
	
	return typetok;
}


TOKEN instRec(){}//todo

void afterVarDecl() {
    if(DEBUG){
        printf("start afterVarDecl\n");
    }
	int thisblock = blocknumber;
	blocknumber++;
	contblock[blocknumber] = thisblock;
    if(DEBUG){
        printf("end afterVarDecl\n");
    }
}

int wordaddress(int n, int wordsize) {
	return ((n + wordsize - 1) / wordsize) * wordsize;
}

void genSymVars(TOKEN IDs, TOKEN typeToken)
{
    if(DEBUG){
        printf("start genSymVars\n");
    }
    SYMBOL sym;
    int align = alignsize(typeToken->symType);
    TOKEN temp = IDs;
    while(temp!=NULL){
        sym = searchst(temp->val.stringVal);
        if(sym){
            char s[32];
            sprintf(s, "redefinition of var \"%s\"", IDs->val.stringVal);
			semanticError(s);
			return;           
        }
        sym = insertsym(temp->val.stringVal);
        sym->kind = SYM_VAR;
        sym->offset = wordaddress(blockoffs[blocknumber], align);
        sym->size = typeToken->symType->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        sym->dataType = typeToken->symType;
        sym->basicType = typeToken->symType->basicType;
        //if type is a defined array type, basic type will be determined recursived
        if(typeToken->symType->dataType && typeToken->symType->dataType->kind == SYM_ARRAY){
            SYMBOL temp2 = typeToken->symType->dataType;
            while(temp2->kind==SYM_ARRAY && temp2){
                temp2 = temp2->dataType;
            }
            //here we come to the basic type of the array
            sym->basicType = temp2->basicType;
        }
        else    
            sym->basicType = typeToken->symType->basicType;
        temp = temp->next;
    }
    if(DEBUG){
        printf("end genSymVars\n");
    }
}

TOKEN genTokenFuncDecl(TOKEN head, TOKEN body)
{
    if(DEBUG){
        printf("start genTokenFuncDecl\n");
    }
    TOKEN funcdeclToken = genOperatorToken(OP_FUNDCL);
    if (!funcdeclToken) {
		printf(" Failed to alloc TOKEN(s) at genTokenFuncDecl().\n");
		return NULL;
	}
    funcdeclToken->firstOperand = head;
    head->next = body;

    lastblock = blocknumber;
    blockoffs[blocknumber++]=0;
    contblock[blocknumber] = contblock[lastblock];
    if(DEBUG){
        printf("end genTokenFuncDecl\n");
    }
    return funcdeclToken;
}

TOKEN genSymFunc(TOKEN head) //FUNCTION ID type para
{
    if(DEBUG){
        printf("start genSymFunc\n");
    }
    TOKEN funID = head->next;

    //function
    if(strcmp(head->val.stringVal,"function") == 0) {
        TOKEN type = funID->next;
        TOKEN paras = type->next; 
        SYMBOL typeSym = searchst(type->val.stringVal);
        SYMBOL parasSym = symalloc();
        SYMBOL temp = parasSym;
        if(DEBUG){
           printf("======1\n");
        }
        while(paras){
            SYMBOL thisParaSym = searchst(paras->val.stringVal);
            if(!thisParaSym){
                printf("can't find symbol %s at genSymFunc\n",paras->val.stringVal);
                return NULL;
            }
            SYMBOL nextLevelSym = symalloc();
            if(!nextLevelSym){
                printf("failed to alloc Symbol at genSymFunc\n");
                return NULL;
            }
            nextLevelSym->kind = SYM_ARGLIST;
            nextLevelSym->basicType = thisParaSym->basicType;
            temp->dataType = nextLevelSym;
            temp = nextLevelSym;
            paras = paras->next;
            if(DEBUG){
                printf("======4\n");
            }
        }

        insertfnx(funID->val.stringVal,typeSym,parasSym);
        // insert "_funname" variable
		TOKEN new_var = talloc();
		int i;
		new_var->val.stringVal[0] = '_';
		for (i = 1; i < 16; i++) {
			new_var->val.stringVal[i] = funID->val.stringVal[i-1];
		}
		new_var->tokenType = TOKEN_ID;
		
		genSymVars(new_var, findType(type));

    }
    //procedure
    else if(strcmp(head->val.stringVal,"procedure") == 0){
        TOKEN paras = funID->next; 
        SYMBOL parasSym = symalloc();
        SYMBOL temp = parasSym;
        while(paras){
            SYMBOL thisParaSym = searchst(paras->val.stringVal);
            SYMBOL nextLevelSym = symalloc();
            nextLevelSym->kind = SYM_ARGLIST;
            nextLevelSym->basicType = thisParaSym->basicType;
            temp->dataType = nextLevelSym;
            temp = nextLevelSym;
            paras = paras->next;
        }
        insertfnx(funID->val.stringVal,NULL,parasSym);
    }

    TOKEN funBlockNum = genTokenConstInt(blocknumber);
    head->firstOperand = funBlockNum;
    funBlockNum->next = funID;
    if(DEBUG){
        printf("end genSymFunc\n");
    }
    return head;
}

TOKEN binTypeCoerce(TOKEN op, TOKEN lhs, TOKEN rhs) {
    if(DEBUG){
        printf("start binTypeCoerce\n");
    }	
	TOKEN cast_tok;

	int lhs_dataType = lhs->dataType;
	int rhs_dataType = rhs->dataType;
	int op_type = op->tokenNo;
	
	if (lhs_dataType == TYPE_INT && rhs_dataType == TYPE_REAL) {
		// LHS is integer, RHS is real.
		// Fix if OP_ASSIGN, else float the integer.
		
		op->dataType = TYPE_REAL;
		
		if (op_type == OP_ASSIGN) {
			cast_tok = makefix(rhs);
			op->firstOperand = lhs;
			lhs->next = cast_tok;
		}
		else {
			cast_tok = makefloat(lhs);
			op->firstOperand = cast_tok;
			cast_tok->next = rhs;
		}
	}
	else if (lhs_dataType == TYPE_REAL && rhs_dataType == TYPE_INT) {
		
		cast_tok = makefloat(rhs);
		
		op->dataType = TYPE_REAL;
		op->firstOperand = lhs;
		lhs->next = cast_tok;
		cast_tok->next = NULL;
		rhs->next = NULL;
	}
	else {
		op->dataType = lhs->dataType;
		op->firstOperand = lhs;     // next firstOperand to operator
		lhs->next = rhs;     // next second operand to first
		rhs->next = NULL;    // terminate operand list
	}
    if(DEBUG){
        printf("end binTypeCoerce\n");
    }		
	return op;
}

TOKEN genTokenBinOperator(TOKEN op, TOKEN left, TOKEN right)
{
    if(DEBUG){
        printf("start genTokenBinOperator\n");
    }	
    if(left->dataType != right->dataType){
        semanticWarning("type coerced");
        op = binTypeCoerce(op,left,right);
    }
    else{
        op->dataType = left->dataType; // the dataType of operator is the dataType of its calculate result
        op->firstOperand = left;
        left->next = right;
        right->next = NULL;
    }
    if(DEBUG){
        printf("end genTokenBinOperator\n");
    }
    return op;
}

TOKEN genTokenUnaryOp(TOKEN op, TOKEN lhs) {
    if(DEBUG){
        printf("start genTokenUnaryOp\n");
    }
    op->firstOperand = lhs;
	lhs->next = NULL;
    if(DEBUG){
        printf("end genTokenUnaryOp\n");
    }   
	return op;
}

TOKEN genTokenFuncall(TOKEN token, TOKEN funToken, TOKEN parasToken)
{
    if(DEBUG){
        printf("start genTokenFuncall\n");
    }
    TOKEN out = genOperatorToken(OP_FUNCALL);
    if(!out){
        printf("Failed to alloc token at genTokenFuncall().\n");
        return NULL;
    }
    SYMBOL funSymbol = searchst(funToken->val.stringVal);
    if(!funSymbol){
        char s[32];
        sprintf(s,"Function \"%s\" is not defined",funToken->val.stringVal);
        semanticError(s);
        return NULL;
    }
    out->dataType = funSymbol->dataType->basicType;

    out->firstOperand = funToken;
    funToken->next = parasToken;
    if(DEBUG){
        printf("end genTokenFuncall\n");
    }
    return out;

}

TOKEN genTokenProgn(TOKEN token, TOKEN stmtToken)
{
    if(DEBUG){
        printf("start genTokenProgn\n");
    }
    token->tokenType = OPERATOR;
    token->tokenNo = OP_PROGN;
    token->firstOperand = stmtToken;
    if(DEBUG){
        printf("end genTokenProgn\n");
    }
    return token;
}

TOKEN genTokenIF(TOKEN token, TOKEN expToken, TOKEN thenToken, TOKEN elseToken)
{
    if(DEBUG){
        printf("start genTokenIF\n");
    }
    token->tokenType = OPERATOR;
    token->tokenNo = OP_IF;
    if(elseToken){
        elseToken->next = NULL;
    }
    token->firstOperand = expToken;
    expToken->next = thenToken;
    thenToken->next =elseToken;
    if(DEBUG){
        printf("end genTokenIF\n");
    }
    return token;   
}

TOKEN goToLastBrother(TOKEN tok) {
    if(DEBUG){
        printf("start goToLastBrother\n");
    }
    if (!tok) {
		return NULL;
	}
	TOKEN current = tok;
	TOKEN nextToken = current->next;
	while (nextToken) {
		current = nextToken;
		nextToken = nextToken->next;
	}
    if(DEBUG){
        printf("end goToLastBrother\n");
    }
	return current;
}
TOKEN goToLastFirstSon(TOKEN tok) {
    if(DEBUG){
        printf("start goToLastFirstSon\n");
    }
    if (!tok) {
		return NULL;
	}
	
	TOKEN current = tok;
	TOKEN Son = current->firstOperand;
	while (Son) {
		current = Son;
		Son = Son->firstOperand;
	}
    if(DEBUG){
        printf("end goToLastFirstSon\n");
    }	
	return current;
}

TOKEN makeLabel() {	
	// DO NOT CALL FOR USER LABELS
	
	TOKEN label_tok = genOperatorToken(OP_LABEL);
	TOKEN label_num_tok = genTokenConstInt(labelCount++);  // increment it after creation
	
	if (!label_tok || !label_num_tok) {
		printf(" Failed to alloc TOKEN(s), makeLabel().\n");
		return NULL;
	}
	label_tok->firstOperand = label_num_tok;   // operand together		
	return label_tok;
}

TOKEN makeGoto(int label) {	
	if (label < 0) {
		printf(" Warning: label number is negative (%d), makeGoto().\n", label);
	}
	
	TOKEN goto_tok = genOperatorToken(OP_GOTO);
	TOKEN goto_num_tok = genTokenConstInt(label);
	if (!goto_tok || !goto_num_tok) {
		printf(" Failed to alloc TOKEN, makeGoto().\n");
		return NULL;
	}
	goto_tok->firstOperand = goto_num_tok;  // operand together	
	return goto_tok;
}


TOKEN genTokenRepeat(TOKEN stmtToken, TOKEN exprToken)
{
    if(DEBUG){
        printf("start genTokenRepeat\n");
    }
    TOKEN labelToken = makeLabel(); //this label shoule be at end of expr
    TOKEN gotoToken = makeGoto(labelToken->firstOperand->val.intVal);
    TOKEN temp = talloc();
    TOKEN notDoToken = genOperatorToken(OP_PROGN);
    TOKEN doToken = genOperatorToken(OP_PROGN);
    TOKEN repeatToken = genTokenProgn(temp,stmtToken);   
    TOKEN ifToken = genOperatorToken(OP_IF);
    ifToken = genTokenIF(ifToken,exprToken,notDoToken,NULL);

    if(!labelToken || !gotoToken||!repeatToken||!doToken||!notDoToken||!ifToken){
        printf(" Failed to alloc TOKEN(s) at makeRepeat().\n");
		return NULL; 
    }
    labelToken->next = stmtToken;;
    notDoToken->next = gotoToken;
    goToLastBrother(stmtToken)->next = ifToken;
    if(DEBUG){
        printf("end genTokenRepeat\n");
    }
    return repeatToken;
}


TOKEN genTokenWhile(TOKEN exprToken, TOKEN stmtToken)
{
    if(DEBUG){
        printf("start genTokenWhile\n");
    }
    TOKEN labelToken = makeLabel(); //this label shoule be at begin of stmt
    TOKEN gotoToken = makeGoto(labelToken->firstOperand->val.intVal);
    TOKEN whileToken = genTokenProgn(talloc(),labelToken);
    TOKEN doToken = genOperatorToken(OP_PROGN);
    TOKEN ifToken = genOperatorToken(OP_IF);
    ifToken = genTokenIF(ifToken,exprToken,doToken,NULL);
    if(!labelToken || !gotoToken||!whileToken||!doToken||!ifToken){
        printf(" Failed to alloc TOKEN(s) at makeRepeat().\n");
		return NULL; 
    }  
    labelToken->next = ifToken;
    doToken->firstOperand = stmtToken;
    goToLastBrother(stmtToken)->next = gotoToken;
    if(DEBUG){
        printf("end genTokenWhile\n");
    }
    return whileToken;

}

TOKEN makeLoopIncr(TOKEN var, int incr_amt) {
    if(DEBUG){
        printf("start makeLoopIncr\n");
    }	
	TOKEN assignop = genOperatorToken(OP_ASSIGN);
	TOKEN var_cpy = TokenCopyConstruct(var);
	TOKEN plusop = makePlus(TokenCopyConstruct(var), genTokenConstInt(incr_amt), NULL);  // OP_PLUS operand "var" next amt
	
	assignop->firstOperand = var_cpy;
	var_cpy->next = plusop;
    if(DEBUG){
        printf("end makeLoopIncr\n");
    }		
	return assignop;
}

TOKEN genTokenFor(TOKEN assignToken, TOKEN dirToken, TOKEN experToken, TOKEN stmtToken)
{
    if(DEBUG){
        printf("start genTokenFor\n");
    }	
	int sign = 1;
	if (strcmp("to", dirToken->val.stringVal) == 0) sign = 1;
	else if (strcmp("downto", dirToken->val.stringVal) == 0) sign = -1;
	
	TOKEN for_asg_progn_tok = genTokenProgn(talloc(), assignToken);
	TOKEN label_tok = makeLabel();
	
	TOKEN stop_op_tok = genOperatorToken(OP_LE);
	TOKEN do_progn_tok = genTokenProgn(talloc(), stmtToken);
	TOKEN ifop_tok = genTokenIF(genOperatorToken(OP_IF), stop_op_tok, do_progn_tok, NULL);
	
	TOKEN loop_stop_tok = TokenCopyConstruct(assignToken->firstOperand); // the counter var, eg "i" in trivb.pas
	TOKEN stmt_incr_tok = makeLoopIncr(assignToken->firstOperand, sign);
	TOKEN goto_tok;
	
	if (!for_asg_progn_tok || !label_tok || !ifop_tok || !stop_op_tok ||
	!do_progn_tok || !loop_stop_tok || !stmt_incr_tok) {
		printf(" Failed to alloc TOKEN(s), makeFor().\n");
		return NULL;
	}
	
	goto_tok = makeGoto(label_tok->firstOperand->val.intVal);  // TODO: not null-checked
	
	if (sign == -1) {
		stop_op_tok->tokenNo = OP_GE;   // "downto"
	}
	
	/* Link all the tokens together. */
	assignToken->next = label_tok;
	label_tok->next = ifop_tok;
	stop_op_tok->firstOperand = loop_stop_tok;
	loop_stop_tok->next = experToken;
	
	/* Handle elimination of nested progns */
	if (do_progn_tok->tokenNo != OP_PROGN) {
		do_progn_tok->firstOperand = stmtToken;
		stmtToken->next = stmt_incr_tok;
	}
	else {   // do_progn_tok == statement
		goToLastBrother(do_progn_tok->firstOperand)->next = stmt_incr_tok;
	}
	stmt_incr_tok->next = goto_tok;
    if(DEBUG){
        printf("end genTokenFor\n");
    }		
	return for_asg_progn_tok;
}

TOKEN findId(TOKEN tok) {
    if(DEBUG){
        printf("start findId\n");
    }		
	SYMBOL sym, typ;
	sym = searchst(tok->val.stringVal);

	if (!sym) {
		char s[32];
		sprintf(s, "var \"%s\" not defined", tok->val.stringVal);
		semanticError(s);
		return NULL;
	}

	if (sym->kind == SYM_FUNCTION) {
		int i;
		for (i = 15; i >= 1; i--) {
			tok->val.stringVal[i] = tok->val.stringVal[i-1];
		}
		tok->val.stringVal[0] = '_';
		sym = searchst(tok->val.stringVal);
	}

	if (sym->kind == SYM_CONST) {
		tok->tokenType = TOKEN_NUM;
		
		if (sym->basicType == 0) {
			tok->dataType = TYPE_INT;
			tok->val.intVal = sym->constval.intNum;
		}
		else if (sym->basicType == 1) {
			tok->dataType = TYPE_FLOAT;
			tok->val.floatVal = sym->constval.realNum;
		}
	}
	else {
		tok->symEntry = sym;
		typ = sym->dataType;
		tok->symType = typ;
		
		if (typ->kind == SYM_BASIC || typ->kind == SYM_POINTER) {
			tok->dataType = typ->basicType;
		}
	}
    if(DEBUG){
        printf("end findId\n");
    }	
	return tok;
}

TOKEN addInt(TOKEN exp, TOKEN off, TOKEN tok) {
	if (!exp || !off) {
		return NULL;
	}
	
	int a = exp->val.intVal;
	int b = off->val.intVal;

	
	if ((b > 0) && (a > INT_MAX - b)) { // if ((INT_MAX / exp->val.intVal) > off->val.intVal)
		printf(" Error: integer overflow detected, addInt()\n");
		printf(" Cannot add %d to %d\n", b, a);
	}
	else {
		exp->val.intVal = a + b;
	}

	
	return exp;
}

TOKEN arrayRef(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
    if(DEBUG){
        printf("start arrayRef\n");
    }	
	TOKEN array_ref = NULL;
	SYMBOL arr_varsym, typesym, temp;
	SYMBOL arrsyms[10];
	
	arr_varsym = searchst(arr->val.stringVal);
	if (!arr_varsym) {
		char s[32];
		sprintf(s, "array \"%s\" not defined", arr->val.stringVal);
		semanticError(s);
		return NULL;
	}
	
	temp = arr_varsym->dataType;
	
	int counter = 0;
	int num_arr_dims = 0;   // not being used for anything
	
	// Store the SYM_ARRAYs into an array
	while (temp && temp->kind != SYM_TYPE) {
		arrsyms[counter] = temp;
		num_arr_dims++;
		counter++;
		temp = temp->dataType;
	}
	if(DEBUG){
        printf("====1\n");
    }	
	// The type of the array
	// arr_varsym->dataType
	
	// only one const integer
	if (subs->next == NULL && subs->tokenType == TOKEN_NUM && subs->dataType == TYPE_INT) {
        if(DEBUG){
            printf("======2\n");
       }
       int tempp = arr_varsym->dataType->dataType->size;
       if(DEBUG){
            printf("size = %d\n",tempp);
       }
        int offset = (subs->val.intVal-arr_varsym->dataType->lowBound) * arr_varsym->dataType->dataType->size;
		array_ref = makeAref(arr, genTokenConstInt(offset), NULL);
		array_ref->dataType = arr_varsym->basicType;
		return array_ref;
	}
	// else if tokenType is IDENTIFIER?
	if(DEBUG){
        printf("====3\n");
    }

	counter = 0;
	TOKEN curr_sub = subs;
	
	while (curr_sub) {
		
		if (counter == 0) {     // first iteration; need to make aref
			SYMBOL curr_sym = arrsyms[counter];
			int curr_size = curr_sym->size / (curr_sym->highBound - curr_sym->lowBound + 1);
			
			// TOKEN mul_op = maketimes(genTokenConstInt(curr_size), curr_sub, NULL);
			
			TOKEN mul_op = genOperatorToken(OP_MUL);
			TOKEN pos_typesym_size = genTokenConstInt(curr_size);
			TOKEN neg_typesym_size = genTokenConstInt(curr_size * -curr_sym->lowBound);
			
			mul_op->firstOperand = pos_typesym_size;
			pos_typesym_size->next = curr_sub;
			
			neg_typesym_size->next = mul_op;
			
			TOKEN plus_op = makePlus(neg_typesym_size, mul_op, NULL);
			
			array_ref = makeAref(arr, plus_op, NULL);
			array_ref->dataType = arr_varsym->basicType;
			
		}
		else {
			
			if (curr_sub->tokenType == TOKEN_NUM) {      // smash constants (optimization)
				TOKEN add_to = array_ref->firstOperand->next->firstOperand;
				add_to = addInt(add_to, genTokenConstInt(curr_sub->tokenNo * typesym->size), NULL);
			}
			else {
				// Smash constants and add to tree
				
				SYMBOL curr_sym = arrsyms[counter];
				int curr_size = curr_sym->size / (curr_sym->highBound - curr_sym->lowBound + 1);
				
				TOKEN mul_op = genOperatorToken(OP_MUL);
				TOKEN pos_typesym_size = genTokenConstInt(curr_size);
				TOKEN neg_typesym_size = genTokenConstInt(curr_size * -1);
				
				mul_op->firstOperand = pos_typesym_size;
				pos_typesym_size->next = curr_sub;
				
				TOKEN added = array_ref->firstOperand->next->firstOperand;
				added = addInt(added, neg_typesym_size, NULL);
				
				TOKEN add_to = array_ref->firstOperand->next->firstOperand->next;
				TOKEN plus_op = makePlus(add_to, mul_op, NULL);
				add_to = plus_op;
				
			}
		}
		
		// Destroy the current next
		TOKEN unlink = curr_sub;
		curr_sub = curr_sub->next;
		unlink->next = NULL;
		counter++;
	}
	
    if(DEBUG){
        printf("end arrayRef\n");
    }		
	return array_ref;
}

TOKEN makePlus(TOKEN lhs, TOKEN rhs, TOKEN tok) {	
	TOKEN out = genOperatorToken(OP_PLUS);
	if (lhs && rhs) {
		out->firstOperand = lhs;
		lhs->next = rhs;
		rhs->next = NULL;
	}
	
	return out;
}

TOKEN makeAref(TOKEN var, TOKEN off, TOKEN tok) {
	if(DEBUG){
        printf("start makeAref\n");
    }
	TOKEN aref = genOperatorToken(OP_AREF);
	aref->firstOperand = var;
	var->next = off;
	if(DEBUG){
        printf("end makeAref\n");
    }	
	return aref;
}

TOKEN get_offset(TOKEN var, TOKEN field) {
	
	TOKEN offset = genTokenConstInt(-1);
	
	TOKEN root_name = goToLastFirstSon(var);
	TOKEN last_offset = goToLastBrother(var->firstOperand);
	
	SYMBOL found = NULL;
	SYMBOL varsym = searchst(root_name->val.stringVal);

	if (!varsym) {
		char s[64];
		sprintf(s, "var \"%s\" not defined", root_name->val.stringVal);
		semanticError(s);
		return NULL;
	}
	
	int var_is_arefop = 0;
	if (var->tokenNo == OP_AREF) {
		var_is_arefop = 1;
	}
	
	SYMBOL temp = varsym;
	while (temp) {
		if (temp->dataType && temp->dataType->kind == SYM_BASIC) {
			break;
		}
		temp = temp->dataType;
	}
	
	if (!temp) {
		char s[64];
		sprintf(s, "symbol table entry \"%s\" is corrupt, pos 1", root_name->val.stringVal);
		semanticError(s);
		return NULL;
	}
	
	while (temp) {
		
		if ((strcmp(temp->nameString, field->val.stringVal) == 0)) {
			found = temp;
			if (var_is_arefop) {
				
				// TOKEN var is an aref TOKEN; ignore 
				if (last_offset->tokenType == OPERATOR) {
					offset->tokenNo = -1;
				}
				else {
					offset->tokenNo = last_offset->tokenNo + found->offset;
				}
				
				// Set offset's next field to a REAL TOKEN_NUM.
				// Is necessary to ensure correct behaviour of
				// binop() during type checking/coercion.
				 
				// The next MUST be nulled out after use, otherwise
				// the console output will be incorrect.
				if (found->dataType->basicType == TYPE_REAL) {
					offset->next = makeRealTok(0);
					offset->next->val.floatVal = -DBL_MAX;
				}
			}
			else {
				
				offset->tokenNo = found->offset;
				if (found->dataType->basicType == TYPE_REAL) {
					offset->next = makeRealTok(0);
					offset->next->val.floatVal = -DBL_MAX;
				}
			}
			
			return offset;
		}
		else if (var_is_arefop && (temp->offset == last_offset->tokenNo)) {
			found = temp;
			break;
		}
		
		temp = temp->link;
	}
	
	/* NOT an error condition if !found here. */
	
	if (!var_is_arefop && found) {
		offset->tokenNo = found->offset;
		if (found->dataType->basicType == TYPE_REAL) {
			offset->next = makeRealTok(0);
			offset->next->val.floatVal = -DBL_MAX;
		}
		return offset;
	}
	else if (var_is_arefop && found) {
		/* TOKEN field represents a record field; search for
		 the record in the symbol table and then search for
		 the field within that record. */
		
		SYMBOL temp1 = searchst(found->dataType->nameString);
		found = NULL;
		if (!temp1) {
			char s[64];
			sprintf(s, "symbol table entry \"%s\" is corrupt, pos 2", root_name->val.stringVal);
			semanticError(s);
			return NULL;
		}
		
		while (temp1) {
			if (temp1->dataType && temp1->dataType->kind == SYM_BASIC) {
				break;
			}
			temp1 = temp1->dataType;
		}
		
		if (!temp1) {
			char s[64];
			sprintf(s, "symbol table entry \"%s\" is corrupt, pos 3", root_name->val.stringVal);
			semanticError(s);
			return NULL;
		}
		
		while (temp1 && !found) {
			if (strcmp(temp1->nameString, field->val.stringVal) == 0) {
				found = temp1;
			}
			else {
				temp1 = temp1->link;
			}
		}
		
		/* NOT an error condition if !found here. */
		if (found) {
			offset->tokenNo = last_offset->tokenNo + found->offset;
			if (found->dataType->basicType == TYPE_REAL) {
				offset->next = makeRealTok(0);
				offset->next->val.floatVal = -DBL_MAX;
			}
			
			return offset;
		}
	}
	
	return offset;
}

TOKEN reduceDot(TOKEN var, TOKEN dot, TOKEN field) {

	TOKEN aref;
	TOKEN offset = get_offset(var, field);
	
	if (var->tokenNo == OP_AREF) {
		// Avoid adding multiple copies to the tree.
		
		if (offset->tokenNo >= 0) {
			var->firstOperand->next = offset;
		}
		aref = var;
	}
	else {
		aref = makeAref(var, offset, NULL);
	}
	
	// Change aref's dataType to REAL to avoid incorrect
	// fixes/floats in binop(). NULL out the dummy next.
	if (offset->next && offset->next->dataType == TYPE_FLOAT &&
	offset->next->val.floatVal == -DBL_MAX) {
		
		aref->dataType = TYPE_FLOAT;
		offset->next = NULL;
	}
	
	return aref;
}

TOKEN makefix(TOKEN tok) {

	
	TOKEN out = genOperatorToken(OP_FIX);   // create OP_FIX TOKEN
	if (!out) {
		printf(" Failed to alloc TOKEN, makefix().\n");
		return NULL;
	}
	
	out->firstOperand = tok;
	out->next = NULL;
	return out;
}
TOKEN makefloat(TOKEN tok) {
	TOKEN out;

	if (tok->tokenType == TOKEN_NUM) {
		// e.g., floating 34 prints "3.400000e+01" to console
		out = tok;
		out->dataType = TYPE_REAL;
		out->val.floatVal = out->val.intVal;
		out->val.intVal = INT_MIN;
	}
	else {
		// e.g., floating 34 prints "(float 34)" to console
		out = genOperatorToken(OP_FLOAT);
		if (!out) {
			printf(" Failed to alloc TOKEN, makefloat().\n");
			return NULL;
		}

		out->firstOperand = tok;
		out->next = NULL;
	}
	return out;
}

TOKEN makeRealTok(float num) {
	TOKEN out = talloc();	
	out->tokenType = TOKEN_NUM;
	out->dataType = TYPE_REAL;
	out->val.floatVal = num;
	
	return out;
}
TOKEN doLabel(TOKEN t1, TOKEN t2, TOKEN t3){}

TOKEN doGoto(TOKEN a1, TOKEN a2){}

TOKEN instFields(TOKEN t1, TOKEN t2){}