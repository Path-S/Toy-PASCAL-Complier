/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "parse.y" /* yacc.c:339  */

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



#line 83 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    CONST_STR = 259,
    CONST_INT = 260,
    CONST_REAL = 261,
    CONST_CHAR = 262,
    LP = 263,
    RP = 264,
    LB = 265,
    RB = 266,
    DOTDOT = 267,
    COMMA = 268,
    COLON = 269,
    SEMI = 270,
    DOT = 271,
    PLUS = 272,
    MINUS = 273,
    MUL = 274,
    DIV_R = 275,
    LT = 276,
    LE = 277,
    EQ = 278,
    NE = 279,
    GT = 280,
    GE = 281,
    ASSIGN = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    DIV = 286,
    MOD = 287,
    ARRAY = 288,
    BEGIN_T = 289,
    CASE = 290,
    CONST = 291,
    DO = 292,
    DOWNTO = 293,
    ELSE = 294,
    END = 295,
    FOR = 296,
    FUNCTION = 297,
    GOTO = 298,
    IF = 299,
    IN = 300,
    OF = 301,
    PACKED = 302,
    PROCEDURE = 303,
    PROGRAM = 304,
    READ = 305,
    RECORD = 306,
    REPEAT = 307,
    SET = 308,
    THEN = 309,
    TO = 310,
    TYPE = 311,
    UNTIL = 312,
    VAR = 313,
    WHILE = 314,
    WITH = 315,
    SYS_CON = 316,
    SYS_FUNCT = 317,
    SYS_PROC = 318,
    SYS_TYPE = 319
  };
#endif
/* Tokens.  */
#define ID 258
#define CONST_STR 259
#define CONST_INT 260
#define CONST_REAL 261
#define CONST_CHAR 262
#define LP 263
#define RP 264
#define LB 265
#define RB 266
#define DOTDOT 267
#define COMMA 268
#define COLON 269
#define SEMI 270
#define DOT 271
#define PLUS 272
#define MINUS 273
#define MUL 274
#define DIV_R 275
#define LT 276
#define LE 277
#define EQ 278
#define NE 279
#define GT 280
#define GE 281
#define ASSIGN 282
#define AND 283
#define OR 284
#define NOT 285
#define DIV 286
#define MOD 287
#define ARRAY 288
#define BEGIN_T 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FOR 296
#define FUNCTION 297
#define GOTO 298
#define IF 299
#define IN 300
#define OF 301
#define PACKED 302
#define PROCEDURE 303
#define PROGRAM 304
#define READ 305
#define RECORD 306
#define REPEAT 307
#define SET 308
#define THEN 309
#define TO 310
#define TYPE 311
#define UNTIL 312
#define VAR 313
#define WHILE 314
#define WITH 315
#define SYS_CON 316
#define SYS_FUNCT 317
#define SYS_PROC 318
#define SYS_TYPE 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 259 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    35,    35,    37,    39,    41,    44,    47,    50,    51,
      53,    55,    57,    58,    59,    60,    61,    64,    65,    67,
      68,    70,    72,    73,    74,    76,    77,    78,    79,    80,
      82,    85,    87,    88,    90,    92,    93,    96,    97,    99,
     100,   102,   105,   106,   107,   108,   109,   111,   114,   117,
     120,   122,   123,   125,   127,   129,   131,   134,   136,   140,
     142,   144,   145,   147,   148,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   160,   161,   163,   165,   166,   168,
     169,   171,   174,   175,   177,   179,   181,   184,   185,   187,
     190,   191,   193,   194,   196,   198,   199,   201,   202,   203,
     204,   205,   206,   207,   209,   210,   211,   212,   214,   215,
     216,   217,   218,   220,   221,   223,   224,   225,   226,   227,
     228,   229,   231,   232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST_STR", "CONST_INT",
  "CONST_REAL", "CONST_CHAR", "LP", "RP", "LB", "RB", "DOTDOT", "COMMA",
  "COLON", "SEMI", "DOT", "PLUS", "MINUS", "MUL", "DIV_R", "LT", "LE",
  "EQ", "NE", "GT", "GE", "ASSIGN", "AND", "OR", "NOT", "DIV", "MOD",
  "ARRAY", "BEGIN_T", "CASE", "CONST", "DO", "DOWNTO", "ELSE", "END",
  "FOR", "FUNCTION", "GOTO", "IF", "IN", "OF", "PACKED", "PROCEDURE",
  "PROGRAM", "READ", "RECORD", "REPEAT", "SET", "THEN", "TO", "TYPE",
  "UNTIL", "VAR", "WHILE", "WITH", "SYS_CON", "SYS_FUNCT", "SYS_PROC",
  "SYS_TYPE", "$accept", "program", "program_head", "routine",
  "sub_routine", "routine_head", "label_part", "const_part",
  "const_expr_list", "const_value", "type_part", "type_decl_list",
  "type_definition", "type_decl", "simple_type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "id_list",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression_list", "expression", "expr",
  "term", "factor", "args_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

