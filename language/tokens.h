/* 
 * Inspired by principes of compilators
 * by J. Yaghob 
 */


#ifndef TOKENS_H
#define TOKENS_H

/* group elements */
#define TOKENGE_OPER_REL	10
#define TOKEN_LT		(TOKENGE_OPER_REL+1)	/* < */
#define TOKEN_LE		(TOKENGE_OPER_REL+2)	/* <= */
#define TOKEN_NE		(TOKENGE_OPER_REL+3)	/* != */
#define TOKEN_GE		(TOKENGE_OPER_REL+4)	/* >= */
#define TOKEN_GT		(TOKENGE_OPER_REL+5)	/* > */

#define TOKENGE_OPER_SIGNADD	20
#define TOKENGE_PLUS		(TOKENGE_OPER_SIGNADD+1)/* + */
#define TOKENGE_MINUS		(TOKENGE_OPER_SIGNADD+2)/* - */

#define TOKENGE_OPER_MUL	30
#define TOKENGE_ASTERISK	(TOKENGE_OPER_MUL+1)	/* * */
#define TOKENGE_SOLIDUS		(TOKENGE_OPER_MUL+2)	/* / */
#define TOKENGE_DIV		(TOKENGE_OPER_MUL+3)	/* div */
#define TOKENGE_MOD		(TOKENGE_OPER_MUL+4)	/* mod */
#define TOKENGE_AND		(TOKENGE_OPER_MUL+5)	/* and */

/* keywords */
#define TOKEN_KEYWORD		100
#define TOKEN_POINT		(TOKEN_KEYWORD+1)	/* point */
#define TOKEN_VAR		(TOKEN_KEYWORD+2)	/* var */
#define TOKEN_FUNCTION		(TOKEN_KEYWORD+3)	/* function */
#define TOKEN_ARRAY		(TOKEN_KEYWORD+4)	/* array */
#define TOKEN_IF		(TOKEN_KEYWORD+5)	/* if */
#define TOKEN_ELSE		(TOKEN_KEYWORD+6)	/* else */
#define TOKEN_WHILE		(TOKEN_KEYWORD+7)	/* while */
#define TOKEN_DO		(TOKEN_KEYWORD+8)	/* do */
#define TOKEN_REPEAT		(TOKEN_KEYWORD+9)	/* repeat */
#define TOKEN_UNTIL		(TOKEN_KEYWORD+10)	/* until */
#define TOKEN_FOR		(TOKEN_KEYWORD+11)	/* for */
#define TOKEN_OR		(TOKEN_KEYWORD+12)	/* or */
#define TOKEN_NOT		(TOKEN_KEYWORD+13)	/* not */
#define TOKEN_RETURN		(TOKEN_KEYWORD+14)	/* return */
#define TOKEN_BREAK		(TOKEN_KEYWORD+15)	/* break */

/* object features 
#define TOKEN_OBJECT		250
#define TOKEN_ISPLAYER		(TOKEN_OBJECT+1)
#define TOKEN_ISMOVING		(TOKEN_OBJECT+2)
#define TOKEN_ISWALL		(TOKEN_OBJECT+3)
#define TOKEN_ISHIT		(TOKEN_OBJECT+4)
#define TOKEN_LOCATION		(TOKEN_OBJECT+5)
#define TOKEN_DISTANCE		(TOKEN_OBJECT+6)
#define TOKEN_X			(TOKEN_OBJECT+7)
#define TOKEN_Y			(TOKEN_OBJECT+8)
#define TOKEN_GETID		(TOKEN_OBJECT+9)*/


/* literals */
#define TOKEN_LITERAL		300
#define TOKEN_IDENTIFIER	(TOKEN_LITERAL+1)	/* identifier */
#define TOKEN_UINT		(TOKEN_LITERAL+2)	/* unsigned integer */
#define TOKEN_REAL		(TOKEN_LITERAL+3)	/* real number */

/* delimiters */
#define TOKEN_DELIMITER		500
#define TOKEN_SEMICOLON		(TOKEN_DELIMITER+1)	/* ; */
#define TOKEN_DOT		(TOKEN_DELIMITER+2)	/* . */
#define TOKEN_COMMA		(TOKEN_DELIMITER+3)	/* , */
#define TOKEN_EQ		(TOKEN_DELIMITER+4)	/* == */
#define TOKEN_COLON		(TOKEN_DELIMITER+5)	/* : */
#define TOKEN_LPAR		(TOKEN_DELIMITER+6)	/* ( */
#define TOKEN_RPAR		(TOKEN_DELIMITER+7)	/* ) */
#define TOKEN_LSBRA		(TOKEN_DELIMITER+9)	/* [ */
#define TOKEN_RSBRA		(TOKEN_DELIMITER+10)	/* ] */
#define TOKEN_ASSIGN		(TOKEN_DELIMITER+11)	/* = */
#define TOKEN_BEGIN		(TOKEN_DELIMITER+12)	/* { */
#define TOKEN_END		(TOKEN_DELIMITER+13)	/* } */

/* group tokens */
#define TOKEN_GROUP_TOKEN	700
#define TOKEN_OPER_REL		(TOKEN_GROUP_TOKEN+1)	/* < > <= >= <> */
#define TOKEN_OPER_SIGNADD	(TOKEN_GROUP_TOKEN+2)	/* + - */
#define TOKEN_OPER_MUL		(TOKEN_GROUP_TOKEN+3)	/* * / div mod and */
#define TOKEN_BOT_ACTION	(TOKEN_GROUP_TOKEN+4)	//* bot features */ MOVE,RUN,SHOOT,WAIT,WALK,SEE

#endif
