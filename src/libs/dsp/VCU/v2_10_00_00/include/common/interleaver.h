#ifndef _INTERLEAVER_H_
#define _INTERLEAVER_H_
//#############################################################################
//! \file include/common/interleaver.h
//!
//! \brief  Interleaver header file
//!
//! \date   Jan 6, 2015
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x VCU Library Version v2.10.00.00 $
//$Release Date: Mar 3, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>

//!
//! \defgroup _INTERLEAVER_H_ Interleaver

//!
//! \ingroup _INTERLEAVER_H_
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define _DOXYGEN_	1	// Temporary Definition for documentation purposes
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief Interleaver structure
//! The de-interleaver will reshuffle the rows and
//! columns according to the following two equations
//! J = (j * n_j + i * n_i) % n
//! I = (i * m_i + J * m_j) % m
//! where m (# columns) is the number of subcarriers perror
//! OFDM symbol and n (# rows) is the number of OFDM symbols
//! Each OFDM symbol may have mod_size number of bits (bits
//! per constellation e.g. 1, 2, 3, 4) and so the entire matrix
//! is m x (n x mod_size)
//! m_i, m_j are relatively prime to m i.e. 
//!     GCD(m_i,m) = 1, m_i > 2
//!     GCD(m_j,m) = 1, m_j > 2 
//!     m_i < m_j < m 
//! Similarly, n_i, n_j are relatively prime to n i.e. 
//!     GCD(n_i,n) = 1, n_i > 2
//!     GCD(n_j,n) = 1, n_j > 2 
//!     n_i < n_j < n
//! Solving these equations give us i, j which are the
//! interleaver operations
//!     i*m_i = (I - J*m_j) mod m
//! We find a_i s.t. m_i * a_i = 1 mod m i.e. m_i is the
//! multiplicative inverse (mod m) of a_i
//!     i*a_i*m_i = a_i*(I - J*m_j) mod m
//!     i = a_i*I - a_i*m_j*J mod m
//!     i = a_i*I - u_ij*J mod m, where u_ij = a_i*m_j
//!     i = a*I - u*J mod m (dropping subscripts)
//! In a similar fashion we find j to begin
//!     j = b_j*J - b_j*n_i*i mod n
//!     j = b_j*J - v_ji*i mod n, where v_ji = b_j*n_i
//!     j = b*J - v*i mod n (dropping subscripts)
//! The interleaver equations are:
//! i = a*I - u*J mod m
//! j = b*J - v*i mod n
//
typedef struct _INTERLEAVER_Obj_{
  uint16_t  n;
  uint16_t  m;
  uint16_t  b;
  uint16_t  v;
  uint16_t  a;
  uint16_t  u;
  uint16_t  n_i;
  uint16_t  n_j;
  uint16_t  m_i;
  uint16_t  m_j;
  uint16_t  offset; //!< offset index into the sub carrier parameters table
  uint16_t  *tbl_p; //!< Pointer to the sub-carrier parameters table
}INTERLEAVER_Obj;

//! \brief Handle to the Interleaver structure
//!
typedef INTERLEAVER_Obj *INTERLEAVER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Finds the interleaver parameters
//! 
//! \param     hndInterleaver pointer to the interleaver object
//! \param[in] n    number of symbols
//! \param[in] m    number of sub-carriers
//!
void INTERLEAVER_findParams(INTERLEAVER_Handle hndInterleaver, 
                uint16_t n,
                uint16_t m);
                
//! \brief Runs the Interleaver
//!
//! Generates interleaved bits for data
//!
//! \param     hndInterleaver pointer to the interleaver object
//! \param[in] in_p  pointer to the input buffer
//! \param[in] out_p pointer to the output buffer
//! \param[in] symb  number of sub-carriers
//!
void INTERLEAVER_run(INTERLEAVER_Handle hndInterleaver,
                     uint16_t *in_p, uint16_t *out_p,
                     uint16_t  symb);
#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _INTERLEAVER_H_ definition

// End of File
