#include "bots.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define RIGHT 1
#define LEFT -1 //iba dve hodnoty left,right

my_variable::my_variable()
	{
		type=0;
		init=0;
		created=1;
	};
my_variable::my_variable(int a,int _type)
	{
		type=_type;
		init=a;
		hodnota=a;
	};
my_variable& my_variable::operator=(const my_variable a)
	{
		this->hodnota=a.hodnota;
		this->created=1;
		return *this;
	};
Policko::Policko()
	{
		next_true=NULL;
		next_normal=NULL;
		prikaz[0]=prikaz[1]=prikaz[2]="";
	};
void Bot::move(string a,AbstractSteny***pole)
	{//vsetko ide vzhladom na seeposition!
		int x=-1,y=-1;
		if (a=="forward")
		{
			x=this->position.first+this->pohyb.first;
			y=this->position.second+this->pohyb.second;			
		}
		if (a=="back")
		{
			x=this->position.first-this->pohyb.first;
			y=this->position.second-this->pohyb.second;			
		}
		if (a=="right")
		{
			x=this->position.first+this->pohyb.second;
			y=this->position.second+this->pohyb.first;
		}
		if (a=="left")
		{
			x=this->position.first-this->pohyb.second;
			y=this->position.second-this->pohyb.first;
		}
		if(x>0&&y>0&&x<100&&y<100&&pole[x][y]->active==NIC)//moze tam ist,KONSTANTA!
		{
			pole[position.first][position.second]->active=NIC;
			this->position.first=x;
			this->position.second=y;
			pole[x][y]->active=BOT;
		}//nikdy nepojde mimo pola, ak by tam chcel ist, potom sa kod "preskoci"
	};
void Bot::turn(string kam)//right left
{
	if (kam=="right")//case sensitive?
	{
		int pom;
		this->seeposition++;
		if (seeposition==4) seeposition=0;
		pom=this->pohyb.first;
		this->pohyb.first=(-1)*this->pohyb.second;
		this->pohyb.second=pom;
	}
	if (kam=="left")
	{
		int pom;
		this->seeposition--;
		if (seeposition==0) seeposition=3;
		pom=this->pohyb.first;
		this->pohyb.first=this->pohyb.second;
		this->pohyb.second=(-1)*pom;
	}
};
bool Bot::exec(string* command,AbstractSteny***pole)
	{
		if (command[0]=="turn") 
		{
			turn(command[1]);
			return true;
		}
		if (command[0]=="shoot") 
		{
			//shoot(command[1]);//radsej si niekde uchovavat tie inty, nech to nemusim premienat?Jedno a to same
			return true;
		}
		if(command[0]=="move")
		{
			move(command[1],pole);
			return true;
		}
		return false;
	};
void Bot::shoot(string kam){};
bool Bot::is_move(string a)
	{
		return (a=="turn"||a=="seeMove"||a=="shoot"||a=="seeStatic"||a=="move");
	};
void Bot::add_variable(string variables,string typ)
	{//rozparsuj podla ',',zisti, ze je tak niecko ako =
		int type;
		if (typ=="bool") type=my_boolean;
		if (typ=="int") type=my_int;
		string add_v="";
		unsigned int i=0;
		int rovnitko=0;
		string strData = "One";
		//Declaration for C++ vector
		 vector <string> str_Vector;
		//str_Vector.push_back(strData);		
		vector<string> parser;
		while (i<variables.length())//prejdeme cez vsetkty variables
		{
			while (variables[i]&&(variables[i]!=',')&&(variables[i]!=';')&&(variables[i]!='='))
			{
				if (variables[i]!=' ')
				{
					add_v+=variables[i];
				}
				i++;
			}
			parser.push_back("ahoj!");
			if (variables[i]=='=') parser.push_back("=");
			if (add_v!="")parser.push_back(add_v);
			add_v="";
			i++;
		}
		//pridavanie do robotovych premennych na zaklade parsovania
		//kontrola povolenych znakov
		string predch="";
		for(vector<string>::iterator iter=parser.begin();iter!=parser.end();iter++)
		{
			if (obsahuje((*iter),'='))
			{
				string* s=new string[2];
				s=parse((*iter),'=');
				this->variables[s[0]]=my_variable(atoi(s[1].c_str()),type);
			}
			else this->variables[(*iter)]=my_variable(0,type);
		}
	};
bool Bot::obsahuje(string s,char a)
	{
		for(unsigned int i=0;i<s.length();i++)
		{
			if (s[i]==a) return true;
		}
		return false;
	};
string* Bot::parse(string a)
	{
		int i=0,j=0;
		//char* whitechars[] = {" ","}","{","\n","\t"};		
		string line="";
		string* pole=new string[3];
		int zavorky=0;
		while (a[j]&&i<2)//odmedzenie,ze chcem iba prve slovo a jeho argumentu a zvysok
		{
			if (((a[j]==';')||(a[j]==' ')||(a[j]=='{')||(a[j]=='(')||(a[j]=='\n')||(a[j]=='\t')||((a[j]==')')&&(zavorky==1)))&&line!="")
			{
				pole[i]=line;
				i++;
				line="";
			}
			else 
			{
				line+=a[j];
			}
			if (a[j]==')')zavorky--;
			if (a[j]=='(')zavorky++;
			j++;
		}
		//zvysok daj do pole[2]
		pole[2]="";
		for(int i=j;a[i];i++)
		{
			pole[2]+=a[i];
		}
		return pole;
	};
