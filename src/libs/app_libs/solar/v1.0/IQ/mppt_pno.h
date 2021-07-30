#ifndef _mppt_pno_H_
#define _mppt_pno_H_

typedef struct {  	_iq  Ipv;
				  _iq  Vpv;
				  _iq  DeltaPmin;
				  _iq  MaxVolt;
				  _iq  MinVolt;
				  _iq  Stepsize;
				  _iq  VmppOut;
				  // internal variables
				  _iq  DeltaP;
				  _iq  PanelPower;
				  _iq  PanelPower_Prev;
				  Uint16 mppt_enable;
				  Uint16 mppt_first;
				  } mppt_pno;

typedef mppt_pno *mppt_pno_handle;

//-----------------------------------------------------------------------------
//Default initalizer for the MPPT pno object.
//-----------------------------------------------------------------------------                     
#define mppt_pno_DEFAULTS { _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.00001),	\
                           _IQ(0.9), 	\
                           _IQ(0.0), 	\
                           _IQ(0.002), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           1,			\
                           1,			\
                           }
                           
//------------------------------------------------------------------------------
// 	MPPT pno Macro Definition
//------------------------------------------------------------------------------

#define mppt_pno_MACRO(v)												\
if (v.mppt_enable==1)													\
{																		\
	if (v.mppt_first == 1)												\
	{																	\
		v.VmppOut= v.Vpv - _IQ(0.02);									\
		v.mppt_first=0;													\
		v.PanelPower_Prev=v.PanelPower;									\
	}																	\
	else																\
	{																	\
		v.PanelPower= _IQmpy(v.Vpv,v.Ipv);								\
		v.DeltaP=v.PanelPower-v.PanelPower_Prev;						\
		if (v.DeltaP > v.DeltaPmin)										\
		{																\
			v.VmppOut=v.Vpv+v.Stepsize;								\
		}																\
		else															\
		{																\
			if (v.DeltaP < -v.DeltaPmin)								\
			{															\
				v.Stepsize=-v.Stepsize;									\
				v.VmppOut=v.Vpv+v.Stepsize;							\
			}															\
		}																\
		v.PanelPower_Prev = v.PanelPower;								\
	}																	\
	if(v.VmppOut< v.MinVolt) v.VmppOut = v.MinVolt;					\
	if(v.VmppOut> v.MaxVolt) v.VmppOut= v.MaxVolt;					\
}	
#endif /*mppt_pno_H_*/

