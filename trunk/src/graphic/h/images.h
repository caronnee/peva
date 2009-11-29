#ifndef ___IMAGE_LOAD____
#define ___IMAGE_LOAD____

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>


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
class ImageSet
{
	std::string namesOfSet;
	std::string* filenames;
	public:
	SDL_Surface ** images;
	ImageSet(std::string name);
	~ImageSet();
};
#endif
