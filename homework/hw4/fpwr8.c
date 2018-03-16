#include <stdio.h>
static float u2f(unsigned u)
{
	/*Must return bit representation. Can't type cast*/
	union {
		unsigned s; 
		float f; 
	} result; 
	result.s = u; 
	return result.f; 
}

float fpwr8(int x)
{
	unsigned exp, frac; 
	unsigned u; 
	if (x < -49)
	{
	/*Too small, return 0.0 */
		exp = 0; 
		frac = 0; 
	}
	else if(x < -42)
	{
	/*Denormalized result*/ 
		exp = 0;
		frac = 1 << (149 + (x*3)); 
	}
	else if(x < 43)
	{
	/*Normalized result*/ 
		exp = 127 + (x*3);  
		frac = 0; 
	}
	else
	{
	/*Too big. Return +infinity*/
		exp = 255; 
		frac = 0; 
	}
	/*Pack exp and frac into 32 bits */
	u = exp << 23 | frac; 
	/*Return as float*/
	return u2f(u); 
}