#define YYPACT_NINF -157

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-157)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -45,     8,    21,  -157,    16,  -157,    17,     6,     2,  -157,
    -157,  -157,  -157,  -157,    46,    -4,   103,    38,    75,    93,
      45,    48,   110,   190,  -157,   136,   135,   190,   134,  -157,
     190,   144,  -157,   139,  -157,  -157,  -157,  -157,  -157,  -157,
    -157,  -157,  -157,   197,   137,   138,    93,  -157,   162,   -13,
     190,   190,   164,   190,     7,   102,  -157,  -157,  -157,  -157,
     190,   190,   190,  -157,   160,  -157,   218,    36,    15,  -157,
     142,  -157,   207,   190,    57,   259,   190,  -157,   156,   197,
      12,  -157,  -157,   113,   162,  -157,   171,   172,   -13,  -157,
     165,  -157,   167,   294,    72,   282,   150,   294,  -157,   190,
     190,   180,   253,  -157,  -157,   190,   190,   190,   190,   190,
     190,   190,   211,   190,   190,   190,   190,   190,   190,   190,
     190,   129,   175,   190,   129,   104,   294,  -157,   176,   174,
     162,   177,   162,  -157,   194,   192,  -157,  -157,  -157,   216,
      12,  -157,   219,   219,  -157,  -157,  -157,  -157,  -157,   190,
     208,   190,   106,   288,  -157,  -157,   112,    36,    36,    36,
      36,    36,    36,   220,   222,   206,  -157,    15,    15,    15,
    -157,  -157,  -157,  -157,   200,   198,  -157,   294,  -157,  -157,
     190,  -157,   242,   120,    19,     4,  -157,   122,   197,  -157,
    -157,   232,    10,   234,  -157,   235,     6,   238,   294,   190,
     294,  -157,  -157,  -157,   129,   129,  -157,  -157,  -157,  -157,
     190,   129,  -157,   294,  -157,  -157,   243,  -157,  -157,    12,
    -157,  -157,   162,   236,    62,  -157,   245,   246,    19,  -157,
    -157,  -157,   294,   241,   248,   265,  -157,   223,   250,   236,
    -157,    10,    19,    19,  -157,  -157,  -157,   129,    12,  -157,
    -157,  -157,  -157,  -157,  -157
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    62,     4,    59,     0,    18,     0,     0,     8,     0,
      38,    77,     0,     0,    60,     0,     0,     0,     0,    62,
       0,     0,    67,     0,    64,    65,    66,    68,    69,    70,
      71,    72,    73,     0,     0,     0,    17,    20,     0,    46,
       0,     0,     0,     0,     0,   113,    15,    12,    13,    14,
       0,     0,     0,    16,     0,   116,     0,   103,   107,   112,
       0,    94,     0,     0,     0,     0,     0,    61,     0,     0,
       0,    19,    36,     0,    37,    40,     0,     0,     6,    44,
       0,    45,     0,   123,     0,     0,     0,    74,    63,     0,
       0,     0,     0,   119,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,    11,     0,    26,
       0,     0,     0,    25,     0,     0,    22,    23,    24,     0,
       0,    39,    52,    52,    42,    43,     7,     7,    78,     0,
       0,     0,     0,     0,   121,   117,     0,   100,    99,   101,
     102,    98,    97,     0,     0,     0,    91,   104,   105,   106,
     108,   111,   109,   110,     0,    83,    80,    84,    85,    79,
       0,    10,     0,     0,     0,     0,    33,     0,     0,    21,
      35,     0,     0,     0,    50,     0,     0,     0,   122,     0,
      76,   114,   120,   115,     0,     0,    89,    90,    88,    87,
       0,     0,    81,    95,    29,    27,     0,    31,    32,     0,
      28,    41,     0,    58,     0,    54,     0,     0,     0,    47,
       5,    49,    75,     0,     0,     0,    82,     0,     0,    57,
      51,     0,     0,     0,    48,    93,    92,     0,     0,    34,
      53,    55,    56,    86,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -157,  -157,  -157,  -157,   119,   254,  -157,  -157,  -157,   -43,
    -157,  -157,   224,  -137,  -156,  -157,  -157,  -157,    83,  -118,
    -157,  -157,   187,  -157,   185,  -157,   204,  -157,   151,  -157,
      54,  -157,  -157,   101,    -6,   269,  -116,   247,  -157,  -157,
    -157,  -157,  -157,  -157,  -157,  -157,  -157,  -157,   163,  -157,
    -157,   -21,   215,    43,    32,   -15
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   195,   196,     8,    15,    18,    65,
      20,    46,    47,   135,   136,   137,   138,   185,   186,    83,
      49,    84,    85,    88,    89,    90,    91,    92,   193,   224,
     225,   226,   227,    12,    32,    16,    33,    34,    35,    36,
      37,   212,    38,    39,    40,   210,    41,   165,   166,    42,
     125,    93,    67,    68,    69,    94
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      78,    13,    66,   191,     1,   175,    72,    82,   178,    75,
      21,     4,   183,    82,   187,   129,    56,    57,    58,    59,
     130,     5,   129,    56,    57,    58,    59,   130,   216,    86,
      95,     9,    97,    10,   116,    87,   128,   134,    14,   102,
      11,    11,    23,   117,   217,   131,   118,   119,    25,    17,
      26,    27,    19,   113,   114,   126,    50,    28,    51,    29,
      21,    43,    22,   132,    52,   115,    30,   187,   222,   164,
      31,   240,   244,    63,   223,    53,   133,   241,    44,   153,
      63,   148,   238,   133,   152,   149,   251,   252,   233,   234,
     156,    11,    23,   103,   104,   236,    45,   134,    25,   174,
      26,    27,   177,    48,   239,   122,    21,    28,    22,    29,
      99,   254,   100,   179,   123,   201,    30,   180,   101,   149,
      31,   203,   164,   223,    54,   149,   139,   140,   198,   215,
     200,   253,    21,   139,    22,   139,   219,    11,    23,    70,
      71,   134,    73,    24,    25,   220,    26,    27,   170,   171,
     172,   173,    76,    28,    77,    29,   167,   168,   169,   213,
      79,    80,    30,    11,    23,    82,    31,    96,   105,   120,
      25,   127,    26,    27,   142,   143,   134,   151,   232,    28,
     146,    29,   147,   154,   176,   134,   182,   184,    30,   235,
      13,   181,    31,    55,    56,    57,    58,    59,    60,   134,
     134,    56,    57,    58,    59,   134,   188,   189,    61,   163,
      56,    57,    58,    59,   163,    56,    57,    58,    59,   190,
      62,   106,   107,   108,   109,   110,   111,   192,   106,   107,
     108,   109,   110,   111,   204,   199,   205,   211,   208,   106,
     107,   108,   109,   110,   111,   214,   206,   221,   228,   139,
     229,    63,    64,   231,   237,   209,   245,     7,    63,   242,
     243,   121,   155,   246,   112,   249,   197,    63,   218,   248,
      81,   141,    63,   144,   106,   107,   108,   109,   110,   111,
     106,   107,   108,   109,   110,   111,   106,   107,   108,   109,
     110,   111,   145,   150,   194,   250,   124,   230,    74,   202,
       0,    98,   247,   106,   107,   108,   109,   110,   111,   106,
     107,   108,   109,   110,   111,   106,   107,   108,   109,   110,
     111,   157,   158,   159,   160,   161,   162,     0,   207
};

