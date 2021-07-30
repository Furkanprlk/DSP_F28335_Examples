#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void MPPT_PNO_IQ_init(MPPT_PNO_IQ *v)
{
	v->Ipv=_IQ(0.0);
	v->Vpv=_IQ(0.0);
	v->DeltaPmin=_IQ(0.00001);
	v->MaxVolt=_IQ(0.9);
	v->MinVolt=_IQ(0.0);
	v->Stepsize=_IQ(0.002);
	v->VmppOut=_IQ(0.0);
	v->DeltaP=_IQ(0.0);
	v->PanelPower=_IQ(0.0);
	v->PanelPower_Prev=_IQ(0.0);
	v->mppt_enable=1;
	v->mppt_first=1;
}

//*********** Function Definition ********//
void MPPT_PNO_IQ_FUNC(MPPT_PNO_IQ *v)
{
	if (v->mppt_enable==1)
	{
		if (v->mppt_first == 1)
		{
			v->VmppOut= v->Vpv - _IQ(0.02);
			v->mppt_first=0;
			v->PanelPower_Prev=v->PanelPower;
		}
		else
		{
			v->PanelPower= _IQmpy(v->Vpv,v->Ipv);
			v->DeltaP=v->PanelPower-v->PanelPower_Prev;
			if (v->DeltaP > v->DeltaPmin)
			{
				v->VmppOut=v->Vpv+v->Stepsize;
			}
			else
			{
				if (v->DeltaP < -v->DeltaPmin)
				{
					v->Stepsize=-v->Stepsize;
					v->VmppOut=v->Vpv+v->Stepsize;
				}
			}
			v->PanelPower_Prev = v->PanelPower;
		}
		if(v->VmppOut < v->MinVolt) v->VmppOut = v->MinVolt;
		if(v->VmppOut > v->MaxVolt) v->VmppOut = v->MaxVolt;
	}
}
