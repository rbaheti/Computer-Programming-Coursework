Part one: (22 Points)

1. Assume that you are given values in eax,ebx,ecx. Write code that adds the values inside all those registers, and stores the final result inside edx.  
Solution: add eax, ebx  
	  add eax, ecx  
	  mov edx, eax  

2. Write a piece of code that copies the number inside al (Only 8 bits) into whole edx, so that the value inside edx will be equal to the value inside the original al.  
Solution: mov edx, 0h  
	  movzx edx, al  


3. You are given eax = 0x1. Could you zero eax using only ADD instructions? What is the lowest number of ADD instructions that you need to use to acheive that result.  
Solution: add eax, 0FFFFh  
    	  The lowest number of ADD instructions we need to zero eax is 1.  


4. Write a piece of code that calculates the following expression: eax = (eax + ebx) - (ecx + edx)  
Solution: add eax, ebx  
	  add ecx, edx  
	  sub eax, ecx  


5. Write a piece of code that implements the following C++ statement x = y = 1; // x and y are of size word (2 bytes)  
Solution: mov y, 1  
	  mov ax, y  
	  mov x, ax  


6. Write a piece of code that implements the following C++ statements  
d = 'z'; // a ,d,b are of size byte. use the ascii code for z.  
a = d;  
b = a;  
Solution: mov d, 7Ah  
	  mov al, d  
	  mov a, al  
	  mov b, al  

Part two:(8 points)

Copy C:\irvine\Examples\Project_sample to your local directory.  
Open the project and open sample.asm  
  
Before the exit line of code, add the line of code:  
mov ebx, -18  

Save and build the project. Set a breakpoint at the mov line that you just added. Run to the break point. Open the debug window to see all the registers. Select Step Into (F11) to run the mov line of code. Show what values are in the following registers:  
BL:EE  
BH:FF  
BX:FFEE  
EBX:FFFFFFEE  


 
