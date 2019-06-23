#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "token.h"

TOKENNODE user_labels = NULL;
TOKENNODE curr_label = NULL;


/* BASEOFFSET is the offset for the first variable */
#define BASEOFFSET 0

extern int lastblock;
extern int    blocknumber;       	/* Number of current block being compiled */
extern int    contblock[MAXBLOCKS];  /* Containing block for each block (the outer block of this block)        */
int    blockoffs[MAXBLOCKS] = {0};  		/* Storage offsets for each block         */
SYMBOL symtab[MAXBLOCKS][HASH_SIZE];     /* Symbol chain for each block            */

/* Sizes of basic types  INTEGER  REAL  	CHAR  	BOOL 	 STRING   */
int basicsizes[5] =      { 4,       8,       1,         4,        16 };

char* symprint[10]  = {"ARGM", "BASIC", "CONST", "VAR", "SYM_SUBRANGE",
                       "FUNCTION", "ARRAY", "RECORD", "TYPE", "ARGLIST"};
int symsize[10] = { 1, 5, 5, 3, 8, 8, 5, 6, 4, 7 };

/* allocate a new symbol record */
SYMBOL symalloc() { 
	return((SYMBOL) calloc(1,sizeof(SYMBOLREC)));
}

/* Make a symbol table entry with the given name */
SYMBOL makesym(char name[]) {
	SYMBOL sym; int i;
    sym = symalloc();
    for ( i = 0; i < 16; i++) sym->nameString[i] = name[i];
    sym->link = NULL;
    return sym;
}

/* Insert a name in the symbol table at current value of blocknumber */
/* Returns pointer to the new symbol table entry, which is empty     */
/* except for the name.                                              */
SYMBOL insertsym(char name[]) {
	return insertsymat(name, blocknumber);
}
SYMBOL insertsymat(char name[], int level) {
	SYMBOL sym;
	sym = makesym(name);
	int pos = hashfun(name);
	while (symtab[level][pos] != NULL) {
		pos = (pos + 1) % HASH_SIZE;
		if (pos == hashfun(name)) {
			printf("Error: symbol table overflow.\n");
			exit(-1);
		}
	}
	symtab[level][pos] = sym;
	sym->blockLevel = level;

	if (sym->kind == SYM_VAR) {
		sym->offset = blockoffs[level];
		blockoffs[level] += basicsizes[sym->basicType];
	} 

	if (DEBUG_SYMTAB) printf("insertsym %8s %ld at level %d, pos %d\n",
		name, (long) sym, level, pos);
	return sym;
}

int hashfun(char name[]) {
	if (name[0] == '_') return 26;
	return tolower(name[0])-'a';
}


/* Search one level of the symbol table for the given name.         */
/* Result is a pointer to the symbol table entry or NULL            */
SYMBOL searchlev(char name[], int level){
	int pos = hashfun(name);
	SYMBOL sym; 

	while ((sym = symtab[level][pos]) != NULL) {
		if (strcmp(name, sym->nameString) == 0) return sym;
		pos = (pos + 1) % HASH_SIZE;
		if (pos == hashfun(name)) return NULL;
	}
	return NULL;
}

/* Search all levels of the symbol table for the given name.        */
/* Result is a pointer to the symbol table entry or NULL            */
SYMBOL searchst(char name[]){
	SYMBOL sym = NULL;
	int level = blocknumber;
	while ( sym == NULL && level >= 0 ) {
		sym = searchlev(name, level);
		if (level > 0) level = contblock[level]; /* try containing block */
		else level = -1;                      /* until all are tried  */
	}
	if (DEBUG_SYMTAB) printf("searchst %8s %ld at level %d\n",
		name, (long) sym, level);
	return sym;
}

/* Search for symbol, insert if not there. */
SYMBOL searchins(char name[]) {
	SYMBOL res;
	res = searchst(name);
	if ( res != NULL ) return(res);
	res = insertsym(name);
	return(res);
}

/* Get the alignment boundary for a type  */
int alignsize(SYMBOL sym) {
	switch (sym->kind) {
		case SYM_BASIC:
		case SYM_SUBRANGE:
			return sym->size;
			break;
		case SYM_ARRAY:
		case SYM_RECORD:
			return 16;
			break;
		default:
			return 8;
			break;
	}
}


/* Insert a basic type into the symbol table */
SYMBOL insertbt(char name[], int basictp, int siz) {
	SYMBOL sym = insertsym(name);
	sym->kind = SYM_BASIC;
	sym->basicType = basictp;
	sym->size = siz;
	return sym;
}

/* Insert a one-argument function in the symbol table. */
/* Linked to the function symbol are result type followed by arg types.  */
SYMBOL insertfn(char name[], SYMBOL resulttp, SYMBOL argtp) {
	SYMBOL sym, res, arg;
	sym = insertsym(name);
	sym->kind = SYM_FUNCTION;
	res = symalloc();
	res->kind = SYM_ARGM;
	res->dataType = resulttp;
	if (resulttp != NULL) res->basicType = resulttp->basicType;
	arg = symalloc();
	arg->kind = SYM_ARGM;
	arg->dataType = argtp;
	if (argtp != NULL) arg->basicType = argtp->basicType;
	arg->link = NULL;
	res->link = arg;
	sym->dataType = res;
	return sym;
}

// insert function with argument list
SYMBOL insertfnx(char name[], SYMBOL resulttp, SYMBOL arglist) {
	SYMBOL sym, res, arg;
	sym = insertsymat(name, contblock[blocknumber]);
	sym->kind = SYM_FUNCTION;
	res = symalloc();
	res->kind = SYM_ARGM;
	res->dataType = resulttp;
	if (resulttp != NULL) res->basicType = resulttp->basicType;

	res->link = arglist;
	sym->dataType = res;
	return sym;
}

/* Call this to initialize symbols provided by the compiler */
void initsyms() {
	SYMBOL sym, realsym, intsym, charsym, boolsym;
	blocknumber = 0;               /* Put compiler symbols in block 0 */
	blockoffs[1] = BASEOFFSET;     /* offset of first variable */
	realsym = insertbt("real", TYPE_FLOAT, 8);
	intsym  = insertbt("integer", TYPE_INT, 4);
	charsym = insertbt("char", TYPE_CHAR, 1);
	boolsym = insertbt("boolean", TYPE_BOOL, 4);

	sym = insertfn("abs", realsym, realsym);
	sym = insertfn("sqr", realsym, realsym);
	sym = insertfn("sqrt", realsym, realsym);
	sym = insertfn("ord", intsym, intsym);
	sym = insertfn("chr", charsym, intsym);
	sym = insertfn("pred", charsym, charsym);
	sym = insertfn("succ", charsym, charsym);
	sym = insertfn("odd", boolsym, intsym);

	sym = insertfn("write", NULL, charsym);
	sym = insertfn("writeln", NULL, charsym);
	sym = insertfn("read", NULL, NULL);
	sym = insertfn("readln", NULL, NULL);

	blocknumber = 1;             /* Start the user program in block 1 */
	lastblock = 1;
	contblock[1] = 0;
}


