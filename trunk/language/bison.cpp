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
     TOKEN_FUNCTION = 263,
     TOKEN_ARRAY = 264,
     TOKEN_IF = 265,
     TOKEN_ELSE = 266,
     TOKEN_WHILE = 267,
     TOKEN_DO = 268,
     TOKEN_FOR = 269,
     TOKEN_BOOL_AND = 270,
     TOKEN_BOOL_OR = 271,
     TOKEN_RETURN = 272,
     TOKEN_BREAK = 273,
     TOKEN_SEMICOLON = 274,
     TOKEN_DOT = 275,
     TOKEN_COMMA = 276,
     TOKEN_LPAR = 277,
     TOKEN_RPAR = 278,
     TOKEN_LSBRA = 279,
     TOKEN_RSBRA = 280,
     TOKEN_ASSIGN = 281,
     TOKEN_BEGIN = 282,
     TOKEN_END = 283,
     TOKEN_IDENTIFIER = 284,
     TOKEN_UINT = 285,
     TOKEN_REAL = 286,
     TOKEN_OPER_REL = 287,
     TOKEN_OPER_SIGNADD = 288,
     TOKEN_OPER_MUL = 289,
     TOKEN_PLUSPLUS = 290,
     TOKEN_MINUSMINUS = 291
   };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_LOCATION 259
#define TOKEN_OBJECT 260
#define TOKEN_VAR_REAL 261
#define TOKEN_VAR_INT 262
#define TOKEN_FUNCTION 263
#define TOKEN_ARRAY 264
#define TOKEN_IF 265
#define TOKEN_ELSE 266
#define TOKEN_WHILE 267
#define TOKEN_DO 268
#define TOKEN_FOR 269
#define TOKEN_BOOL_AND 270
#define TOKEN_BOOL_OR 271
#define TOKEN_RETURN 272
#define TOKEN_BREAK 273
#define TOKEN_SEMICOLON 274
#define TOKEN_DOT 275
#define TOKEN_COMMA 276
#define TOKEN_LPAR 277
#define TOKEN_RPAR 278
#define TOKEN_LSBRA 279
#define TOKEN_RSBRA 280
#define TOKEN_ASSIGN 281
#define TOKEN_BEGIN 282
#define TOKEN_END 283
#define TOKEN_IDENTIFIER 284
#define TOKEN_UINT 285
#define TOKEN_REAL 286
#define TOKEN_OPER_REL 287
#define TOKEN_OPER_SIGNADD 288
#define TOKEN_OPER_MUL 289
#define TOKEN_PLUSPLUS 290
#define TOKEN_MINUSMINUS 291




