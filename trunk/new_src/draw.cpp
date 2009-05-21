#include <sstream>
#include "draw.h"

static SDL_Surface * g_screen; //TODO! spravit get_functiony, zmena na read_only

void Menu::tapestry()
{
	SDL_Rect rect;
	if (w->background == NULL) {std::cout << "kvjfjbnskb"<<std::endl;return;}
	int i;
	for (i = 0; i < g_screen->h; i+=w->background->h) //tapetujeme pozadie, TODO zmenit na iba raz
	{
		rect.y=i;
		int j;
		for (j =0; j < g_screen->w; j+=w->background->w)
		{
			rect.x=j;
			SDL_BlitSurface(w->background,NULL,g_screen, &rect);
		}
	}
}
Main::Main(Window * w_)
{
	iterator = 0;
	w = w_; //akonahle sa vytvori, tak sa vykresli to, co sa ma
	menus[0] = new Play(w_); //TODO zmenit na add a tak podobne, aby to bolo dynamicke
	menus[1] = new Host(w_);
	menus[2] = new Join(w_);
	menus[3] = new Settings(w_);
	menus[4] = new Create_map(w_);
	}
void Main::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					case SDLK_RETURN:
						{
							w->state.push(menus[iterator]);
							break;
						}
					case SDLK_UP:
						{
							iterator--;
							if (iterator<0) iterator = 4;
							break;
						}
					case SDLK_DOWN:
						{
							iterator++;
							iterator%=NUMBEROFMENUS;
						}
					default:
						break;
				}
				break;
			}
	}
	draw();
}
void Main::draw()
{
	SDL_Rect rect;

	tapestry();
	
	int offset_up = 10;
	rect.y = (g_screen->h + (w->font_size+offset_up)*4)/2;
	rect.x = (g_screen->w)/2 - 15;// TODO zmenit na lepsie
	SDL_Surface* text;
	TTF_SetFontStyle(w->g_font, TTF_STYLE_NORMAL);
	int width;
	
	rect.y = (g_screen->h >> 1) - TTF_FontLineSkip(w->g_font)*2;
	for (int i =0; i< NUMBEROFMENUS; i++)
	{
		TTF_SizeText(w->g_font, menus[i]->name.c_str(),	&width, NULL);
		if (i==iterator)
		{
			text = TTF_RenderText_Solid(w->g_font,menus[i]->name.c_str(), w->light );
		}
		else
		{
			text = TTF_RenderText_Solid(w->g_font,menus[i]->name.c_str(), w->normal );
		}	
		if (text ==NULL) std::cout << " Error rendering text " << TTF_GetError() <<std::endl; //podla mna tu tato podmienka nemusi byt
		rect.x = (g_screen->w >> 1) - (width >> 1);
		if (text ==NULL) std::cout << "IEuhfzeuh:"<<TTF_GetError() <<std::endl;
		SDL_BlitSurface(text, NULL, g_screen, &rect);
		SDL_FreeSurface(text);
		rect.y+=30;
	}
	SDL_Flip(g_screen);
}
Main::~Main()throw ()
{
	for (int i =0; i < NUMBEROFMENUS; i++)
	{
		delete menus[i];
	}
}

Join::Join(Window *w_)
{
	w = w_;
	name = "Join";
}
void Join::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Join::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Join::~Join()throw(){};

Host::Host(Window *w_)
{
	name = "Host";
	w = w_;
}
void Host::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Host::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Host::~Host()throw(){};

