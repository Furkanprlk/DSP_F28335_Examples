;***************************************************************
;* TMS320C2000 C/C++ Codegen                         PC v5.2.4 *
;* Date/Time created: Thu Jan 14 10:22:24 2010                 *
;***************************************************************
	.compiler_opts --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --quiet --silicon_version=28 --symdebug:dwarf 
FP	.set	XAR2

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("IQsample.cpp")
	.dwattr $C$DW$CU, DW_AT_producer("TMS320C2000 C/C++ Codegen PC v5.2.4 Copyright (c) 1996-2009 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\ti\controlSUITE\libs\math\IQmath\v15b\examples\Cpp\source")
;**************************************************************
;* CINIT RECORDS                                              *
;**************************************************************
	.sect	".cinit"
	.align	1
	.field  	-2,16
	.field  	_GlobalQ+0,32
	.field  	24,32			; _GlobalQ @ 0


$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("operator new")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("___nw__FUl")
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$13)
	.dwendtag $C$DW$1

	.global	_GlobalQ
_GlobalQ:	.usect	".ebss",2,1,1
$C$DW$354	.dwtag  DW_TAG_variable, DW_AT_name("GlobalQ")
	.dwattr $C$DW$354, DW_AT_TI_symbol_name("_GlobalQ")
	.dwattr $C$DW$354, DW_AT_location[DW_OP_addr _GlobalQ]
	.dwattr $C$DW$354, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$354, DW_AT_external
	.dwattr $C$DW$354, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$354, DW_AT_decl_line(0x0b)
	.dwattr $C$DW$354, DW_AT_decl_column(0x06)

$C$DW$355	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24atan2PU")
	.dwattr $C$DW$355, DW_AT_TI_symbol_name("__IQ24atan2PU")
	.dwattr $C$DW$355, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$355, DW_AT_declaration
	.dwattr $C$DW$355, DW_AT_external
	.dwattr $C$DW$355, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$355, DW_AT_decl_line(0x7ac)
	.dwattr $C$DW$355, DW_AT_decl_column(0x10)
$C$DW$356	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$356, DW_AT_type(*$C$DW$T$12)
$C$DW$357	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$357, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$355


$C$DW$358	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24sin")
	.dwattr $C$DW$358, DW_AT_TI_symbol_name("__IQ24sin")
	.dwattr $C$DW$358, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$358, DW_AT_declaration
	.dwattr $C$DW$358, DW_AT_external
	.dwattr $C$DW$358, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$358, DW_AT_decl_line(0x456)
	.dwattr $C$DW$358, DW_AT_decl_column(0x10)
$C$DW$359	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$359, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$358


$C$DW$360	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24mag")
	.dwattr $C$DW$360, DW_AT_TI_symbol_name("__IQ24mag")
	.dwattr $C$DW$360, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$360, DW_AT_declaration
	.dwattr $C$DW$360, DW_AT_external
	.dwattr $C$DW$360, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$360, DW_AT_decl_line(0xc35)
	.dwattr $C$DW$360, DW_AT_decl_column(0x10)
$C$DW$361	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$361, DW_AT_type(*$C$DW$T$12)
$C$DW$362	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$362, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$360


$C$DW$363	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24mpyI32int")
	.dwattr $C$DW$363, DW_AT_TI_symbol_name("__IQ24mpyI32int")
	.dwattr $C$DW$363, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$363, DW_AT_declaration
	.dwattr $C$DW$363, DW_AT_external
	.dwattr $C$DW$363, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$363, DW_AT_decl_line(0xb41)
	.dwattr $C$DW$363, DW_AT_decl_column(0x10)
$C$DW$364	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$364, DW_AT_type(*$C$DW$T$12)
$C$DW$365	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$365, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$363


$C$DW$366	.dwtag  DW_TAG_subprogram, DW_AT_name("__anew")
	.dwattr $C$DW$366, DW_AT_TI_symbol_name("___anew")
	.dwattr $C$DW$366, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$366, DW_AT_declaration
	.dwattr $C$DW$366, DW_AT_external

$C$DW$367	.dwtag  DW_TAG_subprogram, DW_AT_name("__IQmpy")
	.dwattr $C$DW$367, DW_AT_TI_symbol_name("___IQmpy")
	.dwattr $C$DW$367, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$367, DW_AT_declaration
	.dwattr $C$DW$367, DW_AT_external
$C$DW$368	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$368, DW_AT_type(*$C$DW$T$12)
$C$DW$369	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$369, DW_AT_type(*$C$DW$T$12)
$C$DW$370	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$370, DW_AT_type(*$C$DW$T$10)
	.dwendtag $C$DW$367


$C$DW$371	.dwtag  DW_TAG_subprogram, DW_AT_name("labs")
	.dwattr $C$DW$371, DW_AT_TI_symbol_name("_labs")
	.dwattr $C$DW$371, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$371, DW_AT_declaration
	.dwattr $C$DW$371, DW_AT_external
	.dwattr $C$DW$371, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$371, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$371, DW_AT_decl_column(0x1d)
$C$DW$372	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$372, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$371


$C$DW$373	.dwtag  DW_TAG_subprogram, DW_AT_name("_IQ24div")
	.dwattr $C$DW$373, DW_AT_TI_symbol_name("__IQ24div")
	.dwattr $C$DW$373, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$373, DW_AT_declaration
	.dwattr $C$DW$373, DW_AT_external
	.dwattr $C$DW$373, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$373, DW_AT_decl_line(0x3dc)
	.dwattr $C$DW$373, DW_AT_decl_column(0x10)
$C$DW$374	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$374, DW_AT_type(*$C$DW$T$12)
$C$DW$375	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$375, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$373

	.global	_Step
_Step:	.usect	".ebss",18,1,1
$C$DW$376	.dwtag  DW_TAG_variable, DW_AT_name("Step")
	.dwattr $C$DW$376, DW_AT_TI_symbol_name("_Step")
	.dwattr $C$DW$376, DW_AT_location[DW_OP_addr _Step]
	.dwattr $C$DW$376, DW_AT_type(*$C$DW$T$274)
	.dwattr $C$DW$376, DW_AT_external
	.dwattr $C$DW$376, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$376, DW_AT_decl_line(0x35)
	.dwattr $C$DW$376, DW_AT_decl_column(0x03)
	.global	_Dlog
_Dlog:	.usect	".ebss",512,1,1
$C$DW$377	.dwtag  DW_TAG_variable, DW_AT_name("Dlog")
	.dwattr $C$DW$377, DW_AT_TI_symbol_name("_Dlog")
	.dwattr $C$DW$377, DW_AT_location[DW_OP_addr _Dlog]
	.dwattr $C$DW$377, DW_AT_type(*$C$DW$T$268)
	.dwattr $C$DW$377, DW_AT_external
	.dwattr $C$DW$377, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$377, DW_AT_decl_line(0x28)
	.dwattr $C$DW$377, DW_AT_decl_column(0x03)
;	C:\Program Files\Texas Instruments\C2000 Code Generation Tools 5.2.4\bin\opt2000.exe C:\\DOCUME~1\\a0322405\\LOCALS~1\\Temp\\034123 C:\\DOCUME~1\\a0322405\\LOCALS~1\\Temp\\034125 
;	C:\Program Files\Texas Instruments\C2000 Code Generation Tools 5.2.4\bin\ac2000.exe -@C:\DOCUME~1\a0322405\LOCALS~1\Temp\0341212 
	.sect	".text"

$C$DW$378	.dwtag  DW_TAG_subprogram, DW_AT_name("iq")
	.dwattr $C$DW$378, DW_AT_low_pc(___ct__2iqFv)
	.dwattr $C$DW$378, DW_AT_high_pc(0x00)
	.dwattr $C$DW$378, DW_AT_TI_symbol_name("___ct__2iqFv")
	.dwattr $C$DW$378, DW_AT_specification(*$C$DW$7)
	.dwattr $C$DW$378, DW_AT_TI_begin_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$378, DW_AT_TI_begin_line(0x42)
	.dwattr $C$DW$378, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$378, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$378, DW_AT_decl_line(0x42)
	.dwattr $C$DW$378, DW_AT_decl_column(0x05)
	.dwattr $C$DW$378, DW_AT_TI_max_frame_size(-2)
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt,address ___ct__2iqFv

	.dwfde $C$DW$CIE, ___ct__2iqFv
$C$DW$379	.dwtag  DW_TAG_formal_parameter, DW_AT_name("this")
	.dwattr $C$DW$379, DW_AT_TI_symbol_name("_this")
	.dwattr $C$DW$379, DW_AT_type(*$C$DW$T$339)
	.dwattr $C$DW$379, DW_AT_location[DW_OP_reg12]

;***************************************************************
;* FNAME: ___ct__2iqFv                  FR SIZE:   0           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  0 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___ct__2iqFv:
	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
	.dwcfi	save_reg_to_reg, 78, 26
;* AL    assigned to _this
$C$DW$380	.dwtag  DW_TAG_variable, DW_AT_name("this")
	.dwattr $C$DW$380, DW_AT_TI_symbol_name("_this")
	.dwattr $C$DW$380, DW_AT_type(*$C$DW$T$339)
	.dwattr $C$DW$380, DW_AT_location[DW_OP_reg0]
        MOVL      ACC,XAR4              ; |66| 
        BF        $C$L1,NEQ             ; |66| 
        ; branchcc occurs ; |66| 
        MOVB      ACC,#2
