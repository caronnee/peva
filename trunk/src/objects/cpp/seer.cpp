#include "../h/seer.h"

Seer::Seer(Position p) 
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
	masks[0][0].mask = 1;
//	std::cout << "PositionSize:" << positions.size() << std::endl;
	for (size_t i =0; i< positions.size(); i++)
	{
//		std::cout << "x:" << positions[i].x << ", y:" << positions[i].y << " i: "<<i<< std::endl;
		yn = positions[i].y;
		xn = positions[i].x; //mame stredy celociselne
		A = y0-yn;
	       	B = xn-x0; 
		C = -y0*xn + x0*yn;
		for (int y = 0; y < yn-1; y+=2)
		{
			for(int x = 0; x < xn; x+=2) //x,y aktualne dolny pravy roh, < 0
			{
				if (A * x + B * y +B*2  + C >= 0)
				{
					if (A * x + B * y + A*2 + C <= 0)
					{
						masks[xn >> 1][yn >> 1].mask |= 1<<masks[x >> 1][y >> 1].ID;
					}
				}
			}
		}
	}	
	for(size_t i =0; i< positions.size(); i++)
	{
		positions[i].x = positions[i].x >> 1;
		positions[i].y = positions[i].y >> 1;
		std::cout << "ID" << masks[positions[i].x][positions[i].y].ID << ", maska:" <<masks[positions[i].x][positions[i].y].mask << std::endl;
	}
}
void Seer::see(Direction d, Map * m, Position pos) 
{
	Position row = pos;
	objects.clear();
	uint32_t mask = 1; //pre robota
	uint32_t mask2 = 1; //pre robota
	int corr =1;
	switch(d)
	{
		case DOWN:
			corr = -1;
		case UP:
			{
				for(int i =0; i< resolution.x; i++)
				{
			/*		for(int j =0; j<resolution.y; j++)
					{
						int xx = pos.x + i, yy = pos.y + j*corr;
						if ((i ==0 )&& (j == 0))
							continue;
						if((xx >= m->resolution.x)||(yy >= m->resolution.y)||(yy < 0))
							break;
						if((m->map[xx][yy]==NULL)||(!m->map[xx][yy]->is_blocking()))
						{
							mask |= 1 << (i*resolution.y + j);
						}
						masks[i][j].object = m->map[xx][yy];
					}
					for(int j =0; j<resolution.y; j++)
					{
						int xx = pos.x - i, yy = pos.y + j*corr;
						if((xx < 0 )||(yy >= m->resolution.y)|| (yy < 0)) //TODO skontrolovat
							break;
						if((m->map[xx][yy]==NULL)||(!m->map[xx][yy]->is_blocking()))
						{
							mask2 |= 1 << (i*resolution.y + j);
						}
						masks[i][j].object_l = m->map[xx][yy];
					}*/
				}
				std::cout << std::endl;
				break;
			}
		case LEFT:
			corr = -1;
		case RIGTH:
			{
				for(int j =0; j<resolution.y; j++)
				{
					for(int i =0; i< resolution.x; i++)
					{
						int xx = pos.x + j, yy = pos.y + i*corr;
						if ((i ==0 )&& (j == 0))
							continue;
						if((xx >= m->resolution.x)||(yy >= m->resolution.y)||(yy < 0))
							break;
						/*if((m->map[xx][yy]==NULL)||(!m->map[xx][yy]->is_blocking()))
						{
							mask |= 1 << (i*resolution.y + j);
						}
						masks[i][j].object = m->map[xx][yy];
						*/
					}
					for(int i =0; i<resolution.x; i++)
					{
						int xx = pos.x - j, yy = pos.y + i*corr;
						if((xx < 0 )||(yy >= m->resolution.y)|| (yy < 0)) //TODO skontrolovat
							break;
						/*if((m->map[xx][yy]==NULL)||(!m->map[xx][yy]->is_blocking()))
						{
							mask2 |= 1 << (i*resolution.y + j);
						}
						masks[i][j].object_l = m->map[xx][yy];
						*/
					}
				}
				std::cout << std::endl;
				break;
			}
		default:
			return;
	}
	for(size_t i =0; i< positions.size(); i++)
	{
		uint32_t mask_comp = masks[positions[i].x][positions[i].y].mask;
		Object * o = masks[positions[i].x][positions[i].y].object;
		Object * o2 = masks[positions[i].x][positions[i].y].object_l;
		if (((mask_comp & mask) == mask_comp) && (o!=NULL))
		{
			objects.push_back(o);
		}
		if (positions[i].x == 0)
			continue;
		if (((mask_comp & mask2) == mask_comp) && (o2!=NULL))
		{
			objects.push_back(o2);
		}
	}
	std::cout << mask << std::endl;
	std::cout << mask2 << std::endl;
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
