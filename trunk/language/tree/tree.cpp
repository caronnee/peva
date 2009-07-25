#include "tree.h"
#include <iostream>

void Tree::reset()
{
inner_node = false;
	depth = 0;
	for (int i =0; i< 256; i++)
		next[i] = NULL;
}
Tree::Tree()
{
	reset();
}
Tree::Tree(int d)
{
	reset();
	depth = d;
}
std::string quicksort(std::string s)
{
	if (s.length()<=1)
		return s;
	std::string s1 ="",s2 ="";
	for (size_t i =1; i< s.length();i++)
		if (s[i] < s[0]) s1+=s[i];
		else s2+=s[i];
	return quicksort(s1) + s[0] + quicksort(s2);
}
