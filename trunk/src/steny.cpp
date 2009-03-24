#include "steny.h"
SDL_Surface* mizne=IMG_Load("./images/Fade.png");
SDL_Surface* change=IMG_Load("./images/Change.png");
SDL_Surface* hybe=IMG_Load("./images/Fade.png");//potom zmenit
SDL_Surface* solid=IMG_Load("./images/Solid.png");
SDL_Surface* nic=IMG_Load("./images/Nic.png");

AbstractSteny::AbstractSteny()
{
	active=NIC;
	stena=NULL;
	x=y=0;
};
void AbstractSteny::action(AbstractSteny *** xxx,int x,int y){};
SDL_Surface*AbstractSteny::image()
{
	return this->stena;
}
StenaMizne::StenaMizne(int x_,int y_)
{
	this->stena2=NULL;//popripade dlazdice
	this->stena=mizne;
	this->active=STENA;
	this->x=x_;
	this->y=y_;
};
void StenaMizne::action(AbstractSteny ***,int x=0,int y=0)
{
	if (active=NIC) 
	{
		active=STENA;//dat tomu este nejaky vacsi casovy limit, nez je 1 tah
	//	if (active==BOT) active=STENA; ak je 
		SDL_Surface*pom;
		pom=this->stena;
		stena=stena2;
		stena2=pom;
	}
};
StenaPresuva::StenaPresuva(int x_,int y_)
{
	this->stena=change;
	this->active=STENA;
	this->x=x_;
	this->y=y_;
};
void StenaPresuva::action(AbstractSteny*** steny,int max_x,int max_y)
{
	int x_nove=rand()%max_x;
	int y_nove=rand()%max_y;
	while (steny[x_nove][y_nove]->active!=NIC)	
	{//hladaj najblisiu volny neaktivnu stenu
		x_nove++;
		if (x_nove>max_x) 
		{
			x_nove=0;
			y_nove++;
		}
		if (y_nove>max_y)y_nove=0;
	}
	//zamen sa s prazdnym priestorom,resp.zamen ukazovatele
	AbstractSteny* pom;
	pom=steny[x][y];
	steny[x][y]=steny[x_nove][y_nove];
	x=x_nove;
	y=y_nove;
	steny[x][y]=pom;
};
StenaHybe::StenaHybe(int x_,int y_)
{
	stena=hybe;
	active=STENA;
	this->x=x_;
	this->y=y_;
};
void StenaHybe::action(AbstractSteny ***steny,int max_x,int max_y)
{
	int x_stare=x;
	int y_stare=y;
	int zmena=rand()%3-1;//pole o velosti 4 prvkov
	if (steny[(x+zmena)%max_x][y]->active==NIC)x=(x+zmena)%max_x;//pozor na pretecenie pola!
	else if (steny[abs(x-zmena)][y]->active==NIC)x=abs(x-zmena);
	else if (steny[x][(y+zmena)%max_y]->active==NIC)y=(y+zmena)%max_y;
	else if (steny[x][abs(y-zmena)]->active==NIC)y=abs(y-zmena);
	//tu uz bude zarucene zmenena alebo stejna, co nas ale netrapi	
	steny[x_stare][y_stare]=steny[x][y];
	steny[x][y]=this;
};

StenaSolid::StenaSolid(int x_,int y_)
{
	this->active=STENA;
	stena=solid;
	this->x=x_;
	this->y=y_;
};
void StenaSolid::action(AbstractSteny ***,int x,int y){};//nepusti robota,odraz strelu - ale pre kazdu!

StenaNic::StenaNic(int x_,int y_)
{
	this->active=NIC;
	this->stena=nic;
	this->x=x_;
	this->y=y_;
};
void StenaNic::action(AbstractSteny ***p, int x, int y)
{};

