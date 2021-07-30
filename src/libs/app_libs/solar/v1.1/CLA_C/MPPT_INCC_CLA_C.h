/**
 * Incremental conductance maximum power-point tracking algorithm implementation.
 */
#ifndef MPPT_INCC_CLA_C_H_
#define MPPT_INCC_CLA_C_H_

/**
 * MPPT_INCC_CLA_C structure.
 */
typedef struct {
	float32 Ipv;
	float32 Vpv;
	float32 IpvH;
	float32 IpvL;
	float32 VpvH;
	float32 VpvL;
	float32 MaxVolt;
	float32 MinVolt;
	float32 Stepsize;
	float32 VmppOut;

	// Internal variables
	float32 Cond;
	float32 IncCond;
	float32 DeltaV;
	float32 DeltaI;
	float32 VpvOld;
	float32 IpvOld;
	float32 MPPT_Enable;
	float32 MPPT_First;
} MPPT_INCC_CLA_C;

#define MPPT_INCC_CONST_1 ((float32) 0.05)

/**
 * Default values for the MPPT INCC structure.
 */
#define MPPT_INCC_CLA_C_INIT(v)						\
		v.Ipv = 0.0;								\
		v.Vpv = 0.0;								\
		v.IpvH = 1.65;								\
		v.IpvL = 0.0;								\
		v.VpvH = 0.0;								\
		v.VpvL = 0.0;								\
		v.MaxVolt = 0.0;							\
		v.MinVolt = 0.0;							\
		v.Stepsize = 0.0;							\
		v.VmppOut = 0.0;							\
													\
		/* Internal variables */					\
		v.Cond = 0.0;								\
		v.IncCond = 0.0;							\
		v.DeltaV = 0.0;								\
		v.DeltaI = 0.0;								\
		v.VpvOld = 0.0;								\
		v.IpvOld = 0.0;								\
		v.MPPT_Enable = 1;							\
		v.MPPT_First = (1)

/**
 * Performs incremental conductance maximum power point tracking calculations.
 * @param v - MPPT_INCC_CLA_C structure.
 * @return Vpv and Ipv parameters are updated.
 */
#define MPPT_INCC_CLA_C(v)																				\
		if(v.MPPT_Enable == 1) {																		\
			if(v.MPPT_First == 1) {		/* Initial iteration */											\
				v.VmppOut = v.Vpv - (MPPT_INCC_CONST_1);												\
				v.VpvOld = v.Vpv;																		\
				v.IpvOld = v.Ipv;																		\
				v.MPPT_First = 0;																		\
			}                                                                       					\
			else { 																						\
				v.DeltaV = v.Vpv - v.VpvOld;	/* PV voltage change */									\
				v.DeltaI = v.Ipv - v.IpvOld;	/* PV current change */									\
																										\
				/* Tolerance limits PV Voltage Variation */												\
				if((v.DeltaV < v.VpvH) && (v.DeltaV > -v.VpvL)) {v.DeltaV = 0;}  						\
																										\
				/* Tolerance limits PV current Variation */ 											\
				if((v.DeltaI < v.IpvH) && (v.DeltaI > -v.IpvL)) {v.DeltaI = 0;} 						\
																										\
				if(v.DeltaV == 0) {    																	\
					if(v.DeltaI != 0) {    		/* Operating at MPP when dI = 0 */						\
						/* Climbing towards MPP */														\
						if (v.DeltaI > 0) {v.VmppOut = v.Vpv + v.Stepsize;} /* Increment Vref */  		\
						else {v.VmppOut = v.Vpv - v.Stepsize;}					/* Decrement Vref */	\
					}																					\
				}																						\
				else {  																				\
					v.Cond = v.Ipv / v.Vpv;																\
					v.IncCond = v.DeltaI / v.DeltaV; 													\
					if(v.IncCond != v.Cond) { 		/* Operating at MPP if v.IncCond == v.Cond */		\
						if(v.IncCond > (-v.Cond)) {v.VmppOut = v.Vpv + v.Stepsize;} /* left of MPP */	\
						else {v.VmppOut = v.Vpv - v.Stepsize;} /* Right of MPP */						\
					}																					\
				}																						\
																										\
				v.VpvOld = v.Vpv;																		\
				v.IpvOld = v.Ipv;																		\
			} 																							\
		}

#endif /* MPPT_INCC_CLA_C_H_ */
