#ifndef DLOG_1CH_IQ_H_
#define DLOG_1CH_IQ_H_

//*********** Structure Definition ********//
typedef struct{
	int16 *input_ptr;
	int16 *output_ptr;
	int32 prev_value;
	int32 trig_value;
	int16 status;
	int16 pre_scalar;
	int16 skip_count;
	int16 size;
	int16 count;
}DLOG_1CH_IQ;

//*********** Function Declarations *******//
void DLOG_1CH_IQ_init(DLOG_1CH_IQ *v);
void DLOG_1CH_IQ_FUNC(DLOG_1CH_IQ *v);

//*********** Macro Definition ***********//
#define DLOG_1CH_IQ_MACRO(v)										\
	switch(v.status)												\
	{																\
	case 0: /* wait for trigger*/									\
		if(*v.input_ptr>v.trig_value && v.prev_value<v.trig_value)	\
		{															\
			/* rising edge detected start logging data*/			\
			v.status=1;												\
		}															\
		break;														\
	case 1:															\
		v.skip_count++;												\
		if(v.skip_count==v.pre_scalar)								\
		{															\
			v.skip_count=0;											\
			v.output_ptr[v.count]=*v.input_ptr;						\
			v.count++;												\
			if(v.count==v.size)										\
			{														\
				v.count=0;											\
				v.status=0;											\
			}														\
		}															\
		break;														\
	}																\
	v.prev_value=*v.input_ptr;										\


#endif /* DLOG_1CH_IQ_H_ */
