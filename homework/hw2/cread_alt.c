#include <stdio.h>
//used on lnxsrv06 with O1 optimization
//used the following commands:
//gcc -O1 -S cread_alt.c
//gcc -O1 -c cread_alt.s
//objdump -d cread_alt.o
long cread_alt(long * xp)
{  
    long test = 0;
    return *(xp ? xp : &test); //check xp before we dereference.  
}
