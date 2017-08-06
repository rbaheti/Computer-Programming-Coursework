; Program template
TITLE   Assignment 8
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name: Rashmi Baheti
; date: 06/11/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
COMMENT !
Write a program that would build a two-dimensional array using the inputs from
the user and find the sum of a selected row.
Your program must do the following:
Ask the user to enter how many elements the array has. The maxSize is 40.
Ask the user to enter how many elements in each row in the array.
Ask the user what type the array is. It could be byte, word or dword array.
Ask the user to enter the elements inside the array.
Ask the user for the row index and display the sum of the selected row.
Your program must have a procedure that calculates the sum of one row in the
two-dimensional array of bytes, words, or doublewords.
For the parameters and the return value use the stack.
!

INCLUDE Irvine32.inc

.data
	numElementsPrompt	Byte "Enter how many elements in your array: ", 0
	rowSizePrompt		Byte "Enter the row size: ", 0
	arrayTypePrompt		Byte "Enter the type of your array:", 0dh, 0ah, 
							 "1 for byte.", 0dh, 0ah, 
							 "2 for word.", 0dh, 0ah, 
							 "4 for doubleword.", 0

	enterArrElemtsPrompt Byte "Enter an element in your array: ", 0
	rowNumPrompt		Byte "Enter row number that you want me to sum: ", 0
	sumPrompt			Byte "The sum is: ", 0
	wrongInputPrompt	Byte "You should enter 1, 2 or 4. Please try again.", 0

	numElements	DWORD ?	
	rowSize		DWORD ?
	arrayType	DWORD ?
	rowNum		Dword ?

	arrayByte BYTE 40 Dup(0)
	arrayWord Word 40 Dup(0)
	arrayDoubleword DWord 40 Dup(0)

	rowSum DWORD 0

.code
Main proc
	;; Get user input.
	mov edx, offset numElementsPrompt
	call WriteString
	call Readint
	mov numElements, EAX
	mov edx, offset rowSizePrompt
	call WriteString
	call Readint
	mov rowSize, EAX
	mov edx, offset arrayTypePrompt
	call WriteString
	call crlf
	call Readint
	mov arrayType, EAX

	;; Check for user entered array type (byte, word or doubleword).
	cmp arrayType, 1
	JE case1
	cmp arrayType, 2
	JE case2
	cmp arrayType, 4
	JE case4
	JMP default

case1: 
	LEA EBX, arrayByte
	JMP endSwitch01
case2: 
	LEA EBX, arrayWord
	JMP endSwitch01
case4: 
	LEA EBX, arrayDoubleword
	JMP endSwitch01
default: 
	mov edx, offset wrongInputPrompt
	call writeString
	JMP endProgram

	;; Fill the array entered by the user.
endSwitch01:
	mov ecx, numElements
	mov esi, 0
L1: mov edx, offset enterArrElemtsPrompt
	call writeString
	call readInt
	mov [ebx + esi], eax
	add esi, arrayType
	Loop L1

	mov edx, offset rowNumPrompt
	call writeString
	call readInt
	mov rowNum, eax

	;; Pass arguments to the function calc_row_sum using stack.
	sub esp, 4	; Reserve space for the return value "rowSum".
	push rowNum
	push arrayType
	push rowSize
	push ebx	; Pass array's 1'st index by reference to the callee.
	call calc_row_sum	
	pop rowSum	; Read row sum from stack.

	mov edx, offset sumPrompt
	call writeString
	mov eax, rowSum
	call writeInt	; Print row sum on console.

endProgram: 
	exit
Main endp

;------------------------------------------------------------
; Procedure: calc_row_sum
; Task: Calculates the sum of a row in an array.
; Receives: row size, array type, row number and
;			array's first index.
; Returns: Sum of a row in array.
;------------------------------------------------------------
calc_row_sum PROC uses eax ecx edx esi edi
	mov eax, [esp+36]	; eax = row num
	mov edi, [esp+28]	; edi = row size
	mul edi				; eax = row num * row size
	mov edi, [esp+32]	; edi = array type
	mul edi				; eax = row num * row size * array type
	add ebx, eax		; ebx = Address of starting element of the desired row.
	mov ecx, [esp+28]	; loop counter (row size).
	
	mov edi, [esp+32]	; edi = array type
	cmp edi, 1
	JE ProcCase1
	cmp edi, 2
	JE ProcCase2
	cmp edi, 4
	JE ProcCase4

ProcCase1:
	mov	edi,0			; accumulator	
	mov	esi,0			; column index	 
L2:	movsx edx,BYTE PTR[ebx + esi]	; get a byte
	add	 edi,edx		; add to accumulator
	inc	 esi			; next byte in row
	Loop L2
	JMP endSwitch02

ProcCase2: 
	mov	edi,0			; accumulator	
	mov	esi,0			; column index
L3:	movsx edx,Word PTR[ebx + esi]	; get a word
	add	 edi,edx		; add to accumulator
	add	 esi, 2			; next word in row
	Loop L3
	JMP endSwitch02

ProcCase4: 
	mov	edi,0			; accumulator	
	mov	esi,0			; column index
L4:	mov edx, [ebx + esi]	; get a doubleword
	add	 edi,edx		; add to accumulator
	add	 esi, 4			; next doubleword in row
	Loop L4
	JMP endSwitch02 

endSwitch02: 
	mov [esp+40],edi	; store sum in the stack
	ret 16
calc_row_sum ENDP

end Main