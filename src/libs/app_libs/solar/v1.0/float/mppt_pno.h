#ifndef _mppt_pno_H_
#define _mppt_pno_H_

typedef struct {  	float  Ipv;
				  float  Vpv;
				  float  DeltaPmin;
				  float  MaxVolt;
				  float  MinVolt;
				  float  Stepsize;
				  float  VmppOut;
				  // internal variables
				  float  DeltaP;
				  float  PanelPower;
				  float  PanelPower_Prev;
				  Uint16 mppt_enable;
				  Uint16 mppt_first;
				  } mppt_pno;

typedef mppt_pno *mppt_pno_handle;

//-----------------------------------------------------------------------------
//Default initalizer for the MPPT pno object.
//-----------------------------------------------------------------------------                     
#define mppt_pno_DEFAULTS { (0.0), 	\
                           (0.0), 	\
                           (0.00001),	\
                           (0.9), 	\
                           (0.0), 	\
                           (0.002), 	\
                           (0.0), 	\
                           (0.0),	\
                           (0.0),	\
                           (0.0),	\
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
		v.VmppOut= v.Vpv - (0.02);									\
		v.mppt_first=0;													\
		v.PanelPower_Prev=v.PanelPower;									\
	}																	\
	else																\
	{																	\
		v.PanelPower= (v.Vpv*v.Ipv);								\
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

