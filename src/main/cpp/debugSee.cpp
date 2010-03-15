#include <iostream>
#include <vector>
#include <cmath>
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"
#include "../../graphic/h/graphic.h"
#include "../../map/h/map.h"
#include "../../objects/h/body.h"
#include "../../objects/h/wall.h"
#include "../../objects/h/missille.h"

#define BIGX 400
#define BIGY 400
#define ANGLE 45
#define DISTANCE 300

Graphic g;
Window w(&g);

void redraw(Map * m)
{
	m->redraw(&w);
	SDL_Flip(g.screen);
}
void addToMap(Map * map, Object * object)
{
	Position p;
	SDL_GetMouseState(&p.x, &p.y);
	object->setPosition(p);
	map->add(object);
	//TEST("Na pozicii" << p)
	redraw(map);
}

int main()
{
	bool end = false;
	if (!g.Init())
	{
		g.Destroy();
		return 1;
	}
	Map * map = new Map(Position (BIGX,BIGY), "grass"); //TODO konfigurovat
	map->clean();
	map->setBoundary(min (w.g->screen->w, BIGX), min (w.g->screen->h,BIGY));
	Body * body = new Body();
	body->seer.setEyes(ANGLE,DISTANCE);
	body->setSkin(new Skin("dragon",Skin::BotSkin));
	body->place(map, Position (100,100));
	map->add(body);

	redraw(map);

	std::vector<Skin *> wSkins;
	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wSkins.push_back(new WallSkin("grass",i));
	}
	wSkins.push_back(new MissilleSkin("dragon"));

	while (!end)
	{
		if (body->isMoving())
		{
			body->step(1000);
			body->move();
			redraw(map);
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
									Object * o = map->removeAt(p);
									if ((o!=NULL) && (o!=body))
										delete o;
									redraw(map);
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
									redraw(map);
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
										body->step(0);
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
									addToMap(map,new Wall(wSkins[WallSolidId]));
									break;
								}
							case SDLK_p://pushwall
								{
									addToMap(map,new PushableWall(wSkins[WallPushId]));
									break;
								}
							case SDLK_t://trapwall
								{
									addToMap(map,new TrapWall(wSkins[WallTrapId]));
									break;
								}
							case SDLK_m: //missille
								{
									addToMap(map,new Missille(wSkins.back(),NULL));
									break;
								}
							default:
								std::cout << "Button not recognized" << std::endl;
								break;
						}
						break;
					}
			}
		}
	}
	delete map;
	delete body;
	return 0;
}
