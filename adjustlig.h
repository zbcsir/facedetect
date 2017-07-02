#ifndef ADJUSTLIG_H
#define ADJUSTLIG_H
#include <windows.h>
#include <QLibrary>

/*
 * 调节屏幕亮度类
 */

class AdjustLig
{
public:
    AdjustLig();
    ~AdjustLig() ;
    BOOL LoadLibrary();
    void FreeLibrary();
    BOOL LoadLibraryIfNeeded();
    BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
    BOOL GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
    BOOL SetBrightness(HDC hDC, WORD wBrightness);

protected:
    HMODULE hGDI32;
//    QLibrary hGDI32 ;
    HDC hScreenDC;
    typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

    Type_SetDeviceGammaRamp pGetDeviceGammaRamp;
    Type_SetDeviceGammaRamp pSetDeviceGammaRamp;
};

#endif // ADJUSTLIG_H
