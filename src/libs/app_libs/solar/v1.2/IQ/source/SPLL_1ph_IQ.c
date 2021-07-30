#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void SPLL_1ph_IQ_init(int Grid_freq, long DELTA_T, SPLL_1ph_IQ *spll_obj)
{
	spll_obj->Upd[0]=SPLL_Q(0.0);
	spll_obj->Upd[1]=SPLL_Q(0.0);
	spll_obj->Upd[2]=SPLL_Q(0.0);
	
	spll_obj->ynotch[0]=SPLL_Q(0.0);
	spll_obj->ynotch[1]=SPLL_Q(0.0);
	spll_obj->ynotch[2]=SPLL_Q(0.0);
	
	spll_obj->ylf[0]=SPLL_Q(0.0);
	spll_obj->ylf[1]=SPLL_Q(0.0);
	
	spll_obj->sin[0]=SPLL_Q(0.0);
	spll_obj->sin[1]=SPLL_Q(0.0);
	
	spll_obj->cos[0]=SPLL_Q(0.999);
	spll_obj->cos[1]=SPLL_Q(0.999);
	
	spll_obj->theta[0]=SPLL_Q(0.0);
	spll_obj->theta[1]=SPLL_Q(0.0);
	
	spll_obj->wn=SPLL_Q(2*3.14*Grid_freq);

	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=SPLL_Q(166.9743);
	spll_obj->lpf_coeff.B1_lf=SPLL_Q(-166.266);
	spll_obj->lpf_coeff.A1_lf=SPLL_Q(-1.0);
	
	spll_obj->delta_t=DELTA_T;  
}

//*********** Structure Coeff Update *****//
void SPLL_1ph_IQ_notch_coeff_update(float delta_T, float wn,float c2, float c1, SPLL_1ph_IQ *spll_obj)
{
	// Note c2<<c1 for the notch to work
	float x,y,z;
	x=(float)(2.0*c2*wn*delta_T);
	y=(float)(2.0*c1*wn*delta_T);
	z=(float)(wn*delta_T*wn*delta_T);

	spll_obj->notch_coeff.A1_notch=SPLL_Q(y-2);
	spll_obj->notch_coeff.A2_notch=SPLL_Q(z-y+1);
	spll_obj->notch_coeff.B0_notch=SPLL_Q(1.0);
	spll_obj->notch_coeff.B1_notch=SPLL_Q(x-2);
	spll_obj->notch_coeff.B2_notch=SPLL_Q(z-x+1);
}
	
//*********** Function Definition ********//
void SPLL_1ph_IQ_FUNC(SPLL_1ph_IQ *spll_obj)
{
	//-------------------//
	// Phase Detect 	 //
	//-------------------//
	
	spll_obj->Upd[0]=SPLL_Qmpy(spll_obj->AC_input,spll_obj->cos[1]);
	
	//-------------------//
	//Notch filter structure//
	//-------------------//
	
	spll_obj->ynotch[0]=-SPLL_Qmpy(spll_obj->notch_coeff.A1_notch,spll_obj->ynotch[1])-SPLL_Qmpy(spll_obj->notch_coeff.A2_notch,spll_obj->ynotch[2])+SPLL_Qmpy(spll_obj->notch_coeff.B0_notch,spll_obj->Upd[0])+SPLL_Qmpy(spll_obj->notch_coeff.B1_notch,spll_obj->Upd[1])+SPLL_Qmpy(spll_obj->notch_coeff.B2_notch,spll_obj->Upd[2]);
	
	// update the Upd array for future
	spll_obj->Upd[2]=spll_obj->Upd[1];
	spll_obj->Upd[1]=spll_obj->Upd[0];
	
	//---------------------------//
	// PI loop filter 			 //
	//---------------------------//
	
	spll_obj->ylf[0]=-SPLL_Qmpy(spll_obj->lpf_coeff.A1_lf,spll_obj->ylf[1])+SPLL_Qmpy(spll_obj->lpf_coeff.B0_lf,spll_obj->ynotch[0])+SPLL_Qmpy(spll_obj->lpf_coeff.B1_lf,spll_obj->ynotch[1]);
	
	//update array for future use
	spll_obj->ynotch[2]=spll_obj->ynotch[1];
	spll_obj->ynotch[1]=spll_obj->ynotch[0];
	
	spll_obj->ylf[1]=spll_obj->ylf[0];
	
	//------------------//
	// VCO              //
	//------------------//
	
	spll_obj->wo=spll_obj->wn+spll_obj->ylf[0];
	
	//integration process
	spll_obj->sin[0]=spll_obj->sin[1]+SPLL_Qmpy((SPLL_Qmpy(spll_obj->delta_t,spll_obj->wo)),spll_obj->cos[1]);
	spll_obj->cos[0]=spll_obj->cos[1]-SPLL_Qmpy((SPLL_Qmpy(spll_obj->delta_t,spll_obj->wo)),spll_obj->sin[1]);

	if(spll_obj->sin[0]>SPLL_Q(0.99))
		spll_obj->sin[0]=SPLL_Q(0.99);
	else if(spll_obj->sin[0]<SPLL_Q(-0.99))
		spll_obj->sin[0]=SPLL_Q(-0.99);
	
	if(spll_obj->cos[0]>SPLL_Q(0.99))
		spll_obj->cos[0]=SPLL_Q(0.99);
	else if(spll_obj->cos[0]<SPLL_Q(-0.99))
		spll_obj->cos[0]=SPLL_Q(-0.99);
	
	spll_obj->theta[0]=spll_obj->theta[1]+SPLL_Qmpy(SPLL_Qmpy(spll_obj->wo,SPLL_Q(0.159154943)),spll_obj->delta_t);
	
	if(spll_obj->sin[0]>SPLL_Q(0.0) && spll_obj->sin[1]<=SPLL_Q(0.0))
	{
		spll_obj->theta[0]=SPLL_Q(0.0);
	} 
	
	spll_obj->theta[1]=spll_obj->theta[0];
	
	spll_obj->sin[1]=spll_obj->sin[0];
	spll_obj->cos[1]=spll_obj->cos[0];
}

