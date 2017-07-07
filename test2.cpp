//Example will loop until a key is pressed
//Example will not work with all compilers
#include <conio.h>
#include <iostream>
#include<bits/stdc++.h>
#include <windows.h>

using namespace std;

int main()
{
    char ch;
    DWORD start_time, check_time;
    start_time=GetTickCount();
    check_time=start_time+2000; //GetTickCount returns time in miliseconds, so I add 500 to wait input for half a second.

    while(check_time>GetTickCount())
    {
        if (kbhit())
        {
            ch=getch();
            cout<<"char was "<<ch;
            break;
        }else
        {
            ch='q';
        }
    }
    cout<<"char was "<<ch;
    return 0;
}
