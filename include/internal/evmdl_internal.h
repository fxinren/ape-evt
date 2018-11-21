/************************************************************************************
* evmdl_internal.h : header file
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

#if !defined(__APE_EVMDL_INTERNAL_H__)
#define __APE_EVMDL_INTERNAL_H__

#include "ape_evmdl.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************/
/*		Event Module											*/
/****************************************************************/

typedef struct _tag_evmdlcb_t {
	union {
		int (*evcb_callback)( ape_evfd_t, ape_event_t, void* );
		int (*evcb_selfcb)( struct _tag_evmdlcb_t*, void* );
		int (*evcb_evfinalize)( ape_evmdl_t*, void* );
		int (*evcb_cbfinalize)( struct _tag_evmdlcb_t*, void* );
	};
	void *arg;
} evmdlcb_t;

typedef struct _tag_evbase_t ape_evbase_t;
struct _tag_event_module_t {
	evmdlcb_t		callback;
	ape_evbase_t	*base;
	ape_event_t		events;
	ape_evfd_t		fd;
	int				interval;
};


#ifdef __cplusplus
}
#endif

#endif /* __APE_EVMDL_INTERNAL_H__ */
