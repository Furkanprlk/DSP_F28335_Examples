#ifndef DLOG_4CH_CLA_H_
#define DLOG_4CH_CLA_H_

//*********** Structure Definition ********//
typedef struct{
	float32 *input_ptr1;
	float32 *input_ptr2;
	float32 *input_ptr3;
	float32 *input_ptr4;
	float32 *output_ptr1;
	float32 *output_ptr2;
	float32 *output_ptr3;
	float32 *output_ptr4;
	float32 prev_value;
	float32 trig_value;
	int16_t status;
	int16_t pre_scalar;
	int16_t skip_count;
	int16_t size;
	int16_t count;
}DLOG_4CH_CLA;

//*********** Function Declarations *******//
void DLOG_4CH_CLA_FUNC(DLOG_4CH_CLA *v);

//*********** Structure Init Macro ********//
#define DLOG_4CH_CLA_init(v)	\
	v.input_ptr1=0;				\
	v.input_ptr2=0;				\
	v.input_ptr3=0;				\
	v.input_ptr4=0;				\
	v.output_ptr1=0;			\
	v.output_ptr2=0;			\
	v.output_ptr3=0;			\
	v.output_ptr4=0;			\
	v.prev_value=0;				\
	v.trig_value=0;				\
	v.status=0;					\
	v.pre_scalar=0;				\
	v.skip_count=0;				\
	v.size=0;					\
	v.count=0;					\

//*********** Macro Definition ***********//
#define DLOG_4CH_CLA_MACRO(v)									\
switch(v.status)												\
{																\
case 1: /* wait for trigger*/									\
	if(*v.input_ptr1>v.trig_value && v.prev_value<v.trig_value)	\
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
		v.output_ptr1[v.count]=*v.input_ptr1;					\
		v.output_ptr2[v.count]=*v.input_ptr2;					\
		v.output_ptr3[v.count]=*v.input_ptr3;					\
		v.output_ptr4[v.count]=*v.input_ptr4;					\
		v.count++;												\
		if(v.count==v.size)										\
		{														\
			v.count=0;											\
			v.status=1;											\
		}														\
	}															\
	break;														\
}																\
v.prev_value=*v.input_ptr1;										\


#endif /* DLOG_4CH_CLA_H_ */
