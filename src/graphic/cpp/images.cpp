#include "../h/images.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <fstream>

#define TICKS 100
#define BORED_AFTER 100

namespace bf = boost::filesystem;

std::string toLoadBot[] = { "default.png", "sleep.png", "walk.png", "attack.png", "hit.png", "dead.png", "deadBody.png" };
std::string toLoadMissille[] = {"missille.png"};

//TODO akonsa steny rozbijaju
std::string toLoadMap[] = {	"Free.png","SolidWall.png", "PushableWall.png", "TrapWall.png", 
			    	"BreakableWall.png", "StartWall.png", "Target.png", "selected.png"};

Skin::Skin()
{
	images = NULL;
	directory = "./";
}

BotSkin::BotSkin(std::string name)
{
	nameOfSet = name;
	std::string * load;
	directory = "./botSkins/";
	load = toLoadBot;
	size = NumberOfActions;
	images = new SDL_Surface *[size];
	create(load, name, size);	
}
void Skin::create(std::string * load, std::string name, int sizeLoaded)
{
	for (size_t i  = 0; i< size; i++)
	{
		images[i] = NULL;
	}
	if (!bf::exists(directory + name))
	{
		throw "Directory " + directory + name + " not found!";
	}
	directory = directory + name + '/';
	for (int i = 0; i<sizeLoaded; i++ )
		images[i] = IMG_Load((directory + load[i]).c_str());

	for (size_t i  = 1; i<size; i++) //action default tam musi byt v kazdom pripade, TODO doplnit
	{
		if (images[i] == NULL)
			images[i] = IMG_Load((directory + load[0]).c_str()); //aby sa dalo pouzit free
	}
	for(size_t i =0; i<size; i++)
		if(images[i] == NULL)
			throw "Images of type " + directory + "not found!";
	if (!bf::exists(directory + "config"))
	{
		begin_in_picture.x = 0;
		begin_in_picture.y = 0;
		shift.x = images[0]->h;
		shift.y = images[0]->w;
		imageSize.x = images[0]->w; //predpokladame, ze su vsetky rovnakej velkosti
		imageSize.y = images[0]->h;
		return; 
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
MissilleSkin::MissilleSkin(std::string name)
{
	std::string * load;
	directory = "./botSkins/";
	load = toLoadMissille;
	size = NumberOfActions;
	images = new SDL_Surface *[NumberOfActions];

	create(load, name,1);

	begin_in_picture.x = 0;
	begin_in_picture.y = 0;
	shift.x = images[0]->w;
	shift.y = images[0]->w;
	imageSize.x = imageSize.y = images[0]->w; //strely su stvorcove
}
WallSkin::WallSkin(std::string name, size_t wall)
{
	nameOfSet = name;
	directory = "./mapSkins/" + name + "/";
	if (!bf::exists(directory))
	{
		TEST("Nonexistent maps!");//TODO vynimka
		return;
	}
	size = NumberOfActions;
	images = new SDL_Surface *[size];
	//TODO zatial, pridat sleep veci a pod.
	for (size_t i  = 0; i< size; i++)
	{
		images[i] = IMG_Load((directory +toLoadMap[wall]).c_str());
	}//TODO skonsolidovat
	for (size_t i  = 0; i< size; i++)
		if (!images[i])
			throw "Image " +toLoadMap[wall] + " at " + directory + " not found!" + directory +toLoadMap[wall];
	
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
	imageCut.x = skin->get_begin().x;
	imageCut.y = skin->get_begin().y;
	imageCut.width = skin->get_size().x;
	imageCut.height = skin->get_size().y;
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
	Uint32 t = SDL_GetTicks();
	if (t - lastUpdate > TICKS)
		{
			rect.x +=  s->get_shift().x;
			lastUpdate = SDL_GetTicks();
		}
	if (rect.x >=  s->get_surface(states[state.top()])->w)
	{
		rect.x = 0;
		if (state.top()  ==  StateTemporarily)
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
	//rect.x = 0; //zakomentovane pre debugSee
	if (index<state.top())
	{
		//zarad to pod aktual
		States s = state.top();
		removeState();
		switch_state(s,states[s]);
		state.push(index);
		index = s;
	}
	if (state.top() != index)
		state.push(index); //neocitnu sa dve stavy vedla seba, ani perman.
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
Skin * ImageSkinWork::getSkin()const
{
	return s;
}
/*size_t ImageSkinWork::width() //bude sa pytat kvoli kolizii
{
	return s->get_size().x;
}
size_t ImageSkinWork::height() //bude sa pytat kvoli kolizii
{
	return s->get_size().y;
}*/
Rectangle ImageSkinWork::getCollissionRectagle() const
{
	return imageCut;
}
/*Position ImageSkinWork::get_begin() const
{
	return s->get_begin();
}
Position ImageSkinWork::get_size()
{
	return s->get_size();
}*/

float ImageSkinWork::turn(int degree, int shift)//nastavi uhol na degree, ak je nula, tak na lezato
{
	count = 0;
	states[StateDefault] = ActionDefault;
	size_t directions = get_image()->h / s->get_shift().y;
	//how much of angle can one image represent
	float dirShift = 360 / directions;
	//which image should we use
	int sh = (degree + dirShift/2) / dirShift + shift;
	rect.y = sh*s->get_shift().y;
	rect.y %=  get_image()->h;
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
			p.x +=  (dir%oneSide)*add*s->get_shift().x;
			break;
		}
		case 1:
		{
			p.x +=  s->get_shift().x;
			p.y +=  (dir%oneSide)*add*s->get_shift().y;
			break;
		}
		case 2:
		{
			p.x +=  ( oneSide - dir % oneSide )*add*s->get_shift().x;
			p.y +=  s->get_shift().y;
			break;
		}
		case 3:
		{
			p.y +=  (oneSide - dir % oneSide )* add * s->get_shift().y;
			break;
		}
	}
	return p;
}
/*std::string ImageSkinWork::name()
{
	return s->nameOfSet;
}*/
