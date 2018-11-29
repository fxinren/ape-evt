/************************************************************************************
* ape_evbase.h : header file
*
* Built-in data type Definitions header
*
* AUTHOR	:	Sean Feng <SeanFeng2006@hotmail.com>
* DATE		:	Nov. 7, 2009
* Copyright (c) 2009-?. All Rights Reserved.
*
* This code may be used in compiled form in any way you desire. This
* file may be redistributed unmodified by any means PROVIDING it is 
* not sold for profit without the authors written consent, and 
* providing that this notice and the authors name and all copyright 
* notices remains intact. 
*
* An email letting me know how you are using it would be nice as well. 
*
* This file is provided "as is" with no expressed or implied warranty.
* The author accepts no liability for any damage/loss of business that
* this product may cause.
*
************************************************************************************/

#if !defined(__APE_EVBASE_H__)
#define __APE_EVBASE_H__

#include "ape.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
		Basic built-in Data Types
************************************************************/

typedef struct ape_evbase_t			ape_evbase_t;

/******************************************************************
	System Predefined Reactor Event:
		EV_TIMEOUT, EV_READ, EV_WRITE, EV_SIGNAL, EV_PERSIST, EV_ET 
******************************************************************/

/****************************************************************/
/*		Event Module											*/
/****************************************************************/
#ifdef __cplusplus
}
#endif

#endif /*__APE_EVMDL_H__*/
