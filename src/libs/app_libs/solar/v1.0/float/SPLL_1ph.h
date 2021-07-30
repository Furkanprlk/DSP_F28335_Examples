#ifndef _SPLL_1ph_H_
#define _SPLL_1ph_H_

typedef struct{
	float	B2_notch;
	float	B1_notch;
	float	B0_notch;
	float	A2_notch;
	float	A1_notch;
}SPLL_NOTCH_COEFF; 

typedef struct{
	float	B1_lf;
	float	B0_lf;
	float	A1_lf;
}SPLL_LPF_COEFF;

typedef struct{
	float	AC_input;				//INPUT		: 	1ph AC Signal measured
	float	wn;						//INPUT		:	Grid Frequency in radians/sec 
	float	theta[2];				//OUTPUT	:	grid phase angle
	float	cos[2];					//OUTPUT	:	Cos(grid phase angle)
	float	sin[2];					//OUTPUT	:	Sin(grid phase angle)
	float   wo;						//INTERNAL	:	Instantaneous Grid Frequency in radians/sec
	SPLL_NOTCH_COEFF notch_coeff;	//INTERNAL : 	Notch Filter Coefficients
	SPLL_LPF_COEFF	 lpf_coeff;		//INTERNAL : 	Loop Filer Coefficients
	float   Upd[3];					//INTERNAL	:   Internal Data Buffer for phase detect output
	float	ynotch[3];				//INTERNAL	:	Internal Data Buffer for the notch output
	float	ylf[2];					//INTERNAL	:	Internal Data Buffer for Loop Filter output
	float   delta_t;				//INTERNAL	:	1/Frequency of calling the PLL routine
}SPLL_1ph;


void SPLL_1ph_init(float Grid_freq, float DELTA_T, SPLL_1ph *spll);
inline void SPLL_1ph_run(SPLL_1ph *spll1);

void SPLL_1ph_init(float  Grid_freq, float  DELTA_T, SPLL_1ph *spll_obj)
{
	spll_obj->Upd[0]=0.0;
	spll_obj->Upd[1]=0.0;
	spll_obj->Upd[2]=0.0;
	
	spll_obj->ynotch[0]=0.0;
	spll_obj->ynotch[1]=0.0;
	spll_obj->ynotch[2]=0.0;
	
	spll_obj->ylf[0]=0.0;
	spll_obj->ylf[1]=0.0;
	
	spll_obj->sin[0]=0.0;
	spll_obj->sin[1]=0.0;
	
	spll_obj->cos[0]=0.999;
	spll_obj->cos[1]=0.999;
	
	spll_obj->theta[0]=0.0;
	spll_obj->theta[1]=0.0;
	
	spll_obj->wn=(2.0*3.14*Grid_freq);
	
	// coefficients for the notch filter

	// Grid Frequency 50Hz
	if(Grid_freq==50)
	{
		spll_obj->notch_coeff.B2_notch=0.972;
		spll_obj->notch_coeff.B1_notch=-1.9402;
		spll_obj->notch_coeff.B0_notch=0.972;
		spll_obj->notch_coeff.A2_notch=0.944;
		spll_obj->notch_coeff.A1_notch=-1.9402;
	}
	// Grid Frequency 60Hz
	else if (Grid_freq==60)
	{
		spll_obj->notch_coeff.B2_notch=0.9969;
		spll_obj->notch_coeff.B1_notch=-1.9923;
		spll_obj->notch_coeff.B0_notch=0.9969;
		spll_obj->notch_coeff.A2_notch=0.9937;
		spll_obj->notch_coeff.A1_notch=-1.9923;
	}

	//coefficients for the loop filter 
	spll_obj->lpf_coeff.B1_lf=-247.8;
	spll_obj->lpf_coeff.B0_lf=250.0;
	spll_obj->lpf_coeff.A1_lf=-1.0;
	
	spll_obj->delta_t=DELTA_T;  

}



	
inline void SPLL_1ph_run(SPLL_1ph *spll_obj)
{

	//-------------------//
	// Phase Detect 	 //
	//-------------------//
	
	spll_obj->Upd[0]=spll_obj->AC_input*spll_obj->cos[1];
	
	//-------------------//
	//Notch filter structure//
	//-------------------//
	
	spll_obj->ynotch[0]=-(spll_obj->notch_coeff.A1_notch*spll_obj->ynotch[1])-(spll_obj->notch_coeff.A2_notch*spll_obj->ynotch[2])+(spll_obj->notch_coeff.B0_notch*spll_obj->Upd[0])+(spll_obj->notch_coeff.B1_notch*spll_obj->Upd[1])+(spll_obj->notch_coeff.B2_notch*spll_obj->Upd[2]);
	
	// update the Upd array for future
	spll_obj->Upd[2]=spll_obj->Upd[1];
	spll_obj->Upd[1]=spll_obj->Upd[0];
	
	//---------------------------//
	// PI loop filter 			 //
	//---------------------------//
	
	spll_obj->ylf[0]=-(spll_obj->lpf_coeff.A1_lf*spll_obj->ylf[1])+(spll_obj->lpf_coeff.B0_lf*spll_obj->ynotch[0])+(spll_obj->lpf_coeff.B1_lf*spll_obj->ynotch[1]);
	
	//update array for future use
	spll_obj->ynotch[2]=spll_obj->ynotch[1];
	spll_obj->ynotch[1]=spll_obj->ynotch[0];
	
	spll_obj->ylf[1]=spll_obj->ylf[0];
	
	//------------------//
	// VCO              //
	//------------------//
	
	spll_obj->wo=spll_obj->wn+spll_obj->ylf[0];
	
	//integration process
	spll_obj->sin[0]=spll_obj->sin[1]+(((spll_obj->delta_t*spll_obj->wo))*spll_obj->cos[1]);
	spll_obj->cos[0]=spll_obj->cos[1]-(((spll_obj->delta_t*spll_obj->wo))*spll_obj->sin[1]);

	if(spll_obj->sin[0]>(0.99))
		spll_obj->sin[0]=(0.99);
	else if(spll_obj->sin[0]<(-0.99))
		spll_obj->sin[0]=(-0.99);
	
	if(spll_obj->cos[0]>(0.99))
		spll_obj->cos[0]=(0.99);
	else if(spll_obj->cos[0]<(-0.99))
		spll_obj->cos[0]=(-0.99);
	
	spll_obj->theta[0]=spll_obj->theta[1]+(spll_obj->wn*(0.00001591549));
	
	if(spll_obj->sin[0]>(0.0) && spll_obj->sin[1]<=(0.0))
	{
		spll_obj->theta[0]=(0.0);
	} 
	
	spll_obj->theta[1]=spll_obj->theta[0];
	
	spll_obj->sin[1]=spll_obj->sin[0];
	spll_obj->cos[1]=spll_obj->cos[0];
	
	
}




