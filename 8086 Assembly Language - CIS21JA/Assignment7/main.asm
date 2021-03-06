﻿INCLUDE Irvine32.inc

.DATA
	num1	DWORD ?
	num2	DWORD ?
	result	DWORD ?
	integerPrompt BYTE	"Please enter an unsigned integer: ", 0
	displayResult BYTE	"The multiplication of 2 entered integers is: ", 0
	pressKeyPrompt BYTE "Press Enter and Continue...", 0

.CODE
Main PROC
while01:
	CALL Input
	MOV EAX, 0FFFF80C0h
	CWD
	MOV EAX, num1
	OR EAX, num2	;; Use OR instruction to check if the
	CMP EAX, 0		;; user enters 0 for both inputs.
	JE endWhile01
	SUB ESP, 4
	PUSH num2
	PUSH num1
	CALL Multiply
	POP result
	MOV EDX, offset displayResult
	CALL WriteString
	MOV EAX, result
	CALL WriteDec	;; Display result (multiplication) on console.
	CALL crlf
	CALL WaitForKey
	CALL ClrScr
	CALL while01
endWhile01:
	exit
Main endp

;-------------------------------------------------------------------
;Procedure: Input
;Task: This procedure prompts the user for 2 integers and saves the
;input in variables num1 and num2.
;Recieves: 2 integers from user.
;Returns: Nothing.
;-------------------------------------------------------------------
Input PROC
	MOV EDX, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num1, EAX
	MOV edx, offset integerPrompt
	CALL writeString
	CALL readDec
	MOV num2, EAX
	RET
Input endp 

;-------------------------------------------------------------------
;Procedure: Multiply
;Task: This procedure multiplies 2 unsigned integers and saves the
;result in variable result.
;Recieves: 2 integers.
;Returns: Multiplication of 2 integers.
;-------------------------------------------------------------------
Multiply PROC
	PUSH EBP	
	MOV EBP, ESP
	PUSH EBX	;; Preserving values of all the registers, i.e.
	PUSH ECX	;; EBX, ECX, ESI and EDX as they are used in
	PUSH ESI	;; this procedure.
	PUSH EDX
	MOV EBX, 0	;; EBX is used to Add and store the result of addition.
	MOV ECX, 32	;; Initializing the counter.
	MOV ESI, [EBP+8]	;; ESI = num1
	MOV EDX, [EBP+12]	;; EDX = num2
L1:
	SHR EDX, 1
	JNC endif01
	ADD EBX, ESI
endif01:
	SHL ESI, 1
	Loop L1
	MOV [EBP+16], EBX

	POP EDX
	POP ESI
	POP ECX
	POP EBX
	POP EBP
	RET 8
Multiply endp

;-----------------------------------------------------------
;Procedure: WaitForKey
;Task: This procedure displays "Press Enter and Continue..." and
;waits for an input.
;Recieves: A character
;Returns: Nothing.
;-----------------------------------------------------------
WaitForKey PROC
	MOV EDX, offset pressKeyPrompt
	CALL writeString
	CALL readChar
	RET
WaitForKey endp

end Main
