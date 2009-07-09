#include "node.h"

Location::Location(int x_, int y_)
{
	x = x_; y = y_;
}
Node::Node() //toto sa normalne nebude pouzivat
{
	last_access = 0;
	type = TypeUndefined;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	//location, object, real numbers a pod, nahodne cisla
}
Node::Node(std::string s,Type t)
{
	last_access = 0;
	type = TypeUndefined;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	name = s;
	type = t;
}

