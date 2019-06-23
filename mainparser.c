#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexcial.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"
#include "geninter.h"

extern TOKEN parseresult;


int main() {

	int res;
	initsyms();
	res = yyparse();
	Ppexpr(parseresult);           /* Pretty-print the result tree */
	codegenerator(parseresult);
	printf("---------done---------\n");
	return 0;
}
