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
	l.add(o3);
	l.add(o4);
	l.add(o5);
	std::cout<<std::endl;
	for (size_t i = 0; i< l.size(); i++)
	{
		std::cout << i << "_" <<l.data->value << "\t";
		l.next();
	}
	l.clear();
	std::cout<<std::endl;
	for (size_t i = 0; i< 6; i++)
	{
		std::cout << i << "_" <<l.data->value << "\t";
		l.next();
	}
	std::cout << std::endl;
	l.add(o1);
	l.add(o2);
	l.add(o3);
	l.add(o4);
	l.add(o5);
	l.moveHead(l2);
	l.moveHead(l2);
	l.moveHead(l2);
	for (size_t i = 0; i< 6; i++)
	{
		std::cout << i << ":" <<l.data->value << std::endl;
		l.next();
	}
	for (size_t i = 0; i< 6; i++)
	{
		std::cout << i << ":" <<l2.data->value << std::endl;
		l2.next();
	}
	return 0;
}
