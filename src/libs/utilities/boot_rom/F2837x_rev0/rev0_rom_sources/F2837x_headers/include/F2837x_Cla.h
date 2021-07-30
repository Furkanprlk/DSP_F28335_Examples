//########################################################################### 
// 
// FILE:   F2837x_Cla.h 
// 
// TITLE:  F2837x Device CLA Register Definitions. 
// 
//########################################################################### 
// $TI Release:  $
// $Release Date:  $
//########################################################################### 

#ifndef F2837x_CLA_H 
#define F2837x_CLA_H 

#ifdef __cplusplus 
extern "C" {
#endif 


//--------------------------------------------------------------------------- 
// CLA Individual Register Bit Definitions: 

struct MCTL_BITS {                           // bits description
    Uint16  HARDRESET:1;                     // 0 Issue a hard reset 
    Uint16  SOFTRESET:1;                     // 1 Issue a soft reset 
    Uint16  IACKE:1;                         // 2 Enable IACK for task start 
    Uint16  rsvd1:13;                        // 15:3 Reserved 
};

union MCTL_REG {
    Uint16  all;  
    struct  MCTL_BITS  bit;  
};

struct MIFR_BITS {                           // bits description
    Uint16  INT1:1;                          // 0 Interrupt 1 Flag 
    Uint16  INT2:1;                          // 1 Interrupt 2 Flag 
    Uint16  INT3:1;                          // 2 Interrupt 3 Flag 
    Uint16  INT4:1;                          // 3 Interrupt 4 Flag 
    Uint16  INT5:1;                          // 4 Interrupt 5 Flag 
    Uint16  INT6:1;                          // 5 Interrupt 6 Flag 
    Uint16  INT7:1;                          // 6 Interrupt 7 Flag 
    Uint16  INT8:1;                          // 7 Interrupt 8 Flag 
    Uint16  rsvd1:8;                         // 15:8 Reserved 
};

union MIFR_REG {
    Uint16  all;  
    struct  MIFR_BITS  bit;  
};

struct MSTF_BITS {                           // bits description
    Uint32  LVF:1;                           // 0 Latched Overflow Flag
    Uint32  LUF:1;                           // 1 Latched Underflow Flag
    Uint32  NF:1;                            // 2 Negative Float Flag
    Uint32  ZF:1;                            // 3 Zero Float Flag
    Uint32  rsvd1:2;                         // 5:4 Reserved
    Uint32  TF:1;                            // 6 Test Flag
    Uint32  rsvd2:2;                         // 8:7 Reserved
    Uint32  RNDF32:1;                        // 9 Rounding Mode
    Uint32  rsvd3:1;                         // 10 Reserved
    Uint32  MEALLOW:1;                       // 11 MEALLOW Status
    Uint32  _RPC:16;                          // 27:12 Return PC: Low Portion
    Uint32  rsvd4:4;                         // 31:28 Reserved
};

union MSTF_REG {
    Uint32  all;
    struct  MSTF_BITS  bit;  
};

union MR_REG {
    Uint32  i32;  
    float  f32;  
};


struct SOFTINTEN_BITS {                      // bits description
    Uint16  TASK1:1;                          // 0 task 1 Software Interrupt Enable
    Uint16  TASK2:1;                          // 1 task 2 Software Interrupt Enable
    Uint16  TASK3:1;                          // 2 task 3 Software Interrupt Enable
    Uint16  TASK4:1;                          // 3 task 4 Software Interrupt Enable
    Uint16  TASK5:1;                          // 4 task 5 Software Interrupt Enable
    Uint16  TASK6:1;                          // 5 task 6 Software Interrupt Enable
    Uint16  TASK7:1;                          // 6 task 7 Software Interrupt Enable
    Uint16  TASK8:1;                          // 7 task 8 Software Interrupt Enable
    Uint16  rsvd1:8;                         // 15:8 Reserved
};

union SOFTINTEN_REG {
    Uint16  all;
    struct  SOFTINTEN_BITS  bit;
};

struct SOFTINTFRC_BITS {                      // bits description
    Uint16  TASK1:1;                          // 0 task 1 Software Interrupt Force
    Uint16  TASK2:1;                          // 1 task 2 Software Interrupt Force
    Uint16  TASK3:1;                          // 2 task 3 Software Interrupt Force
    Uint16  TASK4:1;                          // 3 task 4 Software Interrupt Force
    Uint16  TASK5:1;                          // 4 task 5 Software Interrupt Force
    Uint16  TASK6:1;                          // 5 task 6 Software Interrupt Force
    Uint16  TASK7:1;                          // 6 task 7 Software Interrupt Force
    Uint16  TASK8:1;                          // 7 task 8 Software Interrupt Force
    Uint16  rsvd1:8;                         // 15:8 Reserved
};

union SOFTINTFRC_REG {
    Uint16  all;
    struct  SOFTINTFRC_BITS  bit;
};

struct CLA_SOFTINT_REGS {
	union SOFTINTEN_REG		SOFTINTEN;
	union SOFTINTFRC_REG	SOFTINTFRC;
};

struct CLA_REGS {
    Uint16                    MVECT1;        // Task 1 Vecotr 
    Uint16                    MVECT2;        // Task 2 Vector 
    Uint16                    MVECT3;        // Task 3 Vector 
    Uint16                    MVECT4;        // Task 4 Vector 
    Uint16                    MVECT5;        // Task 5 Vector 
    Uint16                    MVECT6;        // Task 6 Vector 
    Uint16                    MVECT7;        // Task 7 Vecotr 
    Uint16                    MVECT8;        // Task 8 Vector 
    Uint16                    rsvd1[8];      // Reserved 
    union   MCTL_REG          MCTL;          // CLA Control
    Uint16                    rsvd2[15];      // Reserved
    union   MIFR_REG          MIFR;          // CLA Interrupt Flag 
    union   MIFR_REG          MIOVF;         // CLA Interrupt Overflow Flag 
    union   MIFR_REG          MIFRC;         // CLA Interrupt Force 
    union   MIFR_REG          MICLR;         // CLA Interrupt Flag Clear 
    union   MIFR_REG          MICLROVF;      // CLA Interrupt Overflow Flag Clear 
    union   MIFR_REG          MIER;          // CLA Interrupt Enable 
    union   MIFR_REG          MIRUN;         // CLA Interrupt Run Status 
    Uint16                    rsvd4;         // Reserved 
    Uint16                    _MPC;          // CLA Program Counter 
    Uint16                    rsvd5;         // Reserved 
    Uint16                    _MAR0;         // CLA Auxillary Register 0 
    Uint16                    _MAR1;         // CLA Auxillary Register 1 
    Uint16                    rsvd6[2];      // Reserved 
    union   MSTF_REG          _MSTF;         // CLA Floating-Point Status Register 
    union   MR_REG            _MR0;          // CLA Result Register 0 
    Uint16                    rsvd7;         // Reserved 
    union   MR_REG            _MR1;          // CLA Result Register 1 
    Uint16                    rsvd8;         // Reserved 
    union   MR_REG            _MR2;          // CLA Result Register 2 
    Uint16                    rsvd9;         // Reserved 
    union   MR_REG            _MR3;          // CLA Result Register 3 
    Uint16                    rsvd10;        // Reserved 
};

//---------------------------------------------------------------------------
// Cla External References & Function Declarations:
//
extern volatile struct CLA_REGS Cla1Regs;
extern volatile struct CLA_SOFTINT_REGS Cla1SoftIntRegs;

#ifdef __cplusplus
}
#endif                                       /* extern "C" */


#endif                                       // end of F2837x_CLA_H definition
//===========================================================================
// End of file.
//===========================================================================
