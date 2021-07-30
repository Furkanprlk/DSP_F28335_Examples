*
* The leading underscore of _lowpass_asm 
* indicates a routine that can be called by C.
*
* For the instruction LTD to work correctly, array2[] must be
* in internal data memory.

* This code does not affect array[] in the main program. 

	.global _lowpass_asm

	.sect ".data"

constants:
		.word 0
		.word 1534
		.word 3306
		.word 4961
		.word 6134
		.word 6554
		.word 6134
		.word 4961
		.word 3306
		.word 1534
	    .word 0 

array2 .set 300h

temp:   .word   0h

	.sect ".code"
	
_lowpass_asm:
        
        LAR AR6, #array2   ; Point to beginning of array2.
        MAR *, AR6         ; ARP = 6. 
*		SPLK #3FF0h, *     ; Test input. Use instead of next line.
        SACL *             ; Save new input value at array[0].
        
        LAR AR5, #constants + 10 ; Highest constant.
        LAR AR6, #array2 + 10     ; Highest value in array.
        LAR AR7, #11-1           ; Loop counter

		SPM 1              ; Shift P register before accumulation.		
        MPY #0	           ; Clear P register
        LACC #0            ; Clear accumulator
		        
loop:   LTD *-, AR5        ; Load T with array[].       
        MPY *-, AR7        ; Multiply by constants[]
        BANZ loop, *-, AR6 ; Decrement counter

		APAC 			   ; Final accumulation			
        
        SFR				   ; Maximum is 95F27A00h. Reduce to 4FA93D00h.
        
        CLRC SXM		   ; Turn off sign-extension mode.
                
        ADD #4AF9h, 15     ; Add 4FA93D00h to convert to unsigned.
        ADD #3D00h         ; Maximum value in accumulator will be 95F27A00h.
       
        SPM 0			   ; No shift for next multiply.
        
        LAR AR6, #temp     ; Temporary storage
        SACH *             ; Save high word of accumulation.
        LT *               ; Copy to T register for scaling.
        
        SPLK #13ACh, *     ; Store 13ACh in temporary storage
        MPYU *             ; Multiply by 13ACh.
        
        SPH *              ; Copy high word of result to temp
        LACC *             ; Copy high word of result to accumulator
        
        SUB #1475		   ; Test for over-range	
   		BCND done, LEQ
    	LACC #1475         ; Limit output to 1475.
        B end

done    LACC *			   ; Use un-limited value.        
        
end:    MAR *, AR1         ; Restore original value ARP
        
		RET    			   ; Return to calling program.	
