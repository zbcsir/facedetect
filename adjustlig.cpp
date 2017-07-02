#include "adjustlig.h"
#include <tchar.h>
#include <QLibrary>

AdjustLig::AdjustLig()
{
//Initialize all variables.
//    hGDI32 = NULL;
    hScreenDC = NULL;
    pGetDeviceGammaRamp = NULL;
    pSetDeviceGammaRamp = NULL;
}

AdjustLig::~AdjustLig()
{
//    FreeLibrary();
}


BOOL AdjustLig::LoadLibrary()
{
    BOOL bReturn = FALSE;

//    FreeLibrary();
    //Load the GDI library.
//    QLibrary hGDI32("gdi32.dll");
//    hGDI32 = ::LoadLibrary(_T("gdi32.dll"));
    if (hGDI32 != NULL)
    {
        //Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API functions.
        pGetDeviceGammaRamp =
            (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");
        pSetDeviceGammaRamp =
            (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");
        //Return TRUE only if these functions exist.
        if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
            FreeLibrary();
        else
            bReturn = TRUE;
    }

    return bReturn;
}


void AdjustLig::FreeLibrary()
{
    //Free the GDI library.
    if (hGDI32 != NULL)
    {
        ::FreeLibrary(hGDI32);
        hGDI32 = NULL;
    }
}


BOOL AdjustLig::LoadLibraryIfNeeded()
{
    BOOL bReturn = FALSE;

    if (hGDI32 == NULL)
        LoadLibrary();

    if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
        bReturn = TRUE;

    return bReturn;
}


BOOL AdjustLig::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
    //Call to SetDeviceGammaRamp only if this function is successfully loaded.
    if (LoadLibraryIfNeeded())
    {
        return pSetDeviceGammaRamp(hDC, lpRamp);
    }
    else
        return FALSE;
}


BOOL AdjustLig::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
//Call to GetDeviceGammaRamp only if this function is successfully loaded.
    if (LoadLibraryIfNeeded())
    {
        return pGetDeviceGammaRamp(hDC, lpRamp);
    }
    else
        return FALSE;

}


BOOL AdjustLig::SetBrightness(HDC hDC, WORD wBrightness)
{
    BOOL bReturn = FALSE;
    HDC hGammaDC = hDC;

    //Load the display device context of the entire screen if hDC is NULL.
    if (hDC == NULL)
    hGammaDC = GetDC(NULL);

    if (hGammaDC != NULL)
    {
    //Generate the 256-colors array for the specified wBrightness value.
    WORD GammaArray[3][256];

    for (int iIndex = 0; iIndex < 256; iIndex++)
    {
        int iArrayValue = iIndex * (wBrightness + 128);

        if (iArrayValue > 65535)
            iArrayValue = 65535;

        GammaArray[0][iIndex] =
        GammaArray[1][iIndex] =
        GammaArray[2][iIndex] = (WORD)iArrayValue;
    }

    //Set the GammaArray values into the display device context.
    bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
}

    if (hDC == NULL)
        ReleaseDC(NULL, hGammaDC);

    return bReturn;
}

