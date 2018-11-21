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

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
		Basic built-in Data Types
************************************************************/

typedef ape_os_fd_t			ape_evfd_t;
typedef ape_ushort_t		ape_event_t;

/******************************************************************
	System Predefined Reactor Event:
		EV_TIMEOUT, EV_READ, EV_WRITE, EV_SIGNAL, EV_PERSIST, EV_ET 
******************************************************************/
#define _APE_EV_TIMEOUT			0x01
#define _APE_EV_READ			0x02
#define _APE_EV_WRITE			0x04	
#define _APE_EV_SIGNAL			0x08

#define _APE_EV_PERSIST			0x10
#define _APE_EV_ET				0x11

/****************************************************************/
/*		Event Module											*/
/****************************************************************/

typedef enum _tag_ape_event_module_category_e {
	APE_EVCAT_NONE = 0,
	APE_EVCAT_IO,
	APE_EVCAT_SIG,
	APE_EVCAT_TIMER,

	APE_EVCAT_END
} ape_evcat_e;
#define ape_evmdl_isvalid_cat(cat)						((cat)>APE_EVCAT_NONE && (cat)<APE_EVCAT_END)

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

#define ape_evmdl_isactive(evmdlp)						((evmdlp)->reactorp!=NULL)

#define ape_evmdl_get_cat(evmdlp)						(evmdlp)->cat

#define ape_evmdl_get_fd(evmdlp)						(evmdlp)->fd

#define ape_evmdl_get_events(evmdlp)					(((evmdlp)->evnets)&(~(APE_EV_PERSIST|APE_EV_ET)))
#define ape_evmdl_add_events(evmdlp, events)			do {											\
															if ((evmdlp)->cat == APE_EVCAT_IO ) {		\
																((evmdlp)->events |= (events));			\
															}											\
														} while (0)
#define ape_evmdl_mod_events(evmdlp, events)			do {											\
															if ((evmdlp)->cat == APE_EVCAT_IO ) {		\
																((evmdlp)->events = events |((evmdlp)->events&(APE_EV_PERSIST|APE_EV_ET)));	\
															}											\
														} while (0)
#define ape_evmdl_del_events(evmdlp, events)			do {											\
															if ((evmdlp)->cat == APE_EVCAT_IO ) {		\
																((evmdlp)->events &= (~(events)));		\
															}											\
														} while (0)	

#define ape_evmdl_is_persist(evmdlp)					((evmdlp)->events&APE_EV_PERSIST)?1:0
#define ape_evmdl_set_persist(evmdlp, on)			do {													\
															if ( on ) {										\
																ape_evmdl_add_events(APE_EV_PERSIST);		\
															} else {										\
																ape_evmdl_del_events(APE_EV_PERSIST);		\
															}												\
														} while (0)

/* Edge Trigger if os supports this feature. */
#define ape_evmdl_is_etmode(evmdlp)					((evmdlp)->events&APE_EV_ET)?1:0
#define ape_evmdl_set_etmode(evmdlp, on)				do {										\
															if ( on ) {								\
																ape_evmdl_add_events(APE_EV_ET);	\
															} else {								\
																ape_evmdl_del_events(APE_EV_ET);	\
															}										\
														} while (0)


#define ape_evmdl_get_interval(evmdlp)				(evmdlp)->interval

#ifdef __cplusplus
}
#endif

#endif /*__APE_EVMDL_H__*/
