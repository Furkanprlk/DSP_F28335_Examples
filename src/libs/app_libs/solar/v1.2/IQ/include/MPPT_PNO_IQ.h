#ifndef MPPT_PNO_IQ_H_
#define MPPT_PNO_IQ_H_

//*********** Structure Definition ********//
typedef struct {
	int32  Ipv;
	int32  Vpv;
	int32  DeltaPmin;
	int32  MaxVolt;
	int32  MinVolt;
	int32  Stepsize;
	int32  VmppOut;
	int32  DeltaP;
	int32  PanelPower;
	int32  PanelPower_Prev;
	int16 mppt_enable;
	int16 mppt_first;
} MPPT_PNO_IQ;

typedef MPPT_PNO_IQ *MPPT_PNO_handle;

//*********** Function Declarations *******//
void MPPT_PNO_IQ_init(MPPT_PNO_IQ *v);
void MPPT_PNO_IQ_FUNC(MPPT_PNO_IQ *v);

//*********** Macro Definition ***********//
#define MPPT_PNO_IQ_MACRO(v)						\
if (v.mppt_enable==1)								\
{													\
	if (v.mppt_first == 1)							\
	{												\
		v.VmppOut= v.Vpv - _IQ(0.02);				\
		v.mppt_first=0;								\
		v.PanelPower_Prev=v.PanelPower;				\
	}												\
	else											\
	{												\
		v.PanelPower= _IQmpy(v.Vpv,v.Ipv);			\
		v.DeltaP=v.PanelPower-v.PanelPower_Prev;	\
		if (v.DeltaP > v.DeltaPmin)					\
		{											\
			v.VmppOut=v.Vpv+v.Stepsize;				\
		}											\
		else										\
		{											\
			if (v.DeltaP < -v.DeltaPmin)			\
			{										\
				v.Stepsize=-v.Stepsize;				\
				v.VmppOut=v.Vpv+v.Stepsize;			\
			}										\
		}											\
		v.PanelPower_Prev = v.PanelPower;			\
	}												\
	if(v.VmppOut< v.MinVolt) v.VmppOut = v.MinVolt;	\
	if(v.VmppOut> v.MaxVolt) v.VmppOut= v.MaxVolt;	\
}	


#endif /*MPPT_PNO_IQ_H_*/
