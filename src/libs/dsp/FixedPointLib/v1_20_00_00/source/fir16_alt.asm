;;#############################################################################
;;! \file source/fir16_alt.asm
;;!
;;! \brief  Alternate 16-bit FIR filter
;;!
;;! \date   Aug 11, 2014
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
    .def      _FIR16_alt_init
    .def      _FIR16_alt_calc
   
;; Module Structure
;; typedef struct { <------------ XAR4
;;     int32_t *coeff_ptr;      /*  +0  Pointer to Filter coefficient */
;;     int32_t * dbuffer_ptr;   /*  +2  Delay buffer ptr              */
;;     int16_t cbindex;         /*  +4  Circular Buffer Index         */
;;     int16_t order;           /*  +5  Order of the Filter           */
;;     int16_t input;           /*  +6  Latest Input sample           */ 
;;     int16_t output;          /*  +7  Filter Output                 */
;;     void (*init)(void *);    /*  +8  Ptr to Init funtion           */
;;     void (*calc)(void *);    /*  +10 Ptr to calc fn                */  
;; }FIR16; 
;;
ARG_COEFF_PTR     .set    0
ARG_DBUFFER_PTR   .set    2
ARG_CBINDEX       .set    4
ARG_ORDER         .set    5
ARG_INPUT         .set    6
ARG_OUTPUT        .set    7
   
;;
;;=============================================================================
;;! \fn FIR_alt_init
;;! \brief Initialization function for the alternate FIR function
;;! \param FIR16_handle pointer to an FIR16 object
;;
;; This routine will zero out the dbuffer and, if necessary, alter 
;; "order" to make it even if its odd
;;
;;=============================================================================
;; 
_FIR16_alt_init:
    MOV       *+XAR4[ARG_INPUT],#0               ; input=0
    MOV       *+XAR4[ARG_OUTPUT],#0              ; output=0
              
    MOVL      XAR6,*+XAR4[ARG_DBUFFER_PTR]       ; XAR6=dbuffer_ptr            
    MOV       AL,*+XAR4[ARG_ORDER]               ; AL=order
    MOV       AH,AL                              ; AH=order
    TBIT      AL,#0                              ; if(AL(0) == 1) TC = 1 else TC = 0  
    ADDB      AL,#1                              ; AL=order+1        
    MOV       AL,AH,TC                           ; if(TC == 1(odd)) AL = order (AH)
                                                 ; else      (even) AL = order + 1 (AL)
                                                 ; make the order odd so that nTaps is even
    MOV       AH,AL                              ; AH = new_order(always odd)
    SUBB      AH,#1                              ; AH = new_order - 1 (always even)
    MOV       *+XAR4[ARG_ORDER],AH               ; order = new_order - 1 (always even)
              
    RPT       AL                                 ; repeat AL(order(TC=1)/order+1(TC=0)) + 1 times
 || MOV       *XAR6++,#0                         ; clear out the dbuffer elements
    
    LRETR
    
;;
;;=============================================================================
;;! \fn FIR_alt_calc
;;! \brief Alternate FIR function
;;! \param FIR16_handle pointer to an FIR16 object
;;
;; This routine will use the LP addressing mode for circular buffer addressing
;; i.e *+XAR6[AR1%++] instead of *AR6%++, allowing for greater than 256 tap filters
;; 
;; \note The filter coefficients need to be stored in the following order for the
;; filter to work correctly i.e. (filter size is L = Order + 1)
;;
;; Index       LSW       MSW
;;         +---------+---------+
;;  0      | h(L/2-1)| h(L-1)  |
;;  2      | h(L/2-2)| h(L-2)  |
;;  4      | h(L/2-3)| h(L-3)  |
;;  6      | h(L/2-4)| h(L-4)  |
;;  ...    | ...     | ...     |
;;  L/2-3  | h(2)    | h(L/2+2)|
;;  L/2-2  | h(1)    | h(L/2+1)|
;;  L/2-1  | h(0)    | h(L/2)  |
;;         +---------+---------+
;;
;; Register usage:
;; AR0       : repeat block counter (order)
;; AR1H/AR1L : buffer size-1/index pointer
;; XAR7      : coefficient pointer
;; XAR6      : delay line pointer (circular buffer)
;; 
;;=============================================================================
;; 

ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 

FILTER_SIZE   .set     44

_FIR16_alt_calc:
    PUSH      XAR1                               ; Context Save
    SETC      SXM, OVM                           ; Turn on sign extension and 
                                                 ; overflow mode to saturate
    SPM       -6                                 ; guard band of 6 bits for the
                                                 ; product (P) register
    MOVL      XAR7, *+XAR4[ARG_COEFF_PTR]        ; XAR7 = coeff_ptr
    MOVL      XAR6, *+XAR4[ARG_DBUFFER_PTR]      ; XAR6 = dbuffer_ptr
    MOV	      AH,   *+XAR4[ARG_ORDER]            ; ACC  = [order : 0]
    MOV       AL,   *+XAR4[ARG_CBINDEX]          ; ACC  = [order : cbindex]
    MOVL      XAR1, ACC                          ; XAR1 = [order : cbindex]
    LSR       AH, #1                             ; AH = order/2
    MOV       AR0,  AH                           ; AR0  = order/2 (for RPT)
    MOV       ACC, *+XAR6[AR1]                   ; ACC  = [ - : X ] X is whats in the delay line
    MOV       AH, AL                             ; ACC  = [ X : X]  - is being shifted out
    MOV       AL,   *+XAR4[ARG_INPUT]            ; ACC  = [ X : input]
    
    .lp_amode
    SETC      AMODE                              ; C2xLP addressing mode to allow 
                                                 ; *+XAR6[AR1%++]
    MOVL      *+XAR6[AR1%++], ACC                ; *XAR6[AR1] = [ X : input], AR1+=2
    ZAPA
    ;; <<VC140828 - debug only
    ;; .asg	  0, N
    ;; .loop
    ;; DMAC      ACC:P,*+XAR6[AR1%++],*XAR7++       ; XT = *+XAR6[AR1%++], Temp = *XAR7++
    ;;                                              ; ACC = (XT.MSW*Temp.MSW) << PM (>> -6)
    ;;                                              ; P   = (XT.LSW*Temp.LSW) << PM (>> -6)
    ;; .eval    N + 1, N                            ; increment N
    ;; .break   N = (FILTER_SIZE/2)
    ;; .endloop
    ;; VC140828>>
    RPT       AR0                                ; Repeat order/2 + 1 times
 || DMAC      ACC:P,*+XAR6[AR1%++],*XAR7++       ; XT = *+XAR6[AR1%++], Temp = *XAR7++
                                                 ; ACC = (XT.MSW*Temp.MSW) << PM (>> -6)
                                                 ; P   = (XT.LSW*Temp.LSW) << PM (>> -6)
    
    .c28_amode
    CLRC      AMODE                              ; Back to C28x addressing mode
    ADDL      ACC, P                             ; ACC += P
    MOVW      DP,#PosSatVal
    MINL      ACC,@PosSatVal 	                 ; Saturate result 

    MOVW      DP,#NegSatVal
    MAXL      ACC,@NegSatVal 
    
    MOVH      *+XAR4[ARG_OUTPUT],ACC<<7          ; Store saturated result (Q15) 
                                                 ; output = ACC << 7 
    MOV       *+XAR4[ARG_CBINDEX], AR1           ; Store AR1(index for the next sample)
    SPM       0
    POP       XAR1                               ; Restore
    CLRC      SXM, OVM                           ; Clear sign extension and saturate mode
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
