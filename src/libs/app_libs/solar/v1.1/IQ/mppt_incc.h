#ifndef _mppt_incc_H_
#define _mppt_incc_H_

typedef struct {  	_iq  Ipv;
				  _iq  Vpv;
				  _iq  IpvH;
				  _iq  IpvL;
				  _iq  VpvH;
				  _iq  VpvL;
				  _iq  MaxVolt;
				  _iq  MinVolt;
				  _iq  Stepsize;
				  _iq  VmppOut;
				  // internal variables
				  _iq  Cond;
				  _iq  IncCond;
				  _iq  DeltaV;
				  _iq  DeltaI;
				  _iq  VpvOld;
				  _iq  IpvOld;
				  Uint16 mppt_enable;
				  Uint16 mppt_first;
				  } mppt_incc;
typedef mppt_incc *mppt_incc_handle;

//-----------------------------------------------------------------------------
//Default initalizer for the MPPT INCC object.
//-----------------------------------------------------------------------------                     
#define mppt_incc_DEFAULTS { _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(1.65),	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           1,			\
                           1,			\
                           }
                           
//------------------------------------------------------------------------------
// 	MPPT INCC Macro Definition
//------------------------------------------------------------------------------

#define mppt_incc_MACRO(v)														\
if (v.mppt_enable==1)															\
{						/*MPPT mode enable*/									\
	if (v.mppt_first == 1)														\
	{																			\
		v.VmppOut= v.Vpv - _IQ24(0.05);											\
    	v.VpvOld=v.Vpv;															\
    	v.IpvOld=v.Ipv;															\
		v.mppt_first=0;															\
	}                                                                       	\
	else 																		\
	{																			\
		v.DeltaV = v.Vpv-v.VpvOld ; 				/* PV voltage change */		\
    	v.DeltaI = v.Ipv-v.IpvOld ; 				/* PV current change */		\
   		if(v.DeltaV <v.VpvH && v.DeltaV >-v.VpvL )  /* Tolerence limits PV Voaltge Variation */	\
    	v.DeltaV= 0;															\
   		if(v.DeltaI <v.IpvH && v.DeltaI >-v.IpvL )  /* Tolerence limits PV current Variation */	\
    	v.DeltaI = 0;															\
    	if(v.DeltaV == 0)    						/* DeltaV=0 */				\
		{																		\
			if(v.DeltaI !=0 )    					/* dI=0 operating at MPP */	\
			{																	\
				if ( v.DeltaI > 0 )  				/* climbing towards MPP */	\
				{v.VmppOut=v.Vpv+v.Stepsize;}	/* Increment Vref */		\
				else															\
				{v.VmppOut=v.Vpv-v.Stepsize;} 	 /* Decrement Vref */		\
			}																	\
		}																		\
    	else  																	\
		{																		\
    	 	v.Cond = _IQdiv(v.Ipv, v.Vpv);	/*Cond =-(v.Ipv<<10)/v.Vpv;*/		\
    	 	v.IncCond = _IQdiv(v.DeltaI, v.DeltaV);	/*IncCond =(DeltaI<<10)/DeltaV;*/		\
       		if (v.IncCond != v.Cond)				/* Operating at MPP */		\
			{																	\
				if (v.IncCond > (-v.Cond))				/* left of MPP */		\
				{																\
				v.VmppOut=v.Vpv+v.Stepsize;		/* change Vref */			\
				}																\
				else							/* Right of MPP */				\
				{																\
				v.VmppOut=v.Vpv-v.Stepsize;		/* change Vref */			\
				}																\
        	}																	\
		}																		\
	/*	if (v.VmppOut<v.MinVolt) v.VmppOut=v.MinVolt;	 Min. MPP Voltage	*/	\
	/*	if (v.VmppOut>v.MaxVolt) v.VmppOut=v.MaxVolt; 	 Max. MPP Voltage	*/	\
		v.VpvOld = v.Vpv;														\
		v.IpvOld = v.Ipv;														\
	}																			\
}
#endif /*mppt_INCC_H_*/
