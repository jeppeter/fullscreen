#ifndef  __OUTPUT_DEBUG_H__
#define  __OUTPUT_DEBUG_H__

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define  DEBUG_INFO(fmt,...) DebugOutString(__FILE__,__LINE__,fmt,__VA_ARGS__)

extern "C" void DebugOutString(const char* file,int lineno,const char* fmt,...);

#ifdef __cplusplus
}
#endif



#endif /*__OUTPUT_DEBUG_H__*/