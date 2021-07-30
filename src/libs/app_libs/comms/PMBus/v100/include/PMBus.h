/*******************************************************************************
    Filename:       PMBus.h

    Copyright 2011 Texas Instruments, Inc.
*******************************************************************************/
#ifndef PMBUS_H
#define PMBUS_H

////////////USER CODE////////////
// The user should change the value of PEC to match their implementation's
// desired Packet Error Checking capability. This will cause all associated
// files to build either with or without PEC capability, accordingly.
#warn	"User should change PEC value to build with or without PEC capability."
#define PEC		0	//PEC 0: Disable Packet Error Checking
					//PEC 1: Enable Packet Error Checking
////////////END USER CODE////////					
					
#if PEC
	#define PEC_PASS           	1
	#define PEC_FAIL           	0
	#define CRC8_POLY	   		0x07
	#define CRC8_INIT_REM      	0x0
#endif

#define READBYTE      0
#define READWORD      2
#define WRITEBYTE     4
#define SENDBYTE      6
#define WRITEWORD     8
#define RWBYTE		  1
#define RWWORD		  3

//GROUP#0
#define CAPABILITY                          1
#define STATUS_BYTE                         2
#define STATUS_VOUT                         3
#define STATUS_IOUT                         4
#define STATUS_INPUT                        5
#define STATUS_TEMPERATURE                  6
#define STATUS_CML                          7
#define STATUS_OTHER                        8
#define STATUS_MFR_SPECIFIC                 9
#define STATUS_FANS_1_2                     10
#define STATUS_FANS_3_4                     11
#define PMBUS_REVISION                      12

// GROUP #2 
#define STATUS_WORD                         13
#define READ_VIN                            14
#define READ_IIN                            15
#define READ_VCAP                           16
#define READ_VOUT                           17
#define READ_IOUT                           18
#define READ_TEMPERATURE_1                  19
#define READ_TEMPERATURE_2                  20
#define READ_TEMPERATURE_3                  21
#define READ_FAN_SPEED_1                    22
#define READ_FAN_SPEED_2                    23
#define READ_FAN_SPEED_3                    24
#define READ_FAN_SPEED_4                    25
#define READ_DUTY_CYCLE                     26
#define READ_FREQUENCY                      27
#define READ_POUT                           28
#define READ_PIN                            29
#define MFR_VIN_MIN                         30
#define MFR_VIN_MAX                         31
#define MFR_IIN_MAX                         32
#define MFR_PIN_MAX                         33
#define MFR_VOUT_MIN                        34
#define MFR_VOUT_MAX                        35
#define MFR_IOUT_MAX                        36
#define MFR_POUT_MAX                        37
#define MFR_TAMBIENT_MAX                    38
#define MFR_TAMBIENT_MIN                    39

// GROUP #4
#define STORE_DEFAULT_CODE                  40
#define RESTORE_DEFAULT_CODE                41
#define STORE_USER_CODE                     42
#define RESTORE_USER_CODE                   43

// GROUP#6
#define CLEAR_FAULTS                        44
#define STORE_DEFAULT_ALL                   45
#define RESTORE_DEFAULT_ALL                 46
#define STORE_USER_ALL                      47
#define RESTORE_USER_ALL                    48

//GROUP#8
#define PAGE/ GENERAL CALL                  49
#define OPERATION                           50
#define ON_OFF_CONFIG                       51
#define PHASE                               52
#define WRITE_PROTECT                       53
#define VOUT_MODE                           54
#define FAN_CONFIG_1_2                      55
#define FAN_CONFIG_3_4                      56
#define VOUT_OV_FAULT_RESPONSE              57
#define VOUT_UV_FAULT_RESPONSE              58
#define IOUT_OC_FAULT_RESPONSE              59
#define IOUT_0C_LV_FAULT_RESPONSE           60
#define IOUT_UC_FAULT_RESPONSE              61
#define OT_FAULT_RESPONSE                   62
#define UT_FAULT_RESPONSE                   63
#define VIN_OV_FAULT_RESPONSE               64
#define VIN_UV_FAULT_RESPONSE               65
#define IIN_OC_FAULT_RESPONSE               66
#define TON_MAX_FAULT_RESPONSE              67
#define POUT_OP_FAULT_RESPONSE              68

