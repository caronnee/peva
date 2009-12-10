#include "../h/images.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <fstream>

#define TICKS 130

namespace bf = boost::filesystem;

std::string toLoadBot[] = {"default.png", "sleep.png", "walk.png", "attack.png", "hit.png", "dead.png" };
std::string toLoadMissille[] = {"missille.png"};

//TODO akonsa steny rozbijaju
std::string toLoadMap[] = {"Free.png","SolidWall.png", "PushableWall.png", "TrapWall.png","ExitWall.png", "selected.png" };

Skin::Skin(std::string name, Skin::Type t)
{
	nameOfSet = name;
	std::string * load;
	std::string directory = "./"; 
	bool x = false;
	switch (t)
	{
		case MapSkin:
		{
			directory = "./mapSkins/";
			load = toLoadMap;
			size = NumberObjectsImages;
			images = new SDL_Surface *[size];
			break;
		}
		case MissilleSkin:
		{
			directory = "./botSkins/";
			x = true;
			load = toLoadMissille;
			size = 1;
			images = new SDL_Surface *[NumberOfActions];
			break;
		}
		case BotSkin:
		{
			directory = "./botSkins/";
			load = toLoadBot;
			size = NumberOfActions;
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
	bf::directory_iterator end_itr;
	for (bf::directory_iterator iter (directory); iter!= end_itr; iter++)
	{
		for (size_t i = 0; i<size; i++ )
		{
			if (load[i] == iter->leaf())
			{
				images[i] = IMG_Load((directory + load[i]).c_str());
				break;
			}
		}
	}	

	for (size_t i =1; i<size; i++) //action default tam musi byt v kazdom pripade, TODO doplnit
	{
		if (images[i]==NULL)
			images[i] = images[i-1];
	}
	if (t == MissilleSkin)
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = images[0]->h;
		shift.y = 0;
		imageSize.x = imageSize.y = images[0]->h; //strely u stvorcove
		return;
	}
	if (!bf::exists(directory + "config"))
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = 0;
		shift.y = 0;
		imageSize.x = images[0]->w; //predpokladame, ze su vsetky rovnakej velkosti
		imageSize.y = images[0]->h;
		return; //exception?
	}
	std::fstream f;
	f.open((directory + "config").c_str());
	if (f.good())
	{
		f >> (begin_in_picture.x);	
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

ImageSkinWork::ImageSkinWork(Skin * skin)
{
	s = skin;
	state = StateDefault;
	states[StateDefault] = ActionDefault; //ostatene sa budu prepisovat
	rect.w = skin->get_size().x;
	rect.h = skin->get_size().y;
	rect.x = 0;
	rect.y = 0;
	lastUpdate = 0;
}
SDL_Surface * ImageSkinWork::get_image()
{
	return s->get_surface(states[state]);
}
SDL_Rect ImageSkinWork::get_rect()
{
	Uint32 t =SDL_GetTicks();
	std::cout <<t - lastUpdate<<std::endl;
	if (t - lastUpdate > TICKS)
		{
			rect.x +=s->get_shift().x;
			lastUpdate = SDL_GetTicks();
		}
	if (rect.x >= s->get_surface(states[state])->w)
	{
		rect.x = s->get_begin().x;
	}
	return rect;	
}
void ImageSkinWork::switch_state(States index, Actions action)
{
	state = index;
	states[index] = action;
}
void ImageSkinWork::removeState()
{
	//FIXME moc sa mne nelubi, drak spi a potom kychne a zase spi?
	switch (state)
	{
		case ImageSkinWork::StateTemporarily:
			{
				state = ImageSkinWork::StatePermanent;
				break;
			}
		case ImageSkinWork::StatePermanent:
			{
				state = ImageSkinWork::StateDefault;
				states[ImageSkinWork::StateDefault] = 0; //not sleeping
				break;
			}
		default:
			break;

	}	
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

float ImageSkinWork::turn(int degree)
{
	while (degree < 0)
	{
		degree += 360;
	}
	size_t directions = get_image()->h / s->get_shift().y;
	float dirShift = 360 / directions;
	int sh = degree / dirShift;
	rect.y = sh*s->get_shift().y;
	rect.y %= get_image()->h;
	return dirShift;
}
