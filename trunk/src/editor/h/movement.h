#ifndef ___MOVEMENT____
#define ___MOVEMENT____

class Movement
{
public:
	int addiction, x, y, interval;	
	Movement();
	Movement(int v,int x,int y);
//	Movement(const Movement& a);
	void swap(Movement &a);
	Movement& operator=(const Movement& a);
};

#endif
