#include <string>
#include "../../add-ons/h/help_functions.h"
#include "../../editor/h/snake.h"

int main(int args, char ** argv)
{
	Position p(100,100);
	std::string filename = "output";
	if (args > 1)
		filename = deconvert<char *>(argv[1]);
	if (args >2)
		p.x = convert <int>(argv[2]);
	if (args >3)
		p.y = convert <int>(argv[3]);
	Snakes snakes(p);
	snakes.create();
	snakes.saveToFile(filename);

	return 0;
}
