#include "Screen.h"

void startBot(Screen& src1)
{
    Sleep(50);

    // copy image of screen
    src1.TakeScreenShot();

    //src1.CopyToClipoard(src1.hBitmap);

    /* copy this screen to the clipboard ctrl-c / to paste to paint or something, click ctrl-v */

    uint16_t middleX = (uint16_t)(src1.bmInfo.bmWidth / 2);
    uint16_t middleY = (uint16_t)(src1.bmInfo.bmHeight / 2);

    if (src1.centerPos.x != 0.0 || src1.centerPos.y != 0.0)
    {
        middleX = src1.centerPos.x - src1.gameRect.left;
        middleY = src1.centerPos.y - src1.gameRect.top;
    }
    POINT Closest = src1.PixelsPos(src1.Pixels, {middleX, middleY});
    Closest.x += src1.gameRect.left+2;
    Closest.y += src1.gameRect.top-1;

    // Aim on the closest pixel on the screen
    SetCursorPos(Closest.x,Closest.y);

    // Click on it
    src1.Click(Closest);
    Sleep(50);
}
void optionMenu(Screen& src1)
{
    Sleep(100);
    while (true)
    {
        int num = 0;
        cout<<"Option menu: \n";
        for (int i = 0; i<35; i++) {cout<<"-";}
        cout<<"\n";
        cout<<"1. Choose area of bot \n";
        cout<<"2. Custom center position \n";
        cout<<"3. Write color tollerance ( "<<src1.Toller<<" )\n";
        cout<<"4. Exit \n";
        for (int i = 0; i<35; i++) {cout<<"-";}
        cout<<"\n";
        cin>>num;
        switch(num)
        {
            case 1:
            {
                POINT e;
                while (!GetAsyncKeyState(0x4D))
                {
                    cout<<"Press m on the top left corner";
                    Sleep(100);
                    system("CLS");
                }
                if (GetCursorPos(&e))
                {
                    src1.gameRect.top = e.y; src1.gameRect.left = e.x;
                }
                Sleep(100);
                while (!GetAsyncKeyState(0x4D))
                {
                    cout<<"Now, press m on the bottom right corner"; Sleep(100); system("CLS");
                }
                if (GetCursorPos(&e))
                {
                    src1.gameRect.bottom = e.y; src1.gameRect.right = e.x;
                }
                    Sleep(100);
                    break;
            }
            case 2:
                {
                    while (!GetAsyncKeyState(0x4D))
                    {
                        cout<<"Press m on the center position";
                        Sleep(100);
                        system("CLS");
                    }
                    GetCursorPos(&src1.centerPos);
                    break;
                }
            case 3:
                {
                    system("cls");
                    cin>>src1.Toller;
                    break;
                }
            case 4:
                {
                    system("cls");
                    return;
                }
        }
        Sleep(200);
        system("cls");
    }
}
void choosePixelColor(Screen& src1)
{
    cout<<"Move mouse on the pixel\non the screen you want to choose\nand click p to select this color\n";
    while (!GetAsyncKeyState(0x50))
    {
        COLORREF color = src1.GetCurrentPosPixelColor(GetDC(NULL));
        src1.pallColor[0][0] = GetRValue(color);
        src1.pallColor[0][1] = GetGValue(color);
        src1.pallColor[0][2] = GetBValue(color);
        Sleep(100);
    }
    cout<<"\nYour color: "<<src1.pallColor[0][0]<<" "<<src1.pallColor[0][1]<<" "<<src1.pallColor[0][2]<<"\n";
    Sleep(1000);
}
int main()
{
    HWND console = GetConsoleWindow();
    SetConsoleTitle("Simple Pixel Bot");
    MoveWindow(console, 100, 100, 330, 180, true);
    Screen src1;
    Sleep(200);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        int num = 0;
        cout<<"Choose option: \n";
        for (int i = 0; i<35;i++) cout<<"-";
        cout<<"\n";
        cout<<"1. Run Bot\n";
        cout<<"2. Options\n";
        cout<<"3. Exit\n";
        for (int i = 0; i<35;i++) cout<<"-";
        cout<<"\n";
        cin>>num;
        system("CLS");
        switch(num)
        {
            case 1:
                {
                    choosePixelColor(src1);
                    while (!GetAsyncKeyState(VK_ESCAPE))
                    {
                        cout<<"Click k to aim and click to pixel\n";
                        if (GetAsyncKeyState(0x4B))
                        {
                            startBot(src1);
                        }
                        Sleep(75);
                        system("cls");
                    }
        break;}
            case 2:
                {
                    optionMenu(src1);
                    break;
                }
            case 3:
                {
                    return 0; break;
                }
        }
        Sleep(200);
        system("CLS");
    }
    return 0;
}

