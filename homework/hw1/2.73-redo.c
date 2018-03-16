#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{	int sum = x+y; 
	(!(x & INT_MIN) && (__builtin_add_overflow_p(x, y, (int)0)) && (sum = INT_MAX)) || ((x & INT_MIN) && (__builtin_add_overflow_p(x, y, (int)0)) && (sum = INT_MIN)); 
	return sum; 
}

int main(void)
{return 0;} 
