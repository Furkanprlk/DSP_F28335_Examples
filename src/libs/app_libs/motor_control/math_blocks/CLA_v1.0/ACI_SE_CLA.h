#ifndef __ACI_SE_CLA_H__
#define __ACI_SE_CLA_H__

typedef struct { float  	IQsS;  			// Input: Stationary q-axis stator current  
				 float  	PsiDrS;  		// Input: Stationary d-axis rotor flux  
				 float  	IDsS;			// Input: Stationary d-axis stator current  
				 float  	PsiQrS;			// Input: Stationary q-axis rotor flux  		
		 	 	 float  	K1;				// Parameter: Constant using in speed computation  
                 float  	SquaredPsi; 	// Variable: Squared rotor flux    
    			 float  	ThetaFlux;  	// Input: Rotor flux angle      		  
		 	 	 float 		K2;				// Parameter: Constant using in differentiator (Q21) - independently with global Q 
    			 float  	OldThetaFlux; 	// Variable: Previous rotor flux angle      		  
		 	 	 float  	K3;				// Parameter: Constant using in low-pass filter   
		 	 	 float 		WPsi;			// Variable: Synchronous rotor flux speed (Q21) - independently with global Q 
		 	 	 float  	K4;				// Parameter: Constant using in low-pass filter  
		 	 	 float  	WrHat;			// Output: Estimated speed in per unit  
				 float 		BaseRpm; 		// Parameter: Base rpm speed (Q0) - independently with global Q  		 	 	  
		 	 	 float 		WrHatRpm;		// Output: Estimated speed in rpm (Q0) - independently with global Q
		 	 	 float   	WSlip;			// Variable: Slip
		 	 	 float		WSyn;			// Variable: Synchronous speed
				 } ACI_SE_CLA;	            
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																			

#define DIFF_MAX_LIMIT  	(0.80)
#define DIFF_MIN_LIMIT  	(0.20)

/*------------------------------------------------------------------------------
	ACI Speed Estimator MACRO Definition 
------------------------------------------------------------------------------ */


#define ACI_SE_CLA_MACRO(v)														\
																				\
/*  Slip computation */															\
	v.SquaredPsi =(v.PsiDrS*v.PsiDrS)+(v.PsiQrS*v.PsiQrS);						\
																				\
	v.WSlip= (v.K1*((v.PsiDrS*v.IQsS) - (v.PsiQrS*v.IDsS)));					\
	v.WSlip= (v.WSlip/v.SquaredPsi);											\
																				\
/*	Synchronous speed computation	*/											\
	if ((v.ThetaFlux < DIFF_MAX_LIMIT)&&(v.ThetaFlux > DIFF_MIN_LIMIT))			\
		  v.WSyn = (v.K2*(v.ThetaFlux - v.OldThetaFlux));						\
	else  v.WSyn = v.WPsi;														\
																				\
/* low-pass filter */															\
	v.WPsi = (v.K3*v.WPsi) + (v.K4*v.WSyn);										\
																				\
/*  */																			\
	v.OldThetaFlux = v.ThetaFlux;												\
	v.WrHat = v.WPsi - v.WSlip;													\
																				\
/* Limit the estimated speed between -1 and 1 per-unit */						\
	v.WrHat=__mminf32(v.WrHat,(1.0));											\
	v.WrHat=__mmaxf32(v.WrHat,(-1.0));											\
																				\
/*  */																			\
	v.WrHatRpm = (v.BaseRpm*v.WrHat);	

#define ACI_SE_CLA_INIT(v)	\
	 v.IQsS=0;  			\
	 v.PsiDrS=0;  			\
	 v.IDsS=0;				\
	 v.PsiQrS=0;			\
 	 v.K1=0;				\
     v.SquaredPsi=0; 	 	\
	 v.ThetaFlux=0;  		\
 	 v.K2=0;				\
	 v.OldThetaFlux=0; 	   	\
 	 v.K3=0;				\
 	 v.WPsi=0;			 	\
 	 v.K4=0;				\
 	 v.WrHat=0;				\
	 v.BaseRpm=0; 		 	\
 	 v.WrHatRpm=0;			\
 	 v.WSlip=0;				\
 	 v.WSyn=0;				\


#endif // __ACI_SE_H__
