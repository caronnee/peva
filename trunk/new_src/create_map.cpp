#include "create_map.h"
#include "help_functions.h"

Create_map::Create_map(Window *w_)
{
	name = "Create map";
	w = w_;
	map= NULL;
	std::string txt = "Write map resolution:";
	text = TTF_RenderText_Solid(w->g->g_font,txt.c_str(),w->g->normal);//resize 2.krat
	TTF_SizeText(w->g->g_font,txt.c_str(),&text_width,NULL);
	if (text == NULL)  std::cout << "hejdgfjlg";
	std::string s[] = {"0","1","2","3","4","5","6","7","8","9","x"};
	selected = IMG_Load("../images/selected.png");
	if (selected == NULL)
		std::cerr << "uaaaa";
	for (int i =0; i< NUMCHARS; i++)
	{
		resol[i] = TTF_RenderText_Solid(w->g->g_font,s[i].c_str(),w->g->normal);
		TTF_SizeText(w->g->g_font,s[i].c_str(),&resol_width[i],NULL);
	}//TODO! po esc spat na resolution a resize
	
	rects[LEFT].w = rects[RIGHT].w =  15;//15 pixelov, obr neskor
	rects[UP].w = rects[DOWN].w = w->g->g_screen->w - rects[LEFT].w - rects[RIGHT].w - rects[CHOOSE].w;
	rects[CHOOSE].w = 2*IMG_WIDTH; //TODO! co aj sa to bude menit? Da sa z SDL_Surface zistit vyska sirka, TODO!
	rects[MAP].w = w->g->g_screen->w - rects[CHOOSE].w - rects[LEFT].w - rects[RIGHT].w;
	rects[SAVE].w = rects[GENERATE].w = rects[EXIT].w = w->g->g_screen->w /3;
//Mono by si kazda classa mohla precitat svoj vlastny konfigurat, ak nejaky je

	rects[SAVE].h = rects[EXIT].h = rects[GENERATE].h = 30;//TODO!
	rects[CHOOSE].h = w->g->g_screen->h - rects[EXIT].h;
	rects[UP].h = rects[DOWN].h = 15; //TODO potom sa to zosti z obrazkov naloadovanych
	rects[LEFT].h = rects[RIGHT].h = w->g->g_screen->h - rects[EXIT].h - rects[UP].h - rects[DOWN].h;
	rects[MAP].h = w->g->g_screen->h - rects[UP].h - rects[DOWN].h - rects[EXIT].h;

	rects[LEFT].x = rects[SAVE].x = 0;
	rects[UP].x = rects[DOWN].x = rects[LEFT].w;
	rects[MAP].x = rects[LEFT].x + rects[LEFT].w;
	rects[RIGHT].x = rects[MAP].x + rects[MAP].w;
	rects[CHOOSE].x = rects[RIGHT].x + rects[RIGHT].w;
	rects[GENERATE].x = rects[SAVE].x + rects[SAVE].w; //na jednej urovni
	rects[EXIT].x = rects[GENERATE].x + rects[GENERATE].w;

	rects[UP].y = 0;
	rects[CHOOSE].y = 0; 
	rects[MAP].y = rects[LEFT].y = rects[RIGHT].y = rects[UP].h;
	rects[DOWN].y = rects[MAP].y+rects[MAP].h;
	rects[EXIT].y = rects[SAVE].y = rects[GENERATE].y = rects[DOWN].y + rects[DOWN].h;

	tiles[FreeTile] = new Tile();
	tiles[SolidWall_] = new SolidWall();
	tiles[TrapWall_] = new TrapWall();
	tiles[PushableWall_] = new PushableWall();
	tiles[ExitWall_] = new ExitWall();
	int pom = rects[CHOOSE].y + IMG_HEIGHT/2;
	for (int i =1; i< NumberOfWalls_; i++)
	{
		tile_rect[i].x = rects[CHOOSE].x+ IMG_WIDTH/2;
		tile_rect[i].y = pom;
		pom+=3*IMG_HEIGHT/2; //TODO konstanta
	}
	//vygnerujeme mapove s tym, ze prva rada a prvy stlpec nevykresluju nic	
	reset();
}
int Create_map::get_rect(int x, int y,SDL_Rect * r, int max)
{
	int i;
	for (i = 0; i < max; i++)
	{
		if ((x >=r[i].x) 
		&& (x< r[i].x + r[i].w)
		&& (y >= r[i].y)
		&& (y < r[i].y + r[i].h))
			return i;
	}
	std::cout <<x << " medzi " << rects[UP].x << " " <<rects[UP].x + rects[UP].w << " " << std::endl;
	std::cout <<y << " medzi " << rects[UP].y << " " <<rects[UP].y + rects[UP].h << " " << std::endl;
	return i;
}
void Create_map::reset()
{
	set = false;
	x = false;
	select = NumberOfWalls_;
	mouse_down = false;
	written_x = "";
	written_y = "";
	if (map!=NULL)
	{
		for (int i =0; i< resolX; i++)
			delete map[i];
		delete[] map; //TODO ocheckovat!
	}
	map = NULL;
	begin_x = 0;
	begin_y = 0;
	window_begin_x = rects[MAP].x;
	window_begin_y = rects[MAP].y;
}
void Create_map::draw_resol()
{
	SDL_Rect r;
	r.x = (w->g->g_screen->w >> 1) - (text_width >> 1);
	r.y = (w->g->g_screen->h >> 1) - TTF_FontLineSkip(w->g->g_font)*2;
	SDL_BlitSurface (text, NULL, w->g->g_screen, &r);
	r.y+=TTF_FontLineSkip(w->g->g_font);
	for (unsigned int i = 0; i< written_x.size(); i++)
	{
		SDL_BlitSurface(resol[written_x[i] - '0'], NULL,w->g->g_screen, &r);
		r.x+=resol_width[written_x[i] - '0'];//potom to vycentrovat, samostatna funkcia
	}
	SDL_BlitSurface(resol[NUMCHARS - 1], NULL,w->g->g_screen, &r);
	r.x+=resol_width[NUMCHARS - 1];//potom to vycentrovat, samostatna funkcia
	for (unsigned int i = 0; i< written_y.size(); i++)
	{
		SDL_BlitSurface(resol[written_y[i] - '0'], NULL,w->g->g_screen, &r);
		r.x+=resol_width[written_y[i] - '0'];// TODO potom to vycentrovat, samostatna funkcia
	}
}
void Create_map::draw()
{
	w->tapestry(); //TODO zmenit tapestry tak, aby sa to v jednom kuse neprekreslovalo
	if (set == false)
	{
		draw_resol();
	}
	else
	{
		//TODO vysvietit tu, o sa ma zmazat/ zmaze sa to procese klikom lavym tlacitkom
		//nakresli pole
		//TODO ukazat uzivatelovi, ze je uz na hranici a nikam dalej to nepojde
		int max_width = rects[MAP].x + min(rects[MAP].w,IMG_WIDTH*resolX);
		int max_heigth = rects[MAP].y + min(rects[MAP].h, IMG_HEIGHT*resolY);
		SDL_SetClipRect(w->g->g_screen,&rects[MAP]);
		SDL_Rect rect;//TODO dokreslit sipky
		rect.x = window_begin_x;
		rect.y = window_begin_y; //od jakeho pixelu mame zacinat
		int tile_x = begin_x; //jake x-ove sa vykresli
		int tile_y = begin_y;
		while (rect.y < max_heigth)
		{
			while (rect.x < max_width)
			{
				if (map[tile_x][tile_y]!=FreeTile)
				{
					for (int i = 0; i < NumberOfWalls_; i++)
					{
						if (map[tile_x][tile_y] & (1<<i))
							SDL_BlitSurface(tiles[i]->show(),NULL,w->g->g_screen, &rect); //mutacie vidielny len ten prvy povrch
					}
				}
				else SDL_BlitSurface(tiles[FreeTile]->show(),NULL,w->g->g_screen,&rect);
				rect.x+=IMG_WIDTH;
				tile_x++;
				if (tile_x == resolX)
					break;
			}
			rect.x = window_begin_x;
			rect.y += IMG_HEIGHT;
			tile_y++;
			if (tile_y == resolY)
				break;
			tile_x = begin_x;
		}
		//dokreslime panel
		SDL_SetClipRect(w->g->g_screen, NULL);
		for (int i =1 ; i< NumberOfWalls_; i++) //bez grass
		{
			SDL_BlitSurface(tiles[i]->show(),NULL,w->g->g_screen,&tile_rect[i]);
		}
		if (select < NumberOfWalls_)
		{
			SDL_BlitSurface(selected,NULL,w->g->g_screen,&tile_rect[select]);
		}

	}
	SDL_Flip(w->g->g_screen);
}
void Create_map::process_resolution()
{
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_0: 
					case SDLK_1: 
					case SDLK_2: 
					case SDLK_3: 
					case SDLK_4: 
					case SDLK_5: 
					case SDLK_6: 
					case SDLK_7: 
					case SDLK_8: 
					case SDLK_9: 
						{
							if (!x) written_x+=w->g->event.key.keysym.sym; 
							else written_y+=w->g->event.key.keysym.sym;
							break;
						}
					case SDLK_BACKSPACE:
						{
							if ((!x)&&(written_x.length())) written_x.erase(written_x.length()-1,1);
							if (x && (written_y.length())) written_y.erase(written_y.length()-1,1);

							break;
						}
					case SDLK_RETURN: 
						{ 
							set = true;
							resolX = convert(written_x);
							resolY = convert(written_y);//TODO skontrolovat rozmedzie, 10 <MUST_BE < 100000, prazdne riadku checkovat
							map = new unsigned int*[resolX];
							for (int i =0; i< resolX; i++)
							{
								map[i] = new unsigned int[resolY];//TODO checking memory
								for (int j = 0; j < resolY; j++)
									map[i][j] = 0;//nic tam zatial nie je
							} //TODO cetrovanie
							break; 
						}
					case SDLK_RIGHT:
					case SDLK_x: { x = true; break;}
					case SDLK_LEFT:{x = false;break;}
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							reset();
							w->state.pop();
							break;
						}
					default:
						std::cout << "Unknown command (Create map)" << std::endl;
						break;
				}
				break;
			}
	}
}