$C$DW$381	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$381, DW_AT_low_pc(0x00)
	.dwattr $C$DW$381, DW_AT_name("___nw__FUl")
	.dwattr $C$DW$381, DW_AT_TI_call
        LCR       #___nw__FUl           ; |66| 
        ; call occurs [#___nw__FUl] ; |66| 
        MOVL      ACC,XAR4              ; |66| 
        BF        $C$L2,EQ              ; |66| 
        ; branchcc occurs ; |66| 
$C$L1:    
        MOVB      XAR6,#0
        MOVL      XAR4,ACC              ; |66| 
        MOVL      *+XAR4[0],XAR6        ; |66| 
$C$L2:    
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 22,is_stmt
        MOVL      XAR4,ACC              ; |66| 
$C$DW$382	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$382, DW_AT_low_pc(0x00)
	.dwattr $C$DW$382, DW_AT_TI_return
        LRETR
        ; return occurs
	.dwattr $C$DW$378, DW_AT_TI_end_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$378, DW_AT_TI_end_line(0x42)
	.dwattr $C$DW$378, DW_AT_TI_end_column(0x16)
	.dwendentry
	.dwendtag $C$DW$378

	.sect	".text"
	.global	_main

$C$DW$383	.dwtag  DW_TAG_subprogram, DW_AT_name("main")
	.dwattr $C$DW$383, DW_AT_low_pc(_main)
	.dwattr $C$DW$383, DW_AT_high_pc(0x00)
	.dwattr $C$DW$383, DW_AT_TI_symbol_name("_main")
	.dwattr $C$DW$383, DW_AT_external
	.dwattr $C$DW$383, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$383, DW_AT_TI_begin_file("IQsample.cpp")
	.dwattr $C$DW$383, DW_AT_TI_begin_line(0x3a)
	.dwattr $C$DW$383, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$383, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$383, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$383, DW_AT_decl_column(0x05)
	.dwattr $C$DW$383, DW_AT_TI_max_frame_size(-20)
	.dwpsn	file "IQsample.cpp",line 59,column 1,is_stmt,address _main

	.dwfde $C$DW$CIE, _main

;***************************************************************
;* FNAME: _main                         FR SIZE:  18           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  2 Auto, 14 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
_main:
	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
	.dwcfi	save_reg_to_reg, 78, 26
        MOVL      *SP++,XAR1
	.dwcfi	save_reg_to_mem, 7, 2
	.dwcfi	cfa_offset, -4
        MOVL      *SP++,XAR2
	.dwcfi	save_reg_to_mem, 9, 4
	.dwcfi	cfa_offset, -6
        MOVL      *SP++,XAR3
	.dwcfi	save_reg_to_mem, 11, 6
	.dwcfi	cfa_offset, -8
        MOV32     *SP++,R4H
	.dwcfi	save_reg_to_mem, 60, 8
	.dwcfi	cfa_offset, -10
        MOV32     *SP++,R5H
	.dwcfi	save_reg_to_mem, 64, 10
	.dwcfi	cfa_offset, -12
        MOV32     *SP++,R6H
	.dwcfi	save_reg_to_mem, 68, 12
	.dwcfi	cfa_offset, -14
        MOV32     *SP++,R7H
	.dwcfi	save_reg_to_mem, 72, 14
	.dwcfi	cfa_offset, -16
        ADDB      SP,#4
	.dwcfi	cfa_offset, -20
;* R5HL  assigned to $O$C19
;* XT    assigned to $O$C20
;* AR3   assigned to $O$C21
;* AR5   assigned to $O$C22
;* AR5   assigned to $O$C23
;* AR4   assigned to $O$C24
;* AR4   assigned to $O$C25
;* AR6   assigned to $O$C26
;* R6HL  assigned to $O$K24
;* AR4   assigned to $O$K17
;* AR4   assigned to $O$K20
;* AL    assigned to $O$R1
;* AL    assigned to $O$CSU$temp$val
;* XT    assigned to $O$CSU$temp$val
;* R7HL  assigned to $O$CSU$temp$val
;* R7HL  assigned to $O$CSU$tempMmax$val
;* AR3   assigned to $O$CSU$tempY$val
;* R4HL  assigned to $O$CSU$tempX$val
;* AR5   assigned to $O$U35
;* AR7   assigned to _i
$C$DW$384	.dwtag  DW_TAG_variable, DW_AT_name("i")
	.dwattr $C$DW$384, DW_AT_TI_symbol_name("_i")
	.dwattr $C$DW$384, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$384, DW_AT_location[DW_OP_reg18]
;* AR2   assigned to _i
$C$DW$385	.dwtag  DW_TAG_variable, DW_AT_name("i")
	.dwattr $C$DW$385, DW_AT_TI_symbol_name("_i")
	.dwattr $C$DW$385, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$385, DW_AT_location[DW_OP_reg8]
 EALLOW 
	.dwpsn	file "IQsample.cpp",line 68,column 5,is_stmt
        MOVB      AL,#104               ; |68| 
        MOV       *(0:0x7029),AL        ; |68| 
 EDIS 
        MOVL      XAR4,#_Dlog
        MOV       PH,#80
        MOV       PL,#27838
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      XAR6,#_Step           ; |7034| 
        MOVL      XAR5,#256
        MOVB      XAR2,#0
        MOVB      XAR0,#8               ; |7034| 
        MOV32     R6H,XAR4
        MOVB      XAR7,#0
        MOVL      XAR1,#384             ; |7034| 
        MOVB      XAR4,#0
        MOVL      *+XAR6[0],P           ; |7034| 
        MOVL      *+XAR6[2],P           ; |7034| 
        MOV32     ACC,R6H
        MOV       P,#0
        MOVL      *+XAR6[6],XAR2        ; |7034| 
        ADDL      XAR5,ACC
        MOVL      *+XAR6[AR0],XAR4      ; |7034| 
        MOVB      XAR0,#128             ; |7034| 
        MOVL      *+XAR6[4],P           ; |7034| 
        RPTB      $C$L4,#63
        ; repeat block starts
$C$L3:    
$C$DW$L$_main$2$B:
        MOV32     XAR4,R6H
        MOVU      ACC,AR7
        LSL       ACC,1                 ; |7034| 
        ADDL      XAR4,ACC
	.dwpsn	file "IQsample.cpp",line 77,column 14,is_stmt
        ADDB      XAR7,#1               ; |77| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      *+XAR4[AR0],XAR2      ; |7034| 
        MOVB      ACC,#0
        MOVL      *+XAR4[0],ACC         ; |7034| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7035,column 4,is_stmt
        MOVL      *XAR5++,P             ; |7035| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      *+XAR4[AR1],ACC       ; |7034| 
        ; repeat block ends
$C$DW$L$_main$2$E:
$C$L4:    
        MOV       ACC,#512 << 15
        MOVB      XAR0,#10              ; |7034| 
        MOVL      XAR4,#_Step           ; |7034| 
        MOVB      XAR1,#16              ; |7034| 
        MOV       PH,#256
        MOV       PL,#0
        SPM       #0
        MOVL      *+XAR4[AR0],ACC       ; |7034| 
        MOVB      XAR0,#14              ; |7034| 
        MOVL      *+XAR4[AR1],ACC       ; |7034| 
        MOVL      *+XAR4[AR0],ACC       ; |7034| 
        MOVB      XAR0,#12              ; |7034| 
        MOVL      *+XAR4[AR0],ACC       ; |7034| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        MOVL      *-SP[2],P             ; |66| 
$C$DW$386	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$386, DW_AT_low_pc(0x00)
	.dwattr $C$DW$386, DW_AT_name("__IQ24mag")
	.dwattr $C$DW$386, DW_AT_TI_call
        LCR       #__IQ24mag            ; |66| 
        ; call occurs [#__IQ24mag] ; |66| 
        MOVL      XAR6,ACC              ; |66| 
        MOVL      XAR4,#256
        MOV32     ACC,R6H
        ADDL      XAR4,ACC
        MOV32     R7H,XAR6
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVB      XAR1,#128             ; |7034| 
        MOVB      XAR2,#0
        MOVL      *-SP[4],XAR4
$C$L5:    
	.dwpsn	file "../../../include/IQmathCPP.h",line 7035,column 4,is_stmt
$C$DW$L$_main$4$B:
        MOVW      DP,#_Step
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      XAR5,#_Step           ; |7034| 
        MOVB      XAR0,#14              ; |7034| 
        MOVL      XT,@_Step             ; |7034| 
        MOVL      XAR4,XAR5             ; |7034| 
        ADDB      XAR4,#6               ; |7034| 
        IMPYL     P,XT,*+XAR5[AR0]      ; |7034| 
        QMPYL     ACC,XT,*+XAR5[AR0]    ; |7034| 
        LSL64     ACC:P,#8              ; |7034| 
        ADDL      *+XAR4[0],ACC         ; |7034| 
        MOV       AL,#32472
        MOV       AH,#1608
	.dwpsn	file "../../../include/IQmathCPP.h",line 8761,column 58,is_stmt
        CMPL      ACC,*+XAR4[0]         ; |8761| 
        BF        $C$L6,GEQ             ; |8761| 
        ; branchcc occurs ; |8761| 
$C$DW$L$_main$4$E:
$C$DW$L$_main$5$B:
	.dwpsn	file "../../../include/IQmathCPP.h",line 7238,column 4,is_stmt
        SUBL      *+XAR4[0],ACC         ; |7238| 
$C$DW$L$_main$5$E:
$C$L6:    
	.dwpsn	file "../../../include/IQmathCPP.h",line 8761,column 58,is_stmt
$C$DW$L$_main$6$B:
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      XAR4,XAR5             ; |7034| 
        MOVB      XAR0,#16              ; |7034| 
        MOVL      XT,*+XAR5[2]          ; |7034| 
        ADDB      XAR4,#8               ; |7034| 
        IMPYL     P,XT,*+XAR5[AR0]      ; |7034| 
        QMPYL     ACC,XT,*+XAR5[AR0]    ; |7034| 
        LSL64     ACC:P,#8              ; |7034| 
        ADDL      *+XAR4[0],ACC         ; |7034| 
        MOV       AL,#32472
        MOV       AH,#1608
	.dwpsn	file "../../../include/IQmathCPP.h",line 8761,column 58,is_stmt
        CMPL      ACC,*+XAR4[0]         ; |8761| 
        BF        $C$L7,GEQ             ; |8761| 
        ; branchcc occurs ; |8761| 
$C$DW$L$_main$6$E:
$C$DW$L$_main$7$B:
	.dwpsn	file "../../../include/IQmathCPP.h",line 7238,column 4,is_stmt
        SUBL      *+XAR4[0],ACC         ; |7238| 
$C$DW$L$_main$7$E:
$C$L7:    
	.dwpsn	file "../../../include/IQmathCPP.h",line 8761,column 58,is_stmt
$C$DW$L$_main$8$B:
	.dwpsn	file "IQsample.cpp",line 104,column 9,is_stmt
        MOVL      XAR3,#_Step           ; |104| 
        MOVL      ACC,*+XAR3[6]         ; |104| 
$C$DW$387	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$387, DW_AT_low_pc(0x00)
	.dwattr $C$DW$387, DW_AT_name("__IQ24sin")
	.dwattr $C$DW$387, DW_AT_TI_call
        LCR       #__IQ24sin            ; |104| 
        ; call occurs [#__IQ24sin] ; |104| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVB      XAR0,#10              ; |7034| 
	.dwpsn	file "IQsample.cpp",line 104,column 9,is_stmt
        MOVL      XT,ACC                ; |104| 
        MOV32     XAR6,R6H
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        IMPYL     P,XT,*+XAR3[AR0]      ; |7034| 
        QMPYL     ACC,XT,*+XAR3[AR0]    ; |7034| 
        LSL64     ACC:P,#8              ; |7034| 
        MOV32     R4H,ACC
        MOVU      ACC,AR2
        LSL       ACC,1                 ; |7034| 
        ADDL      XAR6,ACC
        MOV32     R5H,XAR6
        NOP
        NOP
        NOP
        NOP
        NOP
        MOV32     XAR4,R5H
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        MOVB      XAR0,#8               ; |66| 
        MOVL      ACC,*+XAR3[AR0]       ; |66| 
        MOV32     *+XAR4[0],R4H
$C$DW$388	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$388, DW_AT_low_pc(0x00)
	.dwattr $C$DW$388, DW_AT_name("__IQ24sin")
	.dwattr $C$DW$388, DW_AT_TI_call
        LCR       #__IQ24sin            ; |66| 
        ; call occurs [#__IQ24sin] ; |66| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVB      XAR0,#12              ; |7034| 
        MOVW      DP,#_Step+12
        ABS       ACC                   ; |7034| 
        MOV32     XAR4,R5H
        MOVL      XT,ACC                ; |7034| 
        IMPYL     P,XT,*+XAR3[AR0]      ; |7034| 
        QMPYL     ACC,XT,*+XAR3[AR0]    ; |7034| 
        LSL64     ACC:P,#8              ; |7034| 
        MOVL      *+XAR4[AR1],ACC       ; |7034| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        IMPYL     P,XT,@_Step+12        ; |66| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      XAR3,ACC              ; |7034| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        QMPYL     ACC,XT,@_Step+12      ; |66| 
        LSL64     ACC:P,#8              ; |66| 
        MOVL      *-SP[2],ACC           ; |66| 
        MOV32     ACC,R4H
$C$DW$389	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$389, DW_AT_low_pc(0x00)
	.dwattr $C$DW$389, DW_AT_name("__IQ24mag")
	.dwattr $C$DW$389, DW_AT_TI_call
        LCR       #__IQ24mag            ; |66| 
        ; call occurs [#__IQ24mag] ; |66| 
        MOV32     *-SP[2],R7H
$C$DW$390	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$390, DW_AT_low_pc(0x00)
	.dwattr $C$DW$390, DW_AT_name("__IQ24div")
	.dwattr $C$DW$390, DW_AT_TI_call
        LCR       #__IQ24div            ; |66| 
        ; call occurs [#__IQ24div] ; |66| 
        MOV32     XAR4,R5H
	.dwpsn	file "../../../include/IQmathCPP.h",line 7034,column 4,is_stmt
        MOVL      XAR0,#384             ; |7034| 
        MOVL      *+XAR4[AR0],ACC       ; |7034| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        MOVL      ACC,XAR3              ; |66| 
        MOV32     *-SP[2],R4H
$C$DW$391	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$391, DW_AT_low_pc(0x00)
	.dwattr $C$DW$391, DW_AT_name("__IQ24atan2PU")
	.dwattr $C$DW$391, DW_AT_TI_call
        LCR       #__IQ24atan2PU        ; |66| 
        ; call occurs [#__IQ24atan2PU] ; |66| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 3210,column 57,is_stmt
        MOVL      XAR4,#360             ; |3210| 
        MOVL      *-SP[2],XAR4          ; |3210| 
$C$DW$392	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$392, DW_AT_low_pc(0x00)
	.dwattr $C$DW$392, DW_AT_name("__IQ24mpyI32int")
	.dwattr $C$DW$392, DW_AT_TI_call
        LCR       #__IQ24mpyI32int      ; |3210| 
        ; call occurs [#__IQ24mpyI32int] ; |3210| 
        MOVL      XAR4,*-SP[4]          ; |3210| 
	.dwpsn	file "IQsample.cpp",line 93,column 14,is_stmt
        ADDB      XAR2,#1               ; |93| 
	.dwpsn	file "../../../include/IQmathCPP.h",line 3210,column 57,is_stmt
        MOVL      *XAR4++,ACC           ; |3210| 
        MOVL      *-SP[4],XAR4          ; |3210| 
        MOV       AL,AR2                ; |3210| 
	.dwpsn	file "IQsample.cpp",line 93,column 14,is_stmt
        CMPB      AL,#64                ; |93| 
        BF        $C$L5,LO              ; |93| 
        ; branchcc occurs ; |93| 
$C$DW$L$_main$8$E:
        MOVB      AL,#0
        SUBB      SP,#4
	.dwcfi	cfa_offset, -16
        MOV32     R7H,*--SP
	.dwcfi	save_reg_to_mem, 72, 2
	.dwcfi	cfa_offset, -18
        MOV32     R6H,*--SP
	.dwcfi	save_reg_to_mem, 68, 4
	.dwcfi	cfa_offset, -20
        MOV32     R5H,*--SP
	.dwcfi	save_reg_to_mem, 64, 6
	.dwcfi	cfa_offset, -22
        MOV32     R4H,*--SP
	.dwcfi	save_reg_to_mem, 60, 8
	.dwcfi	cfa_offset, -24
        MOVL      XAR3,*--SP
	.dwcfi	cfa_offset, -22
	.dwcfi	restore_reg, 11
        MOVL      XAR2,*--SP
	.dwcfi	cfa_offset, -20
	.dwcfi	restore_reg, 9
        MOVL      XAR1,*--SP
	.dwcfi	cfa_offset, -18
	.dwcfi	restore_reg, 7
$C$DW$393	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$393, DW_AT_low_pc(0x00)
	.dwattr $C$DW$393, DW_AT_TI_return
        LRETR
        ; return occurs

$C$DW$394	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$394, DW_AT_name("C:\ti\controlSUITE\libs\math\IQmath\v15b\examples\Cpp\source\IQsample.asm:$C$L5:1:1263486144")
	.dwattr $C$DW$394, DW_AT_TI_begin_file("IQsample.cpp")
	.dwattr $C$DW$394, DW_AT_TI_begin_line(0x5d)
	.dwattr $C$DW$394, DW_AT_TI_end_line(0x76)
$C$DW$395	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$395, DW_AT_low_pc($C$DW$L$_main$4$B)
	.dwattr $C$DW$395, DW_AT_high_pc($C$DW$L$_main$4$E)
$C$DW$396	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$396, DW_AT_low_pc($C$DW$L$_main$5$B)
	.dwattr $C$DW$396, DW_AT_high_pc($C$DW$L$_main$5$E)
$C$DW$397	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$397, DW_AT_low_pc($C$DW$L$_main$6$B)
	.dwattr $C$DW$397, DW_AT_high_pc($C$DW$L$_main$6$E)
$C$DW$398	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$398, DW_AT_low_pc($C$DW$L$_main$7$B)
	.dwattr $C$DW$398, DW_AT_high_pc($C$DW$L$_main$7$E)
$C$DW$399	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$399, DW_AT_low_pc($C$DW$L$_main$8$B)
	.dwattr $C$DW$399, DW_AT_high_pc($C$DW$L$_main$8$E)
	.dwendtag $C$DW$394


$C$DW$400	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$400, DW_AT_name("C:\ti\controlSUITE\libs\math\IQmath\v15b\examples\Cpp\source\IQsample.asm:$C$L3:1:1263486144")
	.dwattr $C$DW$400, DW_AT_TI_begin_file("IQsample.cpp")
	.dwattr $C$DW$400, DW_AT_TI_begin_line(0x4d)
	.dwattr $C$DW$400, DW_AT_TI_end_line(0x53)
$C$DW$401	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$401, DW_AT_low_pc($C$DW$L$_main$2$B)
	.dwattr $C$DW$401, DW_AT_high_pc($C$DW$L$_main$2$E)
	.dwendtag $C$DW$400

	.dwattr $C$DW$383, DW_AT_TI_end_file("IQsample.cpp")
	.dwattr $C$DW$383, DW_AT_TI_end_line(0x77)
	.dwattr $C$DW$383, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$383

	.sect	".pinit"
	.align	2
	.field	___sti___12_IQsample_cpp_GlobalQ, 22
	.sect	".text"
	.global	___sti___12_IQsample_cpp_GlobalQ

$C$DW$402	.dwtag  DW_TAG_subprogram, DW_AT_name("__sti___12_IQsample_cpp_GlobalQ")
	.dwattr $C$DW$402, DW_AT_low_pc(___sti___12_IQsample_cpp_GlobalQ)
	.dwattr $C$DW$402, DW_AT_high_pc(0x00)
	.dwattr $C$DW$402, DW_AT_TI_symbol_name("___sti___12_IQsample_cpp_GlobalQ")
	.dwattr $C$DW$402, DW_AT_external
	.dwattr $C$DW$402, DW_AT_TI_max_frame_size(-10)

	.dwfde $C$DW$CIE, ___sti___12_IQsample_cpp_GlobalQ

;***************************************************************
;* FNAME: ___sti___12_IQsample_cpp_GlobalQ FR SIZE:   8           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  6 SOE     *
;***************************************************************


;***************************************************************
;*                                                             *
;* Using -g (debug) with optimization (-o3) may disable key op *
;*                                                             *
;***************************************************************
___sti___12_IQsample_cpp_GlobalQ:
	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
	.dwcfi	save_reg_to_reg, 78, 26
        MOVL      *SP++,XAR1
	.dwcfi	save_reg_to_mem, 7, 2
	.dwcfi	cfa_offset, -4
        MOVL      *SP++,XAR2
	.dwcfi	save_reg_to_mem, 9, 4
	.dwcfi	cfa_offset, -6
        MOVL      *SP++,XAR3
	.dwcfi	save_reg_to_mem, 11, 6
	.dwcfi	cfa_offset, -8
        ADDB      SP,#2
	.dwcfi	cfa_offset, -10
;* AR4   assigned to $O$C1
;* AR3   assigned to $O$C2
;* AR2   assigned to $O$C3
        MOVL      XAR4,#___ct__2iqFv
        MOVB      ACC,#2
        MOVL      XAR3,#_Dlog
        MOVL      XAR5,XAR4
        MOVL      XAR2,XAR4
        MOVL      *-SP[2],ACC
        MOVL      XAR4,XAR3
        MOVB      ACC,#64
$C$DW$403	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$403, DW_AT_low_pc(0x00)
	.dwattr $C$DW$403, DW_AT_name("___anew")
	.dwattr $C$DW$403, DW_AT_TI_call
        LCR       #___anew
        ; call occurs [#___anew]
        MOVB      XAR6,#2
        MOVB      XAR4,#128
        MOVL      ACC,XAR3
        MOVL      XAR5,XAR2
        MOVL      *-SP[2],XAR6
        ADDU      ACC,AR4
        MOVL      XAR4,ACC
        MOVB      ACC,#64
$C$DW$404	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$404, DW_AT_low_pc(0x00)
	.dwattr $C$DW$404, DW_AT_name("___anew")
	.dwattr $C$DW$404, DW_AT_TI_call
        LCR       #___anew
        ; call occurs [#___anew]
        MOVB      XAR6,#2
        MOVL      XAR4,#384
        MOVL      ACC,XAR3
        MOVL      XAR5,XAR2
        MOVL      *-SP[2],XAR6
        ADDL      XAR4,ACC
        MOVB      ACC,#64
$C$DW$405	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$405, DW_AT_low_pc(0x00)
	.dwattr $C$DW$405, DW_AT_name("___anew")
	.dwattr $C$DW$405, DW_AT_TI_call
        LCR       #___anew
        ; call occurs [#___anew]
	.dwpsn	file "../../../include/IQmathCPP.h",line 66,column 20,is_stmt
        MOVB      XAR1,#16              ; |66| 
        MOVB      XAR2,#0
        MOVL      XAR4,#_Step           ; |66| 
        MOVB      XAR5,#0
        MOVB      XAR0,#0
        MOVB      XAR6,#0
        MOV       P,#0
        MOVB      XAR7,#0
        MOVL      *+XAR4[2],XAR0        ; |66| 
        MOVL      *+XAR4[6],P           ; |66| 
        MOVB      XAR0,#10              ; |66| 
        MOVL      *+XAR4[4],XAR5        ; |66| 
        MOVB      ACC,#0
        MOVL      *+XAR4[AR0],XAR6      ; |66| 
        MOVB      XAR0,#12              ; |66| 
        MOVL      XT,ACC                ; |66| 
        MOVL      *+XAR4[AR0],XAR2      ; |66| 
        MOVB      XAR0,#14              ; |66| 
        MOVL      *+XAR4[AR0],ACC       ; |66| 
        MOVB      XAR0,#8               ; |66| 
        SUBB      SP,#2
        MOVL      *+XAR4[AR1],ACC       ; |66| 
        MOVL      *+XAR4[0],XT          ; |66| 
        MOVL      *+XAR4[AR0],XAR7      ; |66| 
	.dwcfi	cfa_offset, -8
        MOVL      XAR3,*--SP
	.dwcfi	cfa_offset, -6
	.dwcfi	restore_reg, 11
        MOVL      XAR2,*--SP
	.dwcfi	cfa_offset, -4
	.dwcfi	restore_reg, 9
        MOVL      XAR1,*--SP
	.dwcfi	cfa_offset, -2
	.dwcfi	restore_reg, 7
$C$DW$406	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$406, DW_AT_low_pc(0x00)
	.dwattr $C$DW$406, DW_AT_TI_return
        LRETR
        ; return occurs
	.dwendentry
	.dwendtag $C$DW$402

;**************************************************************
;* UNDEFINED EXTERNAL REFERENCES                              *
;**************************************************************
	.global	___nw__FUl
	.global	__IQ24atan2PU
	.global	__IQ24sin
	.global	__IQ24mag
	.global	__IQ24mpyI32int
	.global	___anew
	.global	__IQ24div

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x16)

$C$DW$T$40	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C_plus_plus)

$C$DW$T$41	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$407	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$407, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$T$41


$C$DW$T$44	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$408	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$408, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$T$44


$C$DW$T$53	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$53, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$409	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$409, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$T$53


$C$DW$T$60	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$60, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$410	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$410, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$T$60


$C$DW$T$67	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$67, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$411	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$411, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$T$67


$C$DW$T$74	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$74, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$412	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$412, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$T$74


$C$DW$T$81	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$81, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$413	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$413, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$T$81


$C$DW$T$88	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$88, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$414	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$414, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$T$88


$C$DW$T$95	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$95, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$415	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$415, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$T$95


$C$DW$T$102	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$102, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$416	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$416, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$T$102


$C$DW$T$109	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$109, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$417	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$417, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$T$109


$C$DW$T$116	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$116, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$418	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$418, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$T$116


$C$DW$T$123	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$123, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$419	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$419, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$T$123


$C$DW$T$130	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$130, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$420	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$420, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$T$130


$C$DW$T$137	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$137, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$421	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$421, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$T$137


$C$DW$T$144	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$144, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$422	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$422, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$T$144


$C$DW$T$151	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$151, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$423	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$423, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$T$151


$C$DW$T$158	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$158, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$424	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$424, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$T$158


$C$DW$T$165	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$165, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$425	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$425, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$T$165


$C$DW$T$172	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$172, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$426	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$426, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$T$172


$C$DW$T$179	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$179, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$427	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$427, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$T$179


$C$DW$T$186	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$186, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$428	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$428, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$T$186


$C$DW$T$193	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$193, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$429	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$429, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$T$193


$C$DW$T$200	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$200, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$430	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$430, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$T$200


$C$DW$T$207	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$207, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$431	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$431, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$T$207


$C$DW$T$214	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$214, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$432	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$432, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$T$214


$C$DW$T$221	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$221, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$433	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$433, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$T$221


$C$DW$T$228	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$228, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$434	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$434, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$T$228


$C$DW$T$235	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$235, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$435	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$435, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$T$235


$C$DW$T$242	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$242, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$436	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$436, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$T$242


$C$DW$T$249	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$249, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$437	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$437, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$T$249


$C$DW$T$256	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$256, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$438	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$438, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$T$256


$C$DW$T$265	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$265, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$439	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$439, DW_AT_type(*$C$DW$T$264)
	.dwendtag $C$DW$T$265


$C$DW$T$271	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$271, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$440	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$440, DW_AT_type(*$C$DW$T$270)
	.dwendtag $C$DW$T$271

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$19	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$19, DW_AT_address_class(0x16)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x01)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x01)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x01)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x01)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x01)
$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x02)
$C$DW$441	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$441, DW_AT_type(*$C$DW$T$12)
$C$DW$T$47	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$441)
$C$DW$T$48	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$48, DW_AT_type(*$C$DW$T$47)
	.dwattr $C$DW$T$48, DW_AT_address_class(0x16)

$C$DW$T$262	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$262, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$262, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$262, DW_AT_byte_size(0x80)
$C$DW$442	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$442, DW_AT_upper_bound(0x3f)
	.dwendtag $C$DW$T$262

$C$DW$T$294	.dwtag  DW_TAG_typedef, DW_AT_name("fpos_t")
	.dwattr $C$DW$T$294, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$294, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$294, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$T$294, DW_AT_decl_line(0x27)
	.dwattr $C$DW$T$294, DW_AT_decl_column(0x0e)
$C$DW$T$295	.dwtag  DW_TAG_typedef, DW_AT_name("_iq")
	.dwattr $C$DW$T$295, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$295, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$295, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$295, DW_AT_decl_line(0x86)
	.dwattr $C$DW$T$295, DW_AT_decl_column(0x13)
$C$DW$T$296	.dwtag  DW_TAG_typedef, DW_AT_name("_iq30")
	.dwattr $C$DW$T$296, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$296, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$296, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$296, DW_AT_decl_line(0x87)
	.dwattr $C$DW$T$296, DW_AT_decl_column(0x13)
$C$DW$T$297	.dwtag  DW_TAG_typedef, DW_AT_name("_iq29")
	.dwattr $C$DW$T$297, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$297, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$297, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$297, DW_AT_decl_line(0x88)
	.dwattr $C$DW$T$297, DW_AT_decl_column(0x13)
$C$DW$T$298	.dwtag  DW_TAG_typedef, DW_AT_name("_iq28")
	.dwattr $C$DW$T$298, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$298, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$298, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$298, DW_AT_decl_line(0x89)
	.dwattr $C$DW$T$298, DW_AT_decl_column(0x13)
$C$DW$T$299	.dwtag  DW_TAG_typedef, DW_AT_name("_iq27")
	.dwattr $C$DW$T$299, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$299, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$299, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$299, DW_AT_decl_line(0x8a)
	.dwattr $C$DW$T$299, DW_AT_decl_column(0x13)
$C$DW$T$300	.dwtag  DW_TAG_typedef, DW_AT_name("_iq26")
	.dwattr $C$DW$T$300, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$300, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$300, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$300, DW_AT_decl_line(0x8b)
	.dwattr $C$DW$T$300, DW_AT_decl_column(0x13)
$C$DW$T$301	.dwtag  DW_TAG_typedef, DW_AT_name("_iq25")
	.dwattr $C$DW$T$301, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$301, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$301, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$301, DW_AT_decl_line(0x8c)
	.dwattr $C$DW$T$301, DW_AT_decl_column(0x13)
$C$DW$T$302	.dwtag  DW_TAG_typedef, DW_AT_name("_iq24")
	.dwattr $C$DW$T$302, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$302, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$302, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$302, DW_AT_decl_line(0x8d)
	.dwattr $C$DW$T$302, DW_AT_decl_column(0x13)
$C$DW$T$303	.dwtag  DW_TAG_typedef, DW_AT_name("_iq23")
	.dwattr $C$DW$T$303, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$303, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$303, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$303, DW_AT_decl_line(0x8e)
	.dwattr $C$DW$T$303, DW_AT_decl_column(0x13)
$C$DW$T$304	.dwtag  DW_TAG_typedef, DW_AT_name("_iq22")
	.dwattr $C$DW$T$304, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$304, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$304, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$304, DW_AT_decl_line(0x8f)
	.dwattr $C$DW$T$304, DW_AT_decl_column(0x13)
$C$DW$T$305	.dwtag  DW_TAG_typedef, DW_AT_name("_iq21")
	.dwattr $C$DW$T$305, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$305, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$305, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$305, DW_AT_decl_line(0x90)
	.dwattr $C$DW$T$305, DW_AT_decl_column(0x13)
$C$DW$T$306	.dwtag  DW_TAG_typedef, DW_AT_name("_iq20")
	.dwattr $C$DW$T$306, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$306, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$306, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$306, DW_AT_decl_line(0x91)
	.dwattr $C$DW$T$306, DW_AT_decl_column(0x13)
$C$DW$T$307	.dwtag  DW_TAG_typedef, DW_AT_name("_iq19")
	.dwattr $C$DW$T$307, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$307, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$307, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$307, DW_AT_decl_line(0x92)
	.dwattr $C$DW$T$307, DW_AT_decl_column(0x13)
$C$DW$T$308	.dwtag  DW_TAG_typedef, DW_AT_name("_iq18")
	.dwattr $C$DW$T$308, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$308, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$308, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$308, DW_AT_decl_line(0x93)
	.dwattr $C$DW$T$308, DW_AT_decl_column(0x13)
$C$DW$T$309	.dwtag  DW_TAG_typedef, DW_AT_name("_iq17")
	.dwattr $C$DW$T$309, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$309, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$309, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$309, DW_AT_decl_line(0x94)
	.dwattr $C$DW$T$309, DW_AT_decl_column(0x13)
$C$DW$T$310	.dwtag  DW_TAG_typedef, DW_AT_name("_iq16")
	.dwattr $C$DW$T$310, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$310, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$310, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$310, DW_AT_decl_line(0x95)
	.dwattr $C$DW$T$310, DW_AT_decl_column(0x13)
$C$DW$T$311	.dwtag  DW_TAG_typedef, DW_AT_name("_iq15")
	.dwattr $C$DW$T$311, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$311, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$311, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$311, DW_AT_decl_line(0x96)
	.dwattr $C$DW$T$311, DW_AT_decl_column(0x13)
$C$DW$T$312	.dwtag  DW_TAG_typedef, DW_AT_name("_iq14")
	.dwattr $C$DW$T$312, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$312, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$312, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$312, DW_AT_decl_line(0x97)
	.dwattr $C$DW$T$312, DW_AT_decl_column(0x13)
$C$DW$T$313	.dwtag  DW_TAG_typedef, DW_AT_name("_iq13")
	.dwattr $C$DW$T$313, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$313, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$313, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$313, DW_AT_decl_line(0x98)
	.dwattr $C$DW$T$313, DW_AT_decl_column(0x13)
$C$DW$T$314	.dwtag  DW_TAG_typedef, DW_AT_name("_iq12")
	.dwattr $C$DW$T$314, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$314, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$314, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$314, DW_AT_decl_line(0x99)
	.dwattr $C$DW$T$314, DW_AT_decl_column(0x13)
$C$DW$T$315	.dwtag  DW_TAG_typedef, DW_AT_name("_iq11")
	.dwattr $C$DW$T$315, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$315, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$315, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$315, DW_AT_decl_line(0x9a)
	.dwattr $C$DW$T$315, DW_AT_decl_column(0x13)
$C$DW$T$316	.dwtag  DW_TAG_typedef, DW_AT_name("_iq10")
	.dwattr $C$DW$T$316, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$316, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$316, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$316, DW_AT_decl_line(0x9b)
	.dwattr $C$DW$T$316, DW_AT_decl_column(0x13)
$C$DW$T$317	.dwtag  DW_TAG_typedef, DW_AT_name("_iq9")
	.dwattr $C$DW$T$317, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$317, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$317, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$317, DW_AT_decl_line(0x9c)
	.dwattr $C$DW$T$317, DW_AT_decl_column(0x13)
$C$DW$T$318	.dwtag  DW_TAG_typedef, DW_AT_name("_iq8")
	.dwattr $C$DW$T$318, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$318, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$318, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$318, DW_AT_decl_line(0x9d)
	.dwattr $C$DW$T$318, DW_AT_decl_column(0x13)
$C$DW$T$319	.dwtag  DW_TAG_typedef, DW_AT_name("_iq7")
	.dwattr $C$DW$T$319, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$319, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$319, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$319, DW_AT_decl_line(0x9e)
	.dwattr $C$DW$T$319, DW_AT_decl_column(0x13)
$C$DW$T$320	.dwtag  DW_TAG_typedef, DW_AT_name("_iq6")
	.dwattr $C$DW$T$320, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$320, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$320, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$320, DW_AT_decl_line(0x9f)
	.dwattr $C$DW$T$320, DW_AT_decl_column(0x13)
$C$DW$T$321	.dwtag  DW_TAG_typedef, DW_AT_name("_iq5")
	.dwattr $C$DW$T$321, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$321, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$321, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$321, DW_AT_decl_line(0xa0)
	.dwattr $C$DW$T$321, DW_AT_decl_column(0x13)
$C$DW$T$322	.dwtag  DW_TAG_typedef, DW_AT_name("_iq4")
	.dwattr $C$DW$T$322, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$322, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$322, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$322, DW_AT_decl_line(0xa1)
	.dwattr $C$DW$T$322, DW_AT_decl_column(0x13)
$C$DW$T$323	.dwtag  DW_TAG_typedef, DW_AT_name("_iq3")
	.dwattr $C$DW$T$323, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$323, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$323, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$323, DW_AT_decl_line(0xa2)
	.dwattr $C$DW$T$323, DW_AT_decl_column(0x13)
$C$DW$T$324	.dwtag  DW_TAG_typedef, DW_AT_name("_iq2")
	.dwattr $C$DW$T$324, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$324, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$324, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$324, DW_AT_decl_line(0xa3)
	.dwattr $C$DW$T$324, DW_AT_decl_column(0x13)
$C$DW$T$325	.dwtag  DW_TAG_typedef, DW_AT_name("_iq1")
	.dwattr $C$DW$T$325, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$325, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$325, DW_AT_decl_file("../../../include/IQmathLib.h")
	.dwattr $C$DW$T$325, DW_AT_decl_line(0xa4)
	.dwattr $C$DW$T$325, DW_AT_decl_column(0x13)
$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x02)
$C$DW$T$334	.dwtag  DW_TAG_typedef, DW_AT_name("size_t")
	.dwattr $C$DW$T$334, DW_AT_type(*$C$DW$T$13)
	.dwattr $C$DW$T$334, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$334, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$T$334, DW_AT_decl_line(0x19)
	.dwattr $C$DW$T$334, DW_AT_decl_column(0x19)
$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x04)
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x04)
$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x02)
$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x02)
$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x04)

$C$DW$T$24	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$24, DW_AT_name("FILE")
	.dwattr $C$DW$T$24, DW_AT_byte_size(0x0c)
$C$DW$443	.dwtag  DW_TAG_member
	.dwattr $C$DW$443, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$443, DW_AT_name("fd")
	.dwattr $C$DW$443, DW_AT_TI_symbol_name("_fd")
	.dwattr $C$DW$443, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$443, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$443, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$443, DW_AT_decl_line(0x1d)
	.dwattr $C$DW$443, DW_AT_decl_column(0x0b)
$C$DW$444	.dwtag  DW_TAG_member
	.dwattr $C$DW$444, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$444, DW_AT_name("buf")
	.dwattr $C$DW$444, DW_AT_TI_symbol_name("_buf")
	.dwattr $C$DW$444, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$444, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$444, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$444, DW_AT_decl_line(0x1e)
	.dwattr $C$DW$444, DW_AT_decl_column(0x16)
$C$DW$445	.dwtag  DW_TAG_member
	.dwattr $C$DW$445, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$445, DW_AT_name("pos")
	.dwattr $C$DW$445, DW_AT_TI_symbol_name("_pos")
	.dwattr $C$DW$445, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$445, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$445, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$445, DW_AT_decl_line(0x1f)
	.dwattr $C$DW$445, DW_AT_decl_column(0x16)
$C$DW$446	.dwtag  DW_TAG_member
	.dwattr $C$DW$446, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$446, DW_AT_name("bufend")
	.dwattr $C$DW$446, DW_AT_TI_symbol_name("_bufend")
	.dwattr $C$DW$446, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr $C$DW$446, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$446, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$446, DW_AT_decl_line(0x20)
	.dwattr $C$DW$446, DW_AT_decl_column(0x16)
$C$DW$447	.dwtag  DW_TAG_member
	.dwattr $C$DW$447, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$447, DW_AT_name("buff_stop")
	.dwattr $C$DW$447, DW_AT_TI_symbol_name("_buff_stop")
	.dwattr $C$DW$447, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$447, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$447, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$447, DW_AT_decl_line(0x21)
	.dwattr $C$DW$447, DW_AT_decl_column(0x16)
$C$DW$448	.dwtag  DW_TAG_member
	.dwattr $C$DW$448, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$448, DW_AT_name("flags")
	.dwattr $C$DW$448, DW_AT_TI_symbol_name("_flags")
	.dwattr $C$DW$448, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr $C$DW$448, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$448, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$448, DW_AT_decl_line(0x22)
	.dwattr $C$DW$448, DW_AT_decl_column(0x16)

$C$DW$3	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("___as__Q2_3std4FILEFRCQ2_3std4FILE")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$3, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$449	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$449, DW_AT_type(*$C$DW$T$22)
	.dwendtag $C$DW$3

	.dwendtag $C$DW$T$24

	.dwattr $C$DW$T$24, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$T$24, DW_AT_decl_line(0x1c)
	.dwattr $C$DW$T$24, DW_AT_decl_column(0x10)
$C$DW$T$20	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$20, DW_AT_address_class(0x16)

$C$DW$T$23	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$450	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$450, DW_AT_type(*$C$DW$T$22)
	.dwendtag $C$DW$T$23

$C$DW$451	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$451, DW_AT_type(*$C$DW$T$24)
$C$DW$T$21	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$451)
$C$DW$T$22	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$T$22, DW_AT_address_class(0x16)
$C$DW$T$335	.dwtag  DW_TAG_typedef, DW_AT_name("FILE")
	.dwattr $C$DW$T$335, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$335, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$335, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdio.h")
	.dwattr $C$DW$T$335, DW_AT_decl_line(0x23)
	.dwattr $C$DW$T$335, DW_AT_decl_column(0x03)

$C$DW$T$29	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$29, DW_AT_name("div_t")
	.dwattr $C$DW$T$29, DW_AT_byte_size(0x02)
$C$DW$452	.dwtag  DW_TAG_member
	.dwattr $C$DW$452, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$452, DW_AT_name("quot")
	.dwattr $C$DW$452, DW_AT_TI_symbol_name("_quot")
	.dwattr $C$DW$452, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$452, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$452, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$452, DW_AT_decl_line(0x12)
	.dwattr $C$DW$452, DW_AT_decl_column(0x16)
$C$DW$453	.dwtag  DW_TAG_member
	.dwattr $C$DW$453, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$453, DW_AT_name("rem")
	.dwattr $C$DW$453, DW_AT_TI_symbol_name("_rem")
	.dwattr $C$DW$453, DW_AT_data_member_location[DW_OP_plus_uconst 0x1]
	.dwattr $C$DW$453, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$453, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$453, DW_AT_decl_line(0x12)
	.dwattr $C$DW$453, DW_AT_decl_column(0x1c)

$C$DW$4	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$4, DW_AT_declaration
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("___as__Q2_3std5div_tFRCQ2_3std5div_t")
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$4, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$454	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$454, DW_AT_type(*$C$DW$T$27)
	.dwendtag $C$DW$4

	.dwendtag $C$DW$T$29

	.dwattr $C$DW$T$29, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$29, DW_AT_decl_line(0x12)
	.dwattr $C$DW$T$29, DW_AT_decl_column(0x10)
$C$DW$T$25	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$25, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$25, DW_AT_address_class(0x16)

$C$DW$T$28	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$28, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$455	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$455, DW_AT_type(*$C$DW$T$27)
	.dwendtag $C$DW$T$28

