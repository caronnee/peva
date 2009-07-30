/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_MAIN = 258,
     TOKEN_LOCATION = 259,
     TOKEN_OBJECT = 260,
     TOKEN_VAR_REAL = 261,
     TOKEN_VAR_INT = 262,
     TOKEN_VOID = 263,
     TOKEN_FUNCTION = 264,
     TOKEN_IF = 265,
     TOKEN_ELSE = 266,
     TOKEN_WHILE = 267,
     TOKEN_DO = 268,
     TOKEN_FOR = 269,
     TOKEN_RETURN = 270,
     TOKEN_BREAK = 271,
     TOKEN_SEMICOLON = 272,
     TOKEN_DOT = 273,
     TOKEN_COMMA = 274,
     TOKEN_LPAR = 275,
     TOKEN_RPAR = 276,
     TOKEN_LSBRA = 277,
     TOKEN_RSBRA = 278,
     TOKEN_ASSIGN = 279,
     TOKEN_BEGIN = 280,
     TOKEN_END = 281,
     TOKEN_OBJECT_FEATURE = 282,
     TOKEN_IDENTIFIER = 283,
     TOKEN_UINT = 284,
     TOKEN_REAL = 285,
     TOKEN_OPER_REL = 286,
     TOKEN_OPER_SIGNADD = 287,
     TOKEN_OPER_MUL = 288,
     TOKEN_PLUSPLUS = 289,
     TOKEN_MINUSMINUS = 290,
     TOKEN_BOOL_AND = 291,
     TOKEN_BOOL_OR = 292
   };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_LOCATION 259
#define TOKEN_OBJECT 260
#define TOKEN_VAR_REAL 261
#define TOKEN_VAR_INT 262
#define TOKEN_VOID 263
#define TOKEN_FUNCTION 264
#define TOKEN_IF 265
#define TOKEN_ELSE 266
#define TOKEN_WHILE 267
#define TOKEN_DO 268
#define TOKEN_FOR 269
#define TOKEN_RETURN 270
#define TOKEN_BREAK 271
#define TOKEN_SEMICOLON 272
#define TOKEN_DOT 273
#define TOKEN_COMMA 274
#define TOKEN_LPAR 275
#define TOKEN_RPAR 276
#define TOKEN_LSBRA 277
#define TOKEN_RSBRA 278
#define TOKEN_ASSIGN 279
#define TOKEN_BEGIN 280
#define TOKEN_END 281
#define TOKEN_OBJECT_FEATURE 282
#define TOKEN_IDENTIFIER 283
#define TOKEN_UINT 284
#define TOKEN_REAL 285
#define TOKEN_OPER_REL 286
#define TOKEN_OPER_SIGNADD 287
#define TOKEN_OPER_MUL 288
#define TOKEN_PLUSPLUS 289
#define TOKEN_MINUSMINUS 290
#define TOKEN_BOOL_AND 291
#define TOKEN_BOOL_OR 292




/* Copy the first part of user declarations.  */
#line 1 "bison.y"

	#include <iostream>
	#include "header1.h"
	#include "program.h"
	#include "parser_functions.h"

	#define YYSTYPE Lval 
	#define YYLTYPE unsigned
	#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)

	#define YYERROR_VERBOSE 1		
	static void yyerror(YYLTYPE *line, Program* ctx, const char *m);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 207 "bison.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNRULES -- Number of states.  */
#define YYNSTATES  197

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    10,    11,    14,    16,    18,    22,    24,
      26,    28,    30,    33,    37,    42,    44,    48,    52,    58,
      66,    68,    70,    74,    78,    79,    81,    84,    86,    88,
      91,    96,   103,   111,   117,   124,   127,   130,   132,   134,
     137,   141,   145,   147,   150,   152,   155,   157,   159,   161,
     171,   179,   185,   189,   192,   195,   197,   200,   202,   205,
     208,   210,   214,   216,   219,   224,   229,   231,   232,   236,
     244,   246,   248,   254,   260,   268,   270,   272,   274,   277,
     279,   283,   287,   291,   296,   298,   302,   304,   306,   309,
     312,   316,   318,   322,   324,   328,   330,   332,   336,   338,
     344,   346
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    48,     3,    20,    21,    54,    -1,
      -1,    40,    42,    -1,    43,    -1,    44,    -1,    41,    46,
      17,    -1,     6,    -1,     7,    -1,     4,    -1,     5,    -1,
      43,    45,    -1,    22,    29,    23,    -1,    45,    22,    29,
      23,    -1,    28,    -1,    28,    24,    74,    -1,    46,    19,
      28,    -1,    46,    19,    28,    24,    74,    -1,    46,    19,
      28,    24,    25,    47,    26,    -1,    53,    -1,    28,    -1,
      47,    19,    28,    -1,    47,    19,    53,    -1,    -1,    52,
      -1,     9,    28,    -1,    41,    -1,     8,    -1,    41,    28,
      -1,    51,    19,    41,    28,    -1,    50,    49,    20,    51,
      21,    54,    -1,    52,    50,    49,    20,    51,    21,    54,
      -1,    50,    49,    20,    21,    54,    -1,    52,    50,    49,
      20,    21,    54,    -1,    32,    30,    -1,    32,    29,    -1,
      30,    -1,    29,    -1,    25,    26,    -1,    25,    17,    26,
      -1,    25,    55,    26,    -1,    65,    -1,    55,    65,    -1,
      66,    -1,    55,    66,    -1,    14,    -1,    13,    -1,    12,
      -1,    56,    20,    67,    17,    77,    17,    60,    21,    54,
      -1,    57,    54,    12,    20,    77,    21,    17,    -1,    58,
      20,    77,    21,    54,    -1,    15,    74,    17,    -1,    15,
      17,    -1,    16,    17,    -1,    42,    -1,    60,    17,    -1,
      61,    -1,    68,    34,    -1,    68,    35,    -1,    68,    -1,
      62,    24,    74,    -1,    28,    -1,    28,    69,    -1,    28,
      20,    64,    21,    -1,    27,    20,    64,    21,    -1,    74,
      -1,    -1,    64,    19,    74,    -1,    10,    20,    77,    21,
      65,    11,    65,    -1,    59,    -1,    54,    -1,    10,    20,
      77,    21,    54,    -1,    10,    20,    77,    21,    59,    -1,
      10,    20,    77,    21,    65,    11,    66,    -1,    42,    -1,
      61,    -1,    28,    -1,    28,    69,    -1,    63,    -1,    68,
      18,    63,    -1,    68,    18,    28,    -1,    22,    70,    23,
      -1,    69,    22,    70,    23,    -1,    74,    -1,    70,    19,
      74,    -1,    68,    -1,    53,    -1,    68,    35,    -1,    68,
      34,    -1,    20,    74,    21,    -1,    71,    -1,    72,    33,
      71,    -1,    72,    -1,    73,    32,    72,    -1,    73,    -1,
      74,    -1,    74,    31,    74,    -1,    75,    -1,    76,    37,
      20,    77,    21,    -1,    76,    -1,    77,    36,    76,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   113,   114,   117,   118,   121,   140,   141,
     142,   143,   146,   149,   150,   153,   154,   155,   156,   157,
     160,   161,   172,   173,   176,   177,   180,   183,   184,   187,
     188,   190,   191,   192,   193,   196,   197,   198,   199,   202,
     203,   204,   207,   208,   209,   210,   212,   214,   216,   218,
     228,   233,   241,   247,   248,   252,   253,   256,   257,   258,
     259,   262,   265,   266,   269,   270,   273,   274,   275,   278,
     285,   286,   289,   290,   292,   301,   302,   305,   306,   307,
     308,   309,   312,   313,   316,   317,   320,   321,   322,   323,
     324,   327,   328,   331,   332,   335,   338,   339,   342,   343,
     346,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_LOCATION",
  "TOKEN_OBJECT", "TOKEN_VAR_REAL", "TOKEN_VAR_INT", "TOKEN_VOID",
  "TOKEN_FUNCTION", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_WHILE", "TOKEN_DO",
  "TOKEN_FOR", "TOKEN_RETURN", "TOKEN_BREAK", "TOKEN_SEMICOLON",
  "TOKEN_DOT", "TOKEN_COMMA", "TOKEN_LPAR", "TOKEN_RPAR", "TOKEN_LSBRA",
  "TOKEN_RSBRA", "TOKEN_ASSIGN", "TOKEN_BEGIN", "TOKEN_END",
  "TOKEN_OBJECT_FEATURE", "TOKEN_IDENTIFIER", "TOKEN_UINT", "TOKEN_REAL",
  "TOKEN_OPER_REL", "TOKEN_OPER_SIGNADD", "TOKEN_OPER_MUL",
  "TOKEN_PLUSPLUS", "TOKEN_MINUSMINUS", "TOKEN_BOOL_AND", "TOKEN_BOOL_OR",
  "$accept", "program", "global_variables", "type", "local_variables",
  "simple_type", "complex_type", "ranges", "names", "values",
  "declare_functions", "function_header", "return_type", "parameters",
  "declare_function_", "number", "block_of_instructions", "commands",
  "forcycle", "do_cycle", "while_cycle", "command", "simple_command",
  "assign", "variable_left", "call_fce", "call_parameters", "matched",
  "unmatched", "init", "variable", "array_access", "exps",
  "expression_base", "expression_mul", "expression_add", "expression",
  "expression_bool_base", "expression_bool_or", "expression_bool", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    42,    43,    43,
      43,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    53,    53,    53,    53,    54,
      54,    54,    55,    55,    55,    55,    56,    57,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    62,    62,    63,    63,    64,    64,    64,    65,
      65,    65,    66,    66,    66,    67,    67,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    74,    75,    75,    76,    76,
      77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     2,     1,     1,     3,     1,     1,
       1,     1,     2,     3,     4,     1,     3,     3,     5,     7,
       1,     1,     3,     3,     0,     1,     2,     1,     1,     2,
       4,     6,     7,     5,     6,     2,     2,     1,     1,     2,
       3,     3,     1,     2,     1,     2,     1,     1,     1,     9,
       7,     5,     3,     2,     2,     1,     2,     1,     2,     2,
       1,     3,     1,     2,     4,     4,     1,     0,     3,     7,
       1,     1,     5,     5,     7,     1,     1,     1,     2,     1,
       3,     3,     3,     4,     1,     3,     1,     1,     2,     2,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     5,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,    10,    11,     8,     9,    28,    27,
       4,     5,     6,     0,     0,    25,    15,     0,     0,    12,
       0,     0,     0,    27,     0,     0,     7,     0,     0,     0,
       0,    26,     0,     0,     0,     0,    77,    38,    37,     0,
      87,    79,    86,    91,    93,    95,    16,    17,    13,     0,
       0,     0,     0,     0,     0,     0,    67,    67,     0,    78,
      36,    35,     0,    89,    88,     0,     0,     0,    14,     0,
       2,    33,    29,     0,     0,     0,     0,    90,     0,    66,
       0,     0,    84,     0,    81,    80,    92,    94,     0,    18,
       0,    48,    47,    46,     0,     0,     0,    39,    77,     0,
      55,    71,     0,     0,     0,     0,    70,     0,    57,     0,
      42,    44,    60,     0,    31,    34,     0,     0,    65,    64,
       0,    82,     0,    21,     0,    20,     0,    53,     0,    54,
      40,    78,    41,    43,    45,     0,     0,     0,    56,     0,
      58,    59,    30,    32,    68,    85,    83,     0,    19,    96,
      98,   100,     0,    52,    62,    75,    76,     0,     0,     0,
      61,    22,    23,     0,     0,     0,     0,    63,     0,     0,
       0,    97,     0,     0,    72,    73,     0,   101,     0,     0,
      51,     0,     0,     0,     0,     0,    99,     0,    69,    74,
       0,    50,     0,     0,     0,    49,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    99,   100,    11,    12,    19,    17,   124,
      13,    22,    14,    53,    15,    40,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    41,    78,   188,   111,   157,
      42,    59,    81,    43,    44,    45,   149,   150,   151,   152
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -128
static const yytype_int16 yypact[] =
{
    -128,    30,   178,  -128,  -128,  -128,  -128,  -128,  -128,    23,
    -128,    36,  -128,    83,    90,   178,    68,    40,    77,    95,
      45,   101,   118,  -128,    90,   131,  -128,   114,   139,   135,
     152,  -128,    22,   154,   131,   156,    -2,  -128,  -128,    66,
    -128,  -128,    34,  -128,   166,   169,  -128,   174,  -128,   185,
     188,   188,   182,    55,    43,   191,   131,   131,   131,   198,
    -128,  -128,    94,  -128,  -128,   131,   131,   194,  -128,   140,
    -128,  -128,  -128,   223,   188,   188,    63,  -128,    88,  -128,
     111,     0,  -128,   131,   196,  -128,  -128,   166,   105,  -128,
     205,  -128,  -128,  -128,    61,   214,   206,  -128,   187,    23,
    -128,  -128,    98,   213,   188,   215,  -128,   217,  -128,   212,
    -128,  -128,    38,   209,  -128,  -128,   188,   131,  -128,  -128,
     131,  -128,    56,  -128,    27,  -128,   131,  -128,   221,  -128,
    -128,   117,  -128,  -128,  -128,     8,   227,   131,  -128,   131,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,   159,  -128,   210,
    -128,   203,    -5,  -128,   220,  -128,  -128,   226,   224,    -4,
    -128,  -128,  -128,   131,   225,   165,   131,   198,   131,   131,
     188,  -128,   131,   228,   235,   236,   238,   203,     4,    41,
    -128,    49,   131,   190,   121,   233,  -128,    62,  -128,  -128,
     230,  -128,   165,   188,   241,  -128,   165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,  -128,     7,     1,  -128,  -128,  -128,  -128,  -128,
    -128,   229,   239,   201,  -128,   -80,   -50,  -128,  -128,  -128,
    -128,    91,    73,   123,  -128,   197,   204,   -64,   -96,  -128,
     -65,   -91,   177,   199,   200,  -128,   -23,  -128,    96,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -72
static const yytype_int16 yytable[] =
{
      70,    71,    46,    10,   112,   110,   134,   131,   125,     9,
     159,    55,     4,     5,     6,     7,   165,   170,    57,   120,
      58,   184,    23,   121,   114,   115,     4,     5,     6,     7,
       3,   166,   166,    79,    79,    82,   154,   112,   133,    52,
     166,   178,   179,    51,    89,   181,   147,     4,     5,     6,
       7,    16,    62,   148,   136,   187,    62,    26,    18,    27,
      82,    52,   185,   167,    75,    30,   143,   162,    63,    64,
     186,   128,   140,   141,    73,   120,    74,   166,   127,   146,
     113,    34,    73,   192,   116,   166,    20,   189,    35,    36,
      37,    38,    25,    39,   144,    60,    61,   145,   166,    21,
     112,   176,     4,     5,     6,     7,    28,   117,    90,   118,
      91,    92,    93,    94,    95,   174,   160,    29,   112,   112,
     180,    35,    84,    69,   132,    35,    98,   112,   194,    31,
     117,   112,   119,   123,    37,    38,   155,    39,    32,    83,
     171,   -63,    47,   195,     4,     5,     6,     7,    35,    98,
      90,    34,    91,    92,    93,    94,    95,    96,    35,    36,
      37,    38,    48,    39,    49,    69,    97,    35,    98,     4,
       5,     6,     7,    50,    54,   173,    56,    91,    92,    93,
      94,    95,     4,     5,     6,     7,     8,   161,    37,    38,
      69,    39,    35,    98,     4,     5,     6,     7,    67,    65,
      90,    66,    91,    92,    93,    94,    95,    57,    68,    58,
      72,   -62,    77,    69,    34,    69,    57,    35,    98,    88,
      83,    35,    36,    37,    38,   126,    39,     4,     5,     6,
       7,   129,   130,   135,   138,   137,   139,   142,   153,   158,
     164,   163,    58,   168,   169,   172,   -71,   -70,   182,   183,
     191,   193,   196,    33,    24,    76,   175,   190,   156,    85,
     122,    80,   177,     0,    86,     0,    87
};

static const yytype_int16 yycheck[] =
{
      50,    51,    25,     2,    69,    69,   102,    98,    88,     2,
     137,    34,     4,     5,     6,     7,    21,    21,    20,    19,
      22,    17,    15,    23,    74,    75,     4,     5,     6,     7,
       0,    36,    36,    56,    57,    58,    28,   102,   102,    32,
      36,   168,   169,    21,    67,   172,    19,     4,     5,     6,
       7,    28,    18,    26,   104,   182,    18,    17,    22,    19,
      83,    54,    21,   154,    21,    20,   116,   147,    34,    35,
      21,    94,    34,    35,    19,    19,    21,    36,    17,    23,
      73,    20,    19,    21,    21,    36,     3,   183,    27,    28,
      29,    30,    24,    32,   117,    29,    30,   120,    36,     9,
     165,   165,     4,     5,     6,     7,    29,    19,    10,    21,
      12,    13,    14,    15,    16,   165,   139,    22,   183,   184,
     170,    27,    28,    25,    26,    27,    28,   192,   192,    28,
      19,   196,    21,    28,    29,    30,   135,    32,    20,    22,
     163,    24,    28,   193,     4,     5,     6,     7,    27,    28,
      10,    20,    12,    13,    14,    15,    16,    17,    27,    28,
      29,    30,    23,    32,    29,    25,    26,    27,    28,     4,
       5,     6,     7,    21,    20,    10,    20,    12,    13,    14,
      15,    16,     4,     5,     6,     7,     8,    28,    29,    30,
      25,    32,    27,    28,     4,     5,     6,     7,    24,    33,
      10,    32,    12,    13,    14,    15,    16,    20,    23,    22,
      28,    24,    21,    25,    20,    25,    20,    27,    28,    25,
      22,    27,    28,    29,    30,    20,    32,     4,     5,     6,
       7,    17,    26,    20,    17,    20,    24,    28,    17,    12,
      37,    31,    22,    17,    20,    20,    11,    11,    20,    11,
      17,    21,    11,    24,    15,    54,   165,   184,   135,    62,
      83,    57,   166,    -1,    65,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    39,    40,     0,     4,     5,     6,     7,     8,    41,
      42,    43,    44,    48,    50,    52,    28,    46,    22,    45,
       3,     9,    49,    41,    50,    24,    17,    19,    29,    22,
      20,    28,    20,    49,    20,    27,    28,    29,    30,    32,
      53,    63,    68,    71,    72,    73,    74,    28,    23,    29,
      21,    21,    41,    51,    20,    74,    20,    20,    22,    69,
      29,    30,    18,    34,    35,    33,    32,    24,    23,    25,
      54,    54,    28,    19,    21,    21,    51,    21,    64,    74,
      64,    70,    74,    22,    28,    63,    71,    72,    25,    74,
      10,    12,    13,    14,    15,    16,    17,    26,    28,    41,
      42,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      65,    66,    68,    41,    54,    54,    21,    19,    21,    21,
      19,    23,    70,    28,    47,    53,    20,    17,    74,    17,
      26,    69,    26,    65,    66,    20,    54,    20,    17,    24,
      34,    35,    28,    54,    74,    74,    23,    19,    26,    74,
      75,    76,    77,    17,    28,    42,    61,    67,    12,    77,
      74,    28,    53,    31,    37,    21,    36,    69,    17,    20,
      21,    74,    20,    10,    54,    59,    65,    76,    77,    77,
      54,    77,    20,    11,    17,    21,    21,    77,    65,    66,
      60,    17,    21,    21,    65,    54,    11
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, program, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, program)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, program); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Program *program)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Program *program;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (program);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Program *program)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Program *program;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, program);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Program *program)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, program)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    Program *program;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , program);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, program); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Program *program)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, program)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    Program *program;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (program);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (Program *program);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (Program *program)
#else
int
yyparse (program)
    Program *program;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "bison.y"
    { 
	  std::vector<Parameter_entry> p;
	  program->add_global((yyvsp[(1) - (6)].instructions));
	  reg(program, Create_type(TypeVoid),"main", p, (yyvsp[(6) - (6)].instructions)); 
		;}
    break;

  case 3:
