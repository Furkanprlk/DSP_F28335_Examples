/* demo2837x_link.cmd */

SECTIONS
{
	codestart        : > BEGIN,     PAGE = 0
	ramfuncs         : > RAMM0      PAGE = 0

	.text            : >>RAMM0 | RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,   PAGE = 0
	.cinit           : > RAMM0,     PAGE = 0
	.pinit           : > RAMM0,     PAGE = 0
	.switch          : > RAMM0,     PAGE = 0
	.reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
	.stack           : > RAMM1,     PAGE = 1
	.bss             : > RAMGS5,    PAGE = 1
	.ebss            : > RAMGS5,    PAGE = 1
	.econst          : > RAMGS5,    PAGE = 1
	.esysmem         : > RAMGS5,    PAGE = 1
	Filter_RegsFile  : > RAMGS0,	PAGE = 1

	DataLogSection	 : > RAMGS9,	PAGE = 1	align(2)	/* data log buffers */
	
	ramgs0           : > RAMGS0,    PAGE = 1
	ramgs1           : > RAMGS1,    PAGE = 1

	IQmath           : > RAMGS1415,   PAGE = 0            	/* Math Code */
	IQmathTables	 : > RAMGS1415,   PAGE = 0
	DummyIQmathTables	 : > RAMGS1415,   PAGE = 0, type = NOLOAD

	UNION load = RAMGS1415,   PAGE = 0
	{
		IQmathTables
		DummyIQmathTables
	}

	sinDataLogSection	: > RAMGS10,		PAGE = 1	align(2)	/* sine input data log buffer */
   	cosDataLogSection	: > RAMGS11,		PAGE = 1	align(2)	/* cosine input data log buffer */
	uDataLogSection		: > RAMGS12,		PAGE = 1	align(2)	/* data log buffer */
}

/* end of file */
