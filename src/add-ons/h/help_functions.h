#ifndef ___HELP_FUNCTIONS___
#define ___HELP_FUNCTIONS___

#include <string>
#include <sstream>

#define PI 3.14159265

/** 
 * @brief @return minimum of two elements 
 * */
template <class T>
T min(T x, T y)
{
	if ( x>y)
		return y;
	return x;
}

/** 
 * @brief @return maximum of two elements 
 * */
template <class T>
T max(T a, T b)
{
	if ( a > b)
		return a;
	return b;
};

/** 
 * @brief converts class T to string 
 * */
template<class T> 
T convert(std::string s)
{
	T number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
};

/** 
 * @brief converts string to class T 
 * */
template<class T> 
std::string deconvert(T i)
{
	std::ostringstream convertor;
	convertor << i;
	return convertor.str();
};

/** 
 * @brief converts @param angle to @return 
 * positive integer number representing degrees 
 * */
int toDegree(float angle);

/** 
 * @brief converts @param angle to @return 
 * positive float number representing radians 
 * */
float toRadians(int angle);

#endif
