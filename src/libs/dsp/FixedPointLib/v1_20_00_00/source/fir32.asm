;;#############################################################################
;;! \file source/fir32.asm
;;!
;;! \brief  32-bit FIR filter
;;!
;;! \date   Jan 11, 2011
;;! 
;;
;;  Group:            C2000
;;  Target Family:    C28x
;;
;; (C)Copyright 2014, Texas Instruments, Inc.
;;#############################################################################
;;$TI Release: C28x Fixed Point DSP Library V1.20.00.00 $
;;$Release Date: Oct 23, 2014 $
;;#############################################################################
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference
    .def      _FIR32_init
    .def      _FIR32_calc
;;               
;;=============================================================================
;; Routine Type  : C Callable
;; Description   :
;; void FIR16_calc(FIR16_handle) 
;;       
;; This routine implements the non-recursive difference equation of an 
;; all-zero filter(FIR), of order N. All the coefficients of all-zero 
;; filter are assumed to be less than 1 in magnitude.
;;=============================================================================
;;
;; Difference Equation :
;;
;;       y(n)=H(0)*x(n)+H(1)*x(n-1)+H(2)*x(n-2)+....+H(N)*x(n-N)
;;
;;      where
;;              y(n)=output sample of the filter at index n 
;;              x(n)=input sample of the filter at index n 
;;
;; Transfer Function :
;;                                  
;;              Y(z)                -1        -2               -N+1       -N
;;             ----- = h(0) + h(1) z  + h(2) z  + ... +h(N-1) z   + h(N) z    
;;              X(z)
;;
;;     Network Diagram  : 
 ;
;;     dbuffer[0]          dbuffer[1]    dbuffer[2]    dbuffer[N}
;;     Input           -1  x(n-1)  -1    x(n-2)        x(n-N)
;;   x(n) >------o----z---->-o----z---->-o---  - ->- - o
;;               |           |           |             |
;;               |           |           |             |
;;               |           |           |             |
;;               v H(0)      v H(1)      v H(2)        v H(N)  
;;               |           |           |             |  
;;               |           |           |             |        output
;;               |---->-----(+)---->----(+)-- - -> -  (+)-----> y(n)    
;;
;;       Symbols Used :
;;             H(0),H(1),H(2),...,H(N) : filter coefficients
;;            x(n-1),x(n-2),...,x(n-N) : filter states
;;                                x(n) : filter input 
;;                                y(n) : filter output
;;=============================================================================
;;  Function Input: This function accepts the handle of the below structure
;;
;; typedef struct { <------------ XAR4
;;     int32_t *coeff_ptr;      /*  +0  Pointer to Filter coefficient */
;;     int32_t * dbuffer_ptr;   /*  +2  Delay buffer ptr              */
;;     int16_t cbindex;         /*  +4  Circular Buffer Index         */
;;     int16_t order;           /*  +5  Order of the Filter           */
;;     int16_t input;           /*  +6  Latest Input sample           */ 
;;     int16_t output;          /*  +7  Filter Output                 */
;;     void (*init)(void *);    /*  +8  Ptr to Init funtion           */
;;     void (*calc)(void *);    /*  +10 Ptr to calc fn                */  
;; }FIR32;  
;;       

_FIR32_init:
    ADDB      XAR4,#2
    MOV       *+XAR4[4],#0          ; XAR4->ouput, input=0
    MOV       *+XAR4[6],#0          ; output=0

    MOVL      XAR6,*XAR4            ; XAR6=dbuffer_ptr
    MOV       ACC,*+XAR4[3] << 1    ; AL=2*order
    MOV       AH,AL                 ; AH=2*order
    ADDB      AL,#1                 ; AL=2*order+1
    MOV       *+XAR4[2],AH          ; cbindex = 2*order (will wrap around if offset > 2*order)

    RPT       AL
 || MOV       *XAR6++,#0
    
    LRETR

ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 

FILTER_SIZE   .set     44

_FIR32_calc:    
    PUSH      XAR1                  ; Context Save           
                                    
    SETC      SXM,OVM               ; AR4=FIR16_handle->coeff_ptr 
    SPM       0                     ; Create guard band of >> 6
                                    
    MOVL      XAR7,*XAR4            ; XAR4->coeff_ptr, XAR7=coeff_ptr    
    MOVZ      AR1,*+XAR4[4]         ; XAR4->coeff_ptr, AR1=cbindex
                                    
    MOVL      XAR6,*+XAR4[2]        ; XAR4->coeff_ptr, XAR6=dbuffer_ptr
    MOVL      ACC,*+XAR4[6]         ; ACC = X:Input  
              
    MOVL      *XAR6%++,ACC          ; Store in data array and inc circ address 
    MOVL      *+XAR4[2],XAR6        ; XAR4->coeff_ptr, update the dbuffer pointer
              
    MOV       ACC,*+XAR4[5]         ; AR0=order
    MOVZ      AR0,AL                ; AR0=order
              
    ZAPA                            ; Zero the ACC, P registers and OVC counter
    ;; <<VC140828 - debug only
    ;;.asg	  0, N
    ;;.loop
    ;;QMACL     P,*+XAR6[AR1%++],*XAR7++           ; ACC = ACC + P << PM = ACC + P << 0
    ;;                                             ; P = (signed[*+XAR6[AR1%++]] * signed[*XAR7++]) >> 32
    ;;.eval    N + 1, N                            ; increment N
    ;;.break   N = FILTER_SIZE
    ;;.endloop
    ;; VC140828>>
    RPT       AR0
 || QMACL     P,*XAR6%++,*XAR7++
              
    ADDL      ACC,P                 ; Add the two sums with shift 
                                    
    ADDB      XAR4,#1               
    MOVL      *+XAR4[7],ACC         ; Store saturated result (Q30) 
              
    SPM       0
              
    POP       XAR1 
    CLRC      OVM
    LRETR      
    
;;#############################################################################
;;  End of File
;;#############################################################################
