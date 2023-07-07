#include "Screen.h"

void Screen::TakeScreenShot()
{
    hdc = GetDC(0);
    gameHDC = CreateCompatibleDC(hdc);
    hBitmap = CreateCompatibleBitmap(hdc, gameRect.right - gameRect.left, gameRect.bottom - gameRect.top);
    // Select bitmap on hdc
    hBitold = (HBITMAP)SelectObject(gameHDC , hBitmap);
    GetObjectA(hBitmap, sizeof(bmInfo), &bmInfo);
    // Copy from source HDC to destination HDC
    BitBlt(gameHDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, hdc, gameRect.left, gameRect.top, SRCCOPY);
}
void Screen::CopyToClipoard(HBITMAP hBitmap)
{
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
}
void Screen::GetBitmapinfo()
{
    // Basic bitmap info -- usualy the same
    bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitInfo.bmiHeader.biWidth = bmInfo.bmWidth;
    bitInfo.bmiHeader.biHeight = -bmInfo.bmHeight;
    bitInfo.bmiHeader.biPlanes = 1;
    bitInfo.bmiHeader.biBitCount = 32;
    bitInfo.bmiHeader.biCompression = BI_RGB;
    bitInfo.bmiHeader.biSizeImage = 0;
    bitInfo.bmiHeader.biClrImportant = 0;
}
POINT Screen::PixelsPos(vector<POINT> &Pixels, POINT Player)
{
    GetBitmapinfo();
    // Create pixel table
    RGBQUAD *_rgb = new RGBQUAD[bmInfo.bmWidth * bmInfo.bmHeight];
    // Get pixels from hdc and copy it to my table
    GetDIBits(gameHDC, hBitmap, 0, bmInfo.bmHeight, _rgb, &bitInfo, DIB_RGB_COLORS);

    int j = 0;
    bool flag = false;
    // Default posisiton of the closest pixel
    POINT closest = {-1000, -1000};
    double minD = Get2Ddistance(closest, Player);

    // Iterate through every pixel on the screen -- for optimlize remove sleeps and add more than 1 to the iterator every iteration -- you need change (i, j, k)
    // i - x position on bitmap  -- j - y position on bitmap -- k - number of pixel
    for(int i = 0; i < bmInfo.bmHeight; i++)
    {
       long int k = 0;
        while (k < bmInfo.bmWidth)
        {
            // Check for valid color
            for (long long unsigned int l = 0; l< sizeof(pallColor)/sizeof(pallColor[0]); l++)
            {
                if (abs((int)(_rgb[j].rgbRed) - pallColor[l][0])<Toller)
                {
                    if (abs((int)(_rgb[j].rgbGreen) - pallColor[l][1])<Toller)
                    {
                        if (abs((int)(_rgb[j].rgbBlue) - pallColor[l][2])<Toller)
                        {
                            flag = true;
                            break;
                        }}}
            }
            if (flag)
            {
                double delta = Get2Ddistance({k,i}, Player);
                if (delta < minD)
                {
                    minD = delta;
                    Sleep(0.5);
                    closest = {k,i};
                }
                if (k+12 <bmInfo.bmWidth)
                    {k+=12; j+=12;}
                else if (k+12 >= bmInfo.bmWidth)
                    {int tmp = bmInfo.bmWidth - k;k += tmp;j += tmp +1;}
                Sleep(0.5);
                flag = false;
            }
            else
            {k++;j++;}
            Sleep(0.2);
        }

    }
    // Mandatory trash collect do not remove !
    delete[] _rgb;
    SelectObject(gameHDC, hBitold);
    DeleteObject(hBitmap);
    DeleteObject(hBitold);
    DeleteDC(gameHDC);
    return closest;
}
double Screen::Get2Ddistance(POINT A, POINT B)
{
    return sqrt( (abs(A.y - B.y) * abs(A.y - B.y)) + (abs(A.x - B.x) * abs(A.x - B.x)));
}
void Screen::Click(POINT pixel)
{
    SetCursorPos(pixel.x, pixel.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0,0,0);
    Sleep(75);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0,0,0);
}
COLORREF Screen::GetCurrentPosPixelColor(HDC hdc)
{
    POINT point;
    GetCursorPos(&point);
    return GetPixel(hdc, point.x, point.y);
}
