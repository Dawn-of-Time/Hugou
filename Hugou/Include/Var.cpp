#include "Var.h"

double scale = calculateScale();

double calculateScale()
{
    int nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
    HWND hwd = ::GetDesktopWindow();
    HDC hdc = ::GetDC(hwd);
    int width = GetDeviceCaps(hdc, DESKTOPHORZRES);
    int height = GetDeviceCaps(hdc, DESKTOPVERTRES);
    double dWidth = (double)width;
    double dScreenWidth = (double)nScreenWidth;
    return dWidth / dScreenWidth;
}

double getScale() { return scale; }