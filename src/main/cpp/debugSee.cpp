#include <iostream>
#include <vector>
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"
#include "../../graphic/h/graphic.h"
#include "../../map/h/map.h"
#include "../../objects/h/body.h"
#include "../../objects/h/wall.h"

#define BIGX 400
#define BIGY 400

int main()
{
	Graphic g;
	bool end = false;
	Window w(&g);
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
	map->redraw(&w);
	std::cout << "redrawed";
	std::vector<Skin *> wSkins;
	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wSkins.push_back(new WallSkin("grass",i));
	}
	while (!end)
	{
		if (SDL_WaitEvent(&w.g->event) == 0){w.pop(); break;}
		switch (w.g->event.type)
		{
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
								break;
							}
						case SDLK_b://move bodoy
						{
							map->remove(body);
							map->redraw(&w);
							break;
						}
						case SDLK_w://wall
						{
							Wall * wall= new Wall(wSkins[WallSolidId]);
							wall->setPosition(Position(g.event.motion.x, g.event.motion.y),0);
							std::cout<<"df:" << wall->get_pos();
						//	map->add(wall);
							break;
						}
						case SDLK_p://pushwall
						case SDLK_t://trapwal
						case SDLK_m: //missille
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
