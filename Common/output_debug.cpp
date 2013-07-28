
#include "output_debug.h"
#include "dxstdafx.h"



extern "C" void InnerDebug(char* pFmtStr)
{
#ifdef UNICODE
    LPWSTR pWide=NULL;
    int len;
    BOOL bret;
    len = (int) strlen(pFmtStr);
    pWide = new wchar_t[len*2];
    bret = MultiByteToWideChar(CP_ACP,NULL,pFmtStr,-1,pWide,len*2);
    if (bret)
    {
        OutputDebugString(pWide);
    }
    else
    {
        OutputDebugString(L"can not change fmt string");
    }
    delete [] pWide;
#else
    OutputDebugString(pFmtStr);
#endif
    return ;
}

extern "C" void DebugOutString(const char* file,int lineno,const char* fmt,...)
{
    char* pFmt=NULL;
    char* pLine=NULL;
    char* pWhole=NULL;
    va_list ap;

    pFmt = new char[2000];
    pLine = new char[2000];
    pWhole = new char[4000];

    _snprintf_s(pLine,2000,1999,"%s:%d\t",file,lineno);
    va_start(ap,fmt);
    _vsnprintf_s(pFmt,2000,1999,fmt,ap);
    strcpy_s(pWhole,4000,pLine);
    strcat_s(pWhole,4000,pFmt);

	InnerDebug(pWhole);
    delete [] pFmt;
    delete [] pLine;
    delete [] pWhole;

    return ;
}