//GROUP#10 
#define VOUT_COMMAND                        69
#define VOUT_TRIM                           70
#define VOUT_CAL_OFFSET                     71
#define VOUT_MAX                            72
#define VOUT_MARGIN_HIGH                    73
#define VOUT_MARGIN_LOW                     74
#define VOUT_TRANSITION_RATE                75
#define VOUT_DROOP                          76
#define VOUT_SCALE_LOOP                     77
#define VOUT_SCALE_MONITOR                  78
#define POUT_MAX                            79
#define MAX_DUTY                            80
#define FREQUENCY_SWITCH                    81
#define VIN_ON                              82
#define VIN_OFF                             83
#define INTERLEAVE                          84
#define IOUT_CAL_GAIN                       85
#define IOUT_CAL_OFFSET                     86
#define FAN_COMMAND_1                       87
#define FAN_COMMAND_2                       88
#define FAN_COMMAND_3                       89
#define FAN_COMMAND_4                       90
#define VOUT_OV_FAULT_LIMIT                 91
#define VOUT_OV_WARN_LIMIT                  92
#define VOUT_UV_WARN_LIMIT                  93
#define VOUT_UV_FAULT_LIMIT                 94
#define IOUT_OC_FAULT_LIMIT                 95
#define IOUT_OC_LV_FAULT_LIMIT              96
#define IOUT_OC_WARN_LIMIT                  97
#define IOUT_UC_FAULT_LIMIT                 98
#define OT_FAULT_LIMIT                      99
#define OT_WARN_LIMIT                       100
#define UT_WARN_LIMIT                       101
#define UT_FAULT_LIMIT                      102
#define VIN_OV_FAULT_LIMIT                  103
#define VIN_OV_WARN_LIMIT                   104
#define VIN_UV_WARN_LIMIT                   105
#define VIN_UV_FAULT_LIMIT                  106
#define IIN_OC_FAULT_LIMIT                  107
#define IIN_OC_WARN_LIMIT                   108
#define POWER_GOOD_ON                       109
#define POWER_GOOD_OFF                      110
#define TON_DELAY                           111
#define TON_RISE                            112
#define TON_MAX_FAULT_LIMIT                 113
#define TOFF_DELAY                          114
#define TOFF_FALL                           115
#define TOFF_MAX_WARN_LIMIT                 116
#define POUT_OP_FAULT_LIMIT                 117
#define POUT_OP_WARN_LIMIT                  118
#define PIN_OP_WARN_LIMIT                   119 

//----------------------------------------------------
//	Status registers
//	STATUS_BYTE and STATUS_WORD register bit definitions */
//lower byte
struct STATUS_LOWER_BITS {		// bits
   Uint16 NONE_OF_THE_ABOVE:1;  // 0
   Uint16 CML:1;        		// 1
   Uint16 TEMPERATURE:1;        // 2
   Uint16 VIN_UV:1;        		// 3   
   Uint16 IOUT_OC:1;        	// 4
   Uint16 VOUT_OV:1;        	// 5
   Uint16 OFF:1;        		// 6
   Uint16 BUSY:1;        		// 7
};
//upper byte
struct STATUS_UPPER_BITS {		// bits
   Uint16 UNKNOWN:1;  			// 8
   Uint16 OTHER:1;        		// 9
   Uint16 FANS:1;        		// 10
   Uint16 POWER_GOOD:1;        	// 11   
   Uint16 MFR:1;        		// 12
   Uint16 INPUT:1;        		// 13
   Uint16 IOUT_POUT:1;        	// 14
   Uint16 VOUT:1;        		// 15
   
};

union STATUS_BYTE_REG {
	Uint16              all;
	struct STATUS_LOWER_BITS bit;
};

union STATUS_WORD_REG {
   Uint16              all;
   union STATUS_BYTE_REG StatusByte;
   struct STATUS_UPPER_BITS bit;
};

//----------------------------------------------------
//	STATUS_VOUT register bit definitions */
struct STATUS_VOUT_BITS {		// bits
   Uint16 POWER_ON_TRACKING_ERROR:1;	// 0
   Uint16 TOFF_MAX_WARNING:1;        	// 1
   Uint16 TON_MAX_WARNING:1;        	// 2
   Uint16 VOUT_MAX_WARNING:1;        	// 3   
   Uint16 VOUT_UV_FAULT:1;        		// 4
   Uint16 VOUT_UV_WARNING:1;        	// 5
   Uint16 VOUT_OV_WARNING:1;        	// 6
   Uint16 VOUT_OV_FAULT:1;        		// 7
};

union STATUS_VOUT_REG {
   Uint16              all;
   struct STATUS_VOUT_BITS bit;
};

//----------------------------------------------------
//	STATUS_IOUT register bit definitions */
struct STATUS_IOUT_BITS {		// bits
   Uint16 POUT_OP_WARNING:1;			// 0
   Uint16 POUT_OP_FAULT:1;        		// 1
   Uint16 IN_POWER_LIMITING_MODE:1;     // 2
   Uint16 CURRENT_SHARE_FAULT:1;        // 3   
   Uint16 IOUT_UC_FAULT:1;        		// 4
   Uint16 IOUT_OC_WARNING:1;        	// 5
   Uint16 IOUT_OC_FAULT_LV_SHUTDOWN:1;	// 6
   Uint16 IOUT_OC_FAULT:1;        		// 7
};

union STATUS_IOUT_REG {
   Uint16              all;
   struct STATUS_IOUT_BITS bit;
};

//----------------------------------------------------
//	STATUS_TEMPERATURE register bit definitions */
struct STATUS_TEMPERATURE_BITS {		// bits
   Uint16 rsvd:4;			// 0:3   
   Uint16 UT_FAULT:1;		// 4
   Uint16 UT_WARNING:1;		// 5
   Uint16 OT_WARNING:1;     // 6
   Uint16 OT_FAULT:1;       // 7
};

