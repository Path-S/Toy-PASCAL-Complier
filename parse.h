#ifndef PARSE_H
#define PARSE_H

#define DEBUG 0
#define DB_PRINT_ARGS			1     /* print function arguments */

void semanticError(char* s);
void semanticWarning(char* s);
TOKEN genTokenProgram(TOKEN programHead, TOKEN routine);

TOKEN genOperatorToken(int whichOp);

TOKEN linkBrothers(TOKEN origin, TOKEN newSon);

TOKEN afterDecl(TOKEN decl);

void genSymConst(TOKEN IDtoken, TOKEN constToken);

void genSymType(TOKEN typeName, TOKEN typeToken);

TOKEN genSymEnum(TOKEN IDs);

TOKEN genTokenConstInt(int num);

TOKEN findType(TOKEN tok);

TOKEN genTokenSubrange(TOKEN tok, int low, int high);

TOKEN TokenCopyConstruct(TOKEN origin);

TOKEN genSymDotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok);

TOKEN genSymArray(TOKEN buonds,TOKEN typeToken);

void afterVarDecl();

void genSymVars(TOKEN IDs, TOKEN typeToken);


TOKEN genTokenFuncDecl(TOKEN head, TOKEN body);

TOKEN genSymFunc(TOKEN firstOperand);

TOKEN genTokenBinOperator(TOKEN op, TOKEN left, TOKEN right);

TOKEN genTokenUnaryOp(TOKEN op, TOKEN lhs);

TOKEN genTokenFuncall(TOKEN token, TOKEN funToken, TOKEN parasToken);

TOKEN genTokenProgn(TOKEN token, TOKEN stmtToken);

TOKEN genTokenIF(TOKEN token, TOKEN expToken, TOKEN thenToken, TOKEN elseToken);

TOKEN goToLastBrother(TOKEN tok);

TOKEN goToLastFirstSon(TOKEN tok);

TOKEN makeLabel();

TOKEN makeGoto(int label);


TOKEN genTokenRepeat(TOKEN stmtToken, TOKEN exprToken);

TOKEN genTokenWhile(TOKEN exprToken, TOKEN stmtToken);

TOKEN makeLoopIncr(TOKEN var, int incr_amt);


TOKEN genTokenFor(TOKEN assignToken, TOKEN dirToken, TOKEN experToken, TOKEN stmtToken);

TOKEN findId(TOKEN tok);

TOKEN arrayRef(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb);

TOKEN makePlus(TOKEN lhs, TOKEN rhs, TOKEN tok);

TOKEN makeAref(TOKEN var, TOKEN off, TOKEN tok);

TOKEN reduceDot(TOKEN var, TOKEN dot, TOKEN field);
TOKEN makefix(TOKEN tok);
TOKEN addInt(TOKEN exp, TOKEN off, TOKEN tok);
TOKEN makePlus(TOKEN lhs, TOKEN rhs, TOKEN tok);
TOKEN get_offset(TOKEN var, TOKEN field);
TOKEN makefloat(TOKEN tok);
TOKEN makeRealTok(float num);

#define INT_MAX 2147483647
#define INT_MIN -2147483648

/* Maximum double */
#define DBL_MAX 1.7976931348623157e+308
/* Minimum normalised double */
#define DBL_MIN 2.2250738585072014e-308
/* Maximum float */
#define FLT_MAX 3.40282347e+38F

#endif