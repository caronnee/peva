#include <libxml/parser.h>
#include <libxml/tree.h>
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

	info = "Zadajte meno suboru";
	info_width;
	TTF_SizeText(w->g->g_font,info.c_str(),&info_width,NULL); 
	info_o = TTF_RenderText_Solid(w->g->g_font,info.c_str(), w->g->normal);//TODO prehodit do kontruktora

	file_r.y = w->g->g_screen-> h/2 - 2*TTF_FontLineSkip(w->g->g_font);
	file_r.x = w->g->g_screen->w /2 - info_width/2;
	file_r.w = info_width+20;
	file_r.h = 3*TTF_FontLineSkip(w->g->g_font);

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
	state = RESOLUTION;
	file_name = "";
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
	if (state == RESOLUTION)
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
							state = DRAW;
							resolX = convert<int>(written_x);
							resolY = convert<int>(written_y);//TODO skontrolovat rozmedzie, 10 <MUST_BE < 100000, prazdne riadku checkovat
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
bool Create_map::save() // vracia ci sa podarilo zapamatat do suboru alebo nie
{
	//TODO uistit sa, ze to podpurujeme, ak nie, iny format (napriklad cisto textovy, fuj!:)
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc (BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,BAD_CAST "map");
	xmlDocSetRootElement(doc, root_node);

	xmlNewProp(root_node, BAD_CAST "width", BAD_CAST written_x.c_str());
	xmlNewProp(root_node, BAD_CAST "heigth", BAD_CAST written_y.c_str());

	int x = 0, y = 0;
	int write_x, write_y;
	bool found = false;
	xmlNodePtr tile = NULL;
	xmlNodePtr line = NULL;
	std::string walls[] = {"FreeTile","Solid Wall","Pushable Wall","Trap Wall","Exit"};//TODO dat to do statit niekam medzi walls
	int from,to;
	for (int i = 1; i< NumberOfWalls_; i++)
	{
		int wall = 1 << i;
		tile = xmlNewChild(root_node,NULL,BAD_CAST walls[i].c_str(),NULL);
		for (y = 0; y < resolY; y++)
		{
			for (x = 0; x < resolX; x++)
			{
				if ((map[x][y] & wall)&&(!found)) //prva najdena
				{
					from = x;
					found = true;
				}
				if ((!(map[x][y]&wall)) && (found))
				{
					if (line == NULL) //ak sme este nic nenasli, privesim line
					{
						std::string l= "line" + deconvert<int>(y);
						line = xmlNewChild(tile,NULL,BAD_CAST l.c_str(),NULL);
					}
					xmlNodePtr n;
					std::string range = deconvert<int>(from) + "-"+ deconvert<int>(x);
					n = xmlNewChild(line,NULL,BAD_CAST "range",BAD_CAST range.c_str());
					found = false;
				}
			}
			line = NULL;
		}
	}


	xmlSaveFormatFileEnc(file_name.c_str(),doc, "UTF-8",1);

	xmlFreeDoc(doc);
	xmlCleanupParser();
	return true; //TODO checkovanie, ci sa to podarilo
}
void Create_map::generuj(Position resolution)
{
	//zaplnime to solidnymi stenami vsetko
	int exits = 0;//musi byt aspon jeden exit
	for (int i = 0; i < width; i++)
		for (int j = 0; j < heigth; j++)
			map[i][j] = SolidWall_;
	//vypocitaj, kolko hadov by sa na to hodilo
	Snakes snake(resolution);//automaticky random x,y zaciatok, vitality 
	//zivotnost, to, ze existuje cesta k cielu sa vygeneruje jednoducho, iba vedla zozratych stien sa generuju exity
	Position p1,p2,n; //normal
	//Snake je normalny had, Snakes je list hadov
	while(!snake.empty())
	{
		p1 = p2 = snake.location();
		n.x = snake.direction().y;
		n.y = snake.direction().y * (-1); //normala
		int type = srand()%(2*NumberOfWalls_);
		for (int i =0; i< snake.robust(); i++)
		{
			map[p1.x][p1.y] = FreeTile;
			map[p2.x][p2.y] = FreeTile;
			p1+=n;
			p2-=n;
			p1.clip(resolution);
			p2.clip(resolution);
		}
		if (type < NumberOfWalls_)
		{	
			int where = srand()%3;
			if ((where & 2) && (map[p1.x][p1.y]!=FreeTile))
			{
				map[p1.x][p1.y] &= ~(1 << type);
				map[p1.x][p1.y] |= 1 << type;
			}
			if ((where & 1) && (map[p2.x][p2.y]!=FreeTile))
			{
				map[p2.x][p2.y] &= ~(1 << SolidWall_);
				map[p2.x][p2.y] |= 1 << type;
			}
		}
		snake.pohyb();//ak sa v pohne x_krat, vytvor dalsieho mensieho
	}
}
void Create_map::saving()
{
	//napis do stredu vyzvus menom, meno nesmie byt viac ako povedzme 8 pismen
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				Uint16 znak = w->g->event.key.keysym.unicode;
				switch(znak)
				{
					case SDLK_ESCAPE:
						{
							reset();
							w->state.pop();
							break;
						}
					case SDLK_RETURN:
						{
							if (!save())
								do 
									SDL_WaitEvent(&w->g->event); //TODO vyhruzny napis!
								while (w->g->event.type != SDL_KEYDOWN);
							reset();
							w->state.pop();
							break;
						}
					default:
						{
							std::string temp;
							if (znak!=0)
								file_name+=(char) w->g->event.key.keysym.unicode; //TODO zistit ako funuje unicode
							if (temp==file_name)
							{
								break;
							}

							SDL_Surface *s = TTF_RenderText_Solid(w->g->g_font,file_name.c_str(),w->g->normal);
							if (s == NULL)
								std::cout << "something's reeealy realy wrong" <<std::endl;
							SDL_Rect r = file_r;
							r.y+=TTF_FontLineSkip(w->g->g_font);
							SDL_BlitSurface(s, NULL, w->g->g_screen, &r);
							SDL_Flip(w->g->g_screen);
							std::cout << "blitted" <<std::endl;
							SDL_FreeSurface(s);
							break;
						}
				}
				break;
			}
		case SDL_QUIT:
			{
				while(!w->state.empty())
					w->state.pop();
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
										   SDL_Rect r = file_r;
										   SDL_FillRect(w->g->g_screen, &r,0);
										   r.x+=10;
										   SDL_BlitSurface(info_o,NULL,w->g->g_screen,&r);
										   SDL_Flip(w->g->g_screen);
										   state = SAVING;
										   break;
									   }
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
	if (state == DRAW) {
		process_map();
		return;
	}
	if (state == RESOLUTION)
	{
		process_resolution();
		draw();//TODO opravit iba tu cast screenu, co sa pokazila
		return;
	}
	if (state == SAVING)
	{
		std::cout << "start saving function" << std::endl;
		saving();
	}
}

Create_map::~Create_map()throw()
{
} //TODO uvolnovanie premennych
