#include <iostream>
#include "../../add-ons/h/macros.h"
#include "../../objects/h/list.h"
#include "../../objects/h/list.h"
#include "../../objects/h/wall.h"

int main()
{
	Wall * o1 = new Wall(NULL);
	TEST(o1 << "\t")
	Wall * o2 = new Wall(NULL);
	TEST(o2 << "\t")
	Wall * o3 = new Wall(NULL);
	TEST(o3 << "\t")
	Wall * o4 = new Wall(NULL);
	TEST(o4 << "\t")
	Wall * o5 = new Wall(NULL);
	TEST(o5 << "\t")
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
		TEST(i << "_" <<l.data->value << "\t")
		l.next();
	}
	l.clear();
	std::cout<<std::endl;
	for (size_t i = 0; i< 6; i++)
	{
		TEST(i << "_" <<l.data->value << "\t")
		l.next();
	}
	TEST(std::endl)
	l.add(o1);
	l.add(o2);
//	l.add(o3);
//	l.add(o4);
//	l.add(o5);
	std::cout <<"MOVING 1!:"<<l.size() << ":" << l2.size() ;
	l.moveHead(l);
//	l.moveHead(l2);
//	l.moveHead(l2);
	std::cout <<"MOVING 2!:"<<l.size() << ":" << l2.size() ;
	l.reset();
	l2.reset();
	for (size_t i = 0; i< 6; i++)
	{
		TEST(i << ":" <<l.data->value )
		TEST(i << "::" <<l2.data->value )
		l.next();
		l2.next();
	}
	return 0;
}
