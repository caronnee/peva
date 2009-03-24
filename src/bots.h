#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "steny.h"
#include "bot_table.h"

using namespace std;

class Policko
{
public:
	string prikaz[3];//maximalne 3
	Policko* next_normal;
	Policko* next_true;
	Policko();
};
class Bot
{	
	bool no_init;	
	std::map <std::string,my_variable> variables;	//viacia hodnotu tej-ktorej premennej
	Policko* code;	
	pair<int,int>pohyb;
	//polia - zisti,kolko  ich chce uzivatel nadeklarovat a potom ich nadeklaruj
	//operacie na boolen &,|,xor,not
	//operacie na int +-* /,mod div;*/
	//cod bota	

	void move(std::string a,AbstractSteny***);
	void turn(std::string kam);
	bool exec(std::string* command,AbstractSteny***);
	void shoot(std::string kam);
	bool is_move(std::string a);
	std::string* parse(std::string a,char delim);
	bool obsahuje(std::string s,char a);
	void add_variable(std::string variables,std::string typ);	
	std::string* parse(std::string a);
	
	void spracuj(std::string sl,Policko* p);
	
	void spracuj_prikaz(std::string* co,Policko* odkial,Policko*kam);
	void spracuj_blok(Policko* odkial,Policko*kam);
public:
	Bot(char *,AbstractSteny***);
	void run(AbstractSteny***);
	pair<int,int> position;
	int seeposition;//4 smer, 1->hore,doprava,dole,dolava
	SDL_Surface* obr[4];//4 smery
};

