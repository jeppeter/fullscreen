

#include "dxstdafx.h"
#include "scrcap.h"
#include "output_debug.h"

extern "C" int  CaptureFile(IDirect3D9* pD3D,IDirect3DDevice9* pDevice,const char* filetosave)
{
    D3DDISPLAYMODE D3DMode;
    HRESULT hr;
    LPDIRECT3DSURFACE9 pSurface = NULL;
    LPWSTR pFileName=NULL;
    BOOL bret;
    int ret;
    if (pDevice== NULL || pD3D==NULL)
    {
        DEBUG_INFO("pDevice is NULL\n");
        ret=  -ERROR_INVALID_HANDLE;
        goto fail;
    }

    hr = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DMode);
    if (FAILED(hr))
    {
        DEBUG_INFO("could not get adapter mode 0x%08x\n",hr);
		ret = -(int)GetLastError() ? - (int)GetLastError(): -1;
        goto fail;
    }

    hr = pDevice->CreateOffscreenPlainSurface(D3DMode.Width,
            D3DMode.Height,
            D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pSurface, NULL);
    if (FAILED(hr))
    {
        DEBUG_INFO("could not create surface\n");
		ret = -(int)GetLastError() ? - (int)GetLastError(): -1;
        goto fail;
    }

    pFileName = new wchar_t[8000];
    bret = MultiByteToWideChar(CP_ACP,NULL,filetosave,-1,pFileName,8000);
    if (!bret)
    {
        DEBUG_INFO("can not save file %s\n",filetosave);
		ret = -(int)GetLastError() ? - (int)GetLastError(): -1;
        goto fail;
    }


    hr = D3DXSaveSurfaceToFile(pFileName, D3DXIFF_BMP, pSurface, NULL, NULL);
    if (FAILED(hr))
    {
        DEBUG_INFO("could not save file %s\n",filetosave);
		ret = -(int)GetLastError() ? - (int)GetLastError(): -1;
        goto fail;
    }
    if (pSurface)
    {
        pSurface->Release();
    }
    pSurface = NULL;
    if (pFileName)
    {
        delete [] pFileName;
    }
    pFileName = NULL;

    return 0;

fail:
    if (pSurface)
    {
        pSurface->Release();
    }
    pSurface = NULL;
    if (pFileName)
    {
        delete [] pFileName;
    }
    pFileName = NULL;
    return ret;
}