string* Bot::parse(string a,char delim)
	{
		string* s=new string[2];
		unsigned int i=0;
		while (a[i]!=delim)
		{
			s[0]+=a[i];
			i++;
		}
		while(i<a.length())
		{
			i++;
			s[1]+=a[i];			
		}
		return s;
	};
	
void Bot::spracuj_blok(Policko* odkial,Policko*kam)
	{	
//!!!
	};
void Bot::spracuj_prikaz(string* co,Policko* odkial,Policko*kam)
	{//spracuvavame jenoduchy,dalej nedelitelny prikaz
		odkial->prikaz[0]=co[0];
		odkial->prikaz[1]=co[1];
		odkial->next_true=NULL;
		odkial->next_normal=kam;
	};
void Bot::spracuj(string sl,Policko* p)
	{		
		string* slovo=new string[3];
		slovo=parse(sl);//da to do pola s jednotlivymi argunetami, napr. while, (..), prikaz alebo jeho zlozenina
		int p_if=0;
		if ((slovo[0]=="int")||(slovo[0]=="bool"))
			{
				add_variable(slovo[1],slovo[0]);				
				p_if=0;
			}//OK
			else if (slovo[0]=="if")
			{
				p->next_normal=new Policko();
				p_if=1;
				if (slovo[2]==";") 
				{
					Policko* q=p->next_true;					
					//spracuj_prikaz(slovo[2],p->next_true,p->next_normal);
				}
				else spracuj_blok(p->next_true,p->next_normal);
				p=p->next_normal;
			}
			else if(slovo[0]=="else")
			{
				if(p_if!=1) 
				{
					//cout<<"bacha!je bez ifu!"<<endl;
					//vyhod nieco ako return, exception
				}
				else
				{
					Policko* pom=p->next_normal;
					//...
					p=p->next_normal;
					p_if=0;
				}
			}
			else if(slovo[0]=="while")
			{
				p_if=0;
				string* s=new string[3];
				s=parse(slovo[2]);
				p->next_true=new Policko();				
				if (is_move(s[0])) spracuj_prikaz(s,p->next_true,p->next_normal);
				else if (slovo[3]=="{") spracuj_blok(p->next_true,p);
				else //mame za while () dlasi systemovy prikaz
				{

				}
				p=p->next_normal;
			}
			else 
			{
				p_if=0;//slovo 3 musim byt ;, pretoze za prikazmi uz nic nesmie nasledovat
				p->prikaz[0]=slovo[0];
				p->prikaz[1]=slovo[1];
			}
			p=p->next_normal;//?
	};
void Bot::run(AbstractSteny*** p)////////////////******
	{
		bool pohyb=false;
		while (!pohyb)//alebo timeout
		{
			pohyb=exec(code->prikaz,p);
			code=this->code->next_normal;//+podmienky
		}
	};

Bot::Bot(char * src,AbstractSteny*** plocha)
	{	
		//rucne?		
		this->obr[0]=IMG_Load("./images/bot1.png");
		this->obr[1]=IMG_Load("./images/bot2.png");
		this->obr[2]=IMG_Load("./images/bot3.png");
		this->obr[3]=IMG_Load("./images/bot4.png");
		this->seeposition=0;//najkor otoceny smerom dole
		this->pohyb=make_pair(0,1);
		code=NULL;
		//zalozit ho niekde v poli tak, aby nezavadza ostatnym botom		
		this->position=make_pair(rand()%100,rand()%100);
		while(plocha[position.first][position.second]->active!=NIC)
		{
			position.second++;			
			if(position.second>=100) 
			{
				position.second=0;
				position.first++;
			}//ak sa dostane na zaciatok, tak potom zrus! !!!
			if(position.first>=100) position.first=0;
		}
		plocha[position.first][position.second]->active=BOT;
		Policko* p=code;//s p budeme pracovat
		no_init=true;//no init znamena, ze bot loaduje prvykrat, cize v map nema ziadne premenne zatial a teda ich nesmie ignorovat, keby sa nejake vyskytli
		ifstream kod;
		kod.open (src);
		if (!kod.is_open()) 
		{
			cout<<"nenajden kod!";//!!!throw exceptions
			exit(3);
		}
		string line="";
		char* whitespc[]={" ","(",";"};
		char letter=' ';
		while (kod)
		{				
			do
			{		
				kod.get(letter);
				if (letter!='\n')
					line+=letter;				
			}
			while (letter!=';' && letter!='{' &&kod);
			if (kod) 
			{
				if (code==NULL)
				{
					code= new Policko();
					p=code;
				}
				else 
				{
					p->next_normal=new Policko();
					p=p->next_normal;
				}
				spracuj(line,p);
			}
			line="";
		}//chod vsad po normal a ak najdes null, potom tam, pridaj code
		//zatial
		p->next_normal=code;//pre zacyklenie
	};