$C$DW$456	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$456, DW_AT_type(*$C$DW$T$29)
$C$DW$T$26	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$456)
$C$DW$T$27	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$27, DW_AT_address_class(0x16)
$C$DW$T$336	.dwtag  DW_TAG_typedef, DW_AT_name("div_t")
	.dwattr $C$DW$T$336, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$336, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$336, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$336, DW_AT_decl_line(0x12)
	.dwattr $C$DW$T$336, DW_AT_decl_column(0x23)

$C$DW$T$34	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$34, DW_AT_name("ldiv_t")
	.dwattr $C$DW$T$34, DW_AT_byte_size(0x04)
$C$DW$457	.dwtag  DW_TAG_member
	.dwattr $C$DW$457, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$457, DW_AT_name("quot")
	.dwattr $C$DW$457, DW_AT_TI_symbol_name("_quot")
	.dwattr $C$DW$457, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$457, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$457, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$457, DW_AT_decl_line(0x14)
	.dwattr $C$DW$457, DW_AT_decl_column(0x17)
$C$DW$458	.dwtag  DW_TAG_member
	.dwattr $C$DW$458, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$458, DW_AT_name("rem")
	.dwattr $C$DW$458, DW_AT_TI_symbol_name("_rem")
	.dwattr $C$DW$458, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$458, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$458, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$458, DW_AT_decl_line(0x14)
	.dwattr $C$DW$458, DW_AT_decl_column(0x1d)

$C$DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$5, DW_AT_declaration
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("___as__Q2_3std6ldiv_tFRCQ2_3std6ldiv_t")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$5, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$459	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$459, DW_AT_type(*$C$DW$T$32)
	.dwendtag $C$DW$5

	.dwendtag $C$DW$T$34

	.dwattr $C$DW$T$34, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$34, DW_AT_decl_line(0x14)
	.dwattr $C$DW$T$34, DW_AT_decl_column(0x10)
$C$DW$T$30	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$T$30, DW_AT_address_class(0x16)

$C$DW$T$33	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$460	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$460, DW_AT_type(*$C$DW$T$32)
	.dwendtag $C$DW$T$33

$C$DW$461	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$461, DW_AT_type(*$C$DW$T$34)
$C$DW$T$31	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$461)
$C$DW$T$32	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$32, DW_AT_address_class(0x16)
$C$DW$T$337	.dwtag  DW_TAG_typedef, DW_AT_name("ldiv_t")
	.dwattr $C$DW$T$337, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$T$337, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$337, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$337, DW_AT_decl_line(0x14)
	.dwattr $C$DW$T$337, DW_AT_decl_column(0x24)

$C$DW$T$39	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$39, DW_AT_name("lldiv_t")
	.dwattr $C$DW$T$39, DW_AT_byte_size(0x08)
$C$DW$462	.dwtag  DW_TAG_member
	.dwattr $C$DW$462, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$462, DW_AT_name("quot")
	.dwattr $C$DW$462, DW_AT_TI_symbol_name("_quot")
	.dwattr $C$DW$462, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$462, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$462, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$462, DW_AT_decl_line(0x17)
	.dwattr $C$DW$462, DW_AT_decl_column(0x1c)
$C$DW$463	.dwtag  DW_TAG_member
	.dwattr $C$DW$463, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$463, DW_AT_name("rem")
	.dwattr $C$DW$463, DW_AT_TI_symbol_name("_rem")
	.dwattr $C$DW$463, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$463, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$463, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$463, DW_AT_decl_line(0x17)
	.dwattr $C$DW$463, DW_AT_decl_column(0x22)

$C$DW$6	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$6, DW_AT_declaration
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("___as__Q2_3std7lldiv_tFRCQ2_3std7lldiv_t")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$6, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$464	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$464, DW_AT_type(*$C$DW$T$37)
	.dwendtag $C$DW$6

	.dwendtag $C$DW$T$39

	.dwattr $C$DW$T$39, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$39, DW_AT_decl_line(0x17)
	.dwattr $C$DW$T$39, DW_AT_decl_column(0x10)
$C$DW$T$35	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$T$35, DW_AT_address_class(0x16)

$C$DW$T$38	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$38, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$T$38, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$465	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$465, DW_AT_type(*$C$DW$T$37)
	.dwendtag $C$DW$T$38

$C$DW$466	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$466, DW_AT_type(*$C$DW$T$39)
$C$DW$T$36	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$466)
$C$DW$T$37	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$T$37, DW_AT_address_class(0x16)
$C$DW$T$338	.dwtag  DW_TAG_typedef, DW_AT_name("lldiv_t")
	.dwattr $C$DW$T$338, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$T$338, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$338, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdlib.h")
	.dwattr $C$DW$T$338, DW_AT_decl_line(0x17)
	.dwattr $C$DW$T$338, DW_AT_decl_column(0x29)

$C$DW$T$50	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$50, DW_AT_name("iq")
	.dwattr $C$DW$T$50, DW_AT_byte_size(0x02)
$C$DW$467	.dwtag  DW_TAG_member
	.dwattr $C$DW$467, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$467, DW_AT_name("val")
	.dwattr $C$DW$467, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$467, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$467, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$467, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$467, DW_AT_decl_line(0x56)
	.dwattr $C$DW$467, DW_AT_decl_column(0x0a)

$C$DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("iq")
	.dwattr $C$DW$7, DW_AT_declaration
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("___ct__2iqFv")
	.dwattr $C$DW$7, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$8	.dwtag  DW_TAG_subprogram, DW_AT_name("iq")
	.dwattr $C$DW$8, DW_AT_declaration
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("___ct__2iqFl")
	.dwattr $C$DW$8, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$468	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$468, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$8


$C$DW$9	.dwtag  DW_TAG_subprogram, DW_AT_name("iq")
	.dwattr $C$DW$9, DW_AT_declaration
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("___ct__2iqFRC2iq")
	.dwattr $C$DW$9, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$469	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$469, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$9


$C$DW$10	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$10, DW_AT_declaration
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("___as__2iqFRC2iq")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$10, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$470	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$470, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$10


$C$DW$11	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$11, DW_AT_declaration
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("___apl__2iqFRC2iq")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$11, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$471	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$471, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$11


$C$DW$12	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$12, DW_AT_declaration
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("___ami__2iqFRC2iq")
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$12, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$472	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$472, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$12


$C$DW$13	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$13, DW_AT_declaration
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("___amu__2iqFRC2iq")
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$13, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$473	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$473, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$13


$C$DW$14	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$14, DW_AT_declaration
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("___adv__2iqFRC2iq")
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$14, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$474	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$474, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$14


$C$DW$15	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$15, DW_AT_declaration
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("___aad__2iqFRCl")
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$15, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$475	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$475, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$15


$C$DW$16	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$16, DW_AT_declaration
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("___aor__2iqFRCl")
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$16, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$476	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$476, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$16


$C$DW$17	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$17, DW_AT_declaration
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("___aer__2iqFRCl")
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$17, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$477	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$477, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$17

	.dwendtag $C$DW$T$50

	.dwattr $C$DW$T$50, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$50, DW_AT_decl_line(0x40)
	.dwattr $C$DW$T$50, DW_AT_decl_column(0x08)
$C$DW$478	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$478, DW_AT_type(*$C$DW$T$50)
$C$DW$T$42	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$478)
$C$DW$T$43	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$42)
	.dwattr $C$DW$T$43, DW_AT_address_class(0x16)
$C$DW$T$45	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$T$45, DW_AT_address_class(0x16)

$C$DW$T$46	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$479	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$479, DW_AT_type(*$C$DW$T$43)
	.dwendtag $C$DW$T$46


$C$DW$T$49	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$T$49, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$480	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$480, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$49


$C$DW$T$261	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$261, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$T$261, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$261, DW_AT_byte_size(0x80)
$C$DW$481	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$481, DW_AT_upper_bound(0x3f)
	.dwendtag $C$DW$T$261

$C$DW$T$339	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$339, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$T$339, DW_AT_address_class(0x16)

$C$DW$T$57	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$57, DW_AT_name("iq30")
	.dwattr $C$DW$T$57, DW_AT_byte_size(0x02)
$C$DW$482	.dwtag  DW_TAG_member
	.dwattr $C$DW$482, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$482, DW_AT_name("val")
	.dwattr $C$DW$482, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$482, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$482, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$482, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$482, DW_AT_decl_line(0x6f)
	.dwattr $C$DW$482, DW_AT_decl_column(0x0a)

$C$DW$18	.dwtag  DW_TAG_subprogram, DW_AT_name("iq30")
	.dwattr $C$DW$18, DW_AT_declaration
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("___ct__4iq30Fv")
	.dwattr $C$DW$18, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$19	.dwtag  DW_TAG_subprogram, DW_AT_name("iq30")
	.dwattr $C$DW$19, DW_AT_declaration
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("___ct__4iq30Fl")
	.dwattr $C$DW$19, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$483	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$483, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$19


$C$DW$20	.dwtag  DW_TAG_subprogram, DW_AT_name("iq30")
	.dwattr $C$DW$20, DW_AT_declaration
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("___ct__4iq30FRC4iq30")
	.dwattr $C$DW$20, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$484	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$484, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$20


$C$DW$21	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$21, DW_AT_declaration
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("___as__4iq30FRC4iq30")
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$21, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$485	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$485, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$21


$C$DW$22	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$22, DW_AT_declaration
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("___apl__4iq30FRC4iq30")
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$22, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$486	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$486, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$22


$C$DW$23	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$23, DW_AT_declaration
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("___ami__4iq30FRC4iq30")
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$23, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$487	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$487, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$23


$C$DW$24	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$24, DW_AT_declaration
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("___amu__4iq30FRC4iq30")
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$24, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$488	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$488, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$24


$C$DW$25	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$25, DW_AT_declaration
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("___adv__4iq30FRC4iq30")
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$25, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$489	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$489, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$25


$C$DW$26	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$26, DW_AT_declaration
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("___aad__4iq30FRCl")
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$26, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$490	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$490, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$26


$C$DW$27	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$27, DW_AT_declaration
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("___aor__4iq30FRCl")
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$27, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$491	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$491, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$27


$C$DW$28	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$28, DW_AT_declaration
	.dwattr $C$DW$28, DW_AT_TI_symbol_name("___aer__4iq30FRCl")
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$28, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$492	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$492, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$28

	.dwendtag $C$DW$T$57

	.dwattr $C$DW$T$57, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$57, DW_AT_decl_line(0x59)
	.dwattr $C$DW$T$57, DW_AT_decl_column(0x08)
$C$DW$493	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$493, DW_AT_type(*$C$DW$T$57)
$C$DW$T$51	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$51, DW_AT_type(*$C$DW$493)
$C$DW$T$52	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$52, DW_AT_type(*$C$DW$T$51)
	.dwattr $C$DW$T$52, DW_AT_address_class(0x16)
$C$DW$T$54	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$54, DW_AT_type(*$C$DW$T$57)
	.dwattr $C$DW$T$54, DW_AT_address_class(0x16)

$C$DW$T$55	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$55, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$55, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$494	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$494, DW_AT_type(*$C$DW$T$52)
	.dwendtag $C$DW$T$55


$C$DW$T$56	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$56, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$56, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$495	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$495, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$56


$C$DW$T$64	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$64, DW_AT_name("iq29")
	.dwattr $C$DW$T$64, DW_AT_byte_size(0x02)
$C$DW$496	.dwtag  DW_TAG_member
	.dwattr $C$DW$496, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$496, DW_AT_name("val")
	.dwattr $C$DW$496, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$496, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$496, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$496, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$496, DW_AT_decl_line(0x88)
	.dwattr $C$DW$496, DW_AT_decl_column(0x0a)

$C$DW$29	.dwtag  DW_TAG_subprogram, DW_AT_name("iq29")
	.dwattr $C$DW$29, DW_AT_declaration
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("___ct__4iq29Fv")
	.dwattr $C$DW$29, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$30	.dwtag  DW_TAG_subprogram, DW_AT_name("iq29")
	.dwattr $C$DW$30, DW_AT_declaration
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("___ct__4iq29Fl")
	.dwattr $C$DW$30, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$497	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$497, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$30


$C$DW$31	.dwtag  DW_TAG_subprogram, DW_AT_name("iq29")
	.dwattr $C$DW$31, DW_AT_declaration
	.dwattr $C$DW$31, DW_AT_TI_symbol_name("___ct__4iq29FRC4iq29")
	.dwattr $C$DW$31, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$498	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$498, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$31


$C$DW$32	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$32, DW_AT_declaration
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("___as__4iq29FRC4iq29")
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$32, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$499	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$499, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$32


$C$DW$33	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$33, DW_AT_declaration
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("___apl__4iq29FRC4iq29")
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$33, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$500	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$500, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$33


$C$DW$34	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$34, DW_AT_declaration
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("___ami__4iq29FRC4iq29")
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$34, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$501	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$501, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$34


$C$DW$35	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$35, DW_AT_declaration
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("___amu__4iq29FRC4iq29")
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$35, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$502	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$502, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$35


$C$DW$36	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$36, DW_AT_declaration
	.dwattr $C$DW$36, DW_AT_TI_symbol_name("___adv__4iq29FRC4iq29")
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$36, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$503	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$503, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$36


$C$DW$37	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$37, DW_AT_declaration
	.dwattr $C$DW$37, DW_AT_TI_symbol_name("___aad__4iq29FRCl")
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$37, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$504	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$504, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$37


$C$DW$38	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$38, DW_AT_declaration
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("___aor__4iq29FRCl")
	.dwattr $C$DW$38, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$38, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$505	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$505, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$38


$C$DW$39	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$39, DW_AT_declaration
	.dwattr $C$DW$39, DW_AT_TI_symbol_name("___aer__4iq29FRCl")
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$39, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$506	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$506, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$39

	.dwendtag $C$DW$T$64

	.dwattr $C$DW$T$64, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$64, DW_AT_decl_line(0x72)
	.dwattr $C$DW$T$64, DW_AT_decl_column(0x08)
$C$DW$507	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$507, DW_AT_type(*$C$DW$T$64)
$C$DW$T$58	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$58, DW_AT_type(*$C$DW$507)
$C$DW$T$59	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$59, DW_AT_type(*$C$DW$T$58)
	.dwattr $C$DW$T$59, DW_AT_address_class(0x16)
$C$DW$T$61	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$61, DW_AT_type(*$C$DW$T$64)
	.dwattr $C$DW$T$61, DW_AT_address_class(0x16)

$C$DW$T$62	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$62, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$T$62, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$508	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$508, DW_AT_type(*$C$DW$T$59)
	.dwendtag $C$DW$T$62


$C$DW$T$63	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$63, DW_AT_type(*$C$DW$T$61)
	.dwattr $C$DW$T$63, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$509	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$509, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$63


$C$DW$T$71	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$71, DW_AT_name("iq28")
	.dwattr $C$DW$T$71, DW_AT_byte_size(0x02)
$C$DW$510	.dwtag  DW_TAG_member
	.dwattr $C$DW$510, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$510, DW_AT_name("val")
	.dwattr $C$DW$510, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$510, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$510, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$510, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$510, DW_AT_decl_line(0xa1)
	.dwattr $C$DW$510, DW_AT_decl_column(0x0a)

$C$DW$40	.dwtag  DW_TAG_subprogram, DW_AT_name("iq28")
	.dwattr $C$DW$40, DW_AT_declaration
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("___ct__4iq28Fv")
	.dwattr $C$DW$40, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$41	.dwtag  DW_TAG_subprogram, DW_AT_name("iq28")
	.dwattr $C$DW$41, DW_AT_declaration
	.dwattr $C$DW$41, DW_AT_TI_symbol_name("___ct__4iq28Fl")
	.dwattr $C$DW$41, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$511	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$511, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$41


$C$DW$42	.dwtag  DW_TAG_subprogram, DW_AT_name("iq28")
	.dwattr $C$DW$42, DW_AT_declaration
	.dwattr $C$DW$42, DW_AT_TI_symbol_name("___ct__4iq28FRC4iq28")
	.dwattr $C$DW$42, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$512	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$512, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$42


$C$DW$43	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$43, DW_AT_declaration
	.dwattr $C$DW$43, DW_AT_TI_symbol_name("___as__4iq28FRC4iq28")
	.dwattr $C$DW$43, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$43, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$513	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$513, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$43


$C$DW$44	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$44, DW_AT_declaration
	.dwattr $C$DW$44, DW_AT_TI_symbol_name("___apl__4iq28FRC4iq28")
	.dwattr $C$DW$44, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$44, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$514	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$514, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$44


$C$DW$45	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$45, DW_AT_declaration
	.dwattr $C$DW$45, DW_AT_TI_symbol_name("___ami__4iq28FRC4iq28")
	.dwattr $C$DW$45, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$45, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$515	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$515, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$45


$C$DW$46	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$46, DW_AT_declaration
	.dwattr $C$DW$46, DW_AT_TI_symbol_name("___amu__4iq28FRC4iq28")
	.dwattr $C$DW$46, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$46, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$516	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$516, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$46


$C$DW$47	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$47, DW_AT_declaration
	.dwattr $C$DW$47, DW_AT_TI_symbol_name("___adv__4iq28FRC4iq28")
	.dwattr $C$DW$47, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$47, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$517	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$517, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$47


$C$DW$48	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$48, DW_AT_declaration
	.dwattr $C$DW$48, DW_AT_TI_symbol_name("___aad__4iq28FRCl")
	.dwattr $C$DW$48, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$48, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$518	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$518, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$48


$C$DW$49	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$49, DW_AT_declaration
	.dwattr $C$DW$49, DW_AT_TI_symbol_name("___aor__4iq28FRCl")
	.dwattr $C$DW$49, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$49, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$519	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$519, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$49


$C$DW$50	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$50, DW_AT_declaration
	.dwattr $C$DW$50, DW_AT_TI_symbol_name("___aer__4iq28FRCl")
	.dwattr $C$DW$50, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$50, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$520	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$520, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$50

	.dwendtag $C$DW$T$71

	.dwattr $C$DW$T$71, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$71, DW_AT_decl_line(0x8b)
	.dwattr $C$DW$T$71, DW_AT_decl_column(0x08)
$C$DW$521	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$521, DW_AT_type(*$C$DW$T$71)
$C$DW$T$65	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$65, DW_AT_type(*$C$DW$521)
$C$DW$T$66	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$66, DW_AT_type(*$C$DW$T$65)
	.dwattr $C$DW$T$66, DW_AT_address_class(0x16)
$C$DW$T$68	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$68, DW_AT_type(*$C$DW$T$71)
	.dwattr $C$DW$T$68, DW_AT_address_class(0x16)

$C$DW$T$69	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$69, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$T$69, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$522	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$522, DW_AT_type(*$C$DW$T$66)
	.dwendtag $C$DW$T$69


$C$DW$T$70	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$70, DW_AT_type(*$C$DW$T$68)
	.dwattr $C$DW$T$70, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$523	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$523, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$70


$C$DW$T$78	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$78, DW_AT_name("iq27")
	.dwattr $C$DW$T$78, DW_AT_byte_size(0x02)
$C$DW$524	.dwtag  DW_TAG_member
	.dwattr $C$DW$524, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$524, DW_AT_name("val")
	.dwattr $C$DW$524, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$524, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$524, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$524, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$524, DW_AT_decl_line(0xba)
	.dwattr $C$DW$524, DW_AT_decl_column(0x0a)

$C$DW$51	.dwtag  DW_TAG_subprogram, DW_AT_name("iq27")
	.dwattr $C$DW$51, DW_AT_declaration
	.dwattr $C$DW$51, DW_AT_TI_symbol_name("___ct__4iq27Fv")
	.dwattr $C$DW$51, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$52	.dwtag  DW_TAG_subprogram, DW_AT_name("iq27")
	.dwattr $C$DW$52, DW_AT_declaration
	.dwattr $C$DW$52, DW_AT_TI_symbol_name("___ct__4iq27Fl")
	.dwattr $C$DW$52, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$525	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$525, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$52


$C$DW$53	.dwtag  DW_TAG_subprogram, DW_AT_name("iq27")
	.dwattr $C$DW$53, DW_AT_declaration
	.dwattr $C$DW$53, DW_AT_TI_symbol_name("___ct__4iq27FRC4iq27")
	.dwattr $C$DW$53, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$526	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$526, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$53


$C$DW$54	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$54, DW_AT_declaration
	.dwattr $C$DW$54, DW_AT_TI_symbol_name("___as__4iq27FRC4iq27")
	.dwattr $C$DW$54, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$54, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$527	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$527, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$54


$C$DW$55	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$55, DW_AT_declaration
	.dwattr $C$DW$55, DW_AT_TI_symbol_name("___apl__4iq27FRC4iq27")
	.dwattr $C$DW$55, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$55, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$528	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$528, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$55


$C$DW$56	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$56, DW_AT_declaration
	.dwattr $C$DW$56, DW_AT_TI_symbol_name("___ami__4iq27FRC4iq27")
	.dwattr $C$DW$56, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$56, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$529	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$529, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$56


$C$DW$57	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$57, DW_AT_declaration
	.dwattr $C$DW$57, DW_AT_TI_symbol_name("___amu__4iq27FRC4iq27")
	.dwattr $C$DW$57, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$57, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$530	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$530, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$57


$C$DW$58	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$58, DW_AT_declaration
	.dwattr $C$DW$58, DW_AT_TI_symbol_name("___adv__4iq27FRC4iq27")
	.dwattr $C$DW$58, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$58, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$531	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$531, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$58


$C$DW$59	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$59, DW_AT_declaration
	.dwattr $C$DW$59, DW_AT_TI_symbol_name("___aad__4iq27FRCl")
	.dwattr $C$DW$59, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$59, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$532	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$532, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$59


$C$DW$60	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$60, DW_AT_declaration
	.dwattr $C$DW$60, DW_AT_TI_symbol_name("___aor__4iq27FRCl")
	.dwattr $C$DW$60, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$60, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$533	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$533, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$60


$C$DW$61	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$61, DW_AT_declaration
	.dwattr $C$DW$61, DW_AT_TI_symbol_name("___aer__4iq27FRCl")
	.dwattr $C$DW$61, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$61, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$534	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$534, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$61

	.dwendtag $C$DW$T$78

	.dwattr $C$DW$T$78, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$78, DW_AT_decl_line(0xa4)
	.dwattr $C$DW$T$78, DW_AT_decl_column(0x08)
$C$DW$535	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$535, DW_AT_type(*$C$DW$T$78)
$C$DW$T$72	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$72, DW_AT_type(*$C$DW$535)
$C$DW$T$73	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$73, DW_AT_type(*$C$DW$T$72)
	.dwattr $C$DW$T$73, DW_AT_address_class(0x16)
$C$DW$T$75	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$75, DW_AT_type(*$C$DW$T$78)
	.dwattr $C$DW$T$75, DW_AT_address_class(0x16)

$C$DW$T$76	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$76, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$T$76, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$536	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$536, DW_AT_type(*$C$DW$T$73)
	.dwendtag $C$DW$T$76


$C$DW$T$77	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$77, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$T$77, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$537	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$537, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$77


$C$DW$T$85	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$85, DW_AT_name("iq26")
	.dwattr $C$DW$T$85, DW_AT_byte_size(0x02)
$C$DW$538	.dwtag  DW_TAG_member
	.dwattr $C$DW$538, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$538, DW_AT_name("val")
	.dwattr $C$DW$538, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$538, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$538, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$538, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$538, DW_AT_decl_line(0xd3)
	.dwattr $C$DW$538, DW_AT_decl_column(0x0a)

$C$DW$62	.dwtag  DW_TAG_subprogram, DW_AT_name("iq26")
	.dwattr $C$DW$62, DW_AT_declaration
	.dwattr $C$DW$62, DW_AT_TI_symbol_name("___ct__4iq26Fv")
	.dwattr $C$DW$62, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$63	.dwtag  DW_TAG_subprogram, DW_AT_name("iq26")
	.dwattr $C$DW$63, DW_AT_declaration
	.dwattr $C$DW$63, DW_AT_TI_symbol_name("___ct__4iq26Fl")
	.dwattr $C$DW$63, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$539	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$539, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$63


$C$DW$64	.dwtag  DW_TAG_subprogram, DW_AT_name("iq26")
	.dwattr $C$DW$64, DW_AT_declaration
	.dwattr $C$DW$64, DW_AT_TI_symbol_name("___ct__4iq26FRC4iq26")
	.dwattr $C$DW$64, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$540	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$540, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$64


$C$DW$65	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$65, DW_AT_declaration
	.dwattr $C$DW$65, DW_AT_TI_symbol_name("___as__4iq26FRC4iq26")
	.dwattr $C$DW$65, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$65, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$541	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$541, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$65


$C$DW$66	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$66, DW_AT_declaration
	.dwattr $C$DW$66, DW_AT_TI_symbol_name("___apl__4iq26FRC4iq26")
	.dwattr $C$DW$66, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$66, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$542	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$542, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$66


$C$DW$67	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$67, DW_AT_declaration
	.dwattr $C$DW$67, DW_AT_TI_symbol_name("___ami__4iq26FRC4iq26")
	.dwattr $C$DW$67, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$67, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$543	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$543, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$67


$C$DW$68	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$68, DW_AT_declaration
	.dwattr $C$DW$68, DW_AT_TI_symbol_name("___amu__4iq26FRC4iq26")
	.dwattr $C$DW$68, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$68, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$544	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$544, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$68


$C$DW$69	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$69, DW_AT_declaration
	.dwattr $C$DW$69, DW_AT_TI_symbol_name("___adv__4iq26FRC4iq26")
	.dwattr $C$DW$69, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$69, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$545	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$545, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$69


$C$DW$70	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$70, DW_AT_declaration
	.dwattr $C$DW$70, DW_AT_TI_symbol_name("___aad__4iq26FRCl")
	.dwattr $C$DW$70, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$70, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$546	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$546, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$70


$C$DW$71	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$71, DW_AT_declaration
	.dwattr $C$DW$71, DW_AT_TI_symbol_name("___aor__4iq26FRCl")
	.dwattr $C$DW$71, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$71, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$547	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$547, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$71


$C$DW$72	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$72, DW_AT_declaration
	.dwattr $C$DW$72, DW_AT_TI_symbol_name("___aer__4iq26FRCl")
	.dwattr $C$DW$72, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$72, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$548	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$548, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$72

	.dwendtag $C$DW$T$85

	.dwattr $C$DW$T$85, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$85, DW_AT_decl_line(0xbd)
	.dwattr $C$DW$T$85, DW_AT_decl_column(0x08)
