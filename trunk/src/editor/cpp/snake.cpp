#include "../h/snake.h"

void Snake::Init()
{
	//potom vytvorit na to nejaky algoritm	TODO

	movements[0]=Movement(position.x-1,1,0);//->
	movements[1]=Movement(resolution.y-position.y,0,1);//^
	movements[2]=Movement(resolution.x-position.x,-1,0);//<-
	movements[3]=Movement(position.y-1,0,-1);///v

		//suradna sustava, ze 00 je v lavom dolnom rohu
	//zatriedit podla addictioni od najvacieseho po najmensie

	this->fatness=0;
	int i=1;
	visited = new int[LAST_VISITED];  //TODO konstanta sa nejak prerobi
	for (int i =0; i < LAST_VISITED; i++)
	{
		visited[i] = -1;
	}
	while (i < MOVEMENTS)
	{
		if (movements[i].addiction>movements[i - 1].addiction) 
		{
			movements[i].swap(movements[i - 1]);
			i=0;
		}
		i++;
	}
	//prejdi to a vytvore odpovedajuce intervaly
	movements[0].interval = movements[0].addiction;
	for(i=1;i<MOVEMENTS;i++)
	{
		movements[i].interval = 
			movements[i].addiction + movements[i-1].interval;
	}
	/*for (int i =0; i< 4; i++)
	{
		std::cout << movements[i].x << ":" << movements[i].y << std::endl;
	}
	exit(4);
*/
}

bool Snake::move()
{
	int i = 0;
	this->health--;//pohol sa,klesa mu health;

	if (health == 0) 
		return true;

	int p = rand()%this->max_interval;

	while(movements[i].interval<p)
		i++;

	this->position.x += movements[i].x;
	this->position.y += movements[i].y;

	direction.x=movements[i].x;
	direction.y=movements[i].y;

	std::cout << resolution.x << ":"<< resolution.y << std::endl;
	if (position>=resolution)
	{
		//bude prechadzat na druhu obrazovku
		position.x%=resolution.x;
		position.y%=resolution.y;
		std::cout << " dalsia obrazovka" << std::endl;
	}
	if (position.x<0)
		position.x+=resolution.x;
	if(position.y<0)
		position.y+=resolution.y;
	int fatter = rand()%5-2;//-2,2, 2- ztenci sa,2 rozsir, inak zostan
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
	if (fatness<0) fatness=1;
	if (fatness>2) fatness=2;
	return false;
}

Snake::Snake(const Snake& a)
{		
	max_interval=a.resolution.x+a.resolution.y - 2;//co s neparnymi?
	this->resolution=a.resolution;
	this->health=a.health;
	for (int i=0;i<4;i++)
		this->visited[i]=a.visited[i];
	this->position=a.position;	
}

Snake::Snake(Position resolution_)
{
	resolution = resolution_;
	max_interval = resolution.x + resolution.y - 2;		
	int hlt = resolution.x + resolution.y;
	position.x %= resolution.x;
	position.y %= resolution.y;
	health=rand()%hlt + resolution.x + resolution.y; //TODO?
	Init();		
}

int Snake::get_x()
{
	return this->position.x;
}
int Snake::get_y()
{
	return this->position.y;
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