Create_map::Create_map(Window *w_)
{
	name = "Create map";
	w = w_;
	map= NULL;
	std::string txt = "Write map resolution:";
	text = TTF_RenderText_Solid(w->g_font,txt.c_str(),w->normal);//resize 2.krat
	TTF_SizeText(w->g_font,txt.c_str(),&text_width,NULL);
	if (text == NULL)  std::cout << "hejdgfjlg";
	std::string s[] = {"0","1","2","3","4","5","6","7","8","9","x"};
	selected = IMG_Load("../images/selected.png");
	if (selected == NULL)
		std::cerr << "uaaaa";
	for (int i =0; i< NUMCHARS; i++)
	{
		resol[i] = TTF_RenderText_Solid(w->g_font,s[i].c_str(),w->normal);
		TTF_SizeText(w->g_font,s[i].c_str(),&resol_width[i],NULL);
	}//TODO! po esc spat na resolution a resize
	
	rects[LEFT].w = rects[RIGHT].w =  15;//15 pixelov, obr neskor
	rects[UP].w = rects[DOWN].w = g_screen->w - rects[LEFT].w - rects[RIGHT].w - rects[CHOOSE].w;
	rects[CHOOSE].w = 2*IMG_WIDTH; //TODO! co aj sa to bude menit? Da sa z SDL_Surface zistit vyska sirka, TODO!
	rects[MAP].w = g_screen->w - rects[CHOOSE].w - rects[LEFT].w - rects[RIGHT].w;
	rects[SAVE].w = rects[GENERATE].w = rects[EXIT].w = g_screen->w /3;
//Mono by si kazda classa mohla precitat svoj vlastny konfigurat, ak nejaky je

	rects[SAVE].h = rects[EXIT].h = rects[GENERATE].h = 30;//TODO!
	rects[CHOOSE].h = g_screen->h - rects[EXIT].h;
	rects[UP].h = rects[DOWN].h = 15; //TODO potom sa to zosti z obrazkov naloadovanych
	rects[LEFT].h = rects[RIGHT].h = g_screen->h - rects[EXIT].h - rects[UP].h - rects[DOWN].h;
	rects[MAP].h = g_screen->h - rects[UP].h - rects[DOWN].h - rects[EXIT].h;

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
	r.x = (g_screen->w >> 1) - (text_width >> 1);
	r.y = (g_screen->h >> 1) - TTF_FontLineSkip(w->g_font)*2;
	SDL_BlitSurface (text, NULL, g_screen, &r);
	r.y+=TTF_FontLineSkip(w->g_font);
	for (unsigned int i = 0; i< written_x.size(); i++)
	{
		SDL_BlitSurface(resol[written_x[i] - '0'], NULL,g_screen, &r);
		r.x+=resol_width[written_x[i] - '0'];//potom to vycentrovat, samostatna funkcia
	}
	SDL_BlitSurface(resol[NUMCHARS - 1], NULL,g_screen, &r);
	r.x+=resol_width[NUMCHARS - 1];//potom to vycentrovat, samostatna funkcia
	for (unsigned int i = 0; i< written_y.size(); i++)
	{
		SDL_BlitSurface(resol[written_y[i] - '0'], NULL,g_screen, &r);
		r.x+=resol_width[written_y[i] - '0'];// TODO potom to vycentrovat, samostatna funkcia
	}
}
int min(int x, int y)
{
	if (x < y) return x;
	return y;
}
void Create_map::draw()
{
	tapestry(); //TODO zmenit tapestry tak, aby sa to v jednom kuse neprekreslovalo
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
		SDL_SetClipRect(g_screen,&rects[MAP]);
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
							SDL_BlitSurface(tiles[i]->show(),NULL,g_screen, &rect); //mutacie vidielny len ten prvy povrch
					}
				}
				else SDL_BlitSurface(tiles[FreeTile]->show(),NULL,g_screen,&rect);
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
		SDL_SetClipRect(g_screen, NULL);
		for (int i =1 ; i< NumberOfWalls_; i++) //bez grass
		{
			SDL_BlitSurface(tiles[i]->show(),NULL,g_screen,&tile_rect[i]);
		}
		if (select < NumberOfWalls_)
		{
			SDL_BlitSurface(selected,NULL,g_screen,&tile_rect[select]);
		}

	}
	SDL_Flip(g_screen);
}
void Create_map::process_resolution()
{
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
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
							if (!x) written_x+=w->event.key.keysym.sym; 
							else written_y+=w->event.key.keysym.sym;
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
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
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
				switch (w->event.button.button)
				{
					case SDL_BUTTON_LEFT:
						{
							mouse_down = true;
							int number = get_rect(w->event.button.x, w->event.button.y,rects,NumberOfMapDivision);
							switch (number)
							{
								case  MAP:{
										  if (select < NumberOfWalls_) //mame nieco vyebrane
										  {
											  int x, y;
											  x = w->event.button.x - rects[MAP].x;
											  y = w->event.button.y - rects[MAP].y;
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
										     int wall = get_rect(w->event.button.x,w->event.button.y, tile_rect, NumberOfWalls_);
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
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}//movement!
	if (set) {
		process_map();
	}
	else 
	{
		process_resolution();
		draw();//TODO opravit iba tu cast screenu, co sa pokazila
	}
}

Create_map::~Create_map()throw(){}; //TODO uvolnovanie premennych

Play::Play(Window *w_)
{
	name = "Play";
	w = w_;
}
void Play::draw()
{
	SDL_Rect r;
	r.x = 100;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Play::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Play::~Play()throw(){};

Settings::Settings(Window *w_)
{
	w = w_;
	name = "Settings";
}
void Settings::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Settings::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Settings::~Settings()throw(){};

Window:: Window()
{
	SDL_Color s = {255,255,255,0};normal =s;
	SDL_Color t = {255,0,0,0};	
	light =t; 
}
void Window::Init_default()
{
	font = DEFAULT_FONT;
	font_size = DEFAULT_FONT_SIZE;
	resolution_width = DEFAULT_WIN_WIDTH;
	resolution_heigth = DEFAULT_WIN_HEIGTH;
	timeout = DEFAULT_TIMEOUT;
	background = IMG_Load(DEFAULT_BACKGROUND);
}
bool Window::Init()
{
	// Inicializace SDL
	if(SDL_Init(SDL_SUBSYSTEMS) == -1)
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Surface* icon=IMG_Load(ICON);
	if (icon!=NULL)
	{
		SDL_WM_SetIcon(icon,NULL);
		SDL_FreeSurface(icon);
	} 

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		std::cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	g_font = TTF_OpenFont(font.c_str(), font_size);
	if(!g_font)
	{
		std::cout << font << std::endl;
		std::cerr << "Unable to open font: " << TTF_GetError() << std::endl;
		return false;
	}	
	g_screen = SDL_SetVideoMode(resolution_width, resolution_heigth, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		std::cerr << "Unable to set video, resolution: " << resolution_width << resolution_heigth << ", " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	//SDL_Rect ** r = SDL_ListModes(g_screen->format,WIN_FLAGS|SDL_FULLSCREEN);
	/*int i =0;
	if (r == NULL ) { std::cout << "awekfgajesgfbewa" <<std::endl; return false;}
	if (r == (SDL_Rect**) -1 ) { std::cout << "mmmmmm" <<std::endl; }
	std::cout << "podoprujem mody fullscreenu: " << std::endl;
	printf("Available Modes\n");
	for (i=0; r[i]; ++i)
		std::cout << r[i]->w << " " <<  r[i]->h << std::endl;*/
	main_menu = new Main(this);
	state.push(main_menu);
	return true;
}

int Window::Toggle_screen()
{
	if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
//		WIN_FLAGS &= !SDL_FULLSCREEN;
	} 
//	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	if( SDL_WM_ToggleFullScreen(g_screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"Nepodarilo zmenit rozlisenie!"<<std::endl;
		SDL_FreeSurface(g_screen);
		return Init();
		}
	return true;
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblazni

unsigned int convert(std::string s)
{
	std::cout << s<< std::endl;
	unsigned number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
}
void Window::set_resolution(std::string res)
{
	unsigned int pos = res.find("x");
	resolution_width = convert(res.substr(0,pos));
	resolution_heigth = convert ( res.substr(pos+1)); //ocheckovat, ci sa to da, ci nemam corrupted file!
}
void Window::set_timeout(std::string time)
{
	timeout = convert(time);
}
void Window::set_font(std::string s)
{
	font = s;
}
void Window::set_font_size(std::string s)
{
	font_size = convert(s);
}
void Window::set_background(std::string res)
{
	background = IMG_Load(res.c_str());
	if (background == NULL) std::cout << "Backgound image not found!" <<std::endl;
}

void Window::Destroy()
{
	// Ak bol nejaky kod, uprace po nom 
	if(g_font != NULL)
	{
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	TTF_Quit();
	SDL_Quit();
	delete main_menu;
}
