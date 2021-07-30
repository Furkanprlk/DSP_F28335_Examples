#ifndef __SVGEN_CLA_H__
#define __SVGEN_CLA_H__

typedef struct 	{ float  Ualpha; 			// Input: reference alpha-axis phase voltage 
				  float  Ubeta;			// Input: reference beta-axis phase voltage 
				  float  Ta;				// Output: reference phase-a switching function		
				  float  Tb;				// Output: reference phase-b switching function 
				  float  Tc;				// Output: reference phase-c switching function
				  float  tmp1;			// Variable: temp variable
				  float  tmp2;			// Variable: temp variable
				  float  tmp3;			// Variable: temp variable
				  float VecSector;		// Space vector sector
				} SVGEN_CLA;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				

 

/*------------------------------------------------------------------------------
	Space Vector  Generator (SVGEN) Macro Definition
------------------------------------------------------------------------------*/


#define SVGEN_CLA_MACRO(v)														\
	v.tmp1= v.Ubeta;															\
	v.tmp2= v.Ubeta*0.5 + ((0.866)*v.Ualpha);									\
    v.tmp3= v.tmp2 - v.tmp1;													\
																				\
	v.VecSector=3;																\
	v.VecSector=(v.tmp2> 0)?( v.VecSector-1):v.VecSector;						\
	v.VecSector=(v.tmp3> 0)?( v.VecSector-1):v.VecSector;						\
	v.VecSector=(v.tmp1< 0)?(7-v.VecSector) :v.VecSector;						\
																				\
	if     (v.VecSector==1 || v.VecSector==4)                                   \
      {     v.Ta= v.tmp2; 														\
      		v.Tb= v.tmp1-v.tmp3; 												\
      		v.Tc=-v.tmp2;														\
      }								    										\
   																				\
    else if(v.VecSector==2 || v.VecSector==5)                                   \
      {     v.Ta= v.tmp3+v.tmp2; 												\
      		v.Tb= v.tmp1; 														\
      		v.Tc=-v.tmp1;														\
      }																	   		\
   																				\
    else                                                                        \
      {     v.Ta= v.tmp3; 														\
      		v.Tb=-v.tmp3; 														\
      		v.Tc=-(v.tmp1+v.tmp2);												\
      }																	   		\
		
#define SVGEN_CLA_INIT_MACRO(v)	\
	  v.  Ualpha=0; 		\
	  v.  Ubeta=0;			\
	  v.  Ta=0;				\
	  v.  Tb=0;				\
	  v.  Tc=0;				\
	  v.  tmp1=0;			\
	  v.  tmp2=0;			\
	  v.  tmp3=0;			\
	  v. VecSector=0;		\

#endif // __SVGEN_H__
