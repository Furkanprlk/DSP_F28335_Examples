/* =================================================================================
File name:       SMOPOS_CONST.H                     
===================================================================================*/

typedef struct 	{ float  Rs; 				// Input: Stator resistance (ohm) 
			      float  Ls;				// Input: Stator inductance (H) 	  			      
				  float  Ib; 				// Input: Base phase current (amp) 
				  float  Vb;				// Input: Base phase voltage (volt) 
				  float  Ts;				// Input: Sampling period in sec 
			      float  Fsmopos;			// Output: constant using in observed current calculation 
			      float  Gsmopos;			// Output: constant using in observed current calculation 
				  
				} SMOPOS_CLA_CONST;
																																																																																																																																																																																																								
/*------------------------------------------------------------------------------
Prototypes for the functions in SMOPOS_CONST.C
------------------------------------------------------------------------------*/

#define SMOPOS_CLA_CONST_MACRO(v)						\
														\
	v.Fsmopos = CLAexp((-v.Rs/v.Ls)*(v.Ts));			\
	v.Gsmopos = (v.Vb/v.Ib)*(1/v.Rs)*(1-v.Fsmopos);







