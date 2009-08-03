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
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

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
      66,    68,    70,    74,    78,    79,    81,    85,    87,    89,
      92,    97,   103,   110,   115,   121,   124,   127,   129,   131,
     133,   135,   138,   142,   146,   148,   151,   153,   156,   158,
     160,   162,   171,   179,   185,   189,   192,   195,   198,   200,
     202,   204,   207,   210,   212,   216,   218,   221,   226,   231,
     233,   234,   238,   246,   248,   250,   256,   262,   270,   272,
     275,   277,   280,   282,   286,   290,   294,   299,   301,   305,
     307,   309,   312,   315,   319,   321,   325,   327,   331,   333,
     335,   339,   341,   347,   349
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    48,     3,    20,    21,    56,    -1,
      -1,    40,    42,    -1,    43,    -1,    44,    -1,    41,    46,
      17,    -1,     6,    -1,     7,    -1,     4,    -1,     5,    -1,
      43,    45,    -1,    22,    29,    23,    -1,    45,    22,    29,
      23,    -1,    28,    -1,    28,    24,    77,    -1,    46,    19,
      28,    -1,    46,    19,    28,    24,    77,    -1,    46,    19,
      28,    24,    25,    47,    26,    -1,    53,    -1,    28,    -1,
      47,    19,    28,    -1,    47,    19,    53,    -1,    -1,    52,
      -1,    50,     9,    28,    -1,    41,    -1,     8,    -1,    41,
      28,    -1,    51,    19,    41,    28,    -1,    49,    20,    51,
      21,    56,    -1,    52,    49,    20,    51,    21,    56,    -1,
      49,    20,    21,    56,    -1,    52,    49,    20,    21,    56,
      -1,    32,    30,    -1,    32,    29,    -1,    30,    -1,    29,
      -1,    25,    -1,    26,    -1,    54,    55,    -1,    54,    17,
      55,    -1,    54,    57,    55,    -1,    68,    -1,    57,    68,
      -1,    69,    -1,    57,    69,    -1,    14,    -1,    13,    -1,
      12,    -1,    58,    20,    70,    80,    17,    63,    21,    56,
      -1,    59,    56,    12,    20,    80,    21,    17,    -1,    60,
      20,    80,    21,    56,    -1,    15,    77,    17,    -1,    15,
      17,    -1,    16,    17,    -1,    63,    17,    -1,    42,    -1,
      61,    -1,    64,    -1,    71,    34,    -1,    71,    35,    -1,
      71,    -1,    65,    24,    77,    -1,    28,    -1,    28,    72,
      -1,    28,    20,    67,    21,    -1,    27,    20,    67,    21,
      -1,    77,    -1,    -1,    67,    19,    77,    -1,    10,    20,
      80,    21,    68,    11,    68,    -1,    62,    -1,    56,    -1,
      10,    20,    80,    21,    56,    -1,    10,    20,    80,    21,
      61,    -1,    10,    20,    80,    21,    68,    11,    69,    -1,
      42,    -1,    64,    17,    -1,    28,    -1,    28,    72,    -1,
      66,    -1,    71,    18,    66,    -1,    71,    18,    28,    -1,
      22,    73,    23,    -1,    72,    22,    73,    23,    -1,    77,
      -1,    73,    19,    77,    -1,    71,    -1,    53,    -1,    71,
      35,    -1,    71,    34,    -1,    20,    77,    21,    -1,    74,
      -1,    75,    33,    74,    -1,    75,    -1,    76,    32,    75,
      -1,    76,    -1,    77,    -1,    77,    31,    77,    -1,    78,
      -1,    79,    37,    20,    80,    21,    -1,    79,    -1,    80,
      36,    79,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   114,   115,   118,   119,   122,   141,   142,
     143,   144,   147,   150,   151,   154,   155,   156,   157,   158,
     161,   162,   173,   174,   177,   178,   181,   184,   185,   188,
     189,   192,   193,   194,   195,   198,   199,   200,   201,   204,
     207,   210,   211,   212,   215,   216,   217,   218,   220,   222,
     224,   226,   236,   242,   251,   260,   261,   267,   270,   271,
     273,   274,   275,   276,   279,   282,   283,   286,   287,   290,
     291,   292,   295,   302,   303,   306,   307,   309,   318,   319,
     322,   323,   324,   325,   326,   329,   330,   333,   334,   337,
     338,   339,   340,   341,   344,   345,   348,   349,   352,   355,
     356,   359,   360,   363,   364
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
  "declare_function_", "number", "begin", "end", "block_of_instructions",
  "commands", "forcycle", "do_cycle", "while_cycle", "command",
  "command_var", "simple_command", "assign", "variable_left", "call_fce",
  "call_parameters", "matched", "unmatched", "init", "variable",
  "array_access", "exps", "expression_base", "expression_mul",
  "expression_add", "expression", "expression_bool_base",
  "expression_bool_or", "expression_bool", 0
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
      55,    56,    56,    56,    57,    57,    57,    57,    58,    59,
      60,    61,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    63,    63,    64,    65,    65,    66,    66,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    70,    70,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     2,     1,     1,     3,     1,     1,
       1,     1,     2,     3,     4,     1,     3,     3,     5,     7,
       1,     1,     3,     3,     0,     1,     3,     1,     1,     2,
       4,     5,     6,     4,     5,     2,     2,     1,     1,     1,
       1,     2,     3,     3,     1,     2,     1,     2,     1,     1,
       1,     8,     7,     5,     3,     2,     2,     2,     1,     1,
       1,     2,     2,     1,     3,     1,     2,     4,     4,     1,
       0,     3,     7,     1,     1,     5,     5,     7,     1,     2,
       1,     2,     1,     3,     3,     3,     4,     1,     3,     1,
       1,     2,     2,     3,     1,     3,     1,     3,     1,     1,
       3,     1,     5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,    10,    11,     8,     9,    28,    27,
       4,     5,     6,     0,     0,     0,    25,    15,     0,     0,
      12,     0,     0,     0,    27,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,    80,
      38,    37,     0,    90,    82,    89,    94,    96,    98,    16,
      17,    13,     0,     0,    39,     0,    33,    29,     0,     0,
       0,     0,     0,    70,    70,     0,    81,    36,    35,     0,
      92,    91,     0,     0,     0,    14,     2,     0,    50,    49,
      48,     0,     0,     0,    40,    80,     0,    58,    41,    74,
       0,     0,     0,     0,    59,    73,     0,    60,     0,    44,
      46,    63,     0,    31,    34,     0,    93,     0,    69,     0,
       0,    87,     0,    84,    83,    95,    97,     0,    18,     0,
      55,     0,    56,    42,    81,    43,    45,    47,     0,     0,
       0,    57,     0,    61,    62,    30,    32,     0,    68,    67,
       0,    85,     0,    21,     0,    20,    99,   101,   103,     0,
      54,    65,    78,     0,     0,     0,     0,    64,    71,    88,
      86,     0,    19,     0,     0,     0,     0,    66,    79,     0,
       0,     0,    22,    23,   100,     0,     0,    75,    76,     0,
     104,     0,     0,    53,     0,     0,     0,     0,     0,   102,
       0,    72,    77,     0,    52,     0,    51,     0,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    86,    87,    11,    12,    20,    18,   144,
      13,    14,    15,    34,    16,    43,    55,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    44,   107,
     191,   100,   154,    45,    66,   110,    46,    47,    48,   146,
     147,   148,   149
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -124
static const yytype_int16 yypact[] =
{
    -124,    78,    98,  -124,  -124,  -124,  -124,  -124,  -124,    66,
    -124,    97,  -124,    42,    68,    99,    98,    91,    52,   108,
     121,   129,    28,   136,  -124,   163,   157,  -124,   160,   176,
     171,   181,   187,   185,    60,  -124,    86,   157,   194,    96,
    -124,  -124,   145,  -124,  -124,   -10,  -124,   184,   189,  -124,
     202,  -124,   205,   187,  -124,    70,  -124,  -124,   204,   187,
     187,   110,   208,   157,   157,   157,   209,  -124,  -124,    29,
    -124,  -124,   157,   157,   195,  -124,  -124,   210,  -124,  -124,
    -124,    93,   215,   207,  -124,   104,    66,  -124,  -124,  -124,
     141,   214,   187,   216,  -124,  -124,   218,  -124,   213,  -124,
    -124,    32,   211,  -124,  -124,   187,  -124,   131,  -124,   144,
       3,  -124,   157,   220,  -124,  -124,   184,   106,  -124,   157,
    -124,   221,  -124,  -124,   168,  -124,  -124,  -124,    11,   229,
     157,  -124,   157,  -124,  -124,  -124,  -124,   157,  -124,  -124,
     157,  -124,    45,  -124,    -7,  -124,   212,  -124,   217,    17,
    -124,   222,  -124,   225,   157,   226,    23,  -124,  -124,  -124,
    -124,   130,  -124,   157,   227,   166,   157,   209,  -124,    -6,
     157,   187,  -124,  -124,  -124,   157,   228,   234,   238,   239,
     217,    72,    25,  -124,    27,   157,   191,   230,   235,  -124,
      34,  -124,  -124,   187,  -124,   166,  -124,   242,   166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,     7,     2,  -124,  -124,  -124,  -124,  -124,
    -124,   240,  -124,   219,  -124,  -107,  -124,   -70,   -32,  -124,
    -124,  -124,  -124,    92,  -124,    77,   132,  -124,   190,   197,
     -53,   -85,  -124,   -54,   -79,   150,   192,   193,  -124,   -23,
    -124,   101,  -123
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -75
static const yytype_int16 yytable[] =
{
      56,   101,    99,    49,    10,   127,   124,   156,    69,     9,
     145,   181,   161,   123,    62,     4,     5,     6,     7,   162,
     125,    76,   140,    24,    70,    71,   141,   103,   104,    33,
     166,   169,     4,     5,     6,     7,   101,   126,   165,   151,
     108,   108,   111,    33,   171,    21,   188,   182,   189,    32,
      69,   118,   184,   166,   173,   195,    38,   113,   121,   166,
     129,   166,   190,   166,   140,   102,   133,   134,   160,    27,
     166,    28,   167,   136,     4,     5,     6,     7,     3,    58,
      77,    59,    78,    79,    80,    81,    82,    83,    22,   111,
       4,     5,     6,     7,    17,    54,    84,    38,    85,    38,
      85,   192,     4,     5,     6,     7,     8,    60,    23,   157,
     120,   101,   179,    37,   158,    26,    64,   159,    65,    19,
      38,    39,    40,    41,    64,    42,    65,   101,   -65,    58,
     152,   105,   101,   177,   143,    40,    41,    29,    42,   183,
     174,   101,   197,    30,   101,     4,     5,     6,     7,    31,
     137,    77,   138,    78,    79,    80,    81,    82,   172,    40,
      41,   196,    42,   137,    35,   139,    54,    84,    38,    85,
       4,     5,     6,     7,    67,    68,   176,    37,    78,    79,
      80,    81,    82,    36,    38,    39,    40,    41,    50,    42,
     112,    54,   -66,    38,    85,     4,     5,     6,     7,    51,
      52,    77,    53,    78,    79,    80,    81,    82,     4,     5,
       6,     7,    54,    57,    63,    37,    54,    72,    38,    85,
     117,    73,    38,    39,    40,    41,    74,    42,    75,   106,
     119,   112,   122,    84,   128,   131,   130,   132,   150,   135,
      64,   155,   168,   163,    65,   -74,   170,   175,   185,   -59,
     186,   193,   194,   198,   164,    61,    25,   178,   187,   114,
     153,   109,   142,     0,   115,     0,   116,   180
};

static const yytype_int16 yycheck[] =
{
      32,    55,    55,    26,     2,    90,    85,   130,    18,     2,
     117,    17,    19,    83,    37,     4,     5,     6,     7,    26,
      90,    53,    19,    16,    34,    35,    23,    59,    60,    22,
      36,   154,     4,     5,     6,     7,    90,    90,    21,    28,
      63,    64,    65,    36,    21,     3,    21,   170,    21,    21,
      18,    74,   175,    36,   161,    21,    27,    28,    81,    36,
      92,    36,   185,    36,    19,    58,    34,    35,    23,    17,
      36,    19,   151,   105,     4,     5,     6,     7,     0,    19,
      10,    21,    12,    13,    14,    15,    16,    17,    20,   112,
       4,     5,     6,     7,    28,    25,    26,    27,    28,    27,
      28,   186,     4,     5,     6,     7,     8,    21,     9,   132,
      17,   165,   165,    20,   137,    24,    20,   140,    22,    22,
      27,    28,    29,    30,    20,    32,    22,   181,    24,    19,
     128,    21,   186,   165,    28,    29,    30,    29,    32,   171,
     163,   195,   195,    22,   198,     4,     5,     6,     7,    20,
      19,    10,    21,    12,    13,    14,    15,    16,    28,    29,
      30,   193,    32,    19,    28,    21,    25,    26,    27,    28,
       4,     5,     6,     7,    29,    30,    10,    20,    12,    13,
      14,    15,    16,    20,    27,    28,    29,    30,    28,    32,
      22,    25,    24,    27,    28,     4,     5,     6,     7,    23,
      29,    10,    21,    12,    13,    14,    15,    16,     4,     5,
       6,     7,    25,    28,    20,    20,    25,    33,    27,    28,
      25,    32,    27,    28,    29,    30,    24,    32,    23,    21,
      20,    22,    17,    26,    20,    17,    20,    24,    17,    28,
      20,    12,    17,    31,    22,    11,    20,    20,    20,    11,
      11,    21,    17,    11,    37,    36,    16,   165,   181,    69,
     128,    64,   112,    -1,    72,    -1,    73,   166
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    39,    40,     0,     4,     5,     6,     7,     8,    41,
      42,    43,    44,    48,    49,    50,    52,    28,    46,    22,
      45,     3,    20,     9,    41,    49,    24,    17,    19,    29,
      22,    20,    21,    41,    51,    28,    20,    20,    27,    28,
      29,    30,    32,    53,    66,    71,    74,    75,    76,    77,
      28,    23,    29,    21,    25,    54,    56,    28,    19,    21,
      21,    51,    77,    20,    20,    22,    72,    29,    30,    18,
      34,    35,    33,    32,    24,    23,    56,    10,    12,    13,
      14,    15,    16,    17,    26,    28,    41,    42,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    68,
      69,    71,    41,    56,    56,    21,    21,    67,    77,    67,
      73,    77,    22,    28,    66,    74,    75,    25,    77,    20,
      17,    77,    17,    55,    72,    55,    68,    69,    20,    56,
      20,    17,    24,    34,    35,    28,    56,    19,    21,    21,
      19,    23,    73,    28,    47,    53,    77,    78,    79,    80,
      17,    28,    42,    64,    70,    12,    80,    77,    77,    77,
      23,    19,    26,    31,    37,    21,    36,    72,    17,    80,
      20,    21,    28,    53,    77,    20,    10,    56,    61,    68,
      79,    17,    80,    56,    80,    20,    11,    63,    21,    21,
      80,    68,    69,    21,    17,    21,    56,    68,    11
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
#line 107 "bison.y"
    { 
	  std::vector<Parameter_entry> p;
	  program->add_global((yyvsp[(1) - (6)].instructions));
	  reg(program, p, (yyvsp[(6) - (6)].instructions)); 
		;}
    break;

  case 3:
#line 114 "bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 4:
#line 115 "bison.y"
    { (yyval.instructions)=join_instructions((yyvsp[(1) - (2)].instructions),(yyvsp[(2) - (2)].instructions));;}
    break;

  case 5:
#line 118 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type);;}
    break;

  case 6:
#line 119 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 7:
#line 123 "bison.y"
    {  
			for(int i =0; i< (yyvsp[(2) - (3)].idents).size(); i++)
			{
				Node * n = program->add((yyvsp[(2) - (3)].idents)[i].id, (yyvsp[(1) - (3)].type)); //pridali sme do stromu pre neskorsie vyhladavanie
				(yyval.instructions).push_back(new InstructionCreate(program->find_var((yyvsp[(2) - (3)].idents)[i].id))); 
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
#line 141 "bison.y"
    { (yyval.type) = Create_type(TypeReal); ;}
    break;

  case 9:
#line 142 "bison.y"
    { (yyval.type) = Create_type(TypeInteger); ;}
    break;

  case 10:
#line 143 "bison.y"
    { (yyval.type) = Create_type(TypeLocation); ;}
    break;

  case 11:
#line 144 "bison.y"
    { (yyval.type) = Create_type(TypeObject); ;}
    break;

  case 12:
#line 147 "bison.y"
    { (yyval.type) = (yyvsp[(2) - (2)].type).composite((yyvsp[(1) - (2)].type)); ;}
    break;

  case 13:
#line 150 "bison.y"
    { (yyval.type) = Create_type(TypeArray,(yyvsp[(2) - (3)].number)); ;}
    break;

  case 14:
#line 151 "bison.y"
    { Create_type t(TypeArray,(yyvsp[(3) - (4)].number)); (yyval.type) = (yyvsp[(1) - (4)].type).composite(t); ;}
    break;

  case 15:
#line 154 "bison.y"
    { (yyval.idents).push_back(Constr((yyvsp[(1) - (1)].ident))); ;}
    break;

  case 16:
#line 155 "bison.y"
    { (yyval.idents).push_back(Constr((yyvsp[(1) - (3)].ident),(yyvsp[(3) - (3)].instructions))); ;}
    break;

  case 17:
#line 156 "bison.y"
    { (yyvsp[(1) - (3)].idents).push_back(Constr((yyvsp[(3) - (3)].ident))); (yyval.idents) = (yyvsp[(1) - (3)].idents); ;}
    break;

  case 18:
#line 157 "bison.y"
    { (yyvsp[(1) - (5)].idents).push_back(Constr((yyvsp[(3) - (5)].ident),(yyvsp[(5) - (5)].instructions)));(yyval.idents) = (yyvsp[(1) - (5)].idents); ;}
    break;

  case 19:
#line 158 "bison.y"
    { (yyvsp[(1) - (7)].idents).push_back((yyvsp[(3) - (7)].ident));(yyval.idents) = (yyvsp[(1) - (7)].idents); ;}
    break;

  case 20:
#line 161 "bison.y"
    { (yyval.instructions)=(yyvsp[(1) - (1)].instructions);;}
    break;

  case 21:
#line 162 "bison.y"
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
#line 173 "bison.y"
    {(yyvsp[(1) - (3)].instructions).push_back(instruction_load(program, (yyvsp[(3) - (3)].ident)));(yyval.instructions) = (yyvsp[(1) - (3)].instructions);;}
    break;

  case 23:
#line 174 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions));;}
    break;

  case 24:
#line 177 "bison.y"
    { (yyval.instructions).clear(); program->enter("main", Create_type(TypeVoid)); ;}
    break;

  case 25:
#line 178 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); program->enter("main", Create_type(TypeVoid));;}
    break;

  case 26:
#line 181 "bison.y"
    { (yyval.ident) = (yyvsp[(3) - (3)].ident); program->enter((yyvsp[(3) - (3)].ident), (yyvsp[(1) - (3)].type)); ;}
    break;

  case 27:
#line 184 "bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 28:
#line 185 "bison.y"
    { (yyval.type) = Create_type(TypeVoid); ;}
    break;

  case 29:
#line 188 "bison.y"
    { (yyval.entries).push_back(Parameter_entry((yyvsp[(2) - (2)].ident),PARAMETER_BY_VALUE, program->add((yyvsp[(2) - (2)].ident), (yyvsp[(1) - (2)].type)))); ;}
    break;

  case 30:
#line 189 "bison.y"
    { (yyval.entries) = (yyvsp[(1) - (4)].entries); (yyval.entries).push_back(Parameter_entry((yyvsp[(4) - (4)].ident),PARAMETER_BY_VALUE,program->add((yyvsp[(4) - (4)].ident), (yyvsp[(3) - (4)].type))));;}
    break;

  case 31:
#line 192 "bison.y"
    { reg(program,(yyvsp[(3) - (5)].entries),(yyvsp[(5) - (5)].instructions));program->leave();;}
    break;

  case 32:
#line 193 "bison.y"
    { reg(program,(yyvsp[(4) - (6)].entries),(yyvsp[(6) - (6)].instructions)); program->leave();;}
    break;

  case 33:
#line 194 "bison.y"
    {std::vector<Parameter_entry> a; reg(program, a, (yyvsp[(4) - (4)].instructions)); program->leave();;}
    break;

  case 34:
#line 195 "bison.y"
    {std::vector<Parameter_entry> a; reg(program, a, (yyvsp[(5) - (5)].instructions));program->leave(); ;}
    break;

  case 35:
#line 198 "bison.y"
    { if (TOKEN_OPER_SIGNADD == OperationMinus ) {(yyvsp[(2) - (2)].f_number)*=-1;} (yyval.instructions).push_back(new InstructionLoad((yyvsp[(2) - (2)].f_number))); ;}
    break;

  case 36:
#line 199 "bison.y"
    { if (TOKEN_OPER_SIGNADD == OperationMinus) {(yyvsp[(2) - (2)].number)*=-1;} (yyval.instructions).push_back(new InstructionLoad((yyvsp[(2) - (2)].number))); ;}
    break;

  case 37:
#line 200 "bison.y"
    { (yyval.instructions).push_back(new InstructionLoad((yyvsp[(1) - (1)].f_number))); ;}
    break;

  case 38:
#line 201 "bison.y"
    { (yyval.instructions).push_back(new InstructionLoad((yyvsp[(1) - (1)].number))); ;}
    break;

  case 39:
#line 204 "bison.y"
    { program->core->depth++; ;}
    break;

  case 40:
#line 207 "bison.y"
    { program->core->depth--; ;}
    break;

  case 41:
#line 210 "bison.y"
    { (yyval.instructions).push_back(new InstructionBegin()); (yyval.instructions).push_back(new InstructionEndBlock());;}
    break;

  case 42:
#line 211 "bison.y"
    { (yyval.instructions).clear();(yyval.instructions).push_back(new InstructionBegin()); (yyval.instructions).push_back(new InstructionEndBlock()); ;}
    break;

  case 43:
#line 212 "bison.y"
    { (yyval.instructions).push_back(new InstructionBegin()); (yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (3)].instructions));(yyval.instructions).push_back(new InstructionEndBlock()); ;}
    break;

  case 44:
#line 215 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 45:
#line 216 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 46:
#line 217 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 47:
#line 218 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 48:
#line 220 "bison.y"
    { program->enter_loop();;}
    break;

  case 49:
#line 222 "bison.y"
    { program->enter_loop();;}
    break;

  case 50:
#line 224 "bison.y"
    { program->enter_loop();;}
    break;

  case 51:
#line 227 "bison.y"
    { 
		  (yyvsp[(8) - (8)].instructions) = join_instructions((yyvsp[(8) - (8)].instructions), (yyvsp[(6) - (8)].instructions)); 
		  (yyvsp[(3) - (8)].instructions).push_back(new InstructionMustJump((yyvsp[(8) - (8)].instructions).size())); 
		  (yyvsp[(4) - (8)].instructions).push_back(new InstructionJump(-1*(yyvsp[(8) - (8)].instructions).size()-(yyvsp[(4) - (8)].instructions).size()-1,0));
		  (yyvsp[(8) - (8)].instructions) = join_instructions((yyvsp[(8) - (8)].instructions),(yyvsp[(4) - (8)].instructions));
		  (yyval.instructions) = join_instructions((yyvsp[(3) - (8)].instructions),(yyvsp[(8) - (8)].instructions));
		  set_breaks(program, (yyval.instructions));
		  program->end_loop();
		;}
    break;

  case 52:
#line 237 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(2) - (7)].instructions),(yyvsp[(5) - (7)].instructions)); 
		  (yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size()-1,0));
		  set_breaks(program, (yyval.instructions));
		  program->end_loop();
		;}
    break;

  case 53:
