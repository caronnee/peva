#include "../h/images.h"
#include "boost/filesystem.hpp"
#include <iostream>

namespace bf = boost::filesystem;

Skin::Skin()
{
	size = 0;
	nameOfSet = "Undefined";
	filenames = NULL;
}

//TODO predat len nejaky parameter alebo kopirovat;)
Skin::Skin(std::string name, myMap s, Skin::Type t)
{
	nameOfSet = name;
	size = s.size();
	images = new SDL_Surface *[s.size()];
	std::string directory = "./mapSkins"; 
	switch (t)
	{
		case MapSkin:
		{
			directory = "./mapSkins/";
			break;
		}
		case BotSkin:
		{
			directory = "./botSkins/";
			break;
		}
		default:
		{
			directory = "./";
		}
	}
	if (!bf::exists(directory + name))
	{
		std::cerr << "Directory not found!"<< std::endl; //TODO exception
		getc(stdin);
		return;
	}
	bf::directory_iterator end_itr;
	for (bf::directory_iterator iter (directory); iter!= end_itr; iter++)
	{
		myMap::iterator iii;
		iii = s.find(iter->leaf());
		if (iii==s.end())
			continue;
		images[iii->second] = IMG_Load(iii->first.c_str());
	}	
}
SDL_Surface * Skin::get_surface(size_t index)
{
	return images[index];
}
Skin::~Skin()
{
	for (size_t i = 0; i< size; i++)
	{
		SDL_FreeSurface(images[i]);
	}
	delete[] images;
}
