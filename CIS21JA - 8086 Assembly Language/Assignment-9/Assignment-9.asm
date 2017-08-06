; Program template
TITLE   Assignment 9
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name: Rashmi Baheti
; date: 06/13/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
COMMENT !
Assignment 9: This assignment is closed on Saturday 11:55 PM. No assignments
will be accepted after that. No exceptions.
Write a complete program that sorts dword unsigned integer array in 
descending order.
Assume that the user doesn’t enter more than 40 integers.
You have to use the template and follow all the directions there.
Sample run ( not unique):

Enter up to 40 unsigned dword integers. To end the array, enter 0.
After each element press enter: 1
4
3
8
99
76
34
5
2
17
0
Initial array:
1 4 3 8 99 76 34 5 2 17
Array sorted in descending order:
99 76 34 17 8 5 4 3 2 1
Press any key to continue . . .
!

INCLUDE Irvine32.inc

; ===============================================
.data
  array			Dword 40 dup(?)
  arrayLength	Dword ?

  enterIntegersPrompt Byte "Enter up to 40 unsigned dword integers. ",
						   "To end the array, enter 0.", 0dh, 0ah,
						   "After each element press enter: ", 0dh, 0ah
;=================================================
.code
main proc
	sub esp, 4	; store space for 
	lea ebx, array
	push ebx
	lea edx, enterIntegersPrompt
	push edx
	call enter_elem
    pop arrayLength
	
	push arrayLength
	push ebx	;; Push starting address of array on stack
	mov eax, [ebx]
	call writeInt
	call print_arr
	mov eax, ecx
	; FILL YOUR CODE HERE 
	; YOU NEED TO CALL ENTER_ELEM, SORT_ARR AND PRINT_ARR PROCEDURES
	; 
	
   

   exit
main endp

; ================================================
; enter_elem(arr_addr)
;
; Input:
;   ARR_ADDRESS THROUGH THE STACK
; Output:
;   ARR_LENGTH THROUGH THE STACK
; Operation:
;   Fill in the array with user input integers.
;	Save the array length in ecx register.

enter_elem proc
	push ebp	
	mov ebp, esp
	push edx
	mov edx, [ebp+8]
	call writeString
	push eax
	push esi
	push ecx
	mov ecx, 0
	mov esi, 0

L1:	call readInt
	cmp eax, 0
	je endif01
	mov [edx+esi], eax
	add esi, 4
	inc ecx
	JMP L1

endif01:
	mov [ebp + 16], ecx
	pop ecx
	pop esi
	pop eax
	pop edx
	pop ebp
	ret 8
enter_elem endp

; ================================================
; print_arr(arr_addr,arr_len)
;
; Input:
;   array address and array length
; Output:
;   Contents of array
; Operation:
;   Use array address and array count to print
;	the contents in array.

print_arr proc
	push ebp	
	mov ebp, esp
	push ecx
	push ebx
	push edi
	push eax
	mov ecx, [ebp+12]
	mov ebx, [ebp+8]
	mov edi, 0
	mov eax, [ebx]
	call writeInt

L2: mov eax, [ebx+edi]
	call writeInt
	add edi, 4
	Loop L2

	pop eax
	pop edi
	pop ebx
	pop ecx
	pop ebp
  ; FILL YOUR CODE HERE

print_arr endp

; ================================================
; sort_arr(arr_addr,arr_len)
;
; Input:
;   ?
; Output:
;   ?
; Operation:
;   ?
;

sort_arr proc

   ; FILL YOUR CODE HERE
   ; YOU NEED TO CALL COMPARE_AND_SWAP PROCEDURE 

sort_arr endp

; ===============================================
; compare_and_swap(x_addr,y_addr)
;
; Input:
;   ?
; Output:
;   ?
; Operation:
;   ?
;

compare_and_swap proc

   ; FILL YOUR CODE HERE
   ; YOU NEED TO CALL SWAP PROCEDURE 

compare_and_swap endp

; =================================================
; swap(x_addr,y_addr)
;
; Input:
;   ?
; Output:
;   ?
; Operation:
;   SWAP ONLY IF Y > X
;

swap proc

   ; FILL YOUR CODE HERE

swap endp

end main