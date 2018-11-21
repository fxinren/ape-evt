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

/****************************************************************/
/*		Event Data												*/
/****************************************************************/
typedef ape_evfd_t			ape_evfd_t;
typedef ape_event_t			ape_event_t;

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

// ape_evmdl_ctl(): ops values
enum {
	APE_EVCTL_ADD = 0x01,
	APE_EVCTL_MOD,
	APE_EVCTL_DEL,

	APE_EVCTL_END
};

typedef struct _tag_event_module_t	ape_evmdl_t;

typedef struct _tag_event_base_t	ape_evbase_t;

// event module callback handler
typedef int (*ape_evhandler_t)( ape_evfd_t fd, ape_event_t events, void *arg );

/****************************************************************/
/*		Event API												*/
/****************************************************************/
// event module
APE_DECLARE(ape_evmdl_t*)	ape_evmdl_new( ape_evmdl_cat_e cat, ape_evbase_t *base, ape_evhandler_t cb, void *arg );
// do NOT use ape_evmdl_free
APE_DECLARE(int)		ape_evmdl_assign( ape_evmdl_t* evmdl, ape_evmdl_cat_e cat, ape_evbase_t *base, ape_evhandler_t cb, void *arg );

APE_DECLARE(int)			ape_evmdl_free( ape_evmdl_t *evmdl );

APE_DECLARE(int)			ape_evmdl_ctl( ape_evmdl_t *evmdl, int ops, ape_event_t events );

APE_DECLARE(int)			ape_evmdl_add( ape_evmdl_t *evmdl, int timeout );
APE_DECLARE(int)			ape_evmdl_del( ape_evmdl_t *evmdl );

APE_DECLARE(ape_size_t)		ape_evmdl_get_size(void);

// event base 
APE_DECLARE(ape_evbase_t*)	ape_evbase_new(void);
APE_DECLARE(int)			ape_evbase_free( ape_evbase_t *base );

APE_DECLARE(int)			ape_evbase_loop( ape_evbase_t *base, int flag );
APE_DECLARE(int)			ape_evbase_dispatch( ape_evbase_t *base );

#ifdef __cplusplus
}
#endif

#endif /*__APE_EVT_H__*/