$C$DW$549	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$549, DW_AT_type(*$C$DW$T$85)
$C$DW$T$79	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$79, DW_AT_type(*$C$DW$549)
$C$DW$T$80	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$80, DW_AT_type(*$C$DW$T$79)
	.dwattr $C$DW$T$80, DW_AT_address_class(0x16)
$C$DW$T$82	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$82, DW_AT_type(*$C$DW$T$85)
	.dwattr $C$DW$T$82, DW_AT_address_class(0x16)

$C$DW$T$83	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$83, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$T$83, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$550	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$550, DW_AT_type(*$C$DW$T$80)
	.dwendtag $C$DW$T$83


$C$DW$T$84	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$84, DW_AT_type(*$C$DW$T$82)
	.dwattr $C$DW$T$84, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$551	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$551, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$84


$C$DW$T$92	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$92, DW_AT_name("iq25")
	.dwattr $C$DW$T$92, DW_AT_byte_size(0x02)
$C$DW$552	.dwtag  DW_TAG_member
	.dwattr $C$DW$552, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$552, DW_AT_name("val")
	.dwattr $C$DW$552, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$552, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$552, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$552, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$552, DW_AT_decl_line(0xec)
	.dwattr $C$DW$552, DW_AT_decl_column(0x0a)

$C$DW$73	.dwtag  DW_TAG_subprogram, DW_AT_name("iq25")
	.dwattr $C$DW$73, DW_AT_declaration
	.dwattr $C$DW$73, DW_AT_TI_symbol_name("___ct__4iq25Fv")
	.dwattr $C$DW$73, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$74	.dwtag  DW_TAG_subprogram, DW_AT_name("iq25")
	.dwattr $C$DW$74, DW_AT_declaration
	.dwattr $C$DW$74, DW_AT_TI_symbol_name("___ct__4iq25Fl")
	.dwattr $C$DW$74, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$553	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$553, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$74


$C$DW$75	.dwtag  DW_TAG_subprogram, DW_AT_name("iq25")
	.dwattr $C$DW$75, DW_AT_declaration
	.dwattr $C$DW$75, DW_AT_TI_symbol_name("___ct__4iq25FRC4iq25")
	.dwattr $C$DW$75, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$554	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$554, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$75


$C$DW$76	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$76, DW_AT_declaration
	.dwattr $C$DW$76, DW_AT_TI_symbol_name("___as__4iq25FRC4iq25")
	.dwattr $C$DW$76, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$76, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$555	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$555, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$76


$C$DW$77	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$77, DW_AT_declaration
	.dwattr $C$DW$77, DW_AT_TI_symbol_name("___apl__4iq25FRC4iq25")
	.dwattr $C$DW$77, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$77, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$556	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$556, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$77


$C$DW$78	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$78, DW_AT_declaration
	.dwattr $C$DW$78, DW_AT_TI_symbol_name("___ami__4iq25FRC4iq25")
	.dwattr $C$DW$78, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$78, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$557	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$557, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$78


$C$DW$79	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$79, DW_AT_declaration
	.dwattr $C$DW$79, DW_AT_TI_symbol_name("___amu__4iq25FRC4iq25")
	.dwattr $C$DW$79, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$79, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$558	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$558, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$79


$C$DW$80	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$80, DW_AT_declaration
	.dwattr $C$DW$80, DW_AT_TI_symbol_name("___adv__4iq25FRC4iq25")
	.dwattr $C$DW$80, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$80, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$559	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$559, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$80


$C$DW$81	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$81, DW_AT_declaration
	.dwattr $C$DW$81, DW_AT_TI_symbol_name("___aad__4iq25FRCl")
	.dwattr $C$DW$81, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$81, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$560	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$560, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$81


$C$DW$82	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$82, DW_AT_declaration
	.dwattr $C$DW$82, DW_AT_TI_symbol_name("___aor__4iq25FRCl")
	.dwattr $C$DW$82, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$82, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$561	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$561, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$82


$C$DW$83	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$83, DW_AT_declaration
	.dwattr $C$DW$83, DW_AT_TI_symbol_name("___aer__4iq25FRCl")
	.dwattr $C$DW$83, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$83, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$562	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$562, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$83

	.dwendtag $C$DW$T$92

	.dwattr $C$DW$T$92, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$92, DW_AT_decl_line(0xd6)
	.dwattr $C$DW$T$92, DW_AT_decl_column(0x08)
$C$DW$563	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$563, DW_AT_type(*$C$DW$T$92)
$C$DW$T$86	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$86, DW_AT_type(*$C$DW$563)
$C$DW$T$87	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$87, DW_AT_type(*$C$DW$T$86)
	.dwattr $C$DW$T$87, DW_AT_address_class(0x16)
$C$DW$T$89	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$89, DW_AT_type(*$C$DW$T$92)
	.dwattr $C$DW$T$89, DW_AT_address_class(0x16)

$C$DW$T$90	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$90, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$T$90, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$564	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$564, DW_AT_type(*$C$DW$T$87)
	.dwendtag $C$DW$T$90


$C$DW$T$91	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$91, DW_AT_type(*$C$DW$T$89)
	.dwattr $C$DW$T$91, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$565	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$565, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$91


$C$DW$T$99	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$99, DW_AT_name("iq24")
	.dwattr $C$DW$T$99, DW_AT_byte_size(0x02)
$C$DW$566	.dwtag  DW_TAG_member
	.dwattr $C$DW$566, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$566, DW_AT_name("val")
	.dwattr $C$DW$566, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$566, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$566, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$566, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$566, DW_AT_decl_line(0x106)
	.dwattr $C$DW$566, DW_AT_decl_column(0x0a)

$C$DW$84	.dwtag  DW_TAG_subprogram, DW_AT_name("iq24")
	.dwattr $C$DW$84, DW_AT_declaration
	.dwattr $C$DW$84, DW_AT_TI_symbol_name("___ct__4iq24Fv")
	.dwattr $C$DW$84, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$85	.dwtag  DW_TAG_subprogram, DW_AT_name("iq24")
	.dwattr $C$DW$85, DW_AT_declaration
	.dwattr $C$DW$85, DW_AT_TI_symbol_name("___ct__4iq24Fl")
	.dwattr $C$DW$85, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$567	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$567, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$85


$C$DW$86	.dwtag  DW_TAG_subprogram, DW_AT_name("iq24")
	.dwattr $C$DW$86, DW_AT_declaration
	.dwattr $C$DW$86, DW_AT_TI_symbol_name("___ct__4iq24FRC4iq24")
	.dwattr $C$DW$86, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$568	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$568, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$86


$C$DW$87	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$87, DW_AT_declaration
	.dwattr $C$DW$87, DW_AT_TI_symbol_name("___as__4iq24FRC4iq24")
	.dwattr $C$DW$87, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$87, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$569	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$569, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$87


$C$DW$88	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$88, DW_AT_declaration
	.dwattr $C$DW$88, DW_AT_TI_symbol_name("___apl__4iq24FRC4iq24")
	.dwattr $C$DW$88, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$88, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$570	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$570, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$88


$C$DW$89	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$89, DW_AT_declaration
	.dwattr $C$DW$89, DW_AT_TI_symbol_name("___ami__4iq24FRC4iq24")
	.dwattr $C$DW$89, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$89, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$571	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$571, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$89


$C$DW$90	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$90, DW_AT_declaration
	.dwattr $C$DW$90, DW_AT_TI_symbol_name("___amu__4iq24FRC4iq24")
	.dwattr $C$DW$90, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$90, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$572	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$572, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$90


$C$DW$91	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$91, DW_AT_declaration
	.dwattr $C$DW$91, DW_AT_TI_symbol_name("___adv__4iq24FRC4iq24")
	.dwattr $C$DW$91, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$91, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$573	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$573, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$91


$C$DW$92	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$92, DW_AT_declaration
	.dwattr $C$DW$92, DW_AT_TI_symbol_name("___aad__4iq24FRCl")
	.dwattr $C$DW$92, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$92, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$574	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$574, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$92


$C$DW$93	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$93, DW_AT_declaration
	.dwattr $C$DW$93, DW_AT_TI_symbol_name("___aor__4iq24FRCl")
	.dwattr $C$DW$93, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$93, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$575	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$575, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$93


$C$DW$94	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$94, DW_AT_declaration
	.dwattr $C$DW$94, DW_AT_TI_symbol_name("___aer__4iq24FRCl")
	.dwattr $C$DW$94, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$94, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$576	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$576, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$94

	.dwendtag $C$DW$T$99

	.dwattr $C$DW$T$99, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$99, DW_AT_decl_line(0xf0)
	.dwattr $C$DW$T$99, DW_AT_decl_column(0x08)
$C$DW$577	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$577, DW_AT_type(*$C$DW$T$99)
$C$DW$T$93	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$93, DW_AT_type(*$C$DW$577)
$C$DW$T$94	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$94, DW_AT_type(*$C$DW$T$93)
	.dwattr $C$DW$T$94, DW_AT_address_class(0x16)
$C$DW$T$96	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$96, DW_AT_type(*$C$DW$T$99)
	.dwattr $C$DW$T$96, DW_AT_address_class(0x16)

$C$DW$T$97	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$97, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$T$97, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$578	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$578, DW_AT_type(*$C$DW$T$94)
	.dwendtag $C$DW$T$97


$C$DW$T$98	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$98, DW_AT_type(*$C$DW$T$96)
	.dwattr $C$DW$T$98, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$579	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$579, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$98


$C$DW$T$106	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$106, DW_AT_name("iq23")
	.dwattr $C$DW$T$106, DW_AT_byte_size(0x02)
$C$DW$580	.dwtag  DW_TAG_member
	.dwattr $C$DW$580, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$580, DW_AT_name("val")
	.dwattr $C$DW$580, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$580, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$580, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$580, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$580, DW_AT_decl_line(0x11f)
	.dwattr $C$DW$580, DW_AT_decl_column(0x0a)

$C$DW$95	.dwtag  DW_TAG_subprogram, DW_AT_name("iq23")
	.dwattr $C$DW$95, DW_AT_declaration
	.dwattr $C$DW$95, DW_AT_TI_symbol_name("___ct__4iq23Fv")
	.dwattr $C$DW$95, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$96	.dwtag  DW_TAG_subprogram, DW_AT_name("iq23")
	.dwattr $C$DW$96, DW_AT_declaration
	.dwattr $C$DW$96, DW_AT_TI_symbol_name("___ct__4iq23Fl")
	.dwattr $C$DW$96, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$581	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$581, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$96


$C$DW$97	.dwtag  DW_TAG_subprogram, DW_AT_name("iq23")
	.dwattr $C$DW$97, DW_AT_declaration
	.dwattr $C$DW$97, DW_AT_TI_symbol_name("___ct__4iq23FRC4iq23")
	.dwattr $C$DW$97, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$582	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$582, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$97


$C$DW$98	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$98, DW_AT_declaration
	.dwattr $C$DW$98, DW_AT_TI_symbol_name("___as__4iq23FRC4iq23")
	.dwattr $C$DW$98, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$98, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$583	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$583, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$98


$C$DW$99	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$99, DW_AT_declaration
	.dwattr $C$DW$99, DW_AT_TI_symbol_name("___apl__4iq23FRC4iq23")
	.dwattr $C$DW$99, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$99, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$584	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$584, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$99


$C$DW$100	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$100, DW_AT_declaration
	.dwattr $C$DW$100, DW_AT_TI_symbol_name("___ami__4iq23FRC4iq23")
	.dwattr $C$DW$100, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$100, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$585	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$585, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$100


$C$DW$101	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$101, DW_AT_declaration
	.dwattr $C$DW$101, DW_AT_TI_symbol_name("___amu__4iq23FRC4iq23")
	.dwattr $C$DW$101, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$101, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$586	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$586, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$101


$C$DW$102	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$102, DW_AT_declaration
	.dwattr $C$DW$102, DW_AT_TI_symbol_name("___adv__4iq23FRC4iq23")
	.dwattr $C$DW$102, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$102, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$587	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$587, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$102


$C$DW$103	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$103, DW_AT_declaration
	.dwattr $C$DW$103, DW_AT_TI_symbol_name("___aad__4iq23FRCl")
	.dwattr $C$DW$103, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$103, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$588	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$588, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$103


$C$DW$104	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$104, DW_AT_declaration
	.dwattr $C$DW$104, DW_AT_TI_symbol_name("___aor__4iq23FRCl")
	.dwattr $C$DW$104, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$104, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$589	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$589, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$104


$C$DW$105	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$105, DW_AT_declaration
	.dwattr $C$DW$105, DW_AT_TI_symbol_name("___aer__4iq23FRCl")
	.dwattr $C$DW$105, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$105, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$590	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$590, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$105

	.dwendtag $C$DW$T$106

	.dwattr $C$DW$T$106, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$106, DW_AT_decl_line(0x109)
	.dwattr $C$DW$T$106, DW_AT_decl_column(0x08)
$C$DW$591	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$591, DW_AT_type(*$C$DW$T$106)
$C$DW$T$100	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$100, DW_AT_type(*$C$DW$591)
$C$DW$T$101	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$101, DW_AT_type(*$C$DW$T$100)
	.dwattr $C$DW$T$101, DW_AT_address_class(0x16)
$C$DW$T$103	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$103, DW_AT_type(*$C$DW$T$106)
	.dwattr $C$DW$T$103, DW_AT_address_class(0x16)

$C$DW$T$104	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$104, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$T$104, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$592	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$592, DW_AT_type(*$C$DW$T$101)
	.dwendtag $C$DW$T$104


$C$DW$T$105	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$105, DW_AT_type(*$C$DW$T$103)
	.dwattr $C$DW$T$105, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$593	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$593, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$105


$C$DW$T$113	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$113, DW_AT_name("iq22")
	.dwattr $C$DW$T$113, DW_AT_byte_size(0x02)
$C$DW$594	.dwtag  DW_TAG_member
	.dwattr $C$DW$594, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$594, DW_AT_name("val")
	.dwattr $C$DW$594, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$594, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$594, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$594, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$594, DW_AT_decl_line(0x138)
	.dwattr $C$DW$594, DW_AT_decl_column(0x0a)

$C$DW$106	.dwtag  DW_TAG_subprogram, DW_AT_name("iq22")
	.dwattr $C$DW$106, DW_AT_declaration
	.dwattr $C$DW$106, DW_AT_TI_symbol_name("___ct__4iq22Fv")
	.dwattr $C$DW$106, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$107	.dwtag  DW_TAG_subprogram, DW_AT_name("iq22")
	.dwattr $C$DW$107, DW_AT_declaration
	.dwattr $C$DW$107, DW_AT_TI_symbol_name("___ct__4iq22Fl")
	.dwattr $C$DW$107, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$595	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$595, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$107


$C$DW$108	.dwtag  DW_TAG_subprogram, DW_AT_name("iq22")
	.dwattr $C$DW$108, DW_AT_declaration
	.dwattr $C$DW$108, DW_AT_TI_symbol_name("___ct__4iq22FRC4iq22")
	.dwattr $C$DW$108, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$596	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$596, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$108


$C$DW$109	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$109, DW_AT_declaration
	.dwattr $C$DW$109, DW_AT_TI_symbol_name("___as__4iq22FRC4iq22")
	.dwattr $C$DW$109, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$109, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$597	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$597, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$109


$C$DW$110	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$110, DW_AT_declaration
	.dwattr $C$DW$110, DW_AT_TI_symbol_name("___apl__4iq22FRC4iq22")
	.dwattr $C$DW$110, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$110, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$598	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$598, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$110


$C$DW$111	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$111, DW_AT_declaration
	.dwattr $C$DW$111, DW_AT_TI_symbol_name("___ami__4iq22FRC4iq22")
	.dwattr $C$DW$111, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$111, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$599	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$599, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$111


$C$DW$112	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$112, DW_AT_declaration
	.dwattr $C$DW$112, DW_AT_TI_symbol_name("___amu__4iq22FRC4iq22")
	.dwattr $C$DW$112, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$112, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$600	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$600, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$112


$C$DW$113	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$113, DW_AT_declaration
	.dwattr $C$DW$113, DW_AT_TI_symbol_name("___adv__4iq22FRC4iq22")
	.dwattr $C$DW$113, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$113, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$601	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$601, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$113


$C$DW$114	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$114, DW_AT_declaration
	.dwattr $C$DW$114, DW_AT_TI_symbol_name("___aad__4iq22FRCl")
	.dwattr $C$DW$114, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$114, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$602	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$602, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$114


$C$DW$115	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$115, DW_AT_declaration
	.dwattr $C$DW$115, DW_AT_TI_symbol_name("___aor__4iq22FRCl")
	.dwattr $C$DW$115, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$115, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$603	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$603, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$115


$C$DW$116	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$116, DW_AT_declaration
	.dwattr $C$DW$116, DW_AT_TI_symbol_name("___aer__4iq22FRCl")
	.dwattr $C$DW$116, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$116, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$604	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$604, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$116

	.dwendtag $C$DW$T$113

	.dwattr $C$DW$T$113, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$113, DW_AT_decl_line(0x122)
	.dwattr $C$DW$T$113, DW_AT_decl_column(0x08)
$C$DW$605	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$605, DW_AT_type(*$C$DW$T$113)
$C$DW$T$107	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$107, DW_AT_type(*$C$DW$605)
$C$DW$T$108	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$108, DW_AT_type(*$C$DW$T$107)
	.dwattr $C$DW$T$108, DW_AT_address_class(0x16)
$C$DW$T$110	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$110, DW_AT_type(*$C$DW$T$113)
	.dwattr $C$DW$T$110, DW_AT_address_class(0x16)

$C$DW$T$111	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$111, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$T$111, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$606	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$606, DW_AT_type(*$C$DW$T$108)
	.dwendtag $C$DW$T$111


$C$DW$T$112	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$112, DW_AT_type(*$C$DW$T$110)
	.dwattr $C$DW$T$112, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$607	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$607, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$112


$C$DW$T$120	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$120, DW_AT_name("iq21")
	.dwattr $C$DW$T$120, DW_AT_byte_size(0x02)
$C$DW$608	.dwtag  DW_TAG_member
	.dwattr $C$DW$608, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$608, DW_AT_name("val")
	.dwattr $C$DW$608, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$608, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$608, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$608, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$608, DW_AT_decl_line(0x151)
	.dwattr $C$DW$608, DW_AT_decl_column(0x0a)

$C$DW$117	.dwtag  DW_TAG_subprogram, DW_AT_name("iq21")
	.dwattr $C$DW$117, DW_AT_declaration
	.dwattr $C$DW$117, DW_AT_TI_symbol_name("___ct__4iq21Fv")
	.dwattr $C$DW$117, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$118	.dwtag  DW_TAG_subprogram, DW_AT_name("iq21")
	.dwattr $C$DW$118, DW_AT_declaration
	.dwattr $C$DW$118, DW_AT_TI_symbol_name("___ct__4iq21Fl")
	.dwattr $C$DW$118, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$609	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$609, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$118


$C$DW$119	.dwtag  DW_TAG_subprogram, DW_AT_name("iq21")
	.dwattr $C$DW$119, DW_AT_declaration
	.dwattr $C$DW$119, DW_AT_TI_symbol_name("___ct__4iq21FRC4iq21")
	.dwattr $C$DW$119, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$610	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$610, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$119


$C$DW$120	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$120, DW_AT_declaration
	.dwattr $C$DW$120, DW_AT_TI_symbol_name("___as__4iq21FRC4iq21")
	.dwattr $C$DW$120, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$120, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$611	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$611, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$120


$C$DW$121	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$121, DW_AT_declaration
	.dwattr $C$DW$121, DW_AT_TI_symbol_name("___apl__4iq21FRC4iq21")
	.dwattr $C$DW$121, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$121, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$612	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$612, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$121


$C$DW$122	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$122, DW_AT_declaration
	.dwattr $C$DW$122, DW_AT_TI_symbol_name("___ami__4iq21FRC4iq21")
	.dwattr $C$DW$122, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$122, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$613	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$613, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$122


$C$DW$123	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$123, DW_AT_declaration
	.dwattr $C$DW$123, DW_AT_TI_symbol_name("___amu__4iq21FRC4iq21")
	.dwattr $C$DW$123, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$123, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$614	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$614, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$123


$C$DW$124	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$124, DW_AT_declaration
	.dwattr $C$DW$124, DW_AT_TI_symbol_name("___adv__4iq21FRC4iq21")
	.dwattr $C$DW$124, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$124, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$615	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$615, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$124


$C$DW$125	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$125, DW_AT_declaration
	.dwattr $C$DW$125, DW_AT_TI_symbol_name("___aad__4iq21FRCl")
	.dwattr $C$DW$125, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$125, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$616	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$616, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$125


$C$DW$126	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$126, DW_AT_declaration
	.dwattr $C$DW$126, DW_AT_TI_symbol_name("___aor__4iq21FRCl")
	.dwattr $C$DW$126, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$126, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$617	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$617, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$126


$C$DW$127	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$127, DW_AT_declaration
	.dwattr $C$DW$127, DW_AT_TI_symbol_name("___aer__4iq21FRCl")
	.dwattr $C$DW$127, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$127, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$618	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$618, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$127

	.dwendtag $C$DW$T$120

	.dwattr $C$DW$T$120, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$120, DW_AT_decl_line(0x13b)
	.dwattr $C$DW$T$120, DW_AT_decl_column(0x08)
$C$DW$619	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$619, DW_AT_type(*$C$DW$T$120)
$C$DW$T$114	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$114, DW_AT_type(*$C$DW$619)
$C$DW$T$115	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$115, DW_AT_type(*$C$DW$T$114)
	.dwattr $C$DW$T$115, DW_AT_address_class(0x16)
$C$DW$T$117	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$117, DW_AT_type(*$C$DW$T$120)
	.dwattr $C$DW$T$117, DW_AT_address_class(0x16)

$C$DW$T$118	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$118, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$T$118, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$620	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$620, DW_AT_type(*$C$DW$T$115)
	.dwendtag $C$DW$T$118


$C$DW$T$119	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$119, DW_AT_type(*$C$DW$T$117)
	.dwattr $C$DW$T$119, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$621	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$621, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$119


$C$DW$T$127	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$127, DW_AT_name("iq20")
	.dwattr $C$DW$T$127, DW_AT_byte_size(0x02)
$C$DW$622	.dwtag  DW_TAG_member
	.dwattr $C$DW$622, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$622, DW_AT_name("val")
	.dwattr $C$DW$622, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$622, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$622, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$622, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$622, DW_AT_decl_line(0x16a)
	.dwattr $C$DW$622, DW_AT_decl_column(0x0a)

$C$DW$128	.dwtag  DW_TAG_subprogram, DW_AT_name("iq20")
	.dwattr $C$DW$128, DW_AT_declaration
	.dwattr $C$DW$128, DW_AT_TI_symbol_name("___ct__4iq20Fv")
	.dwattr $C$DW$128, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$129	.dwtag  DW_TAG_subprogram, DW_AT_name("iq20")
	.dwattr $C$DW$129, DW_AT_declaration
	.dwattr $C$DW$129, DW_AT_TI_symbol_name("___ct__4iq20Fl")
	.dwattr $C$DW$129, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$623	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$623, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$129


$C$DW$130	.dwtag  DW_TAG_subprogram, DW_AT_name("iq20")
	.dwattr $C$DW$130, DW_AT_declaration
	.dwattr $C$DW$130, DW_AT_TI_symbol_name("___ct__4iq20FRC4iq20")
	.dwattr $C$DW$130, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$624	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$624, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$130


$C$DW$131	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$131, DW_AT_declaration
	.dwattr $C$DW$131, DW_AT_TI_symbol_name("___as__4iq20FRC4iq20")
	.dwattr $C$DW$131, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$131, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$625	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$625, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$131


$C$DW$132	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$132, DW_AT_declaration
	.dwattr $C$DW$132, DW_AT_TI_symbol_name("___apl__4iq20FRC4iq20")
	.dwattr $C$DW$132, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$132, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$626	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$626, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$132


$C$DW$133	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$133, DW_AT_declaration
	.dwattr $C$DW$133, DW_AT_TI_symbol_name("___ami__4iq20FRC4iq20")
	.dwattr $C$DW$133, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$133, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$627	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$627, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$133


$C$DW$134	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$134, DW_AT_declaration
	.dwattr $C$DW$134, DW_AT_TI_symbol_name("___amu__4iq20FRC4iq20")
	.dwattr $C$DW$134, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$134, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$628	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$628, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$134


$C$DW$135	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$135, DW_AT_declaration
	.dwattr $C$DW$135, DW_AT_TI_symbol_name("___adv__4iq20FRC4iq20")
	.dwattr $C$DW$135, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$135, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$629	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$629, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$135


$C$DW$136	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$136, DW_AT_declaration
	.dwattr $C$DW$136, DW_AT_TI_symbol_name("___aad__4iq20FRCl")
	.dwattr $C$DW$136, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$136, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$630	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$630, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$136


$C$DW$137	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$137, DW_AT_declaration
	.dwattr $C$DW$137, DW_AT_TI_symbol_name("___aor__4iq20FRCl")
	.dwattr $C$DW$137, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$137, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$631	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$631, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$137


$C$DW$138	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$138, DW_AT_declaration
	.dwattr $C$DW$138, DW_AT_TI_symbol_name("___aer__4iq20FRCl")
	.dwattr $C$DW$138, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$138, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$632	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$632, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$138

	.dwendtag $C$DW$T$127

	.dwattr $C$DW$T$127, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$127, DW_AT_decl_line(0x154)
	.dwattr $C$DW$T$127, DW_AT_decl_column(0x08)
$C$DW$633	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$633, DW_AT_type(*$C$DW$T$127)
$C$DW$T$121	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$121, DW_AT_type(*$C$DW$633)
$C$DW$T$122	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$122, DW_AT_type(*$C$DW$T$121)
	.dwattr $C$DW$T$122, DW_AT_address_class(0x16)
$C$DW$T$124	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$124, DW_AT_type(*$C$DW$T$127)
	.dwattr $C$DW$T$124, DW_AT_address_class(0x16)

$C$DW$T$125	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$125, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$T$125, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$634	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$634, DW_AT_type(*$C$DW$T$122)
	.dwendtag $C$DW$T$125


$C$DW$T$126	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$126, DW_AT_type(*$C$DW$T$124)
	.dwattr $C$DW$T$126, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$635	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$635, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$126