void Create_map::process_map()
{
	//TODO if SLD_KEY PRESSED, do last action
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						     {
							     reset();
							     w->state.pop();
							     break;
						     }
					default:
						std::cout << "Unknown command (Create map)" << std::endl;
						break;

				}
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			{
				switch (w->g->event.button.button)
				{
					case SDL_BUTTON_LEFT:
						{
							mouse_down = true;
							int number = get_rect(w->g->event.button.x, w->g->event.button.y,rects,NumberOfMapDivision);
							switch (number)
							{
								case  MAP:{
										  if (select < NumberOfWalls_) //mame nieco vyebrane
										  {
											  int x, y;
											  x = w->g->event.button.x - rects[MAP].x;
											  y = w->g->event.button.y - rects[MAP].y;
											  if((begin_x + x/IMG_WIDTH >= resolX)|| (begin_y + y/IMG_HEIGHT >= resolY))
												  return;
											  map[begin_x + x/IMG_WIDTH][begin_y + y/IMG_HEIGHT] |= (1 << select);
											  draw();
										  }
										  break;
									  }
								case  SAVE:{std::cout << "save" <<std::endl;
										   break;}
								case  GENERATE:{std::cout << "generate" <<std::endl;
										  break;}
								case  EXIT:{std::cout << "exit" <<std::endl;
										  break;}
								case  CHOOSE:{std::cout << "choose" <<std::endl;
										     int wall = get_rect(w->g->event.button.x,w->g->event.button.y, tile_rect, NumberOfWalls_);
										     switch (wall)
										     {
											     case SolidWall_:
												     std::cout << "S";
												     break;
											     case ExitWall_: std::cout<< "E";
													break;
											     case PushableWall_: std::cout << "pushable";
														break;
											     case TrapWall_: std::cout <<"T";
													     break;
											     default: std::cout << "ble!";
										     }
										     if (wall < NumberOfWalls_)
										     {
											    select = wall;
										     }
										     draw();
										  break;}
								case  LEFT:{ begin_x--; 
										   if (begin_x < 0) begin_x = 0;
										   draw();
										  break;}
								case  UP:{ begin_y--;
										 if (begin_y < 0) begin_y = 0;
										   draw();
										  break;}
								case  DOWN:{begin_y++;
										   if (begin_y + rects[MAP].h/IMG_HEIGHT > resolY )
											   begin_y--;
										   draw();
										  break;}
								case  RIGHT:{begin_x++;
										    if (begin_x > resolX - rects[MAP].w/IMG_WIDTH)
											    begin_x--;
										   draw();
										  break;}
								default: std::cout  << "HE?" << std::endl;
							}
							break;
						}
					default:
						break;
				}
			}
		case SDL_MOUSEBUTTONUP:
			{
				mouse_down = false; //POZOR na to, ze to moze byt aj iny button!
			}
		case SDL_MOUSEMOTION: //ina ak je stale pressed
			{
				//stejna fcia
				break;
			}
	}
}

void Create_map::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}//movement!
	if (set) {
		process_map();
	}
	else 
	{
		process_resolution();
		draw();//TODO opravit iba tu cast screenu, co sa pokazila
	}
}

Create_map::~Create_map()throw()
{
} //TODO uvolnovanie premennych
