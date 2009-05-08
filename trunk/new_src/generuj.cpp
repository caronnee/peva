#include "generuj.h"

#define POHYB 4

Dvojica::Dvojica()
	{
		x=rand();
		y=rand();
	}
Dvojica::Dvojica(int x_,int y_)
	{
		x=x_;
		y=y_;
	}
Dvojica& Dvojica::operator=(const Dvojica &a)
	{
		this->x=a.x;
		this->y=a.y;
		return *this;
	}
bool Dvojica::operator>=(Dvojica &a)
	{
		return ((this->x>=a.x)||(this->y>=a.y));
	}

Delty::Delty()
	{
		velkost=hodnotaX=hodnotaY=interval=0;
	}
Delty::Delty(int v,int x,int y)
	{
		this->velkost=v;this->hodnotaX=x;this->hodnotaY=y;
	}
Delty::Delty(const Delty& a)
	{
		velkost=a.velkost;hodnotaX=a.hodnotaX;hodnotaY=a.hodnotaY;
	}
void Delty::swap(Delty &a)
	{
		Delty pom(*this);
		*this=a;
		a=pom;
	}
Delty& Delty::operator=(const Delty& a) //idelanejsie, aby vracala referenciu na to, co spachala, return this?
	{
		this->hodnotaX=a.hodnotaX;
		this->hodnotaY=a.hodnotaY;
		this->interval=a.interval;
		this->velkost=a.velkost;
		return *this;
	}
	/*void add(Delty a)
	{
		//dojdi na koniec a tam pridaj a
		Delty* x=this;
		while (x->next!=NULL)
		{
			x=x->next;
		}
		x->next=new Delty(a);
	}*/
void Had::vytvorDelty()
	{
		//potom vytvorit na to nejaky algoritm	
		delty[0]=Delty(poz.x-1,1,0);//->
		delty[1]=Delty(res.y-poz.y,0,1);//^
		delty[2]=Delty(res.x-poz.x,-1,0);//<-
		delty[3]=Delty(poz.y-1,0,-1);///v
		//suradna sustava, ze 00 je v lavom dolnom rohu
		//zatriedit podla velkosti od najvacieseho po najmensie
		int i=0;
		while (i<POHYB-1)
		{
			int i1;
			i1=i+1;
			//if((i1=i+1)==POHYB) i1=0;
			if (delty[i1].velkost>delty[i].velkost) //bublinkove triedenie
			{
				delty[i1].swap(delty[i]);
				i=-1;
			}
			i++;
		}
		//prejdi to a vytvore odpovedajuce intervaly
		delty[0].interval=delty[0].velkost;
		for(i=1;i<POHYB;i++)
		{
			delty[i].interval=delty[i].velkost+delty[i-1].interval;
		}
	}

bool Had::pohyb()
	{
		int i=0;
		//std::cout<<"Mohutnost:"<<this->mohutnost<<std::endl;
		this->zivotnost--;//pohol sa,klesa mu zivotnost;
		if (zivotnost==0) return true;
		int p=rand()%this->stopro;
		while(delty[i].interval<p)
			i++;
		//sme na spravnom delte,pricitame hodnoty k pozicii
		this->poz.x+=delty[i].hodnotaX;
		this->poz.y+=delty[i].hodnotaY;
		smer.x=delty[i].hodnotaX;
		smer.y=delty[i].hodnotaY;
		//ak je to mimo pola, orez a chod na 0;
		if (poz>=res)
		{
			//bude prechadzat na druhu obrazovku
			poz.x%=res.x;
			poz.y%=res.y;
		}
		if (poz.x<0)
			poz.x+=res.x;
		if(poz.y<0)
			poz.y+=res.y;
		int rozsir=rand()%5-2;//-2,2, 2- ztenci sa,2 rozsir, inak zostan
		switch(rozsir)
		{
		case -2: 
			{
				mohutnost--;
				break;
			}
		case 2:
			{
				mohutnost++;
				break;
			}
		}
		if (mohutnost<0) mohutnost=1;
		if (mohutnost>2) mohutnost=2;
		return false;
	}
Had::Had(const Had& a)
	{		
		mohutnost=0;
		stopro=a.res.x+a.res.y - 2;//co s neparnymi?
		this->res=a.res;
		this->zivotnost=a.zivotnost;
		navstivene = new int[4];
		for (int i=0;i<4;i++)
			this->navstivene[i]=a.navstivene[i];
		this->poz=a.poz;	
		vytvorDelty();	
	}
Had::Had(Dvojica resolution,int n)
	{
		mohutnost=0;
		res=resolution;
		stopro=res.x+res.y - 2;		
		int ziv=resolution.x+resolution.y;
		poz.x%=resolution.x;
		poz.y%=resolution.y;
		zivotnost=rand()%ziv+resolution.x+resolution.y;//upravit
		navstivene=new int[4];
		vytvorDelty();		
	}
