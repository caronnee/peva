#include <iostream> //len pre debugovacie ucely! TODO
#include <sstream>
#include <string>
#include "help_functions.h"

unsigned int convert(std::string s)
{
	unsigned number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
}
std::string deconvert(int i)
{
	std::ostringstream convertor;
	convertor << i;
	return convertor.str();
}

int min(int x, int y)
{
	if (x < y) return x;
	return y;
}
