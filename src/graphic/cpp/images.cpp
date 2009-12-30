#include "../h/images.h"
#include "../../add-ons/h/help_functions.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <fstream>

#define TICKS 100
#define BORED_AFTER 100

namespace bf = boost::filesystem;

std::string toLoadBot[] = { "default.png", "sleep.png", "walk.png", "attack.png", "hit.png", "dead.png" };
std::string toLoadMissille[] = {"missille.png"};

//TODO akonsa steny rozbijaju
std::string toLoadMap[] = {"Free.png","SolidWall.png", "PushableWall.png", "TrapWall.png","ExitWall.png", "selected.png" };

Skin::Skin()
{
	images = NULL;
}
Skin::Skin(std::string name, Skin::Type t)
{
	nameOfSet = name;
	std::string * load;
	std::string directory = "./"; 
	int sizeLoaded;
	switch (t)
	{
		case MapSkin:
		{
			directory = "./mapSkins/";
			load = toLoadMap;
			size = NumberObjectsImages;
			sizeLoaded = size;
			images = new SDL_Surface *[size];
			break;
		}
		case MissilleSkin:
		{
			directory = "./botSkins/";
			load = toLoadMissille;
			size = NumberOfActions;
			sizeLoaded = 1;
			images = new SDL_Surface *[NumberOfActions];
			break;
		}
		case BotSkin:
		{
			directory = "./botSkins/";
			load = toLoadBot;
			size = NumberOfActions;
			sizeLoaded = NumberOfActions;
			images = new SDL_Surface *[size];
			break;
		}
		default:
		{
			directory = "./";
			size = -1;
			load = NULL;
		}
	}
	for (size_t i =0; i< size; i++)
	{
		images[i] = NULL;
	}
	
	if (!bf::exists(directory + name))
	{
		std::cerr << "Error! Directory " <<directory + name<< " not found!"<< std::endl; //TODO exception
		getc(stdin);
		return;
	}
	directory = directory+name + '/';
	for (size_t i = 0; i<sizeLoaded; i++ )
	{
		images[i] = IMG_Load((directory + load[i]).c_str());
	}

	for (size_t i =1; i<size; i++) //action default tam musi byt v kazdom pripade, TODO doplnit
	{
		if (images[i]==NULL)
			images[i] = IMG_Load((directory + load[0]).c_str()); //aby sa dalo pouzit free
	}
	if (t == MissilleSkin)
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = images[0]->h;
		shift.y = images[0]->h;
		imageSize.x = imageSize.y = images[0]->h; //strely u stvorcove
		return;
	}
	if (!bf::exists(directory + "config"))
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = images[0]->h;
		shift.y = images[0]->w;
		imageSize.x = images[0]->w; //predpokladame, ze su vsetky rovnakej velkosti
		imageSize.y = images[0]->h;
		return; //exception?
	}
	std::fstream f;
	f.open((directory + "config").c_str());
	if (f.good())
	{
		f >>begin_in_picture.x;	
		f >>begin_in_picture.y;	
		f >>imageSize.x;	
		f >>imageSize.y;
		f >>shift.x;	
		f >>shift.y;	
	}	
}
SDL_Surface * Skin::get_surface(size_t index)
{
	return images[index];
}
Position Skin::get_size()
{
	return imageSize;
}
Position Skin::get_begin()
{
	return begin_in_picture;
}
Position Skin::get_shift()
{
	return shift;
}
Skin::~Skin()
{
	for (size_t i = 0; i< size; i++)
	{
		SDL_FreeSurface(images[i]);
	}
	delete[] images;
}

