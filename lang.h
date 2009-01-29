//fce samostatny header, pretoze bude includovat roboty
#include <string>
#include <vector>
#include <map>
#include <iostream>

#define MAX 360

typedef unsigned int Uint;

/*enum Codewords//vsetky prikazy, ktore sa daju zadat
{
	NOTHING,MAIN,FUNCTION,VAR,IF,ELSEIF,ELSE,WHILE //ak je uz definovana nova funkcia, nebude int a bool, ale iba int, bool je hocico nenulove
};*/
enum RESULTS
{
	OK,NO
};
enum WHAT
{
	BRACKET = -MAX+2, ANTIBRACKET = -MAX, COMMA = -MAX+1, FUNCTION = -2, PARAM = -1, VALUE = 0
};
enum Commands
{
	WHILE, IF, ELSEIF, ELSE, MOVE, SHOOT, WAIT, RUN, TURN, PLUS, MINUS, MULTIP, DIV, ADD, AND, OR, RETURN
};	//vsetky standarte prikazy, ktore jazyk pozna
typedef enum Node_commands //co mam v jednotlich stavoch robit
{
	NOTHING = -1, START, ADD_VAR,ADD_VALUE, ADD_FUNCTION, WAIT_END, BLOCK_IF, BLOCK_ELSE, CONDITION_WHILE, CONDITION_IF, NUMBER_OF_ELEMENTS
};
class Default
{
public:		
	Uint recurse;
	int number_args;
	std::vector<int> params; //cisla zadane
	virtual int result() = 0; //co vypadne po dokonceni operacie
	void fill(int c);
	void Destroy();
};
class Code
{	
public:
	Uint type;
	//std::vector<int>* params; // parametre funkcie, z ktorej to spustame	
	std::vector<int> variables; //potrebujeme vediet, s akymi premennymi narabat
	Code();
	Code * Ok, * No;
	//int result();
};
class Var : Default
{
	int var;//typ toho, ci je ti pole alebo funkcia??
public:
	Var();
	Var(int a);
	Var(std::string str);
	virtual int result();
};
class Fce:Default
{
	Code* block;//samostatny blok, co sa ma vykonat	
public:
	Fce();
	//void add_block();
	virtual int result();
};
class Plus:Default
{
public:
	Plus();
	virtual int result();
};
class Minus:Default
{
public:
	Minus();
	virtual int result();
};
class Multip:Default
{
public:
	Multip();
	virtual int result();
};
class Div:Default
{
public:
	Div();
	virtual int result();
};
class Add:Default
{
	void Destroy();
	std::vector<int> num_args_add;
public:
	Add();
	virtual int result();
};
class And:Default
{
public:
	And();
	virtual int result();
};
class Or:Default
{
public:
	Or();
	virtual int result();
};
class Move:Default
{
public:
	Move();
	virtual int result();
};
class Wait:Default
{
public:
	Wait();
	virtual int result();
};
class Shoot:Default
{
public:
	Shoot();
	virtual int result();
};
class Run:Default
{
public:
	Run();
	virtual int result();
};
class Turn:Default
{
public:
	Turn();
	virtual int result();
};
/*struct Node //u rozpoznavacieho stromu
{
	int action; //defaultne 0
	std::map<std::string,Node *> nodes; //podla nacitanych stringov sa rozhodne, kam ist
};
class Tree
{
	Node* root;
	std::map<std::string,int> defined; //ake cislo sme definovanej veci priradili	
public:
	Tree();
	//void make_name();
};*/
class Tree
{
public:
	std::vector<std::pair<char,Tree>> next; //kam vsade sa dokaze dostat po pismenku c
	int number;// mame niekde vonku vektor nodov a chcem vediet, do ktoreho sme sa trafili	
	Tree();	//znak, ktory sa nepovoli
	bool operator==(const Tree& b);
	int find(char c);
	void add(std::string c_, Uint cmd); // pridava a vytvara novy uzol stromu, kde to pripoji
	//void add(char c_, Node_commands cmd); //prida, ak dame jeden znak
	void add(std::string c_, Node_commands cmd,Tree * end );//kam presne ho pripojit
};
class Node
{
	Uint what; //co mame robit v okamihu, ked sa ozve whitespace alebo podobna nehoraznost		
	Tree* actual;//aktualne na com sme
	//int elsewhere; //kam sa dostaneme, ak nenajdeme odpovedajuce v tree a sucasne koncime v tree
public:
	Tree* root; //nemenny koren stromu
	Node(Uint what_ = NOTHING);
	Uint numb();
	void add(std::string c_, Uint cmd); // pridava a vytvara novy uzol stromu, kde to pripoji
	//void add(char c_, Node_commands cmd); //prida, ak dame jeden znak
	void add(std::string c_, Uint cmd,Tree * end );//kam presne ho pripojit
	//void add(char c_, Node_commands cmd, Node* x); // vracia node, v ktorom skoncila, teda ten najvzdialenejsi
};
class Automat
{
	std::vector<Node> nodes;//vsetky node, vytvora sa iba raz v konstruktore
	void name(Tree * tree, Uint cmd);
public:
	Automat();
};