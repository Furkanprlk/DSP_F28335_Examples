;; TI File Version : 3.00
;; Checkin Date :Fri 09/24/2010  05:42 PM
;;##############################################################################
;;
;; FILE:  CLAmathLib2_type0.inc	
;;
;; TITLE: CLA type 0 Math Macros 
;;
;; This file contains addiitonal CLA assembly macros for common math functions.
;;
;; The macros in this file are valid for CLA type 0.
;;
;; Macro Contents:
;; CLAcopy		.macro	my,mx		   		;my=mx       
;; CLAadd		.macro  my,ma,mb	   		;my=ma+mb
;; CLAsub    	.macro  my,ma,mb            ;my=ma-mb
;; CLAmul   	.macro  my,ma,mb            ;my=ma*mb
;; CLAinv    	.macro  my,mx             	;my=1/mx;
;; CLAsatmax 	.macro  mx,mxmax	   		;mx=min(mx,mxmax)
;; CLAsatmin 	.macro  mx,mxmin	   		;mx=max(mx,mxmin)
;; CLAsatmaxmin .macro  mx,mxmax,mxmin      ;mx=max(min(mx,mxmax),mxmin)
;; CLAabs		.macro  my,mx	       	    ;my=|mx|
;; CLAsuboffsetsatzero    
;;				.macro  my,mx,mxoffset	    ;my=max((mx-mxoffset),0)
;; CLAcondexec	.macro  my,mx,cnd,L1,L2     ;(my cnd mx)? L1 : L2
;; CLAIQ24toF	.macro	my,mx	       	    ;my = float(IQ24(mx))
;; CLAFtoIQ24	.macro	my,mx	       	    ;my = IQ24(float(mx))
;;
;;##############################################################################
;; TI Release: 
;; Release Date: Fri 09/24/2010  
;;##############################################################################
;;
;; This software is licensed for use with Texas Instruments Control
;; Law Accelerator (CLA). This license was provided to you prior
;; to installing the software.  You may review this license by 
;; consulting a copy of the agreement in the doc directory of this library.
;;------------------------------------------------------------------------
;;         Copyright (C) 2009 Texas Instruments, Incorporated.
;;                         All Rights Reserved.
;;
;;##############################################################################
;;
;============================================================================
;; Macro: CLAcopy
;;----------------------------------------------------------------------------
;; Description: Copy a variable
;;
;; Equation:	my = mx
;;
;; Regs Used:	MR0
;;
;; Input:		mx	f32 value in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 5 
;; 				Instructions = 5(20 bytes)
;;----------------------------------------------------------------------------
CLAcopy .macro my,mx

		; MR0 = mx
		; MR0 = my

		MMOV32 MR0,@_:mx:
		MMOV32 @_:my:,MR0
		MNOP
		MNOP
		MNOP
		.endm
	
;============================================================================
;; Macro: CLAadd
;;----------------------------------------------------------------------------
;; Description: Add two float numbers
;;
;; Equation:	my =ma + mb
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		ma,mb	f32 values in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 7 
;; 				Instructions = 7(28 bytes)
;;----------------------------------------------------------------------------
CLAadd .macro my,ma,mb

       ;MR0 = my,ma
       ;MR1 = mb
 
       MMOV32	MR0,@_:ma:
       MMOV32	MR1,@_:mb:
       MADDF32	MR0,MR0,MR1
       MMOV32	@_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAsub
;;----------------------------------------------------------------------------
;; Description: Subtract two float numbers
;;
;; Equation:	my = ma - mb
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		ma,mb	f32 values in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 7
;; 				Instructions = 7(28 bytes) 
;;----------------------------------------------------------------------------
CLAsub .macro my,ma,mb

       ;MR0 = my,ma
       ;MR1 = mb

       MMOV32	MR0,@_:ma:
       MMOV32	MR1,@_:mb:
       MSUBF32	MR0,MR0,MR1
       MMOV32	@_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
       
