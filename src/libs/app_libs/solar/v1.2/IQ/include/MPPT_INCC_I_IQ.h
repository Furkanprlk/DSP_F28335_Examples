#ifndef MPPT_INCC_I_IQ_H_
#define MPPT_INCC_I_IQ_H_

//*********** Structure Definition ********//
typedef struct{
	int32  Ipv;
	int32  Vpv;
	int32  IpvH;
	int32  IpvL;
	int32  VpvH;
	int32  VpvL;
	int32  MaxI;
	int32  MinI;
	int32  Stepsize;
	int32  ImppOut;
	// internal variables
	int32  Cond;
	int32  IncCond;
	int32  DeltaV;
	int32  DeltaI;
	int32  VpvOld;
	int32  IpvOld;
	int32  StepFirst;
	int16 mppt_enable;
	int16 mppt_first;
} MPPT_INCC_I_IQ;

typedef MPPT_INCC_I_IQ *MPPT_INCC_I_handle;

//*********** Function Declarations *******//
void MPPT_INCC_I_IQ_init(MPPT_INCC_I_IQ *v);
void MPPT_INCC_I_IQ_FUNC(MPPT_INCC_I_IQ *v);

//*********** Macro Definition ***********//
#define MPPT_INCC_I_IQ_MACRO(v)																		\
if (v.mppt_enable==1)																				\
{	/*MPPT mode enable*/																			\
	if (v.mppt_first == 1)																			\
	{																								\
		v.ImppOut= v.Ipv + v.StepFirst;																\
    	v.VpvOld=v.Vpv;																				\
    	v.IpvOld=v.Ipv;																				\
		v.mppt_first=0;																				\
	}                                   															\
	else 																							\
	{																								\
		v.DeltaV = v.Vpv-v.VpvOld ; 				/* PV voltage change */							\
    	v.DeltaI = v.Ipv-v.IpvOld ; 				/* PV current change */							\
   		/*if(v.DeltaV <v.VpvH && v.DeltaV >-v.VpvL )*/  /* Tolerence limits PV Voaltge Variation */	\
    	/*v.DeltaV= 0;*/																			\
   		/*if(v.DeltaI <v.IpvH && v.DeltaI >-v.IpvL )*/  /* Tolerence limits PV current Variation */	\
    	/*v.DeltaI = 0;*/																			\
    	if(v.DeltaV >= 0)    						/* DeltaV=0 */									\
		{																							\
			if(v.DeltaI !=0 )    					/* dI=0 operating at MPP */						\
			{																						\
				if ( v.DeltaI > 0 )  				/* climbing towards MPP */						\
				{v.ImppOut=v.Ipv-v.Stepsize;}		/* Increment Vref */							\
				else																				\
				{v.ImppOut=v.Ipv+v.Stepsize;} 	 	/* Decrement Vref */							\
			}																						\
		}																							\
    	else  																						\
		{																							\
    	 	v.Cond = _IQdiv(v.Ipv, v.Vpv);				/*Cond =-(v.Ipv<<10)/v.Vpv;*/				\
    	 	v.IncCond = _IQdiv(v.DeltaI, v.DeltaV);		/*IncCond =(DeltaI<<10)/DeltaV;*/			\
       		if (v.IncCond != v.Cond)					/* Operating at MPP */						\
			{																						\
				if (v.IncCond > (-v.Cond))				/* left of MPP */							\
				{																					\
				v.ImppOut=v.Ipv-v.Stepsize;				/* change Vref */							\
				}																					\
				else									/* Right of MPP */							\
				{																					\
				v.ImppOut=v.Ipv+v.Stepsize;				/* change Vref */							\
				}																					\
        	}																						\
		}																							\
	    v.ImppOut=(v.ImppOut<v.MinI)?v.MinI: v.ImppOut;	 /*Min. MPP Current */  					\
		v.ImppOut=(v.ImppOut>v.MaxI)?v.MaxI: v.ImppOut;  /*Max. MPP Current	*/						\
		v.VpvOld = v.Vpv;																			\
		v.IpvOld = v.Ipv;																			\
	}																								\
}


#endif /*MPPT_INCC_I_IQ_H_*/
