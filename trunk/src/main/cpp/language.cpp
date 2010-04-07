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
		q.actualRobot->output(&q.actualRobot->defined);
		/*for (int i =0; i<q.actualRobot->instructions.size(); i++)
		TEST( q.actualRobot->instructions[i]->name_)
		q.actualRobot->save_to_xml();
		q.actualRobot->execute();
	 */
	TEST("Zacinam na:"<<q.actualRobot->core->PC)
	if ((err) || (q.actualRobot->errors))
		TEST ( q.actualRobot->errorList )
	else
	{
		q.actualRobot->save_to_xml();
		q.actualRobot->execute();
	}
	fclose(yyin);	
	my_destroy();
	return 0;	
}