$C$DW$T$134	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$134, DW_AT_name("iq19")
	.dwattr $C$DW$T$134, DW_AT_byte_size(0x02)
$C$DW$636	.dwtag  DW_TAG_member
	.dwattr $C$DW$636, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$636, DW_AT_name("val")
	.dwattr $C$DW$636, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$636, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$636, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$636, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$636, DW_AT_decl_line(0x183)
	.dwattr $C$DW$636, DW_AT_decl_column(0x0a)

$C$DW$139	.dwtag  DW_TAG_subprogram, DW_AT_name("iq19")
	.dwattr $C$DW$139, DW_AT_declaration
	.dwattr $C$DW$139, DW_AT_TI_symbol_name("___ct__4iq19Fv")
	.dwattr $C$DW$139, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$140	.dwtag  DW_TAG_subprogram, DW_AT_name("iq19")
	.dwattr $C$DW$140, DW_AT_declaration
	.dwattr $C$DW$140, DW_AT_TI_symbol_name("___ct__4iq19Fl")
	.dwattr $C$DW$140, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$637	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$637, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$140


$C$DW$141	.dwtag  DW_TAG_subprogram, DW_AT_name("iq19")
	.dwattr $C$DW$141, DW_AT_declaration
	.dwattr $C$DW$141, DW_AT_TI_symbol_name("___ct__4iq19FRC4iq19")
	.dwattr $C$DW$141, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$638	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$638, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$141


$C$DW$142	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$142, DW_AT_declaration
	.dwattr $C$DW$142, DW_AT_TI_symbol_name("___as__4iq19FRC4iq19")
	.dwattr $C$DW$142, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$142, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$639	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$639, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$142


$C$DW$143	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$143, DW_AT_declaration
	.dwattr $C$DW$143, DW_AT_TI_symbol_name("___apl__4iq19FRC4iq19")
	.dwattr $C$DW$143, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$143, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$640	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$640, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$143


$C$DW$144	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$144, DW_AT_declaration
	.dwattr $C$DW$144, DW_AT_TI_symbol_name("___ami__4iq19FRC4iq19")
	.dwattr $C$DW$144, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$144, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$641	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$641, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$144


$C$DW$145	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$145, DW_AT_declaration
	.dwattr $C$DW$145, DW_AT_TI_symbol_name("___amu__4iq19FRC4iq19")
	.dwattr $C$DW$145, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$145, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$642	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$642, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$145


$C$DW$146	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$146, DW_AT_declaration
	.dwattr $C$DW$146, DW_AT_TI_symbol_name("___adv__4iq19FRC4iq19")
	.dwattr $C$DW$146, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$146, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$643	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$643, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$146


$C$DW$147	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$147, DW_AT_declaration
	.dwattr $C$DW$147, DW_AT_TI_symbol_name("___aad__4iq19FRCl")
	.dwattr $C$DW$147, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$147, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$644	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$644, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$147


$C$DW$148	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$148, DW_AT_declaration
	.dwattr $C$DW$148, DW_AT_TI_symbol_name("___aor__4iq19FRCl")
	.dwattr $C$DW$148, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$148, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$645	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$645, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$148


$C$DW$149	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$149, DW_AT_declaration
	.dwattr $C$DW$149, DW_AT_TI_symbol_name("___aer__4iq19FRCl")
	.dwattr $C$DW$149, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$149, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$646	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$646, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$149

	.dwendtag $C$DW$T$134

	.dwattr $C$DW$T$134, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$134, DW_AT_decl_line(0x16d)
	.dwattr $C$DW$T$134, DW_AT_decl_column(0x08)
$C$DW$647	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$647, DW_AT_type(*$C$DW$T$134)
$C$DW$T$128	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$128, DW_AT_type(*$C$DW$647)
$C$DW$T$129	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$129, DW_AT_type(*$C$DW$T$128)
	.dwattr $C$DW$T$129, DW_AT_address_class(0x16)
$C$DW$T$131	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$131, DW_AT_type(*$C$DW$T$134)
	.dwattr $C$DW$T$131, DW_AT_address_class(0x16)

$C$DW$T$132	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$132, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$T$132, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$648	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$648, DW_AT_type(*$C$DW$T$129)
	.dwendtag $C$DW$T$132


$C$DW$T$133	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$133, DW_AT_type(*$C$DW$T$131)
	.dwattr $C$DW$T$133, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$649	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$649, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$133


$C$DW$T$141	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$141, DW_AT_name("iq18")
	.dwattr $C$DW$T$141, DW_AT_byte_size(0x02)
$C$DW$650	.dwtag  DW_TAG_member
	.dwattr $C$DW$650, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$650, DW_AT_name("val")
	.dwattr $C$DW$650, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$650, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$650, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$650, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$650, DW_AT_decl_line(0x19c)
	.dwattr $C$DW$650, DW_AT_decl_column(0x0a)

$C$DW$150	.dwtag  DW_TAG_subprogram, DW_AT_name("iq18")
	.dwattr $C$DW$150, DW_AT_declaration
	.dwattr $C$DW$150, DW_AT_TI_symbol_name("___ct__4iq18Fv")
	.dwattr $C$DW$150, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$151	.dwtag  DW_TAG_subprogram, DW_AT_name("iq18")
	.dwattr $C$DW$151, DW_AT_declaration
	.dwattr $C$DW$151, DW_AT_TI_symbol_name("___ct__4iq18Fl")
	.dwattr $C$DW$151, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$651	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$651, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$151


$C$DW$152	.dwtag  DW_TAG_subprogram, DW_AT_name("iq18")
	.dwattr $C$DW$152, DW_AT_declaration
	.dwattr $C$DW$152, DW_AT_TI_symbol_name("___ct__4iq18FRC4iq18")
	.dwattr $C$DW$152, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$652	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$652, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$152


$C$DW$153	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$153, DW_AT_declaration
	.dwattr $C$DW$153, DW_AT_TI_symbol_name("___as__4iq18FRC4iq18")
	.dwattr $C$DW$153, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$153, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$653	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$653, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$153


$C$DW$154	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$154, DW_AT_declaration
	.dwattr $C$DW$154, DW_AT_TI_symbol_name("___apl__4iq18FRC4iq18")
	.dwattr $C$DW$154, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$154, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$654	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$654, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$154


$C$DW$155	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$155, DW_AT_declaration
	.dwattr $C$DW$155, DW_AT_TI_symbol_name("___ami__4iq18FRC4iq18")
	.dwattr $C$DW$155, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$155, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$655	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$655, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$155


$C$DW$156	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$156, DW_AT_declaration
	.dwattr $C$DW$156, DW_AT_TI_symbol_name("___amu__4iq18FRC4iq18")
	.dwattr $C$DW$156, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$156, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$656	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$656, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$156


$C$DW$157	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$157, DW_AT_declaration
	.dwattr $C$DW$157, DW_AT_TI_symbol_name("___adv__4iq18FRC4iq18")
	.dwattr $C$DW$157, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$157, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$657	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$657, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$157


$C$DW$158	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$158, DW_AT_declaration
	.dwattr $C$DW$158, DW_AT_TI_symbol_name("___aad__4iq18FRCl")
	.dwattr $C$DW$158, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$158, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$658	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$658, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$158


$C$DW$159	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$159, DW_AT_declaration
	.dwattr $C$DW$159, DW_AT_TI_symbol_name("___aor__4iq18FRCl")
	.dwattr $C$DW$159, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$159, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$659	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$659, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$159


$C$DW$160	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$160, DW_AT_declaration
	.dwattr $C$DW$160, DW_AT_TI_symbol_name("___aer__4iq18FRCl")
	.dwattr $C$DW$160, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$160, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$660	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$660, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$160

	.dwendtag $C$DW$T$141

	.dwattr $C$DW$T$141, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$141, DW_AT_decl_line(0x186)
	.dwattr $C$DW$T$141, DW_AT_decl_column(0x08)
$C$DW$661	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$661, DW_AT_type(*$C$DW$T$141)
$C$DW$T$135	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$135, DW_AT_type(*$C$DW$661)
$C$DW$T$136	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$136, DW_AT_type(*$C$DW$T$135)
	.dwattr $C$DW$T$136, DW_AT_address_class(0x16)
$C$DW$T$138	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$138, DW_AT_type(*$C$DW$T$141)
	.dwattr $C$DW$T$138, DW_AT_address_class(0x16)

$C$DW$T$139	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$139, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$T$139, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$662	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$662, DW_AT_type(*$C$DW$T$136)
	.dwendtag $C$DW$T$139


$C$DW$T$140	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$140, DW_AT_type(*$C$DW$T$138)
	.dwattr $C$DW$T$140, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$663	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$663, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$140


$C$DW$T$148	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$148, DW_AT_name("iq17")
	.dwattr $C$DW$T$148, DW_AT_byte_size(0x02)
$C$DW$664	.dwtag  DW_TAG_member
	.dwattr $C$DW$664, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$664, DW_AT_name("val")
	.dwattr $C$DW$664, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$664, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$664, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$664, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$664, DW_AT_decl_line(0x1b5)
	.dwattr $C$DW$664, DW_AT_decl_column(0x0a)

$C$DW$161	.dwtag  DW_TAG_subprogram, DW_AT_name("iq17")
	.dwattr $C$DW$161, DW_AT_declaration
	.dwattr $C$DW$161, DW_AT_TI_symbol_name("___ct__4iq17Fv")
	.dwattr $C$DW$161, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$162	.dwtag  DW_TAG_subprogram, DW_AT_name("iq17")
	.dwattr $C$DW$162, DW_AT_declaration
	.dwattr $C$DW$162, DW_AT_TI_symbol_name("___ct__4iq17Fl")
	.dwattr $C$DW$162, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$665	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$665, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$162


$C$DW$163	.dwtag  DW_TAG_subprogram, DW_AT_name("iq17")
	.dwattr $C$DW$163, DW_AT_declaration
	.dwattr $C$DW$163, DW_AT_TI_symbol_name("___ct__4iq17FRC4iq17")
	.dwattr $C$DW$163, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$666	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$666, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$163


$C$DW$164	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$164, DW_AT_declaration
	.dwattr $C$DW$164, DW_AT_TI_symbol_name("___as__4iq17FRC4iq17")
	.dwattr $C$DW$164, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$164, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$667	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$667, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$164


$C$DW$165	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$165, DW_AT_declaration
	.dwattr $C$DW$165, DW_AT_TI_symbol_name("___apl__4iq17FRC4iq17")
	.dwattr $C$DW$165, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$165, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$668	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$668, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$165


$C$DW$166	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$166, DW_AT_declaration
	.dwattr $C$DW$166, DW_AT_TI_symbol_name("___ami__4iq17FRC4iq17")
	.dwattr $C$DW$166, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$166, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$669	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$669, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$166


$C$DW$167	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$167, DW_AT_declaration
	.dwattr $C$DW$167, DW_AT_TI_symbol_name("___amu__4iq17FRC4iq17")
	.dwattr $C$DW$167, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$167, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$670	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$670, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$167


$C$DW$168	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$168, DW_AT_declaration
	.dwattr $C$DW$168, DW_AT_TI_symbol_name("___adv__4iq17FRC4iq17")
	.dwattr $C$DW$168, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$168, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$671	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$671, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$168


$C$DW$169	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$169, DW_AT_declaration
	.dwattr $C$DW$169, DW_AT_TI_symbol_name("___aad__4iq17FRCl")
	.dwattr $C$DW$169, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$169, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$672	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$672, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$169


$C$DW$170	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$170, DW_AT_declaration
	.dwattr $C$DW$170, DW_AT_TI_symbol_name("___aor__4iq17FRCl")
	.dwattr $C$DW$170, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$170, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$673	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$673, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$170


$C$DW$171	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$171, DW_AT_declaration
	.dwattr $C$DW$171, DW_AT_TI_symbol_name("___aer__4iq17FRCl")
	.dwattr $C$DW$171, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$171, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$674	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$674, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$171

	.dwendtag $C$DW$T$148

	.dwattr $C$DW$T$148, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$148, DW_AT_decl_line(0x19f)
	.dwattr $C$DW$T$148, DW_AT_decl_column(0x08)
$C$DW$675	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$675, DW_AT_type(*$C$DW$T$148)
$C$DW$T$142	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$142, DW_AT_type(*$C$DW$675)
$C$DW$T$143	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$143, DW_AT_type(*$C$DW$T$142)
	.dwattr $C$DW$T$143, DW_AT_address_class(0x16)
$C$DW$T$145	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$145, DW_AT_type(*$C$DW$T$148)
	.dwattr $C$DW$T$145, DW_AT_address_class(0x16)

$C$DW$T$146	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$146, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$T$146, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$676	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$676, DW_AT_type(*$C$DW$T$143)
	.dwendtag $C$DW$T$146


$C$DW$T$147	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$147, DW_AT_type(*$C$DW$T$145)
	.dwattr $C$DW$T$147, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$677	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$677, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$147


$C$DW$T$155	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$155, DW_AT_name("iq16")
	.dwattr $C$DW$T$155, DW_AT_byte_size(0x02)
$C$DW$678	.dwtag  DW_TAG_member
	.dwattr $C$DW$678, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$678, DW_AT_name("val")
	.dwattr $C$DW$678, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$678, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$678, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$678, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$678, DW_AT_decl_line(0x1ce)
	.dwattr $C$DW$678, DW_AT_decl_column(0x0a)

$C$DW$172	.dwtag  DW_TAG_subprogram, DW_AT_name("iq16")
	.dwattr $C$DW$172, DW_AT_declaration
	.dwattr $C$DW$172, DW_AT_TI_symbol_name("___ct__4iq16Fv")
	.dwattr $C$DW$172, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$173	.dwtag  DW_TAG_subprogram, DW_AT_name("iq16")
	.dwattr $C$DW$173, DW_AT_declaration
	.dwattr $C$DW$173, DW_AT_TI_symbol_name("___ct__4iq16Fl")
	.dwattr $C$DW$173, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$679	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$679, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$173


$C$DW$174	.dwtag  DW_TAG_subprogram, DW_AT_name("iq16")
	.dwattr $C$DW$174, DW_AT_declaration
	.dwattr $C$DW$174, DW_AT_TI_symbol_name("___ct__4iq16FRC4iq16")
	.dwattr $C$DW$174, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$680	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$680, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$174


$C$DW$175	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$175, DW_AT_declaration
	.dwattr $C$DW$175, DW_AT_TI_symbol_name("___as__4iq16FRC4iq16")
	.dwattr $C$DW$175, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$175, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$681	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$681, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$175


$C$DW$176	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$176, DW_AT_declaration
	.dwattr $C$DW$176, DW_AT_TI_symbol_name("___apl__4iq16FRC4iq16")
	.dwattr $C$DW$176, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$176, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$682	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$682, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$176


$C$DW$177	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$177, DW_AT_declaration
	.dwattr $C$DW$177, DW_AT_TI_symbol_name("___ami__4iq16FRC4iq16")
	.dwattr $C$DW$177, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$177, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$683	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$683, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$177


$C$DW$178	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$178, DW_AT_declaration
	.dwattr $C$DW$178, DW_AT_TI_symbol_name("___amu__4iq16FRC4iq16")
	.dwattr $C$DW$178, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$178, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$684	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$684, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$178


$C$DW$179	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$179, DW_AT_declaration
	.dwattr $C$DW$179, DW_AT_TI_symbol_name("___adv__4iq16FRC4iq16")
	.dwattr $C$DW$179, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$179, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$685	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$685, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$179


$C$DW$180	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$180, DW_AT_declaration
	.dwattr $C$DW$180, DW_AT_TI_symbol_name("___aad__4iq16FRCl")
	.dwattr $C$DW$180, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$180, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$686	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$686, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$180


$C$DW$181	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$181, DW_AT_declaration
	.dwattr $C$DW$181, DW_AT_TI_symbol_name("___aor__4iq16FRCl")
	.dwattr $C$DW$181, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$181, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$687	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$687, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$181


$C$DW$182	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$182, DW_AT_declaration
	.dwattr $C$DW$182, DW_AT_TI_symbol_name("___aer__4iq16FRCl")
	.dwattr $C$DW$182, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$182, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$688	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$688, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$182

	.dwendtag $C$DW$T$155

	.dwattr $C$DW$T$155, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$155, DW_AT_decl_line(0x1b8)
	.dwattr $C$DW$T$155, DW_AT_decl_column(0x08)
$C$DW$689	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$689, DW_AT_type(*$C$DW$T$155)
$C$DW$T$149	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$149, DW_AT_type(*$C$DW$689)
$C$DW$T$150	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$150, DW_AT_type(*$C$DW$T$149)
	.dwattr $C$DW$T$150, DW_AT_address_class(0x16)
$C$DW$T$152	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$152, DW_AT_type(*$C$DW$T$155)
	.dwattr $C$DW$T$152, DW_AT_address_class(0x16)

$C$DW$T$153	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$153, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$T$153, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$690	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$690, DW_AT_type(*$C$DW$T$150)
	.dwendtag $C$DW$T$153


$C$DW$T$154	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$154, DW_AT_type(*$C$DW$T$152)
	.dwattr $C$DW$T$154, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$691	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$691, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$154


$C$DW$T$162	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$162, DW_AT_name("iq15")
	.dwattr $C$DW$T$162, DW_AT_byte_size(0x02)
$C$DW$692	.dwtag  DW_TAG_member
	.dwattr $C$DW$692, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$692, DW_AT_name("val")
	.dwattr $C$DW$692, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$692, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$692, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$692, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$692, DW_AT_decl_line(0x1e7)
	.dwattr $C$DW$692, DW_AT_decl_column(0x0a)

$C$DW$183	.dwtag  DW_TAG_subprogram, DW_AT_name("iq15")
	.dwattr $C$DW$183, DW_AT_declaration
	.dwattr $C$DW$183, DW_AT_TI_symbol_name("___ct__4iq15Fv")
	.dwattr $C$DW$183, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$184	.dwtag  DW_TAG_subprogram, DW_AT_name("iq15")
	.dwattr $C$DW$184, DW_AT_declaration
	.dwattr $C$DW$184, DW_AT_TI_symbol_name("___ct__4iq15Fl")
	.dwattr $C$DW$184, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$693	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$693, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$184


$C$DW$185	.dwtag  DW_TAG_subprogram, DW_AT_name("iq15")
	.dwattr $C$DW$185, DW_AT_declaration
	.dwattr $C$DW$185, DW_AT_TI_symbol_name("___ct__4iq15FRC4iq15")
	.dwattr $C$DW$185, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$694	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$694, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$185


$C$DW$186	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$186, DW_AT_declaration
	.dwattr $C$DW$186, DW_AT_TI_symbol_name("___as__4iq15FRC4iq15")
	.dwattr $C$DW$186, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$186, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$695	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$695, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$186


$C$DW$187	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$187, DW_AT_declaration
	.dwattr $C$DW$187, DW_AT_TI_symbol_name("___apl__4iq15FRC4iq15")
	.dwattr $C$DW$187, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$187, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$696	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$696, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$187


$C$DW$188	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$188, DW_AT_declaration
	.dwattr $C$DW$188, DW_AT_TI_symbol_name("___ami__4iq15FRC4iq15")
	.dwattr $C$DW$188, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$188, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$697	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$697, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$188


$C$DW$189	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$189, DW_AT_declaration
	.dwattr $C$DW$189, DW_AT_TI_symbol_name("___amu__4iq15FRC4iq15")
	.dwattr $C$DW$189, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$189, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$698	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$698, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$189


$C$DW$190	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$190, DW_AT_declaration
	.dwattr $C$DW$190, DW_AT_TI_symbol_name("___adv__4iq15FRC4iq15")
	.dwattr $C$DW$190, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$190, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$699	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$699, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$190


$C$DW$191	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$191, DW_AT_declaration
	.dwattr $C$DW$191, DW_AT_TI_symbol_name("___aad__4iq15FRCl")
	.dwattr $C$DW$191, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$191, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$700	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$700, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$191


$C$DW$192	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$192, DW_AT_declaration
	.dwattr $C$DW$192, DW_AT_TI_symbol_name("___aor__4iq15FRCl")
	.dwattr $C$DW$192, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$192, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$701	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$701, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$192


$C$DW$193	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$193, DW_AT_declaration
	.dwattr $C$DW$193, DW_AT_TI_symbol_name("___aer__4iq15FRCl")
	.dwattr $C$DW$193, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$193, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$702	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$702, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$193

	.dwendtag $C$DW$T$162

	.dwattr $C$DW$T$162, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$162, DW_AT_decl_line(0x1d1)
	.dwattr $C$DW$T$162, DW_AT_decl_column(0x08)
$C$DW$703	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$703, DW_AT_type(*$C$DW$T$162)
$C$DW$T$156	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$156, DW_AT_type(*$C$DW$703)
$C$DW$T$157	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$157, DW_AT_type(*$C$DW$T$156)
	.dwattr $C$DW$T$157, DW_AT_address_class(0x16)
$C$DW$T$159	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$159, DW_AT_type(*$C$DW$T$162)
	.dwattr $C$DW$T$159, DW_AT_address_class(0x16)

$C$DW$T$160	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$160, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$T$160, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$704	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$704, DW_AT_type(*$C$DW$T$157)
	.dwendtag $C$DW$T$160


$C$DW$T$161	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$161, DW_AT_type(*$C$DW$T$159)
	.dwattr $C$DW$T$161, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$705	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$705, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$161


$C$DW$T$169	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$169, DW_AT_name("iq14")
	.dwattr $C$DW$T$169, DW_AT_byte_size(0x02)
$C$DW$706	.dwtag  DW_TAG_member
	.dwattr $C$DW$706, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$706, DW_AT_name("val")
	.dwattr $C$DW$706, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$706, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$706, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$706, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$706, DW_AT_decl_line(0x200)
	.dwattr $C$DW$706, DW_AT_decl_column(0x0a)

$C$DW$194	.dwtag  DW_TAG_subprogram, DW_AT_name("iq14")
	.dwattr $C$DW$194, DW_AT_declaration
	.dwattr $C$DW$194, DW_AT_TI_symbol_name("___ct__4iq14Fv")
	.dwattr $C$DW$194, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$195	.dwtag  DW_TAG_subprogram, DW_AT_name("iq14")
	.dwattr $C$DW$195, DW_AT_declaration
	.dwattr $C$DW$195, DW_AT_TI_symbol_name("___ct__4iq14Fl")
	.dwattr $C$DW$195, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$707	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$707, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$195


$C$DW$196	.dwtag  DW_TAG_subprogram, DW_AT_name("iq14")
	.dwattr $C$DW$196, DW_AT_declaration
	.dwattr $C$DW$196, DW_AT_TI_symbol_name("___ct__4iq14FRC4iq14")
	.dwattr $C$DW$196, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$708	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$708, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$196


$C$DW$197	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$197, DW_AT_declaration
	.dwattr $C$DW$197, DW_AT_TI_symbol_name("___as__4iq14FRC4iq14")
	.dwattr $C$DW$197, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$197, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$709	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$709, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$197


$C$DW$198	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$198, DW_AT_declaration
	.dwattr $C$DW$198, DW_AT_TI_symbol_name("___apl__4iq14FRC4iq14")
	.dwattr $C$DW$198, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$198, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$710	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$710, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$198


$C$DW$199	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$199, DW_AT_declaration
	.dwattr $C$DW$199, DW_AT_TI_symbol_name("___ami__4iq14FRC4iq14")
	.dwattr $C$DW$199, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$199, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$711	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$711, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$199


$C$DW$200	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$200, DW_AT_declaration
	.dwattr $C$DW$200, DW_AT_TI_symbol_name("___amu__4iq14FRC4iq14")
	.dwattr $C$DW$200, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$200, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$712	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$712, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$200


$C$DW$201	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$201, DW_AT_declaration
	.dwattr $C$DW$201, DW_AT_TI_symbol_name("___adv__4iq14FRC4iq14")
	.dwattr $C$DW$201, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$201, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$713	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$713, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$201


$C$DW$202	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$202, DW_AT_declaration
	.dwattr $C$DW$202, DW_AT_TI_symbol_name("___aad__4iq14FRCl")
	.dwattr $C$DW$202, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$202, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$714	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$714, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$202


$C$DW$203	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$203, DW_AT_declaration
	.dwattr $C$DW$203, DW_AT_TI_symbol_name("___aor__4iq14FRCl")
	.dwattr $C$DW$203, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$203, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$715	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$715, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$203


$C$DW$204	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$204, DW_AT_declaration
	.dwattr $C$DW$204, DW_AT_TI_symbol_name("___aer__4iq14FRCl")
	.dwattr $C$DW$204, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$204, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$716	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$716, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$204

	.dwendtag $C$DW$T$169

	.dwattr $C$DW$T$169, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$169, DW_AT_decl_line(0x1ea)
	.dwattr $C$DW$T$169, DW_AT_decl_column(0x08)
$C$DW$717	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$717, DW_AT_type(*$C$DW$T$169)
$C$DW$T$163	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$163, DW_AT_type(*$C$DW$717)
$C$DW$T$164	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$164, DW_AT_type(*$C$DW$T$163)
	.dwattr $C$DW$T$164, DW_AT_address_class(0x16)
$C$DW$T$166	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$166, DW_AT_type(*$C$DW$T$169)
	.dwattr $C$DW$T$166, DW_AT_address_class(0x16)

$C$DW$T$167	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$167, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$T$167, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$718	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$718, DW_AT_type(*$C$DW$T$164)
	.dwendtag $C$DW$T$167


$C$DW$T$168	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$168, DW_AT_type(*$C$DW$T$166)
	.dwattr $C$DW$T$168, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$719	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$719, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$168


$C$DW$T$176	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$176, DW_AT_name("iq13")
	.dwattr $C$DW$T$176, DW_AT_byte_size(0x02)
$C$DW$720	.dwtag  DW_TAG_member
	.dwattr $C$DW$720, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$720, DW_AT_name("val")
	.dwattr $C$DW$720, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$720, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$720, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$720, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$720, DW_AT_decl_line(0x219)
	.dwattr $C$DW$720, DW_AT_decl_column(0x0a)