#line 243 "bison.y"
    {
			(yyval.instructions).push_back(new InstructionMustJump((yyvsp[(5) - (5)].instructions).size()));
			(yyvsp[(3) - (5)].instructions) = join_instructions((yyvsp[(5) - (5)].instructions),(yyvsp[(3) - (5)].instructions));
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(3) - (5)].instructions));
			(yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size(),0));
		  	set_breaks(program, (yyval.instructions));
		  	program->end_loop();
		;}
    break;

  case 54:
#line 252 "bison.y"
    {
			(yyval.instructions) = (yyvsp[(2) - (3)].instructions);
			std::cout << program->nested_function << "-----"<< std::endl;
			getc(stdin);
			(yyval.instructions).insert((yyval.instructions).begin(), new InstructionLoadLocal(program->nested_function->return_var));
			(yyval.instructions).push_back(new InstructionStore()); //budu vedla seba, takze by to malo prejst
			(yyval.instructions).push_back(new InstructionReturn());
		;}
    break;

  case 55:
#line 260 "bison.y"
    {(yyval.instructions).push_back(new InstructionReturn());;}
    break;

  case 56:
#line 262 "bison.y"
    {
			std::cout << "Adding break to in depth" <<program->core->depth << std::endl;
			getc(stdin);
			(yyval.instructions).push_back(new InstructionBreak(program->last_loop_number, program->core->depth));
		;}
    break;

  case 57:
