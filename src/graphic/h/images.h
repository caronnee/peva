#ifndef ___IMAGE_LOAD____
#define ___IMAGE_LOAD____

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stack>

#include "../../add-ons/h/position.h"
#define SHIFT 2

/* types of walls we have */

enum WallImageObjects
{
	WallFree = 0,
	WallSolidId,
	WallPushId,
	WallTrapId,
	WallStartId,
	TargetPlace,
	SelectedID,
	NumberObjectsImages
};

/* type of actions an object can do */

enum Actions
{
	ActionDefault = 0,
	ActionSleep,
	ActionWalk,
	ActionAttack,
	ActionHit,
	ActionDead,
	ActionDeadStill,
	NumberOfActions
};

/* class for loading images */

class Skin
{
protected:
	std::string directory;

public:
	/* number of files a skin have to load */
	size_t size;

	/* one dimensional attay of loaded images size of 'size' */
	SDL_Surface ** images;

	/* size of image that should be visible */
	Position imageSize;

	/* how manu pixels we must add t get to he next state of images */
	Position shift;

	/* how many pixels in the begining is 'empty' */
	Position begin_in_picture; //kolko toho ma urezat zo zaciatku

public:
	Skin();

	/* name of set for memory optimalization, no need to be private */
	std::string nameOfSet;

	/* types of skins, could be solved by inheritance*/
	enum Type
	{
		MapSkin, //TODO znicit
		BotSkin
	};
	/* constructor for skin */
	Skin(std::string name, Skin::Type t);

	/* common method for loading images */
	void create(std::string * loadImages, std::string name, int sizeToLoad);

	/* returns image corresponding to index */
	SDL_Surface * get_surface(size_t index);

	/* returns size of image */
	Position get_size();

	/* returns the distance to the nex omage state in x and y axis*/
	Position get_shift();

	/* returns the first position when ther is someting to see*/
	Position get_begin();

	/* destructor */
	virtual ~Skin();
};

/* class for creating missille skins */

class MissilleSkin : public Skin
{
public:
	MissilleSkin( std::string name );
};

/* class for creating wall skins */

class WallSkin : public Skin
{
public:
	WallSkin(std::string name, size_t wall); //ktory wall ma naloadovat
};
/* class for handling the skin */

class ImageSkinWork
{
public:
	enum States
	{
		StateDefault = 0,
		StatePermanent,
		StateTemporarily,
		NumberOfStates
	};

public:
	/* miliseconds grom the last blit */
	Uint32 lastUpdate;
	size_t count;
	std::stack<States> state;

	Rectangle imageCut;
public:
	/* constructor */
	ImageSkinWork(Skin * s);

	Rectangle getCollissionRectagle() const;

	/* return whether temporary action is still running */
	bool processing();	

	/* returns the actual picture of state */
	SDL_Surface * get_image();

	/* returns the SDL rectangle what part of image should be showed */
	SDL_Rect get_rect();

	/* set the image according to state and action */
	void switch_state(States s, Actions a);
	
	/* set the image to the previous state, if none, default */
	void removeState();

	/* returns width of picture that should be visible */
	size_t width();

	/* returns height of picture that should be visible */
	size_t height();

	/* returns the size of visible rectangle in picture */
	Position get_size();

	/* changes the direction of object , shift removeswring image direction at beginning */
	float turn(int degree, int shift = SHIFT);

	/* returns position od supposed head character according size */
	Position head();

	/* return beginning of the picture */
	Position get_begin()const;

public:

	Skin * s;
	Actions states[NumberOfStates];
	//size_t row; netreba, zostane stale stejna
	SDL_Rect rect; //kde prave som
};
class ImageSkinWallWorker: public ImageSkinWork
{
	public:
	virtual void switch_state(States s, Actions a);
};
#endif
