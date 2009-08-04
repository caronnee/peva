#include "seer.h"

Seer::Seer(Position p) //mame iba resolution
{
	resolution = p;
	masks = new Mask*[p.x];
	int ID = 0;
	for(int i =0; i < p.y; i++)
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
		for (int y = 0; y < yn; y+=2)
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
}
void Seer::see(Direction d, Map * m, Position pos) 
{
	uint32_t left = ~0, right = ~0; //pociatocne masky, uvodne policko, na ktorom stoji robit, budu vidiet vzdy, preto ma masku jedna
	//zarotujeme v zavislosti na otoceni
		
	Position row = pos;
	switch(d)
	{
		case UP:
			{
				for(size_t i = 0; i < positions.size(); i++) //cez vsetky viditelne pozicie
				{
					int xx = pos.x - positions[i].x;
				        int yy = pos.y + positions[i].y;
					if ((xx < 0)||(yy > m->resolution.y))
						continue;
					uint32_t mask = masks[positions[i].x][positions[i].y].mask;
					if((left & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								left &= (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						left &= ~(1 << masks[positions[i].x][positions[i].y].ID);
					//ideme na druhu stranu
					xx = pos.x + positions[i].x;
					if((right & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								right &= ~ ( 0 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						right &= ~(1 << masks[xx][yy].ID);
				}
				break;
			}
		case DOWN:
			{
				for(size_t i = 0; i < positions.size(); i++) //cez vsetky viditelne pozicie
				{
					int xx = pos.x - positions[i].x;
					int yy = pos.y - positions[i].y;
					uint32_t mask = masks[positions[i].x][positions[i].y].mask;
					if((left & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								left &= (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						left &= ~(1 << masks[xx][yy].ID);
					xx = pos.x + positions[i].x;
					if((right & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								right &= (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						right &= (1 << masks[xx][yy].ID);
				}
				break;
			}
		case LEFT:
			{
				for(size_t i = 0; i < positions.size(); i++) //cez vsetky viditelne pozicie
				{
					int yy = pos.x - positions[i].x;
					int xx = pos.y - positions[i].y;
					uint32_t mask = masks[positions[i].x][positions[i].y].mask;
					if((left & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								left &= ~ (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						left &= ~( 1 << masks[xx][yy].ID);
					xx = pos.x + positions[i].x;
					if((right & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								right &= ~ (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						right &= (1 << masks[xx][yy].ID);
				}
				break;
					
			}
		case RIGTH:
			{
				for(size_t i = 0; i < positions.size(); i++) //cez vsetky viditelne pozicie
				{
					int yy = pos.x + positions[i].x;
					int xx = pos.y - positions[i].y;
					uint32_t mask = masks[positions[i].x][positions[i].y].mask;
					if((left & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								left &= (1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						left &= ~(1 << masks[xx][yy].ID);
					xx = pos.x + positions[i].x;
					if((right & mask) == mask)
					{
						if(m->map[xx][yy]!=NULL)
						{
							if(m->map[xx][yy]->is_blocking())
							{
								right &=~( 1 << masks[xx][yy].ID);
							}
							objects.push_back(m->map[xx][yy]);
						}
					}
					else
						right &= (1 << masks[xx][yy].ID);
				}
				break;

			}
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