$C$DW$205	.dwtag  DW_TAG_subprogram, DW_AT_name("iq13")
	.dwattr $C$DW$205, DW_AT_declaration
	.dwattr $C$DW$205, DW_AT_TI_symbol_name("___ct__4iq13Fv")
	.dwattr $C$DW$205, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$206	.dwtag  DW_TAG_subprogram, DW_AT_name("iq13")
	.dwattr $C$DW$206, DW_AT_declaration
	.dwattr $C$DW$206, DW_AT_TI_symbol_name("___ct__4iq13Fl")
	.dwattr $C$DW$206, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$721	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$721, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$206


$C$DW$207	.dwtag  DW_TAG_subprogram, DW_AT_name("iq13")
	.dwattr $C$DW$207, DW_AT_declaration
	.dwattr $C$DW$207, DW_AT_TI_symbol_name("___ct__4iq13FRC4iq13")
	.dwattr $C$DW$207, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$722	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$722, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$207


$C$DW$208	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$208, DW_AT_declaration
	.dwattr $C$DW$208, DW_AT_TI_symbol_name("___as__4iq13FRC4iq13")
	.dwattr $C$DW$208, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$208, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$723	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$723, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$208


$C$DW$209	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$209, DW_AT_declaration
	.dwattr $C$DW$209, DW_AT_TI_symbol_name("___apl__4iq13FRC4iq13")
	.dwattr $C$DW$209, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$209, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$724	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$724, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$209


$C$DW$210	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$210, DW_AT_declaration
	.dwattr $C$DW$210, DW_AT_TI_symbol_name("___ami__4iq13FRC4iq13")
	.dwattr $C$DW$210, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$210, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$725	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$725, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$210


$C$DW$211	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$211, DW_AT_declaration
	.dwattr $C$DW$211, DW_AT_TI_symbol_name("___amu__4iq13FRC4iq13")
	.dwattr $C$DW$211, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$211, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$726	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$726, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$211


$C$DW$212	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$212, DW_AT_declaration
	.dwattr $C$DW$212, DW_AT_TI_symbol_name("___adv__4iq13FRC4iq13")
	.dwattr $C$DW$212, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$212, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$727	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$727, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$212


$C$DW$213	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$213, DW_AT_declaration
	.dwattr $C$DW$213, DW_AT_TI_symbol_name("___aad__4iq13FRCl")
	.dwattr $C$DW$213, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$213, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$728	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$728, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$213


$C$DW$214	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$214, DW_AT_declaration
	.dwattr $C$DW$214, DW_AT_TI_symbol_name("___aor__4iq13FRCl")
	.dwattr $C$DW$214, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$214, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$729	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$729, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$214


$C$DW$215	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$215, DW_AT_declaration
	.dwattr $C$DW$215, DW_AT_TI_symbol_name("___aer__4iq13FRCl")
	.dwattr $C$DW$215, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$215, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$730	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$730, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$215

	.dwendtag $C$DW$T$176

	.dwattr $C$DW$T$176, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$176, DW_AT_decl_line(0x203)
	.dwattr $C$DW$T$176, DW_AT_decl_column(0x08)
$C$DW$731	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$731, DW_AT_type(*$C$DW$T$176)
$C$DW$T$170	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$170, DW_AT_type(*$C$DW$731)
$C$DW$T$171	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$171, DW_AT_type(*$C$DW$T$170)
	.dwattr $C$DW$T$171, DW_AT_address_class(0x16)
$C$DW$T$173	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$173, DW_AT_type(*$C$DW$T$176)
	.dwattr $C$DW$T$173, DW_AT_address_class(0x16)

$C$DW$T$174	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$174, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$T$174, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$732	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$732, DW_AT_type(*$C$DW$T$171)
	.dwendtag $C$DW$T$174


$C$DW$T$175	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$175, DW_AT_type(*$C$DW$T$173)
	.dwattr $C$DW$T$175, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$733	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$733, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$175


$C$DW$T$183	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$183, DW_AT_name("iq12")
	.dwattr $C$DW$T$183, DW_AT_byte_size(0x02)
$C$DW$734	.dwtag  DW_TAG_member
	.dwattr $C$DW$734, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$734, DW_AT_name("val")
	.dwattr $C$DW$734, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$734, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$734, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$734, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$734, DW_AT_decl_line(0x232)
	.dwattr $C$DW$734, DW_AT_decl_column(0x0a)

$C$DW$216	.dwtag  DW_TAG_subprogram, DW_AT_name("iq12")
	.dwattr $C$DW$216, DW_AT_declaration
	.dwattr $C$DW$216, DW_AT_TI_symbol_name("___ct__4iq12Fv")
	.dwattr $C$DW$216, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$217	.dwtag  DW_TAG_subprogram, DW_AT_name("iq12")
	.dwattr $C$DW$217, DW_AT_declaration
	.dwattr $C$DW$217, DW_AT_TI_symbol_name("___ct__4iq12Fl")
	.dwattr $C$DW$217, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$735	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$735, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$217


$C$DW$218	.dwtag  DW_TAG_subprogram, DW_AT_name("iq12")
	.dwattr $C$DW$218, DW_AT_declaration
	.dwattr $C$DW$218, DW_AT_TI_symbol_name("___ct__4iq12FRC4iq12")
	.dwattr $C$DW$218, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$736	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$736, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$218


$C$DW$219	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$219, DW_AT_declaration
	.dwattr $C$DW$219, DW_AT_TI_symbol_name("___as__4iq12FRC4iq12")
	.dwattr $C$DW$219, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$219, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$737	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$737, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$219


$C$DW$220	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$220, DW_AT_declaration
	.dwattr $C$DW$220, DW_AT_TI_symbol_name("___apl__4iq12FRC4iq12")
	.dwattr $C$DW$220, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$220, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$738	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$738, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$220


$C$DW$221	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$221, DW_AT_declaration
	.dwattr $C$DW$221, DW_AT_TI_symbol_name("___ami__4iq12FRC4iq12")
	.dwattr $C$DW$221, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$221, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$739	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$739, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$221


$C$DW$222	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$222, DW_AT_declaration
	.dwattr $C$DW$222, DW_AT_TI_symbol_name("___amu__4iq12FRC4iq12")
	.dwattr $C$DW$222, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$222, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$740	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$740, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$222


$C$DW$223	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$223, DW_AT_declaration
	.dwattr $C$DW$223, DW_AT_TI_symbol_name("___adv__4iq12FRC4iq12")
	.dwattr $C$DW$223, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$223, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$741	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$741, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$223


$C$DW$224	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$224, DW_AT_declaration
	.dwattr $C$DW$224, DW_AT_TI_symbol_name("___aad__4iq12FRCl")
	.dwattr $C$DW$224, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$224, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$742	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$742, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$224


$C$DW$225	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$225, DW_AT_declaration
	.dwattr $C$DW$225, DW_AT_TI_symbol_name("___aor__4iq12FRCl")
	.dwattr $C$DW$225, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$225, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$743	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$743, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$225


$C$DW$226	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$226, DW_AT_declaration
	.dwattr $C$DW$226, DW_AT_TI_symbol_name("___aer__4iq12FRCl")
	.dwattr $C$DW$226, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$226, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$744	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$744, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$226

	.dwendtag $C$DW$T$183

	.dwattr $C$DW$T$183, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$183, DW_AT_decl_line(0x21c)
	.dwattr $C$DW$T$183, DW_AT_decl_column(0x08)
$C$DW$745	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$745, DW_AT_type(*$C$DW$T$183)
$C$DW$T$177	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$177, DW_AT_type(*$C$DW$745)
$C$DW$T$178	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$178, DW_AT_type(*$C$DW$T$177)
	.dwattr $C$DW$T$178, DW_AT_address_class(0x16)
$C$DW$T$180	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$180, DW_AT_type(*$C$DW$T$183)
	.dwattr $C$DW$T$180, DW_AT_address_class(0x16)

$C$DW$T$181	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$181, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$T$181, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$746	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$746, DW_AT_type(*$C$DW$T$178)
	.dwendtag $C$DW$T$181


$C$DW$T$182	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$182, DW_AT_type(*$C$DW$T$180)
	.dwattr $C$DW$T$182, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$747	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$747, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$182


$C$DW$T$190	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$190, DW_AT_name("iq11")
	.dwattr $C$DW$T$190, DW_AT_byte_size(0x02)
$C$DW$748	.dwtag  DW_TAG_member
	.dwattr $C$DW$748, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$748, DW_AT_name("val")
	.dwattr $C$DW$748, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$748, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$748, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$748, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$748, DW_AT_decl_line(0x24b)
	.dwattr $C$DW$748, DW_AT_decl_column(0x0a)

$C$DW$227	.dwtag  DW_TAG_subprogram, DW_AT_name("iq11")
	.dwattr $C$DW$227, DW_AT_declaration
	.dwattr $C$DW$227, DW_AT_TI_symbol_name("___ct__4iq11Fv")
	.dwattr $C$DW$227, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$228	.dwtag  DW_TAG_subprogram, DW_AT_name("iq11")
	.dwattr $C$DW$228, DW_AT_declaration
	.dwattr $C$DW$228, DW_AT_TI_symbol_name("___ct__4iq11Fl")
	.dwattr $C$DW$228, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$749	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$749, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$228


$C$DW$229	.dwtag  DW_TAG_subprogram, DW_AT_name("iq11")
	.dwattr $C$DW$229, DW_AT_declaration
	.dwattr $C$DW$229, DW_AT_TI_symbol_name("___ct__4iq11FRC4iq11")
	.dwattr $C$DW$229, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$750	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$750, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$229


$C$DW$230	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$230, DW_AT_declaration
	.dwattr $C$DW$230, DW_AT_TI_symbol_name("___as__4iq11FRC4iq11")
	.dwattr $C$DW$230, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$230, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$751	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$751, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$230


$C$DW$231	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$231, DW_AT_declaration
	.dwattr $C$DW$231, DW_AT_TI_symbol_name("___apl__4iq11FRC4iq11")
	.dwattr $C$DW$231, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$231, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$752	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$752, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$231


$C$DW$232	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$232, DW_AT_declaration
	.dwattr $C$DW$232, DW_AT_TI_symbol_name("___ami__4iq11FRC4iq11")
	.dwattr $C$DW$232, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$232, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$753	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$753, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$232


$C$DW$233	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$233, DW_AT_declaration
	.dwattr $C$DW$233, DW_AT_TI_symbol_name("___amu__4iq11FRC4iq11")
	.dwattr $C$DW$233, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$233, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$754	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$754, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$233


$C$DW$234	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$234, DW_AT_declaration
	.dwattr $C$DW$234, DW_AT_TI_symbol_name("___adv__4iq11FRC4iq11")
	.dwattr $C$DW$234, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$234, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$755	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$755, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$234


$C$DW$235	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$235, DW_AT_declaration
	.dwattr $C$DW$235, DW_AT_TI_symbol_name("___aad__4iq11FRCl")
	.dwattr $C$DW$235, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$235, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$756	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$756, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$235


$C$DW$236	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$236, DW_AT_declaration
	.dwattr $C$DW$236, DW_AT_TI_symbol_name("___aor__4iq11FRCl")
	.dwattr $C$DW$236, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$236, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$757	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$757, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$236


$C$DW$237	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$237, DW_AT_declaration
	.dwattr $C$DW$237, DW_AT_TI_symbol_name("___aer__4iq11FRCl")
	.dwattr $C$DW$237, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$237, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$758	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$758, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$237

	.dwendtag $C$DW$T$190

	.dwattr $C$DW$T$190, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$190, DW_AT_decl_line(0x235)
	.dwattr $C$DW$T$190, DW_AT_decl_column(0x08)
$C$DW$759	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$759, DW_AT_type(*$C$DW$T$190)
$C$DW$T$184	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$184, DW_AT_type(*$C$DW$759)
$C$DW$T$185	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$185, DW_AT_type(*$C$DW$T$184)
	.dwattr $C$DW$T$185, DW_AT_address_class(0x16)
$C$DW$T$187	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$187, DW_AT_type(*$C$DW$T$190)
	.dwattr $C$DW$T$187, DW_AT_address_class(0x16)

$C$DW$T$188	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$188, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$T$188, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$760	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$760, DW_AT_type(*$C$DW$T$185)
	.dwendtag $C$DW$T$188


$C$DW$T$189	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$189, DW_AT_type(*$C$DW$T$187)
	.dwattr $C$DW$T$189, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$761	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$761, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$189


$C$DW$T$197	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$197, DW_AT_name("iq10")
	.dwattr $C$DW$T$197, DW_AT_byte_size(0x02)
$C$DW$762	.dwtag  DW_TAG_member
	.dwattr $C$DW$762, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$762, DW_AT_name("val")
	.dwattr $C$DW$762, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$762, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$762, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$762, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$762, DW_AT_decl_line(0x264)
	.dwattr $C$DW$762, DW_AT_decl_column(0x0a)

$C$DW$238	.dwtag  DW_TAG_subprogram, DW_AT_name("iq10")
	.dwattr $C$DW$238, DW_AT_declaration
	.dwattr $C$DW$238, DW_AT_TI_symbol_name("___ct__4iq10Fv")
	.dwattr $C$DW$238, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$239	.dwtag  DW_TAG_subprogram, DW_AT_name("iq10")
	.dwattr $C$DW$239, DW_AT_declaration
	.dwattr $C$DW$239, DW_AT_TI_symbol_name("___ct__4iq10Fl")
	.dwattr $C$DW$239, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$763	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$763, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$239


$C$DW$240	.dwtag  DW_TAG_subprogram, DW_AT_name("iq10")
	.dwattr $C$DW$240, DW_AT_declaration
	.dwattr $C$DW$240, DW_AT_TI_symbol_name("___ct__4iq10FRC4iq10")
	.dwattr $C$DW$240, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$764	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$764, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$240


$C$DW$241	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$241, DW_AT_declaration
	.dwattr $C$DW$241, DW_AT_TI_symbol_name("___as__4iq10FRC4iq10")
	.dwattr $C$DW$241, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$241, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$765	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$765, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$241


$C$DW$242	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$242, DW_AT_declaration
	.dwattr $C$DW$242, DW_AT_TI_symbol_name("___apl__4iq10FRC4iq10")
	.dwattr $C$DW$242, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$242, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$766	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$766, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$242


$C$DW$243	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$243, DW_AT_declaration
	.dwattr $C$DW$243, DW_AT_TI_symbol_name("___ami__4iq10FRC4iq10")
	.dwattr $C$DW$243, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$243, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$767	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$767, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$243


$C$DW$244	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$244, DW_AT_declaration
	.dwattr $C$DW$244, DW_AT_TI_symbol_name("___amu__4iq10FRC4iq10")
	.dwattr $C$DW$244, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$244, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$768	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$768, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$244


$C$DW$245	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$245, DW_AT_declaration
	.dwattr $C$DW$245, DW_AT_TI_symbol_name("___adv__4iq10FRC4iq10")
	.dwattr $C$DW$245, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$245, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$769	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$769, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$245


$C$DW$246	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$246, DW_AT_declaration
	.dwattr $C$DW$246, DW_AT_TI_symbol_name("___aad__4iq10FRCl")
	.dwattr $C$DW$246, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$246, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$770	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$770, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$246


$C$DW$247	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$247, DW_AT_declaration
	.dwattr $C$DW$247, DW_AT_TI_symbol_name("___aor__4iq10FRCl")
	.dwattr $C$DW$247, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$247, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$771	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$771, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$247


$C$DW$248	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$248, DW_AT_declaration
	.dwattr $C$DW$248, DW_AT_TI_symbol_name("___aer__4iq10FRCl")
	.dwattr $C$DW$248, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$248, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$772	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$772, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$248

	.dwendtag $C$DW$T$197

	.dwattr $C$DW$T$197, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$197, DW_AT_decl_line(0x24e)
	.dwattr $C$DW$T$197, DW_AT_decl_column(0x08)
$C$DW$773	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$773, DW_AT_type(*$C$DW$T$197)
$C$DW$T$191	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$191, DW_AT_type(*$C$DW$773)
$C$DW$T$192	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$192, DW_AT_type(*$C$DW$T$191)
	.dwattr $C$DW$T$192, DW_AT_address_class(0x16)
$C$DW$T$194	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$194, DW_AT_type(*$C$DW$T$197)
	.dwattr $C$DW$T$194, DW_AT_address_class(0x16)

$C$DW$T$195	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$195, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$T$195, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$774	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$774, DW_AT_type(*$C$DW$T$192)
	.dwendtag $C$DW$T$195


$C$DW$T$196	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$196, DW_AT_type(*$C$DW$T$194)
	.dwattr $C$DW$T$196, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$775	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$775, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$196


$C$DW$T$204	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$204, DW_AT_name("iq9")
	.dwattr $C$DW$T$204, DW_AT_byte_size(0x02)
$C$DW$776	.dwtag  DW_TAG_member
	.dwattr $C$DW$776, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$776, DW_AT_name("val")
	.dwattr $C$DW$776, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$776, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$776, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$776, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$776, DW_AT_decl_line(0x27d)
	.dwattr $C$DW$776, DW_AT_decl_column(0x0a)

$C$DW$249	.dwtag  DW_TAG_subprogram, DW_AT_name("iq9")
	.dwattr $C$DW$249, DW_AT_declaration
	.dwattr $C$DW$249, DW_AT_TI_symbol_name("___ct__3iq9Fv")
	.dwattr $C$DW$249, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$250	.dwtag  DW_TAG_subprogram, DW_AT_name("iq9")
	.dwattr $C$DW$250, DW_AT_declaration
	.dwattr $C$DW$250, DW_AT_TI_symbol_name("___ct__3iq9Fl")
	.dwattr $C$DW$250, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$777	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$777, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$250


$C$DW$251	.dwtag  DW_TAG_subprogram, DW_AT_name("iq9")
	.dwattr $C$DW$251, DW_AT_declaration
	.dwattr $C$DW$251, DW_AT_TI_symbol_name("___ct__3iq9FRC3iq9")
	.dwattr $C$DW$251, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$778	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$778, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$251


$C$DW$252	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$252, DW_AT_declaration
	.dwattr $C$DW$252, DW_AT_TI_symbol_name("___as__3iq9FRC3iq9")
	.dwattr $C$DW$252, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$252, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$779	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$779, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$252


$C$DW$253	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$253, DW_AT_declaration
	.dwattr $C$DW$253, DW_AT_TI_symbol_name("___apl__3iq9FRC3iq9")
	.dwattr $C$DW$253, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$253, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$780	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$780, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$253


$C$DW$254	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$254, DW_AT_declaration
	.dwattr $C$DW$254, DW_AT_TI_symbol_name("___ami__3iq9FRC3iq9")
	.dwattr $C$DW$254, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$254, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$781	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$781, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$254


$C$DW$255	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$255, DW_AT_declaration
	.dwattr $C$DW$255, DW_AT_TI_symbol_name("___amu__3iq9FRC3iq9")
	.dwattr $C$DW$255, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$255, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$782	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$782, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$255


$C$DW$256	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$256, DW_AT_declaration
	.dwattr $C$DW$256, DW_AT_TI_symbol_name("___adv__3iq9FRC3iq9")
	.dwattr $C$DW$256, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$256, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$783	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$783, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$256


$C$DW$257	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$257, DW_AT_declaration
	.dwattr $C$DW$257, DW_AT_TI_symbol_name("___aad__3iq9FRCl")
	.dwattr $C$DW$257, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$257, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$784	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$784, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$257


$C$DW$258	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$258, DW_AT_declaration
	.dwattr $C$DW$258, DW_AT_TI_symbol_name("___aor__3iq9FRCl")
	.dwattr $C$DW$258, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$258, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$785	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$785, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$258


$C$DW$259	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$259, DW_AT_declaration
	.dwattr $C$DW$259, DW_AT_TI_symbol_name("___aer__3iq9FRCl")
	.dwattr $C$DW$259, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$259, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$786	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$786, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$259

	.dwendtag $C$DW$T$204

	.dwattr $C$DW$T$204, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$204, DW_AT_decl_line(0x267)
	.dwattr $C$DW$T$204, DW_AT_decl_column(0x08)
$C$DW$787	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$787, DW_AT_type(*$C$DW$T$204)
$C$DW$T$198	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$198, DW_AT_type(*$C$DW$787)
$C$DW$T$199	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$199, DW_AT_type(*$C$DW$T$198)
	.dwattr $C$DW$T$199, DW_AT_address_class(0x16)
$C$DW$T$201	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$201, DW_AT_type(*$C$DW$T$204)
	.dwattr $C$DW$T$201, DW_AT_address_class(0x16)

$C$DW$T$202	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$202, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$T$202, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$788	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$788, DW_AT_type(*$C$DW$T$199)
	.dwendtag $C$DW$T$202


$C$DW$T$203	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$203, DW_AT_type(*$C$DW$T$201)
	.dwattr $C$DW$T$203, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$789	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$789, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$203


$C$DW$T$211	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$211, DW_AT_name("iq8")
	.dwattr $C$DW$T$211, DW_AT_byte_size(0x02)
$C$DW$790	.dwtag  DW_TAG_member
	.dwattr $C$DW$790, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$790, DW_AT_name("val")
	.dwattr $C$DW$790, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$790, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$790, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$790, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$790, DW_AT_decl_line(0x296)
	.dwattr $C$DW$790, DW_AT_decl_column(0x0a)

$C$DW$260	.dwtag  DW_TAG_subprogram, DW_AT_name("iq8")
	.dwattr $C$DW$260, DW_AT_declaration
	.dwattr $C$DW$260, DW_AT_TI_symbol_name("___ct__3iq8Fv")
	.dwattr $C$DW$260, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$261	.dwtag  DW_TAG_subprogram, DW_AT_name("iq8")
	.dwattr $C$DW$261, DW_AT_declaration
	.dwattr $C$DW$261, DW_AT_TI_symbol_name("___ct__3iq8Fl")
	.dwattr $C$DW$261, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$791	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$791, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$261


$C$DW$262	.dwtag  DW_TAG_subprogram, DW_AT_name("iq8")
	.dwattr $C$DW$262, DW_AT_declaration
	.dwattr $C$DW$262, DW_AT_TI_symbol_name("___ct__3iq8FRC3iq8")
	.dwattr $C$DW$262, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$792	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$792, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$262


$C$DW$263	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$263, DW_AT_declaration
	.dwattr $C$DW$263, DW_AT_TI_symbol_name("___as__3iq8FRC3iq8")
	.dwattr $C$DW$263, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$263, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$793	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$793, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$263


$C$DW$264	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$264, DW_AT_declaration
	.dwattr $C$DW$264, DW_AT_TI_symbol_name("___apl__3iq8FRC3iq8")
	.dwattr $C$DW$264, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$264, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$794	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$794, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$264


$C$DW$265	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$265, DW_AT_declaration
	.dwattr $C$DW$265, DW_AT_TI_symbol_name("___ami__3iq8FRC3iq8")
	.dwattr $C$DW$265, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$265, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$795	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$795, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$265


$C$DW$266	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$266, DW_AT_declaration
	.dwattr $C$DW$266, DW_AT_TI_symbol_name("___amu__3iq8FRC3iq8")
	.dwattr $C$DW$266, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$266, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$796	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$796, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$266


$C$DW$267	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$267, DW_AT_declaration
	.dwattr $C$DW$267, DW_AT_TI_symbol_name("___adv__3iq8FRC3iq8")
	.dwattr $C$DW$267, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$267, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$797	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$797, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$267


$C$DW$268	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$268, DW_AT_declaration
	.dwattr $C$DW$268, DW_AT_TI_symbol_name("___aad__3iq8FRCl")
	.dwattr $C$DW$268, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$268, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$798	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$798, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$268


$C$DW$269	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$269, DW_AT_declaration
	.dwattr $C$DW$269, DW_AT_TI_symbol_name("___aor__3iq8FRCl")
	.dwattr $C$DW$269, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$269, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$799	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$799, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$269


$C$DW$270	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$270, DW_AT_declaration
	.dwattr $C$DW$270, DW_AT_TI_symbol_name("___aer__3iq8FRCl")
	.dwattr $C$DW$270, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$270, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$800	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$800, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$270

	.dwendtag $C$DW$T$211

	.dwattr $C$DW$T$211, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$211, DW_AT_decl_line(0x280)
	.dwattr $C$DW$T$211, DW_AT_decl_column(0x08)
$C$DW$801	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$801, DW_AT_type(*$C$DW$T$211)
$C$DW$T$205	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$205, DW_AT_type(*$C$DW$801)
$C$DW$T$206	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$206, DW_AT_type(*$C$DW$T$205)
	.dwattr $C$DW$T$206, DW_AT_address_class(0x16)
$C$DW$T$208	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$208, DW_AT_type(*$C$DW$T$211)
	.dwattr $C$DW$T$208, DW_AT_address_class(0x16)

$C$DW$T$209	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$209, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$T$209, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$802	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$802, DW_AT_type(*$C$DW$T$206)
	.dwendtag $C$DW$T$209


$C$DW$T$210	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$210, DW_AT_type(*$C$DW$T$208)
	.dwattr $C$DW$T$210, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$803	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$803, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$210


$C$DW$T$218	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$218, DW_AT_name("iq7")
	.dwattr $C$DW$T$218, DW_AT_byte_size(0x02)
$C$DW$804	.dwtag  DW_TAG_member
	.dwattr $C$DW$804, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$804, DW_AT_name("val")
	.dwattr $C$DW$804, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$804, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$804, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$804, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$804, DW_AT_decl_line(0x2af)
	.dwattr $C$DW$804, DW_AT_decl_column(0x0a)

$C$DW$271	.dwtag  DW_TAG_subprogram, DW_AT_name("iq7")
	.dwattr $C$DW$271, DW_AT_declaration
	.dwattr $C$DW$271, DW_AT_TI_symbol_name("___ct__3iq7Fv")
	.dwattr $C$DW$271, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$272	.dwtag  DW_TAG_subprogram, DW_AT_name("iq7")
	.dwattr $C$DW$272, DW_AT_declaration
	.dwattr $C$DW$272, DW_AT_TI_symbol_name("___ct__3iq7Fl")
	.dwattr $C$DW$272, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$805	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$805, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$272


$C$DW$273	.dwtag  DW_TAG_subprogram, DW_AT_name("iq7")
	.dwattr $C$DW$273, DW_AT_declaration
	.dwattr $C$DW$273, DW_AT_TI_symbol_name("___ct__3iq7FRC3iq7")
	.dwattr $C$DW$273, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$806	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$806, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$273


$C$DW$274	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$274, DW_AT_declaration
	.dwattr $C$DW$274, DW_AT_TI_symbol_name("___as__3iq7FRC3iq7")
	.dwattr $C$DW$274, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$274, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$807	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$807, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$274