#line 113 "bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 4:
#line 114 "bison.y"
    { (yyval.instructions)=join_instructions((yyvsp[(1) - (2)].instructions),(yyvsp[(2) - (2)].instructions));;}
    break;

  case 5:
#line 117 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type);;}
    break;

  case 6:
#line 118 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 7:
#line 122 "bison.y"
    {  
			for(int i =0; i< (yyvsp[(2) - (3)].idents).size(); i++)
			{
				Node * n = program->add((yyvsp[(2) - (3)].idents)[i].id, (yyvsp[(1) - (3)].type)); //pridali sme do stromu pre neskorsie vyhladavanie
				(yyval.instructions).push_back(new InstructionCreate(program->find_var((yyvsp[(2) - (3)].idents)[i].id))); //treba este aktivovat, na to sluzi tato instrukcia
				if ((yyvsp[(2) - (3)].idents)[i].default_set){ //ak bola zadana defaultna hodnota 
					if (n->nested == Local) //toto  je vnode, lebo sa to pre premennu nemeni
						(yyval.instructions).push_back(new InstructionLoadLocal(n));
					else
						(yyval.instructions).push_back(new InstructionLoadGlobal(n));
					(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (3)].idents)[i].ins);
					(yyval.instructions).push_back(new InstructionStore());
					}
			}
		;}
    break;

  case 8:
