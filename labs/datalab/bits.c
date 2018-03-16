/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
    //we only care for most sig bit. mask will start with 1 if x is neg, otheriwise mask MSB will be 0.
    int mask = (1 << 31) & x; x = ~x;
    x = x | mask; x = ~x; //negated x and or comparison to extract MSB
    x = x + 1 + ~1; x = ~x;
    x = x | mask;
    x >>= 31;
    x = x + 1;
    return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
  int group2Mask=0;
  int group4Mask=0; 
  int group8Mask=0;    
 //hamming weight!
     group2Mask = (0x55 << 8) | 0x55; group2Mask = group2Mask << 16 | group2Mask;  //this hex in binary is 01010101..., thus as a mask allows us to split the int x in bits in 16 groups of 2
    group4Mask = (0x33 << 8) | 0x33; group4Mask = group4Mask << 16 | group4Mask;//this hex in binary is 00110011..., thus allowing to group bits into 8 groups of 4
    group8Mask = (0x0F << 8)| 0x0F; group8Mask = group8Mask << 16 | group8Mask; //this hex in binary is 00001111..., thus allowing to group bits into 4 groups of 8

    //divide and conquer! we split the bits into groups, even and odds, by shifting. count, append, rinse, wash, repeat. yay parity, yay parallelism, yay hamming!
    
    x = x + (~((x >> 1) & group2Mask)+1);
    x = (x & group4Mask) + ((x >> 2) & group4Mask);
    x = (x + (x >> 4)) & group8Mask;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F; //compare to max num to return correct value
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y)
{
    return (~(~x & ~y)); // De Morgan's law!
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n)
{
    //extract the n bits from x. compare to a mask. shift (increasing each shift by a magnitude of 2^n)
    //and check that the multiple will be of x and less than 32
    //(otherwise do nothing as to prevent undefined behavior.
    int shiftCheck;  
    int mask = ((1 << n) * !(n/32)) - 1;
    int result = x & mask;
    result = result << (n * !((n/32) ^ 0)) | result; 
    shiftCheck = n / 16;
    result = result << (n << (1 * !((shiftCheck) ^ 0))) | result;
    shiftCheck = n / 8;
    result = result << (n << (2 * !((shiftCheck) ^ 0))) | result;
    shiftCheck = n / 4;
    result = result << (n << (3 * !((shiftCheck) ^ 0))) | result;
    shiftCheck = n / 2;
    result = result << (n << (4 * !((shiftCheck) ^ 0))) | result;
    return result;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
    int shift = 33 + ~n;  //-n = ~n +1. save shift bits in consideration
    //shifting back and forth changes the value depending on the sign of x.
    //in doing so, we can tell whether or not it fits. if same number post-shift,
    //it fits. otherwise it does not.
    int otherShift = x << shift;
    otherShift = otherShift >> shift;
    return !(x^otherShift);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n)
{
    x = x >> (n << 3);
    return (x & 0xFF);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
    int isDiffSignAndxisNeg = (!(x>>31)^!(y>>31)) & (x>>31);
    int isSameSignAndxisPos = !(!(x>>31)^!(y>>31)) & !((y+(~x+1))>>31);
    int result = isDiffSignAndxisNeg | isSameSignAndxisPos;
    return result;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
    int zero = !(x);
    int negative = ((x >> 31) & ~0); //compare with mask to test if negative
    return (!zero) & (!negative); //if not negative and not zero, it must be positive!

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n)
{
    int mask = 0; 
    x = x >> n; 
    mask = ~0; //all 1s
    mask <<= 32 + ~n; //31 + 1 + ~n == 32 -n
    mask <<= 1;
    mask = ~mask;
    return (x & mask);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  return (1 << 31);
}
