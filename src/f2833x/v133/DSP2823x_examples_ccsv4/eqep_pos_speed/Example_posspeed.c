//###########################################################################
//
// FILE:	Example_posspeed.c
//
// TITLE:	Pos/speed measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file includes the EQEP initialization and position and speed calcuation
// functions called by Example_2823xEqep_posspeed.c.  The position and
// speed calculation steps performed by POSSPEED_Calc() at  SYSCLKOUT = 150 MHz 
// and 100 MHz are described in detail below:
//
// For 150 MHz Operation:
// ----------------------
//
// 1. This program calculates: **theta_mech**
//    
//    theta_mech = QPOSCNT/mech_Scaler = QPOSCNT/4000, where 4000 is the number of
//                 counts in 1 revolution.(4000/4 = 1000 line/rev. quadrature encoder)
//
// 2. This program calculates: **theta_elec**
//
//    theta_elec = (# pole pairs) * theta_mech = 2*QPOSCNT/4000 for this example
//
// 3. This program calculates: **SpeedRpm_fr**
//
//    SpeedRpm_fr = [(x2-x1)/4000]/T                                             - Equation 1
//    Note (x2-x1) = difference in number of QPOSCNT counts. Dividing (x2-x1) by
//    4000 gives position relative to Index in one revolution.
// If base RPM  = 6000 rpm:   6000 rpm = [(x2-x1)/4000]/10ms                     - Equation 2
//                                     = [(x2-x1)/4000]/(.01s*1 min/60 sec)
//                                     = [(x2-x1)/4000]/(1/6000) min
//                         max (x2-x1) = 4000 counts, or 1 revolution in 10 ms
//
//
// If both sides of Equation 2 are divided by 6000 rpm, then:
//                            1 = [(x2-x1)/4000] rev./[(1/6000) min * 6000rpm] 
//							Because (x2-x1) must be <4000 (max) for QPOSCNT increment,
//						    (x2-x1)/4000 < 1 for CW rotation
//                          And because (x2-x1) must be >-4000 for QPOSCNT decrement,
//                          (x2-x1)/4000>-1  for CCW rotation
//						    speed_fr = [(x2-x1)/4000]/[(1/6000) min * 6000rpm]
//                                   = (x2-x1)/4000                              - Equation 3
//
// To convert speed_fr to RPM, multiply Equation 3 by 6000 rpm
//                           SpeedRpm_fr = 6000rpm *(x2-x1)/4000                 - Final Equation
//						                          
//
// 2. **min rpm ** = selected at 10 rpm based on CCPS prescaler options available (128 is greatest)
//
// 3. **SpeedRpm_pr**
//    SpeedRpm_pr = X/(t2-t1)                                                    - Equation 4
//    where X = QCAPCTL [UPPS]/4000 rev. (position relative to Index in 1 revolution) 
// If max/base speed = 6000 rpm:  6000 = (32/4000)/[(t2-t1)/(150MHz/128)]  
//    where 32 = QCAPCTL [UPPS] (Unit timeout - once every 32 edges)
//          32/4000 = position in 1 revolution (position as a fraction of 1 revolution)
//          t2-t1/(150MHz/128),  t2-t1= # of QCAPCLK cycles, and
//		                  1 QCAPCLK cycle = 1/(150MHz/128)
//										  = QCPRDLAT
//
//		        So: 6000 rpm = [32(150MHz/128)*60s/min]/[4000(t2-t1)]
//		             t2-t1 = [32(150MHz/128)*60 s/min]/(4000*6000rpm)           - Equation 5 
//		                   = 94 CAPCLK cycles = maximum (t2-t1) = SpeedScaler
//
// Divide both sides by (t2-t1), and:
//                   1 = 94/(t2-t1) = [32(150MHz/128)*60 s/min]/(4000*6000rpm)]/(t2-t1)
//				     Because (t2-t1) must be < 94 for QPOSCNT increment:
//				     94/(t2-t1) < 1 for CW rotation
//                   And because (t2-t1) must be >-94 for QPOSCNT decrement:
//				     94/(t2-t1)> -1 for CCW rotation
//
//					 speed_pr = 94/(t2-t1) 
//                      or [32(150MHz/128)*60 s/min]/(4000*6000rpm)]/(t2-t1)  - Equation 6
//
// To convert speed_pr to RPM:
// Multiply Equation 6 by 6000rpm:
//                  SpeedRpm_fr  = 6000rpm * [32(150MHz/128)*60 s/min]/[4000*6000rpm*(t2-t1)]
//							                = [32(150MHz/128)*60 s/min]/[4000*(t2-t1)]
//                                        or [(32/4000)rev * 60 s/min]/[(t2-t1)(QCPRDLAT)]- Final Equation
//
//
// For 100 MHz Operation:
// ----------------------
//
// The same calculations as above are performed, but with 100 MHz
// instead of 150MHz when calculating SpeedRpm_pr.
// The value for freqScaler_pr becomes: [32*(100MHz/128)*60s/min]/(4000*6000rpm) = 63
// More detailed calculation results can be found in the Example_freqcal.xls
// spreadsheet included in the example folder.
//
//
//
// This file contains source for the posspeed module
//
//###########################################################################
// Original Author: SD
//
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_posspeed.h"   // Example specific Include file

