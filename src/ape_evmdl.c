/************************************************************************************
* ape_evmdl.c: Implementation File
*
* DESCRIPTION  :   
*
* AUTHOR		:	Sean Feng <SeanFeng2006@hotmail.com>
* DATE			:	Sep. 24, 2010
*
* Copyright (c) 2010-?. All Rights Reserved.
*
* REMARKS:
*		
*	  
************************************************************************************/
#include "ape_mem.h"
#include "ape_threadproc.h"
#include "ape_evmdl.h"
#include "internal/evmdl.h"
#include "ape_evt.h"

#if defined(__cplusplus)
extern "C" {
#endif
	
static int _is_evbase_thread( struct ape_evbase_t *base );

#define IO_EVT_SET			(APE_EV_READ|APE_EV_WRITE|APE_EV_TIMEOUT)
#define SIG_EVT_SET			(APE_EV_SIG|APE_EV_TIMEOUT)
#define TIMER_EVT_SET		(APE_EV_TIMEOUT)

#if defined(__cplusplus)
}
#endif

APE_DECLARE(struct ape_evmdl_t*) ape_evmdl_new( ape_evcat_e cat, struct ape_evbase_t *base, ape_evhandler_t cb, void *arg ) {
	struct ape_evmdl_t *evmdl = NULL;

	evmdl = ape_malloc( sizeof(struct ape_evmdl_t) );
	if ( evmdl == NULL ) {
		return NULL;
	}
	
	if ( ape_evmdl_assign(evmdl, cat, base, cb, arg) ) {
		ape_free( evmdl );
		evmdl = NULL;
	}

	return evmdl;
}

// do NOT use ape_evmdl_free
APE_DECLARE(int) ape_evmdl_assign( struct ape_evmdl_t *evmdl, ape_evcat_e cat, struct ape_evbase_t *base, ape_evhandler_t cb, void *arg ) {
	int ret = 0;
	ape_event_t events = APE_EV_NONE;

	switch ( cat ) {
	case APE_EVCAT_IO:
		break;
	case APE_EVCAT_SIG:
		events = APE_EV_SIG;
		break;
	case APE_EVCAT_TIMER:
		events = APE_EV_TIMEOUT;
		evmdl->fd = _APE_EVFD_INVALID_;
		break;
	default:
		ret = -1;
		break;
	}

	if ( ret == 0 ) {
		evmdl->base = base;
		evmdl->cat = cat;
		evmdl->events = events;
		evmdl->cb.evcb_callback = cb;
		evmdl->cb.arg = arg;
	}

	return ret;
}

APE_DECLARE(int) ape_evmdl_free( struct ape_evmdl_t *evmdl ) {
	if ( evmdl ) {
		ape_free( evmdl );
	}

	return 0;
}

APE_DECLARE(int) ape_evmdl_setfd( struct ape_evmdl_t *evmdl, ape_evfd_t fd ) {
	if ( evmdl->cat == APE_EVCAT_TIMER ) {
		return -1;
	}

	evmdl->fd = fd;
	return 0;
}

APE_DECLARE(ape_evfd_t) ape_evmdl_fd( struct ape_evmdl_t *evmdl ) {
	return evmdl->fd;
}

APE_DECLARE(int) ape_evmdl_ctl( struct ape_evmdl_t *evmdl, int ops, ape_event_t events ) {
	int ret = 0;
	int _events = 0;

	switch ( evmdl->cat ) {
	case APE_EVCAT_IO:
		_events = (events & IO_EVT_SET);
		break;
	case APE_EVCAT_SIG:
		_events = (events & SIG_EVT_SET);
		break;
	case APE_EVCAT_TIMER:
		_events = (events & TIMER_EVT_SET);
		break;
	default:
		ret = -1;
		break;
	}

	if ( ret==-1 || _events!=events ) {
		return -1;
	}

	switch ( ops ) {
	case APE_EVCTL_ADD:
		evmdl->events |= _events;
		break;
	case APE_EVCTL_DEL:
		evmdl->events &= (~((ape_event_t)_events));
		break;
	case APE_EVCTL_MOD:
		evmdl->events = _events;
		break;
	default:
		ret = -1;
		break;
	}

	if ( ret == -1 ) {
		return -1;
	}

	return ret;
}

APE_DECLARE(int) ape_evmdl_add( struct ape_evmdl_t *evmdl, int timeout ) {
	struct ape_evbase_t *base = NULL;
	return 0;
}

APE_DECLARE(int) ape_evmdl_del( struct ape_evmdl_t *evmdl ) {
	return 0;
}

APE_DECLARE(ape_size_t) ape_evmdl_get_size(void) {
	return sizeof(struct ape_evmdl_t);
}

APE_DECLARE(ape_event_t) ape_evmdl_events( struct ape_evmdl_t *evmdl ) {
	return (evmdl->events & (APE_EV_PERSIST|APE_EV_ET));
}

APE_DECLARE(int) ape_evmdl_set_persist( struct ape_evmdl_t *evmdl, int on ) {
	if ( on ) {
		evmdl->events |= APE_EV_PERSIST;
	} else {
		evmdl->events &= (~((ape_event_t)APE_EV_PERSIST));
	}

	return 0;
}

APE_DECLARE(int) ape_evmdl_is_persist( struct ape_evmdl_t *evmdl ) {
	return ((evmdl->events & APE_EV_PERSIST) == APE_EV_PERSIST);
}

APE_DECLARE(int) ape_evmdl_set_etmode( struct ape_evmdl_t *evmdl, int on ) {
	if ( on ) {
		evmdl->events |= APE_EV_ET;
	} else {
		evmdl->events &= (~((ape_event_t)APE_EV_ET));
	}

	return 0;
}

APE_DECLARE(int) ape_evmdl_is_etmode( struct ape_evmdl_t *evmdl ) {
	return ((evmdl->events & APE_EV_ET) == APE_EV_ET);
}

///////////////////////////////////////////////////////
static int _is_evbase_thread( struct ape_evbase_t *base ) {
	if ( base->tid == ape_os_thread_self() ) {
		return 1;
	}

	return 0;
}
