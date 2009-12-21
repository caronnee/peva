#include <iostream>
#include "../../objects/h/list.h"

int main()
{
	Object * o1 = new Object();
	std::cout << o1 << "\t";
	Object * o2 = new Object();
	std::cout << o2 << "\t";
	Object * o3 = new Object();
	std::cout << o3 << "\t";
	Object * o4 = new Object();
	std::cout << o4 << "\t";
	Object * o5 = new Object();
	std::cout << o5 << "\t";
	List l;
	List l2;
	l.add(o1);
	l.add(o2);
	std::cout<<std::endl;
	for (size_t i = 0; i< 10; i++)
	{
		std::cout << l.items->data << "\t";
		l.next();
	}
	std::cout<<std::endl;
	return 0;
}
