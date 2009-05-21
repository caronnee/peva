#include <iostream> //len pre debugovacie ucely! TODO
#include <sstream>
#include <string>
#include "help_functions.h"

unsigned int convert(std::string s)
{
	std::cout << s<< std::endl;
	unsigned number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
}
int min(int x, int y)
{
	if (x < y) return x;
	return y;
}
