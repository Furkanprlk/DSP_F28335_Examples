;;#############################################################################
;;! \file source/RFFT32_brev.asm
;;!
;;! \brief  Bit Reversal routine for the real 32-bit FFT
;;!
;;! \date   Feb 26, 2002
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
                .def _RFFT32_brev
;; Module Structure
;; typedef struct { <------------- XAR4
;;     int32_t *ipcbptr;      /* +0  Pointer to input buffer              */
;;     int32_t *tfptr         /* +2  Pointer to twiddle factors           */
;;     int16_t size;          /* +4  Size of the FFT                      */
;;     int16_t nrstage;       /* +5  Number of FFT stages (log2(size))    */
;;     int16_t *magptr;       /* +6  Pointer to the magnitude buffer      */
;;     int16_t *winptr;       /* +8  Pointer to the sampling window       */
;;     int16_t peakmag;       /* +10 Peak magnitude value                 */
;;     int16_t peakfrq;       /* +11 Peak Frequency                       */
;;     int16_t ratio;         /* +12 Twiddles Skip factor                 */
;;     void (*init)(void);    /* +14 Pointer to the initialization ()     */
;;     void (*calc)(void *);  /* +16 Pointer to the calculation ()        */
;;     void (*split)(void *); /* +18 Pointer to the split(0               */
;;     void (*mag)(void *);   /* +20 Pointer to the magnitude ()          */
;;     void (*win)(void *);   /* +22 Pointer to the windowing ()          */
;; }RFFT32;
;;============================================================================== 
;; \fn  void RFFT32_brev(int32_t *src, int32_t *dst, uint16_t size)
;; \brief Bit Reversal routine for the complex 32-bit FFT
;;
;; This function bit reverses a 2N-point real sequence (x(n)) stored in 
;; consecutive memory locations, that is, 
;; src(0)    = x(0)    | src(1)    = x(1)
;; src(2)    = x(2)    | src(3)    = y(3)
;; ...                 | ...
;; src(2N-2) = x(2N-2) | src(2N-1) = y(2N-1)
;; If src = dst, then in-place bit reversal is performed.
;; The destination array should be aligned to 2N long words, where 2N is the size
;; of the Real FFT (Remember, a 2N-pt real FFT is done with an N-pt complex FFT
;; followed by some post processing to get the spectrum of x(n)) 
;;
;; \param src (XAR4) pointer to the source array or buffer
;; \param dst (XAR5) pointer to the destination array or buffer
;; \param size(  AL) size of the buffer (must be a power of 2)
;;============================================================================== 
;;
_RFFT32_brev:  
    MOVL      XAR0,XAR4         ; XAR0->src
    NOP       *,ARP5        
    
    MOV       AH,AL             ; AH=size
    LSR       AH,#1             ; AH=size/2
    MOVZ      AR7,AH            ; XAR7=size/2
    SUBB      XAR7,#1           ; XAR7=(size/2)-1
    
    CMPR      0                 ; TC=1, if src==dst
    BF        off_place,NTC     ; If not equal, jump to off place bit rev

next_data1:    
    MOVL      XT,*XAR4          ; XT=*src
    MOVL      P,*XAR5           ; P=*dst
    MOVL      XAR0,XAR4         ; XAR0=src
    CMPR      2                 ; check src<dst
    BF        noswap,TC         ; if src<dst, do not swap *src & *dst
                
    MOVL      *XAR4,P           ; *src=*dst
    MOVL      *XAR5,XT          ; *dst=*src 
    MOVL      XT,*+XAR4[2]      ; XT=*(src+1)
    MOVL      P,*+XAR5[2]       ; P=*(dst+1)
    MOVL      *+XAR4[2],P       ; *(src+1)=*(dst+1)
    MOVL      *+XAR5[2],XT      ; *(dst+1)=*(src+1) 
                
noswap:         
    ADDB      XAR4,#4           ; XAR4=src+2
    MOVZ      AR0,AL            ; AR0=2*size
    NOP       *BR0++            ; ; dst=br(dst+2*size)
    BANZ      next_data1,AR7--   
    LRETR       
                
off_place:      
    MOVZ      AR0,AL            ; AR0=2*size
                
next_data2:     
    MOVL      XT,*XAR4++        ; XT=*src
    MOVL      P,*XAR4++         ; P=*(src+1)
    MOVL      *XAR5,XT          ; *dst=*src
    MOVL      *+XAR5[2],P       ; *(dst+1)=*(src+1)
    NOP       *BR0++   
    BANZ      next_data2,AR7--               
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
