#ifndef C28X_INSTASPIN_BLDC_LIB_H
#define C28X_INSTASPIN_BLDC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#define NULL	0
//-----------------------------------------------------------------------------
// Standard C28x Data Types
//-----------------------------------------------------------------------------
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                 int16;
typedef long                int32;
typedef long long           int64;
typedef unsigned int        Uint16;
typedef unsigned long       Uint32;
typedef unsigned long long  Uint64;
typedef float               float32;
typedef long double         float64;
#endif

//-----------------------------------------------------------------------------
// enumerations
//-----------------------------------------------------------------------------
typedef enum
{
	NO=0,
	YES=1
}Eintbool;

//-----------------------------------------------------------------------------
// Structure and object definitions
//-----------------------------------------------------------------------------
typedef struct
{
	int32		Vag;				// Internal: Vag input -- contains real Va + VaOffset --> referenced to ground (_iq)
	int32		Vbg;				// Internal: Vbg input -- contains real Vb + VbOffset --> referenced to ground (_iq)
	int32		Vcg;				// Internal: Vcg input -- contains real Vc + VcOffset --> referenced to ground (_iq)
	int32		Van;				// Internal: Va to neutral (_iq)
	int32		Vbn;				// Internal: Vb to neutral (_iq)
	int32		Vcn;				// Internal: Vc to neutral (_iq)
	int32		VaOffset;			// VaOffset (_iq)
	int32		VbOffset;			// VbOffset (_iq)
	int32		VcOffset;			// VcOffset (_iq)
	int32		Int_Threshold;		// Input: Integration threshold where a commutate happens (_iq)
	Eintbool	Vint_lockout;		// Internal: Flyback voltage lockout flag
	int32		*Vphase;			// Internal: Pointer to the Phase voltage to count	(_iq)
	int32		V_int;				// Output: Integrator	(_iq)
	Eintbool	Comm_Trig;			// Output:  Commutation trigger impulse		
	Uint16		State; 				// Input: Values 0 to 5
} INSTASPIN_BLDC;

typedef INSTASPIN_BLDC *H_INSTASPIN_BLDC;			//  Handle to object INSTASPIN_BLDC


//-----------------------------------------------------------------------------
// Default initalizers for objects.
//-----------------------------------------------------------------------------                     
#define INSTASPIN_BLDC_DEFAULTS	{ 0,\
								  0,\
								  0,\
								  0,\
								  0,\
								  NULL,\
								  0,\
								  YES,\
								  NO}
								  
//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------
void InstaSPIN_BLDC(H_INSTASPIN_BLDC i);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================

