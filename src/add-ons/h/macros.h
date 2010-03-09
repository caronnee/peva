#ifndef ___MACROS___
#define ___MACROS___
#ifdef DEBUG
#define TEST(x) std::cout << x ; getc(stdin);
#else 
#define TEST(x) std::cout << x ;
#endif
#endif
