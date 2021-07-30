#ifndef DLOG_1CH_CLA_H
#define DLOG_1CH_CLA_H

//*********** Structure Definition ********//
typedef struct{
	float32 *input_ptr;
	float32 *output_ptr;
	float32 prev_value;
	float32 trig_value;
	int16_t status;
	int16_t pre_scalar;
	int16_t skip_count;
	int16_t size;
	int16_t count;
}DLOG_1CH_CLA;

//*********** Function Declarations *******//
void DLOG_1CH_CLA_FUNC(DLOG_1CH_CLA *v);

//*********** Structure Init Macro *******//
#define DLOG_1CH_CLA_init(v)	\
	v.input_ptr = 0;			\
	v.output_ptr = 0;			\
	v.prev_value = 0;			\
	v.trig_value = 0;			\
	v.status = 0;				\
	v.pre_scalar = 0;			\
	v.skip_count = 0;			\
	v.size = 0;					\
	v.count = 0;				\

//*********** Macro Definition ***********//
#define DLOG_1CH_CLA_MACRO(v)									\
switch(v.status)												\
{																\
case 1: /* wait for trigger*/									\
	if(*v.input_ptr>v.trig_value && v.prev_value<v.trig_value)	\
	{															\
		/* rising edge detected start logging data*/			\
		v.status=2;												\
	}															\
	break;														\
case 2:															\
	v.skip_count++;												\
	if(v.skip_count==v.pre_scalar)								\
	{															\
		v.skip_count=0;											\
		v.output_ptr[v.count]=*v.input_ptr;						\
		v.count++;												\
		if(v.count==v.size)										\
		{														\
			v.count=0;											\
			v.status=1;											\
		}														\
	}															\
	break;														\
}																\
v.prev_value=*v.input_ptr;										\


#endif /* DLOG_1CH_CLA_H_ */
