INCLUDE Irvine32.inc

.DATA
	str1 BYTE "Please enter 10 non-zero, non-negative values: ",  0dh, 0ah, 0
	str2 BYTE "Please enter your number: ", 0
	sumResult BYTE "The sum is: ", 0
	meanResult BYTE "The mean is: ", 0
	str3 BYTE "/10", 0
	space BYTE " ", 0
	originalArray BYTE "Original Array is: ", 0
	rotation BYTE "After a rotation: ", 0
	last_ECX_value DWORD 0		; last_ECX_value is used to keep track of ECX in loop L3
	last_EBX_value DWORD 0		; last_EBX_value is used to keep track of EBX in loop L3

	array DWORD 10 DUP(?)
	sum DWORD 0
	mean DWORD 0
	inc_array BYTE 0

.CODE
main proc
	MOV EDX, offset str1 
	CALL writeString 
	MOV ECX, 10
	MOV EDI, 0
L1:								; Promts the user to enter 10 numbers
	MOV EDX, offset str2
	CALL writeString
	CALL readDec
	MOV array[EDI], EAX			; Saves numbers in a 32 bit integer array.
	ADD EDI, 4
	ADD sum, EAX				; Calculates the sum of the numbers in array
	LOOP L1

	CALL crlf
	MOV EAX, sum				
	MOV EDX, offset sumResult	; Displays the sum of the numbers.
	CALL writeString
	CALL writeDec
	CALL crlf
	CALL crlf

	MOV EDX, 0					; Calcualtes the mean of the array
	MOV ECX, 10
	DIV ECX
	MOV EBX, EDX
	MOV EDX, offset meanResult	; Displays the mean of the array.
	CALL writeString
	CALL writeDec
	MOV EAX, EBX
	MOV EDX, offset space
	CALL writeString
	CALL writeDec
	MOV EDX, offset str3		; Displays the decimal value of the mean.
	CALL writeString
	CALL crlf
	CALL crlf

	MOV EDX, offset originalArray
	CALL writeString
	MOV ECX, 10
	MOV EBX, 0
L2:
	MOV EAX, [array + EBX]
	CALL writeDec				; Prints the array with the same order it was enterd.
	MOV EDX, offset space
	CALL writeString
	ADD EBX, 4
	LOOP L2
	CALL crlf
	CALL crlf

	MOV ECX, 9					; LOOPS L3 and L4 are used to rotate contentes of array
	MOV EBX, 0					; EBX is used to manipulate array index
	MOV EDI, 10					; EDI register is used to keep track of L4 counter
L3:	MOV last_ECX_value, ECX		; Rotates the members in array forward one position for 9 times
	MOV ECX, EDI	
	MOV ESI, [array + 36]
	MOV last_EBX_value, EBX

L4:	XCHG ESI, [array + EBX]		; Exchange the values of array and ESI counter
	ADD EBX, 4
	LOOP L4						; End of loop L4

	MOV EDX, offset rotation	
	CALL writeString
	MOV ECX, 10
	MOV EBX, 0

L5:	MOV EAX, [array + EBX]
	CALL writeDec				; Prints the array contents after each rotation.
	MOV EDX, offset space
	CALL writeString
	ADD EBX, 4
	LOOP L5
	CALL crlf

	MOV EBX, last_EBX_value
	ADD EBX, 4					; Move EBX to next array index
	SUB EDI, 1
	MOV ECX, last_ECX_value
	LOOP L3						; end of loop L3

	exit
main endp
end main