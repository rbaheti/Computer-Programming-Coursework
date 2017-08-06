


Title Assignment 9

COMMENT !
@@@@@@@@@@@@@@@@@
name: 
date:
@@@@@@@@@@@@@@@@@
!

include irvine32.inc
; ===============================================
.data
  


;=================================================
.code
main proc

  
    
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
;   ?
;
enter_elem proc
	
    ; FILL YOUR CODE HERE

enter_elem endp

; ================================================
; print_arr(arr_addr,arr_len)
;
; Input:
;   ?
; Output:
;   ?
; Operation:
;   ?
;

print_arr proc

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