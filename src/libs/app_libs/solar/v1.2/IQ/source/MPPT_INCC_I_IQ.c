#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void MPPT_INCC_I_IQ_init(MPPT_INCC_I_IQ *v)
{
	v->Ipv=_IQ(0.0);
	v->Vpv=_IQ(0.0);
	v->IpvH=_IQ(1.65);
	v->IpvL=_IQ(0.0);
	v->VpvH=_IQ(0.0);
	v->VpvL=_IQ(0.0);
	v->MaxI=_IQ(0.0);
	v->MinI=_IQ(0.0);
	v->Stepsize=_IQ(0.0);
	v->ImppOut=_IQ(0.0);
	v->Cond=_IQ(0.0);
	v->IncCond=_IQ(0.0);
	v->DeltaV=_IQ(0.0);
	v->DeltaI=_IQ(0.0);
	v->VpvOld=_IQ(0.0);
	v->IpvOld=_IQ(0.0);
	v->StepFirst=_IQ(0.02);
	v->mppt_enable=1;
	v->mppt_first=1;
}

//*********** Function Definition ********//
void MPPT_INCC_I_IQ_FUNC(MPPT_INCC_I_IQ *v)
{
	if (v->mppt_enable==1)
	{	/*MPPT mode enable*/
		if (v->mppt_first == 1)
		{
			v->ImppOut=v->Ipv+v->StepFirst;
	    	v->VpvOld=v->Vpv;
	    	v->IpvOld=v->Ipv;
			v->mppt_first=0;
		}
		else
		{
			v->DeltaV = v->Vpv-v->VpvOld ; 						/* PV voltage change */
	    	v->DeltaI = v->Ipv-v->IpvOld ; 						/* PV current change */
//	   		if(v->DeltaV < v->VpvH && v->DeltaV > -v->VpvL )	/* Tolerence limits PV Voaltge Variation */
//	    	v->DeltaV= 0;
//	   		if(v->DeltaI < v->IpvH && v->DeltaI > -v->IpvL )  	/* Tolerence limits PV current Variation */
//	    	v->DeltaI = 0;
	    	if(v->DeltaV >= 0)    								/* DeltaV=0 */
			{
				if(v->DeltaI !=0 )    							/* dI=0 operating at MPP */
				{
					if ( v->DeltaI > 0 )  						/* climbing towards MPP */
					{v->ImppOut=v->Ipv-v->Stepsize;}			/* Increment Vref */
					else
					{v->ImppOut=v->Ipv+v->Stepsize;} 	 		/* Decrement Vref */
				}
			}
	    	else
			{
	    	 	v->Cond = _IQdiv(v->Ipv, v->Vpv);			/*Cond =-(v->Ipv<<10)/v->Vpv;*/
	    	 	v->IncCond = _IQdiv(v->DeltaI, v->DeltaV);	/*IncCond =(DeltaI<<10)/DeltaV;*/
	       		if (v->IncCond != v->Cond)					/* Operating at MPP */
				{
					if (v->IncCond > (-v->Cond))			/* left of MPP */
					{
					v->ImppOut=v->Ipv-v->Stepsize;			/* change Vref */
					}
					else									/* Right of MPP */
					{
					v->ImppOut=v->Ipv+v->Stepsize;			/* change Vref */
					}
	        	}
			}
		    v->ImppOut=(v->ImppOut<v->MinI)?v->MinI: v->ImppOut;	 /*Min. MPP Current */
			v->ImppOut=(v->ImppOut>v->MaxI)?v->MaxI: v->ImppOut; 	 /*Max. MPP Current	*/
			v->VpvOld = v->Vpv;
			v->IpvOld = v->Ipv;
		}
	}
}

