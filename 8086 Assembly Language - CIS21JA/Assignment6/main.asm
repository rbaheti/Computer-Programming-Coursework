INCLUDE Irvine32.inc

.data
	input_num DWORD 0;	Store input from user.
	integer_prompt BYTE "Please enter a non-zero, non-negative integer: ", 0 
	display_prime_nos BYTE "Prime numbers upto given number are: ",0
	space BYTE " ", 0

.code
;-------------------------------------------------------
;Procedure: Main
;Task: This procedure calls all other procedures in the 
;program, as required.
;Recieves: Nothing.
;Returns: Nothing.
;-------------------------------------------------------
Main PROC
	CALL Input
	CALL DisplayOutput
	MOV ESI, 2
while02:	;; This while loop is used to print all the numbers which are
			;; larger than 1 and smaller and equal to the input number.
	CMP ESI, input_num
	JG endWhile02
	CALL IsPrime
	CMP ECX, 1
	JNE endif02
	MOV EAX, ESI
	CALL writeDec	;; Print number to the console if it is prime.				
	MOV EDX, offset space
	CALL writeString
endif02:
	INC ESI
	JMP while02
endWhile02:

	CALL crlf
	exit
Main endp	;; End of main procedure.

;-------------------------------------------------------
;Procedure: Input
;Task: This procedure prompts user for a number and 
;saves the input in variable input_num.
;Recieves: 1 non-negative integers from user.
;Returns: Nothing.
;-------------------------------------------------------
Input PROC
	MOV EDX, offset integer_prompt
	CALL writeString
	CALL readDec
	MOV input_num, EAX
	RET
Input endp

;-------------------------------------------------------
;Procedure: DisplayOutput
;Task: This procedure displays the output statement. 
;Recieves: Nothing.
;Returns: Nothing.
;-------------------------------------------------------
DisplayOutput PROC
MOV EDX, offset display_prime_nos
	CALL writeString
	RET
DisplayOutput endp

;-------------------------------------------------------
;Procedure: IsPrime
;Task: This procedure checks if this number is prime.
;Recieves: A number through ECX register.
;Returns: Returns back to the main program 1, if the 
;number is prime, 0 otherwise, through ECX register.
;-------------------------------------------------------
IsPrime PROC
	MOV ECX, 1
	MOV EBX, 2
while01:		;; This while loop checks if the given number is prime or not.
	CMP EBX, ESI
	JGE endWhile01
	MOV EDX, 0
	MOV EAX, ESI
	DIV EBX		;; This Division checks if the remainder is 0 or not.
	CMP EDX, 0	;; If remainder (i.e EDX) is 0, then the number is not prime.
	JNE endIf01
	MOV ECX, 0
	JMP endWhile01
endIf01:
	INC EBX
	JMP while01
endWhile01:
	RET
IsPrime endp	;; end of IsPrime procedure.

end Main	;; End of program