#line 140 "bison.y"
    { (yyval.type) = Create_type(TypeReal); ;}
    break;

  case 9:
#line 141 "bison.y"
    { (yyval.type) = Create_type(TypeInteger); ;}
    break;

  case 10:
#line 142 "bison.y"
    { (yyval.type) = Create_type(TypeLocation); ;}
    break;

  case 11:
#line 143 "bison.y"
    { (yyval.type) = Create_type(TypeObject); ;}
    break;

  case 12:
#line 146 "bison.y"
    { (yyval.type) = (yyvsp[(2) - (2)].type).composite((yyvsp[(1) - (2)].type)); ;}
    break;

  case 13:
#line 149 "bison.y"
    { (yyval.type) = Create_type(TypeArray,(yyvsp[(2) - (3)].number)); ;}
    break;

  case 14:
#line 150 "bison.y"
    { Create_type t(TypeArray,(yyvsp[(3) - (4)].number)); (yyval.type) = (yyvsp[(1) - (4)].type).composite(t); ;}
    break;

  case 15:
#line 153 "bison.y"
    { (yyval.idents).push_back(Constr((yyvsp[(1) - (1)].ident))); ;}
    break;

  case 16:
#line 154 "bison.y"
    { (yyval.idents).push_back(Constr((yyvsp[(1) - (3)].ident),(yyvsp[(3) - (3)].instructions))); ;}
    break;

  case 17:
