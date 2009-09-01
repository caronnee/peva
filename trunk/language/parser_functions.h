#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "./robot.h"
#include "./header1.h"

typedef std::vector<std::string> strings;

Element ident_load(unsigned line, Robot * r, std::string s);

Instruction * conversionToReal(Type t1, Type t2);
void reg(Robot *p, std::vector<Parameter_entry> s, Instructions i);
void set_breaks(Robot * p, Instructions i);

Instructions assign_default(int line, Robot * r, Node * n, Constr&l);
Element operRel(int line, Robot *r,Operation op, Create_type t1, Create_type t2);
Element operMul(int line, Robot * r,Operation op, Create_type t1, Create_type t2);
Element operAdd(int line, Robot * r,Operation op, Create_type t1, Create_type t2);
Element operOr(int line, Robot * r,Operation op, Create_type t1, Create_type T2);
Instructions feature (int line, Robot * r, ObjectFeatures feat, Create_type t);

Instruction* possible_conversion(Type to, Type from);
Instructions join_instructions(Instructions a, Instructions b);
Instructions load_full(Node * n);
#endif
