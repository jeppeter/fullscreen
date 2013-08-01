#include "..\\scwlapi\\commdef-int.h"
#include "..\\detours\\detours.h"
#include "..\\common\\output_debug.h"


int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	si.cb = sizeof(si);

	BOOL ret = 
	DetourCreateProcessWithDllW(
		L"z:\\Blobs.exe",
		NULL,
		NULL,
		NULL,
		TRUE,
		CREATE_DEFAULT_ERROR_MODE,
		NULL,
		NULL,
		&si,
		&pi,
		NULL,
		"blob.dll",
		NULL);
	DEBUG_INFO("\n");

	if(!ret)
	{
		MessageBoxW(NULL, L"����Blobs.exeʧ��!", L"", MB_OK);
	}

	return 0;
}