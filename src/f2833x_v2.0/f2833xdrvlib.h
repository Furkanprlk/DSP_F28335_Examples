
#ifndef  __F2833xDRVLIB_H__
#define  __F2833xDRVLIB_H__


// Used to indirectly access all EPWM modules
volatile struct EPWM_REGS *ePWM[] = 
 				  { &EPwm1Regs,			//intentional: (ePWM[0] not used)
				  	&EPwm1Regs,
					&EPwm2Regs,
					&EPwm3Regs,
					&EPwm4Regs,
					&EPwm5Regs,
					&EPwm6Regs,
				  };


// Used to indirectly access eQEP module
volatile struct EQEP_REGS *eQEP[] = 
 				  { &EQep1Regs,
 				  	&EQep1Regs,			
					&EQep2Regs,
				  };

// Used to indirectly access eQEP module
volatile struct ECAP_REGS *eCAP[] = 
 				  { &ECap1Regs,
 				  	&ECap1Regs,
					&ECap2Regs,
					&ECap3Regs,
					&ECap4Regs,
					&ECap5Regs,
					&ECap6Regs,			
				  };
				  
#endif	// __F2833xDRVLIB_H__




