#include <stdio.h>
#include <limits.h>
int saturating_add(int x, int y)
{
	int sum = x+y; 
	
	/* If x and y are both postive, but their sum negative, we can detect
 * 	positive overflow. If x and y are both negative but their sum positive,
 * 	we can detect negative  overflow.  */
	//Trouble is, we can't use conditionals according to bit coding rules
	//We can get around this by exploiting the values of INT_MIN and INT_MAX	//INT_MIN leftmost bit is 1, and if the sum's leftmost bit is 1 that
	//indicates that the sum was negative. Using similar exploitation, if
	// x and y's leftmost bit are 0, by comparing it with INT_MAX, we can
	// check if they are both positive. If the three conditions are met,
	// i.e. each comparison holds the value 1, then positive overflow did
	// occur so the flag posOverflow will hold the value 1. If not, then it 
	//will hold 0.

	int posOverflow = (x & INT_MAX) && (y & INT_MAX) && (sum & INT_MIN); 
	
	//The argument indicated prior also applies for determining negative
	//overflow, except that we have to check if x and y are negative by
	//comparing INT_MIN, and check if the sum is positive by comparing with
	//INT_MAX. If all three statements hold, then negative overflow occured
	//and the flag negOverflow will hold the value 1. If not, it will hold 0

	int negOverflow = (x & INT_MIN) && (y & INT_MIN) && (sum & INT_MAX);

	/* if there is positive overflow, should return INT_MAX. If there was
 	negative overflow, should return INT_MIN. Otherwise, return the sum of
	passed values x and y */
	(posOverflow && (sum = INT_MAX)) || (negOverflow && (sum = INT_MIN)); 

	return sum; 
}

int main(void)
{return 0;}


