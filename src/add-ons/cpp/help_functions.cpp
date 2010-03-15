#include <iostream> //len pre debugovacie ucely! TODO
#include <sstream>
#include <string>
#include "../h/help_functions.h"

int toDegree( float angle )
{
	return angle * 180 / PI;
}

float toRadians( int angle )
{
	return (float)angle * PI /180;
}
