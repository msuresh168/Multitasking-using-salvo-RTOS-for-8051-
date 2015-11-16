/************************************************************ 
Copyright (C) 1995-2002 Pumpkin, Inc. and its
Licensor(s). Freely distributable.

$Source: C:\\RCS\\D\\salvo\\tutorial\\tu1\\sysi\\salvocfg.h,v $
$Author: aek $
$Revision: 1.2 $
$Date: 2001-11-21 10:52:56-08 $

Header file for tutorial programs.

************************************************************/

#if   defined(MAKE_WITH_FREE_LIB)
/*                                                          */
/*  Salvo Lite build                                        */
/*                                                          */
#define OSUSE_LIBRARY				TRUE
#define OSLIBRARY_TYPE				OSF
#define OSLIBRARY_GLOBALS			OSD
#define OSLIBRARY_CONFIG 			OSM
#define OSLIBRARY_VARIANT			OSB
#define OSEVENTS                    0  /* multitasking only */
#define OSEVENT_FLAGS               0
#define OSMESSAGE_QUEUES            0
#define OSTASKS                     2


#elif defined(MAKE_WITH_STD_LIB)
/*                                                          */
/*  Salvo LE & Pro library build                            */
/*                                                          */
#define OSUSE_LIBRARY				TRUE
#define OSLIBRARY_TYPE				OSL
#define OSLIBRARY_GLOBALS			OSD
#define OSLIBRARY_CONFIG 			OSM
#define OSLIBRARY_VARIANT			OSB
#define OSEVENTS                    0  /* multitasking only */
#define OSEVENT_FLAGS               0
#define OSMESSAGE_QUEUES            0
#define OSTASKS                     2


#elif defined(MAKE_WITH_SOURCE) 
/*                                                          */
/*  Salvo Pro source-code build                             */
/*                                                          */
#define OSEVENTS					0  /* multitasking only */
#define OSLOC_ALL					data
#define OSTASKS	                    2


#else

#error No MAKE_WITH_??? symbol defined. See salvocfg.h.

#endif

#if !defined(SYSI)

#error SYSI must be defined for this Cx51 tutorial project ...

#endif


