;; TI File $Revision: /main/4 $
;; Checkin $Date: March 8, 2011   15:18:35 $
;;###########################################################################
;;
;; FILE:    ITRAPIsr.asm
;;
;; TITLE:   Boot Rom ITRAP ISR.
;;
;; Functions:
;;
;;     _ITRAPIsr
;;
;; Notes:
;;  
;;###########################################################################
;; $TI Release: TMS320x2806x Boot ROM V1.0 $
;; $Release Date: October 21, 2010 $
;;###########################################################################

    .def _ITRAPIsr

;-----------------------------------------------
; _ITRAPIsr   
;-----------------------------------------------
;-----------------------------------------------
; This is the ITRAP interrupt service routine for
; thet boot ROM CPU vector table.  This routine
; would be called should an ITRAP be encoutered 
; before the PIE module was initalized and enabled. 
; 
; This module performs the following actions:
; 
;     1) enables the watchdog
;     2) loops forever
;-----------------------------------------------
         
    .sect ".Isr"
             
_ITRAPIsr:
    SETC OBJMODE        ;Set OBJMODE for 28x object code
    EALLOW              ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6  ;Set data page for WDCR register
    MOV @7029h, #0028h  ;Clear WDDIS bit in WDCR to enable Watchdog
    EDIS                ;Disable EALLOW protected register access                             
    SB 0,UNC            ;Loop forever    
    
;eof ----------    
