#include <Windows.h>
#include <process.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;
unsigned __stdcall InkeyBoardThread(void *param);
string getTime();

int main(int argc, char* argv[])
{
    TCHAR consoleName[12] = __TEXT("keyboard");
    SetConsoleTitle(__TEXT("keyboard"));

    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, InkeyBoardThread, (void*)consoleName, 0, NULL);
    CloseHandle(hThread);

    char b;
    cin >> b;
    return 0;
}

string getTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

unsigned __stdcall InkeyBoardThread(void *param)
{
    INPUT myInput[4];
    memset(myInput, 0, sizeof(myInput));
    myInput[0].type = INPUT_KEYBOARD;
    myInput[0].ki.dwFlags = 0;
    myInput[0].ki.wVk = VK_SHIFT;

    myInput[1].type = INPUT_KEYBOARD;
    myInput[1].ki.dwFlags = KEYEVENTF_KEYUP;
    myInput[1].ki.wVk = VK_SHIFT;

    myInput[2].type = INPUT_KEYBOARD;
    myInput[2].ki.dwFlags = 0;
    myInput[2].ki.wVk = VK_SHIFT;

    myInput[3].type = INPUT_KEYBOARD;
    myInput[3].ki.dwFlags = KEYEVENTF_KEYUP;
    myInput[3].ki.wVk = VK_SHIFT;

    while (TRUE)
    {
        POINT p1;
        GetCursorPos(&p1);
        this_thread::sleep_for(chrono::minutes(5));
        POINT p2;
        GetCursorPos(&p2);
        if (p1.x == p2.x && p1.y == p2.y)
        {
            SendInput(1, &myInput[0], sizeof(INPUT));
            SendInput(1, &myInput[1], sizeof(INPUT));
            SendInput(1, &myInput[2], sizeof(INPUT));
            SendInput(1, &myInput[3], sizeof(INPUT));
        }
    }
}