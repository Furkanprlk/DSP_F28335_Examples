; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;=========================================================================
;======================================================================
;
; File Name     : SGTI3DC.ASM
; 
; Originator    : Advanced Embeeded Control (AEC)
;                 Texas Instruments Inc.
; 
; Description   : This file contain source code for Dual three channel
;                 SIN generator module(Using Table look-up and Linear Interpolation)
;                 * Table look-up and linear interpolation provides, low
;                 THD and high phase Resolution
;               
; Routine Type  : CcA
;               
; Date          : 28/12/2001 (DD/MM/YYYY)
;======================================================================
; Description:
;                            ___________________
;                           |                   |
;                           |                   |------o OUT11
;                           |                   |       
;       phase   o---------->|                   |------o OUT12
;                           |                   |
;       gain    o---------->|                   |------o OUT13
;                           |                   |
;       offset  o---------->|     SGENTI_3D     |
;                           |                   |------o OUT21
;       freq    o---------->|                   |
;                           |                   |------o OUT22
;                           |                   |
;                           |                   |------o OUT23
;                           |                   |
;                           |___________________|
;
;======================================================================
; ###########################################################################
; $TI Release: C28x SGEN Library Version v1.01 $
; $Release Date: September 30, 2011 $
; ###########################################################################

; Module definition for external referance
                .def    _SGENTI_3D_calc    
                .ref    SINTAB_360   
ALPHA120        .set    05555h
ALPHA240        .set    0AAABh 
                

_SGENTI_3D_calc:      
            SETC    SXM,OVM         ; XAR4->freq
            MOVL    XAR5,#SINTAB_360

; Obtain the step value in pro-rata with the freq input         
            MOV     T,*XAR4++       ; XAR4->step_max, T=freq
            MPY     ACC,T,*XAR4++   ; XAR4->alpha, ACC=freq*step_max (Q15)
            MOVH    AL,ACC<<1           
            
; Increment the angle "alpha" by step value             
            ADD     AL,*XAR4        ; AL=(freq*step_max)+alpha  (Q0)
            MOV     *XAR4,AL        ; XAR4->alpha, alpha=alpha+step (Unsigned 8.8 format)   

; OUT11 Computation
; Obtain the SIN of the angle "X=alpha" using direct Look-up Table            
            MOVB    XAR0,#0     
            MOV     T,#0           
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format
               
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
        
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[3],AH    ; out11=Y*gain+offset

; OUT12 Computation    
; Add 120deg phase with the "alpha" of OUT1   
            MOVU    ACC,*XAR4       ; ACC=alpha
            ADD     ACC,#ALPHA120   ; ACC=alpha+120
            
            MOVB    XAR0,#0    
            MOV     T,#0
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format

                       
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
          
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[4],AH    ; out12=Y*gain+offset 
            
; OUT13 Computation    
; Add 240deg phase with the "alpha" of OUT1   
            MOVU    ACC,*XAR4       ; ACC=alpha
            ADD     ACC,#ALPHA240   ; ACC=alpha+120
            
            MOVB    XAR0,#0    
            MOV     T,#0            
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format
     
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
         
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[5],AH    ; out13=Y*gain+offset   
            
            
; OUT21, OUT22, OUT23 Computation
; Add "phase" to "alpha" of OUT11   
            MOVL    XAR6,XAR4       ; XAR6->alpha
            ADDB    XAR6,#6
            MOVU    ACC,*XAR4       ; ACC=alpha
            ADD     ACC,*XAR6       ; ACC=alpha+phase
            MOVZ    AR7,AL          ; AR7=alpha+phase

; OUT21 Computation 
            MOVB    XAR0,#0    
            MOV     T,#0
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format

                       
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
        
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR6[1],AH    ; out21=Y*gain+offset 
            
                    
; OUT22 Computation 
            MOVU    ACC,AR7         ; ACC=alpha+phase
            ADD     ACC,#ALPHA120   ; ACC=alpha+phase+120
            
            MOVB    XAR0,#0    
            MOV     T,#0            
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format
                       
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
          
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR6[2],AH    ; out22=Y*gain+offset 
            
            
; OUT23 Computation 
; Obtain the SIN of the angle "X=alpha+phase+ALPHA2400" using Look-up Table
            MOVU    ACC,AR7         ; ACC=alpha+phase
            ADD     ACC,#ALPHA240   ; ACC=alpha+phase+120
            
            MOVB    XAR0,#0    
            MOV     T,#0            
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOVB    T,AL.LSB        ; T=(X-X1) in Q8 format
          
            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q23
            LSL     ACC,8           ; ACC=Y1 in Q23
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)
            MOVH    T,ACC<<8        ; T=Y in Q15 format
          
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR6[3],AH    ; out22=Y*gain+offset 
            
        	CLRC 	OVM
        	LRETR
            
                


 

