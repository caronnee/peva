#include <vector>
#include <fstream>
#include <string>
#include "../../graphic/h/window.h"
#include "../../graphic/h/images.h"
#include "../../add-ons/h/macros.h"

//config file
#define CONFIG "./codewars.config"

// deliminer to delimine values in config
#define DELIMINER '='

using namespace std;

int main(int argc, char *argv[])
{
	Graphic g;
	Window w(&g);
	ifstream config;
	config.open(CONFIG);
	if(!config.good())
	{
		TEST("Creating config file" )
		//create_default
		ofstream o;
		o.open(CONFIG);
		if(!o.good()) return -1;
		o << "resolution=" << DEFAULT_WIN_WIDTH << "x" << DEFAULT_WIN_HEIGTH ;
		o << "font=" << DEFAULT_FONT ;
	       	o << "font-size=" << DEFAULT_FONT_SIZE;
		o << "background=" << DEFAULT_BACKGROUND ;
		o << "timeout=" << DEFAULT_TIMEOUT ;
		o.close();	
	}
	else {
		std::string line;
		char buffer[256];
		while (!config.eof())
		{
			config.getline(buffer, 256);
			line = std::string (buffer);
			size_t pos = line.find(DELIMINER);
			if (pos == std::string::npos) continue;
			std::string name = line.substr(0,pos);
			std::string par = line.substr(pos+1);
			if (name == "resolution") g.set_resolution(par);
			if (name == "font-size") g.set_font_size(par);
			if (name == "font") g.set_font(par);
			if (name == "background") w.set_background(par);
		}
		config.close();
	}
	if(!w.Init(argc, argv))
	{
		w.Destroy(); 
		return 1;
	}

	while (!w.empty())
	{
		w.top()->process();
	}
	g.Destroy();
	w.Destroy(); //odalokovavanie premennych a podobne
	return 0;
}
