#ifndef SCREEN_H
#define SCREEN_H

// Basic libraries
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>

using std::cout, std::cin, std::string, std::vector;

class Screen
{
public:
    int pallColor[1][3] = {{255,100,0}};
    int Toller = 4;
    HWND hWindow = {0};
    HDC hdc;
    POINT centerPos = {0};
    HDC gameHDC;
    RECT gameRect;
    HBITMAP hBitmap;
    HBITMAP hBitold;
    BITMAP bmInfo;
    BITMAPINFO bitInfo;
    vector<POINT>Pixels;

    void TakeScreenShot();
    void CopyToClipoard(HBITMAP hBitmap);
    void GetBitmapinfo();
    double Get2Ddistance(POINT A, POINT B);
    POINT PixelsPos(vector<POINT> &Pixels, POINT Player);
    POINT GetCloseset(vector<POINT> &Pixels, POINT Player);
    COLORREF GetCurrentPosPixelColor(HDC hdc);
    void Click(POINT pixel);
};

#endif // SCREEN_H



