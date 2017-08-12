TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

INCLUDE Irvine32.inc
.data

	myBytes BYTE 10h,20h,30h,40h
	myWords WORD 0Ah,3Bh,72h,44h,66h
	myDoubles DWORD 1,2,3,4,5

	myMessage BYTE "Hello world!"
	val1 BYTE 10h
	val2 WORD 8000h
	val3 DWORD 0FFFFh
	val4 WORD 7FFFh


.code
main PROC
	call Clrscr
	mov esi,OFFSET myWords + 2
	mov ax,[esi] 

	mov dx, [myWords+1]  ; dx:
	mov ax, myWords      ; ax
	mov ebx,mydoubles    ; ebx

div bx                          ; 

	ADD val2, 1
	MOV BX, 0
	MOV BX, val4
	Add BX, 1

	mov ax,7FF0h
	add al,10h ;  a. CF = 1, SF = 0, ZF = 1, OF = 1 and al = 00h
	add ah,1 ;    b. CF = 1, SF = 1, ZF = 0, OF = 0 and ah = 80h
	add ax,2 ;    c. CF = 0, SF = 1, ZF = 0, OF = 1 and ax = 80002h

	;mov edx,OFFSET myMessage
	;call WriteString

	exit
main ENDP

END main