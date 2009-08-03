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
	int x0 = 1, y0 = 1, yn = resolution.y*2, xn = resolution.x *2;//vsetko zdvojnasobit;
	//rovnica v tvare 0 = Ax + By + C;
	int A = y0-yn, B = x0-xn, C = y0*xn + x0*yn;	
	for(int y = 1; y< resolution.y *2; y+=2)
	{
		for(int x = 1; x < resolution.x; x+=2)
		{
			if (A * x + B * y + C > 0)
				positions.push_back(Position(x, y));
		}
	}
	masks[0][0].mask = 1;
	//mame vsetky stredy v intoch ulozene po riadkoch od najmensieho po najvacsie
	for (size_t i =0; i< positions.size(); i++)
	{
		yn = positions[i].y;
		xn = positions[i].x;
		A = y0-yn;
	       	B = x0-xn; 
		C = y0*xn + x0*yn; //mame spravenu rovnice pre dvojnasobok;
		for (int y = 2; y < yn; y+=2)
			for(int x = 2; x < xn; x++) //x,y aktualne dolny pravy roh, < 0
			{
				if (A * x + B * y + C <= 0)
				{
					if (A * (x-2) + B * (y+2) + C >= 0)
					{
						int xx = x/2 -1, yy = y/2;
						masks[(xn-1)/2][(yn-1)/1].mask |= 1<<masks[xx][yy].ID;
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
