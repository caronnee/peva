#ifndef ___MOVEMENT____
#define ___MOVEMENT____

/* snake information structure for determining next move */

class Movement
{
public:
	/* how much the snake tend to go this way */
	int addiction; 

	/* actual direction*/
	int x, y;

	/* upper bound for checking determining next move according to random numbur in interval (0-100). we choose to go this direction, if random numebr is less than interval. The less upper bound the more pririty has dorection  */
	int interval;	

	/* constructors */
	Movement();
	Movement(int v,int x,int y);

//	Movement(const Movement& a);

	/* swaps two information movement */
	void swap(Movement &a);

	/* assign constructor */
	Movement& operator=(const Movement& a);
};

#endif
