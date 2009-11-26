#ifndef __OBJECT_____
#define __OBJECT_____

#include <iostream>
#include "position.h"

class Object
{
public:
	virtual int IsMoving(){
		std::cout << "Object is not moving." << std::endl;
		return 0;
	}
	virtual int IsWall()
	{
		std::cout << "Object is not a Wall." << std::endl;
		return 0;
	}
	virtual int IsPlayer()
	{
		std::cout << "Object is not a Player." << std::endl;
		return 0;
	}
	virtual int IsMissille()
	{
		std::cout << "Object is not a Missille." << std::endl;
		return 0;
	}
	virtual Position Locate()
	{
		Position p(107,107);
		return p;
	}
	virtual int Hit()
	{
		std::cout << "Object was not hit." << std::endl;
		return 0;
	}
	virtual ~Object()
	{}
};
class Nullable : public Object
{
public:
	virtual int IsMoving(){
		std::cout << "Object is NULL" << std::endl;
		return rand()%2;
	}
	virtual int IsWall()
	{
		std::cout << "Object is NULL" << std::endl;
		return rand()%2;
	}
	virtual int IsPlayer()
	{
		std::cout << "Object is NULL" << std::endl;
		return rand()%2;
	}
	virtual int IsMissille()
	{
		std::cout << "Object is NULL" << std::endl;
		return rand()%2;
	}
	virtual Position Locate()
	{
		Position p(rand(),rand());
		return p;
	}
	virtual int Hit()
	{
		std::cout << "Object is NULL" << std::endl;
		return rand()%2;
	}
	virtual ~Nullable(){}
};
struct Robot_body : public Object
{
	virtual Object* Eye(size_t i)
	{
		return this;
	}
	virtual int Step()
	{
		std::cout << "Moving by default number" << std::endl;
		return 0;

	}
	virtual int Step(int i){
		std::cout << "Moving "<< i << " positions" << std::endl;
		return 0;
	}
	virtual int Shoot(int x =2009, int y=1987)
	{
		std::cout <<"Shooting at location [" << x << " ,"<< y  << "]." <<std::endl;
		return 0;
	}
	virtual int See()
	{
		std::cout << "Checking visibility" <<std::endl;
		return 252;
	}
	virtual int Wait(int i)
	{
		std::cout << "Waiting " << i << " times." << std::endl;
		return 0;
	}
	virtual int Turn(int var)
	{
		std::cout << "Turning in direction " << var << "." <<std::endl;
		return 0;
	}
	virtual int TurnL()
	{
		std::cout << "Turning left." <<std::endl;
		return 0;
	}
	virtual int TurnR()
	{
		std::cout << "Turning right." <<std::endl;
		return 0;
	}
	virtual ~Robot_body(){}
};

#endif
