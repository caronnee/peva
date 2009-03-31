#ifndef HEADER_H_
#define HEADER_H_

#include <string>

struct Lval {
	int number;
	std::string idents; //+mozno este nejake sa njdu
	float f_number;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l)
YY_DECL;

// parser interface
int yyparse();

#endif