#define SPLL_1ph_MACRO(v) \
	/* Phase Detect*/								\
	v.Upd[0]=(v.AC_input*v.cos[1]);	\
	/* Notch Filter*/								\
	v.ynotch[0]=-(v.notch_coeff.A1_notch*v.ynotch[1])-(v.notch_coeff.A2_notch*v.ynotch[2])+(v.notch_coeff.B0_notch*v.Upd[0])+(v.notch_coeff.B1_notch*v.Upd[1])+(v.notch_coeff.B2_notch*v.Upd[2]);	\
	/* Update Upd Array for future use*/								\
	v.Upd[2]=v.Upd[1];	\
	v.Upd[1]=v.Upd[0];	\
	/* LPF*/								\
	v.ylf[0]=-(v.lpf_coeff.A1_lf*v.ylf[1])+(v.lpf_coeff.B0_lf*v.ynotch[0])+(v.lpf_coeff.B1_lf*v.ynotch[1]);	\
	/* Update Array for future use*/								\
	v.ynotch[2]=v.ynotch[1];	\
	v.ynotch[1]=v.ynotch[0];	\
	v.ylf[1]=v.ylf[0];			\
	/*VCO*/								\
	v.wo=v.wn+v.ylf[0];	\
	/* integration process */			\
	v.sin[0]=v.sin[1]+(((v.delta_t*v.wo))*v.cos[1]);	\
	v.cos[0]=v.cos[1]-(((v.delta_t*v.wo))*v.sin[1]);	\
	if(v.sin[0]>(0.99))	\
		v.sin[0]=(0.99);	\
	else if(v.sin[0]<(-0.99))	\
		v.sin[0]=(-0.99);	\
	if(v.cos[0]>(0.99))	\
		v.cos[0]=(0.99);	\
	else if(v.cos[0]<(-0.99))	\
		v.cos[0]=(-0.99);	\
	v.theta[0]=v.theta[1]+(v.wn*(0.00001591549));	\
	if(v.sin[0]>(0.0) && v.sin[1]<=(0.0))	\
	{													\
		v.theta[0]=(0.0);							\
	}													\
	v.theta[1]=v.theta[0];								\
	v.sin[1]=v.sin[0];								\
	v.cos[1]=v.cos[0];								\
		
#endif
