#include <iostream>
#include <vector>
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"
#include "../../graphic/h/graphic.h"
#include "../../map/h/map.h"
#include "../../objects/h/body.h"
#include "../../objects/h/wall.h"
#include "../../objects/h/missille.h"

#define BIGX 400
#define BIGY 400

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
	TEST("Na pozicii" << p)
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
	Map * map = new Map(Position (BIGX,BIGY), "grass");
	map->setBoundary(min (w.g->screen->w, BIGX), min (w.g->screen->h,BIGY));
	Body * body = new Body();
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
		if (SDL_WaitEvent(&g.event) == 0){w.pop(); break;}
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
						case SDLK_b://move bodov
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
	delete map;
	delete body;
	return 0;
}