#line 267 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions);;}
    break;

  case 58:
#line 270 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 59:
#line 271 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 60:
#line 273 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 61:
#line 274 "bison.y"
    { (yyval.instructions).push_back(new InstructionPlusPlus());;}
    break;

  case 62:
#line 275 "bison.y"
    { (yyval.instructions).push_back(new InstructionMinusMinus());;}
    break;

  case 63:
#line 276 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 64:
#line 279 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(new InstructionStore()) ;}
    break;

  case 65:
#line 282 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (1)].ident)));;}
    break;

  case 66:
#line 283 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (2)].ident))); (yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 67:
#line 286 "bison.y"
    { (yyval.instructions) = (yyvsp[(3) - (4)].instructions); (yyval.instructions).push_back(new Call(program->find_f((yyvsp[(1) - (4)].ident))));;}
    break;

  case 68:
#line 287 "bison.y"
    { (yyval.instructions) = (yyvsp[(3) - (4)].instructions);(yyval.instructions).push_back(feature((yyvsp[(1) - (4)].of)));;}
    break;

  case 69:
#line 290 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 70:
#line 291 "bison.y"
    {(yyval.instructions).clear();;}
    break;

  case 71:
#line 292 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(3) - (3)].instructions),(yyvsp[(1) - (3)].instructions)); ;}
    break;

  case 72:
