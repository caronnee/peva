#include "../h/images.h"
#include "boost/filesystem.hpp"
#include <iostream>

namespace bf = boost::filesystem;

ImageSet::ImageSet(std::string name)
{
	int size=0;
	namesOfSet = name;
	if (!bf::exists("./skins" + name))
		std::cerr << "not found directory"<< std::endl;
//	std::string files[] = get_files(name, size);
}
