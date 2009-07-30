/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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


