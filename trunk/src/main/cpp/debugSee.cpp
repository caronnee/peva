#include "../../graphic/h/graphic.h"
#include "../../map/h/map.h"
#include "../../objects/h/body.h"

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
	Map * map = new Map(Position (200,200), "grass");
	Body * body = new Body();
	body->setSkin(new Skin("dragon",Skin::BotSkin));
	while (true)
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
								break;
							}
							
						case SDLK_x://remove object
						case SDLK_b://move body
						case SDLK_w://wall
						case SDLK_p://pushwall
						case SDLK_t://trapwal
						case SDLK_m: //missille
						default:
							std::cout << "nezname tlacitko u JOINU" << std::endl;
							break;
					}
					break;
				}
		}
	}
	return 0;
}