;============================================================================
;; Macro: CLAmul
;;----------------------------------------------------------------------------
;; Description: Multiply two float numbers
;;
;; Equation:	my = ma * mb
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		ma,mb	f32 values in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 7
;; 				Instructions = 7(28 bytes) 
;;----------------------------------------------------------------------------
CLAmul .macro my,ma,mb

       ;MR0 = my,ma
       ;MR1 = mb

       MMOV32	MR0,@_:ma:
       MMOV32	MR1,@_:mb:
       MMPYF32	MR0,MR0,MR1
       MMOV32	@_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAinv
;;----------------------------------------------------------------------------
;; Description: Find the inverse of a number using Newton Raphson method
;; 				to increase accuracy
;;
;; Equation:	my = 1/mx
;;
;; Regs Used:	MR0,MR1,MR2
;;
;; Input:		mx	f32 values in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 12
;; 				Instructions = 12(48 bytes) 
;;----------------------------------------------------------------------------
CLAinv .macro my,mx

       ;MR0 = my
       ;MR1 = mx
       ;MR2 = intermediate value
       ;MR3 = intermediate value

       MMOV32	MR1,@_:mx:	;MR1 = mx
       MEINVF32 MR0,MR1		;MR0 = Estimate(1/mx)
       MMPYF32	MR2,MR0,MR1	;MR2 = (1/mx)*mx
       MSUBF32	MR3,#2.0,MR2	;MR3 = 2.0-(1/mx)*mx
       MMPYF32	MR0,MR0,MR3	;MR0 = (1/mx)*(2.0-(1/mx)*mx)
       MMPYF32	MR2,MR0,MR1	;MR2 = Estimate(1/mx)*mx
       MSUBF32	MR3,#2.0,MR2	;MR3 = 2.0-(1/mx)*mx
       MMPYF32	MR0,MR0,MR3	;MR0 = (1/mx)*(2.0-(1/mx)*mx)
       MMOV32	@_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm

;============================================================================
;; Macro: CLAsatmax
;;----------------------------------------------------------------------------
;; Description: Floor any variable to a predetermined max value
;;
;; Equation:	mx = min(mx,mxmax)
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		mx,mxmax	f32 values in memory
;;
;; Output:		mx	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 7
;; 				Instructions = 7 (28 bytes) 
;;----------------------------------------------------------------------------
CLAsatmax .macro mx,mxmax

       ;MR0 = mx
       ;MR1 = mxmax

       MMOV32	MR0,@_:mx:
       MMOV32	MR1,@_:mxmax:
       MMINF32	MR0,MR1
       MMOV32	@_:mx:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAsatmin
;;----------------------------------------------------------------------------
;; Description: Ceil any variable to a predetermined min value
;;
;; Equation:	mx = max(mx,mxmin)
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		mx,mxmin	f32 values in memory
;;
;; Output:		mx	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 7
;; 				Instructions = 7 (28  bytes) 
;;----------------------------------------------------------------------------
CLAsatmin .macro mx,mxmin

       ;MR0 = mx
       ;MR1 = mxmax

       MMOV32	MR0,@_:mx:
       MMOV32	MR1,@_:mxmin:
       MMAXF32	MR0,MR1
       MMOV32	@_:mx:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAsatmaxmin
;;----------------------------------------------------------------------------
;; Description: Floor or ceil a variable that exceeds either of two bounds
;;
;; Equation:	mx = max(min(mx,mxmax),mxmin)
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		mx,mxmax,mxmin	f32 values in memory
;;
;; Output:		mx		f32 value in memory
;;   			MR0		f32 result
;;
;; Benchmark:	Cycles = 9
;; 				Instructions =9 (36 bytes) 
;;----------------------------------------------------------------------------
CLAsatmaxmin .macro mx,mxmax,mxmin

       ;MR0 = my
       ;MR0 = mx
       ;MR1 = mxmin
       ;MR2 = mxmax

       MMOV32	MR0,@_:mx:
       MMOV32	MR1,@_:mxmin:
       MMOV32	MR2,@_:mxmax:
       MMINF32	MR0,MR2
       MMAXF32	MR0,MR1	
       MMOV32	@_:mx:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAsuboffsetsatzero
