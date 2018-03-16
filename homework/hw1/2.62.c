#include <stdio.h>

int int_shifts_are_arithmetic(void)
{
	int x = ~0; /* This makes x holds all 1's. By doing this we can tell
	if the said machine performs arithmetic or logical right shifts. */
	return ((x>>1) == x); /*If logical, will be shifted to the right by one, and the most significant bit will be 0 [01....11] , which changes the value of x,thus not equal to itself, returning 0. If arithmetic, will be shifted to the right by one, but the most significant bit will still be a 1 [1....11] , thus equivalent to the defined value x.*/  

}

int main(void)
{ return 0; }
