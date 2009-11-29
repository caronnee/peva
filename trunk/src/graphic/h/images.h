#ifndef ___IMAGE_LOAD____
#define ___IMAGE_LOAD____

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>

typedef std::map<std::string, size_t> myMap;

enum RobotImageObjects
{
	MissilleID,
	RobotID,
	NumberRobotImages
};
enum WallImageObjects
{
	WallSolidId,
	WallPushId,
	WallTrapId,
	NumberObjectsImages
};
class Skin
{
protected:
	size_t size;
	std::string nameOfSet;
	std::string* filenames;
	SDL_Surface ** images;
public:
	enum Type
	{
		MapSkin,
		BotSkin
	};
	Skin(std::string name, myMap s, Skin::Type t);
	Skin();
	SDL_Surface * get_surface(size_t index);
	virtual ~Skin();
};
#endif