/* Copy the first part of user declarations.  */
#line 1 "bison.y"

	#include "header1.h"
	#include "./tree/my_stack.h"
	#include <iostream>
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
#line 205 "bison.cpp"

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
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  221

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

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
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    10,    11,    14,    18,    22,    26,    30,
      35,    40,    45,    50,    52,    60,    64,    74,    76,    80,
      83,    87,    91,    96,    98,   102,   106,   112,   113,   115,
     118,   124,   131,   136,   142,   145,   148,   150,   152,   155,
     159,   163,   165,   168,   170,   173,   183,   191,   197,   201,
     204,   207,   209,   212,   214,   217,   220,   222,   226,   230,
     232,   235,   240,   242,   243,   247,   255,   257,   259,   265,
     271,   279,   284,   289,   293,   300,   302,   305,   307,   311,
     315,   319,   324,   326,   330,   332,   334,   337,   340,   344,
     346,   350,   352,   356,   358,   360,   364,   366,   372,   374
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    39,    45,     3,    22,    23,    49,    -1,
      -1,    39,    40,    -1,     6,    44,    19,    -1,     7,    44,
      19,    -1,     4,    41,    19,    -1,     5,    44,    19,    -1,
       9,     4,    42,    19,    -1,     9,     6,    42,    19,    -1,
       9,     7,    42,    19,    -1,     9,     5,    42,    19,    -1,
      29,    -1,    29,    26,    27,    30,    21,    30,    28,    -1,
      41,    21,    29,    -1,    41,    21,    29,    26,    27,    30,
      21,    30,    28,    -1,    29,    -1,    42,    21,    29,    -1,
      29,    43,    -1,    42,    29,    43,    -1,    24,    30,    25,
      -1,    43,    24,    30,    25,    -1,    29,    -1,    29,    26,
      48,    -1,    44,    21,    29,    -1,    44,    21,    29,    26,
      48,    -1,    -1,    47,    -1,     8,    29,    -1,    46,    22,
      44,    23,    49,    -1,    47,    46,    22,    44,    23,    49,
      -1,    46,    22,    23,    49,    -1,    47,    46,    22,    23,
      49,    -1,    33,    31,    -1,    33,    30,    -1,    31,    -1,
      30,    -1,    27,    28,    -1,    27,    19,    28,    -1,    27,
      50,    28,    -1,    57,    -1,    50,    57,    -1,    58,    -1,
      50,    58,    -1,    14,    22,    59,    19,    69,    19,    52,
      23,    49,    -1,    13,    49,    12,    22,    69,    23,    19,
      -1,    12,    22,    69,    23,    49,    -1,    17,    66,    19,
      -1,    17,    19,    -1,    18,    19,    -1,    40,    -1,    52,
      19,    -1,    53,    -1,    60,    35,    -1,    60,    36,    -1,
      60,    -1,    54,    26,    60,    -1,    54,    26,    48,    -1,
      29,    -1,    29,    61,    -1,    29,    22,    56,    23,    -1,
      66,    -1,    -1,    56,    21,    66,    -1,    10,    22,    69,
      23,    57,    11,    57,    -1,    51,    -1,    49,    -1,    10,
      22,    69,    23,    49,    -1,    10,    22,    69,    23,    51,
      -1,    10,    22,    69,    23,    57,    11,    58,    -1,     7,
      29,    26,    66,    -1,     6,    29,    26,    66,    -1,    29,
      26,    66,    -1,    29,    24,    66,    25,    26,    66,    -1,
      29,    -1,    29,    61,    -1,    55,    -1,    60,    20,    29,
      -1,    60,    20,    55,    -1,    24,    62,    25,    -1,    61,
      24,    62,    25,    -1,    66,    -1,    62,    21,    66,    -1,
      60,    -1,    48,    -1,    60,    36,    -1,    60,    35,    -1,
      22,    66,    23,    -1,    63,    -1,    64,    34,    63,    -1,
      64,    -1,    65,    33,    64,    -1,    65,    -1,    66,    -1,
      66,    32,    66,    -1,    67,    -1,    68,    16,    22,    69,
      23,    -1,    68,    -1,    69,    15,    68,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    70,    71,    74,    75,    76,    77,    78,
      79,    80,    81,    84,    85,    86,    87,    90,    91,    92,
      93,    96,    97,   100,   101,   102,   103,   106,   107,   110,
     113,   114,   115,   116,   118,   119,   120,   121,   123,   124,
     125,   127,   128,   129,   130,   132,   133,   134,   135,   136,
     137,   138,   139,   141,   142,   143,   144,   146,   147,   149,
     150,   153,   155,   156,   157,   159,   160,   161,   163,   164,
     165,   167,   168,   169,   170,   172,   173,   174,   175,   176,
     178,   179,   181,   182,   184,   185,   186,   187,   188,   190,
     191,   193,   194,   196,   198,   199,   201,   202,   204,   205
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_LOCATION",
  "TOKEN_OBJECT", "TOKEN_VAR_REAL", "TOKEN_VAR_INT", "TOKEN_FUNCTION",
  "TOKEN_ARRAY", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_WHILE", "TOKEN_DO",
  "TOKEN_FOR", "TOKEN_BOOL_AND", "TOKEN_BOOL_OR", "TOKEN_RETURN",
  "TOKEN_BREAK", "TOKEN_SEMICOLON", "TOKEN_DOT", "TOKEN_COMMA",
  "TOKEN_LPAR", "TOKEN_RPAR", "TOKEN_LSBRA", "TOKEN_RSBRA", "TOKEN_ASSIGN",
  "TOKEN_BEGIN", "TOKEN_END", "TOKEN_IDENTIFIER", "TOKEN_UINT",
  "TOKEN_REAL", "TOKEN_OPER_REL", "TOKEN_OPER_SIGNADD", "TOKEN_OPER_MUL",
  "TOKEN_PLUSPLUS", "TOKEN_MINUSMINUS", "$accept", "program",
  "global_variables", "local_variables", "location_name", "array_names",
  "ranges", "names", "declare_functions", "function_header",
  "declare_function_", "number", "block_of_instructions", "commands",
  "command", "simple_command", "assign", "variable_left", "call_fce",
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
     285,   286,   287,   288,   289,   290,   291
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    40,
      40,    40,    40,    41,    41,    41,    41,    42,    42,    42,
      42,    43,    43,    44,    44,    44,    44,    45,    45,    46,
      47,    47,    47,    47,    48,    48,    48,    48,    49,    49,
      49,    50,    50,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    56,    56,    56,    57,    57,    57,    58,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    64,
      64,    65,    65,    66,    67,    67,    68,    68,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     2,     3,     3,     3,     3,     4,
       4,     4,     4,     1,     7,     3,     9,     1,     3,     2,
       3,     3,     4,     1,     3,     3,     5,     0,     1,     2,
       5,     6,     4,     5,     2,     2,     1,     1,     2,     3,
       3,     1,     2,     1,     2,     9,     7,     5,     3,     2,
       2,     1,     2,     1,     2,     2,     1,     3,     3,     1,
       2,     4,     1,     0,     3,     7,     1,     1,     5,     5,
       7,     4,     4,     3,     6,     1,     2,     1,     3,     3,
       3,     4,     1,     3,     1,     1,     2,     2,     3,     1,
       3,     1,     3,     1,     1,     3,     1,     5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    27,     1,     0,     0,     0,     0,     0,     0,
       4,     0,     0,    28,    13,     0,    23,     0,     0,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     8,     0,     5,     6,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    37,    36,     0,
      24,    25,     0,    19,     9,     0,     0,    12,    10,    11,
       0,     0,    32,     0,     0,     0,     0,     0,    35,    34,
       0,     0,     0,    18,    20,     2,     0,     0,     0,     0,
       0,     0,     0,    38,    75,    51,    67,     0,    66,     0,
      53,     0,    77,    41,    43,    56,    30,    33,     0,     0,
       0,    26,    21,     0,     0,     0,     0,     0,    49,     0,
      75,    85,    84,    89,    91,    93,     0,    50,    39,    63,
       0,    76,    40,    42,    44,    52,     0,     0,    54,    55,
      31,     0,     0,    22,    94,    96,    98,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    87,    86,     0,     0,
      48,     0,    62,     0,    82,     0,    58,    57,    78,    79,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,    90,    92,     0,    61,     0,    80,
       0,     0,    95,     0,    99,     0,    68,    69,     0,    47,
       0,     0,     0,     0,    73,     0,    64,    83,    81,    16,
       0,     0,     0,     0,    72,    71,     0,     0,    97,     0,
      65,    70,    46,     0,     0,     0,    74,     0,     0,    45,
       0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    85,    15,    37,    53,    17,    11,    12,
      13,   111,    86,    87,    88,    89,    90,    91,    92,   151,
     210,    94,   143,   112,   121,   153,   113,   114,   115,   134,
     135,   136,   137
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int16 yypact[] =
{
    -100,    11,   174,  -100,    19,    31,    31,    31,    40,   139,
    -100,    95,    67,    18,    78,    -5,   103,    61,    76,    92,
    -100,   125,   125,   125,   125,   110,    41,   140,   143,  -100,
     138,   175,  -100,   145,  -100,  -100,   160,    -6,    12,    46,
      62,   162,   166,   186,    48,   170,   178,  -100,  -100,    91,
    -100,   184,   171,   172,  -100,   194,   160,  -100,  -100,  -100,
     166,   121,  -100,   166,   166,   190,   203,   198,  -100,  -100,
     175,   201,   197,  -100,   172,  -100,   206,   207,   166,   208,
      57,   212,   204,  -100,    86,  -100,  -100,   159,  -100,   214,
    -100,   209,  -100,  -100,  -100,    -1,  -100,  -100,   166,   210,
     211,  -100,  -100,   213,    87,    87,   222,     1,  -100,    87,
     193,  -100,     4,  -100,   202,   215,   218,  -100,  -100,    87,
      87,   192,  -100,  -100,  -100,  -100,   128,   216,  -100,  -100,
    -100,   219,   221,  -100,   217,  -100,   223,    -3,     2,   224,
     225,   226,   195,   231,   220,   227,  -100,  -100,    87,    87,
    -100,   199,  -100,    71,  -100,    87,  -100,   232,   234,  -100,
    -100,   228,    87,   235,    87,    45,   166,    87,   233,   236,
      87,    87,    87,  -100,  -100,   202,    87,  -100,    87,  -100,
      82,   237,  -100,    87,   223,   238,   242,   250,   252,  -100,
      22,    87,    87,   239,  -100,   122,  -100,  -100,  -100,  -100,
      23,    87,   185,   247,  -100,  -100,   241,   240,  -100,    38,
    -100,  -100,  -100,    87,   245,    45,  -100,   166,   259,  -100,
      45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,  -100,   269,  -100,   129,   188,     3,  -100,   260,
    -100,   -26,   -42,  -100,   107,    68,  -100,  -100,   147,  -100,
     -59,   -83,  -100,   -60,   167,   123,   131,   127,  -100,   -77,
    -100,   116,   -99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const yytype_int16 yytable[] =
{
      62,    95,    93,   116,   124,    50,   138,   140,   141,    18,
      19,     3,   164,    54,    29,    55,    30,   164,    75,   127,
     165,    96,    97,    56,   127,   166,     8,    95,   123,    43,
     142,    57,   144,    55,   128,   129,   106,   164,   164,   146,
     147,    56,   152,   154,   101,   203,   208,    65,    14,     4,
       5,     6,     7,   164,     9,   185,   130,    77,    78,    79,
      16,   215,    80,    81,    42,    58,   157,    55,   190,    20,
      16,    64,    61,   195,    84,    56,   108,    16,   154,   109,
      32,    59,    33,    55,   200,   182,   110,    47,    48,    26,
      49,    56,   178,   193,   194,    34,   179,    33,    25,   196,
     156,   197,   209,   178,    28,    95,   188,   198,   119,   109,
     120,    35,   -59,    33,   204,   205,   110,    47,    48,   211,
      49,    68,    69,   186,   189,     4,     5,     6,     7,    31,
       9,    76,    41,    77,    78,    79,   216,   164,    80,    81,
      82,   207,    95,    21,    22,    23,    24,    95,    61,    83,
      84,    38,    39,    40,    36,    95,   218,   110,    47,    48,
      95,    49,    44,     4,     5,     6,     7,    46,     9,    76,
      45,    77,    78,    79,    51,   219,    80,    81,     4,     5,
       6,     7,     8,     9,    52,    60,    61,   122,    84,     4,
       5,     6,     7,    61,     9,    76,    72,    77,    78,    79,
      66,    71,    80,    81,    67,    47,    48,    33,    49,    63,
      70,    33,    61,    98,    84,   119,   155,   120,   -60,   170,
     176,   171,   177,    73,    99,   100,   102,   103,   104,   105,
     107,   117,   118,   125,   139,   126,   148,   150,   133,   163,
     131,   132,   161,   173,    74,   158,   167,   160,   149,   162,
     172,   155,   127,   -67,   168,   169,   119,   183,   181,   191,
     201,   -66,   192,   202,   206,   199,   212,   213,   217,    84,
     220,    10,   187,    27,   159,   214,   175,   145,   180,   174,
     184
};

static const yytype_uint8 yycheck[] =
{
      42,    61,    61,    80,    87,    31,   105,     6,     7,     6,
       7,     0,    15,    19,    19,    21,    21,    15,    60,    20,
      23,    63,    64,    29,    20,    23,     8,    87,    87,    26,
      29,    19,   109,    21,    35,    36,    78,    15,    15,    35,
      36,    29,   119,   120,    70,    23,    23,    44,    29,     4,
       5,     6,     7,    15,     9,    10,    98,    12,    13,    14,
      29,    23,    17,    18,    23,    19,   126,    21,   167,    29,
      29,    23,    27,   172,    29,    29,    19,    29,   155,    22,
      19,    19,    21,    21,   183,   162,    29,    30,    31,    22,
      33,    29,    21,   170,   171,    19,    25,    21,     3,   176,
     126,   178,   201,    21,    26,   165,   165,    25,    22,    22,
      24,    19,    26,    21,   191,   192,    29,    30,    31,   202,
      33,    30,    31,   165,   166,     4,     5,     6,     7,    26,
       9,    10,    22,    12,    13,    14,   213,    15,    17,    18,
      19,    19,   202,     4,     5,     6,     7,   207,    27,    28,
      29,    22,    23,    24,    29,   215,   215,    29,    30,    31,
     220,    33,    22,     4,     5,     6,     7,    29,     9,    10,
      27,    12,    13,    14,    29,   217,    17,    18,     4,     5,
       6,     7,     8,     9,    24,    23,    27,    28,    29,     4,
       5,     6,     7,    27,     9,    10,    24,    12,    13,    14,
      30,    30,    17,    18,    26,    30,    31,    21,    33,    23,
      26,    21,    27,    23,    29,    22,    24,    24,    26,    24,
      21,    26,    23,    29,    21,    27,    25,    30,    22,    22,
      22,    19,    28,    19,    12,    26,    34,    19,    25,    16,
      30,    30,    21,    23,    56,    29,    22,    28,    33,    32,
      19,    24,    20,    11,    29,    29,    22,    22,    30,    26,
      22,    11,    26,    11,    25,    28,    19,    26,    23,    29,
      11,     2,   165,    13,   127,   207,   149,   110,   155,   148,
     164
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,     0,     4,     5,     6,     7,     8,     9,
      40,    45,    46,    47,    29,    41,    29,    44,    44,    44,
      29,     4,     5,     6,     7,     3,    22,    46,    26,    19,
      21,    26,    19,    21,    19,    19,    29,    42,    42,    42,
      42,    22,    23,    44,    22,    27,    29,    30,    31,    33,
      48,    29,    24,    43,    19,    21,    29,    19,    19,    19,
      23,    27,    49,    23,    23,    44,    30,    26,    30,    31,
      26,    30,    24,    29,    43,    49,    10,    12,    13,    14,
      17,    18,    19,    28,    29,    40,    49,    50,    51,    52,
      53,    54,    55,    57,    58,    60,    49,    49,    23,    21,
      27,    48,    25,    30,    22,    22,    49,    22,    19,    22,
      29,    48,    60,    63,    64,    65,    66,    19,    28,    22,
      24,    61,    28,    57,    58,    19,    26,    20,    35,    36,
      49,    30,    30,    25,    66,    67,    68,    69,    69,    12,
       6,     7,    29,    59,    66,    61,    35,    36,    34,    33,
      19,    56,    66,    62,    66,    24,    48,    60,    29,    55,
      28,    21,    32,    16,    15,    23,    23,    22,    29,    29,
      24,    26,    19,    23,    63,    64,    21,    23,    21,    25,
      62,    30,    66,    22,    68,    10,    49,    51,    57,    49,
      69,    26,    26,    66,    66,    69,    66,    66,    25,    28,
      69,    22,    11,    23,    66,    66,    25,    19,    23,    69,
      57,    58,    19,    26,    52,    23,    66,    23,    57,    49,
      11
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
      
/* Line 1267 of yacc.c.  */
#line 1637 "bison.cpp"
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


#line 207 "bison.y"


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
	q.add_string(".", TypeUndefined);//anonymna premenna
	yyparse(&q);
    	fclose(yyin);
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	q.output(&q.defined);
	return 0;	
}

