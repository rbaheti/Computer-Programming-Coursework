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
	sumDisplay BYTE "The sum is: ", 0
	diffDisplay BYTE "The difference is: ", 0
	pressKeyPrompt BYTE "Press any key...", 0
	
.code
Main proc

	MOV ECX, 3
L1:	CALL clrscr		; Clears screen 
	MOV bh,10		; Reset the value of BH register (which then resets DH register).
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
Loop L1

	CALL Locate
	exit
main endp

;-------------------------------------------------------
;Procedure: Locate
;Task: This procedure locates the cursor in the middle
;of the screen.
;Recieves: 
;1. Y-coordinate (row) in DH and 
;2. X-coordinate (column) in DL
;Returns: Nothing (Locates cursor on X-Y co-ordinate)
;-------------------------------------------------------
Locate PROC
	MOV dh,bh ; row 10
	MOV dl,20 ; column 20
	CALL Gotoxy
	INC bh
	RET
Locate endp

;-------------------------------------------------------
;Procedure: Input
;Task: This procedure prompts the user and saves the
;input in variables num1 and num2.
;Recieves: 2 integers from user.
;Returns: Nothing.
;-------------------------------------------------------
Input PROC
	MOV EDX, offset integerPrompt
	CALL writeString
	CALL readInt
	MOV num1, EAX
	CALL Locate
	MOV edx, offset integerPrompt
	CALL writeString
	CALL readInt
	MOV num2, EAX
	RET
Input endp 

;-------------------------------------------------------
;Procedure: CalSum
;Task: This procedure calculates the sum of 2 integers.
;Recieves: 2 integers stored in variables num1 and num2.
;Returns: Sum of the 2 integers.
;-------------------------------------------------------
CalSum PROC
	MOV ESI, num1
	Add ESI, num2
	MOV sum, ESI
	RET
CalSum endp

;-------------------------------------------------------
;Procedure: CalDiff
;Task: This procedure calculates the difference between
; 2 integers.
;Recieves: 2 integers stored in variables num1 and num2.
;Returns: Difference of the 2 integers.
;-------------------------------------------------------
CalDiff PROC
	MOV EAX, 0
	MOV EAX, num1
	SUB EAX, num2
	MOV difference, EAX
	RET
CalDiff endp

;-------------------------------------------------------
;Procedure: DisplaySum
;Task: This procedure displays the sum of 2 integers.
;Recieves: sum of 2 integers
;Returns: Nothing (Displays the sum on the console).
;-------------------------------------------------------
DisplaySum PROC
	MOV EDX, offset sumDisplay
	CALL writeString
	MOV EAX, sum
	CALL writeInt
	CALL crlf
	RET
DisplaySum endp

;-----------------------------------------------------------
;Procedure: DisplayDiff
;Task: This procedure displays the difference of 2 integers.
;Recieves: difference of 2 integers
;Returns: Nothing (Displays the difference on the console).
;-----------------------------------------------------------
DisplayDiff PROC
	MOV EDX, offset diffDisplay
	CALL writeString
	MOV EAX, difference
	CALL writeInt
	CALL crlf
	RET
DisplayDiff endp

;-----------------------------------------------------------
;Procedure: WaitForKey
;Task: This procedure displays "Press any key..." and
;waits for an input.
;Recieves: A character
;Returns: Nothing (Displays "Press any key..." on console).
;-----------------------------------------------------------
WaitForKey PROC
	MOV EDX, offset pressKeyPrompt
	CALL writeString
	CALL readChar
	RET
WaitForKey endp

end Main