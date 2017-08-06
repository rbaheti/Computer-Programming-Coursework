; Program template
TITLE   Assignment 6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name: Rashmi Baheti
; date: 05/16/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
COMMENT !
A prime number is an integer that is divisible only by 1 and by itself.
Write a program that:
1. Takes a number as an input.
2. Prints back to the console all the primes that are larger than 1 
but not larger than the number that has been entered.
You need to have a procedure called isPrime. 
You may have more procedures, if you like.
1. This procedure receives a number through one of the registers.
2. Check if this number is prime.
3. Returns back to the main program 1, if the number is prime, 0 otherwise, 
through one of registers.

You need to add comments at least on these places:
1. At the top of your program, name and date.
2. At the top of each procedures
3. Before any if, while, for statements.
4. Before any multiplication or division statements.
!

INCLUDE Irvine32.inc

.data
	input_num DWORD 0;	Store input from user.
	prime DWORD 0
	integer_prompt BYTE "Please enter an integer: ", 0 
	display_prime_nos BYTE "Prime numbers upto given number are: ",0
	space BYTE " ", 0

.code
main proc
	CALL Input
	CALL DisplayOutput
	CALL IsPrime
	CALL crlf
	exit
main endp

Input PROC
	MOV EDX, offset integer_prompt
	CALL writeString
	CALL readDec
	MOV input_num, EAX
	RET
Input endp

DisplayOutput PROC
MOV EDX, offset display_prime_nos
	CALL writeString
	RET
DisplayOutput endp

IsPrime PROC
	MOV EBX, 2  ; outer loop [2, input_num] counter
while01:
	CMP EBX, input_num
	JG endWhile01
	MOV ESI, 2  ; inner loop [2, EBX) counter
while02:
	CMP ESI, EBX
	JGE endWhile02
	MOV EAX, EBX
	MOV EDX, 0
	DIV ESI
	CMP EDX, 0
	JNE endIf01
	MOV prime, -1
endIf01:
	INC ESI
	JMP while02
endWhile02:
	CMP prime, -1
	JE endif02
	MOV EAX, EBX
	CALL writeDec
	MOV EDX, offset space
	CALL writeString
endIf02:
	INC EBX
	MOV prime, 0
	JMP while01
endWhile01:
	RET
IsPrime endp

end main
