//###########################################################################
//
// FILE:   F2837x_Clb.h
//
// TITLE:  F2837x Device Clb Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Clb_H
#define F2837x_Clb_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Clb Individual Register Bit Definitions:

struct CFG_MISC_CONTROL_BITS {                                 // bit descriptions
    Uint16  COUNT_ADD_SHIFT_0:1;                               // 0 Add/Shift for counter 0 
    Uint16  COUNT_DIR_0:1;                                     // 1 Direction for counter 0 
    Uint16  COUNT_EVENT_CTRL_0:1;                              // 2 Event control for counter 0 
    Uint16  COUNT_ADD_SHIFT_1:1;                               // 3 Add/Shift for counter 1 
    Uint16  COUNT_DIR_1:1;                                     // 4 Direction for counter 1 
    Uint16  COUNT_EVENT_CTRL_1:1;                              // 5 Event control for counter 1 
    Uint16  COUNT_ADD_SHIFT_2:1;                               // 6 Add/Shift for counter 2 
    Uint16  COUNT_DIR_2:1;                                     // 7 Direction for counter 2 
    Uint16  COUNT_EVENT_CTRL_2:1;                              // 8 Event control for counter 2 
    Uint16  COUNT_SERIALIZER_0:1;                              // 9 Serializer enable 0 
    Uint16  COUNT_SERIALIZER_1:1;                              // 10 Serializer enable 1 
    Uint16  COUNT_SERIALIZER_2:1;                              // 11 Serializer enable 2 
    Uint16  FSM_EXTRA_SEL0_0:1;                                // 12 FSM extra_sel0 for 0 
    Uint16  FSM_EXTRA_SEL1_0:1;                                // 13 FSM extra_sel1 for 0 
    Uint16  FSM_EXTRA_SEL0_1:1;                                // 14 FSM extra_sel0 for 1 
    Uint16  FSM_EXTRA_SEL1_1:1;                                // 15 FSM extra_sel1 for 1 
    Uint16  FSM_EXTRA_SEL0_2:1;                                // 16 FSM extra_sel0 for 2 
    Uint16  FSM_EXTRA_SEL1_2:1;                                // 17 FSM extra_sel1 for 2 
    Uint16  rsvd1:14;                                          // 31:18 Reserved 
};

union CFG_MISC_CONTROL_REG {
    Uint32  all;  
    struct  CFG_MISC_CONTROL_BITS  bit;  
};

struct CFG_HLC_EVENT_SEL_BITS {                                // bit descriptions
    Uint16  HLC_EVENT0_SEL:5;                                  // 4:0 Event Select 0 
    Uint16  HLC_EVENT1_SEL:5;                                  // 9:5 Event Select 1 
    Uint16  HLC_EVENT2_SEL:5;                                  // 14:10 Event Select 2 
    Uint32  HLC_EVENT3_SEL:5;                                  // 19:15 Event Select 3 
    Uint16  rsvd1:12;                                          // 31:20 Reserved 
};

union CFG_HLC_EVENT_SEL_REG {
    Uint32  all;  
    struct  CFG_HLC_EVENT_SEL_BITS  bit;  
};

struct RCFG_LOCK_BITS {                                        // bit descriptions
    Uint16  LOCK:1;                                            // 0 LOCK enable 
    Uint16  rsvd1:15;                                          // 15:1 Reserved 
    Uint16  WRITE_ENABLE_KEY:16;                               // 31:16 Key for enabling write 
};

union RCFG_LOCK_REG {
    Uint32  all;  
    struct  RCFG_LOCK_BITS  bit;  
};

struct RCFG_LOAD_ADDR_BITS {                                   // bit descriptions
    Uint16  Address:6;                                         // 5:0 Indirect Address 
    Uint16  rsvd1:10;                                          // 15:6 Reserved 
    Uint16  rsvd2:16;                                          // 31:16 Reserved 
};

union RCFG_LOAD_ADDR_REG {
    Uint32  all;  
    struct  RCFG_LOAD_ADDR_BITS  bit;  
};

struct RCFG_INPUT_FILTER_BITS {                                // bit descriptions
    Uint16  Filter_In_0:2;                                     // 1:0 Input filter control 0 
    Uint16  Filter_In_1:2;                                     // 3:2 Input filter control 1 
    Uint16  Filter_In_2:2;                                     // 5:4 Input filter control 2 
    Uint16  Filter_In_3:2;                                     // 7:6 Input filter control 3 
    Uint16  Filter_In_4:2;                                     // 9:8 Input filter control 4 
    Uint16  Filter_In_5:2;                                     // 11:10 Input filter control 5 
    Uint16  Filter_In_6:2;                                     // 13:12 Input filter control 6 
    Uint16  Filter_In_7:2;                                     // 15:14 Input filter control 7 
    Uint16  Sync_select_In_0:1;                                // 16 Synchronizer control 0 
    Uint16  Sync_select_In_1:1;                                // 17 Synchronizer control 1 
    Uint16  Sync_select_In_2:1;                                // 18 Synchronizer control 2 
    Uint16  Sync_select_In_3:1;                                // 19 Synchronizer control 3 
    Uint16  Sync_select_In_4:1;                                // 20 Synchronizer control 4 
    Uint16  Sync_select_In_5:1;                                // 21 Synchronizer control 5 
    Uint16  Sync_select_In_6:1;                                // 22 Synchronizer control 6 
    Uint16  Sync_select_In_7:1;                                // 23 Synchronizer control 7 
    Uint16  rsvd1:8;                                           // 31:24 Reserved 
};

