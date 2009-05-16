#include "objects.h"

Wall::Wall() {} //zatial pedvhodca nerobi nic

SolidWall::SolidWall()
{
	show = IMG_Load("../images/SolidWall.png");//kedze je to iba v konstruktore, mozno si to mozem dovolit
	if (show == NULL) //crash!
	{
		std::cerr << "Image of solid wall not found!)";
	}
}
TrapWall::TrapWall()
{
	show = IMG_Load("../images/TrapWall.png");
	if (show == NULL) //crash!o
	{
		std::cerr << "Image of trap wall not found!)";
	}
}
PushableWall::PushableWall()
{
	show = IMG_Load("../images/PushableWall.png");
	if (show == NULL) //crash!o
	{
		std::cerr << "Image of pushable wall not found!)";
	}
}
ExitWall::ExitWall()
{
	show = IMG_Load("../images/ExitWall.png");
	if (show == NULL) //crash!o
	{
		std::cerr << "Image of exit wall not found!)";
	}
}
