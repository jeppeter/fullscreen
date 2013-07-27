
#include "output_debug.h"
#include "dxstdafx.h"



void DebugOutString(const char* file,int lineno,const char* fmt,...)
{
	char* pFmt=NULL;
	char* pLine=NULL;
	char* pWhole=NULL;
	LPWSTR pWChar=NULL;
	BOOL bret;
	va_list ap;

	pFmt = new char[2000];
	pLine = new char[2000];
	pWhole = new char[4000];

	_snprintf_s(pLine,2000,1999,"%s:%d\t",file,lineno);
	va_start(ap,fmt);
	_vsnprintf_s(pFmt,2000,1999,fmt,ap);
	strcpy_s(pWhole,4000,pLine);
	strcat_s(pWhole,4000,pFmt);

#ifdef UNICODE
	pWChar = new wchar_t[8000];
	bret = MultiByteToWideChar(CP_ACP,NULL,pWhole,-1,pWChar,8000);
	if (bret)
	{
		OutputDebugString(pWChar);
	}
	else
	{
		OutputDebugString(L"can not change multichar\n");
	}
#else
	OutputDebugString(pWhole);
#endif
	delete [] pFmt;
	delete [] pLine;
	delete [] pWhole;

	if (pWChar)
	{
		delete [] pWChar;
	}
	pWChar = NULL;
	return ;
}

