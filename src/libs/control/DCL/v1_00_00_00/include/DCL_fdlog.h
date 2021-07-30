/* DCL_fdlog.h - a floating-point data buffer utility */
// version 1.0, August 2015

#ifndef _C_DCL_FDLOG_H
#define _C_DCL_FDLOG_H


// example of buffer definition
// ----------------------------
// #pragma DATA_SECTION(r_Array, "DataLogSection")
// float r_Array[FDLOG_DEFAULT_SIZE];
// FDLOG rBuf = FDLOG_DEFAULTS;

// example of buffer initialisation
// --------------------------------
//	DCL_createFDLOG(&rBuf, r_Array, FDLOG_DEFAULT_SIZE);
//	DCL_clearFDLOG(&rBuf);


// 32-bit buffer structure
typedef volatile struct {
	float *fptr;
	float *lptr;
	float *dptr;
} FDLOG;	

// dereference as: *(xxx.fptr) or *(xxx->fptr)
// xxx.dptr points to first unused memory location


// default memory sizes
#define FDLOG_DEFAULT_SIZE	0x0400

// default addresses for pointer structs
// use: [FDLOG] dlogname = FDLOG_DEFAULTS;
#define FDLOG_DEFAULTS { 	0x00000000,	\
							0x00000000,	\
							0x00000000	\
						}

// macro definitions
#define FDLOG_SPACE(buf)		( (buf).lptr - (buf).dptr + 1 )		// space remaining
#define FDLOG_SIZE(buf)			( (buf).lptr - (buf).fptr + 1 )		// buffer size
#define FDLOG_ELEMENT(buf) 		( (buf).dptr - (buf).fptr + 1 )		// current element
#define FDLOG_START(buf)		( (buf).dptr == (buf).fptr )		// start of buffer
#define FDLOG_END(buf)			( (buf).dptr == (buf).lptr )		// end of buffer
#define FDLOG_OUT_OF_RANGE(buf)	( ((buf).dptr < (buf).fptr) || ((buf).dptr > (buf).lptr) )	// over/under-range check
#define FDLOG_EXISTS(buf)		( (buf).lptr != (buf).fptr )		// check if entity exists


/*** function prototypes ***/

static inline void DCL_clearLog(FDLOG *p);
static inline float DCL_writeLog(FDLOG *p, float data);
static inline void DCL_createLog(FDLOG *p, float *addr, unsigned int buflen);
static inline void DCL_resetLog(FDLOG *p);
static inline void DCL_deleteLog(FDLOG *p);
static inline void DCL_fillLog(FDLOG *p, float data);
static inline float DCL_readLog(FDLOG *p);
static inline float DCL_runITAE(FDLOG *rlog, FDLOG *ylog, float prd);

/*** inline function definitions ***/

// clear struct pointers
static inline void DCL_deleteLog(FDLOG *p)	{ p->dptr = p->lptr = p->fptr = 0; }

// reset data pointer to start of buffer
static inline void DCL_resetLog(FDLOG *p)	{ p->dptr = p->fptr; }


// create data buffer
static inline void DCL_createLog(FDLOG *p, float *addr, unsigned int buflen)
{
	p->fptr = addr;
	p->lptr = addr + buflen - 1;
	p->dptr = p->fptr;
}


// write to data log, return over-written data
static inline float DCL_writeLog(FDLOG *p, float data)
{
	float d0 = *(p->dptr);			// save existing data

	*(p->dptr) = data;				// write new data to log
	if (p->dptr >= p->lptr) 	// check for end of buffer & wrap
		p->dptr = p->fptr;
	else
		p->dptr++;

	return d0;
}


// clear buffer contents
static inline void DCL_clearLog(FDLOG *p)
{
	p->dptr = p->lptr;
	*(p->dptr) = 0;
	while (p->dptr > p->fptr)
	{
		--p->dptr;
		*(p->dptr) = 0;
	}
}


// fill buffer with known data
static inline void DCL_fillLog(FDLOG *p, float data)
{
	p->dptr = p->lptr;
	*(p->dptr) = 0;
	while (p->dptr > p->fptr)
	{
		--p->dptr;
		*(p->dptr) = data;
	}
}


// read current value from data log
static inline float DCL_readLog(FDLOG *p)
{
	float fl = *(p->dptr);

	if (p->dptr >= p->lptr)
		p->dptr = p->fptr;
	else
		p->dptr++;

	return fl;
}


// error performance index (ITAE)
static inline float DCL_runITAE(FDLOG *rlog, FDLOG *ylog, float prd)
{
	float i = 0.0f;
	float *rch = rlog->dptr;
	float *ych = ylog->dptr;
	float rlt = 0.0f;
	
	rlog->dptr = rlog->fptr;
	ylog->dptr = ylog->fptr;	
	while (rlog->dptr <= rlog->lptr)
	{
		rlt += fabs(*(rlog->dptr) - *(ylog->dptr)) * i;
		i += prd;
		rlog->dptr++;
		ylog->dptr++;
	}
	
	rlog->dptr = rch;
	ylog->dptr = ych;
	
	return rlt;
}

#endif // _C_DCL_FDLOG_H

/* end of file */
