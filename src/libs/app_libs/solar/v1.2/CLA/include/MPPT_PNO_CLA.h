#ifndef MPPT_PNO_CLA_H_
#define MPPT_PNO_CLA_H_

//*********** Structure Definition ********//
typedef struct {
	float32  Ipv;
	float32  Vpv;
	float32  DeltaPmin;
	float32  MaxVolt;
	float32  MinVolt;
	float32  Stepsize;
	float32  VmppOut;
	float32  DeltaP;
	float32  PanelPower;
	float32  PanelPower_Prev;
	uint16_t mppt_first;
	uint16_t mppt_enable;
} MPPT_PNO_CLA;

typedef MPPT_PNO_CLA *mppt_pno_handle;

//*********** Function Declarations *******//
void MPPT_PNO_CLA_FUNC(MPPT_PNO_CLA *v);

//*********** Structure Init Macro *******//
#define MPPT_PNO_CLA_init(v)	\
	v.Ipv=0;					\
	v.Vpv=0;					\
	v.DeltaPmin=(0.00001);		\
	v.MaxVolt=(0.9);			\
	v.MinVolt=0;				\
	v.Stepsize=(0.002);			\
	v.VmppOut=0;				\
	v.DeltaP=0;					\
	v.PanelPower=0;				\
	v.PanelPower_Prev=0;		\
	v.mppt_enable=1;			\
	v.mppt_first=1;				\

//*********** Macro Definition ***********//
#define MPPT_PNO_CLA_MACRO(v)						\
if (v.mppt_enable==1)								\
{													\
	if (v.mppt_first == 1)							\
	{												\
		v.VmppOut= v.Vpv - (0.02);					\
		v.mppt_first=0;								\
		v.PanelPower_Prev=v.PanelPower;				\
	}												\
	else											\
	{												\
		v.PanelPower= (v.Vpv*v.Ipv);				\
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


#endif /*MPPT_PNO_CLA_H_*/
