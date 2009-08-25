#include "lang.h"

static const char alpha[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const char num[] = "0123456789";
static const char delim[] = ";,"; //tkroe oddeluju funkcnost? Mozno by sa mali zlucit
static const char ws[] = "\n\t\r "; //oddelovanie jenotlivich slov
std::string word; // zapis vsetkeho, co nacitame;
Tree* defined; //definovane premenne a ze sa maju naadovat na do_command
Tree* defined_where; //cisla k tomu, kde sa definovane premenne  a funkcie nachadzju vo fces

//----------------sucast botov
std::vector<Default *> fce;
std::vector<int> vars;//??
std::vector<Node> nodes; //uzly rozpoznavacieho automatu

void Default::fill(int x = 0)
{
	this->recurse = 0;
	this->number_args = x;
	for(int i = 0;i< this->number_args;i++)
	{
		this->params.push_back(0);//inicializacia, TODO!
	}	
};
void Default::Destroy()
{
	for(Uint i = 0; i<this->number_args;i++)
		this->params.pop_back();
	this->recurse--;
}
Code::Code()
{
	//this->params = params_;
	this->No = this->Ok = NULL;
	this->type = 0; //este sme nic nepriradzovali
};

Var::Var()
{
	this->number_args = 0;
	this->var = 0;
};
Var::Var(int a)
{
	this->number_args = 0;
	this->var = a;
};
Var::Var(std::string str) //vypreparujme z toho cislo, moze byt aj zaporne!
{
	this->number_args = 0;
	this->var=0;
	Uint i;
	bool plus = true;
	if (str[0]=='-') 
	{
		i = 1;
		plus = false;
	}
	else i = 0;
	for (i; i< str.size();i++)
	{
		var*=10;
		if (plus) var+=str[i]-'0';
		else var-=str[i]-'0';
	}
};
int Var::result()
{	
	return this->var;
};
Fce::Fce()
{
	this->block = NULL;
};
int Fce::result()
{
	Code pom = * this->block; //zaciatok bloku skopirujeme
	int res;
	int num = pom.variables[0];
	int shift = (this->recurse-1)*this->number_args;
	while((pom.Ok==NULL)||(pom.No==NULL)) //az kym nedojdeme na koniec bloku, teda return alebo bez returnu
	{
		//int number = fce[num]->number_args;
		for(int i = 1;i<pom.variables.size();i++)// v code j -1 ako premenna, kopiruje sa ale iba jeho hodnota, o je value
		{
			if (pom.variables[i] == PARAM) 
			{
				fce[num]->params.push_back(VALUE);i++;
				fce[num]->params.push_back(params[i+shift]);
			}
			if (pom.variables[i] == VALUE)
			{
				fce[num]->params.push_back(VALUE);i++;
				fce[num]->params.push_back(pom.variables[i]);
			}
			if (pom.variables[i] == FUNCTION)
			{
				fce[num]->params.push_back(FUNCTION);i++;
				fce[num]->params.push_back(pom.variables[i]);
			}
		}
		res = fce[num]->result();
		if (res==0) pom = *pom.No;
		else pom = *pom.Ok;
	}
	this->Destroy();
	return res;
};
Plus::Plus()
{
	fill(2);
};
int Plus::result()
{
	return params[0] + params[1];
};
Minus::Minus()
{
	fill(2);
};
int Minus::result()
{
	return this->params[0]-this->params[1];
};
Multip::Multip()
{
	fill(2);
};
int Multip::result()
{
	return this->params[0]*this->params[1];
};
Div::Div()
{
	fill(2);
}
int Div::result()
{
	return (int) (this->params[0]/this->params[1]);
};
Add::Add() //je rovnitko, nema presme dany pocet parametrov!
{
	this->number_args = 0;//nebudeme potrebovat
};
void Add::Destroy()
{
	int num;
	if (this->num_args_add.size()==1) 
		num = num_args_add[0];
	else 
	{
		num = *this->num_args_add.rbegin() - *this->num_args_add.rbegin()++;		
	}
	this->num_args_add.pop_back();
}
int Add::result() //vypocitavanie rovnice
{	
	this->recurse++;
	this->num_args_add.push_back(this->params.size());
	std::vector<int> values;
	std:: vector<int> functions;
	functions.push_back(-MAX);//pri pripad prvej funkcie zarazka
	int x = this->params.size();
	int j= 0;
	while(j<x)
	{
		bool del = true;
		switch (this->params[j])
		{
		case FUNCTION://ak ma ta funkcia nizsie cislo ako ta funkcia, co jej predchadzala, vyhodnot predchadzajucu funkciu		
		{//zavorky a ciaky nevadia, lebo maju brutalne nicku hodnotu
			j++;//cislo funkcie v poli
			if (params[j]<functions[j-1]) //ak je mensie vsetko predtym sa spracuje
			{
				do
				{
					int f = *functions.rbegin();
					functions.pop_back();//vyberie posledny prvok a znici ho					
					for(int i = fce[f]->number_args - 1 ; i >= 0;i--)//prislusnu funkciu naplnime premennymi
					{
						fce[f]->params[i] = *values.rbegin();
						values.pop_back();
					}
					values.push_back(fce[f]->result());//vykona akciu a vysledok sa vlozi do vektor values; 
					//POMALE? TODO!netreba nieco sofistikovanejsie a rychlejsie?			
				}
				while (functions[functions.size()]>=params[j]);
				functions.push_back(params[j]);//na zaver pridaj to, k comu sme sa dopracovali
			}
			else //pockame si, az sa vyhodnotia doleziteksie veci, ak nejake budu
			{
				functions.push_back(params[j]);
			}
			break;
		}
		case BRACKET:
		{
			functions.push_back(this->params[j]);//pripisene zarazku
			break;
		}
		case COMMA:
			del = false; //ci zmazat posldnu bracket
		case ANTIBRACKET: //vzdy n zaver nejaka je, aby sme odzavorkovali tu, co sme dali ako hlavu
		{//vsetko odzadu az po BRACKET vyhodnotime
			int f;
			while ( (f = *functions.rbegin())!=BRACKET)
			{
				functions.pop_back();
				for(int i = fce[f]->number_args-1 ; i >= 0;i--)//prislusnu funkciu naplnime premennymi
					{
						fce[f]->params[i] = *values.rbegin();
						values.pop_back();
					}
				values.push_back(fce[f]->result());//vykona akciu a vysledok sa vlozi do vektor values; 
			}
			if (del) functions.pop_back(); //ak to nebola ciarka
			break;
		}
		case PARAM: //pozor na premenne definovane este mimo akejkolvek funkcie
		{
			j++;
			if (this->params[j]==0)	values.push_back(vars[j*(-1)-1]); //vars v definovanych pred funkciou je globalne, preto to je zaporne
			//else values.push_back(this->);//ta premenna, ktora bola v tej funkcii
			break;
		}
		};//konic switchu
	}
	this->Destroy();
	return 0;/// TODO!
};
And::And()
{
	fill(2);
};
int And::result()//bitove staci and pre nase potreby
{
	return this->params[0] & this-> params[1];
};
Or::Or()
{
	fill(2);
};
int Or::result()
{
	return this->params[0] | this-> params[1];
};
Move::Move()
{
	fill(1);
};
int Move::result()
{
	std::cout<<"ak mozem, pohnem sa v smere "<< this->params[0];
	return 1;//podarilo sa
}
Wait::Wait()
{
	fill(1);
}
int Wait::result()
{
	std::cout<<"cakam "<< this->params[0]<<"sekund";
	return OK;
};
Shoot::Shoot()
{
	fill(1);
};
int Shoot::result()
{
	std::cout<<"ak mozem, strilam pod uhlom "<< this->params[0];
	return OK;
};
Run::Run()
{
	fill(1);
};
int Run::result()
{
	std::cout<<"ak mozem, bezim sa v smere "<< this->params[0];
	return OK;
};
Turn::Turn()
{
	fill(1);
};
int Turn::result()
{
	std::cout<<"otacam sa v smere "<< this->params[0];
	return OK;
};
/*bool Tree::operator==(const Tree& b)
{
	if (this->c==b.c) return true;
	return false;
};*/

Tree::Tree()
{
	this->number = 0;//zatial sme sa trafili do roota, pokial nie je povedane inak
};
Node::Node(Uint what_)
{
	this->what = what_;
	this->root = new Tree();
	this->actual = this->root;
	//this->root sa z toho spravi normalny tree konstruktor, takze number = 0, vector pradny
	//this->elsewhere = -1; //kam sa dostaneme po else, mozno je to prikaz dalsej krabicky, -1 = null;
};
int Tree::find(char c)
{
	for(Uint i =0;i<this->next.size();i++)
	{
		if (this->next[i].first==c) return i;
	}
	return -1;
}

void Tree::add(std::string c_, Uint cmd) // prida kompetne jednoslovo
{
	Tree * pom = this;
	int x;
	for(Uint i  = 0;i<c_.size();i++)
	{
		//bud najdes pismeno a presunies sa tam, kde ti hovori alebovytvoris nove
		if ((x=find(c_[i]))==-1) 
		{
			pom->next.push_back(std::pair<char,Tree>(c_[i],Tree()));
			pom = &pom->next.rbegin()->second;//prepneme sa na poslednu pozciu
		}
		else pom = &pom->next[x].second;//inak sa posunieme na uz vytvorene
	}
	pom->number = cmd;//cislo Nodu, kam sa ma vratit, pristupne cez COMMANDS		
};

Uint Node::numb()
{
	return this->actual->number;
};
void Tree::add(std::string c_, Uint cmd, Tree *end) //kazdy jeden znak sa dostane do rozvnakeho uzla v strome
{
	Tree* pom = this;
	for( Uint i =0; i<c_.size();i++)
	{
		pom->next.push_back(std::pair<char,Tree>(c_[i],*end));
		pom->next.rbegin()->second.number = cmd;//kazdemu z nich dame cislo commandu
	}
};
void Automat::name(Tree * tree,Uint cmd)
{
	tree->add(ws,NOTHING,tree); 
	Tree * pom  = new Tree();
	pom->add(num,cmd,pom);
	pom->add(alpha,cmd,pom);
	tree->add(alpha,cmd,pom);
};
Automat::Automat() //vytvori vestko, co ma rozpoznavat ako strom a ukladat do uzlov
{
	//u definovanych premennych si pamatane iba ich cislo v aktualnej funkcii
	const std::string commands[] = {"while", "if", "move","shoot","wait","run","turn"/*,"+","-","*","/","=","&&","||"*/,"return"}; //stringy vsetkych konstant, ktopre budu pouzite v Bloku
    const Uint command_node[] = {CONDITION, CONDITION_IF, DO_COMMAND, DO_COMMAND, DO_COMMAND, DO_COMMAND, DO_COMMAND, DO_COMMAND};//cisla, kroe odkazuju, do akej krabice sa ma skocit
    const Uint command_fce[] = {0, 0, MOVE, SHOOT, WAIT, RUN, TURN, RETURN};//cisla, ktore odkazuju na indentifikator funkcie
	const string[] operators = {"+","-","*","/","=","&&","||"};
	const Uint[] operator_fce = {PLUS, MINUS, MULTIP, DIV, ADD, AND, OR};
	defined = new Tree();
	defined_where = new Tree();
	for (int i = 0; i< sizeof(commands)/sizeof(std::string);i++)
	{
		defined->add(commands[i],command_node[i]);
		defined_where-> add(commands[i],commands_fce[i]);
	}
	for(int i = 0;i<NUMBER_OF_ELEMENTS;i++)
	{
		Node I(i);
		this->nodes.push_back(I);		
	}
	this->nodes[0].root->add("var",ADD_VAR);
	this->nodes[0].root->add("main",BLOCK_IF);
	this->nodes[0].root->add("function",ADD_FUNCTION);

	this->name(this->nodes[ADD_VAR].root, WAIT_END);	

	this->nodes[WAIT_END].root->add(",",ADD_VAR);
	this->nodes[WAIT_END].root->add(";",START); //bodkociarka zavedie na uplny zaciatok
	this->nodes[WAIT_END].root->add("=",ADD_VALUE);

	this->nodes[ADD_VALUE].root->add(num,WAIT_END,nodes[ADD_VALUE].root);
	this->nodes[ADD_VALUE].root->add(alpha,WAIT_END,nodes[ADD_VALUE].root);

	delete(this->nodes[BLOCK].root); //najprv vycistit a potom priradit nove
	this->nodes[BLOCK].root = defined;
	
	this->nodes[CONDITION].root->add(")",BLOCK);
	this->nodes[CONDITION].root->add(alpha,OPERATORS);
	this->nodes[CONDITION].root->add(num,OPERATORS);
	
	this->nodes[OPERATORS].root->add(operators,CONDITION);
	
	this->name(this->nodes[CONDITION_IF].root, OPERATORS_IF);
	this->nodes[CONDITION_IF].root->add(")",BLOCK_IF);
	
	this->nodes[OPERATORS].root->add(operators,CONDITION_IF);
	
	this->nodes[BLOCK_IF].root.add("else", BLOCK);
	this->nodes[BLOCK_IF].root.add("elseif", CONDITION_IF); // za predpokadu, ze nemame elseif ani else-> 0 v tree, vraciame sa na Block a tam znova cele scheckujeme -> special	
	
	this->nodes[DO_COMMAND].root.add("=",ADD_VALUE);
	this->nodes[DO_COMMAND].root.add(";",BLOCK);
	//this->nodes[DO_COMMAND].root.add(";",BLOCK);
	//"elseif", "else", pridame az v BlockElse
	
	//this->nodes[0].numb();
	//nodes[0].add("var",ADD_VAR);
//	std::cout<<sizeof(Node_commands)<<std::endl;
};