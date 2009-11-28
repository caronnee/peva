#include <vector>
#include <SDL/SDL.h>

class Board
{
	int min_y;
	std::vector <Action *> actions; //akcie, ktore sa maju vykonat na ploche, vratane botov, vsetko pohromade, strely sa vytvaraju a pridavaju tu
	std::vector <Bot *> bots; //vsetci boti na danej boarde
	int Max_bots, Min_bots; //minimalny a maximalny pocet botov, bude existovat este aj vychod alebo ;treasure alebo co vlastnem bud pre kazdeho bota v=zvlast alebo spolocne -> typ hry 
	Walls*** gameboard;
	int begin_x, begin_y; //Odkial sa zacne vykreslovat
	int resolution_x, resolution_y; // Velkost okna, do ktoreho sa to vykresluje, v pixeloch
	int number_x, number_y; //cislo, od ktoreho sa vykresluje
	bool generate(); //generovanie celeho pola, pozdejc s parametrami, kolko toho ma byt, vracia, ci sa podarilo alebo nie, ak nie, skusi to s inym 'grainsize' -> problem bude pravdepodobne v pamati
public:
	Board();
	void action(); // zoberie, co ma v actions a spusti
	int add_bot(Bot * bot); // prida bota do pola, moze sa pouzij aj pocas uz prebiehajucej hry, vracia int, ici sa to podarilo alebo je to locked na pocet botov
	void draw_board(); //vykresli od pola, ktroe je viditelne
}

