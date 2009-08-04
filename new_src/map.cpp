#include "map.h"

Map::Map(Position resol)
{
	resolution = resol;
	map = new Object**[resol.x];
	for( int i =0; i< resolution.x; i++)
	{
		map[i] = new Object*[resolution.y];
		for (int k = 0; k< resolution.y; k++)
		{
			map[i][k] = NULL;
		}
	}
}

