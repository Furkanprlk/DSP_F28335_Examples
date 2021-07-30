#ifndef SMO_CONST_CLA_H_
#define SMO_CONST_CLA_H_

typedef struct 	{ float32  Rs; 				// Input: Stator resistance (ohm) 
			      float32  Ls;				// Input: Stator inductance (H) 	  			      
				  float32  Ib; 				// Input: Base phase current (amp) 
				  float32  Vb;				// Input: Base phase voltage (volt) 
				  float32  Ts;				// Input: Sampling period in sec 
			      float32  Fsmopos;			// Output: constant using in observed current calculation 
			      float32  Gsmopos;			// Output: constant using in observed current calculation 
				} SMO_CONST_CLA;

#define SMO_CONST_CLA_MACRO(v)								\
														    \
	v.Fsmopos = CLAexp((-v.Rs/v.Ls)*(v.Ts));				\
	v.Gsmopos = (v.Vb/v.Ib)*(1/v.Rs)*(1-v.Fsmopos);

#define SMO_CONST_INIT(v)			\
    v.Rs=0; 						\
    v.Ls=0;					  		\
	v.Ib=0; 						\
	v.Vb=0;							\
	v.Ts=0;							\
	v.Fsmopos=0;			 		\
	v.Gsmopos=0;	
					
#endif /*SMP_CONST_H_*/
