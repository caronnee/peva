
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 4 "language/bison.y"

#include <iostream>
#include <queue>
#include "../h/lval.h"
#include "../h/robot.h"
#include "../h/parser_functions.h"
#include "../h/hflex.h"

#define YYSTYPE Lval 
#define YYLTYPE unsigned
#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)
#define YYERROR_VERBOSE 1		

static void yyerror(YYLTYPE *line, Robots* ctx, const char *m);



/* Line 189 of yacc.c  */
#line 91 "language/cpp/bison.cpp"

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
     TOKEN_REFERENCE = 272,
     TOKEN_CONTINUE = 273,
     TOKEN_ROBOT = 274,
     TOKEN_OPTION = 275,
     TOKEN_OBJECT_FEATURE = 276,
     TOKEN_SEMICOLON = 277,
     TOKEN_DOT = 278,
     TOKEN_COMMA = 279,
     TOKEN_LPAR = 280,
     TOKEN_RPAR = 281,
     TOKEN_LSBRA = 282,
     TOKEN_RSBRA = 283,
     TOKEN_ASSIGN = 284,
     TOKEN_BEGIN = 285,
     TOKEN_END = 286,
     TOKEN_IDENTIFIER = 287,
     TOKEN_UINT = 288,
     TOKEN_REAL = 289,
     TOKEN_SEEN = 290,
     TOKEN_VISIT = 291,
     TOKEN_VISIT_SEQUENCE = 292,
     TOKEN_KILLED = 293,
     TOKEN_START = 294,
     TOKEN_OPER_REL = 295,
     TOKEN_OPER_SIGNADD = 296,
     TOKEN_OPER_MUL = 297,
     TOKEN_PLUSPLUS = 298,
     TOKEN_MINUSMINUS = 299,
     TOKEN_BOOL_AND = 300,
     TOKEN_BOOL_OR = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


