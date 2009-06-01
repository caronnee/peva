#include "generuj.h"
#include <vector>
#include "bots.h"

using namespace std;
#define SDL_SUBSYSTEMS SDL_INIT_VIDEO
#define WIN_WIDTH 500
#define WIN_HEIGHT 480
#define WIN_BPP 0
#define WIN_TITLE "Codewars"
#define	IMG_WIDTH 50
#define	IMG_HEIGHT 50
#define PAUSE 1
#define POKRACUJ 0
#define KONIEC 2
#define IMG_WIDTH 50
#define IMG_HEIGHT 50

Uint32 WIN_FLAGS = SDL_HWSURFACE|SDL_RESIZABLE;
bool Init();				// Inicializace
void Destroy();				// Deinicializace
void pohyb_bot();
/*
 * Globalni promenne
 */

SDL_Surface *g_screen;		// Surface aktualneho okna, pri prepnuti sa bue nicit a znovu rekreovat
TTF_Font *g_font;		// Font
SDL_Event event; //event
int xx=0,yy=0;
int rozdielX,rozdielY;
AbstractSteny***pole=NULL; ///samostatna trieda, ktora obsahuje pole, steny, ukazovatele na boto botov,strely
vector<Bot> boti; //ukazovatele na botov, aby bolo mozne pouzit uz rozna blastnosti

/*
 * Inicializacni funkce
 */

bool Init()
{
	// Inicializace SDL
	if(SDL_Init(SDL_SUBSYSTEMS) == -1)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n",
				SDL_GetError());
		return false;
	}
	SDL_Surface* icon=IMG_Load("./images/icon.png");
	if (icon!=NULL)
	{
		SDL_WM_SetIcon(icon,NULL);
		SDL_FreeSurface(icon);
	}

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
		return false;
	}
	g_font = TTF_OpenFont("./fonts/sfd/DejaVuSansCondensed.ttf", 16);
	if(!g_font)
	{
		printf("Unable to open font: %s\n", TTF_GetError());
		return false;
	}	
	g_screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		fprintf(stderr, "Unable to set %dx%d video: %s\n",
				WIN_WIDTH, WIN_HEIGHT, SDL_GetError());
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	return true;
}
/*
 * Toggle funkcia na preskakovanie z obrazu
 */
int Toggle_screen()
{
	if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
		WIN_FLAGS &= ~SDL_FULLSCREEN;
	} 
	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	if( SDL_WM_ToggleFullScreen(g_screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"nepodarilo zmenit rozlisenie, rekreujem"<<std::endl;
		SDL_FreeSurface(g_screen);
		Init();
		}
};


/*
 * Deinicializacni funkce
 */

