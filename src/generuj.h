//language SLOVAK!!!
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "steny.h"

#define POHYB 4

class Pair
{	
public:
	int x,y;
	Pair();
	Pair(int x_,int y_);
	Pair& operator=(const Pair &a);
	bool operator>=(Pair &a);
};
class Delty
{
public:
	int velkost;int hodnotaX,hodnotaY;int interval;	
	Delty();
	Delty(int v,int x,int y);
	Delty(const Delty& a);
	void swap(Delty &a);
	Delty& operator=(const Delty& a);
};
class Had
{
public:
	int* navstivene; //zapamataj si predposledne 4 policka
	Pair res;
	Pair poz;
	int stopro;
	Delty delty[POHYB]; //zoradenie zmeny oproti resolution	
	/*void operator=(Had& a)
	{
	}*/
	void vytvorDelty();	
	Had *next;	
	///previest na funkcie, ktore vysledok ukazu
	int mohutnost;
	int zivotnost;
	Pair smer;
	bool pohyb();
	Had(const Had& a);
	Had(Pair resolution,int n);
	void add(Had h);
	int get_x();
	int get_y();
	int get_mohut();
	int get_smer_x();
	int get_smer_y();
};
AbstractSteny*** generuj();//pozdejc s presnym poctom,kolko toho ma generovat
void destroy(char**);
void destroy(AbstractSteny***);