#line 155 "bison.y"
    { (yyvsp[(1) - (3)].idents).push_back(Constr((yyvsp[(3) - (3)].ident))); (yyval.idents) = (yyvsp[(1) - (3)].idents); ;}
    break;

  case 18:
#line 156 "bison.y"
    { (yyvsp[(1) - (5)].idents).push_back(Constr((yyvsp[(3) - (5)].ident),(yyvsp[(5) - (5)].instructions)));(yyval.idents) = (yyvsp[(1) - (5)].idents); ;}
    break;

  case 19:
#line 157 "bison.y"
    { (yyvsp[(1) - (7)].idents).push_back((yyvsp[(3) - (7)].ident));(yyval.idents) = (yyvsp[(1) - (7)].idents); ;}
    break;

  case 20:
#line 160 "bison.y"
    { (yyval.instructions)=(yyvsp[(1) - (1)].instructions);;}
    break;

  case 21:
#line 161 "bison.y"
    { 
				Node *n = program->find_var((yyvsp[(1) - (1)].ident)); 
				if (n == NULL)
					{
						std::cout << "aekfuhak" <<std::endl;
					}
				if(n->nested == Local)
					(yyval.instructions).push_back(new InstructionLoadLocal(n));
				else  
					(yyval.instructions).push_back(new InstructionLoadGlobal(n));
			;}
    break;

  case 22:
