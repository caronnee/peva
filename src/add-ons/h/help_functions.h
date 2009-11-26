#ifndef ___HELP_FUNCTIONS___
#define ___HELP_FUNCTIONS___

#include <string>
#include <sstream>

int min(int x, int y);
template<class T> 
T convert(std::string s)
{
	T number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
};
template<class T> 
std::string deconvert(T i)
{
	std::ostringstream convertor;
	convertor << i;
	return convertor.str();
};
#endif
