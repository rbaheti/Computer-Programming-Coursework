INCLUDE Irvine32.inc

.data
	a DWORD ?
	b DWORD ?
	cc DWORD ?
	result DWORD ?
	str1 BYTE "Enter the value of a: ", 0
	str2 BYTE "Enter the value of b: ", 0
	str3 BYTE "Enter the value of c: ", 0
	str4 BYTE "The value of the expression (a + b * c)/ (2*b) is: ", 0
	
.code
main proc
	MOV EDX, offset str1 
	CALL writeString ; display message for value of a.
	CALL readDec
	MOV a, EAX

	MOV EDX, offset str2 
	CALL writeString ; display message for value of b.
	CALL readDec
	MOV b, EAX

	MOV EDX, offset str3 
	CALL writeString ; display message for value of cc.
	CALL readDec
	MOV cc, EAX

	MUL b
	ADD EAX, a
	MOV result, EAX
	MOV EAX, 2
	MUL b
	MOV EBX, EAX
	MOV EAX, result
	DIV EBX
	MOV result, EAX

	MOV EDX, offset str4 
	CALL writeString 
	CALL writeDec
	CALL crlf
	CALL crlf
	
	exit
main endp
end main