#line 172 "bison.y"
    {(yyvsp[(1) - (3)].instructions).push_back(instruction_load(program, (yyvsp[(3) - (3)].ident)));(yyval.instructions) = (yyvsp[(1) - (3)].instructions);;}
    break;

  case 23:
#line 173 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions));;}
    break;

  case 24:
#line 176 "bison.y"
    { (yyval.instructions).clear(); program->enter("main"); ;}
    break;

  case 25:
#line 177 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); program->enter("main");;}
    break;

  case 26:
#line 180 "bison.y"
    { (yyval.ident) = (yyvsp[(2) - (2)].ident); program->enter((yyvsp[(2) - (2)].ident)); ;}
    break;

  case 27:
#line 183 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 28:
#line 184 "bison.y"
    { (yyval.type) = Create_type(TypeVoid); ;}
    break;

  case 29:
#line 187 "bison.y"
    { (yyval.entries).push_back(Parameter_entry((yyvsp[(2) - (2)].ident),PARAMETER_BY_VALUE, program->add((yyvsp[(2) - (2)].ident), (yyvsp[(1) - (2)].type))));  ;}
    break;

  case 30:
#line 188 "bison.y"
    { (yyval.entries) = (yyvsp[(1) - (4)].entries); (yyval.entries).push_back(Parameter_entry((yyvsp[(4) - (4)].ident),PARAMETER_BY_VALUE,program->add((yyvsp[(4) - (4)].ident), (yyvsp[(3) - (4)].type))));;}
    break;

  case 31:
#line 190 "bison.y"
    { reg(program,(yyvsp[(1) - (6)].type),(yyvsp[(2) - (6)].ident), (yyvsp[(4) - (6)].entries), (yyvsp[(6) - (6)].instructions));program->leave();;}
    break;

  case 32:
#line 191 "bison.y"
    { reg(program,(yyvsp[(2) - (7)].type),(yyvsp[(3) - (7)].ident),(yyvsp[(5) - (7)].entries),(yyvsp[(7) - (7)].instructions)); program->leave();;}
    break;

  case 33:
#line 192 "bison.y"
    {std::vector<Parameter_entry> a; reg(program,(yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].ident), a, (yyvsp[(5) - (5)].instructions)); program->leave();;}
    break;

  case 34:
#line 193 "bison.y"
    {std::vector<Parameter_entry> a; reg(program, (yyvsp[(2) - (6)].type), (yyvsp[(3) - (6)].ident), a, (yyvsp[(6) - (6)].instructions));program->leave(); ;}
    break;

  case 35:
#line 196 "bison.y"
    { if (TOKEN_OPER_SIGNADD == OperationMinus ) {(yyvsp[(2) - (2)].f_number)*=-1;} (yyval.instructions).push_back(new InstructionLoad((yyvsp[(2) - (2)].f_number))); ;}
    break;

  case 36:
#line 197 "bison.y"
    { if (TOKEN_OPER_SIGNADD == OperationMinus) {(yyvsp[(2) - (2)].number)*=-1;} (yyval.instructions).push_back(new InstructionLoad((yyvsp[(2) - (2)].number))); ;}
    break;

  case 37:
#line 198 "bison.y"
    { (yyval.instructions).push_back(new InstructionLoad((yyvsp[(1) - (1)].f_number))); ;}
    break;

  case 38:
#line 199 "bison.y"
    { (yyval.instructions).push_back(new InstructionLoad((yyvsp[(1) - (1)].number))); ;}
    break;

  case 39:
#line 202 "bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 40:
#line 203 "bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 41:
#line 204 "bison.y"
    { (yyval.instructions).push_back(new InstructionBegin()); (yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (3)].instructions));(yyval.instructions).push_back(new InstructionEndBlock()); ;}
    break;

  case 42:
#line 207 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 43:
#line 208 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 44:
#line 209 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 45:
#line 210 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 46:
#line 212 "bison.y"
    { program->enter_loop();;}
    break;

  case 47:
#line 214 "bison.y"
    { program->enter_loop();;}
    break;

  case 48:
#line 216 "bison.y"
    { program->enter_loop();;}
    break;

  case 49:
#line 219 "bison.y"
    { 
		  (yyvsp[(9) - (9)].instructions) = join_instructions((yyvsp[(9) - (9)].instructions), (yyvsp[(7) - (9)].instructions)); 
		  (yyvsp[(3) - (9)].instructions).push_back(new InstructionMustJump((yyvsp[(9) - (9)].instructions).size())); 
		  (yyvsp[(5) - (9)].instructions).push_back(new InstructionJump(-1*(yyvsp[(9) - (9)].instructions).size()-(yyvsp[(5) - (9)].instructions).size(),1));
		  (yyvsp[(9) - (9)].instructions) = join_instructions((yyvsp[(9) - (9)].instructions),(yyvsp[(5) - (9)].instructions));
		  (yyval.instructions) = join_instructions((yyvsp[(3) - (9)].instructions),(yyvsp[(9) - (9)].instructions));
		  set_breaks(program, (yyvsp[(5) - (9)].instructions));
		  program->end_loop();
		;}
    break;

  case 50:
#line 229 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(2) - (7)].instructions),(yyvsp[(5) - (7)].instructions)); 
		  (yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size(),1)); 
		  program->end_loop();
		;}
    break;

  case 51:
#line 234 "bison.y"
    {
			(yyval.instructions).push_back(new InstructionMustJump((yyvsp[(3) - (5)].instructions).size()));
			(yyvsp[(3) - (5)].instructions) = join_instructions((yyvsp[(5) - (5)].instructions),(yyvsp[(3) - (5)].instructions));
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(3) - (5)].instructions));
			(yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size(),1));
		  	program->end_loop();
		;}
    break;

  case 52:
#line 242 "bison.y"
    {
			(yyval.instructions) = (yyvsp[(2) - (3)].instructions);
			(yyval.instructions).push_back(new InstructionStore()); //budu vedla seba, takze by to malo prejst
			(yyval.instructions).push_back(new InstructionReturn());
		;}
    break;

  case 53:
#line 247 "bison.y"
    {(yyval.instructions).push_back(new InstructionReturn());;}
    break;

  case 54:
#line 249 "bison.y"
    {
			(yyval.instructions).push_back(new InstructionBreak(program->last_loop_number));
		;}
    break;

  case 55:
#line 252 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 56:
#line 253 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions);;}
    break;

  case 57:
#line 256 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 58:
#line 257 "bison.y"
    { (yyval.instructions).push_back(new InstructionPlusPlus());;}
    break;

  case 59:
#line 258 "bison.y"
    { (yyval.instructions).push_back(new InstructionMinusMinus());;}
    break;

  case 60:
#line 259 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 61:
#line 262 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(new InstructionStore()) ;}
    break;

  case 62:
#line 265 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (1)].ident)));;}
    break;

  case 63:
#line 266 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (2)].ident))); (yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 64:
#line 269 "bison.y"
    { (yyval.instructions) = (yyvsp[(3) - (4)].instructions); (yyval.instructions).push_back(new Call(program->find_f((yyvsp[(1) - (4)].ident))));;}
    break;

  case 65:
