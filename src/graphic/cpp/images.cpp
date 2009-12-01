#include "../h/images.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <fstream>

namespace bf = boost::filesystem;

Skin::Skin()
{
	size = 0;
	nameOfSet = "Undefined";
	filenames = NULL;
}

std::string toLoadBot[] = {"default.png", "sleep.png", "walk.png", "attack.png", "hit.png", "dead.png", "missille.png" };

//TODO akonsa steny rozbijaju
std::string toLoadMap[] = {"Free.png","SolidWall.png", "PushWall.png", "TrapWall.png","selected.png" };

//TODO predat len nejaky parameter alebo kopirovat;)
Skin::Skin(std::string name, Skin::Type t)
{
	nameOfSet = name;
	std::string * load;
	std::string directory = "./mapSkins"; 
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
	if (!bf::exists(directory + name))
	{
		std::cerr << "Directory " <<directory + name<< " not found!"<< std::endl; //TODO exception
		getc(stdin);
		return;
	}
	directory = directory+name + '/';
	bf::directory_iterator end_itr;
	int loaded = 0;
	for (bf::directory_iterator iter (directory); iter!= end_itr; iter++)
	{
		for (size_t i = 0; i<size; i++ )
		{
			std::cout << "checkujem:" << iter->leaf();
			if (load[i] == iter->leaf())
			{
				std::cout << "LOADING!"<<directory + load[i];getc(stdin);
				images[loaded] = IMG_Load((directory + load[i]).c_str());
				loaded++;
				break;
			}
		}
	}	
	if (!bf::exists(directory + "config"))
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = 0;
		shift.y = 0;
		std::cout << "images" << images[0];
		getc(stdin);
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

SDL_Surface * ImageSkinWork::get_image()
{
	return s->get_surface(states[state]);
}
SDL_Rect ImageSkinWork::get_rect()
{
	rect.x +=s->get_shift().x;
	if (rect.x >= s->get_surface(states[state])->w)
	{
		rect.x = s->get_begin().x;
	}
	return rect;	
}
void ImageSkinWork::add_state(States index)
{
	state = index;
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