$C$DW$275	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$275, DW_AT_declaration
	.dwattr $C$DW$275, DW_AT_TI_symbol_name("___apl__3iq7FRC3iq7")
	.dwattr $C$DW$275, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$275, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$808	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$808, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$275


$C$DW$276	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$276, DW_AT_declaration
	.dwattr $C$DW$276, DW_AT_TI_symbol_name("___ami__3iq7FRC3iq7")
	.dwattr $C$DW$276, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$276, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$809	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$809, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$276


$C$DW$277	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$277, DW_AT_declaration
	.dwattr $C$DW$277, DW_AT_TI_symbol_name("___amu__3iq7FRC3iq7")
	.dwattr $C$DW$277, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$277, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$810	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$810, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$277


$C$DW$278	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$278, DW_AT_declaration
	.dwattr $C$DW$278, DW_AT_TI_symbol_name("___adv__3iq7FRC3iq7")
	.dwattr $C$DW$278, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$278, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$811	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$811, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$278


$C$DW$279	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$279, DW_AT_declaration
	.dwattr $C$DW$279, DW_AT_TI_symbol_name("___aad__3iq7FRCl")
	.dwattr $C$DW$279, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$279, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$812	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$812, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$279


$C$DW$280	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$280, DW_AT_declaration
	.dwattr $C$DW$280, DW_AT_TI_symbol_name("___aor__3iq7FRCl")
	.dwattr $C$DW$280, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$280, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$813	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$813, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$280


$C$DW$281	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$281, DW_AT_declaration
	.dwattr $C$DW$281, DW_AT_TI_symbol_name("___aer__3iq7FRCl")
	.dwattr $C$DW$281, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$281, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$814	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$814, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$281

	.dwendtag $C$DW$T$218

	.dwattr $C$DW$T$218, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$218, DW_AT_decl_line(0x299)
	.dwattr $C$DW$T$218, DW_AT_decl_column(0x08)
$C$DW$815	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$815, DW_AT_type(*$C$DW$T$218)
$C$DW$T$212	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$212, DW_AT_type(*$C$DW$815)
$C$DW$T$213	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$213, DW_AT_type(*$C$DW$T$212)
	.dwattr $C$DW$T$213, DW_AT_address_class(0x16)
$C$DW$T$215	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$215, DW_AT_type(*$C$DW$T$218)
	.dwattr $C$DW$T$215, DW_AT_address_class(0x16)

$C$DW$T$216	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$216, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$T$216, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$816	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$816, DW_AT_type(*$C$DW$T$213)
	.dwendtag $C$DW$T$216


$C$DW$T$217	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$217, DW_AT_type(*$C$DW$T$215)
	.dwattr $C$DW$T$217, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$817	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$817, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$217


$C$DW$T$225	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$225, DW_AT_name("iq6")
	.dwattr $C$DW$T$225, DW_AT_byte_size(0x02)
$C$DW$818	.dwtag  DW_TAG_member
	.dwattr $C$DW$818, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$818, DW_AT_name("val")
	.dwattr $C$DW$818, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$818, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$818, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$818, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$818, DW_AT_decl_line(0x2c8)
	.dwattr $C$DW$818, DW_AT_decl_column(0x0a)

$C$DW$282	.dwtag  DW_TAG_subprogram, DW_AT_name("iq6")
	.dwattr $C$DW$282, DW_AT_declaration
	.dwattr $C$DW$282, DW_AT_TI_symbol_name("___ct__3iq6Fv")
	.dwattr $C$DW$282, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$283	.dwtag  DW_TAG_subprogram, DW_AT_name("iq6")
	.dwattr $C$DW$283, DW_AT_declaration
	.dwattr $C$DW$283, DW_AT_TI_symbol_name("___ct__3iq6Fl")
	.dwattr $C$DW$283, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$819	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$819, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$283


$C$DW$284	.dwtag  DW_TAG_subprogram, DW_AT_name("iq6")
	.dwattr $C$DW$284, DW_AT_declaration
	.dwattr $C$DW$284, DW_AT_TI_symbol_name("___ct__3iq6FRC3iq6")
	.dwattr $C$DW$284, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$820	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$820, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$284


$C$DW$285	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$285, DW_AT_declaration
	.dwattr $C$DW$285, DW_AT_TI_symbol_name("___as__3iq6FRC3iq6")
	.dwattr $C$DW$285, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$285, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$821	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$821, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$285


$C$DW$286	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$286, DW_AT_declaration
	.dwattr $C$DW$286, DW_AT_TI_symbol_name("___apl__3iq6FRC3iq6")
	.dwattr $C$DW$286, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$286, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$822	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$822, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$286


$C$DW$287	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$287, DW_AT_declaration
	.dwattr $C$DW$287, DW_AT_TI_symbol_name("___ami__3iq6FRC3iq6")
	.dwattr $C$DW$287, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$287, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$823	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$823, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$287


$C$DW$288	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$288, DW_AT_declaration
	.dwattr $C$DW$288, DW_AT_TI_symbol_name("___amu__3iq6FRC3iq6")
	.dwattr $C$DW$288, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$288, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$824	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$824, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$288


$C$DW$289	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$289, DW_AT_declaration
	.dwattr $C$DW$289, DW_AT_TI_symbol_name("___adv__3iq6FRC3iq6")
	.dwattr $C$DW$289, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$289, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$825	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$825, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$289


$C$DW$290	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$290, DW_AT_declaration
	.dwattr $C$DW$290, DW_AT_TI_symbol_name("___aad__3iq6FRCl")
	.dwattr $C$DW$290, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$290, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$826	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$826, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$290


$C$DW$291	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$291, DW_AT_declaration
	.dwattr $C$DW$291, DW_AT_TI_symbol_name("___aor__3iq6FRCl")
	.dwattr $C$DW$291, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$291, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$827	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$827, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$291


$C$DW$292	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$292, DW_AT_declaration
	.dwattr $C$DW$292, DW_AT_TI_symbol_name("___aer__3iq6FRCl")
	.dwattr $C$DW$292, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$292, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$828	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$828, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$292

	.dwendtag $C$DW$T$225

	.dwattr $C$DW$T$225, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$225, DW_AT_decl_line(0x2b2)
	.dwattr $C$DW$T$225, DW_AT_decl_column(0x08)
$C$DW$829	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$829, DW_AT_type(*$C$DW$T$225)
$C$DW$T$219	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$219, DW_AT_type(*$C$DW$829)
$C$DW$T$220	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$220, DW_AT_type(*$C$DW$T$219)
	.dwattr $C$DW$T$220, DW_AT_address_class(0x16)
$C$DW$T$222	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$222, DW_AT_type(*$C$DW$T$225)
	.dwattr $C$DW$T$222, DW_AT_address_class(0x16)

$C$DW$T$223	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$223, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$T$223, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$830	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$830, DW_AT_type(*$C$DW$T$220)
	.dwendtag $C$DW$T$223


$C$DW$T$224	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$224, DW_AT_type(*$C$DW$T$222)
	.dwattr $C$DW$T$224, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$831	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$831, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$224


$C$DW$T$232	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$232, DW_AT_name("iq5")
	.dwattr $C$DW$T$232, DW_AT_byte_size(0x02)
$C$DW$832	.dwtag  DW_TAG_member
	.dwattr $C$DW$832, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$832, DW_AT_name("val")
	.dwattr $C$DW$832, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$832, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$832, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$832, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$832, DW_AT_decl_line(0x2e2)
	.dwattr $C$DW$832, DW_AT_decl_column(0x0a)

$C$DW$293	.dwtag  DW_TAG_subprogram, DW_AT_name("iq5")
	.dwattr $C$DW$293, DW_AT_declaration
	.dwattr $C$DW$293, DW_AT_TI_symbol_name("___ct__3iq5Fv")
	.dwattr $C$DW$293, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$294	.dwtag  DW_TAG_subprogram, DW_AT_name("iq5")
	.dwattr $C$DW$294, DW_AT_declaration
	.dwattr $C$DW$294, DW_AT_TI_symbol_name("___ct__3iq5Fl")
	.dwattr $C$DW$294, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$833	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$833, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$294


$C$DW$295	.dwtag  DW_TAG_subprogram, DW_AT_name("iq5")
	.dwattr $C$DW$295, DW_AT_declaration
	.dwattr $C$DW$295, DW_AT_TI_symbol_name("___ct__3iq5FRC3iq5")
	.dwattr $C$DW$295, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$834	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$834, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$295


$C$DW$296	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$296, DW_AT_declaration
	.dwattr $C$DW$296, DW_AT_TI_symbol_name("___as__3iq5FRC3iq5")
	.dwattr $C$DW$296, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$296, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$835	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$835, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$296


$C$DW$297	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$297, DW_AT_declaration
	.dwattr $C$DW$297, DW_AT_TI_symbol_name("___apl__3iq5FRC3iq5")
	.dwattr $C$DW$297, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$297, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$836	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$836, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$297


$C$DW$298	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$298, DW_AT_declaration
	.dwattr $C$DW$298, DW_AT_TI_symbol_name("___ami__3iq5FRC3iq5")
	.dwattr $C$DW$298, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$298, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$837	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$837, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$298


$C$DW$299	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$299, DW_AT_declaration
	.dwattr $C$DW$299, DW_AT_TI_symbol_name("___amu__3iq5FRC3iq5")
	.dwattr $C$DW$299, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$299, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$838	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$838, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$299


$C$DW$300	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$300, DW_AT_declaration
	.dwattr $C$DW$300, DW_AT_TI_symbol_name("___adv__3iq5FRC3iq5")
	.dwattr $C$DW$300, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$300, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$839	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$839, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$300


$C$DW$301	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$301, DW_AT_declaration
	.dwattr $C$DW$301, DW_AT_TI_symbol_name("___aad__3iq5FRCl")
	.dwattr $C$DW$301, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$301, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$840	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$840, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$301


$C$DW$302	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$302, DW_AT_declaration
	.dwattr $C$DW$302, DW_AT_TI_symbol_name("___aor__3iq5FRCl")
	.dwattr $C$DW$302, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$302, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$841	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$841, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$302


$C$DW$303	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$303, DW_AT_declaration
	.dwattr $C$DW$303, DW_AT_TI_symbol_name("___aer__3iq5FRCl")
	.dwattr $C$DW$303, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$303, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$842	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$842, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$303

	.dwendtag $C$DW$T$232

	.dwattr $C$DW$T$232, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$232, DW_AT_decl_line(0x2cc)
	.dwattr $C$DW$T$232, DW_AT_decl_column(0x08)
$C$DW$843	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$843, DW_AT_type(*$C$DW$T$232)
$C$DW$T$226	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$226, DW_AT_type(*$C$DW$843)
$C$DW$T$227	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$227, DW_AT_type(*$C$DW$T$226)
	.dwattr $C$DW$T$227, DW_AT_address_class(0x16)
$C$DW$T$229	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$229, DW_AT_type(*$C$DW$T$232)
	.dwattr $C$DW$T$229, DW_AT_address_class(0x16)

$C$DW$T$230	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$230, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$T$230, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$844	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$844, DW_AT_type(*$C$DW$T$227)
	.dwendtag $C$DW$T$230


$C$DW$T$231	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$231, DW_AT_type(*$C$DW$T$229)
	.dwattr $C$DW$T$231, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$845	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$845, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$231


$C$DW$T$239	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$239, DW_AT_name("iq4")
	.dwattr $C$DW$T$239, DW_AT_byte_size(0x02)
$C$DW$846	.dwtag  DW_TAG_member
	.dwattr $C$DW$846, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$846, DW_AT_name("val")
	.dwattr $C$DW$846, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$846, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$846, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$846, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$846, DW_AT_decl_line(0x2fb)
	.dwattr $C$DW$846, DW_AT_decl_column(0x0a)

$C$DW$304	.dwtag  DW_TAG_subprogram, DW_AT_name("iq4")
	.dwattr $C$DW$304, DW_AT_declaration
	.dwattr $C$DW$304, DW_AT_TI_symbol_name("___ct__3iq4Fv")
	.dwattr $C$DW$304, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$305	.dwtag  DW_TAG_subprogram, DW_AT_name("iq4")
	.dwattr $C$DW$305, DW_AT_declaration
	.dwattr $C$DW$305, DW_AT_TI_symbol_name("___ct__3iq4Fl")
	.dwattr $C$DW$305, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$847	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$847, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$305


$C$DW$306	.dwtag  DW_TAG_subprogram, DW_AT_name("iq4")
	.dwattr $C$DW$306, DW_AT_declaration
	.dwattr $C$DW$306, DW_AT_TI_symbol_name("___ct__3iq4FRC3iq4")
	.dwattr $C$DW$306, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$848	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$848, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$306


$C$DW$307	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$307, DW_AT_declaration
	.dwattr $C$DW$307, DW_AT_TI_symbol_name("___as__3iq4FRC3iq4")
	.dwattr $C$DW$307, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$307, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$849	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$849, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$307


$C$DW$308	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$308, DW_AT_declaration
	.dwattr $C$DW$308, DW_AT_TI_symbol_name("___apl__3iq4FRC3iq4")
	.dwattr $C$DW$308, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$308, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$850	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$850, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$308


$C$DW$309	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$309, DW_AT_declaration
	.dwattr $C$DW$309, DW_AT_TI_symbol_name("___ami__3iq4FRC3iq4")
	.dwattr $C$DW$309, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$309, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$851	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$851, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$309


$C$DW$310	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$310, DW_AT_declaration
	.dwattr $C$DW$310, DW_AT_TI_symbol_name("___amu__3iq4FRC3iq4")
	.dwattr $C$DW$310, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$310, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$852	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$852, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$310


$C$DW$311	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$311, DW_AT_declaration
	.dwattr $C$DW$311, DW_AT_TI_symbol_name("___adv__3iq4FRC3iq4")
	.dwattr $C$DW$311, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$311, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$853	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$853, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$311


$C$DW$312	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$312, DW_AT_declaration
	.dwattr $C$DW$312, DW_AT_TI_symbol_name("___aad__3iq4FRCl")
	.dwattr $C$DW$312, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$312, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$854	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$854, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$312


$C$DW$313	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$313, DW_AT_declaration
	.dwattr $C$DW$313, DW_AT_TI_symbol_name("___aor__3iq4FRCl")
	.dwattr $C$DW$313, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$313, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$855	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$855, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$313


$C$DW$314	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$314, DW_AT_declaration
	.dwattr $C$DW$314, DW_AT_TI_symbol_name("___aer__3iq4FRCl")
	.dwattr $C$DW$314, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$314, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$856	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$856, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$314

	.dwendtag $C$DW$T$239

	.dwattr $C$DW$T$239, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$239, DW_AT_decl_line(0x2e5)
	.dwattr $C$DW$T$239, DW_AT_decl_column(0x08)
$C$DW$857	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$857, DW_AT_type(*$C$DW$T$239)
$C$DW$T$233	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$233, DW_AT_type(*$C$DW$857)
$C$DW$T$234	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$234, DW_AT_type(*$C$DW$T$233)
	.dwattr $C$DW$T$234, DW_AT_address_class(0x16)
$C$DW$T$236	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$236, DW_AT_type(*$C$DW$T$239)
	.dwattr $C$DW$T$236, DW_AT_address_class(0x16)

$C$DW$T$237	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$237, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$T$237, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$858	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$858, DW_AT_type(*$C$DW$T$234)
	.dwendtag $C$DW$T$237


$C$DW$T$238	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$238, DW_AT_type(*$C$DW$T$236)
	.dwattr $C$DW$T$238, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$859	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$859, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$238


$C$DW$T$246	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$246, DW_AT_name("iq3")
	.dwattr $C$DW$T$246, DW_AT_byte_size(0x02)
$C$DW$860	.dwtag  DW_TAG_member
	.dwattr $C$DW$860, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$860, DW_AT_name("val")
	.dwattr $C$DW$860, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$860, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$860, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$860, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$860, DW_AT_decl_line(0x314)
	.dwattr $C$DW$860, DW_AT_decl_column(0x0a)

$C$DW$315	.dwtag  DW_TAG_subprogram, DW_AT_name("iq3")
	.dwattr $C$DW$315, DW_AT_declaration
	.dwattr $C$DW$315, DW_AT_TI_symbol_name("___ct__3iq3Fv")
	.dwattr $C$DW$315, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$316	.dwtag  DW_TAG_subprogram, DW_AT_name("iq3")
	.dwattr $C$DW$316, DW_AT_declaration
	.dwattr $C$DW$316, DW_AT_TI_symbol_name("___ct__3iq3Fl")
	.dwattr $C$DW$316, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$861	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$861, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$316


$C$DW$317	.dwtag  DW_TAG_subprogram, DW_AT_name("iq3")
	.dwattr $C$DW$317, DW_AT_declaration
	.dwattr $C$DW$317, DW_AT_TI_symbol_name("___ct__3iq3FRC3iq3")
	.dwattr $C$DW$317, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$862	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$862, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$317


$C$DW$318	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$318, DW_AT_declaration
	.dwattr $C$DW$318, DW_AT_TI_symbol_name("___as__3iq3FRC3iq3")
	.dwattr $C$DW$318, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$318, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$863	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$863, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$318


$C$DW$319	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$319, DW_AT_declaration
	.dwattr $C$DW$319, DW_AT_TI_symbol_name("___apl__3iq3FRC3iq3")
	.dwattr $C$DW$319, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$319, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$864	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$864, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$319


$C$DW$320	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$320, DW_AT_declaration
	.dwattr $C$DW$320, DW_AT_TI_symbol_name("___ami__3iq3FRC3iq3")
	.dwattr $C$DW$320, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$320, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$865	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$865, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$320


$C$DW$321	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$321, DW_AT_declaration
	.dwattr $C$DW$321, DW_AT_TI_symbol_name("___amu__3iq3FRC3iq3")
	.dwattr $C$DW$321, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$321, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$866	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$866, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$321


$C$DW$322	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$322, DW_AT_declaration
	.dwattr $C$DW$322, DW_AT_TI_symbol_name("___adv__3iq3FRC3iq3")
	.dwattr $C$DW$322, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$322, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$867	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$867, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$322


$C$DW$323	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$323, DW_AT_declaration
	.dwattr $C$DW$323, DW_AT_TI_symbol_name("___aad__3iq3FRCl")
	.dwattr $C$DW$323, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$323, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$868	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$868, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$323


$C$DW$324	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$324, DW_AT_declaration
	.dwattr $C$DW$324, DW_AT_TI_symbol_name("___aor__3iq3FRCl")
	.dwattr $C$DW$324, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$324, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$869	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$869, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$324


$C$DW$325	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$325, DW_AT_declaration
	.dwattr $C$DW$325, DW_AT_TI_symbol_name("___aer__3iq3FRCl")
	.dwattr $C$DW$325, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$325, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$870	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$870, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$325

	.dwendtag $C$DW$T$246

	.dwattr $C$DW$T$246, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$246, DW_AT_decl_line(0x2fe)
	.dwattr $C$DW$T$246, DW_AT_decl_column(0x08)
$C$DW$871	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$871, DW_AT_type(*$C$DW$T$246)
$C$DW$T$240	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$240, DW_AT_type(*$C$DW$871)
$C$DW$T$241	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$241, DW_AT_type(*$C$DW$T$240)
	.dwattr $C$DW$T$241, DW_AT_address_class(0x16)
$C$DW$T$243	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$243, DW_AT_type(*$C$DW$T$246)
	.dwattr $C$DW$T$243, DW_AT_address_class(0x16)

$C$DW$T$244	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$244, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$T$244, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$872	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$872, DW_AT_type(*$C$DW$T$241)
	.dwendtag $C$DW$T$244


$C$DW$T$245	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$245, DW_AT_type(*$C$DW$T$243)
	.dwattr $C$DW$T$245, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$873	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$873, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$245


$C$DW$T$253	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$253, DW_AT_name("iq2")
	.dwattr $C$DW$T$253, DW_AT_byte_size(0x02)
$C$DW$874	.dwtag  DW_TAG_member
	.dwattr $C$DW$874, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$874, DW_AT_name("val")
	.dwattr $C$DW$874, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$874, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$874, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$874, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$874, DW_AT_decl_line(0x32d)
	.dwattr $C$DW$874, DW_AT_decl_column(0x0a)

$C$DW$326	.dwtag  DW_TAG_subprogram, DW_AT_name("iq2")
	.dwattr $C$DW$326, DW_AT_declaration
	.dwattr $C$DW$326, DW_AT_TI_symbol_name("___ct__3iq2Fv")
	.dwattr $C$DW$326, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$327	.dwtag  DW_TAG_subprogram, DW_AT_name("iq2")
	.dwattr $C$DW$327, DW_AT_declaration
	.dwattr $C$DW$327, DW_AT_TI_symbol_name("___ct__3iq2Fl")
	.dwattr $C$DW$327, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$875	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$875, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$327


$C$DW$328	.dwtag  DW_TAG_subprogram, DW_AT_name("iq2")
	.dwattr $C$DW$328, DW_AT_declaration
	.dwattr $C$DW$328, DW_AT_TI_symbol_name("___ct__3iq2FRC3iq2")
	.dwattr $C$DW$328, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$876	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$876, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$328


$C$DW$329	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$329, DW_AT_declaration
	.dwattr $C$DW$329, DW_AT_TI_symbol_name("___as__3iq2FRC3iq2")
	.dwattr $C$DW$329, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$329, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$877	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$877, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$329


$C$DW$330	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$330, DW_AT_declaration
	.dwattr $C$DW$330, DW_AT_TI_symbol_name("___apl__3iq2FRC3iq2")
	.dwattr $C$DW$330, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$330, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$878	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$878, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$330


$C$DW$331	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$331, DW_AT_declaration
	.dwattr $C$DW$331, DW_AT_TI_symbol_name("___ami__3iq2FRC3iq2")
	.dwattr $C$DW$331, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$331, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$879	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$879, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$331


$C$DW$332	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$332, DW_AT_declaration
	.dwattr $C$DW$332, DW_AT_TI_symbol_name("___amu__3iq2FRC3iq2")
	.dwattr $C$DW$332, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$332, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$880	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$880, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$332


$C$DW$333	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$333, DW_AT_declaration
	.dwattr $C$DW$333, DW_AT_TI_symbol_name("___adv__3iq2FRC3iq2")
	.dwattr $C$DW$333, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$333, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$881	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$881, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$333


$C$DW$334	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$334, DW_AT_declaration
	.dwattr $C$DW$334, DW_AT_TI_symbol_name("___aad__3iq2FRCl")
	.dwattr $C$DW$334, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$334, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$882	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$882, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$334


$C$DW$335	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$335, DW_AT_declaration
	.dwattr $C$DW$335, DW_AT_TI_symbol_name("___aor__3iq2FRCl")
	.dwattr $C$DW$335, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$335, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$883	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$883, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$335


$C$DW$336	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$336, DW_AT_declaration
	.dwattr $C$DW$336, DW_AT_TI_symbol_name("___aer__3iq2FRCl")
	.dwattr $C$DW$336, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$336, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$884	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$884, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$336

	.dwendtag $C$DW$T$253

	.dwattr $C$DW$T$253, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$253, DW_AT_decl_line(0x317)
	.dwattr $C$DW$T$253, DW_AT_decl_column(0x08)
$C$DW$885	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$885, DW_AT_type(*$C$DW$T$253)
$C$DW$T$247	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$247, DW_AT_type(*$C$DW$885)
$C$DW$T$248	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$248, DW_AT_type(*$C$DW$T$247)
	.dwattr $C$DW$T$248, DW_AT_address_class(0x16)
$C$DW$T$250	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$250, DW_AT_type(*$C$DW$T$253)
	.dwattr $C$DW$T$250, DW_AT_address_class(0x16)

$C$DW$T$251	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$251, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$T$251, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$886	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$886, DW_AT_type(*$C$DW$T$248)
	.dwendtag $C$DW$T$251


$C$DW$T$252	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$252, DW_AT_type(*$C$DW$T$250)
	.dwattr $C$DW$T$252, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$887	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$887, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$252


$C$DW$T$260	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$260, DW_AT_name("iq1")
	.dwattr $C$DW$T$260, DW_AT_byte_size(0x02)
$C$DW$888	.dwtag  DW_TAG_member
	.dwattr $C$DW$888, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$888, DW_AT_name("val")
	.dwattr $C$DW$888, DW_AT_TI_symbol_name("_val")
	.dwattr $C$DW$888, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$888, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$888, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$888, DW_AT_decl_line(0x347)
	.dwattr $C$DW$888, DW_AT_decl_column(0x0a)

$C$DW$337	.dwtag  DW_TAG_subprogram, DW_AT_name("iq1")
	.dwattr $C$DW$337, DW_AT_declaration
	.dwattr $C$DW$337, DW_AT_TI_symbol_name("___ct__3iq1Fv")
	.dwattr $C$DW$337, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$338	.dwtag  DW_TAG_subprogram, DW_AT_name("iq1")
	.dwattr $C$DW$338, DW_AT_declaration
	.dwattr $C$DW$338, DW_AT_TI_symbol_name("___ct__3iq1Fl")
	.dwattr $C$DW$338, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$889	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$889, DW_AT_type(*$C$DW$T$12)
	.dwendtag $C$DW$338


$C$DW$339	.dwtag  DW_TAG_subprogram, DW_AT_name("iq1")
	.dwattr $C$DW$339, DW_AT_declaration
	.dwattr $C$DW$339, DW_AT_TI_symbol_name("___ct__3iq1FRC3iq1")
	.dwattr $C$DW$339, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$890	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$890, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$339


$C$DW$340	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$340, DW_AT_declaration
	.dwattr $C$DW$340, DW_AT_TI_symbol_name("___as__3iq1FRC3iq1")
	.dwattr $C$DW$340, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$340, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$891	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$891, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$340


$C$DW$341	.dwtag  DW_TAG_subprogram, DW_AT_name("operator +=")
	.dwattr $C$DW$341, DW_AT_declaration
	.dwattr $C$DW$341, DW_AT_TI_symbol_name("___apl__3iq1FRC3iq1")
	.dwattr $C$DW$341, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$341, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$892	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$892, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$341


$C$DW$342	.dwtag  DW_TAG_subprogram, DW_AT_name("operator -=")
	.dwattr $C$DW$342, DW_AT_declaration
	.dwattr $C$DW$342, DW_AT_TI_symbol_name("___ami__3iq1FRC3iq1")
	.dwattr $C$DW$342, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$342, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$893	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$893, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$342


