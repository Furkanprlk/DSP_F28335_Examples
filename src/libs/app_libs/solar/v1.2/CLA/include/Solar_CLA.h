#ifndef SOLAR_CLA_H
#define SOLAR_CLA_H

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int             	int16;
typedef long            	int32;
//typedef long long			int64;
//typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif
#endif

#ifndef _TI_STD_TYPES
#define _TI_STD_TYPES
typedef int             Int;
typedef unsigned        Uns;
typedef char            Char;
typedef char            *String;
typedef void            *Ptr;
typedef unsigned short	Bool;

typedef unsigned long   Uint32;
typedef unsigned int    Uint16;
typedef unsigned char   Uint8;

typedef long            Int32;
typedef int             Int16;
typedef char            Int8;
#endif

#include "CLAmath.h"
#include <stdint.h>

#include "ABC_DQ0_NEG_CLA.h"
#include "ABC_DQ0_POS_CLA.h"
#include "CLARKE_CLA.h"
#include "CNTL_2P2Z_CLA.h"
#include "CNTL_3P3Z_CLA.h"
#include "CNTL_PI_CLA.h"
#include "DLOG_1CH_CLA.h"
#include "DLOG_4CH_CLA.h"
#include "DQ0_ABC_CLA.h"
#include "iCLARKE_CLA.h"
#include "iPARK_CLA.h"
#include "MATH_EMAVG_CLA.h"
#include "MPPT_INCC_CLA.h"
#include "MPPT_INCC_I_CLA.h"
#include "MPPT_PNO_CLA.h"
#include "NOTCH_FLTR_CLA.h"
#include "PARK_CLA.h"
#include "PID_GRANDO_CLA.h"
#include "RAMPGEN_CLA.h"
#include "SINEANALYZER_DIFF_CLA.h"
#include "SINEANALYZER_DIFF_wPWR_CLA.h"
#include "SPLL_1ph_CLA.h"
#include "SPLL_1ph_SOGI_CLA.h"
#include "SPLL_3PH_SRF_CLA.h"
#include "SPLL_3PH_DDSRF_CLA.h"


#endif