#line 270 "bison.y"
    { (yyval.instructions) = (yyvsp[(3) - (4)].instructions);(yyval.instructions).push_back(feature((yyvsp[(1) - (4)].of)));;}
    break;

  case 66:
#line 273 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 67:
#line 274 "bison.y"
    {(yyval.instructions).clear();;}
    break;

  case 68:
#line 275 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(3) - (3)].instructions),(yyvsp[(1) - (3)].instructions)); ;}
    break;

  case 69:
#line 279 "bison.y"
    {
		  (yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size()));
		  (yyvsp[(3) - (7)].instructions).push_back(new InstructionJump(1,(yyvsp[(5) - (7)].instructions).size()));
		  (yyval.instructions) =join_instructions((yyvsp[(3) - (7)].instructions),(yyvsp[(5) - (7)].instructions));
		  (yyval.instructions) =join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
		;}
    break;

  case 70:
#line 285 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 71:
#line 286 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 72:
#line 289 "bison.y"
    {(yyvsp[(3) - (5)].instructions).push_back(new InstructionJump(1,(yyvsp[(5) - (5)].instructions).size()));(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].instructions),(yyvsp[(5) - (5)].instructions));;}
    break;

  case 73:
#line 290 "bison.y"
    {(yyvsp[(3) - (5)].instructions).push_back(new InstructionJump(1,(yyvsp[(5) - (5)].instructions).size()));(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].instructions),(yyvsp[(5) - (5)].instructions));;}
    break;

  case 74:
#line 293 "bison.y"
    {
		  (yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size()));
		  (yyvsp[(3) - (7)].instructions).push_back(new InstructionJump(1,(yyvsp[(5) - (7)].instructions).size()));
		  (yyval.instructions) = join_instructions((yyvsp[(3) - (7)].instructions),(yyvsp[(5) - (7)].instructions));
		  (yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
		;}
    break;

  case 75:
#line 301 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 76:
#line 302 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 77:
#line 305 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (1)].ident)));;}
    break;

  case 78:
#line 306 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (2)].ident))); (yyval.instructions)=join_instructions((yyval.instructions),(yyvsp[(2) - (2)].instructions));;}
    break;

  case 79:
#line 307 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 82:
#line 312 "bison.y"
    { (yyval.instructions) = (yyvsp[(2) - (3)].instructions); (yyval.instructions).push_back(new InstructionLoad());;}
    break;

  case 83:
#line 313 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (4)].instructions), (yyvsp[(3) - (4)].instructions)); (yyval.instructions).push_back(new InstructionLoad());;}
    break;

  case 84:
#line 316 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 85:
#line 317 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); ;}
    break;

  case 86:
#line 320 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 87:
#line 321 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 88:
#line 322 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions); (yyval.instructions).push_back(new InstructionMinusMinus());;}
    break;

  case 89:
#line 323 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions); (yyval.instructions).push_back(new InstructionPlusPlus());;}
    break;

  case 90:
#line 324 "bison.y"
    {(yyval.instructions) = (yyvsp[(2) - (3)].instructions);;}
    break;

  case 91:
#line 327 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 92:
#line 328 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operMul((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 93:
#line 331 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 94:
#line 332 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operAdd((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 95:
#line 335 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 96:
#line 338 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 97:
#line 339 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions),(yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operRel((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 98:
#line 342 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 99:
#line 343 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(1) - (5)].instructions),(yyvsp[(4) - (5)].instructions)); (yyval.instructions).push_back((operOr((yyvsp[(2) - (5)].operation))));;}
    break;

  case 100:
#line 346 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 101:
#line 347 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions),(yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(new InstructionBinaryAnd()); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2179 "bison.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, program, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, program, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, program, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc, program);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, program);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, program, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, program);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, program);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 349 "bison.y"


extern FILE * yyin;

static void yyerror(unsigned *line,Program* ctx, const char *message)
{
	printf("Co to, co to? %s, line %d\n", message, *line);
}

int main(int argc, char ** argv)
{
	if(argc<2)
    	{
		puts("Kde mam vstup, ha?\n");
		return 16;
    	}

	if((yyin=fopen(argv[1], "r"))==0)
    	{
		puts("Vstup je divny\n");
		return 16;
    	}

	Program q;
	Create_type t;
	q.add(".", t);//anonymna premenna
	yyparse(&q);
    	fclose(yyin);
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	q.output(&q.defined);
	for (int i =0; i<q.instructions.size(); i++)
		std::cout << q.instructions[i]->name_<<std::endl;
	q.save_to_xml();
	return 0;	
}

