#include "seer.h"

int main()
{
	Position res(4,6);
	Seer s(res);
	s.set_masks();
	s.output();
	Position p(15,15);
	Position pos(7,7);
	Map m(p);
	m.map[7][10] = new SolidWall();
	m.map[7][11] = new TrapWall();
	s.see(Seer::UP,&m,pos);
	std::cout << s.objects.size() << std::endl; 
	for (int i =0; i< s.objects.size(); i++)
	{
		std::cout << s.objects[i]->name << std::endl;
	}
	return 0;
}
