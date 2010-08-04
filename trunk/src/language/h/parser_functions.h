#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "../h/robot.h"
#include "../h/lval.h"

typedef std::vector<std::string> strings;

Element ident_load(unsigned line, Robot * r, std::string s);

//Instructions check_integer(unsigned line, Element e);

Instruction * conversionToReal(unsigned line, Type t1, Type t2);

Element operRel(int line, Robot *r,Operation op, Create_type t1, Create_type t2);
Element operMul(int line, Robot * r,Operation op, Create_type t1, Create_type t2);
Element operAdd(int line, Robot * r,Operation op, Create_type t1, Create_type t2);
Element operOr(int line, Robot * r,Operation op, Create_type t1, Create_type T2);
Element feature (int line, Robot * r, ObjectFeatures feat, Element t);

Instruction* possible_conversion(unsigned line, Type to, Type from);
Instructions load_full(Node * n);
Instructions get_load_type (unsigned line, Create_type t);
Instructions get_store_type (unsigned line, Create_type t);
#endif
