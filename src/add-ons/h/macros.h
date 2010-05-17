//#define DEBUG
#ifdef DEBUG
#define TEST(x) { std::cout << x ; getc(stdin); }
#else 
#define TEST(x) { std::cout << x << std::endl;}
#endif

#define List std::list<Object *>
#define TEST_RELEASE(x) std::cout << x << std::endl;
