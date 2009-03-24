#ifndef UZ_NALOADOVANE_STENY
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "strela.h"

#define STENA 1
#define BOT 2
#define NIC 0
#define STRELA 3
#define UZ_NALOADOVANE_STENY "ok"

//este jedna dedickost, aby som nemusela pisat furt acvtive

//stenamultiple? Rozprasi jedneho robota na niekolko ciastok, vsetky aktivne:P
class AbstractSteny
{
protected:	
	int x,y;//sucasne pozicie steny	
public:
	SDL_Surface* stena;	
	int active;//keby som sa nahodou chcela zblaznit z dlazdiciek,aby som mohla menit sdl_surface
	virtual void action(AbstractSteny***,int,int);//bud sa zrusi nacas,premiestni na volne miesto,
	//ak je na jej mieste strela,potom nieco,teleport na volne miest
	AbstractSteny();
	SDL_Surface* image();	
};
class StenaNic:public AbstractSteny
{
public:
	void action(AbstractSteny***,int,int);
	StenaNic(int x_,int y_);
};
class StenaMizne:public AbstractSteny
{
	SDL_Surface* stena2;
public:
	void action(AbstractSteny***,int,int);
	StenaMizne(int,int);
};
class StenaPresuva:public AbstractSteny
{
public:
	void action(AbstractSteny***,int,int);
	StenaPresuva(int,int);
};
/*class StenaTeleportuje:public AbstractSteny
{
public:
	void action(AbstractSteny**);
	StenaTeleportuje();
}*/
class StenaHybe:public AbstractSteny
{
public:
	void action(AbstractSteny***,int,int);
	StenaHybe(int,int);
};
class StenaSolid:public AbstractSteny
{
public:
	void action(AbstractSteny***,int,int);
	StenaSolid(int,int);
};
#endif

