#ifndef APP_GENER

//#define SNAPSHOT_VERSION

#define APP_GENER 0
#define APP_MAJOR 0
#define APP_MINOR 107
#define APP_PATCH 0
#define APP_VER_STRING APP_GENER.APP_MAJOR.APP_MINOR.APP_PATCH


#ifdef SNAPSHOT_VERSION
#define VER_PREFIX( N ) v##N-SNAPSHOT
#else
#define VER_PREFIX( N ) v##N
#endif


#define HSTR( N ) #N
#define STR( N ) HSTR( N )
#define VER_STR( N ) STR( VER_PREFIX( N ) )

#endif