void  POSSPEED_Init(void)
{

    #if (CPU_FRQ_150MHZ)
	  EQep1Regs.QUPRD=1500000;			// Unit Timer for 100Hz at 150 MHz SYSCLKOUT
	#endif
    #if (CPU_FRQ_100MHZ)
	  EQep1Regs.QUPRD=1000000;			// Unit Timer for 100Hz at 100 MHz SYSCLKOUT
	#endif	

	EQep1Regs.QDECCTL.bit.QSRC=00;		// QEP quadrature count mode
		
	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
	EQep1Regs.QEPCTL.bit.PCRM=00;		// PCRM=00 mode - QPOSCNT reset on index event
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable 
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep1Regs.QPOSMAX=0xffffffff;
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable
		
	EQep1Regs.QCAPCTL.bit.UPPS=5;   	// 1/32 for unit position
	EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable
	

}

void POSSPEED_Calc(POSSPEED *p)
{
     long tmp;
     unsigned int pos16bval,temp1;
   	 _iq Tmp1,newp,oldp;

//**** Position calculation - mechanical and electrical motor angle  ****//     
     p->DirectionQep = EQep1Regs.QEPSTS.bit.QDF;    // Motor direction: 0=CCW/reverse, 1=CW/forward

	 pos16bval=(unsigned int)EQep1Regs.QPOSCNT;     // capture position once per QA/QB period
     p->theta_raw = pos16bval+ p->cal_angle;        // raw theta = current pos. + ang. offset from QA
	 
	 // The following lines calculate p->theta_mech ~= QPOSCNT/mech_scaler [current cnt/(total cnt in 1 rev.)]
	 // where mech_scaler = 4000 cnts/revolution
     tmp = (long)((long)p->theta_raw*(long)p->mech_scaler);  	// Q0*Q26 = Q26 
     tmp &= 0x03FFF000;                                        
     p->theta_mech = (int)(tmp>>11);         		// Q26 -> Q15 
     p->theta_mech &= 0x7FFF;                       
	 
	 // The following lines calculate p->elec_mech    
     p->theta_elec = p->pole_pairs*p->theta_mech;  // Q0*Q15 = Q15 
     p->theta_elec &= 0x7FFF;                      

// Check an index occurrence
     if (EQep1Regs.QFLG.bit.IEL == 1)                   
     {  
    	p->index_sync_flag = 0x00F0;
    	EQep1Regs.QCLR.bit.IEL=1;					// Clear interrupt flag
     }
      


//**** High Speed Calcultation using QEP Position counter ****//
// Check unit Time out-event for speed calculation:
// Unit Timer is configured for 100Hz in INIT function

	if(EQep1Regs.QFLG.bit.UTO==1)                    // If unit timeout (one 100Hz period)
	{ 
		/** Differentiator	**/
		// The following lines calculate position = (x2-x1)/4000 (position in 1 revolution)
	 	pos16bval=(unsigned int)EQep1Regs.QPOSLAT;	              // Latched POSCNT value		
     	tmp = (long)((long)pos16bval*(long)p->mech_scaler);  	  // Q0*Q26 = Q26 
     	tmp &= 0x03FFF000;
     	tmp = (int)(tmp>>11);         			                  // Q26 -> Q15 
     	tmp &= 0x7FFF;
		newp=_IQ15toIQ(tmp);
		oldp=p->oldpos;

   		if (p->DirectionQep==0)      				// POSCNT is counting down
   		{
    		if (newp>oldp)
      			Tmp1 = - (_IQ(1) - newp + oldp);    // x2-x1 should be negative
    		else
      		Tmp1 = newp -oldp;
   		}
   		else if (p->DirectionQep==1)      			// POSCNT is counting up
   		{
    		if (newp<oldp)
      		Tmp1 = _IQ(1) + newp - oldp;
    		else 
      		Tmp1 = newp - oldp;                     // x2-x1 should be positive
   		}

	   	if (Tmp1>_IQ(1))                            
	     	p->Speed_fr = _IQ(1);
	   	else if (Tmp1<_IQ(-1))
	     	p->Speed_fr = _IQ(-1);      
	   	else
	     	p->Speed_fr = Tmp1;

		// Update the electrical angle
    	p->oldpos = newp;
     
		// Change motor speed from pu value to rpm value (Q15 -> Q0)
		// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
   		p->SpeedRpm_fr = _IQmpy(p->BaseRpm,p->Speed_fr);  
		//=======================================
		
		EQep1Regs.QCLR.bit.UTO=1;					// Clear interrupt flag
	}	

//**** Low-speed computation using QEP capture counter ****//	
	if(EQep1Regs.QEPSTS.bit.UPEVNT==1)                 // Unit position event
	{
		if(EQep1Regs.QEPSTS.bit.COEF==0)               // No Capture overflow
			temp1=(unsigned long)EQep1Regs.QCPRDLAT;   // temp1 = t2-t1  
		else							               // Capture overflow, saturate the result
			temp1=0xFFFF;
	
		p->Speed_pr = _IQdiv(p->SpeedScaler,temp1);    // p->Speed_pr = p->SpeedScaler/temp1 
		Tmp1=p->Speed_pr;
	
		if (Tmp1>_IQ(1))
	 		p->Speed_pr = _IQ(1);   
		else
	 		p->Speed_pr = Tmp1;

	    // Convert p->Speed_pr to RPM
		if (p->DirectionQep==0)                                 // Reverse direction = negative
			p->SpeedRpm_pr = -_IQmpy(p->BaseRpm,p->Speed_pr); 	// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
		else                                                    // Forward direction = positive
			p->SpeedRpm_pr = _IQmpy(p->BaseRpm,p->Speed_pr); 	// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q

	
		EQep1Regs.QEPSTS.all=0x88;					// Clear Unit position event flag	
													// Clear overflow error flag
	}


}


