#ifndef __OBJECT_____
#define __OBJECT_____

#include <iostream>

struct Object;
struct Robot_body
{
	int step(){
		std::cout << "moving!" << std::endl;
		return 0;
	}
	int shoot()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
	int see()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
	int wait()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
};

#endif
