#include <iostream>
#include "../h/robot.h"
#include "../h/bison.h"

extern FILE * yyin; //TODO zmenit na spravne nacitanie z editora
extern void my_destroy();
extern int yyparse(Robots *);
//TUTO NEISIM SKINY!
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
	GamePoints points;
	Robots q(points);
	int err = yyparse(&q);
	std::cout << "-------------------------------------END---------------------------------------------------------------" << std::endl;
		q.actualRobot->output(&q.actualRobot->defined);
		getc(stdin);
		/*for (int i =0; i<q.actualRobot->instructions.size(); i++)
		std::cout << q.actualRobot->instructions[i]->name_<<std::endl;
		q.actualRobot->save_to_xml();
		std::cout << "haho!" << std::endl;
		q.actualRobot->execute();
	 */
	std::cout << "Zacinam na:"<<q.actualRobot->core->PC <<std::endl;
	if ((err) || (q.actualRobot->errors))
		std::cout << q.actualRobot->errorList << std::endl;
	else
	{
		q.actualRobot->save_to_xml();
		q.actualRobot->execute();
	}
	fclose(yyin);	
	my_destroy();
	return 0;	
}
