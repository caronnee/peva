#ifndef __OBJECT_____
#define __OBJECT_____

#include <iostream>

class Object
{
	public:
	int IsMoving(){
		return 0;
	}
	int IsWall()
	{
		return 0;
	}
	int IsPlayer()
	{
		return 0;
	}
	int IsMissille()
	{
		return 0;
	}
	int Locate()
	{
		return 0;
	}
	int Hit()
	{
		return 0;
	}

};
struct Robot_body : public Object
{
	int Step(){
		std::cout << "moving!" << std::endl;
		return 0;
	}
	int Shoot()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
	int See()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
	int Wait()
	{
		std::cout <<"shooting" <<std::endl;
		return 0;
	}
	int Turn(int var)
	{
		std::cout << "otacam sa v smere:" << var <<std::endl;
		return 0;
	}
	int TurnL()
	{
		std::cout << "otacam sa v dolava " <<std::endl;
		return 0;
	}
	int TurnR()
	{
		std::cout << "otacam sa doprava " <<std::endl;
		return 0;
	}
};

#endif