#line 296 "bison.y"
    {
		  (yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size()));
		  (yyvsp[(3) - (7)].instructions).push_back(new InstructionJump(0,(yyvsp[(5) - (7)].instructions).size()));
		  (yyval.instructions) =join_instructions((yyvsp[(3) - (7)].instructions),(yyvsp[(5) - (7)].instructions));
		  (yyval.instructions) =join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
		;}
    break;

  case 73:
#line 302 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 74:
#line 303 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 75:
#line 306 "bison.y"
    {(yyvsp[(3) - (5)].instructions).push_back(new InstructionJump(0,(yyvsp[(5) - (5)].instructions).size()));(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].instructions),(yyvsp[(5) - (5)].instructions));;}
    break;

  case 76:
#line 307 "bison.y"
    {(yyvsp[(3) - (5)].instructions).push_back(new InstructionJump(0,(yyvsp[(5) - (5)].instructions).size()));(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].instructions),(yyvsp[(5) - (5)].instructions));;}
    break;

  case 77:
#line 310 "bison.y"
    {
		  (yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size()));
		  (yyvsp[(3) - (7)].instructions).push_back(new InstructionJump(0,(yyvsp[(5) - (7)].instructions).size()));
		  (yyval.instructions) = join_instructions((yyvsp[(3) - (7)].instructions),(yyvsp[(5) - (7)].instructions));
		  (yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
		;}
    break;

  case 78:
