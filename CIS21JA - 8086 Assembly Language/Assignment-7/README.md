Assignment 7

Question:  
Write a complete program that:  
1.Asks the user to enter 2 numbers. Assume that the user enters unsigned  32-bit integers only.  
2.Displays the product of the two numbers. Assume that the result will never be larger than 32 bits.  
3.This process will continue till the user enters 0 for both inputs.  

You can’t use mul instruction in your program. You need to use shifting and addition only.  

Your program must have at least one procedure called multiply.  
1.This procedure can’t use any global variables (variables that are inside .data segment).  
2.The caller of this procedure sends its argument through the stack.  
3.The procedure receives the multiplicand and multiplier through the stack. It returns the product through the stack also. No passing by registers.  
4.Inside your procedure if you need to use a register, you have to preserve its original value.You can't use uses operator.  
5.The procedure is in charge of cleaning the stack.

