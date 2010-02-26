#ifndef ___HELP_FUNCTIONS___
#define ___HELP_FUNCTIONS___

#include <string>
#include <sstream>

template <class T>
T min(T x, T y)
{
	if ( x>y)
		return y;
	return x;
}

template <class T>
T max(T a, T b)
{
	if ( a > b)
		return a;
	return b;
};

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