;;----------------------------------------------------------------------------
;; Description: Subtract two numbers; if difference is less than 0 then 
;; 		ceil to zero
;;
;; Equation:	mx = max((mx-mxoffset),0)
;;
;; Regs Used:	MR0,MR1,MR2
;;
;; Input:		mx1,mx2		f32 values in memory
;;
;; Output:		mx		f32 value in memory
;;   			MR0		f32 result
;;
;; Benchmark:	Cycles = 8
;; 				Instructions = 8 (32  bytes) 
;;----------------------------------------------------------------------------
CLAsuboffsetsatzero	.macro	mx,mxoffset

		;MR0 = my
		;MR1 = mx1
		;MR2 = mx2

		MMOV32 MR1,@_:mx:
		MMOV32 MR2,@_:mxoffset:
		MSUBF32	MR1,MR1,MR2
		MMAXF32	MR1,#0x0000
		MMOV32	@_:mx:,MR1
		MNOP
		MNOP
		MNOP
		.endm

;============================================================================
;; Macro: CLAabs
;;----------------------------------------------------------------------------
;; Description: Find the absolute value of any variable
;;
;; Equation:	my = |mx|
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		mx	f32 value in memory
;;
;; Output:		my	f32 value in memory
;;   			MR0	f32 result
;;
;; Benchmark:	Cycles = 6
;; 				Instructions =6 (24  bytes) 
;;----------------------------------------------------------------------------
CLAabs .macro my,mx

       ;MR0 = my
       ;MR1 = mx
       MMOV32	MR1,@_:mx:
       MABSF32	MR0,MR1
       MMOV32	@_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAcondexec
;;----------------------------------------------------------------------------
;; Description: IF-THEN equivalent
;;
;; Equation:	(my cnd mx)? L1 : L2
;;
;; Regs Used:	MR0,MR1
;;
;; Input:		mx,my	f32 values in memory
;; 				cnd	Literal condition
;;
;; Output:		None
;;
;; Benchmark:	Cycles = 14
;; 				Instructions = 14 (56 bytes) 
;;----------------------------------------------------------------------------
CLAcondexec .macro my,mx,cnd,L1,L2

       ;MR0 = my
       ;MR0 = mx
 
       MMOV32	MR0,@_:my:
       MMOV32	MR1,@_:mx:
       MCMPF32	MR0,MR1
       MNOP
       MNOP
       MNOP
       MBCNDD	#_:L1:,:cnd:
       MNOP
       MNOP
       MNOP						;L1 if cnd true
       MBCNDD	#_:L2:,UNC
       MNOP
       MNOP	
       MNOP						;L2 if cnd fails
       .endm


;============================================================================
;; Macro: CLAIQ24toF
;;----------------------------------------------------------------------------
;; Description: convert IQ24 to float
;;
;; Equation:	float(_IQ24(mx))
;;
;; Regs Used:	MR0
;;
;; Input:		mx	f32 value in memory
;;	
;; Output:		my	f32 value in memory
;;				MR0	output value
;;
;; Benchmark:	Cycles = 6
;; 				Instructions = 6 (24  bytes) 
;;----------------------------------------------------------------------------
CLAIQ24toF .macro my,mx

       ;MR0 = my
       ;MR0 = mx

       MI32TOF32 MR0,@_:mx:	 	;iqx
       MMPYF32	 MR0,MR0,#0x3380 ;x = 1/(1*2^24)*iqx
       MMOV32	 @_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;============================================================================
;; Macro: CLAFtoIQ24
;;----------------------------------------------------------------------------
;; Description: convert float to IQ24
;;
;; Equation:	_IQ24(float(x))
;;
;; Regs Used:	MR0
;;
;; Input:		mx	f32 value in memory
;;
;; Output:		my	f32 value in memory
;;				MR0	output value
;;
;; Benchmark:	Cycles = 7
;; 				Instructions = 7 (28  bytes) 
;;----------------------------------------------------------------------------
CLAFtoIQ24 .macro my,mx

       ;MR0 = my
       ;MR0 = mx

       MMOV32	 MR0,@_:mx:
       MMPYF32	 MR0,MR0,#0x4B80 ;x = (1.0*2^24)*x
       MF32TOI32 MR0,MR0	     ;intx
       MMOV32	 @_:my:,MR0
       MNOP
       MNOP
       MNOP
       .endm
	   
;;============================================================================
;; End of File
;;============================================================================
