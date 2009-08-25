#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO

#define WIN_FLAGS SDL_HWSURFACE|SDL_RESIZABLE
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_BPP 0

#define WIN_TITLE "Vypis textu pomoci SDL_ttf"


/*
 * Funkcni prototypy
 */

bool Init();				// Inicializace
void Destroy();				// Deinicializace
void Draw();				// Vykresleni
bool ProcessEvent();			// Osetruje udalosti
int  main(int argc, char *argv[]);	// Vstup do programu


/*
 * Globalni promenne
 */

SDL_Surface *g_screen;		// Surface okna
TTF_Font *g_font;		// Font


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

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
		return false;
	}

	// Vytvoreni fontu, mimochodem font stahnut z
	// http://dejavu.sourceforge.net/wiki/index.php/Download
	g_font = TTF_OpenFont("./fonts/sfd/DejaVuSansCondensed.ttf", 16);
	if(!g_font)
	{
		printf("Unable to open font: %s\n", TTF_GetError());
		return false;
	}

	// Vytvori okno s definovanymi vlastnostmi
	g_screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		fprintf(stderr, "Unable to set %dx%d video: %s\n",
				WIN_WIDTH, WIN_HEIGHT, SDL_GetError());
		return false;
	}

	// Titulek okna
	SDL_WM_SetCaption(WIN_TITLE, NULL);

	return true;//+mozno este ikona
}


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


/*
 * Vykresleni sceny
 */

void Draw()
{
	char tmp[256];				// Generovani dynamickych retezcu
	SDL_Color fg_col = { 255, 255, 255, 0 };// Barva textu
	SDL_Color bg_col = { 0, 0, 255, 0 };	// Barva pozadi (pro Shaded)
	SDL_Rect rect;				// Pozice textu na obrazovce
	SDL_Surface *text;			// Surface s vykreslenym textem
	int width;				// Sirka textu (zarovnavani)

	// Smaze okno - kvuli TTF_RenderUTF8_Blended()
	// Zakomentujte a uvidite...
	SDL_FillRect(g_screen, NULL, SDL_MapRGB(g_screen->format, 0, 0, 255));


	// Normalni styl fontu
	TTF_SetFontStyle(g_font, TTF_STYLE_NORMAL);


	// Zjisti sirku textu a zarovna prvni radek na stred okna
	// Ostatni zacinaji na stejne x-ove pozici jako on
	TTF_SizeText(g_font, "Prilis zlutoucky kun upel dabelske ody"
			"- TTF_RenderText_Solid()",
			&width, NULL);
	rect.x = (g_screen->w >> 1) - (width >> 1);
	rect.y = (g_screen->h >> 1) - TTF_FontLineSkip(g_font)*2;


	// Ukazka ceskych znaku
	text = TTF_RenderText_Solid(g_font,
			"Èeské znaky"
			" - TTF_RenderText_Solid()",
			fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);


	rect.y += TTF_FontLineSkip(g_font);
	text = TTF_RenderUTF8_Solid(g_font,// Text musi byt v utf8
			"Pøíliš žluouèký kùn úpìl ïábelské ódy"
			" - TTF_RenderUTF8_Solid()",
			fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);

	rect.y += TTF_FontLineSkip(g_font);
	text = TTF_RenderUTF8_Shaded(g_font,
			"Pøíliš žluouèký kùn úpìl ïábelské ódy"
			" - TTF_RenderUTF8_Shaded()",
			fg_col, bg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);

	rect.y += TTF_FontLineSkip(g_font);
	text = TTF_RenderUTF8_Blended(g_font,
			"Pøíliš žluouèký kùn úpìl ïábelské ódy"
			" - TTF_RenderUTF8_Blended()",
			fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);


	// Od ted kurzivou
	TTF_SetFontStyle(g_font, TTF_STYLE_ITALIC);


	// Umisti text do leveho dolniho rohu, 20px od okraju
	rect.x = 20;
	rect.y =  g_screen->h - TTF_FontLineSkip(g_font)*4 - 40;

	// Vypise info o pouzivanem fontu
	sprintf(tmp, "TTF_FontFaceFamilyName(): %s", TTF_FontFaceFamilyName(g_font));
	text = TTF_RenderUTF8_Blended(g_font, tmp, fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);

	rect.y += TTF_FontLineSkip(g_font);
	sprintf(tmp, "TTF_FontFaceStyleName(): %s", TTF_FontFaceStyleName(g_font));
	text = TTF_RenderUTF8_Blended(g_font, tmp, fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);

	rect.y += TTF_FontLineSkip(g_font);
	sprintf(tmp, "TTF_FontFaceIsFixedWidth(): %s",
			(TTF_FontFaceIsFixedWidth(g_font)) ? "yes" : "no");
	text = TTF_RenderUTF8_Blended(g_font, tmp, fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);
	
	rect.y += TTF_FontLineSkip(g_font);
	sprintf(tmp, "TTF_FontFaces(): %d", TTF_FontFaces(g_font));
	text = TTF_RenderUTF8_Blended(g_font, tmp, fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);

	sprintf(tmp, "TTF_FontHeight(): %d", TTF_FontHeight(g_font));
	rect.y += TTF_FontLineSkip(g_font);
	text = TTF_RenderUTF8_Blended(g_font, tmp, fg_col);
	SDL_BlitSurface(text, NULL, g_screen, &rect);
	SDL_FreeSurface(text);


	// Zobrazi zmenenou scenu
	SDL_Flip(g_screen);
}


/*
 * Osetruje udalosti
 * V tomto pripade ceka se na klavesu ESC, ktera ukonci program
 * a reaguje na zmenu velikosti okna
 */

bool ProcessEvent()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return false;
						break;

					default:
						break;
				}
				break;

			// Zmena velikosti okna
			case SDL_VIDEORESIZE:
				g_screen = SDL_SetVideoMode(event.resize.w,
					event.resize.h, WIN_BPP, WIN_FLAGS);

				if(g_screen == NULL)
				{
					fprintf(stderr,
						"Unable to resize window: %s\n",
						SDL_GetError());
					return false;
				}
				break;

			// Pozadavek na ukonceni
			case SDL_QUIT:
				return false;
				break;

			default:
				break;
		}
	}

	return true;
}


/*
 * Vstup do programu
 */

int xmain(int argc, char *argv[])
{
	printf(WIN_TITLE);
	printf("\nPress ESC key to quit.\n");

	// Inicializace
	if(!Init())
	{
		Destroy();
		return 1;
	}

	// Hlavni smycka programu
	bool done = false;
	while(!done)
	{
		done = !ProcessEvent();
		Draw();
	}

	// Deinicializace a konec
	Destroy();
	return 0;
}