#line 318 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 79:
#line 319 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions);;}
    break;

  case 80:
#line 322 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (1)].ident)));;}
    break;

  case 81:
#line 323 "bison.y"
    { (yyval.instructions).push_back(instruction_load(program, (yyvsp[(1) - (2)].ident))); (yyval.instructions)=join_instructions((yyval.instructions),(yyvsp[(2) - (2)].instructions));;}
    break;

  case 82:
#line 324 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 85:
#line 329 "bison.y"
    { (yyval.instructions) = (yyvsp[(2) - (3)].instructions); (yyval.instructions).push_back(new InstructionLoad());;}
    break;

  case 86:
#line 330 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (4)].instructions), (yyvsp[(3) - (4)].instructions)); (yyval.instructions).push_back(new InstructionLoad());;}
    break;

  case 87:
#line 333 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 88:
#line 334 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); ;}
    break;

  case 89:
#line 337 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 90:
#line 338 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 91:
#line 339 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions); (yyval.instructions).push_back(new InstructionMinusMinus());;}
    break;

  case 92:
#line 340 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions); (yyval.instructions).push_back(new InstructionPlusPlus());;}
    break;

  case 93:
#line 341 "bison.y"
    {(yyval.instructions) = (yyvsp[(2) - (3)].instructions);;}
    break;

  case 94:
#line 344 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 95:
#line 345 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operMul((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 96:
#line 348 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 97:
#line 349 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions), (yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operAdd((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 98:
#line 352 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 99:
#line 355 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 100:
#line 356 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions),(yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(operRel((yyvsp[(2) - (3)].operation))); ;}
    break;

  case 101:
#line 359 "bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 102:
#line 360 "bison.y"
    {(yyval.instructions) = join_instructions((yyvsp[(1) - (5)].instructions),(yyvsp[(4) - (5)].instructions)); (yyval.instructions).push_back((operOr((yyvsp[(2) - (5)].operation))));;}
    break;

  case 103:
#line 363 "bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 104:
#line 364 "bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (3)].instructions),(yyvsp[(3) - (3)].instructions)); (yyval.instructions).push_back(new InstructionBinaryAnd()); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2205 "bison.cpp"
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


#line 366 "bison.y"


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
	std::cout << "haho!" << std::endl;
   	q.execute();
	return 0;	
}

