#ifndef _SPLL_1ph_H_
#define _SPLL_1ph_H_

#define SPLL_Q _IQ21
#define SPLL_Qmpy _IQ21mpy

typedef struct{
	int32	B2_notch;
	int32	B1_notch;
	int32	B0_notch;
	int32	A2_notch;
	int32	A1_notch;
}SPLL_NOTCH_COEFF; 

typedef struct{
	int32	B1_lf;
	int32	B0_lf;
	int32	A1_lf;
}SPLL_LPF_COEFF;

typedef struct{
	int32	AC_input;
	int32	theta[2];
	int32	cos[2];
	int32	sin[2];
	int32   wo;
	int32	wn;
	
	SPLL_NOTCH_COEFF notch_coeff;
	SPLL_LPF_COEFF	 lpf_coeff;
		
	int32   Upd[3];
	int32	ynotch[3];
	int32	ylf[2];
	int32   delta_t;
}SPLL_1ph;


void SPLL_1ph_init(int Grid_freq, int DELTA_T, SPLL_1ph *spll);
inline void SPLL_1ph_run(SPLL_1ph *spll1);

void SPLL_1ph_init(int Grid_freq, int DELTA_T, SPLL_1ph *spll_obj)
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
	
	
	// coefficients for the notch filter

	// Grid Frequency 50Hz
	if(Grid_freq==50)
	{
		spll_obj->notch_coeff.B2_notch=SPLL_Q(0.972);
		spll_obj->notch_coeff.B1_notch=SPLL_Q(-1.9402);
		spll_obj->notch_coeff.B0_notch=SPLL_Q(0.972);
		spll_obj->notch_coeff.A2_notch=SPLL_Q(0.944);
		spll_obj->notch_coeff.A1_notch=SPLL_Q(-1.9402);
	}
	// Grid Frequency 60Hz
	else if (Grid_freq==60)
	{
		spll_obj->notch_coeff.B2_notch=SPLL_Q(0.9969);
		spll_obj->notch_coeff.B1_notch=SPLL_Q(-1.9923);
		spll_obj->notch_coeff.B0_notch=SPLL_Q(0.9969);
		spll_obj->notch_coeff.A2_notch=SPLL_Q(0.9937);
		spll_obj->notch_coeff.A1_notch=SPLL_Q(-1.9923);
	}

	//coefficients for the loop filter 
	spll_obj->lpf_coeff.B1_lf=SPLL_Q(-247.8);
	spll_obj->lpf_coeff.B0_lf=SPLL_Q(250.0);
	spll_obj->lpf_coeff.A1_lf=SPLL_Q(-1.0);
	
	spll_obj->delta_t=DELTA_T;  

}



	
inline void SPLL_1ph_run(SPLL_1ph *spll_obj)
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
	
	spll_obj->theta[0]=spll_obj->theta[1]+SPLL_Qmpy(spll_obj->wn,SPLL_Q(0.00001591549));
	
	if(spll_obj->sin[0]>SPLL_Q(0.0) && spll_obj->sin[1]<=SPLL_Q(0.0))
	{
		spll_obj->theta[0]=SPLL_Q(0.0);
	} 
	
	spll_obj->theta[1]=spll_obj->theta[0];
	
	spll_obj->sin[1]=spll_obj->sin[0];
	spll_obj->cos[1]=spll_obj->cos[0];
	
	
}

#define SPLL_1ph_MACRO(v) \
	/* Phase Detect*/								\
	v.Upd[0]=SPLL_Qmpy(v.AC_input,v.cos[1]);	\
	/* Notch Filter*/								\
	v.ynotch[0]=-SPLL_Qmpy(v.notch_coeff.A1_notch,v.ynotch[1])-SPLL_Qmpy(v.notch_coeff.A2_notch,v.ynotch[2])+SPLL_Qmpy(v.notch_coeff.B0_notch,v.Upd[0])+SPLL_Qmpy(v.notch_coeff.B1_notch,v.Upd[1])+SPLL_Qmpy(v.notch_coeff.B2_notch,v.Upd[2]);	\
	/* Update Upd Array for future use*/								\
	v.Upd[2]=v.Upd[1];	\
	v.Upd[1]=v.Upd[0];	\
	/* LPF*/								\
	v.ylf[0]=-SPLL_Qmpy(v.lpf_coeff.A1_lf,v.ylf[1])+SPLL_Qmpy(v.lpf_coeff.B0_lf,v.ynotch[0])+SPLL_Qmpy(v.lpf_coeff.B1_lf,v.ynotch[1]);	\
	/* Update Array for future use*/								\
	v.ynotch[2]=v.ynotch[1];	\
	v.ynotch[1]=v.ynotch[0];	\
	v.ylf[1]=v.ylf[0];			\
	/*VCO*/								\
	v.wo=v.wn+v.ylf[0];	\
	/* integration process */			\
	v.sin[0]=v.sin[1]+SPLL_Qmpy((SPLL_Qmpy(v.delta_t,v.wo)),v.cos[1]);	\
	v.cos[0]=v.cos[1]-SPLL_Qmpy((SPLL_Qmpy(v.delta_t,v.wo)),v.sin[1]);	\
	if(v.sin[0]>SPLL_Q(0.99))	\
		v.sin[0]=SPLL_Q(0.99);	\
	else if(v.sin[0]<SPLL_Q(-0.99))	\
		v.sin[0]=SPLL_Q(-0.99);	\
	if(v.cos[0]>SPLL_Q(0.99))	\
		v.cos[0]=SPLL_Q(0.99);	\
	else if(v.cos[0]<SPLL_Q(-0.99))	\
		v.cos[0]=SPLL_Q(-0.99);	\
	v.theta[0]=v.theta[1]+SPLL_Qmpy(v.wn,SPLL_Q(0.00001591549));	\
	if(v.sin[0]>SPLL_Q(0.0) && v.sin[1]<=SPLL_Q(0.0))	\
	{													\
		v.theta[0]=SPLL_Q(0.0);							\
	}													\
	v.theta[1]=v.theta[0];								\
	v.sin[1]=v.sin[0];								\
	v.cos[1]=v.cos[0];								\
		
#endif
