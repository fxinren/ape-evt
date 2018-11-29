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
//#include "internal/evmdl.h"
#include "internal/evbase.h"
#include "ape_evt.h"

#if defined(__cplusplus)
extern "C" {
#endif
	
#define APE_EV_PERSIST        0x20
#define APE_EV_ET             0x40

static int _is_evbase_thread( struct ape_evbase_t *base );

#define IO_EVT_SET			(APE_EV_READ|APE_EV_WRITE|APE_EV_CLOSED|APE_EV_TIMEOUT)
#define SIG_EVT_SET			(APE_EV_SIG|APE_EV_TIMEOUT)
#define TIMER_EVT_SET		(APE_EV_TIMEOUT)

#define _is_sigevent(events)		((events)&APE_EV_SIG)
#define _is_ioevent(events)			((events)&(APE_EV_READ|APE_EV_WRITE|APE_EV_CLOSED))

#define _is_persist(events)			((events)&(APE_EV_PERSIST))
#define _is_et(events)				((events)&(APE_EV_ET))

#if defined(__cplusplus)
}
#endif

APE_DECLARE(struct ape_evmdl_t*) ape_evmdl_new( ape_evbase_t *base, ape_evfd_t fd, ape_event_t events, ape_evhandler_t cb, void *arg ) {
	struct ape_evmdl_t *evmdl = NULL;

	evmdl = ape_malloc( sizeof(struct ape_evmdl_t) );
	if ( evmdl == NULL ) {
		return NULL;
	}
	
	if ( ape_evmdl_assign(evmdl, base, fd, events, cb, arg) ) {
		ape_free( evmdl );
		evmdl = NULL;
	}

	return evmdl;
}

APE_DECLARE(int) ape_evmdl_free( struct ape_evmdl_t *evmdl ) {
	if ( evmdl ) {
		ape_free( evmdl );
	}

	return 0;
}

// do NOT use ape_evmdl_free
APE_DECLARE(int) ape_evmdl_assign( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evfd_t fd, ape_event_t events, ape_evhandler_t cb, void *arg ) {
	int ret = 0;

	if ( _is_sigevent(events) ) {
		if ( _is_ioevent(events) ) {
			// EV_SIGNAL is not compatible with EV_READ, EV_WRITE or EV_CLOSED
			ret = -1;
			goto lbl_err:
		}
	}

	evmdl->base = base;
	evmdl->fd = fd;

	evmdl->events = events;

	evmdl->cb.callback = cb;
	evmdl->cb.arg = arg;

lbl_err:

	return ret;
}

APE_DECLARE(int) ape_evtsig_init( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evfd_t signum, ape_evhandler_t cb, void *arg ) {

	if ( ape_evmdl_assign(evmdl, base, fd, APE_EV_SIG|APE_EV_PERSIST, cb, arg) ) {
		return -1;
	}

	return 0;
}

APE_DECLARE(int) ape_evtimer_init( ape_evmdl_t *evmdl, ape_evbase_t *base, ape_evhandler_t cb, void *arg ) {
	
	if ( ape_evmdl_assign(evmdl, base, fd, APE_EV_TIMER, cb, arg) ) {
		return -1;
	}

	return 0;
}

APE_DECLARE(ape_evfd_t) ape_evmdl_fd( struct ape_evmdl_t *evmdl ) {
	return evmdl->fd;
}

APE_DECLARE(int) ape_evmdl_ctl( struct ape_evmdl_t *evmdl, int ops, ape_event_t events ) {
	int ret = 0;
	int _events = 0;

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

APE_DECLARE(int) ape_evmdl_register( struct ape_evmdl_t *evmdl, int timeout ) {
	struct ape_evbase_t *base = NULL;
	return 0;
}

APE_DECLARE(int) ape_evmdl_unregister( struct ape_evmdl_t *evmdl ) {
	return 0;
}

APE_DECLARE(ape_size_t) ape_evmdl_get_size(void) {
	return sizeof(struct ape_evmdl_t);
}

APE_DECLARE(ape_event_t) ape_evmdl_events( struct ape_evmdl_t *evmdl ) {
	return (evmdl->events & (~(ape_event_t)(APE_EV_PERSIST|APE_EV_ET)));
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
