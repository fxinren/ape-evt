/************************************************************************************
* ape_evbase.c: Implementation File
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
#include "ape_evbase.h"
#include "internal/evbase.h"
#include "ape_evt.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

APE_DECLARE(int) ape_evbase_loop( ape_evbase_t *base, int flag ) {
	int done = 0;

	while ( !done ) {
		if ( base->stop_flag & GOT_TREM ) {
			break;
		}
	}
}

APE_DECLARE(int) ape_evbase_dispatch( ape_evbase_t *base ) {
}
