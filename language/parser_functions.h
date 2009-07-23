#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "./tree/my_stack.h"
#include "./header1.h"

typedef std::vector<std::string> strings;
void add_variables(Program * p, strings s, Create_type t);
/*void add(Program * p, std::vector<std::string>, Type t);
void add(Program * p, std::string s, Type t);
void add(Program * p, std::string s, int value);
void add(Program * p, std::string s, float value);
void add(Program * p, std::string s, Location l);

void set_element_type(Program *p, std::vector<Array *> arr, Type t);

Node * add_array(Program *p, std::string s, std::vector<int> range, Type t);
Node * add_array(Program *p, std::string s);
void add_array(std::vector<Node *> n, Type t);
*/
Instruction * operRel(Operation op);
#endif
