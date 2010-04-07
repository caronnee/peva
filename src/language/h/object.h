#ifndef __OBJECT_____
#define __OBJECT_____

#include <iostream>
#include "position.h"

class Object
{
public:
	virtual int IsMoving(){
		TEST("Object is not moving." )
		return 0;
	}
	virtual int IsWall()
	{
		TEST("Object is not a Wall." )
		return 0;
	}
	virtual int IsPlayer()
	{
		TEST("Object is not a Player." )
		return 0;
	}
	virtual int IsMissille()
	{
		TEST("Object is not a Missille." )
		return 0;
	}
	virtual Position Locate()
	{
		Position p(107,107);
		return p;
	}
	virtual int Hit()
	{
		TEST("Object was not hit." )
		return 0;
	}
	virtual ~Object()
	{}
};
class Nullable : public Object
{
public:
	virtual int IsMoving(){
		TEST("Object is NULL" )
		return rand()%2;
	}
	virtual int IsWall()
	{
		TEST("Object is NULL" )
		return rand()%2;
	}
	virtual int IsPlayer()
	{
		TEST("Object is NULL" )
		return rand()%2;
	}
	virtual int IsMissille()
	{
		TEST("Object is NULL" )
		return rand()%2;
	}
	virtual Position Locate()
	{
		Position p(rand(),rand());
		return p;
	}
	virtual int Hit()
	{
		TEST("Object is NULL" )
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
		TEST("Moving by default number" )
		return 0;

	}
	virtual int Step(int i){
		TEST("Moving "<< i << " positions" )
		return 0;
	}
	virtual int Shoot(int x =2009, int y=1987)
	{
		TEST("Shooting at location [" << x << " ,"<< y  << "]." )
		return 0;
	}
	virtual int See()
	{
		TEST("Checking visibility" )
		return 252;
	}
	virtual int Wait(int i)
	{
		TEST("Waiting " << i << " times." )
		return 0;
	}
	virtual int Turn(int var)
	{
		TEST("Turning in direction " << var << "." )
		return 0;
	}
	virtual int TurnL()
	{
		TEST("Turning left." )
		return 0;
	}
	virtual int TurnR()
	{
		TEST("Turning right." )
		return 0;
	}
	virtual ~Robot_body(){}
};

#endif