/* Line 264 of yacc.c  */
#line 191 "language/cpp/bison.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNRULES -- Number of states.  */
#define YYNSTATES  249

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    23,    24,    29,    35,
      41,    47,    55,    60,    67,    68,    73,    74,    77,    79,
      81,    85,    87,    89,    91,    93,    96,   100,   105,   107,
     111,   117,   119,   122,   124,   126,   128,   132,   136,   142,
     143,   145,   151,   154,   156,   158,   159,   161,   164,   169,
     173,   179,   182,   186,   189,   192,   194,   196,   198,   200,
     204,   205,   207,   209,   211,   214,   216,   219,   221,   232,
     242,   250,   254,   257,   260,   263,   266,   268,   270,   272,
     274,   278,   281,   286,   291,   296,   298,   299,   303,   311,
     313,   315,   321,   327,   335,   337,   340,   342,   345,   348,
     350,   352,   356,   358,   362,   367,   369,   373,   375,   377,
     381,   383,   387,   389,   393,   395,   397,   401,   403,   407,
     409
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    48,    50,    -1,    50,    -1,    19,    32,
      -1,    49,    30,    53,    51,    54,    65,     3,    25,    26,
      75,    31,    -1,    -1,    51,    38,    40,    33,    -1,    51,
      36,    25,    52,    26,    -1,    51,    37,    25,    52,    26,
      -1,    27,    33,    24,    33,    28,    -1,    52,    24,    27,
      33,    24,    33,    28,    -1,    39,    27,    33,    28,    -1,
      52,    24,    39,    27,    33,    28,    -1,    -1,    53,    20,
      29,    33,    -1,    -1,    54,    56,    -1,    57,    -1,    58,
      -1,    55,    61,    22,    -1,     6,    -1,     7,    -1,     4,
      -1,     5,    -1,    57,    59,    -1,    27,    33,    28,    -1,
      59,    27,    33,    28,    -1,    32,    -1,    32,    29,    96,
      -1,    32,    29,    62,    64,    63,    -1,    60,    -1,    61,
      60,    -1,    30,    -1,    31,    -1,    96,    -1,    64,    24,
      96,    -1,    62,    64,    63,    -1,    64,    24,    62,    64,
      63,    -1,    -1,    71,    -1,    68,    67,    25,    69,    26,
      -1,     9,    32,    -1,     8,    -1,    55,    -1,    -1,    70,
      -1,    55,    32,    -1,    70,    24,    55,    32,    -1,    17,
      55,    32,    -1,    70,    24,    17,    55,    32,    -1,    66,
      75,    -1,    71,    66,    75,    -1,    41,    34,    -1,    41,
      33,    -1,    34,    -1,    33,    -1,    30,    -1,    31,    -1,
      73,    76,    74,    -1,    -1,    77,    -1,    22,    -1,    86,
      -1,    77,    86,    -1,    87,    -1,    77,    87,    -1,    14,
      -1,    78,    25,    88,    99,    22,    81,    26,    73,    77,
      74,    -1,    13,    73,    77,    74,    12,    25,    99,    26,
      22,    -1,    12,    25,    99,    26,    73,    77,    74,    -1,
      15,    96,    22,    -1,    15,    22,    -1,    16,    22,    -1,
      18,    22,    -1,    81,    22,    -1,    56,    -1,    79,    -1,
      82,    -1,    89,    -1,    90,    29,    96,    -1,    32,    91,
      -1,    35,    27,    72,    28,    -1,    32,    25,    85,    26,
      -1,    21,    25,    85,    26,    -1,    96,    -1,    -1,    85,
      24,    96,    -1,    10,    25,    99,    26,    86,    11,    86,
      -1,    80,    -1,    75,    -1,    10,    25,    99,    26,    75,
      -1,    10,    25,    99,    26,    79,    -1,    10,    25,    99,
      26,    86,    11,    87,    -1,    56,    -1,    82,    22,    -1,
      90,    -1,    90,    43,    -1,    90,    44,    -1,    32,    -1,
      84,    -1,    90,    23,    32,    -1,    83,    -1,    27,    92,
      28,    -1,    91,    27,    92,    28,    -1,    96,    -1,    92,
      24,    96,    -1,    89,    -1,    72,    -1,    25,    99,    26,
      -1,    93,    -1,    94,    42,    93,    -1,    94,    -1,    95,
      41,    94,    -1,    95,    -1,    96,    -1,    96,    40,    96,
      -1,    97,    -1,    98,    46,    97,    -1,    98,    -1,    99,
      45,    98,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   143,   148,   153,   160,   161,   162,   163,
     165,   170,   175,   180,   186,   187,   192,   193,   195,   196,
     198,   205,   206,   207,   208,   210,   226,   227,   229,   235,
     250,   263,   264,   266,   268,   270,   292,   312,   324,   340,
     344,   351,   357,   363,   364,   367,   368,   370,   371,   372,
     373,   378,   383,   389,   399,   409,   415,   423,   426,   429,
     436,   437,   440,   441,   442,   443,   444,   447,   449,   468,
     480,   493,   534,   539,   544,   548,   550,   551,   553,   554,
     566,   619,   637,   652,   725,   733,   738,   739,   752,   764,
     765,   767,   776,   785,   797,   798,   800,   801,   811,   822,
     827,   829,   844,   847,   865,   882,   883,   892,   893,   894,
     896,   897,   912,   913,   929,   931,   932,   946,   947,   956,
     957
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
  "TOKEN_FOR", "TOKEN_RETURN", "TOKEN_BREAK", "TOKEN_REFERENCE",
  "TOKEN_CONTINUE", "TOKEN_ROBOT", "TOKEN_OPTION", "TOKEN_OBJECT_FEATURE",
  "TOKEN_SEMICOLON", "TOKEN_DOT", "TOKEN_COMMA", "TOKEN_LPAR",
  "TOKEN_RPAR", "TOKEN_LSBRA", "TOKEN_RSBRA", "TOKEN_ASSIGN",
  "TOKEN_BEGIN", "TOKEN_END", "TOKEN_IDENTIFIER", "TOKEN_UINT",
  "TOKEN_REAL", "TOKEN_SEEN", "TOKEN_VISIT", "TOKEN_VISIT_SEQUENCE",
  "TOKEN_KILLED", "TOKEN_START", "TOKEN_OPER_REL", "TOKEN_OPER_SIGNADD",
  "TOKEN_OPER_MUL", "TOKEN_PLUSPLUS", "TOKEN_MINUSMINUS", "TOKEN_BOOL_AND",
  "TOKEN_BOOL_OR", "$accept", "program", "define_bot", "robot", "targets",
  "places", "options", "global_variables", "type", "local_variables",
  "simple_type", "complex_type", "ranges", "names_", "names", "begin_type",
  "end_type", "values", "declare_functions", "function_header",
  "function_name", "return_type", "parameters_empty", "parameters",
  "declare_function_", "number", "begin", "end", "block_of_instructions",
  "commands_and_empty", "commands", "cycle_for", "command", "command_var",
  "simple_command", "assign", "array", "call_fce", "call_parameters",
  "matched", "unmatched", "init", "unary_var", "variable", "array_access",
  "exps", "expression_base", "expression_mul", "expression_add",
  "expression", "expression_bool_base", "expression_bool_or",
  "expression_bool", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    50,    51,    51,    51,    51,
      52,    52,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    57,    57,    57,    57,    58,    59,    59,    60,    60,
      60,    61,    61,    62,    63,    64,    64,    64,    64,    65,
      65,    66,    67,    68,    68,    69,    69,    70,    70,    70,
      70,    71,    71,    72,    72,    72,    72,    73,    74,    75,
      76,    76,    77,    77,    77,    77,    77,    78,    79,    79,
      79,    79,    79,    79,    79,    79,    80,    80,    81,    81,
      82,    83,    83,    84,    84,    85,    85,    85,    86,    86,
      86,    87,    87,    87,    88,    88,    89,    89,    89,    90,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    93,
      94,    94,    95,    95,    96,    97,    97,    98,    98,    99,
      99
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,    11,     0,     4,     5,     5,
       5,     7,     4,     6,     0,     4,     0,     2,     1,     1,
       3,     1,     1,     1,     1,     2,     3,     4,     1,     3,
       5,     1,     2,     1,     1,     1,     3,     3,     5,     0,
       1,     5,     2,     1,     1,     0,     1,     2,     4,     3,
       5,     2,     3,     2,     2,     1,     1,     1,     1,     3,
       0,     1,     1,     1,     2,     1,     2,     1,    10,     9,
       7,     3,     2,     2,     2,     2,     1,     1,     1,     1,
       3,     2,     4,     4,     4,     1,     0,     3,     7,     1,
       1,     5,     5,     7,     1,     2,     1,     2,     2,     1,
       1,     3,     1,     3,     4,     1,     3,     1,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     4,     1,     2,    14,     6,
       0,    16,     0,     0,     0,     0,    39,    15,     0,     0,
       0,    23,    24,    21,    22,    43,    44,    17,    18,    19,
       0,     0,     0,    40,     0,     0,     0,     0,     7,    28,
      31,     0,     0,    25,     0,    57,    60,    51,     0,     0,
      44,     0,     0,     0,     0,     8,     9,     0,    20,    32,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,    62,    99,     0,     0,    76,    90,     0,    61,     0,
      77,    89,     0,    78,   102,   100,    63,    65,    79,    96,
      42,    45,    52,     0,     0,     0,     0,     0,    33,    56,
      55,     0,     0,   108,   107,    96,   110,   112,   114,    29,
      26,     0,     0,     0,     0,     0,    72,     0,    73,    74,
      86,    86,     0,    81,     0,    58,    59,    64,    66,     0,
      75,     0,     0,    97,    98,     0,     0,     0,    46,     0,
      12,     0,     0,   115,   117,   119,     0,    54,    53,     0,
       0,    35,     0,     0,    27,     0,     0,     0,     0,    71,
       0,    85,     0,     0,   105,     0,     0,    94,     0,     0,
       0,   101,    80,     0,    47,    41,     0,    10,     0,     0,
       0,     0,   109,     0,     0,     0,    34,    30,   111,   113,
       5,     0,     0,     0,     0,    84,    83,     0,   103,     0,
      82,    95,     0,    49,     0,     0,     0,    13,   116,   118,
     120,    37,     0,    36,     0,    91,    92,     0,     0,     0,
      87,   106,   104,     0,     0,    48,    11,     0,     0,     0,
       0,     0,     0,    50,    38,     0,    88,    93,    70,     0,
       0,     0,     0,     0,     0,    69,     0,     0,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    11,    36,     9,    16,    74,    75,
      28,    29,    43,    40,    41,   149,   187,   150,    30,    31,
      49,    32,   137,   138,    33,   103,    46,   126,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,   160,    86,
      87,   169,   104,   105,   123,   163,   106,   107,   108,   143,
     144,   145,   146
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -171
static const yytype_int16 yypact[] =
{
      31,    -5,    29,    42,  -171,  -171,  -171,  -171,  -171,    55,
      63,    97,    75,    88,    96,    85,   225,  -171,    -1,    -1,
      98,  -171,  -171,  -171,  -171,  -171,    86,  -171,   111,  -171,
     143,   125,   151,   225,   134,   146,    65,    78,  -171,   141,
    -171,    56,   149,   160,   163,  -171,   206,  -171,   157,   165,
    -171,   125,   170,   166,    27,  -171,  -171,    30,  -171,  -171,
     168,   169,   172,   179,   181,   125,  -171,   115,   185,   192,
     190,  -171,    84,   196,    86,  -171,  -171,   186,   270,   200,
    -171,  -171,   204,  -171,  -171,  -171,  -171,  -171,  -171,    -8,
    -171,    93,  -171,   201,   207,   213,   210,   306,  -171,  -171,
    -171,   118,    30,  -171,  -171,     2,  -171,   197,   199,  -171,
    -171,   219,   125,   306,   306,   206,  -171,   227,  -171,  -171,
     306,   306,   306,   228,    40,  -171,  -171,  -171,  -171,    12,
    -171,   226,   306,  -171,  -171,   137,   229,   231,   236,   234,
    -171,   239,   232,   224,  -171,   220,     4,  -171,  -171,    30,
      28,  -171,   306,   306,  -171,   240,     8,    11,   238,  -171,
     140,  -171,   155,     0,  -171,   306,   244,  -171,   245,   306,
      64,  -171,  -171,   246,  -171,  -171,   110,  -171,   248,   251,
     306,   306,  -171,   306,    28,    30,  -171,  -171,  -171,   197,
    -171,   302,   125,   275,   306,  -171,  -171,   306,  -171,    79,
    -171,  -171,    -2,  -171,   137,   257,   262,  -171,  -171,  -171,
     220,  -171,    30,  -171,   267,   282,   283,   284,   206,   271,
    -171,  -171,  -171,    47,   265,  -171,  -171,    28,   306,   270,
     238,   306,   272,  -171,  -171,    13,  -171,  -171,  -171,    16,
     125,   302,   277,   206,   290,  -171,   238,   302,  -171
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,  -171,  -171,   301,  -171,   285,  -171,  -171,   -11,    -7,
    -171,  -171,  -171,   269,  -171,   -53,  -170,  -142,  -171,   278,
    -171,  -171,  -171,  -171,  -171,   189,   -64,  -145,   -28,  -171,
    -113,  -171,   128,  -171,    99,   195,  -171,  -171,   205,   -72,
     -68,  -171,   -38,   -46,  -171,   156,   173,   175,  -171,   -26,
     148,   147,  -102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -91
static const yytype_int16 yytable[] =
{
      89,   115,   158,    47,   102,    26,   127,   184,    88,    27,
     128,   156,   157,   193,   211,   131,    21,    22,    23,    24,
     223,   132,    50,    92,   197,   131,    34,     5,   198,     6,
     182,   109,    89,    70,   191,   133,   134,   192,    35,   241,
      88,   117,   242,   183,    72,   133,   134,    73,     1,   183,
       1,    70,   185,   183,    95,    97,   183,   234,   183,   186,
      98,   183,    72,    99,   100,    73,    96,   202,    70,    89,
     227,   101,     8,    99,   100,    10,   151,    88,    58,    72,
     136,   101,    73,   170,   155,   238,   127,   131,    39,    54,
     128,    55,    12,   132,   161,   161,   164,    21,    22,    23,
      24,   248,    54,   197,    56,   230,   172,   222,    17,   121,
     135,   122,    89,    18,    21,    22,    23,    24,    39,   217,
      88,    19,   167,   151,   173,    20,   235,   204,   218,   239,
     246,    38,   212,    13,    14,    15,    70,   116,    42,   164,
      97,    21,    22,    23,    24,    89,    44,    72,    99,   100,
      73,   147,   148,    88,   208,    45,   101,   236,   127,   213,
      48,   237,   128,   215,   194,   205,   195,    52,   220,   244,
      57,   221,    89,    53,   127,   236,   243,    89,   128,   194,
      88,   196,    60,    89,    89,    88,   151,    61,    62,    90,
      91,    88,    88,   224,    93,    89,   110,    89,   112,    94,
      89,    89,   111,    88,   113,    88,   114,   118,    88,    88,
      21,    22,    23,    24,   119,   120,    63,   125,    64,    65,
      66,    67,    68,   124,    69,   129,   130,    70,    71,    21,
      22,    23,    24,    25,   139,   140,    45,   142,    72,   152,
     153,    73,    21,    22,    23,    24,   141,   154,    63,   159,
      64,    65,    66,    67,    68,   165,    69,   175,   171,    70,
     176,   174,   177,   178,   180,   179,   181,   201,    45,   125,
      72,   190,   200,    73,    21,    22,    23,    24,   203,   207,
      63,   206,    64,    65,    66,    67,    68,   219,    69,   225,
     226,    70,   228,   -90,   -77,   229,   231,   233,   240,   245,
      45,   247,    72,     7,    37,    73,    21,    22,    23,    24,
      59,    51,   214,   166,    64,    65,    66,    67,    68,   216,
      69,   199,   232,    70,   168,   188,   162,    70,   189,   209,
     210,    97,    45,     0,    72,     0,     0,    73,    72,    99,
     100,    73,     0,     0,     0,     0,     0,   101
};

static const yytype_int16 yycheck[] =
{
      46,    65,   115,    31,    57,    16,    78,   149,    46,    16,
      78,   113,   114,   158,   184,    23,     4,     5,     6,     7,
      22,    29,    33,    51,    24,    23,    27,    32,    28,     0,
      26,    57,    78,    21,    26,    43,    44,    26,    39,    26,
      78,    67,    26,    45,    32,    43,    44,    35,    19,    45,
      19,    21,    24,    45,    27,    25,    45,   227,    45,    31,
      30,    45,    32,    33,    34,    35,    39,   169,    21,   115,
     212,    41,    30,    33,    34,    20,   102,   115,    22,    32,
      91,    41,    35,   129,   112,   230,   158,    23,    32,    24,
     158,    26,    29,    29,   120,   121,   122,     4,     5,     6,
       7,   246,    24,    24,    26,   218,   132,    28,    33,    25,
      17,    27,   158,    25,     4,     5,     6,     7,    32,   191,
     158,    25,   129,   149,   135,    40,   228,    17,   192,   231,
     243,    33,   185,    36,    37,    38,    21,    22,    27,   165,
      25,     4,     5,     6,     7,   191,     3,    32,    33,    34,
      35,    33,    34,   191,   180,    30,    41,   229,   230,   185,
       9,   229,   230,   191,    24,   176,    26,    33,   194,   241,
      29,   197,   218,    27,   246,   247,   240,   223,   246,    24,
     218,    26,    33,   229,   230,   223,   212,    27,    25,    32,
      25,   229,   230,   204,    24,   241,    28,   243,    26,    33,
     246,   247,    33,   241,    25,   243,    25,    22,   246,   247,
       4,     5,     6,     7,    22,    25,    10,    31,    12,    13,
      14,    15,    16,    27,    18,    25,    22,    21,    22,     4,
       5,     6,     7,     8,    33,    28,    30,    27,    32,    42,
      41,    35,     4,     5,     6,     7,    33,    28,    10,    22,
      12,    13,    14,    15,    16,    27,    18,    26,    32,    21,
      24,    32,    28,    24,    40,    33,    46,    22,    30,    31,
      32,    31,    28,    35,     4,     5,     6,     7,    32,    28,
      10,    33,    12,    13,    14,    15,    16,    12,    18,    32,
      28,    21,    25,    11,    11,    11,    25,    32,    26,    22,
      30,    11,    32,     2,    19,    35,     4,     5,     6,     7,
      41,    33,    10,   124,    12,    13,    14,    15,    16,   191,
      18,   165,   223,    21,   129,   152,   121,    21,   153,   181,
     183,    25,    30,    -1,    32,    -1,    -1,    35,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    48,    49,    50,    32,     0,    50,    30,    53,
      20,    51,    29,    36,    37,    38,    54,    33,    25,    25,
      40,     4,     5,     6,     7,     8,    55,    56,    57,    58,
      65,    66,    68,    71,    27,    39,    52,    52,    33,    32,
      60,    61,    27,    59,     3,    30,    73,    75,     9,    67,
      55,    66,    33,    27,    24,    26,    26,    29,    22,    60,
      33,    27,    25,    10,    12,    13,    14,    15,    16,    18,
      21,    22,    32,    35,    55,    56,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    86,    87,    89,    90,
      32,    25,    75,    24,    33,    27,    39,    25,    30,    33,
      34,    41,    62,    72,    89,    90,    93,    94,    95,    96,
      28,    33,    26,    25,    25,    73,    22,    96,    22,    22,
      25,    25,    27,    91,    27,    31,    74,    86,    87,    25,
      22,    23,    29,    43,    44,    17,    55,    69,    70,    33,
      28,    33,    27,    96,    97,    98,    99,    33,    34,    62,
      64,    96,    42,    41,    28,    75,    99,    99,    77,    22,
      85,    96,    85,    92,    96,    27,    72,    56,    82,    88,
      90,    32,    96,    55,    32,    26,    24,    28,    24,    33,
      40,    46,    26,    45,    64,    24,    31,    63,    93,    94,
      31,    26,    26,    74,    24,    26,    26,    24,    28,    92,
      28,    22,    99,    32,    17,    55,    33,    28,    96,    97,
      98,    63,    62,    96,    10,    75,    79,    86,    73,    12,
      96,    96,    28,    22,    55,    32,    28,    64,    25,    11,
      77,    25,    81,    32,    63,    99,    86,    87,    74,    99,
      26,    26,    26,    73,    86,    22,    77,    11,    74
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Robots *program)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Robots *program;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Robots *program)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Robots *program;
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Robots *program)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, program)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    Robots *program;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , program);
      YYFPRINTF (stderr, "\n");
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Robots *program)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, program)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    Robots *program;
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
int yyparse (Robots *program);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (Robots *program)
#else
int
yyparse (program)
    Robots *program;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  yylloc.first_column = yylloc.last_column = 1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 140 "language/bison.y"
    { 
		program->robots.push_back(program->actualRobot); 
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 144 "language/bison.y"
    { 
		program->robots.push_back(program->actualRobot);
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 149 "language/bison.y"
    { 	
		program->createNew((yyvsp[(2) - (2)].ident)); 
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 154 "language/bison.y"
    { 
		program->actualRobot->add_global((yyvsp[(5) - (11)].instructions));
		program->actualRobot->add_function((yyvsp[(10) - (11)].instructions)); 
		program->actualRobot->consolidate();
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 161 "language/bison.y"
    { program->actualRobot->addKilled((yylsp[(2) - (4)]),(yyvsp[(3) - (4)].operation),(yyvsp[(4) - (4)].number));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 162 "language/bison.y"
    { program->actualRobot->addVisit((yyvsp[(4) - (5)].positions));;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 163 "language/bison.y"
    {program->actualRobot->addVisitSeq((yyvsp[(4) - (5)].positions));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 166 "language/bison.y"
    { 
		(yyval.positions).clear(); 
		(yyval.positions).push_back(Position((yyvsp[(2) - (5)].number),(yyvsp[(4) - (5)].number))); 
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 171 "language/bison.y"
    {
		(yyval.positions) = (yyvsp[(1) - (7)].positions); 
		(yyval.positions).push_back(Position((yyvsp[(4) - (7)].number),(yyvsp[(6) - (7)].number))); 
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 176 "language/bison.y"
    { 
		(yyval.positions).clear(); 
		(yyval.positions).push_back(Position(-1, (yyvsp[(3) - (4)].number))); 
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 181 "language/bison.y"
    {
		(yyval.positions) = (yyvsp[(1) - (6)].positions); 
		(yyval.positions).push_back(Position(-1,(yyvsp[(5) - (6)].number))); 
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 188 "language/bison.y"
    { 
		program->set((yyvsp[(2) - (4)].op),(yyvsp[(4) - (4)].number)); 
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 192 "language/bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 193 "language/bison.y"
    { (yyval.instructions)= join_instructions((yyvsp[(1) - (2)].instructions),(yyvsp[(2) - (2)].instructions));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 195 "language/bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); program->actualRobot->declare_type();;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 196 "language/bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type);program->actualRobot->declare_type();;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 199 "language/bison.y"
    {
			(yyval.instructions) = (yyvsp[(2) - (3)].instructions);
			
			program->actualRobot->leave_type();
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 205 "language/bison.y"
    { (yyval.type) = program->actualRobot->find_type(TypeReal); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 206 "language/bison.y"
    { (yyval.type) = program->actualRobot->find_type(TypeInteger); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 207 "language/bison.y"
    { (yyval.type) = program->actualRobot->find_type(TypeLocation);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 208 "language/bison.y"
    { (yyval.type) = program->actualRobot->find_type(TypeObject); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 211 "language/bison.y"
    { 
			Create_type * t = (yyvsp[(1) - (2)].type); 
			while(!(yyvsp[(2) - (2)].ranges).empty())
			{
				t = program->actualRobot->find_array_type((yyvsp[(2) - (2)].ranges).front(),t);
				(yyvsp[(2) - (2)].ranges).pop_front();
			}
			Create_type y= *t;
			while (y.data_type!=NULL)
			{
				y = *y.data_type;
			}
			(yyval.type) = t;
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 226 "language/bison.y"
    { (yyval.ranges).push_back((yyvsp[(2) - (3)].number)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 227 "language/bison.y"
    { (yyval.ranges).push_back((yyvsp[(3) - (4)].number)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 230 "language/bison.y"
    { 
			(yyval.instructions).clear();
			Node *n = program->actualRobot->add((yyvsp[(1) - (1)].ident));
			(yyval.instructions).push_back(new InstructionCreate(n)); 
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 236 "language/bison.y"
    { 
			(yyval.instructions).clear();
			Node *n = program->actualRobot->add((yyvsp[(1) - (3)].ident));
			(yyval.instructions).push_back(new InstructionCreate(n));
			(yyval.instructions).push_back(new InstructionLoadLocal(n));
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(3) - (3)].output).ins);
			Instruction * in = possible_conversion(program->actualRobot->active_type.top()->type,(yyvsp[(3) - (3)].output).output.back().type);
			if (in)
			{
				(yyval.instructions).push_back(in);
				(yyvsp[(3) - (3)].output).output.back() = *program->actualRobot->active_type.top();
			}
			(yyval.instructions).push_back(get_store_type((yylsp[(1) - (3)]), program->actualRobot, (yyvsp[(3) - (3)].output).output.back()));
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 251 "language/bison.y"
    { 
			(yyval.instructions).clear();
			Node *n = program->actualRobot->add((yyvsp[(1) - (5)].ident));
			(yyval.instructions).push_back(new InstructionCreate(n));
			(yyval.instructions).push_back(new InstructionLoadLocal(n));
			for (int i =1; i < (yyvsp[(4) - (5)].defVal).level; i++)
			{
				(yyval.instructions).push_back(new InstructionDuplicate());
			}
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(4) - (5)].defVal).ins);
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 263 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 264 "language/bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 266 "language/bison.y"
    { program->actualRobot->declare_next(); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 268 "language/bison.y"
    { program->actualRobot->leave_type(); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 270 "language/bison.y"
    { 
			(yyval.defVal).ins.clear();
			(yyval.defVal).ins.push_back(new InstructionLoad(0));
			(yyval.defVal).ins.push_back(new InstructionLoad());
			(yyval.defVal).ins = join_instructions((yyval.defVal).ins, (yyvsp[(1) - (1)].output).ins);
			Instruction * in = possible_conversion( program->actualRobot->active_type.top()->type,(yyvsp[(1) - (1)].output).output.back().type);
			if (in)
			{
				(yyval.defVal).ins.push_back(in);
				(yyvsp[(1) - (1)].output).output.back() = *program->actualRobot->active_type.top();
			}
			if ((yyvsp[(1) - (1)].output).output.back()!=*program->actualRobot->active_type.top())
			{
				std::cout <<"nnnnnn?"<<(yylsp[(1) - (1)]) << " " << program->actualRobot->active_type.top()->type; getc(stdin);
				program->actualRobot->error((yylsp[(1) - (1)]), Robot::ErrorConversionImpossible);
			}
			else
			{
				(yyval.defVal).ins.push_back(get_store_type((yylsp[(1) - (1)]), program->actualRobot, (yyvsp[(1) - (1)].output).output.back()));
				(yyval.defVal).level = 1;
			}
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 293 "language/bison.y"
    {
			(yyval.defVal).ins.clear();
			(yyval.defVal).ins = (yyvsp[(1) - (3)].defVal).ins;
			(yyval.defVal).ins.push_back(new InstructionLoad((yyvsp[(1) - (3)].defVal).level));
			(yyval.defVal).ins.push_back(new InstructionLoad());
			(yyval.defVal).ins = join_instructions((yyval.defVal).ins , (yyvsp[(3) - (3)].output).ins);
			Instruction * in = possible_conversion(program->actualRobot->active_type.top()->type,(yyvsp[(3) - (3)].output).output.back().type );
			if (in)
			{
				(yyval.defVal).ins.push_back(in);
				(yyvsp[(3) - (3)].output).output.back() = *program->actualRobot->active_type.top();
			}
			(yyval.defVal).ins.push_back(get_store_type((yylsp[(1) - (3)]), program->actualRobot, (yyvsp[(3) - (3)].output).output.back()));
			if ((yyvsp[(3) - (3)].output).temp.back())
			{
				(yyval.defVal).ins.push_back(new InstructionRemoveTemp());
			}	
			(yyval.defVal).level = (yyvsp[(1) - (3)].defVal).level + 1;
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 313 "language/bison.y"
    { 
			(yyval.defVal).ins.clear();	
			(yyval.defVal).ins.push_back(new InstructionLoad(0)); //todo do actual type pridat, ze sme o type dalej, array dalej atd
			(yyval.defVal).ins.push_back(new InstructionLoad());
			for (int i = 1; i < (yyvsp[(2) - (3)].defVal).level; i++)
			{
				(yyval.defVal).ins.push_back(new InstructionDuplicate());
			}
			(yyval.defVal).ins = join_instructions((yyval.defVal).ins, (yyvsp[(2) - (3)].defVal).ins);
			(yyval.defVal).level = 1;
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 325 "language/bison.y"
    {
			(yyval.defVal).ins.clear();
			(yyval.defVal) = (yyvsp[(1) - (5)].defVal); 
			(yyval.defVal).ins.push_back(new InstructionLoad((yyvsp[(1) - (5)].defVal).level));
			(yyval.defVal).ins.push_back(new InstructionLoad());
			for (int i = 1; i < (yyvsp[(4) - (5)].defVal).level; i++)
			{
				(yyval.defVal).ins.push_back(new InstructionDuplicate());
			}

			(yyval.defVal).ins = join_instructions((yyval.defVal).ins,(yyvsp[(4) - (5)].defVal).ins); 
			(yyval.defVal).level++;
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 340 "language/bison.y"
    { 
				std::vector<Parameter_entry> em;
				program->actualRobot->enter("main", em,program->actualRobot->find_type(TypeVoid)); 	
			;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 345 "language/bison.y"
    { 
			(yyval.output) = (yyvsp[(1) - (1)].output);std::vector<Parameter_entry> em;
			program->actualRobot->enter("main", em, program->actualRobot->find_type(TypeVoid));
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 352 "language/bison.y"
    {
			 (yyval.ident) = (yyvsp[(2) - (5)].ident);
			 program->actualRobot->enter((yyvsp[(2) - (5)].ident),(yyvsp[(4) - (5)].entries), (yyvsp[(1) - (5)].type)); 
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 358 "language/bison.y"
    {
			(yyval.ident) = (yyvsp[(2) - (2)].ident);
			program->actualRobot->nested += (yyvsp[(2) - (2)].ident) + DELIMINER_CHAR;
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 363 "language/bison.y"
    { (yyval.type) = program->actualRobot->find_type(TypeVoid);program->actualRobot->declare_type();;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 364 "language/bison.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 367 "language/bison.y"
    { (yyval.entries).clear(); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 368 "language/bison.y"
    { (yyval.entries) = (yyvsp[(1) - (1)].entries);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 370 "language/bison.y"
    { (yyval.entries).push_back(Parameter_entry((yyvsp[(2) - (2)].ident),PARAMETER_BY_VALUE, program->actualRobot->add((yyvsp[(2) - (2)].ident), (yyvsp[(1) - (2)].type)))); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 371 "language/bison.y"
    { (yyval.entries) = (yyvsp[(1) - (4)].entries); (yyval.entries).push_back(Parameter_entry((yyvsp[(4) - (4)].ident),PARAMETER_BY_VALUE,program->actualRobot->add((yyvsp[(4) - (4)].ident), (yyvsp[(3) - (4)].type)))); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 372 "language/bison.y"
    { (yyval.entries).push_back(Parameter_entry((yyvsp[(3) - (3)].ident),PARAMETER_BY_REFERENCE, program->actualRobot->add((yyvsp[(3) - (3)].ident), (yyvsp[(2) - (3)].type)))); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 374 "language/bison.y"
    { 
			(yyval.entries).push_back(Parameter_entry((yyvsp[(5) - (5)].ident),PARAMETER_BY_REFERENCE, program->actualRobot->add((yyvsp[(5) - (5)].ident), (yyvsp[(4) - (5)].type)))); 
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 379 "language/bison.y"
    { 
			program->actualRobot->add_function((yyvsp[(2) - (2)].instructions));
			program->actualRobot->leave();
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 384 "language/bison.y"
    { 
			program->actualRobot->add_function((yyvsp[(3) - (3)].instructions)); 
			program->actualRobot->leave();
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 390 "language/bison.y"
    { 
			if ((yyvsp[(1) - (2)].operation) == OperationMinus ) 
			{
				(yyvsp[(2) - (2)].f_number)*=-1;
			} 
			(yyval.output).ins.push_back(new InstructionLoad((yyvsp[(2) - (2)].f_number)));
			(yyval.output).output.push_back(*program->actualRobot->find_type(TypeReal)); 
			(yyval.output).temp.push_back(false);
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 400 "language/bison.y"
    { 
			if ((yyvsp[(1) - (2)].operation) == OperationMinus) 
			{
				(yyvsp[(2) - (2)].number)*=-1;
			} 
			(yyval.output).ins.push_back(new InstructionLoad((yyvsp[(2) - (2)].number))); 
			(yyval.output).output.push_back( *program->actualRobot->find_type(TypeInteger));
			(yyval.output).temp.push_back(false);
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 410 "language/bison.y"
    { 
			(yyval.output).ins.push_back(new InstructionLoad((yyvsp[(1) - (1)].f_number))); 
			(yyval.output).output.push_back(*program->actualRobot->find_type(TypeReal));
			(yyval.output).temp.push_back(false); 
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 416 "language/bison.y"
    { 
			(yyval.output).ins.push_back(new InstructionLoad((yyvsp[(1) - (1)].number))); 
			(yyval.output).output.push_back(*program->actualRobot->find_type(TypeInteger));
			(yyval.output).temp.push_back(false); 
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 423 "language/bison.y"
    { program->actualRobot->core->depth++; program->actualRobot->defined.new_block();;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 426 "language/bison.y"
    { program->actualRobot->core->depth--; program->actualRobot->defined.leave_block();;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 430 "language/bison.y"
    { 
			(yyval.instructions).push_back(new InstructionBegin()); 
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(2) - (3)].instructions));
			(yyval.instructions).push_back(new InstructionEndBlock()); 
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 436 "language/bison.y"
    {(yyval.instructions).clear();;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 437 "language/bison.y"
    {  (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 440 "language/bison.y"
    { (yyval.instructions).clear(); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 441 "language/bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 442 "language/bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 443 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 444 "language/bison.y"
    { (yyval.instructions) = join_instructions((yyvsp[(1) - (2)].instructions), (yyvsp[(2) - (2)].instructions)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 447 "language/bison.y"
    { program->actualRobot->core->depth++; (yyval.instructions).push_back(new InstructionBegin());program->actualRobot->defined.new_block();;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 450 "language/bison.y"
    { 
		//	INIT, BLOCK, COMMAND CONDITION
			if ((yyvsp[(4) - (10)].output).temp.back())
			{
				(yyvsp[(4) - (10)].output).ins.push_back(new InstructionRemoveTemp());
			}
			(yyvsp[(9) - (10)].instructions).push_back(new InstructionEndBlock((yyvsp[(4) - (10)].output).ins.size()+(yyvsp[(6) - (10)].instructions).size()+1));
			(yyvsp[(9) - (10)].instructions) = join_instructions((yyvsp[(9) - (10)].instructions), (yyvsp[(6) - (10)].instructions)); 
			(yyvsp[(3) - (10)].instructions).push_back(new InstructionMustJump((yyvsp[(9) - (10)].instructions).size()+1)); 
			(yyvsp[(3) - (10)].instructions).push_back(new InstructionBegin(program->actualRobot->core->depth));
			(yyvsp[(4) - (10)].output).ins.push_back(new InstructionJump(-1*(yyvsp[(9) - (10)].instructions).size()-(yyvsp[(4) - (10)].output).ins.size()-2,0));
			(yyvsp[(9) - (10)].instructions) = join_instructions((yyvsp[(9) - (10)].instructions),(yyvsp[(4) - (10)].output).ins);
			(yyval.instructions) = join_instructions((yyvsp[(3) - (10)].instructions),(yyvsp[(9) - (10)].instructions));
			(yyval.instructions).push_back(new InstructionEndBlock());
			(yyval.instructions) = join_instructions((yyvsp[(1) - (10)].instructions), (yyval.instructions));
			program->actualRobot->core->depth--;
			program->actualRobot->defined.leave_block();
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 469 "language/bison.y"
    { 
			if ((yyvsp[(7) - (9)].output).temp.back())
			{
				(yyvsp[(7) - (9)].output).ins.push_back(new InstructionRemoveTemp());
			}
			(yyval.instructions).push_back(new InstructionBegin(program->actualRobot->core->depth));
			(yyvsp[(3) - (9)].instructions).push_back(new InstructionEndBlock((yyvsp[(7) - (9)].output).ins.size()+1));
			(yyval.instructions) = join_instructions((yyval.instructions), (yyvsp[(3) - (9)].instructions));
			(yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(7) - (9)].output).ins); 
			(yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size()-1,0));
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 481 "language/bison.y"
    {
			if ((yyvsp[(3) - (7)].output).temp.back())
			{
				(yyvsp[(3) - (7)].output).ins.push_back(new InstructionRemoveTemp());
			}
			(yyval.instructions).push_back(new InstructionMustJump((yyvsp[(6) - (7)].instructions).size()+2));
			(yyval.instructions).push_back(new InstructionBegin(program->actualRobot->core->depth));
			(yyvsp[(6) - (7)].instructions).push_back(new InstructionEndBlock((yyvsp[(3) - (7)].output).ins.size()+1));
			(yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(6) - (7)].instructions));
			(yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(3) - (7)].output).ins);
			(yyval.instructions).push_back(new InstructionJump(-1*(yyval.instructions).size(),0));
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 494 "language/bison.y"
    {
			(yyval.instructions).push_back(new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));
			(yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(2) - (3)].output).ins);
			
			/* Check for types compatibility */
			if (((yyvsp[(2) - (3)].output).output.back().type == TypeInteger) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeReal))
			{
				if ((yyvsp[(2) - (3)].output).temp.back())
				{
					(yyval.instructions).push_back(new InstructionRemoveTemp());
				}
				(yyvsp[(2) - (3)].output).output.back() = *program->actualRobot->find_type(TypeReal);
				(yyval.instructions).push_back(new InstructionConversionToReal());
				(yyvsp[(2) - (3)].output).temp.back() = true;
			}
			else if (((yyvsp[(2) - (3)].output).output.back().type == TypeReal) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeInteger))
			{
				if ((yyvsp[(2) - (3)].output).temp.back())
				{
					(yyval.instructions).push_back(new InstructionRemoveTemp());
				}
				(yyvsp[(2) - (3)].output).output.back() = *program->actualRobot->find_type(TypeInteger);
				(yyval.instructions).push_back(new InstructionConversionToInt());
				(yyvsp[(2) - (3)].output).temp.back() = true;
			}

			/* Check for types equality */
			if ((yyvsp[(2) - (3)].output).output.back()!= *program->actualRobot->core->nested_function->return_var->type_of_variable)
			{
				program->actualRobot->error((yylsp[(1) - (3)]), Robot::ErrorConversionImpossible);
			}
			else
				(yyval.instructions).push_back(new InstructionStore());
			if ((yyvsp[(2) - (3)].output).temp.back())
			{
				(yyval.instructions).push_back(new InstructionRemoveTemp());
			}
			(yyval.instructions).push_back(new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));// da sa dat aj na konci, vestko  uz je upratane
			(yyval.instructions).push_back(new InstructionReturn(program->actualRobot->core->depth));	
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 535 "language/bison.y"
    {
			(yyval.instructions).push_back(new InstructionReturn(program->actualRobot->core->depth));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 540 "language/bison.y"
    {
			std::cout << "Adding break to in depth" <<program->actualRobot->core->depth << std::endl;
			(yyval.instructions).push_back(new InstructionBreak(program->actualRobot->core->depth));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 545 "language/bison.y"
    {
			(yyval.instructions).push_back(new InstructionContinue(program->actualRobot->core->depth));
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 548 "language/bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 550 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 551 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 553 "language/bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 555 "language/bison.y"
    { 
			(yyval.instructions) = (yyvsp[(1) - (1)].output).ins; 
			if((yyvsp[(1) - (1)].output).output.size()>0)
			{
				(yyval.instructions).push_back(new InstructionPop());
				if((yyvsp[(1) - (1)].output).temp.back())
					(yyval.instructions).push_back(new InstructionRemoveTemp());
			}
		;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 567 "language/bison.y"
    {
		if (((yyvsp[(1) - (3)].output).output.back().type == TypeInteger)&&((yyvsp[(3) - (3)].output).output.back().type == TypeReal))
		{
			if ((yyvsp[(3) - (3)].output).temp.back())
			{
				(yyval.instructions).push_back(new InstructionRemoveTemp());
			}
			(yyvsp[(3) - (3)].output).ins.push_back(new InstructionConversionToInt());
			(yyvsp[(3) - (3)].output).temp.back() = true;
		}
		else if	(((yyvsp[(1) - (3)].output).output.back().type == TypeReal)&&((yyvsp[(3) - (3)].output).output.back().type == TypeInteger))
		{
			if ((yyvsp[(3) - (3)].output).temp.back())
			{
				(yyval.instructions).push_back(new InstructionRemoveTemp());
			}
			(yyvsp[(3) - (3)].output).ins.push_back(new InstructionConversionToReal());
			(yyvsp[(3) - (3)].output).temp.back() = true;
		}
		else if ((yyvsp[(1) - (3)].output).output.back()!=(yyvsp[(3) - (3)].output).output.back())
		{
			std::cout << "grrr" ; getc(stdin);
			program->actualRobot->error((yylsp[(2) - (3)]), Robot::ErrorConversionImpossible);
		}
		(yyval.instructions) = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins); 
		switch ((yyvsp[(1) - (3)].output).output.back().type)
		{
			case TypeInteger:
				(yyval.instructions).push_back(new InstructionStoreInteger());
				break;
			case TypeReal:
				(yyval.instructions).push_back(new InstructionStoreReal());
				break;
			case TypeObject:
				(yyval.instructions).push_back(new InstructionStoreObject());
				break;
			case TypeArray:
				(yyval.instructions).push_back(new InstructionStore());
				break;
			case TypeLocation:
				(yyval.instructions).push_back(new InstructionDuplicate());
				(yyval.instructions).push_back(new InstructionLoad(0));
				(yyval.instructions).push_back(new InstructionStoreInteger());
				(yyval.instructions).push_back(new InstructionLoad(1));
				(yyval.instructions).push_back(new InstructionStoreInteger()); //TODO type array
				break;
			default: program->actualRobot->error((yylsp[(2) - (3)]), Robot::ErrorOperationNotSupported);
		}
		if ((yyvsp[(3) - (3)].output).temp.back())
			(yyval.instructions).push_back(new InstructionRemoveTemp());
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 620 "language/bison.y"
    {
			(yyval.output) = ident_load((yylsp[(1) - (2)]),program->actualRobot, (yyvsp[(1) - (2)].ident));
			(yyval.output).ins = join_instructions((yyval.output).ins, (yyvsp[(2) - (2)].array_access).ins);
			(yyval.output).temp.push_back(false);
			Create_type tt = (yyval.output).output.back();	
			for(int i =(yyvsp[(2) - (2)].array_access).dimension; i>0; i--) 
			{
				if ((yyval.output).output.back().data_type == NULL)
				{
					program->actualRobot->error((yylsp[(1) - (2)]),Robot::ErrorOutOfRange);
					break;
				}
				
				Create_type * t = (yyval.output).output.back().data_type;
				(yyval.output).output.back() = *t;
			}
		;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 638 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output).ins = (yyvsp[(3) - (4)].output).ins;
			(yyval.output).output.push_back(*program->actualRobot->find_type(TypeObject));
			Instruction * in = possible_conversion((yyvsp[(3) - (4)].output).output.back().type, TypeInteger);
			if (in!=NULL)
			{
				(yyval.output).ins.push_back(in);
			}
			(yyval.output).ins.push_back(new InstructionEye());
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 653 "language/bison.y"
    { 
			Function * f =program->actualRobot->find_f((yyvsp[(1) - (4)].ident)); 
			if (f == NULL)
			{
				program->actualRobot->error((yylsp[(1) - (4)]),Robot::ErrorFunctionNotDefined); 
				(yyval.output).clear();
				(yyval.output).output.push_back(*program->actualRobot->find_type(TypeUndefined));
				(yyval.output).temp.push_back(true);
			}
			else 
			{
				if (f->parameters.size()!=(yyvsp[(3) - (4)].output).output.size()) 
				{
					program->actualRobot->error((yylsp[(1) - (4)]),Robot::ErrorWrongNumberOfParameters);
				}
				else
				{
					size_t iter_out = 0;
					for (size_t i= 0; i< (yyvsp[(3) - (4)].output).ins.size(); i++)
					{
						if ((yyvsp[(3) - (4)].output).ins[i]!= NULL)
						{
							(yyval.output).ins.push_back((yyvsp[(3) - (4)].output).ins[i]);
							continue;
						}
						if (((yyvsp[(3) - (4)].output).output[iter_out].type == TypeReal)
								&&(f->parameters[iter_out].node->type_of_variable->type == TypeInteger))
						{
							if ((yyvsp[(3) - (4)].output).temp[iter_out])
							{
								(yyval.output).ins.push_back(new InstructionRemoveTemp());
							}
							(yyval.output).ins.push_back(new InstructionConversionToInt());
							(yyvsp[(3) - (4)].output).temp[iter_out] = true;
							(yyvsp[(3) - (4)].output).output[iter_out] = *program->actualRobot->find_type(TypeInteger);
						}
						if (((yyvsp[(3) - (4)].output).output[iter_out].type == TypeInteger)
								&&(f->parameters[iter_out].node->type_of_variable->type == TypeReal))
						{
							if ((yyvsp[(3) - (4)].output).temp[iter_out])
							{
								(yyval.output).ins.push_back(new InstructionRemoveTemp());
							}
							(yyvsp[(3) - (4)].output).temp[iter_out] = true;
							(yyval.output).ins.push_back(new InstructionConversionToReal());
							(yyvsp[(3) - (4)].output).output[iter_out] = *program->actualRobot->find_type(TypeReal);
						}
						if ((yyvsp[(3) - (4)].output).output[iter_out] != *f->parameters[iter_out].node->type_of_variable)
						{
							program->actualRobot->error((yylsp[(1) - (4)]), Robot::ErrorConversionImpossible);
							break;
						}
						iter_out++;	
					}
					(yyval.output).ins.push_back(new Call(f));
					if (f->return_var->type_of_variable->type == TypeVoid)
						(yyval.output).output.clear();
					else
						(yyval.output).output.push_back(*f->return_var->type_of_variable);
				}
				for (size_t i =0; i< (yyvsp[(3) - (4)].output).temp.size(); i++)
				{
					if ((yyvsp[(3) - (4)].output).temp[i])
						(yyval.output).ins.push_back(new InstructionRemoveTemp()); //likvidovnie premennyh obsadenych v pamati

				}
				if (f->return_var->type_of_variable->type!= TypeVoid)
					(yyval.output).temp.push_back(true);
				else 
					(yyval.output).temp.push_back(false);
			}
		;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 726 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output) = feature((yylsp[(1) - (4)]),program->actualRobot, (yyvsp[(1) - (4)].of), (yyvsp[(3) - (4)].output));
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 734 "language/bison.y"
    {
			(yyval.output) = (yyvsp[(1) - (1)].output); 
			(yyval.output).ins.push_back(NULL);
		;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 738 "language/bison.y"
    { (yyval.output).clear(); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 740 "language/bison.y"
    {
			(yyval.output).clear();
			(yyvsp[(3) - (3)].output).ins.push_back(NULL); //zalozka, po kolkatich instrukciach mi konci output, TODO zmenit
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins,(yyvsp[(3) - (3)].output).ins);
			(yyval.output).output = (yyvsp[(1) - (3)].output).output;
			for (size_t i =0; i< (yyvsp[(3) - (3)].output).output.size();i++) 
			{
				(yyval.output).output.push_back((yyvsp[(3) - (3)].output).output[i]);
				(yyval.output).temp.push_back((yyvsp[(3) - (3)].output).temp[i]);
			}
		;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 753 "language/bison.y"
    {
		(yyval.instructions).clear();
		if ((yyvsp[(3) - (7)].output).temp.back())
			{
				(yyvsp[(3) - (7)].output).ins.push_back(new InstructionRemoveTemp());
			}
		(yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size()));
		(yyvsp[(3) - (7)].output).ins.push_back(new InstructionJump(0,(yyvsp[(5) - (7)].instructions).size()));
		(yyval.instructions) =join_instructions((yyvsp[(3) - (7)].output).ins,(yyvsp[(5) - (7)].instructions));
		(yyval.instructions) =join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 764 "language/bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 765 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 768 "language/bison.y"
    {
			if ((yyvsp[(3) - (5)].output).temp.back())
			{
				(yyvsp[(3) - (5)].output).ins.push_back(new InstructionRemoveTemp());
			}
			(yyvsp[(3) - (5)].output).ins.push_back(new InstructionJump(0,(yyvsp[(5) - (5)].instructions).size()));
			(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].output).ins,(yyvsp[(5) - (5)].instructions));
		;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 777 "language/bison.y"
    {
		if ((yyvsp[(3) - (5)].output).temp.back())
			{
				(yyvsp[(3) - (5)].output).ins.push_back(new InstructionRemoveTemp());
			}
		(yyvsp[(3) - (5)].output).ins.push_back(new InstructionJump(0,(yyvsp[(5) - (5)].instructions).size()));
		(yyval.instructions) = join_instructions((yyvsp[(3) - (5)].output).ins,(yyvsp[(5) - (5)].instructions));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 786 "language/bison.y"
    {
		if ((yyvsp[(3) - (7)].output).temp.back())
			{
				(yyvsp[(3) - (7)].output).ins.push_back(new InstructionRemoveTemp());
			}
		(yyvsp[(5) - (7)].instructions).push_back(new InstructionMustJump((yyvsp[(7) - (7)].instructions).size())); //outputy sa tymto znicia
		(yyvsp[(3) - (7)].output).ins.push_back(new InstructionJump(0,(yyvsp[(5) - (7)].instructions).size()));
		(yyval.instructions) = join_instructions((yyvsp[(3) - (7)].output).ins,(yyvsp[(5) - (7)].instructions));
		(yyval.instructions) = join_instructions((yyval.instructions),(yyvsp[(7) - (7)].instructions));
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 797 "language/bison.y"
    { (yyval.instructions) = (yyvsp[(1) - (1)].instructions);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 798 "language/bison.y"
    {(yyval.instructions) = (yyvsp[(1) - (2)].instructions);;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 800 "language/bison.y"
    {(yyval.output) = (yyvsp[(1) - (1)].output);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 802 "language/bison.y"
    {
			(yyval.output) = (yyvsp[(1) - (2)].output); 
			if((yyval.output).output.back() == TypeReal) 
				(yyval.output).ins.push_back(new InstructionPlusPlusReal());
			else if ((yyval.output).output.back() == TypeInteger) 
				(yyval.output).ins.push_back(new InstructionPlusPlusInteger());
			else program->actualRobot->error((yylsp[(2) - (2)]),Robot::ErrorOperationNotSupported);
			(yyval.output).temp.push_back((yyvsp[(1) - (2)].output).temp.back());
		;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 812 "language/bison.y"
    {
			 (yyval.output) = (yyvsp[(1) - (2)].output); 
			 if((yyval.output).output.back() == TypeReal)
				 (yyval.output).ins.push_back(new InstructionMinusMinusReal());
			else if ((yyval.output).output.back() == TypeInteger) 
				(yyval.output).ins.push_back(new InstructionMinusMinusInteger());
			else program->actualRobot->error((yylsp[(2) - (2)]),Robot::ErrorOperationNotSupported);
			(yyval.output).temp.push_back((yyvsp[(1) - (2)].output).temp.back());
		;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 823 "language/bison.y"
    {
			(yyval.output) = ident_load((yylsp[(1) - (1)]),program->actualRobot, (yyvsp[(1) - (1)].ident));
			(yyval.output).temp.push_back(false);
		;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 827 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output); //TODO ak je to funkci a s navratovou hodnotou, kontrola vsetkych vetvi, ci obsahuju return; main je procedura:)
		;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 830 "language/bison.y"
    { 
			
			for ( size_t i =0; i<(yyval.output).output.back().nested_vars.size(); i++)
				if ((yyval.output).output.back().nested_vars[i].name == (yyvsp[(3) - (3)].ident))
				{ 
					Create_type t = *(yyval.output).output.back().nested_vars[i].type; 
					(yyval.output).output.pop_back();
					(yyval.output).output.push_back(t);
					(yyval.output).ins.push_back(new InstructionLoad((int)i));
					(yyval.output).ins.push_back(new InstructionLoad());
					break;
				}
			(yyval.output).temp.push_back((yyvsp[(1) - (3)].output).temp.back());
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 848 "language/bison.y"
    { 
			(yyval.array_access).dimension = 0;
			(yyval.array_access).ins.clear(); //exps musia by integery
			for (size_t i =0; i< (yyvsp[(2) - (3)].output).ins.size(); i++)
			{
				if ((yyvsp[(2) - (3)].output).ins[i] == NULL)
				{
					(yyval.array_access).ins.push_back(new InstructionLoad());
					if ((yyvsp[(2) - (3)].output).temp[i])
						(yyval.array_access).ins.push_back(new InstructionRemoveTemp());
					(yyval.array_access).dimension++;
				}
				else
					(yyval.array_access).ins.push_back((yyvsp[(2) - (3)].output).ins[i]);
			}

		;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 866 "language/bison.y"
    {
			(yyval.array_access) = (yyvsp[(1) - (4)].array_access);
			for ( size_t i = 0; i < (yyvsp[(3) - (4)].output).ins.size();i++)
			{
				if ((yyvsp[(3) - (4)].output).ins[i] == NULL)
				{
					(yyval.array_access).ins.push_back(new InstructionLoad());
					if ((yyvsp[(3) - (4)].output).temp[i])
						(yyval.array_access).ins.push_back(new InstructionRemoveTemp());
					(yyval.array_access).dimension++;
				}
				else
					(yyval.array_access).ins.push_back((yyvsp[(3) - (4)].output).ins[i]);
			}
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 882 "language/bison.y"
    {(yyval.output) = (yyvsp[(1) - (1)].output);(yyval.output).ins.push_back(NULL);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 884 "language/bison.y"
    { 
			(yyvsp[(1) - (3)].output).ins.push_back(NULL);
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins);
			(yyval.output).output = (yyvsp[(1) - (3)].output).output;
			for (size_t i =0; i<(yyvsp[(1) - (3)].output).output.size(); i++)
				(yyval.output).output.push_back((yyvsp[(1) - (3)].output).output[i]); //aj tak tu bude len jeden output, TODO
		;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 892 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 893 "language/bison.y"
    {(yyval.output) = (yyvsp[(1) - (1)].output);;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 894 "language/bison.y"
    {(yyval.output) = (yyvsp[(2) - (3)].output);;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 896 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 897 "language/bison.y"
    { 
			(yyval.output).clear();
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins);
			if ((yyvsp[(1) - (3)].output).temp.back())
			{
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			}
			if ((yyvsp[(3) - (3)].output).temp.back())
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			Element e = operMul((yylsp[(2) - (3)]), program->actualRobot, (yyvsp[(2) - (3)].operation), (yyvsp[(1) - (3)].output).output.back(), (yyvsp[(3) - (3)].output).output.back());
			(yyval.output).ins = join_instructions((yyval.output).ins, e.ins);
			(yyval.output).output = e.output;
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 912 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output);;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 914 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins);
			if ((yyvsp[(1) - (3)].output).temp.back())
			{
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			}
			if ((yyvsp[(3) - (3)].output).temp.back())
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			Element e = (operAdd((yylsp[(2) - (3)]), program->actualRobot,(yyvsp[(2) - (3)].operation),(yyvsp[(1) - (3)].output).output.back(), (yyvsp[(3) - (3)].output).output.back()));
			(yyval.output).ins = join_instructions((yyval.output).ins, e.ins);
			(yyval.output).output = e.output;
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 929 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 931 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output);;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 933 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins);
			if ((yyvsp[(1) - (3)].output).temp.back())
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			if ((yyvsp[(3) - (3)].output).temp.back())
				(yyval.output).ins.push_back(new InstructionRemoveTemp());
			Element e = operRel((yylsp[(2) - (3)]),program->actualRobot,(yyvsp[(2) - (3)].operation),(yyvsp[(3) - (3)].output).output.back(),(yyvsp[(1) - (3)].output).output.back());
			(yyval.output).ins = join_instructions((yyval.output).ins, e.ins);
			(yyval.output).output = e.output;
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 946 "language/bison.y"
    {(yyval.output) = (yyvsp[(1) - (1)].output); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 948 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins);
			Element e = operOr((yylsp[(2) - (3)]),program->actualRobot,(yyvsp[(2) - (3)].operation),(yyvsp[(1) - (3)].output).output.back(),(yyvsp[(3) - (3)].output).output.back());
			(yyval.output).output = e.output; //aj tak by tu vzy mal byt integer
			(yyval.output).temp.push_back(true);
		;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 956 "language/bison.y"
    { (yyval.output) = (yyvsp[(1) - (1)].output);;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 958 "language/bison.y"
    {
			(yyval.output).clear();
			(yyval.output).ins = join_instructions((yyvsp[(1) - (3)].output).ins, (yyvsp[(3) - (3)].output).ins); 
			if ((yyvsp[(1) - (3)].output).output.back().type == TypeReal) 
			{
				if ((yyvsp[(1) - (3)].output).temp.back())
				{
					(yyval.output).ins.push_back(new InstructionRemoveTemp());
				}
				(yyval.output).ins.push_back(new InstructionConversionToInt());
				(yyval.output).output.push_back(Create_type(TypeInteger));
			}
			else if ((yyvsp[(1) - (3)].output).output.back().type!= TypeInteger) 
				program->actualRobot->error((yylsp[(2) - (3)]),Robot::ErrorConversionImpossible); 

			if ((yyvsp[(3) - (3)].output).output.back().type == TypeReal) 
			{
				if ((yyvsp[(3) - (3)].output).temp.back())
				{
					(yyval.output).ins.push_back(new InstructionRemoveTemp());
				}
				(yyval.output).ins.push_back(new InstructionConversionToInt());
				(yyval.output).output.push_back(Create_type(TypeInteger));
			}
			else if ((yyvsp[(3) - (3)].output).output.back().type!= TypeInteger) 
				program->actualRobot->error((yylsp[(2) - (3)]),Robot::ErrorConversionImpossible); 
			(yyval.output).ins.push_back(new InstructionAnd);
			(yyval.output).temp.push_back(true);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 3098 "language/cpp/bison.cpp"
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
		      yytoken, &yylval, &yylloc, program);
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

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, program, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 988 "language/bison.y"


static void yyerror(unsigned *line, Robots* ctx, const char *message)
{
	printf("Syntax Error %s, line %d\n", message, *line);
}


