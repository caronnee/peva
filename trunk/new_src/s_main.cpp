#include "seer.h"

int main()
{
	Position res(4,6);
	Seer s(res);
	s.set_masks();
	s.output();
	return 0;
}
