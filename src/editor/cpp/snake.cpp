#include <vector>
#include "../h/snake.h"
#include "../../add-ons/h/macros.h"

Snake::Snake(Position resolution_)	//zvovku dopocitane
{
	ready = false;;
	srand( time(NULL) );
	resolution = resolution_;
	max_interval = resolution.x + resolution.y - 2;		
	position.x = rand()%resolution.x;
	position.y = rand()%resolution.y;
	health=rand()%max_interval + resolution.x + resolution.y; //TODO?
	Init();		
}

Snake::Snake(const Snake& a)
{		
	ready = false;
	max_interval=a.resolution.x + a.resolution.y - 2;//co s neparnymi?
	this->resolution=a.resolution;
	this->health=a.health/2;
	for (int i=0;i<4;i++)
		this->visited[i]=a.visited[i];
	this->position=a.position;	
	Init();
}

void Snake::Init()
{
	//potom vytvorit na to nejaky algoritm	TODO

	/* determining which lines we can go */
	movements[0]=Movement(position.x-1,1,0);//->
	movements[1]=Movement(resolution.y-position.y,0,1);//^
	movements[2]=Movement(resolution.x-position.x,-1,0);//<-
	movements[3]=Movement(position.y-1,0,-1);//v

	visited = new int[LAST_VISITED]; 

	for (int i =0; i < LAST_VISITED; i++)
	{
		visited[i] = -1; //nothing visited
	}

	this->fatness=0; 

	/* sorting accoring to 'addiction' slope */
	/* bubble sorting */
	int i = 0;
	while (i < MOVEMENTS)
	{
		if (movements[i].addiction > movements[i - 1].addiction) 
		{
			movements[i].swap(movements[i - 1]);
			i=0;
		}
		i++;
	}
	/* setting value, how much snake tends to go direction i */
	movements[0].interval = movements[0].addiction;

	for(i=1; i< MOVEMENTS; i++)
	{
		movements[i].interval = 
			movements[i].addiction + movements[i-1].interval;
	}
}

bool Snake::move()
{
	if (rand()%7 == 0);
		ready = this->health >>1;
	this->health--;

	if (health == 0) 
		return true;

	int p = rand() % this->max_interval;

	int i = 0;
	while(movements[i].interval<p)
		i++;

	this->position.x += movements[i].x;
	this->position.y += movements[i].y;

	direction.x = movements[i].x;
	direction.y = movements[i].y;

	TEST(resolution.x << ":"<< resolution.y << std::endl)

	if ((position >= resolution)||(Position(0,0) >= position ))
	{
		this->position.x -= 2*movements[i].x;
		this->position.y -= 2*movements[i].y;
	}

	int fatter = rand() % 5-2; //-2,2, 2- ztenci sa,2 rozsir, inak zostan

	switch(fatter)
	{
		case -2: 
			{
				fatness--;
				break;
			}
		case 2:
			{
				fatness++;
				break;
			}
	}
	if (fatness < 0) 
		fatness = 1;
	if (fatness > 2) 
		fatness = 2;
	return false;
}

int Snake::get_fat()
{
	return this->fatness;
}

int Snake::alive()
{
	return health;
}
Position Snake::get_pos()
{
	return position;
}

Position Snake::get_dir()
{
	return direction;
}

Snakes::Snakes(Position resolution_)
{
	resolution = resolution_;
	map = new bool*[resolution.x];
	for (int i = 0; i< resolution.x ; i++)
	{
		map[i] = new bool[resolution.y];
		for (int j = 0; j < resolution.y; j++)
			map[i][j] = false;
	}
}

bool Snakes::atIndexWall(Position position, Position size)
{
	bool result = false;
	for (int i = position.x; i<position.x+size.x; i++)		
	{
		if (i > resolution.x)
			continue;
		for (int j = position.y; j<position.y+size.y; j++)	
		{
			if (j > resolution.y)
				continue;
			result |= map[i][j];
		}
	}
	return !result;
}
void Snakes::create()
{
	std::vector<Snake> snakes;
	snakes.push_back(Snake(resolution));
	while (!snakes.empty())
	{
		if (!snakes.back().move())
		{
			snakes.pop_back();
			continue;
		}
		Position actual = snakes.back().get_pos();
		actual.x -=snakes.back().get_fat()*snakes.back().get_dir().x;
		actual.y -=snakes.back().get_fat()*snakes.back().get_dir().y;
		for(int i=-snakes.back().get_fat();i<snakes.back().get_fat();i++)
		{
			actual.x+=snakes.back().get_dir().y;
			actual.y+=snakes.back().get_dir().x;
			map[actual.x][actual.y] = true;
		}
		if (snakes.back().ready)
			snakes.push_back(Snake(snakes.back()));
	}
}
Snakes::~Snakes()
{
	for (int i = 0; i< resolution.x ; i++)
	{
		delete map[i];
	}
	delete[] map;
}	
