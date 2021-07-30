#ifndef __iPARK_CLA_H__
#define __iPARK_CLA_H__

typedef struct  {
				  float  d;		    	// Input : d 
				  float  q;	    		// Input : q
				  float  sine;			// Input : sin(theta) 	
				  float  cos;			// Input : cos(theta)
				  float  alpha;			// Output  : alpha
				  float  beta;		    // Output  : beta
				}iPARK_CLA;
				
#define iPARK_CLA_MACRO(v)													\
	v.alpha =v.d * v.cos - v.q*v.sine;										\
	v.beta  =v.d * v.sine + v.q*v.cos;

#define iPARK_CLA_INIT(v)													\
	v.cos=0.0;																\
	v.sine=0.0;																\
	v.d=0.0;																\
	v.q=0.0;																\
	v.alpha=0.0;															\
	v.beta=0.0;															
#endif