union RCFG_INPUT_FILTER_REG {
    Uint32  all;  
    struct  RCFG_INPUT_FILTER_BITS  bit;  
};

struct RCFG_IN_SEL_0_BITS {                                    // bit descriptions
    Uint16  SEL_GP_IN_0:1;                                     // 0 Select GP register 0 
    Uint16  SEL_GP_IN_1:1;                                     // 1 Select GP register 1 
    Uint16  SEL_GP_IN_2:1;                                     // 2 Select GP register 2 
    Uint16  SEL_GP_IN_3:1;                                     // 3 Select GP register 3 
    Uint16  SEL_GP_IN_4:1;                                     // 4 Select GP register 4 
    Uint16  SEL_GP_IN_5:1;                                     // 5 Select GP register 5 
    Uint16  SEL_GP_IN_6:1;                                     // 6 Select GP register 6 
    Uint16  SEL_GP_IN_7:1;                                     // 7 Select GP register 7 
    Uint16  rsvd1:8;                                           // 15:8 Reserved 
};

union RCFG_IN_SEL_0_REG {
    Uint16  all;  
    struct  RCFG_IN_SEL_0_BITS  bit;  
};

struct RCFG_LCL_MUX_SEL_1_BITS {                               // bit descriptions
    Uint16  LCL_MUX_SEL_IN_0:5;                                // 4:0 Local Mux select 0 
    Uint16  LCL_MUX_SEL_IN_1:5;                                // 9:5 Local Mux select 1 
    Uint16  LCL_MUX_SEL_IN_2:5;                                // 14:10 Local Mux select 2 
    Uint32  LCL_MUX_SEL_IN_3:5;                                // 19:15 Local Mux select 3 
    Uint16  rsvd1:12;                                          // 31:20 Reserved 
};

union RCFG_LCL_MUX_SEL_1_REG {
    Uint32  all;  
    struct  RCFG_LCL_MUX_SEL_1_BITS  bit;  
};

struct RCFG_LCL_MUX_SEL_2_BITS {                               // bit descriptions
    Uint16  LCL_MUX_SEL_IN_4:5;                                // 4:0 Local Mux select 4 
    Uint16  LCL_MUX_SEL_IN_5:5;                                // 9:5 Local Mux select 5 
    Uint16  LCL_MUX_SEL_IN_6:5;                                // 14:10 Local Mux select 6 
    Uint32  LCL_MUX_SEL_IN_7:5;                                // 19:15 Local Mux select 7 
    Uint16  rsvd1:12;                                          // 31:20 Reserved 
};

union RCFG_LCL_MUX_SEL_2_REG {
    Uint32  all;  
    struct  RCFG_LCL_MUX_SEL_2_BITS  bit;  
};

struct RCFG_GLBL_MUX_SEL_1_BITS {                              // bit descriptions
    Uint16  GLBL_MUX_SEL_IN_0:7;                               // 6:0 Global Mux select 0 
    Uint16  GLBL_MUX_SEL_IN_1:7;                               // 13:7 Global Mux select 1 
    Uint32  GLBL_MUX_SEL_IN_2:7;                               // 20:14 Global Mux select 2 
    Uint16  GLBL_MUX_SEL_IN_3:7;                               // 27:21 Global Mux select 3 
    Uint16  rsvd1:4;                                           // 31:28 Reserved 
};

union RCFG_GLBL_MUX_SEL_1_REG {
    Uint32  all;  
    struct  RCFG_GLBL_MUX_SEL_1_BITS  bit;  
};

struct RCFG_GLBL_MUX_SEL_2_BITS {                              // bit descriptions
    Uint16  GLBL_MUX_SEL_IN_4:7;                               // 6:0 Global Mux select 4 
    Uint16  GLBL_MUX_SEL_IN_5:7;                               // 13:7 Global Mux select 5 
    Uint32  GLBL_MUX_SEL_IN_6:7;                               // 20:14 Global Mux select 6 
    Uint16  GLBL_MUX_SEL_IN_7:7;                               // 27:21 Global Mux select 7 
    Uint16  rsvd1:4;                                           // 31:28 Reserved 
};

union RCFG_GLBL_MUX_SEL_2_REG {
    Uint32  all;  
    struct  RCFG_GLBL_MUX_SEL_2_BITS  bit;  
};

