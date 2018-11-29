/************************************************************************************
* ape_evmdl.h : header file
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

#if !defined(__APE_EVMDL_H__)
#define __APE_EVMDL_H__

#include "ape.h"
#include "ape_file.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
		Basic built-in Data Types
************************************************************/

typedef ape_os_file_t		ape_evfd_t;
typedef ape_ushort_t		ape_event_t;

typedef enum _tag_ape_evmdl_priority_e {
	APE_EVPRIO_0 = 0,

	APE_EVPRIO_INVALID
} ape_evpri_e;

typedef enum _tag_ape_event_state_e {
	/* fd closed. */
	APE_EVSTAT_INVALID = 0, /* event fd is not valid. */
	/* Shutdown */ /* fd opened. */
	APE_EVSTAT_STOPPED, /* Do NOT respond events any more. But data members remains valid. */
	/* Registered. */
	APE_EVSTAT_INIT, /* Initialized. Associated with a Reactor. */
	/* event_add() */
	APE_EVSTAT_PENDING, /* Pending state. */
	APE_EVSTAT_ACTIVE, /* Active state. */

	APE_EVSTAT_END
} ape_evstat_e;

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
