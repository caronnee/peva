#define _NO_IMAGES_
#include <iostream>
#include "../../language/h/robot.h"
#include "../../language/h/bison.h"
#include "../../add-ons/h/macros.h"

extern FILE * yyin; //TODO zmenit na spravne nacitanie z editora
extern void my_destroy();
extern int yyparse(Robots *);

//TUTO NEISIM SKINY! A staci mi len jeden vstup, ten, ktory budem 'testovat'

int main(int argc, char ** argv)
{
	if(argc<2)
	{
		puts("Input nor found\n");
		return 16;
	}
	if((yyin=fopen(argv[1], "r"))==0)
	{
		puts("Unable to open input\n");
		return 16;
	}
	Robots q;
	int err = yyparse(&q);
	TEST("-------------------------------------END---------------------------------------------------------------")
		/*for (int i =0; i<q.robots.back()->instructions.size(); i++)
		TEST( q.robots.back()->instructions[i]->name_)
		q.robots.back()->save_to_xml();
		q.robots.back()->execute();
	 */
	if ((err) || (q.robots.back()->errors))
	{
		for (size_t i =0; i< q.robots.size(); i++)
			TEST ( q.robots.back()->errorList )
		TEST( std::endl)
		TEST ( q.parseErrorsList )
	}
	else
	{
//		q.robots.back()->output(&q.robots.back()->defined);
		q.finalize(0);
		q.robots.back()->save_to_xml();
		q.robots.back()->execute();
	}
	TEST("Program ended its execution")
	fclose(yyin);	
	my_destroy();
	return 0;	
}