WallSkin::WallSkin(std::string name, size_t wall)
{
	nameOfSet = name;
	std::string directory = "./mapSkins/" + name + "/";
	if (!bf::exists(directory))
	{
		std::cout << "Nonexistent maps!";//TODO vynimka
		getc(stdin);
		return;
	}
	size = NumberOfActions;
	images = new SDL_Surface *[size];
	//TODO zatial, pridat sleep veci a pod.
	for (size_t i =0; i< size; i++)
	{
		images[i] = IMG_Load((directory +toLoadMap[wall]).c_str());
	}
	begin_in_picture.x = 0;
	begin_in_picture.y = 0;
	shift.x = images[0]->h;
	shift.y = images[0]->w;
	imageSize.x = images[0]->w; //predpokladame, ze su vsetky rovnakej velkosti
	imageSize.y = images[0]->h;
}

ImageSkinWork::ImageSkinWork(Skin * skin)
{
	count = 0;
	s = skin;
	state.push(StateDefault);
	states[StateDefault] = ActionDefault; //ostatene sa budu prepisovat
	rect.h = skin->get_shift().y;
	rect.w = skin->get_shift().x;
	rect.x = 0;
	rect.y = 0;
	lastUpdate = 0;
}
//BIG TODO walls to vadi, ale do default by sa nikdy nemali dostat
SDL_Surface * ImageSkinWork::get_image()
{
	count++;
	states[StateDefault] = count > BORED_AFTER ? ActionSleep:ActionDefault;
	return s->get_surface(states[state.top()]);
}
SDL_Rect ImageSkinWork::get_rect()
{
	Uint32 t =SDL_GetTicks();
	if (t - lastUpdate > TICKS)
		{
			rect.x += s->get_shift().x;
			lastUpdate = SDL_GetTicks();
		}
	usleep(50);
	if (rect.x >= s->get_surface(states[state.top()])->w)
	{
		rect.x = 0;
		if (state.top() == StateTemporarily)
		{
			removeState();
		}
	}
	return rect;	
}

//stane sa pri hit object
void ImageSkinWork::switch_state(States index, Actions action)
{
	count = 0;
	states[index] = action;
	states[StateDefault] = ActionDefault;
	if (index<state.top())
	{
		//zarad to pod aktual
		States s = state.top();
		removeState();
		switch_state(s,states[s]);
		state.push(index);
		index = s;
	}
	state.push(index);
}
bool ImageSkinWork::processing()
{
	return state.top() == StateTemporarily;
}
void ImageSkinWork::removeState()
{
	count = 0;
	states[StateDefault] = ActionDefault;
	state.pop();
	if(state.empty())
		state.push(StateDefault);
}
size_t ImageSkinWork::width() //bude sa pytat kvoli kolizii
{
	return s->get_size().x;
}
size_t ImageSkinWork::height() //bude sa pytat kvoli kolizii
{
	return s->get_size().y;
}
Position ImageSkinWork::get_size()
{
	return s->get_size();
}

float ImageSkinWork::turn(int degree)//nastavi uhol na degree
{
	count = 0;
	states[StateDefault]=ActionDefault;
	size_t directions = get_image()->h / s->get_shift().y;
	float dirShift = 360 / directions;
	int sh = degree / dirShift;
	rect.y = sh*s->get_shift().y;
	rect.y %= get_image()->h;
	return dirShift;
}
Position ImageSkinWork::head()
{
	Position p(0,0);
	// plus jedna, pretoze zaciname od severu
	size_t directions = 1 + get_image()->h / s->get_shift().y;
	size_t oneSide = directions/4;
	size_t dir = 1 + rect.y / s->get_shift().y;
	float add = 1.0f / oneSide;
	int side = dir/oneSide; 
	switch (side)
	{
		case 0:
		{
			p.x += (dir%oneSide)*add*s->get_shift().x;
			break;
		}
		case 1:
		{
			p.x += s->get_shift().x;
			p.y += (dir%oneSide)*add*s->get_shift().y;
			break;
		}
		case 2:
		{
			p.x += ( oneSide - dir % oneSide )*add*s->get_shift().x;
			p.y += s->get_shift().y;
			break;
		}
		case 3:
		{
			p.y += (oneSide - dir % oneSide )* add * s->get_shift().y;
			break;
		}
	}
	return p;
}
