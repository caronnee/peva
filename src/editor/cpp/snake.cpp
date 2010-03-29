#include <vector>
#include <list>
#include <fstream>
#include "../h/snake.h"
#include "../../add-ons/h/macros.h"

Snake::Snake()
{
	ready = 0;
	indexLast = 0;
	health = 0;
	position = resolution = direction = Position(-1,-1);
	max_interval = 1;
}
Snake::Snake(Position resolution_)	//zvovku dopocitane
{
	srand( time(NULL) );
	resolution = resolution_;
	max_interval = resolution.x + resolution.y - 2;		
	position.x = rand()%resolution.x;
	position.y = rand()%resolution.y;
	//TEST(" generated position " << position)
	health=(resolution.x + resolution.y)*3; //TODO?
	Init();		
}
void Snake::damage(int damage_)
{
	health -= damage_;
}

Snake Snake::clone()
{		
	Snake s;
	s.resolution = resolution;
	s.ready = 0;
	s.health = health/2+1;
	s.position = position;	
	s.Init();
	s.indexLast = indexLast;
	for (int i=0;i<4;i++)
		s.visited[i]=visited[i];
	return s;
}

void Snake::Init()
{
	indexLast = 0;
	ready = 0; //cca v polke zivota by sa mohol chciet okotit
	//potom vytvorit na to nejaky algoritm	TODO

	for (int i =0; i < LAST_VISITED; i++)
	{
		visited[i].x = 0; //nothing visited
		visited[i].y = 0; //nothing visited
	}

	this->fatness=0; 

	setMovement();
}

void Snake::setMovement()
{
	/* determining where we can go */
	movements[0]=Movement(resolution.x-position.x+1,1,0);//->
	movements[1]=Movement(resolution.y-position.y+1,0,1);//^ 
	movements[2]=Movement(position.x,-1,0);//<-
	movements[3]=Movement(position.y-1,0,-1);//v

	/* sorting accoring to 'addiction' slope */
	/* bubble sorting */
	int i = 1;
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
	max_interval = movements[MOVEMENTS-1].interval;
}
bool Snake::move()
{
	ready = rand()%100 == 0;

	this->health--;

	if (health == 0) 
		return false;

	int p = rand() % this->max_interval;

	int i = 0;
	while(movements[i].interval<p)
		i++;

	this->position.x += movements[i].x;
	this->position.y += movements[i].y;

	direction.x = movements[i].x;
	direction.y = movements[i].y;

	if ((position >= resolution)||(Position(0,0) > position ))
	{
		this->position.x -= 2*movements[i].x;
		this->position.y -= 2*movements[i].y;
		setMovement();
	}
	int fatter = rand() % 5-2; //-2,2, 2- ztenci sa,2 rozsir, inak zostan
	
	Position test = visited[(indexLast-1 + MOVEMENTS)%MOVEMENTS];
	test.substractVector(position);
	if (test.x * test.y != 0)
	{
		TEST("??" <<indexLast << " " << visited[indexLast] << ":" << position <<  " "<< test )
	}
	for (int i =0; i< LAST_VISITED; i++)
	{
		if (position == visited[i])
		{
			direction.x = movements[MOVEMENTS - 1].x;
			direction.x = movements[MOVEMENTS - 1].y;
			position = visited[LAST_VISITED];
			position += direction;
		}
	}
	visited[indexLast] = position;
	indexLast++;
	indexLast %= LAST_VISITED;
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
		fatness = 0;
	if (fatness > 4) 
		fatness = 4;
//	TEST("@" << position << " ")
	return true;
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

bool Snakes::isWallAt(Position position, Position size)
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
	std::list<Position> todoPosition;
	snakes.push_back(Snake(resolution));
	/*while (!snakes.empty())
	{
		if (!snakes.back().move())
		{
			snakes.pop_back();
			continue;
		}
		Position actual = snakes.back().get_pos();
		actual.x -=snakes.back().get_fat()*snakes.back().get_dir().x;
		actual.y -=snakes.back().get_fat()*snakes.back().get_dir().y;
		for(int i=-snakes.back().get_fat();i<=snakes.back().get_fat();i++)
		{
			if ((actual.x < 0) 
				|| (actual.y < 0) 
				|| (actual.x >= resolution.x) 
				|| (actual.y >= resolution.y))
				continue;
			map[actual.x][actual.y] = true;
			actual.x+=snakes.back().get_dir().y;
			actual.y+=snakes.back().get_dir().x;
			//TEST(actual << " ")
		}
		if (snakes.back().ready)
			snakes.push_back(Snake(snakes.back().clone()));
	}*/
	for(int i = 0; i < resolution.x;i++)
	{
		for(int j = 0; j < resolution.y;j++)
		{
			map[i][j] = false;
		}
	}
}
void Snakes::saveToFile(std::string filename)
{
	std::ofstream file;
	file.open(filename.c_str(),std::ios::out);
	if (!file.good())
	{
		TEST("Unable to create file " << filename)
		return;
	}
	for (int i =0; i< resolution.x;i++)
	{
		for (int j =0; j< resolution.y; j++)
		{
			if (map[i][j])
				file << ' ';
			else
				file << 'o';
		}
		file << '\n';
	}
	file.close();
}
Snakes::~Snakes()
{
	for (int i = 0; i< resolution.x ; i++)
	{
		delete map[i];
	}
	delete[] map;
}	
