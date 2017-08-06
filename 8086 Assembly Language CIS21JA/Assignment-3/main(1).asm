; Program template
TITLE   Assignment 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name: Rashmi Baheti
; date: 04/20/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
COMMENT !
a. you need four variables a, b, cc and result. 
   Don't use c. c is a reserved letter.
   your variables need to be 4 bytes 
   unsigned 
b. you need three prompt strings 
  
c. procedures that you need to call:
   writeString
   readDec
   writeDec 
   crlf

   Question:
Starting with the main.asm, write a complete program that will input values for a,
b and c and display the value of the expression (a + b * c)/ (2*b)
assume that the user enters only numbers that are greater than zero.
Sample run:

Enter the value of a? 3
Enter the value of b? 6
Enter the value of c? 8
The restult is:  4
Press any key to continue . . .
!

INCLUDE Irvine32.inc

.data
	a DWORD ?
	b DWORD ?
	cc DWORD ?
	result DWORD ?
	str1 BYTE "Enter the value of a: ", 0
	str2 BYTE "Enter the value of b: ", 0
	str3 BYTE "Enter the value of c: ", 0
	str4 BYTE "The value of the expression (a + b * c)/ (2*b) is: ", 0
	
.code
main proc
	MOV EDX, offset str1 
	CALL writeString ; display message for value of a.
	CALL readDec
	MOV a, EAX

	MOV EDX, offset str2 
	CALL writeString ; display message for value of b.
	CALL readDec
	MOV b, EAX

	MOV EDX, offset str3 
	CALL writeString ; display message for value of cc.
	CALL readDec
	MOV cc, EAX

	MUL b
	ADD EAX, a
	MOV result, EAX
	MOV EAX, 2
	MUL b
	MOV EBX, EAX
	MOV EAX, result
	DIV EBX
	MOV result, EAX

	MOV EDX, offset str4 
	CALL writeString 
	CALL writeDec
	CALL crlf
	CALL crlf
	
	exit
main endp
end main