#ifndef __OBJECT_____
#define __OBJECT_____

#include <iostream>
#include "position.h"

class Object
{
	public:
	int IsMoving(){
		std::cout << "Object is not moving." << std::endl;
		return 0;
	}
	int IsWall()
	{
		std::cout << "Object is not a Wall." << std::endl;
		return 0;
	}
	int IsPlayer()
	{
		std::cout << "Object is not a Player." << std::endl;
		return 0;
	}
	int IsMissille()
	{
		std::cout << "Object is not a Missille." << std::endl;
		return 0;
	}
	Position Locate()
	{
		Position p(107,107);
		return p;
	}
	int Hit()
	{
		std::cout << "Object was not hit." << std::endl;
		return 0;
	}
};
struct Robot_body : public Object
{
	int Step(int i){
		std::cout << "moving "<< i << "positions" << std::endl;
		return 0;
	}
	int Shoot(int x,int y=1987)
	{
		std::cout <<"shooting at speed-dir [" << x << " ,"<< y  << "]." <<std::endl;
		return 0;
	}
	int See()
	{
		std::cout << "Checking visibility" <<std::endl;
		return 0;
	}
	int Wait(int i)
	{
		std::cout << "Waiting " << i << "times." << std::endl;
		return 0;
	}
	int Turn(int var)
	{
		std::cout << "Turning in direction " << var << "." <<std::endl;
		return 0;
	}
	int TurnL()
	{
		std::cout << "Turning left." <<std::endl;
		return 0;
	}
	int TurnR()
	{
		std::cout << "Turning right." <<std::endl;
		return 0;
	}
};

#endif