void Destroy()
{
	// Smaze font a uklidi po SDL_ttf
	if(g_font != NULL)
	{
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	TTF_Quit();
	SDL_Quit();
}
void Draw()//mame globalbe xx,yy, vymalujeme len to,AbstractSteny***p,SDL_Surface* okno netreba, pretoze ich mame global
{
	//SDL_Surface* img= IMG_Load("./images/Fade.png");
	SDL_Rect stvorec;
	stvorec.h=IMG_HEIGHT;//velkost obrazkov
	stvorec.w=IMG_WIDTH;	
	//najprv vykresli vsetkych botov,potom tak pridaj steny
	for(vector<Bot>::iterator iter=boti.begin();iter!=boti.end();iter++)
	{//ak je miesto bota v obrazku, tak ho potom vykresli a zapracuj	
		if (((stvorec.x=iter->position.first*IMG_WIDTH-xx)>=0) &&((stvorec.y=iter->position.second*IMG_HEIGHT-yy) >=0)&&
			stvorec.x<g_screen->w&&stvorec.y<g_screen->h)
		{
			SDL_BlitSurface(iter->obr[iter->seeposition],NULL,g_screen,&stvorec);
			SDL_UpdateRect(g_screen,stvorec.x,stvorec.y,stvorec.w,stvorec.h);			
			//iter->run(pole);			
		}
		/*do SDL_WaitEvent(&event);
		while (event.type!=SDL_KEYDOWN);*/
	}
	stvorec.x=0;//xx je uz v poriadku, ale pre istoty to tam treba checknut
	stvorec.y=0;//yy same
	int povI;
	int i=xx/IMG_WIDTH;
	povI=i;
	int j=yy/IMG_HEIGHT;
	while(stvorec.y < SDL_GetVideoSurface()->h&&j<100)	//konstanta!
	{
		while(stvorec.x<SDL_GetVideoSurface()->w&&i<100)
		{
			if (pole[i][j]->active!=BOT)
			{
			SDL_BlitSurface(pole[i][j]->stena,NULL,g_screen,&stvorec);			
			SDL_UpdateRect(g_screen,stvorec.x,stvorec.y,stvorec.w,stvorec.h);			
			}
			stvorec.x+=IMG_WIDTH;
			i++;
		}
		i=povI;
		stvorec.x=0;
		stvorec.y+=IMG_HEIGHT;//konstanta
		j++;
	}
	SDL_Delay(500);
}
void init(AbstractSteny***p,int max_x,int max_y)
{	
	p=generuj();
}
int uzivatel()
{		
	while(SDL_PollEvent(&event))
	{
		if ( event.type == SDL_QUIT )  {  return KONIEC;  }
		if (event.type == SDL_KEYDOWN )
		{
			switch (event.key.keysym.sym)
			{
			case SDL_QUIT:
			case SDLK_ESCAPE: 
				{
					return KONIEC;
					break;
				}
			case SDLK_f:
				{
					Toggle_screen();
					break;					
				}
			}
		}//pause atd
		if ( event.type == SDL_MOUSEBUTTONDOWN )
		{ 
			if (event.button.button=SDL_BUTTON_LEFT)
			{
				//zacni pocitat rozdiely, o ktore sa mam posunut voci obrazu
				rozdielX=event.button.x;
				rozdielY=event.button.y;
			}
		}
		if ( event.type == SDL_MOUSEBUTTONUP )
		{ 
			if (event.button.button=SDL_BUTTON_LEFT)
			{
				//zacni pocitat rozdiely, o ktore sa mam posunut voci obrazu
				rozdielX=event.button.x-rozdielX;
				rozdielY=event.button.y-rozdielY;
				rozdielY-=rozdielY%IMG_HEIGHT;
				rozdielX-=rozdielX%IMG_WIDTH;
				xx-=rozdielX;
				yy-=rozdielY;						
				//if vacsie, ako je povolene, alebo mensie, daj na najblizsie prijatelne
				if(xx<0) xx=0;
				if(yy<0) yy=0;//konstanty!
				if(yy>WIN_HEIGHT*IMG_HEIGHT-IMG_HEIGHT) yy=WIN_HEIGHT*IMG_HEIGHT-IMG_HEIGHT;//pre posledne,aby sa zmestilo s velkostou 50,50
				if(xx>WIN_WIDTH*IMG_WIDTH-IMG_WIDTH) xx=WIN_WIDTH*IMG_WIDTH-IMG_WIDTH;//pre posledne
				//g_screens->clip_rect.
				Draw();//prekresli podla stavajucich x,y;
			}
		}
		if (event.type==SDL_VIDEORESIZE)
		{
			SDL_SetVideoMode(event.resize.w,event.resize.h,WIN_BPP,WIN_FLAGS);
			//+vsetky aplha a background a tak
			/*a=SDL_GetVideoSurface()->h;
			fprintf(stdout, "vyska: %d\n",a);
			a=SDL_GetVideoSurface()->w;
			fprintf(stdout, "sirka: %d\n",a);*/
		}
	}
	return POKRACUJ;
}
void pohyb_bot()
{
	for(vector<Bot>::iterator iter=boti.begin();iter!=boti.end();iter++)
	{
		iter->run(pole);
	}
}
int main(int argc, char *argv[])
{
	Init();	
	//init(pole,100,50);
	pole=generuj();//konstatne velikost!
	boti.push_back(Bot("kod.txt",pole));
	boti.push_back(Bot("kodOK1.txt",pole));
	xx=boti[0].position.first*IMG_WIDTH;
	yy=boti[0].position.second*IMG_HEIGHT;
	int done=POKRACUJ;
	while (done==POKRACUJ)
	{
		Draw();
		done=uzivatel();	//po kazdom vykresleni sa pohnu roboti aj steny
		pohyb_bot();
		/*do SDL_WaitEvent(&event);
		while (event.type!=SDL_KEYDOWN);*/
	}
	Destroy();
	if (pole) destroy(pole);
	return 0;
}
