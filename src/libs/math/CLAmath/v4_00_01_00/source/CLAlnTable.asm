;******************************************************************************
; 
; FILE: CLAlnTable.asm
; 
; DESCRIPTION: Natural Logarithm Tables
; 
;******************************************************************************
;  $TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
;  $Release Date: Apr 23, 2014 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************

	.def	_CLALNV2
	.def	_CLALNVe
	.def	_CLALNV10
	.def	_CLABIAS
	.def	_CLALN_TABLE_MASK1
	.def	_CLALN_TABLE_MASK2
	.def	_CLALnTable
	.def	_CLALnTableEnd

   .sect    "CLA1mathTables"
   
_CLALNV2	         .float                    0.693147180559 ; 
_CLALNVe             .float                    1.0            ;
_CLALNV10            .float                    0.4342944819032;
_CLABIAS             .float                    127.0          ;
_CLALN_TABLE_MASK1   .long                     0x3FFFFFFF     ;     
_CLALN_TABLE_MASK2   .long                     0x3F800000     ;     


_CLALnTable:
                     .float                     0              ;		
                     .float                     1              ;		
                     .float                    -0.5            ;
                     .float                     9.49154e-06    ;		
                     .float                     0.999081726    ;		
                     .float                    -0.470156107    ;
                     .float                     7.09886e-05    ;		
                     .float                     0.996539792    ;		
                     .float                    -0.442906574    ;
                     .float                     0.000224404    ;		
                     .float                     0.992653061    ;		
                     .float                    -0.417959184    ;
                     .float                     0.000499085    ;		
                     .float                     0.987654321    ;		
                     .float                    -0.395061728    ;
                     .float                     0.000916122    ;		
                     .float                     0.981738495    ;		
                     .float                    -0.373995617    ;
                     .float                     0.001490146    ;		
                     .float                     0.975069252    ;		
                     .float                    -0.354570637    ;
                     .float                     0.00223074     ;		
                     .float                     0.967784352    ;		
                     .float                    -0.336620644    ;
                     .float                     0.003143551    ;		
                     .float                     0.96           ;		
                     .float                    -0.32           ;
                     .float                     0.004231167    ;		
                     .float                     0.951814396    ;		
                     .float                    -0.304580607    ;
                     .float                     0.005493806    ;		
                     .float                     0.943310658    ;		
                     .float                    -0.290249433    ;
                     .float                     0.00692987     ;		
                     .float                     0.934559221    ;		
                     .float                    -0.276906436    ;
                     .float                     0.008536376    ;		
                     .float                     0.925619835    ;		
                     .float                    -0.26446281     ;
                     .float                     0.010309303    ;		
                     .float                     0.91654321     ;		
                     .float                    -0.252839506    ;
                     .float                     0.012243868    ;		
                     .float                     0.907372401    ;		
                     .float                    -0.241965974    ;
                     .float                     0.014334741    ;		
                     .float                     0.898143957    ;		
                     .float                    -0.231779086    ;
                     .float                     0.016576219    ;		
                     .float                     0.888888889    ;		
                     .float                    -0.222222222    ;
                     .float                     0.018962363    ;		
                     .float                     0.879633486    ;		
                     .float                    -0.213244481    ;
                     .float                     0.021487103    ;		
                     .float                     0.8704         ;		
                     .float                    -0.2048         ;
                     .float                     0.024144324    ;		
                     .float                     0.861207228    ;		
                     .float                    -0.196847366    ;
                     .float                     0.026927934    ;		
                     .float                     0.852071006    ;		
                     .float                    -0.189349112    ;
                     .float                     0.02983191     ;		
                     .float                     0.843004628    ;		
                     .float                    -0.182271271    ;
                     .float                     0.032850339    ;		
                     .float                     0.834019204    ;		
                     .float                    -0.17558299     ;
                     .float                     0.035977448    ;	
                     .float                     0.825123967    ;		
                     .float                    -0.169256198    ;
                     .float                     0.039207625    ;		
                     .float                     0.816326531    ;		
                     .float                    -0.163265306    ;
                     .float                     0.042535433    ;		
                     .float                     0.807633118    ;		
                     .float                    -0.15758695     ;
                     .float                     0.045955621    ;		
                     .float                     0.799048751    ;		
                     .float                    -0.152199762    ;
                     .float                     0.049463133    ;		
                     .float                     0.79057742     ;		
                     .float                    -0.147084171    ;
                     .float                     0.053053104    ;		
                     .float                     0.782222222    ;		
                     .float                    -0.142222222    ;
                     .float                     0.056720869    ;		
                     .float                     0.773985488    ;		
                     .float                    -0.13759742     ;
                     .float                     0.060461958    ;		
                     .float                     0.765868887    ;		
                     .float                    -0.133194589    ;
                     .float                     0.064272091    ;		
                     .float                     0.75787352     ;		
                     .float                    -0.128999748    ;
                     .float                     0.068147181    ;		
                     .float                     0.75           ;		
                     .float                    -0.125           ;


_CLALnTableEnd:
