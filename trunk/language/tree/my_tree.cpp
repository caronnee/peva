#include <iostream>
#include "my_stack.h"

int main(int c, char** r)
{
	Create_type t(TypeInteger);
	Program b; 
	std::cout << "Aplhabet:" << b.alphabet << std::endl;
	std::string s[] = {"came", "car","cat", "cave", "cy", "cyan", "we", "went", "were", "west", "western"}; 
	std::string a = ".0123456789ABCDEFGHIJKLMNOPQRSTUVXYZ_abcdefghijklmnopqrstuvxyz";
	for (int i =0; i< 11; i++)
		b.add(s[i],new Node(t));
	std::cout << "zacinam vypisovat:" << b.defined.depth << std::endl;
	b.output(&b.defined);
/*	for (int i =0; i< b.alphabet.length(); i++)
	{
		std::cout << b.find_index(b.alphabet[i]) << std::endl;
	}*/
	return 0;
}
