TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

INCLUDE Irvine32.inc
.data
myMessage BYTE "Hello world!"

.code
main PROC
	call Clrscr

	mov	 edx,OFFSET myMessage
	call WriteString

	exit
main ENDP

END main