$C$DW$343	.dwtag  DW_TAG_subprogram, DW_AT_name("operator *=")
	.dwattr $C$DW$343, DW_AT_declaration
	.dwattr $C$DW$343, DW_AT_TI_symbol_name("___amu__3iq1FRC3iq1")
	.dwattr $C$DW$343, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$343, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$894	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$894, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$343


$C$DW$344	.dwtag  DW_TAG_subprogram, DW_AT_name("operator /=")
	.dwattr $C$DW$344, DW_AT_declaration
	.dwattr $C$DW$344, DW_AT_TI_symbol_name("___adv__3iq1FRC3iq1")
	.dwattr $C$DW$344, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$344, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$895	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$895, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$344


$C$DW$345	.dwtag  DW_TAG_subprogram, DW_AT_name("operator &=")
	.dwattr $C$DW$345, DW_AT_declaration
	.dwattr $C$DW$345, DW_AT_TI_symbol_name("___aad__3iq1FRCl")
	.dwattr $C$DW$345, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$345, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$896	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$896, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$345


$C$DW$346	.dwtag  DW_TAG_subprogram, DW_AT_name("operator |=")
	.dwattr $C$DW$346, DW_AT_declaration
	.dwattr $C$DW$346, DW_AT_TI_symbol_name("___aor__3iq1FRCl")
	.dwattr $C$DW$346, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$346, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$897	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$897, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$346


$C$DW$347	.dwtag  DW_TAG_subprogram, DW_AT_name("operator ^=")
	.dwattr $C$DW$347, DW_AT_declaration
	.dwattr $C$DW$347, DW_AT_TI_symbol_name("___aer__3iq1FRCl")
	.dwattr $C$DW$347, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$347, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$898	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$898, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$347

	.dwendtag $C$DW$T$260

	.dwattr $C$DW$T$260, DW_AT_decl_file("../../../include/IQmathCPP.h")
	.dwattr $C$DW$T$260, DW_AT_decl_line(0x331)
	.dwattr $C$DW$T$260, DW_AT_decl_column(0x08)
$C$DW$899	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$899, DW_AT_type(*$C$DW$T$260)
$C$DW$T$254	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$254, DW_AT_type(*$C$DW$899)
$C$DW$T$255	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$255, DW_AT_type(*$C$DW$T$254)
	.dwattr $C$DW$T$255, DW_AT_address_class(0x16)
$C$DW$T$257	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$257, DW_AT_type(*$C$DW$T$260)
	.dwattr $C$DW$T$257, DW_AT_address_class(0x16)

$C$DW$T$258	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$258, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$T$258, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$900	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$900, DW_AT_type(*$C$DW$T$255)
	.dwendtag $C$DW$T$258


$C$DW$T$259	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$259, DW_AT_type(*$C$DW$T$257)
	.dwattr $C$DW$T$259, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$901	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$901, DW_AT_type(*$C$DW$T$48)
	.dwendtag $C$DW$T$259


$C$DW$T$268	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$268, DW_AT_name("DATA_LOG_C")
	.dwattr $C$DW$T$268, DW_AT_byte_size(0x200)
$C$DW$902	.dwtag  DW_TAG_member
	.dwattr $C$DW$902, DW_AT_type(*$C$DW$T$261)
	.dwattr $C$DW$902, DW_AT_name("Xwaveform")
	.dwattr $C$DW$902, DW_AT_TI_symbol_name("_Xwaveform")
	.dwattr $C$DW$902, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$902, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$902, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$902, DW_AT_decl_line(0x24)
	.dwattr $C$DW$902, DW_AT_decl_column(0x0a)
$C$DW$903	.dwtag  DW_TAG_member
	.dwattr $C$DW$903, DW_AT_type(*$C$DW$T$261)
	.dwattr $C$DW$903, DW_AT_name("Ywaveform")
	.dwattr $C$DW$903, DW_AT_TI_symbol_name("_Ywaveform")
	.dwattr $C$DW$903, DW_AT_data_member_location[DW_OP_plus_uconst 0x80]
	.dwattr $C$DW$903, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$903, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$903, DW_AT_decl_line(0x25)
	.dwattr $C$DW$903, DW_AT_decl_column(0x0a)
$C$DW$904	.dwtag  DW_TAG_member
	.dwattr $C$DW$904, DW_AT_type(*$C$DW$T$262)
	.dwattr $C$DW$904, DW_AT_name("Phase")
	.dwattr $C$DW$904, DW_AT_TI_symbol_name("_Phase")
	.dwattr $C$DW$904, DW_AT_data_member_location[DW_OP_plus_uconst 0x100]
	.dwattr $C$DW$904, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$904, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$904, DW_AT_decl_line(0x26)
	.dwattr $C$DW$904, DW_AT_decl_column(0x0b)
$C$DW$905	.dwtag  DW_TAG_member
	.dwattr $C$DW$905, DW_AT_type(*$C$DW$T$261)
	.dwattr $C$DW$905, DW_AT_name("Mag")
	.dwattr $C$DW$905, DW_AT_TI_symbol_name("_Mag")
	.dwattr $C$DW$905, DW_AT_data_member_location[DW_OP_plus_uconst 0x180]
	.dwattr $C$DW$905, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$905, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$905, DW_AT_decl_line(0x27)
	.dwattr $C$DW$905, DW_AT_decl_column(0x0a)

$C$DW$348	.dwtag  DW_TAG_subprogram, DW_AT_name("DATA_LOG_C")
	.dwattr $C$DW$348, DW_AT_declaration
	.dwattr $C$DW$348, DW_AT_TI_symbol_name("___ct__10DATA_LOG_CFv")
	.dwattr $C$DW$348, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$349	.dwtag  DW_TAG_subprogram, DW_AT_name("DATA_LOG_C")
	.dwattr $C$DW$349, DW_AT_declaration
	.dwattr $C$DW$349, DW_AT_TI_symbol_name("___ct__10DATA_LOG_CFRC10DATA_LOG_C")
	.dwattr $C$DW$349, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$906	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$906, DW_AT_type(*$C$DW$T$264)
	.dwendtag $C$DW$349


$C$DW$350	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$350, DW_AT_declaration
	.dwattr $C$DW$350, DW_AT_TI_symbol_name("___as__10DATA_LOG_CFRC10DATA_LOG_C")
	.dwattr $C$DW$350, DW_AT_type(*$C$DW$T$266)
	.dwattr $C$DW$350, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$907	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$907, DW_AT_type(*$C$DW$T$264)
	.dwendtag $C$DW$350

	.dwendtag $C$DW$T$268

	.dwattr $C$DW$T$268, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$T$268, DW_AT_decl_line(0x23)
	.dwattr $C$DW$T$268, DW_AT_decl_column(0x09)
$C$DW$908	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$908, DW_AT_type(*$C$DW$T$268)
$C$DW$T$263	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$263, DW_AT_type(*$C$DW$908)
$C$DW$T$264	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$264, DW_AT_type(*$C$DW$T$263)
	.dwattr $C$DW$T$264, DW_AT_address_class(0x16)
$C$DW$T$266	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$266, DW_AT_type(*$C$DW$T$268)
	.dwattr $C$DW$T$266, DW_AT_address_class(0x16)

$C$DW$T$267	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$267, DW_AT_type(*$C$DW$T$266)
	.dwattr $C$DW$T$267, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$909	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$909, DW_AT_type(*$C$DW$T$264)
	.dwendtag $C$DW$T$267


$C$DW$T$274	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$274, DW_AT_name("STEP")
	.dwattr $C$DW$T$274, DW_AT_byte_size(0x12)
$C$DW$910	.dwtag  DW_TAG_member
	.dwattr $C$DW$910, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$910, DW_AT_name("Xsize")
	.dwattr $C$DW$910, DW_AT_TI_symbol_name("_Xsize")
	.dwattr $C$DW$910, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$910, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$910, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$910, DW_AT_decl_line(0x2c)
	.dwattr $C$DW$910, DW_AT_decl_column(0x0a)
$C$DW$911	.dwtag  DW_TAG_member
	.dwattr $C$DW$911, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$911, DW_AT_name("Ysize")
	.dwattr $C$DW$911, DW_AT_TI_symbol_name("_Ysize")
	.dwattr $C$DW$911, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$911, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$911, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$911, DW_AT_decl_line(0x2d)
	.dwattr $C$DW$911, DW_AT_decl_column(0x0a)
$C$DW$912	.dwtag  DW_TAG_member
	.dwattr $C$DW$912, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$912, DW_AT_name("Yoffset")
	.dwattr $C$DW$912, DW_AT_TI_symbol_name("_Yoffset")
	.dwattr $C$DW$912, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$912, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$912, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$912, DW_AT_decl_line(0x2e)
	.dwattr $C$DW$912, DW_AT_decl_column(0x0a)
$C$DW$913	.dwtag  DW_TAG_member
	.dwattr $C$DW$913, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$913, DW_AT_name("X")
	.dwattr $C$DW$913, DW_AT_TI_symbol_name("_X")
	.dwattr $C$DW$913, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr $C$DW$913, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$913, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$913, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$913, DW_AT_decl_column(0x0a)
$C$DW$914	.dwtag  DW_TAG_member
	.dwattr $C$DW$914, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$914, DW_AT_name("Y")
	.dwattr $C$DW$914, DW_AT_TI_symbol_name("_Y")
	.dwattr $C$DW$914, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$914, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$914, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$914, DW_AT_decl_line(0x30)
	.dwattr $C$DW$914, DW_AT_decl_column(0x0a)
$C$DW$915	.dwtag  DW_TAG_member
	.dwattr $C$DW$915, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$915, DW_AT_name("GainX")
	.dwattr $C$DW$915, DW_AT_TI_symbol_name("_GainX")
	.dwattr $C$DW$915, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr $C$DW$915, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$915, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$915, DW_AT_decl_line(0x31)
	.dwattr $C$DW$915, DW_AT_decl_column(0x0a)
$C$DW$916	.dwtag  DW_TAG_member
	.dwattr $C$DW$916, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$916, DW_AT_name("GainY")
	.dwattr $C$DW$916, DW_AT_TI_symbol_name("_GainY")
	.dwattr $C$DW$916, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$916, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$916, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$916, DW_AT_decl_line(0x32)
	.dwattr $C$DW$916, DW_AT_decl_column(0x0a)
$C$DW$917	.dwtag  DW_TAG_member
	.dwattr $C$DW$917, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$917, DW_AT_name("FreqX")
	.dwattr $C$DW$917, DW_AT_TI_symbol_name("_FreqX")
	.dwattr $C$DW$917, DW_AT_data_member_location[DW_OP_plus_uconst 0xe]
	.dwattr $C$DW$917, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$917, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$917, DW_AT_decl_line(0x33)
	.dwattr $C$DW$917, DW_AT_decl_column(0x0a)
$C$DW$918	.dwtag  DW_TAG_member
	.dwattr $C$DW$918, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$918, DW_AT_name("FreqY")
	.dwattr $C$DW$918, DW_AT_TI_symbol_name("_FreqY")
	.dwattr $C$DW$918, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr $C$DW$918, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$918, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$918, DW_AT_decl_line(0x34)
	.dwattr $C$DW$918, DW_AT_decl_column(0x0a)

$C$DW$351	.dwtag  DW_TAG_subprogram, DW_AT_name("STEP")
	.dwattr $C$DW$351, DW_AT_declaration
	.dwattr $C$DW$351, DW_AT_TI_symbol_name("___ct__4STEPFv")
	.dwattr $C$DW$351, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$352	.dwtag  DW_TAG_subprogram, DW_AT_name("STEP")
	.dwattr $C$DW$352, DW_AT_declaration
	.dwattr $C$DW$352, DW_AT_TI_symbol_name("___ct__4STEPFRC4STEP")
	.dwattr $C$DW$352, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$919	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$919, DW_AT_type(*$C$DW$T$270)
	.dwendtag $C$DW$352


$C$DW$353	.dwtag  DW_TAG_subprogram, DW_AT_name("operator =")
	.dwattr $C$DW$353, DW_AT_declaration
	.dwattr $C$DW$353, DW_AT_TI_symbol_name("___as__4STEPFRC4STEP")
	.dwattr $C$DW$353, DW_AT_type(*$C$DW$T$272)
	.dwattr $C$DW$353, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$920	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$920, DW_AT_type(*$C$DW$T$270)
	.dwendtag $C$DW$353

	.dwendtag $C$DW$T$274

	.dwattr $C$DW$T$274, DW_AT_decl_file("IQsample.cpp")
	.dwattr $C$DW$T$274, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$T$274, DW_AT_decl_column(0x09)
$C$DW$921	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$921, DW_AT_type(*$C$DW$T$274)
$C$DW$T$269	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$269, DW_AT_type(*$C$DW$921)
$C$DW$T$270	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$270, DW_AT_type(*$C$DW$T$269)
	.dwattr $C$DW$T$270, DW_AT_address_class(0x16)
$C$DW$T$272	.dwtag  DW_TAG_reference_type
	.dwattr $C$DW$T$272, DW_AT_type(*$C$DW$T$274)
	.dwattr $C$DW$T$272, DW_AT_address_class(0x16)

$C$DW$T$273	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$273, DW_AT_type(*$C$DW$T$272)
	.dwattr $C$DW$T$273, DW_AT_language(DW_LANG_C_plus_plus)
$C$DW$922	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$922, DW_AT_type(*$C$DW$T$270)
	.dwendtag $C$DW$T$273

$C$DW$T$355	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$355, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$355, DW_AT_name("bool")
	.dwattr $C$DW$T$355, DW_AT_byte_size(0x01)
$C$DW$T$357	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$357, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$357, DW_AT_name("signed char")
	.dwattr $C$DW$T$357, DW_AT_byte_size(0x01)
$C$DW$T$358	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$358, DW_AT_type(*$C$DW$T$357)
	.dwattr $C$DW$T$358, DW_AT_address_class(0x16)
$C$DW$T$359	.dwtag  DW_TAG_typedef, DW_AT_name("va_list")
	.dwattr $C$DW$T$359, DW_AT_type(*$C$DW$T$358)
	.dwattr $C$DW$T$359, DW_AT_language(DW_LANG_C_plus_plus)
	.dwattr $C$DW$T$359, DW_AT_decl_file("C:/Program Files/Texas Instruments/C2000 Code Generation Tools 5.2.4/include/stdarg.h")
	.dwattr $C$DW$T$359, DW_AT_decl_line(0x12)
	.dwattr $C$DW$T$359, DW_AT_decl_column(0x0f)
$C$DW$T$360	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$360, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$360, DW_AT_name("signed char")
	.dwattr $C$DW$T$360, DW_AT_byte_size(0x01)
	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C_plus_plus)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 78
	.dwcfi	cfa_register, 20
	.dwcfi	cfa_offset, 0
	.dwcfi	undefined, 0
	.dwcfi	undefined, 1
	.dwcfi	undefined, 2
	.dwcfi	undefined, 3
	.dwcfi	undefined, 4
	.dwcfi	undefined, 5
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	undefined, 12
	.dwcfi	undefined, 13
	.dwcfi	undefined, 14
	.dwcfi	undefined, 15
	.dwcfi	undefined, 16
	.dwcfi	undefined, 17
	.dwcfi	undefined, 18
	.dwcfi	undefined, 19
	.dwcfi	undefined, 20
	.dwcfi	undefined, 21
	.dwcfi	undefined, 22
	.dwcfi	undefined, 23
	.dwcfi	undefined, 24
	.dwcfi	undefined, 25
	.dwcfi	undefined, 26
	.dwcfi	undefined, 27
	.dwcfi	same_value, 28
	.dwcfi	undefined, 29
	.dwcfi	undefined, 30
	.dwcfi	undefined, 31
	.dwcfi	undefined, 32
	.dwcfi	undefined, 33
	.dwcfi	undefined, 34
	.dwcfi	undefined, 35
	.dwcfi	undefined, 36
	.dwcfi	undefined, 37
	.dwcfi	undefined, 38
	.dwcfi	undefined, 39
	.dwcfi	undefined, 40
	.dwcfi	undefined, 41
	.dwcfi	undefined, 42
	.dwcfi	undefined, 43
	.dwcfi	undefined, 44
	.dwcfi	undefined, 45
	.dwcfi	undefined, 46
	.dwcfi	undefined, 47
	.dwcfi	undefined, 48
	.dwcfi	undefined, 49
	.dwcfi	undefined, 50
	.dwcfi	undefined, 51
	.dwcfi	undefined, 52
	.dwcfi	undefined, 53
	.dwcfi	undefined, 54
	.dwcfi	undefined, 55
	.dwcfi	undefined, 56
	.dwcfi	undefined, 57
	.dwcfi	undefined, 58
	.dwcfi	same_value, 59
	.dwcfi	same_value, 60
	.dwcfi	undefined, 61
	.dwcfi	undefined, 62
	.dwcfi	same_value, 63
	.dwcfi	same_value, 64
	.dwcfi	undefined, 65
	.dwcfi	undefined, 66
	.dwcfi	same_value, 67
	.dwcfi	same_value, 68
	.dwcfi	undefined, 69
	.dwcfi	undefined, 70
	.dwcfi	same_value, 71
	.dwcfi	same_value, 72
	.dwcfi	undefined, 73
	.dwcfi	undefined, 74
	.dwcfi	undefined, 75
	.dwcfi	undefined, 76
	.dwcfi	undefined, 77
	.dwcfi	undefined, 78
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$923	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AL")
	.dwattr $C$DW$923, DW_AT_location[DW_OP_reg0]
$C$DW$924	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AH")
	.dwattr $C$DW$924, DW_AT_location[DW_OP_reg1]
$C$DW$925	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PL")
	.dwattr $C$DW$925, DW_AT_location[DW_OP_reg2]
$C$DW$926	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PH")
	.dwattr $C$DW$926, DW_AT_location[DW_OP_reg3]
$C$DW$927	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR0")
	.dwattr $C$DW$927, DW_AT_location[DW_OP_reg4]
$C$DW$928	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR0")
	.dwattr $C$DW$928, DW_AT_location[DW_OP_reg5]
$C$DW$929	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR1")
	.dwattr $C$DW$929, DW_AT_location[DW_OP_reg6]
$C$DW$930	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR1")
	.dwattr $C$DW$930, DW_AT_location[DW_OP_reg7]
$C$DW$931	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR2")
	.dwattr $C$DW$931, DW_AT_location[DW_OP_reg8]
$C$DW$932	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR2")
	.dwattr $C$DW$932, DW_AT_location[DW_OP_reg9]
$C$DW$933	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR3")
	.dwattr $C$DW$933, DW_AT_location[DW_OP_reg10]
$C$DW$934	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR3")
	.dwattr $C$DW$934, DW_AT_location[DW_OP_reg11]
$C$DW$935	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR4")
	.dwattr $C$DW$935, DW_AT_location[DW_OP_reg12]
$C$DW$936	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR4")
	.dwattr $C$DW$936, DW_AT_location[DW_OP_reg13]
$C$DW$937	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR5")
	.dwattr $C$DW$937, DW_AT_location[DW_OP_reg14]
$C$DW$938	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR5")
	.dwattr $C$DW$938, DW_AT_location[DW_OP_reg15]
$C$DW$939	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR6")
	.dwattr $C$DW$939, DW_AT_location[DW_OP_reg16]
$C$DW$940	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR6")
	.dwattr $C$DW$940, DW_AT_location[DW_OP_reg17]
$C$DW$941	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR7")
	.dwattr $C$DW$941, DW_AT_location[DW_OP_reg18]
$C$DW$942	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR7")
	.dwattr $C$DW$942, DW_AT_location[DW_OP_reg19]
$C$DW$943	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$943, DW_AT_location[DW_OP_reg20]
$C$DW$944	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XT")
	.dwattr $C$DW$944, DW_AT_location[DW_OP_reg21]
$C$DW$945	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("T")
	.dwattr $C$DW$945, DW_AT_location[DW_OP_reg22]
$C$DW$946	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST0")
	.dwattr $C$DW$946, DW_AT_location[DW_OP_reg23]
$C$DW$947	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST1")
	.dwattr $C$DW$947, DW_AT_location[DW_OP_reg24]
$C$DW$948	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$948, DW_AT_location[DW_OP_reg25]
$C$DW$949	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RPC")
	.dwattr $C$DW$949, DW_AT_location[DW_OP_reg26]
$C$DW$950	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$950, DW_AT_location[DW_OP_reg27]
$C$DW$951	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FP")
	.dwattr $C$DW$951, DW_AT_location[DW_OP_reg28]
$C$DW$952	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DP")
	.dwattr $C$DW$952, DW_AT_location[DW_OP_reg29]
$C$DW$953	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SXM")
	.dwattr $C$DW$953, DW_AT_location[DW_OP_reg30]
$C$DW$954	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PM")
	.dwattr $C$DW$954, DW_AT_location[DW_OP_reg31]
$C$DW$955	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("OVM")
	.dwattr $C$DW$955, DW_AT_location[DW_OP_regx 0x20]
$C$DW$956	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PAGE0")
	.dwattr $C$DW$956, DW_AT_location[DW_OP_regx 0x21]
$C$DW$957	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AMODE")
	.dwattr $C$DW$957, DW_AT_location[DW_OP_regx 0x22]
$C$DW$958	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("INTM")
	.dwattr $C$DW$958, DW_AT_location[DW_OP_regx 0x23]
$C$DW$959	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IFR")
	.dwattr $C$DW$959, DW_AT_location[DW_OP_regx 0x24]
$C$DW$960	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IER")
	.dwattr $C$DW$960, DW_AT_location[DW_OP_regx 0x25]
$C$DW$961	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V")
	.dwattr $C$DW$961, DW_AT_location[DW_OP_regx 0x26]
$C$DW$962	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("STFL")
	.dwattr $C$DW$962, DW_AT_location[DW_OP_regx 0x27]
$C$DW$963	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("STF")
	.dwattr $C$DW$963, DW_AT_location[DW_OP_regx 0x28]
$C$DW$964	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R0LL")
	.dwattr $C$DW$964, DW_AT_location[DW_OP_regx 0x29]
$C$DW$965	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R0L")
	.dwattr $C$DW$965, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$966	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R0HL")
	.dwattr $C$DW$966, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$967	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R0H")
	.dwattr $C$DW$967, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$968	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R1LL")
	.dwattr $C$DW$968, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$969	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R1L")
	.dwattr $C$DW$969, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$970	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R1HL")
	.dwattr $C$DW$970, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$971	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R1H")
	.dwattr $C$DW$971, DW_AT_location[DW_OP_regx 0x30]
$C$DW$972	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R2LL")
	.dwattr $C$DW$972, DW_AT_location[DW_OP_regx 0x31]
$C$DW$973	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R2L")
	.dwattr $C$DW$973, DW_AT_location[DW_OP_regx 0x32]
$C$DW$974	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R2HL")
	.dwattr $C$DW$974, DW_AT_location[DW_OP_regx 0x33]
$C$DW$975	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R2H")
	.dwattr $C$DW$975, DW_AT_location[DW_OP_regx 0x34]
$C$DW$976	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R3LL")
	.dwattr $C$DW$976, DW_AT_location[DW_OP_regx 0x35]
$C$DW$977	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R3L")
	.dwattr $C$DW$977, DW_AT_location[DW_OP_regx 0x36]
$C$DW$978	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R3HL")
	.dwattr $C$DW$978, DW_AT_location[DW_OP_regx 0x37]
$C$DW$979	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R3H")
	.dwattr $C$DW$979, DW_AT_location[DW_OP_regx 0x38]
$C$DW$980	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R4LL")
	.dwattr $C$DW$980, DW_AT_location[DW_OP_regx 0x39]
$C$DW$981	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R4L")
	.dwattr $C$DW$981, DW_AT_location[DW_OP_regx 0x3a]
$C$DW$982	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R4HL")
	.dwattr $C$DW$982, DW_AT_location[DW_OP_regx 0x3b]
$C$DW$983	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R4H")
	.dwattr $C$DW$983, DW_AT_location[DW_OP_regx 0x3c]
$C$DW$984	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R5LL")
	.dwattr $C$DW$984, DW_AT_location[DW_OP_regx 0x3d]
$C$DW$985	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R5L")
	.dwattr $C$DW$985, DW_AT_location[DW_OP_regx 0x3e]
$C$DW$986	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R5HL")
	.dwattr $C$DW$986, DW_AT_location[DW_OP_regx 0x3f]
$C$DW$987	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R5H")
	.dwattr $C$DW$987, DW_AT_location[DW_OP_regx 0x40]
$C$DW$988	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R6LL")
	.dwattr $C$DW$988, DW_AT_location[DW_OP_regx 0x41]
$C$DW$989	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R6L")
	.dwattr $C$DW$989, DW_AT_location[DW_OP_regx 0x42]
$C$DW$990	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R6HL")
	.dwattr $C$DW$990, DW_AT_location[DW_OP_regx 0x43]
$C$DW$991	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R6H")
	.dwattr $C$DW$991, DW_AT_location[DW_OP_regx 0x44]
$C$DW$992	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R7LL")
	.dwattr $C$DW$992, DW_AT_location[DW_OP_regx 0x45]
$C$DW$993	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R7L")
	.dwattr $C$DW$993, DW_AT_location[DW_OP_regx 0x46]
$C$DW$994	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R7HL")
	.dwattr $C$DW$994, DW_AT_location[DW_OP_regx 0x47]
$C$DW$995	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("R7H")
	.dwattr $C$DW$995, DW_AT_location[DW_OP_regx 0x48]
$C$DW$996	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RBL")
	.dwattr $C$DW$996, DW_AT_location[DW_OP_regx 0x49]
$C$DW$997	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RB")
	.dwattr $C$DW$997, DW_AT_location[DW_OP_regx 0x4a]
$C$DW$998	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PSEUDO")
	.dwattr $C$DW$998, DW_AT_location[DW_OP_regx 0x4b]
$C$DW$999	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$999, DW_AT_location[DW_OP_regx 0x4c]
$C$DW$1000	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("VOL")
	.dwattr $C$DW$1000, DW_AT_location[DW_OP_regx 0x4d]
$C$DW$1001	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$1001, DW_AT_location[DW_OP_regx 0x4e]
	.dwendtag $C$DW$CU

