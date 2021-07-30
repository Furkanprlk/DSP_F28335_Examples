/******************************************************************************
* FILE PURPOSE: This file contains chEst pilot tracking filter coefficients
*******************************************************************************
*
* FILE NAME: phy_ofdmchEstFirTracking.c
*
* DESCRIPTION: This file contains contains tracking filter coefficients
*               to update the chest every symbol
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 03/10/2013 JKunduru    Written
*
*
*
*******************************************************************************/
#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_ofdmchEstFirTracking,   "sunPhyTable");
#pragma DATA_ALIGN(PHY_ofdmchEstFirTracking,   2)

const SINT16 PHY_ofdmchEstFirTracking[3][3*2*(2*PHY_OFDM_CHFIR_TR_ODD_SIZE + PHY_OFDM_CHFIR_TR_EVEN_SIZE) + 4] =
{
{
/* begin FIR */
0,	0,
0,	0,
23178,	0,
-2585,	8520,
2941,	1965,

/* begin FIR */
0,	0,
-2479,	-8173,
15835,	0,
-3071,	10123,
1620,	1082,

/* begin FIR */
1400,	-935,
-2914,	-9605,
15557,	0,
-2914,	9605,
1400,	935,

/* begin FIR */
1620,	-1082,
-3071,	-10123,
15835,	0,
-2479,	8173,
0,	0,

/* begin FIR */
2941,	-1965,
-2585,	-8520,
23178,	0,
0,	0,
0,	0,

/* begin FIR */
0,	0,
9864,	-13300,
8501,	11462,
-1660,	594,

/* begin FIR */
-2040,	-730,
8754,	-11804,
8754,	11804,
-2040,	730,

/* begin FIR */
-1660,	-594,
8501,	-11462,
9864,	13300,
0,	0,

/* ForgetFactors 0.1, 0.9*/
3277,	3277,
29491,  29491,
},
{
/* begin FIR */
0,	0,
0,	0,
27410,	0,
-2406,	7931,
3307,	2210,

/* begin FIR */
0,	0,
-2272,	-7491,
16334,	0,
-3468,	11434,
2151,	1437,

/* begin FIR */
1644,	-1098,
-3116,	-10271,
15695,	0,
-3116,	10271,
1644,	1098,

/* begin FIR */
2151,	-1437,
-3468,	-11434,
16334,	0,
-2272,	7491,
0,	0,

/* begin FIR */
3307,	-2210,
-2406,	-7931,
27410,	0,
0,	0,
0,	0,

/* begin FIR */
0,	0,
10352,	-13958,
9031,	12177,
-912,	326,

/* begin FIR */
-1109,	-397,
9359,	-12620,
9359,	12620,
-1109,	397,

/* begin FIR */
-912,	-326,
9031,	-12177,
10352,	13958,
0,	0,

/* ForgetFactors 0.2, 0.8*/
6554,	6554,
26214, 26214,
},
{
/* begin FIR */
0,	0,
0,	0,
29711,	0,
-1607,	5299,
2339,	1563,

/* begin FIR */
0,	0,
-1803,	-5945,
17466,	0,
-3834,	12639,
3236,	2162,

/* begin FIR */
2126,	-1421,
-3199,	-10546,
15957,	0,
-3199,	10546,
2126,	1421,

/* begin FIR */
3236,	-2162,
-3834,	-12639,
17466,	0,
-1803,	5945,
0,	0,

/* begin FIR */
2339,	-1563,
-1607,	-5299,
29711,	0,
0,	0,
0,	0,

/* begin FIR */
0,	0,
9460,	-12755,
10734,	14474,
738,	-264,

/* begin FIR */
629,	225,
10243,	-13812,
10243,	13812,
629,	-225,

/* begin FIR */
738,	264,
10734,	-14474,
9460,	12755,
0,	0,

/* ForgetFactors 0.4, 0.6*/
13107,  13107,
19661,	19661,

},
};

#if 0
const SINT16 PHY_ofdmChFirForgetFact[3][4] =
{
{
6554,	6554,
26214,  26214,
},
{
19661,	19661,
13108, 13108,
},
{
26214,  26214,
6554,	6554,
}
};

#endif
