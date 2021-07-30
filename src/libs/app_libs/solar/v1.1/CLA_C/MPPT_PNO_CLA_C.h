/**
 * Perturb and observe maximum power-point tracking algorithm implementation.
 */
#ifndef MPPT_PNO_CLA_C_H_
#define MPPT_PNO_CLA_C_H_

/**
 * MPPT_PNO_CLA_C structure.
 */
typedef struct {
	float32 Ipv;
	float32 Vpv;
	float32 DeltaPmin;
	float32 MaxVolt;
	float32 MinVolt;
	float32 Stepsize;
	float32 VmppOut;

	// Internal variables
	float32 DeltaP;
	float32 PanelPower;
	float32 PanelPower_Prev;
	float32 MPPT_Enable;
	float32 MPPT_First;
} MPPT_PNO_CLA_C;

#define MPPT_PNO_CONST_1 ((float32) 0.02)

/**
 * Default values for the MPPT PNO object.
 */
#define MPPT_PNO_CLA_C_INIT(v)						\
	v.Ipv = 0.0;									\
	v.Vpv = 0.0;									\
	v.DeltaPmin = 0.00001;							\
	v.MaxVolt = 0.9;								\
	v.MinVolt = 0.0;								\
	v.Stepsize = 0.002;								\
	v.VmppOut = 0.0;								\
													\
	/* Internal variables */						\
	v.DeltaP = 0.0;									\
	v.PanelPower = 0.0;								\
	v.PanelPower_Prev = 0.0;						\
	v.MPPT_Enable = 1;								\
	v.MPPT_First = 1

/**
 * Maximum power-point tracking using the perturb and observe method.
 * @param v - MPPT_PNO_CLA_C structure.
 * @return updated Vpv and Ipv values.
 */
#define MPPT_PNO_CLA_C(v)												\
if (v.MPPT_Enable == 1){												\
	if (v.MPPT_First == 1){												\
		v.VmppOut = v.Vpv - MPPT_PNO_CONST_1;							\
		v.MPPT_First = 0;												\
		v.PanelPower_Prev = v.PanelPower;								\
	}																	\
	else{																\
		v.PanelPower = (v.Vpv * v.Ipv);									\
		v.DeltaP = v.PanelPower - v.PanelPower_Prev;					\
																		\
		if (v.DeltaP > v.DeltaPmin){									\
			v.VmppOut = v.Vpv + v.Stepsize;								\
		}																\
		else{															\
			if (v.DeltaP < -v.DeltaPmin){								\
				v.Stepsize = -v.Stepsize;								\
				v.VmppOut = v.Vpv + v.Stepsize;							\
			}															\
		}																\
		v.PanelPower_Prev = v.PanelPower;								\
	}																	\
																		\
	v.VmppOut = (v.VmppOut < v.MinVolt) ? v.MinVolt : v.VmppOut;		\
	v.VmppOut = (v.VmppOut > v.MaxVolt) ? v.MaxVolt : v.VmppOut;		\
}

#endif /* MPPT_PNO_CLA_C_H_ */
