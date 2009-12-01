#ifndef ___IMAGE_LOAD____
#define ___IMAGE_LOAD____

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>

#include "../../add-ons/h/position.h"

enum WallImageObjects
{
	WallFree,
	WallSolidId,
	WallPushId,
	WallTrapId,
	WallExitId,
	SelectedID,
	NumberObjectsImages
};
enum Actions
{
	ActionDefault = 0,
	ActionSleep,
	ActionWalk,
	ActionAttack,
	ActionHit,
	ActionDead,
	ActionMissille,
	NumberOfActions
};

class Skin
{
protected:
	size_t size;
	std::string nameOfSet;
	std::string* filenames;
	SDL_Surface ** images;
	Position imageSize;
	Position shift;
	Position begin_in_picture; //kolko toho ma urezat zo zaciatku
public:
	enum Type
	{
		MapSkin,
		BotSkin
	};
	Skin(std::string name, Skin::Type t);
	Skin();
	SDL_Surface * get_surface(size_t index);
	Position get_size();
	Position get_shift();
	Position get_begin();
	virtual ~Skin();
};
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
	SDL_Surface * get_image();
	SDL_Rect get_rect();
	ImageSkinWork(Skin * s);
	void add_state(States s);
	void go_to_state(size_t i);
	void removeState();
	size_t width();
	size_t height();
private:
	size_t pRow; //natocenie
	Skin * s;
	States state; //aktualny stav
	size_t states[NumberOfStates];
	//size_t row; netreba, zostane stale stejna
	SDL_Rect rect; //kde prave som
};
#endif
