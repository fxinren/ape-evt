/************************************************************************************
* ape_evt.h : header file
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

#if !defined(__APE_EVT_H__)
#define __APE_EVT_H__

#include "ape_evmdl.h"
#include "ape_evbase.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************/
/*		Macros													*/
/****************************************************************/

#define _APE_EVFD_INVALID_          (0)

#define ape_evfd_isvalid(fd)        ((fd)!=_APE_EVFD_INVALID_)

//////////////////////////////////////////////////////
#define APE_EV_NONE				0x00

#define APE_EV_TIMEOUT			0x01

#define APE_EV_READ				0x02
#define APE_EV_WRITE			0x04
#define APE_EV_CLOSED			0x08

#define APE_EV_SIG				0x10
/**************************************
 * are both in use:
 * #define APE_EV_PERSIST			0x20
 * #define APE_EV_ET				0x40
**************************************/

//////////////////////////////////////////////////////

/****************************************************************/
/*		Event Data												*/
/****************************************************************/
typedef ape_evfd_t					ape_evfd_t;
typedef ape_event_t					ape_event_t;

typedef ape_evpri_e					ape_evpri_e;
typedef ape_evstat_e				ape_evstat_e;

typedef ape_evmdl_t					ape_evmdl_t;
typedef ape_evbase_t				ape_evbase_t;

// ape_evmdl_ctl(): ops values
enum {
	APE_EVCTL_ADD = 0x01,
	APE_EVCTL_MOD,
	APE_EVCTL_DEL,

	APE_EVCTL_END
};

// event module callback handler
typedef int (*ape_evhandler_t)( ape_evfd_t fd, ape_event_t events, void *arg );

/****************************************************************/
/*		Event API												*/
/****************************************************************/
// event module
APE_DECLARE(ape_evmdl_t*)	ape_evmdl_new( ape_evbase_t *base, ape_evfd_t fd, ape_event_t events, ape_evhandler_t cb, void *arg );
APE_DECLARE(int)			ape_evmdl_free( ape_evmdl_t *evmdl );

// do NOT use ape_evmdl_free
APE_DECLARE(int)		ape_evmdl_assign( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evfd_t fd, ape_event_t events, ape_evhandler_t cb, void *arg );

APE_DECLARE(int)			ape_evtsig_init( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evfd_t signum, ape_evhandler_t cb, void *arg );
APE_DECLARE(int)			ape_evtimer_init( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evhandler_t cb, void *arg );

APE_DECLARE(ape_evfd_t)		ape_evmdl_fd( struct ape_evmdl_t *evmdl );

APE_DECLARE(int)			ape_evmdl_ctl( ape_evmdl_t *evmdl, int ops, ape_event_t events );
APE_DECLARE(ape_event_t)	ape_evmdl_events( ape_evmdl_t *evmdl );

APE_DECLARE(int)			ape_evmdl_set_persist( ape_evmdl_t *evmdl, int on );
APE_DECLARE(int)			ape_evmdl_is_persist( ape_evmdl_t *evmdl );

APE_DECLARE(int)			ape_evmdl_set_etmode( ape_evmdl_t *evmdl, int on );
APE_DECLARE(int)			ape_evmdl_is_etmode( ape_evmdl_t *evmdl );

APE_DECLARE(int)			ape_evmdl_register( ape_evmdl_t *evmdl, ape_utime_t timeout );
APE_DECLARE(int)			ape_evmdl_unregister( ape_evmdl_t *evmdl );


APE_DECLARE(ape_size_t)		ape_evmdl_get_size(void);

// event base 
APE_DECLARE(ape_evbase_t*)	ape_evbase_new(void);
APE_DECLARE(int)			ape_evbase_free( ape_evbase_t *base );

APE_DECLARE(int)			ape_evbase_loop( ape_evbase_t *base, int flag );
APE_DECLARE(int)			ape_evbase_dispatch( ape_evbase_t *base );

APE_DECLARE(int)			ape_evbase_mksig( ape_evbase_t *base );

#ifdef __cplusplus
}
#endif

#endif /*__APE_EVT_H__*/
