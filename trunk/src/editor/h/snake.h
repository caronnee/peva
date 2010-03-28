#ifndef ___SNAKE____
#define ___SNAKE____

#include "movement.h"
#include "../../add-ons/h/position.h"

#define MOVEMENTS 4
#define LAST_VISITED 4

class Snake
{
public:
	/*  */
	Snake();

	/* constructor */
	Snake(Position resolution_);
	
	/* clone onstructor */
	Snake clone();

	/* if the snak is ready to be split */
	bool ready;
private:

	/* index of last visited tile */
	int indexLast;

	/* inits our class, it is called in every constructor */
	void Init();	

	/* number of tile to left and rigt, symmetrically */
	int fatness;
	
	/* how many tile forward is snake able to do */
	int health;

	/* few last visited tiles for debugging */
	Position visited[LAST_VISITED]; 

	/* actual position in our map */
	Position position;

	/* resolution of map */
	Position resolution;

	/* actual snake direction */
	Position direction;

	/* maximum interva that snad can go */
	int max_interval;

	/* direction and affitity to direction */
	Movement movements[MOVEMENTS];

public:
	void setMovement();
	/* changes position */
	bool move();

	/* return, how much is actual snake fatter than usual */
	int get_fat();

	/* returns number of snake hitpoints */
	int alive();

	/* returns snake direction */
	Position get_dir();

	/* retur actual position in snake map */;
	Position get_pos();
};

class Snakes
{

private:
	/* resolution of the snake map */
	Position resolution;

	/* structure representing snake map */
	bool ** map;
public:
	/* Constructor */
	Snakes(Position resolution);

	/* returns if a wall fits real map according to created snake map */
	bool isWallAt(Position position, Position size);

	/* creates map */
	void create();	

	/* saves map to file */
	void saveToFile(std::string filename);
	
	/* destructor */
	~Snakes();
};
#endif
