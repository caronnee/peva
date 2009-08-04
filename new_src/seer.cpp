#include "seer.h"

Seer::Seer(Position p) //mame iba resolution
{
	resolution = p;
	masks = new Mask*[p.x];
	int ID = 0;
	for(int i =0; i < p.x; i++)
	{
		masks[i] = new Mask[p.y];
		for(int j =0; j < p.y; j++)
		{
			masks[i][j].mask = 0; //ziadne navaznosti
			masks[i][j].ID = ID;
			ID++;
		}
	}
}
void Seer::set_masks()
{
	int  x0 = 1, y0 = 1, yn = resolution.y *2 -1, xn = resolution.x*2-1;//vsetko zdvojnasobit;
	//rovnica v tvare 0 = Ax + By + C;
	int A = y0-yn, B = xn-x0, C =  - y0*xn + x0*yn;	
	for(int y = 1; y < resolution.y*2; y+=2)
	{
		for(int x = 1; x < resolution.x*2; x+=2)
		{
			if (A * x + B * y + C >= 0)
				positions.push_back(Position(x, y ));
		}
	}
	std::cout << A << " " <<B << " " <<C <<std::endl;
//	getc(stdin);
	masks[0][0].mask = 1;
	std::cout << "PositionSize:" << positions.size() << std::endl;
	for (size_t i =0; i< positions.size(); i++)
	{
	//	std::cout <<"he?" << std::endl;
	//	getc(stdin);
		std::cout << "x:" << positions[i].x << ", y:" << positions[i].y << " i: "<<i<< std::endl;
		//getc(stdin);
		yn = positions[i].y;
		xn = positions[i].x; //mame stredy celociselne
		A = y0-yn;
	       	B = xn-x0; 
		C = -y0*xn + x0*yn;
		std::cout << A << " " <<B << " " <<C <<std::endl;
//		getc(stdin);
		for (int y = 0; y < yn-1; y+=2)
		{
			for(int x = 0; x < xn; x+=2) //x,y aktualne dolny pravy roh, < 0
			{
				if (A * x + B * y +B*2  + C >= 0)
				{
					if (A * x + B * y + A*2 + C <= 0)
					{
					//	std::cout << "huurray!";
						masks[xn >> 1][yn >> 1].mask |= 1<<masks[x >> 1][y >> 1].ID;
					}
				}
			}
		}
	}	
	for(int i =0; i< positions.size(); i++)
	{
		positions[i].x = positions[i].x >> 1;
		positions[i].y = positions[i].y >> 1;
	}
}
void Seer::see(Direction d, Map * m, Position pos) 
{
	uint32_t left = ~0, right = ~0; //pociatocne masky, uvodne policko, na ktorom stoji robit, budu vidiet vzdy, preto ma masku jedna
	//zarotujeme v zavislosti na otoceni
		
	Position row = pos;
	objects.clear();
	switch(d)
	{
		case UP:
			{
				std::cout << "hu!";
				getc(stdin);
				uint32_t mask = 0;
				for(int i =0; i< resolution.x; i++)
				{
					for(int j =0; j<resolution.y; j++)
					{
						int xx = pos.x + i, yy = pos.y + j;
						if ((xx ==0 )&& (yy == 0))
							continue;
						if((xx >= m->resolution.x)||(yy >= m->resolution.y))
							break;
						if((m->map[xx][yy]==NULL)||(!m->map[xx][yy]->is_blocking()))
						{
							mask |= 1 << (i*resolution.y + j);
							std::cout << "ID:"<< i*resolution.y + j << " ";
						}
						masks[i][j].object = m->map[xx][yy];
					}
				}
				std::cout << std::endl;
				for(int i =0; i< positions.size(); i++)
				{
					std::cout << "x:" << positions[i].x << " y:" << positions[i].y << "maska:" << masks[positions[i].x][positions[i].y].mask << std::endl;
					uint32_t mask_comp = masks[positions[i].x][positions[i].y].mask;
					std::cout << " x:" << positions[i].x << " y:" << positions[i].y << "maska:" << masks[positions[i].x][positions[i].y].mask<< "sucet" << (masks[positions[i].x][positions[i].y].mask & mask) << std::endl;
					if (((mask_comp & mask) == mask_comp )&&(masks[positions[i].x][positions[i].y].object!=NULL))
					{
						std::cout << "INNNNNNNNNNNNNNNNNN";
						objects.push_back(masks[positions[i].x][positions[i].y].object);
					}
				}
				std::cout << mask << std::endl;
				break;
			}
		default:
			return;
	}
}

void Seer::output()
{
	for(int i =0; i< resolution.x; i++)
	{
		for(int j = 0; j < resolution.y; j++)
		{
			std::cout << masks[i][j].ID << " ";
		}
		std::cout << std::endl;
	}
	for(int i =0; i< resolution.x; i++)
	{
		for(int j = 0; j < resolution.y; j++)
		{
			std::cout << "x:" << i << "y" << j << "zavisi na:" << std::endl;
//			std::cout << "maska:" << masks[i][j].mask << std::endl;
			for(int k = 0; k< resolution.x * resolution.y; k++)
			{
				if (masks[i][j].mask & (1 << k))
					std::cout << k << " ";
			}
			std::cout << std::endl;
			
		}
	}
}
