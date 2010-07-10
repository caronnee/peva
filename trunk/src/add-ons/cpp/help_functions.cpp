#include <iostream> //len pre debugovacie ucely! TODO
#include <sstream>
#include <string>
#include "../h/help_functions.h"

int toDegree( float angle )
{
	return (int)(angle * 180 / PI);
}

double toRadians( int angle )
{
	return (double)angle * PI /180;
}
