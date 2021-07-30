#ifndef DLOG_4CH_IQ_H_
#define DLOG_4CH_IQ_H_

//*********** Structure Definition ********//
typedef struct{
	int16 *input_ptr1;
	int16 *input_ptr2;
	int16 *input_ptr3;
	int16 *input_ptr4;
	int16 *output_ptr1;
	int16 *output_ptr2;
	int16 *output_ptr3;
	int16 *output_ptr4;
	int16 prev_value;
	int16 trig_value;
	int16 status;
	int16 pre_scalar;
	int16 skip_count;
	int16 size;
	int16 count;
}DLOG_4CH_IQ;

//*********** Function Declarations *******//
void DLOG_4CH_IQ_init(DLOG_4CH_IQ *v);
void DLOG_4CH_IQ_FUNC(DLOG_4CH_IQ *v);

//*********** Macro Definition ***********//
#define DLOG_4CH_IQ_MACRO(v)												\
	switch(v.status)														\
	{																		\
	case 0: /* wait for trigger*/											\
		if((int16)*v.input_ptr1>v.trig_value && v.prev_value<v.trig_value)	\
		{																	\
			/* rising edge detected start logging data*/					\
			v.status=1;														\
		}																	\
		break;																\
	case 1:																	\
		v.skip_count++;														\
		if(v.skip_count==v.pre_scalar)										\
		{																	\
			v.skip_count=0;													\
			v.output_ptr1[v.count]=*v.input_ptr1;							\
			v.output_ptr2[v.count]=*v.input_ptr2;							\
			v.output_ptr3[v.count]=*v.input_ptr3;							\
			v.output_ptr4[v.count]=*v.input_ptr4;							\
			v.count++;														\
			if(v.count==v.size)												\
			{																\
				v.count=0;													\
				v.status=0;													\
			}																\
		}																	\
		break;																\
	}																		\
	v.prev_value=*v.input_ptr1;

	
#endif /* DLOG_4CH_IQ_H_ */