static const yytype_int16 yycheck[] =
{
      43,     7,    23,   140,    49,   121,    27,     3,   124,    30,
       3,     3,   130,     3,   132,     3,     4,     5,     6,     7,
       8,     0,     3,     4,     5,     6,     7,     8,   184,    42,
      51,    15,    53,    16,    19,    48,    79,    80,    36,    60,
      34,    34,    35,    28,    40,    33,    31,    32,    41,     3,
      43,    44,    56,    17,    18,    76,     8,    50,    10,    52,
       3,    23,     5,    51,    16,    29,    59,   185,    58,   112,
      63,     9,   228,    61,   192,    27,    64,    15,     3,   100,
      61,     9,   219,    64,    99,    13,   242,   243,   204,   205,
     105,    34,    35,    61,    62,   211,     3,   140,    41,   120,
      43,    44,   123,    58,   222,    73,     3,    50,     5,    52,
       8,   248,    10,     9,    57,     9,    59,    13,    16,    13,
      63,     9,   165,   241,    14,    13,    13,    14,   149,     9,
     151,   247,     3,    13,     5,    13,    14,    34,    35,     3,
       5,   184,     8,    40,    41,   188,    43,    44,   116,   117,
     118,   119,     8,    50,    15,    52,   113,   114,   115,   180,
      23,    23,    59,    34,    35,     3,    63,     3,     8,    27,
      41,    15,    43,    44,     3,     3,   219,    27,   199,    50,
      15,    52,    15,     3,     9,   228,    12,    10,    59,   210,
     196,    15,    63,     3,     4,     5,     6,     7,     8,   242,
     243,     4,     5,     6,     7,   248,    12,    15,    18,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
      30,    21,    22,    23,    24,    25,    26,     8,    21,    22,
      23,    24,    25,    26,    14,    27,    14,    39,    38,    21,
      22,    23,    24,    25,    26,     3,    40,    15,    14,    13,
      15,    61,    62,    15,    11,    55,    15,     3,    61,    14,
      14,    54,     9,    15,    46,    15,   147,    61,   185,    46,
      46,    84,    61,    88,    21,    22,    23,    24,    25,    26,
      21,    22,    23,    24,    25,    26,    21,    22,    23,    24,
      25,    26,    88,    11,   143,   241,    37,   196,    29,    11,
      -1,    54,    37,    21,    22,    23,    24,    25,    26,    21,
      22,    23,    24,    25,    26,    21,    22,    23,    24,    25,
      26,   106,   107,   108,   109,   110,   111,    -1,   165
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    66,    67,     3,     0,    68,    70,    71,    15,
      16,    34,    98,    99,    36,    72,   100,     3,    73,    56,
      75,     3,     5,    35,    40,    41,    43,    44,    50,    52,
      59,    63,    99,   101,   102,   103,   104,   105,   107,   108,
     109,   111,   114,    23,     3,     3,    76,    77,    58,    85,
       8,    10,    16,    27,    14,     3,     4,     5,     6,     7,
       8,    18,    30,    61,    62,    74,   116,   117,   118,   119,
       3,     5,   116,     8,   100,   116,     8,    15,    74,    23,
      23,    77,     3,    84,    86,    87,    42,    48,    88,    89,
      90,    91,    92,   116,   120,   116,     3,   116,   102,     8,
      10,    16,   116,   119,   119,     8,    21,    22,    23,    24,
      25,    26,    46,    17,    18,    29,    19,    28,    31,    32,
      27,    54,   119,    57,    37,   115,   116,    15,    74,     3,
       8,    33,    51,    64,    74,    78,    79,    80,    81,    13,
      14,    87,     3,     3,    89,    91,    15,    15,     9,    13,
      11,    27,   120,   116,     3,     9,   120,   117,   117,   117,
     117,   117,   117,     3,    74,   112,   113,   118,   118,   118,
     119,   119,   119,   119,   116,   101,     9,   116,   101,     9,
      13,    15,    12,    84,    10,    82,    83,    84,    12,    15,
       3,    78,     8,    93,    93,    69,    70,    69,   116,    27,
     116,     9,    11,     9,    14,    14,    40,   113,    38,    55,
     110,    39,   106,   116,     3,     9,    79,    40,    83,    14,
      74,    15,    58,    84,    94,    95,    96,    97,    14,    15,
      98,    15,   116,   101,   101,   116,   101,    11,    78,    84,
       9,    15,    14,    14,    79,    15,    15,    37,    46,    15,
      95,    79,    79,   101,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    68,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    74,    74,    74,    75,    75,    76,
      76,    77,    78,    78,    78,    79,    79,    79,    79,    79,
      80,    81,    82,    82,    83,    84,    84,    85,    85,    86,
      86,    87,    88,    88,    88,    88,    88,    89,    90,    91,
      92,    93,    93,    94,    94,    95,    95,    96,    97,    98,
      99,   100,   100,   101,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   103,   104,   104,   104,
     104,   105,   106,   106,   107,   108,   109,   110,   110,   111,
     112,   112,   113,   113,   114,   115,   115,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     3,
       6,     3,     2,     1,     4,     3,     1,     2,     0,     2,
       1,     4,     2,     2,     1,     1,     0,     4,     5,     4,
       3,     3,     0,     3,     1,     3,     3,     2,     1,     1,
       3,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     6,     5,     1,     4,     4,
       4,     5,     2,     0,     4,     4,     8,     1,     1,     5,
       2,     1,     4,     4,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     4,     4,     1,     3,     2,     2,
       4,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 35 "parse.y" /* yacc.c:1646  */
    { parseresult = genTokenProgram((yyvsp[-2]), (yyvsp[-1])); }
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 37 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 39 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-1]), (yyvsp[0])); }
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 41 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-1]), (yyvsp[0])); }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 45 "parse.y" /* yacc.c:1646  */
    { (yyval) = afterDecl((yyvsp[0])); }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 50 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 54 "parse.y" /* yacc.c:1646  */
    { genSymConst((yyvsp[-3]), (yyvsp[-1])); }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 55 "parse.y" /* yacc.c:1646  */
    { genSymConst((yyvsp[-3]), (yyvsp[-1])); }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 57 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 58 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 59 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 60 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 61 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 64 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 67 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 68 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 70 "parse.y" /* yacc.c:1646  */
    { genSymType((yyvsp[-3]), (yyvsp[-1])); }
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 72 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 73 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 74 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 76 "parse.y" /* yacc.c:1646  */
    { (yyval) = findType((yyvsp[0])); }
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 77 "parse.y" /* yacc.c:1646  */
    { (yyval) = findType((yyvsp[0])); }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 78 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymEnum((yyvsp[-1])); }
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 79 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymDotdot((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 80 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymDotdot((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 83 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymArray((yyvsp[-3]), (yyvsp[0])); }
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 85 "parse.y" /* yacc.c:1646  */
    { (yyval) = instRec((yyvsp[-2]), (yyvsp[-1])); }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 87 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-1]), (yyvsp[0])); }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 88 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 90 "parse.y" /* yacc.c:1646  */
    { (yyval) = instFields((yyvsp[-3]), (yyvsp[-1]));; }
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 92 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-2]), (yyvsp[0])); }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 93 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 96 "parse.y" /* yacc.c:1646  */
    { afterVarDecl(); }
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 97 "parse.y" /* yacc.c:1646  */
    { afterVarDecl(); }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 99 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 100 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 102 "parse.y" /* yacc.c:1646  */
    { genSymVars((yyvsp[-3]), (yyvsp[-1])); }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 105 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-1]), (yyvsp[0])); }
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 106 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-1]), (yyvsp[0])); }
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 107 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 108 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 109 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 112 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncDecl((yyvsp[-3]), (yyvsp[-1])); }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 115 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymFunc(linkBrothers((yyvsp[-4]), linkBrothers((yyvsp[-3]), linkBrothers((yyvsp[0]), (yyvsp[-2]))))); }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 118 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncDecl((yyvsp[-3]), (yyvsp[-1])); }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 120 "parse.y" /* yacc.c:1646  */
    { (yyval) = genSymFunc(linkBrothers((yyvsp[-2]), linkBrothers((yyvsp[-1]), (yyvsp[0])))); }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 122 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 123 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 126 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-2]), (yyvsp[0])); }
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 127 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 130 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]), genSymVars((yyvsp[-2]), (yyvsp[0])); }
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 132 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]), genSymVars((yyvsp[-2]), (yyvsp[0])); }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 134 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 136 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 140 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 142 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenProgn((yyvsp[-2]), (yyvsp[-1])); }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 144 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-2]), (yyvsp[-1])); }
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 145 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 147 "parse.y" /* yacc.c:1646  */
    { (yyval) = doLabel((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 148 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 150 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 151 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 152 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 153 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 154 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 155 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 156 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 157 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 158 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 160 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), findId((yyvsp[-2])), (yyvsp[0])); }
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 162 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), arrayRef((yyvsp[-5]), NULL, (yyvsp[-3]), NULL), (yyvsp[0])); }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 163 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), reduceDot((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2])), (yyvsp[0])); }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 165 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[0]), NULL, NULL); }
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 166 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 168 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 169 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 172 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenIF((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-1]), (yyvsp[0])); }
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 174 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 177 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenRepeat((yyvsp[-2]), (yyvsp[0])); }
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 179 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenWhile((yyvsp[-2]), (yyvsp[0])); }
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 182 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFor(genTokenBinOperator((yyvsp[-5]), (yyvsp[-6]), (yyvsp[-4])), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0])); }
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 184 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 185 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 188 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 190 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 191 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 193 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 194 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 196 "parse.y" /* yacc.c:1646  */
    { (yyval) = doGoto((yyvsp[-1]), (yyvsp[0])); }
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 198 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-2]), (yyvsp[-1])); }
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 199 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 201 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 202 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 203 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 204 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 205 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 206 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 207 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 209 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 210 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 211 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 212 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 214 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 215 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 216 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 217 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenBinOperator((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 218 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 220 "parse.y" /* yacc.c:1646  */
    { (yyval) = findId((yyvsp[0])); }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 221 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 223 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenFuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 224 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 225 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 226 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenUnaryOp((yyvsp[-1]), (yyvsp[0])); }
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 227 "parse.y" /* yacc.c:1646  */
    { (yyval) = genTokenUnaryOp((yyvsp[-1]), (yyvsp[0])); }
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 228 "parse.y" /* yacc.c:1646  */
    { (yyval) = arrayRef((yyvsp[-3]), NULL, (yyvsp[-1]), NULL); }
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 229 "parse.y" /* yacc.c:1646  */
    { (yyval) = reduceDot((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 231 "parse.y" /* yacc.c:1646  */
    { (yyval) = linkBrothers((yyvsp[-2]), (yyvsp[0])); }
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 232 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2246 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 234 "parse.y" /* yacc.c:1906  */

int yyerror(s) char *s; {
	fprintf(stderr, "Parser Error at line %d: %s\n", lineCount, s);
	return 0;
}

