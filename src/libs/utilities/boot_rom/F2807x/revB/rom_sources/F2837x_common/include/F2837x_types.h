//###########################################################################
// FILE:   F2837x_types.h
// TITLE:  Common types and macros.
//###########################################################################
// $TI Release: F2837x Support Library v100 $
// $Release Date: Tue Nov  6 08:49:15 CST 2012 $
//###########################################################################

#ifndef __TYPES_H__
#define __TYPES_H__

//*****************************************************************************
// Macros for hardware access, both direct and via the bit-band region.
//*****************************************************************************
#define HWREG(x)															  \
	(*((volatile unsigned long *)(x)))

#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))


#endif // __HW_TYPES_H__