struct RCFG_BUF_PTR_BITS {                                     // bit descriptions
    Uint16  PULL_DATA_PTR:8;                                   // 7:0 Data pointer for pull 
    Uint16  rsvd1:8;                                           // 15:8 Reserved 
    Uint16  PUSH_DATA_PTR:8;                                   // 23:16 Data pointer for pull 
    Uint16  rsvd2:8;                                           // 31:24 Reserved 
};

union RCFG_BUF_PTR_REG {
    Uint32  all;  
    struct  RCFG_BUF_PTR_BITS  bit;  
};

struct RCFG_GP_REG_BITS {                                      // bit descriptions
    Uint16  GP_REG_0:1;                                        // 0 General Purpose bit 0 
    Uint16  GP_REG_1:1;                                        // 1 General Purpose bit 1 
    Uint16  GP_REG_2:1;                                        // 2 General Purpose bit 2 
    Uint16  GP_REG_3:1;                                        // 3 General Purpose bit 3 
    Uint16  GP_REG_4:1;                                        // 4 General Purpose bit 4 
    Uint16  GP_REG_5:1;                                        // 5 General Purpose bit 5 
    Uint16  GP_REG_6:1;                                        // 6 General Purpose bit 6 
    Uint16  GP_REG_7:1;                                        // 7 General Purpose bit 7 
    Uint16  rsvd1:8;                                           // 15:8 Reserved 
};

union RCFG_GP_REG_REG {
    Uint16  all;  
    struct  RCFG_GP_REG_BITS  bit;  
};

struct CLB_LOGIC_CONFIG_REGS {
    Uint16                             rsvd1[42];              // Reserved 
    union   CFG_MISC_CONTROL_REG       CFG_MISC_CONTROL;       // Miscellaneous static controls for Counter and FSM blocks 
    Uint16                             rsvd2[16];              // Reserved 
    union   CFG_HLC_EVENT_SEL_REG      CFG_HLC_EVENT_SEL;      // Event Selector register for the High Level controller 
};

struct CLB_LOGIC_CONTROL_REGS {
    Uint16                             RCFG_LOAD_EN;           // Global enable & indirect load enable control 
    Uint16                             rsvd1;                  // Reserved 
    union   RCFG_LOAD_ADDR_REG         RCFG_LOAD_ADDR;         // Indirect address 
    Uint32                             RCFG_LOAD_DATA;         // Data for indirect loads 
    union   RCFG_INPUT_FILTER_REG      RCFG_INPUT_FILTER;      // Input filter selection for both edge detection and synchronizers 
    union   RCFG_IN_SEL_0_REG          RCFG_IN_SEL_0;          // Input selection to decide between Signals and GP register 
    union   RCFG_LCL_MUX_SEL_1_REG     RCFG_LCL_MUX_SEL_1;     // Input Mux selection for local mux 
    union   RCFG_LCL_MUX_SEL_2_REG     RCFG_LCL_MUX_SEL_2;     // Input Mux selection for local mux 
    union   RCFG_BUF_PTR_REG           RCFG_BUF_PTR;           // PUSH and PULL pointers 
    union   RCFG_GP_REG_REG            RCFG_GP_REG;            // General purpose register for CELL inputs 
    Uint16                             rsvd2[2];               // Reserved 
    union   RCFG_GLBL_MUX_SEL_1_REG    RCFG_GLBL_MUX_SEL_1;    // Global Mux select for CELL inputs 
    union   RCFG_GLBL_MUX_SEL_2_REG    RCFG_GLBL_MUX_SEL_2;    // Global Mux select for CELL inputs 
    Uint16                             rsvd3[10];              // Reserved 
    union   RCFG_LOCK_REG              RCFG_LOCK;              // Lock control register 
    Uint16                             rsvd4[12];              // Reserved 
    union   RCFG_DBG_R0_REG            RCFG_DBG_R0;            // R0 of High level Controller 
    union   RCFG_DBG_R1_REG            RCFG_DBG_R1;            // R1 of High level Controller 
    union   RCFG_DBG_R2_REG            RCFG_DBG_R2;            // R2 of High level Controller 
    union   RCFG_DBG_R3_REG            RCFG_DBG_R3;            // R3 of High level Controller 
    union   RCFG_DBG_C0_REG            RCFG_DBG_C0;            // Count of Unit 0 
    union   RCFG_DBG_C1_REG            RCFG_DBG_C1;            // Count of Unit 1 
    union   RCFG_DBG_C2_REG            RCFG_DBG_C2;            // Count of Unit 2 
    union   RCFG_DEBUG_OUT_REG         RCFG_DEBUG_OUT;         // Outputs of various units in the Cell 
};

//---------------------------------------------------------------------------
// Clb External References & Function Declarations:
//

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicConfigRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicConfigRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicConfigRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicConfigRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicControlRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicControlRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicControlRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicControlRegs;

#ifdef __cplusplus
}
#endif                                                         /* extern "C" */


#endif                                                         // end of F2837x_CLB_H definition
//===========================================================================
// End of file.
//===========================================================================
