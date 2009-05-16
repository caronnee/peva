#include <vector>
#include <fstream>
#include <string>
#include "draw.h"

#define CONFIG "./codewars.config"
#define DELIMINER "="

using namespace std;

int main(int argc, char *argv[])
{
	Window w;
	ifstream config;
	config.open(CONFIG);
	if(!config.good())
	{
		std::cout << "Creating config file" << std::endl;
		//create_default
		ofstream o;
		o.open(CONFIG);
		if(!o.good()) return -1;
		o << "resolution=" << DEFAULT_WIN_WIDTH << "x" << DEFAULT_WIN_HEIGTH <<std::endl;
		o << "font=" << DEFAULT_FONT <<std::endl;
	       	o << "font-size=" << DEFAULT_FONT_SIZE<<std::endl;
		o << "background=" << DEFAULT_BACKGROUND << std::endl;
		o << "timeout=" << DEFAULT_TIMEOUT << std::endl;
		o.close();	
		w.Init_default();
	}
	else {
		std::string line;
		char buffer[256];
		while (!config.eof())
		{
			config.getline(buffer, 256);
			line = std::string (buffer);
			unsigned int pos = line.find(DELIMINER);
			if (pos == std::string::npos) continue;
			std::string name = line.substr(0,pos);
			std::string par = line.substr(pos+1);
			std::cout << name << std::endl;
			if (name == "resolution") w.set_resolution(par);
			if (name == "font-size") w.set_font_size(par);
			if (name == "font") w.set_font(par);
			if (name == "background") w.set_background(par);
			if (name == "timeout") w.set_timeout(par);
		}
		config.close();
	}
	if(!w.Init())
	{
		w.Destroy(); 
		return 1;
	}
	w.state.top()->draw();
	while (!w.state.empty())
	{
		w.state.top()->process();
	}
	w.Destroy();
	return 0;
}
