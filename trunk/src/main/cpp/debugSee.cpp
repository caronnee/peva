#include <iostream>
#include <vector>
#include <cmath>
#include "../../graphic/h/window.h"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"
#include "../../map/h/map.h"
#include "../../objects/h/body.h"
#include "../../objects/h/wall.h"
#include "../../objects/h/missille.h"

#define BIGX g.screen->w
#define BIGY g.screen->h
#define ANGLE 45
#define DISTANCE 300
#define X 100
#define Y 100

enum Params
{
	ParamX =0,
	ParamY,
	ParamAngle,
	ParamDistance
};

Graphic g;
Window w(&g);

void redraw(Map * m)
{
	m->redraw(w.g);
	SDL_Flip(g.screen);
}
void addToMap(Map * map, Object * object)
{
	Position p;
	SDL_GetMouseState(&p.x, &p.y);
	object->setPosition(p);
	map->add(object);
	redraw(map);
}

int main(int argc, char ** args)
{
	bool end = false;
	int params[] = { X, Y, ANGLE, DISTANCE };
	for (int i =1; i< argc; i++)
	{
		params[i-1] = convert<int>(args[i]);
	}
	if (!g.Init())
	{
		g.Destroy();
		return 1;
	}
	Map * map = new Map(Position (BIGX, BIGY), "grass"); //TODO konfigurovat
	map->clean();
	map->setBoundary(min (w.g->screen->w, BIGX), min (w.g->screen->h,BIGY));
	Body * body = new Body();
	body->seer.setEyes(params[ParamAngle], params[ParamDistance]);
	body->setSkin(new BotSkin("dragon"));
	body->place(map, Position (params[ParamX],params[ParamY]));
	map->add(body);

	redraw(map);

	std::vector<Skin *> wSkins;
	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wSkins.push_back(new WallSkin("grass",i));
	}
	wSkins.push_back(new MissilleSkin("dragon"));
	Position t;
	t.x = body->collisionSize().x + body->collisionSize().width;
	t.y = body->collisionSize().y + body->collisionSize().height;
	t.x = BIGX - t.x;
	t.y = BIGY - t.y;
	while (!end)
	{
		map->updateScreen(w.g);
		if (body->isMoving())
		{
			body->step(1000);
			body->move(map->ticks);
			Position p = body->get_pos();
			if (p.x <0)
				body->place(map, Position(0,body->get_pos().y), body->getAngle());
			if (p.y <0)
				body->place(map, Position(body->get_pos().x,0), body->getAngle());
			if (p.x > t.x)
				body->place(map, Position(t.x,body->get_pos().y), body->getAngle());
			if (p.y > t.y)
				body->place(map, Position(body->get_pos().x,t.y), body->getAngle());

//			map->update(body, w.g); //strati sa neskor
		}
		while (SDL_PollEvent(&g.event)){
			switch (w.g->event.type)
			{
				case SDL_QUIT:
					{
						end = true;
						break;
					}
				case SDL_KEYDOWN:
					{
						switch(w.g->event.key.keysym.sym)
						{
							case SDLK_q:
							case SDLK_ESCAPE:
								{
									end = true;
									break;
								}
							case SDLK_x://remove object
								{
									Position p;
									SDL_GetMouseState(&p.x, &p.y);
									Object * o = map->removeShow(p,false, w.g);
									if ((o!=NULL) && (o!=body))
										delete o;
									break;
								}
							case SDLK_f: //ako follow sipku
								{
									Position p;
									SDL_GetMouseState(&p.x, &p.y);
									int angle= Seer::getDegree(body, p);
									p.substractVector(body->get_pos());
									p.x -= body->collisionSize().x + body->collisionSize().width/2;
									p.y -= body->collisionSize().y + body->collisionSize().height/2;
									//FIXME
									//zistime kvadrant, 0,1,2,3, vzhladom na suradnice
									int kvadr = 0;
									if (p.y * p.x < 0)
										kvadr = 1;
									if (p.y < 0)
										kvadr |= 2;
									if (p.y != 0)
										angle =atan((float)p.y/p.x)*180/PI;
									if (kvadr &1)
										angle+=90;
									angle += 90*kvadr;
									body->absoluteTurn(angle);
//									map->update(body, w.g);
									break;
								}
							case SDLK_s:
								{
									body->see();
									body->seer.output();
									break;
								}

							case SDLK_SPACE:
								{
									if (body->isMoving())
									{
										body->step(0);
										body->move(map->ticks);
									}
									else
										body->step(10);
									map->remove(body);
									map->add(body);
									break;
								} 
							case SDLK_b://move body
								{
									map->remove(body);
									addToMap(map, body);
									redraw(map);
									break;
								}
							case SDLK_w://wall
								{
									addToMap(map,new Wall(wSkins[WallSolidId],NULL));
									break;
								}
							case SDLK_p://pushwall
								{
									addToMap(map,new PushableWall(wSkins[WallPushId],NULL));
									break;
								}
							case SDLK_t://trapwall
								{
									addToMap(map,new TrapWall(wSkins[WallTrapId],NULL));
									break;
								}
							case SDLK_m: //missille
								{
									addToMap(map,new Missille(wSkins.back(),NULL));
									break;
								}
							default:
								TEST("Button not recognized" )
								break;
						}
						break;
					}
			}
		}
	}
	map->remove(body);
	delete map;
	delete body;
	return 0;
}