union STATUS_TEMPERATURE_REG {
   Uint16              all;
   struct STATUS_TEMPERATURE_BITS bit;
};

//----------------------------------------------------
//	STATUS_CML register bit definitions */
struct STATUS_CML_BITS {		// bits
   Uint16 OTHER_MEMORY_OR_LOGIC_FAULT:1;	// 0
   Uint16 OTHER_COMMUNICATION_FAULT:1;      // 1
   Uint16 rsvd:1;        		// 2
   Uint16 PROCESSOR_FAULT_DETECTED:1;		// 3   
   Uint16 MEMORY_FAULT_DETECTED:1;			// 4
   Uint16 PACKET_ERROR_CHECK_FAILED:1;		// 5
   Uint16 INVALID_DATA:1;        			// 6
   Uint16 INVALID_COMMAND:1;        		// 7
};

union STATUS_CML_REG {
   Uint16              all;
   struct STATUS_CML_BITS bit;
};

//----------------------------------------------------
//	STATUS_INPUT register bit definitions */
struct STATUS_INPUT_BITS {		// bits
   Uint16 PIN_OP_WARNING:1;	// 0
   Uint16 IIN_OC_WARNING:1;        	// 1
   Uint16 IIN_OC_FAULT:1;        	// 2
   Uint16 UNIT_OFF_FOR_LOW_INPUT_VOLTAGE:1;        	// 3   
   Uint16 VIN_UV_FAULT:1;        		// 4
   Uint16 VIN_UV_WARNING:1;        	// 5
   Uint16 VIN_OV_WARNING:1;        	// 6
   Uint16 VIN_OV_FAULT:1;        		// 7
};

union STATUS_INPUT_REG {
   Uint16              all;
   struct STATUS_INPUT_BITS bit;
};

//----------------------------------------------------
//	STATUS_FANS_1_2 register bit definitions */
struct STATUS_FANS_1_2_BITS {		// bits
   Uint16 AIR_FLOW_WARNING:1;		// 0
   Uint16 AIR_FLOW_FAULT:1;        	// 1
   Uint16 FAN2_SPEED_OVERRIDE:1;	// 2
   Uint16 FAN1_SPEED_OVERRIDE:1;    // 3   
   Uint16 FAN2_WARNING:1;        	// 4
   Uint16 FAN1_WARNING:1;        	// 5
   Uint16 FAN2_FAULT:1;        		// 6
   Uint16 FAN1_FAULT:1;        		// 7
};

union STATUS_FANS_1_2_REG {
   Uint16              all;
   struct STATUS_FANS_1_2_BITS bit;
};

//----------------------------------------------------
//	STATUS_FANS_3_4 register bit definitions */
struct STATUS_FANS_3_4_BITS {		// bits
   Uint16 rsvd:2;					// 0:1
   Uint16 FAN4_SPEED_OVERRIDE:1;	// 2
   Uint16 FAN3_SPEED_OVERRIDE:1;    // 3   
   Uint16 FAN4_WARNING:1;        	// 4
   Uint16 FAN3_WARNING:1;        	// 5
   Uint16 FAN4_FAULT:1;        		// 6
   Uint16 FAN3_FAULT:1;        		// 7
};

union STATUS_FANS_3_4_REG {
   Uint16              all;
   struct STATUS_FANS_3_4_BITS bit;
};

//----------------------------------------------------
//	STATUS_OTHER register bit definitions */
struct STATUS_OTHER_BITS {		// bits
   Uint16 rsvd1:1;						// 0
   Uint16 OUTPUT_OR_DEVICE_FAULT:1;     // 1
   Uint16 INPUTB_OR_DEVICE_FAULT:1;		// 2
   Uint16 INPUTA_OR_DEVICE_FAULT:1;  	// 3   
   Uint16 INPUTB_FUSE_FAULT:1;        	// 4
   Uint16 INPUTA_FUSE_FAULT:1;        	// 5
   Uint16 rsvd2:2;        				// 6:7
};

union STATUS_OTHER_REG {
   Uint16              all;
   struct STATUS_OTHER_BITS bit;
};

//----------------------------------------------------
//	STATUS registers */
struct STATUS_REGS {
   union  STATUS_WORD_REG			StatusWord; 
   union  STATUS_VOUT_REG			StatusVout; 
   union  STATUS_IOUT_REG			StatusIout;
   union  STATUS_TEMPERATURE_REG	StatusTemperature;
   union  STATUS_CML_REG     		StatusCml;
   union  STATUS_INPUT_REG     		StatusInput;
   union  STATUS_FANS_1_2_REG     	StatusFans12;
   union  STATUS_FANS_3_4_REG     	StatusFans34;
   union  STATUS_OTHER_REG			StatusOther;
};

//---------------------------------------------------------------------------
// Status Registers External References & Function Declarations:
//


/*------------------------------------------------------------------------------
ISR for the XINT1 interrupt triggered from GPIO2 (Alert line) 
------------------------------------------------------------------------------*/
interrupt void xint1_isr(void);

#endif