void Had::add(Had h)
	{
		this->next=new Had(h);
	}
int Had::get_x()
	{
		return this->poz.x;
	}
int Had::get_y()
	{
		return this->poz.y;
	}
int Had::get_mohut()
	{
		return this->mohutnost;
	}
int Had::get_smer_x()
	{
		return smer.x;
	}
int Had::get_smer_y()
	{
		return smer.y;
	}

AbstractSteny*** generuj()
{
	srand((unsigned)time(NULL));
	int x,y,pocet;
	std::ofstream subor;
	subor.open("output.txt");
	/*std::cout<<"zadaj rozmery obrazovky:";	
	std::cin>>x;
	std::cin>>y;
	std::cout<<"zadaj pocet hadov:";
	std::cin>>pocet;*/
	x=y=100;pocet=5;
	Had* hadi;
	Had* hadk;
	for (int i=0;i<pocet;i++)
	{
		//vytvor hadov
		if (i==0) 
		{
			hadi=new Had(Dvojica(x,y),pocet);
			hadk=hadi;
		}
		else
		{
//			Had(Dvojica(x,y),pocet);
			hadk->add(Had(Dvojica(x,y),pocet));
			hadk=hadk->next;
		}
	}
	hadk->next=hadi;//hadi su vytvoreni, bude sa generovat, je to cyklicky zoznam
	char** pole;
	pole=new char*[x];
	for (int i=0;i<x;i++)
	{
		pole[i]=new char[y];
	}
	for (int i=0;i<x;i++)
		for (int j=0;j<y;j++)
		{
			pole[i][j]='X';
		}

	int pocet_hadov=pocet;//ked sa rozmnozia, tak potom pridaj, ked skoncia, potom  uber;
	while (pocet_hadov!=0)
	{
		pole[hadi->get_y()][hadi->get_x()]=' ';
		//na kolme strany hod podla mohutnostnoti kolno na smer
		Dvojica kolmo(hadi->get_smer_y(),(-1)*hadi->get_smer_x());
		Dvojica suc_poz(hadi->get_x(),hadi->get_y());
		for(int i=0;i<hadi->get_mohut();i++)
		{
			suc_poz.x+=kolmo.x;
			suc_poz.y+=kolmo.y;
			if ((suc_poz.x<0)||(suc_poz.y<0)||(suc_poz.x>=x)||(suc_poz.y>=y)) break;
			pole[suc_poz.y][suc_poz.x]=' ';
		}
		//druha strana		
		suc_poz=Dvojica(hadi->get_x(),hadi->get_y());
		for(int i=0;i<hadi->get_mohut();i++)
		{
			suc_poz.x-=kolmo.x;
			suc_poz.y-=kolmo.y;
			if ((suc_poz.x<0)||(suc_poz.y<0)||(suc_poz.x>=x)||(suc_poz.y>=y)) break;
			pole[suc_poz.y][suc_poz.x]=' ';
		}
		if (hadi->pohyb())
		{
			pocet_hadov--;			
		}
		hadi=hadi->next;		
	}
	for (int i=0;i<x;i++)
	{
		for (int j=0;j<y;j++)
			subor<< pole[i][j];
		subor<<std::endl;
	}
		//prejdi cele pole a pridaj tam steny,rand(0-10)0,1,2,3
	AbstractSteny*** pole2=new AbstractSteny**[100];
	for(int i=0;i<100;i++)
		pole2[i]=new AbstractSteny*[100];
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
		{			
			if (pole[i][j]=='X')
			{
				switch (rand()%10)//pocet zvlastnych stien*2?
				{
				case 0:
					 {
						 pole2[i][j]=new StenaHybe(i,j);
						 break;
					 }
				case 1:
					 {
						 pole2[i][j]=new StenaMizne(i,j);
						 break;
					 }
				case 2:
					 {
						 pole2[i][j]=new StenaPresuva(i,j);
						 break;
					 }
				default:
					{
						pole2[i][j]=new StenaSolid(i,j);
						break;
					}
				}
			}
			else pole2[i][j]=new StenaNic(i,j);
		}
		destroy(pole);
	return pole2;
}
void destroy(char **a)
{//zistit velkost u a
	for (int i=0;i<100;i++)
		delete a[i];
	delete a;//akonahle nacita alebo skonci
}
void destroy(AbstractSteny ***a)
{//zistit velkost u a
	for (int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
			delete a[i][j];
		delete a[i];
	}
	delete a;//akonahle nacita alebo skonci
}
//dorobit presuvanie stien,odrazave steny, presvitne a pod., samostatna class steaa a jej vlastnosti pri iterakcii so inou stenou, robotom alebo strelou
