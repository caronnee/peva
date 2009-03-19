/* 
 * Inspired by principes of compilators
 * by J. Yaghob 
 */


#ifndef TOKENS_H
#define TOKENS_H

/* group elements */
#define TOKENGE_OPER_REL	10
#define TOKEN_LT		(DUTOKGE_OPER_REL+1)	    /* < */
#define TOKEN_LE		(DUTOKGE_OPER_REL+2)	    /* <= */
#define TOKEN_NE		(DUTOKGE_OPER_REL+3)	    /* != */
#define TOKEN_GE		(DUTOKGE_OPER_REL+4)	    /* >= */
#define TOKEN_GT		(DUTOKGE_OPER_REL+5)	    /* > */

#define TOKENGE_OPER_SIGNADD	20
#define TOKENGE_PLUS		(DUTOKGE_OPER_SIGNADD+1)    /* + */
#define TOKENGE_MINUS		(DUTOKGE_OPER_SIGNADD+2)    /* - */

#define TOKENGE_OPER_MUL	30
#define TOKENGE_ASTERISK	(DUTOKGE_OPER_MUL+1)	    /* * */
#define TOKENGE_SOLIDUS		(DUTOKGE_OPER_MUL+2)	    /* / */
#define TOKENGE_DIV		(DUTOKGE_OPER_MUL+3)	    /* div */
#define TOKENGE_MOD		(DUTOKGE_OPER_MUL+4)	    /* mod */
#define TOKENGE_AND		(DUTOKGE_OPER_MUL+5)	    /* and */

/* keywords */
#define TOKEN_KEYWORD		100
#define TOKEN_POINT					    /* point */
#define TOKEN_VAR		(DUTOK_KEYWORD+5)	    /* var */
#define TOKEN_FUNCTION		(DUTOK_KEYWORD+9)	    /* function */
#define TOKEN_ARRAY		(DUTOK_KEYWORD+10)	    /* array */
#define TOKEN_IF		(DUTOK_KEYWORD+13)	    /* if */
#define TOKEN_ELSE		(DUTOK_KEYWORD+15)	    /* else */
#define TOKEN_WHILE		(DUTOK_KEYWORD+16)	    /* while */
#define TOKEN_DO		(DUTOK_KEYWORD+17)	    /* do */
#define TOKEN_REPEAT		(DUTOK_KEYWORD+18)	    /* repeat */
#define TOKEN_UNTIL		(DUTOK_KEYWORD+19)	    /* until */
#define TOKEN_FOR		(DUTOK_KEYWORD+20)	    /* for */
#define TOKEN_OR		(DUTOK_KEYWORD+21)	    /* or */
#define TOKEN_NOT		(DUTOK_KEYWORD+22)	    /* not */

/* bot features */
#define TOKEN_BOT		200
#define TOKEN_MOVE		(TOKEN_BOT+1)
#define TOKEN_RUN   		(TOKEN_NOT+2)
#define TOKEN_SHOOT             (TOKEN_BOT+3)
#define TOKEN_WAIT              (TOKEN_BOT+4)
#define TOKEN_WALK              (TOKEN_BOT+5)
#define TOKEN_SEE               (TOKEN_BOT+6)

/* object features */
#define TOKEN_OBJECT		250
#define TOKEN_ISPLAYER		(TOKEN_OBJECT+1)
#define TOKEN_ISMOVING		(TOKEN_OBJECT+2)
#define TOKEN_ISWALL		(TOKEN_OBJECT+3)
#define TOKEN_ISHIT		(TOKEN_OBJECT+4)
#define TOKEN_LOCATION		(TOKEN_OBJECT+5)
#define TOKEN_DISTANCE		(TOKEN_OBJECT+6)
#define TOKEN_X			(TOKEN_OBJECT+7)
#define TOKEN_Y			(TOKEN_OBJECT+8)


/* literals */
#define TOKEN_LITERAL		300
#define TOKEN_IDENTIFIER	(DUTOK_LITERAL+1)	    /* identifier */
#define TOKEN_UINT		(DUTOK_LITERAL+2)	    /* unsigned integer */
#define TOKEN_REAL		(DUTOK_LITERAL+3)	    /* real number */
#define TOKEN_STRING		(DUTOK_LITERAL+4)	    /* string */

/* delimiters */
#define TOKEN_DELIMITER		500
#define TOKEN_SEMICOLON		(DUTOK_DELIMITER+1)	    /* ; */
#define TOKEN_DOT		(DUTOK_DELIMITER+2)	    /* . */
#define TOKEN_COMMA		(DUTOK_DELIMITER+3)	    /* , */
#define TOKEN_EQ		(DUTOK_DELIMITER+4)	    /* == */
#define TOKEN_COLON		(DUTOK_DELIMITER+5)	    /* : */
#define TOKEN_LPAR		(DUTOK_DELIMITER+6)	    /* ( */
#define TOKEN_RPAR		(DUTOK_DELIMITER+7)	    /* ) */
#define TOKEN_LSBRA		(DUTOK_DELIMITER+9)	    /* [ */
#define TOKEN_RSBRA		(DUTOK_DELIMITER+10)	    /* ] */
#define TOKEN_ASSIGN		(DUTOK_DELIMITER+11)	    /* = */

/* group tokens */
#define TOKEN_GROUP_TOKEN	700
#define TOKEN_OPER_REL		(DUTOK_GROUP_TOKEN+1)	    /* < > <= >= <> */
#define TOKEN_OPER_SIGNADD	(DUTOK_GROUP_TOKEN+2)	    /* + - */
#define TOKEN_OPER_MUL		(DUTOK_GROUP_TOKEN+3)	    /* * / div mod and */

#endif
