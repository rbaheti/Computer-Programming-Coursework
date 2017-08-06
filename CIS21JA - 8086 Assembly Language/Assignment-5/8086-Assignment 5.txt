; Program template
TITLE   Assignment 5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name: Rashmi Baheti
; date: 05/09/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

INCLUDE Irvine32.inc

.data
	num1 SDWORD 0
	num2 SDWORD 0
	sum SDWORD 0
	difference SDWORD 0
	integerPrompt BYTE "Enter an integer: ", 0
	sumDisplay BYTE "Sum: ", 0
	diffDisplay BYTE "Difference: ", 0
	pressKeyPrompt BYTE "Press any key...", 0
	
.code
main proc

Comment !	
	MOV dh,10 ; row 10
	MOV dl,20 ; column 20
	CALL Gotoxy

	MOV edx, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num2, EAX

	MOV dh,11 ; row 10
	MOV dl,20 ; column 20
	CALL Gotoxy

	MOV edx, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num2, EAX
	!

	MOV ECX, 3
	MOV bh,10
L1:	
	CALL Locate
	CALL Input
	CALL CalSum
	CALL Locate
	CALL DisplaySum
	CALL CalDiff
	CALL Locate
	CALL DisplayDiff
	CALL Locate
	CALL WaitForKey
	;CALL CLEAR SCREEN HERE
Loop L1
 
Locate PROC
	MOV dh,bh ; row 10
	MOV dl,20 ; column 20
	CALL Gotoxy
	INC bh
	RET
Locate endp

Input PROC
	MOV EDX, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num1, EAX
	CALL Locate
	MOV edx, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num2, EAX
	RET
Input endp 

CalSum PROC
	MOV ESI, num1
	Add ESI, num2
	MOV sum, ESI
	RET
CalSum endp

CalDiff PROC
	MOV EAX, 0
	MOV EAX, num1
	SUB EAX, num2
	MOV difference, EAX
	RET
CalDiff endp

DisplaySum PROC
	MOV EDX, offset sumDisplay
	CALL writeString
	MOV EAX, sum
	CALL writeDec
	CALL crlf
	RET
DisplaySum endp

DisplayDiff PROC
	MOV EDX, offset diffDisplay
	CALL writeString
	MOV EAX, difference
	CALL writeDec
	CALL crlf
	RET
DisplayDiff endp

WaitForKey PROC
	MOV EDX, offset pressKeyPrompt
	CALL writeString
	CALL readChar
	RET
WaitForKey endp
	
	exit
main endp
end main