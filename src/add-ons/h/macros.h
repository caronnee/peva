#ifndef ___MACROS___
#define ___MACROS___
//#define DEBUG
#ifdef DEBUG
#define TEST(x) std::cout << x ; getc(stdin);
#else 
#define TEST(x) 
#endif
#endif
