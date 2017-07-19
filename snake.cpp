#include<bits/stdc++.h>
//#include <iostream>
//#include <deque>
#include<conio.h>
//#include<stdlib.h>
#include <windows.h>
//#include <stdio.h>
using namespace std;

COORD coord={0,0};

int X=10;
int Y=10;
int a;
int b;
struct point
{
    int x;
    int y;
}p,temp;

deque<point> q;

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void bonds()
{
    for(int i=0;i<X+2;i++)
    {
        gotoxy(i,Y+1);
        cout<<"~";
    }
    for(int j=0;j<Y+1;j++)
    {
        gotoxy(X+1,j);
        cout<<"|";
    }
}
int random()
{
    return(rand()%X+1);
}
bool bound(int x,int y)
{
    if( x<0 || y<0 || x>X || y>Y)
    {
        return true;
    }
    else
        return false;
}
void GUI()
{
    deque<point>::iterator it;
    for (it=q.begin();it!=q.end();it++ )
    {
        temp=*it;
        gotoxy(temp.x,temp.y);
        if(it==q.begin())
        {
            cout<<"=";
        }
        else if((it+1)==q.end())
        {
            cout<<"+";
            gotoxy(X+2,Y+2);
            cout<<" ";
        }
        else
        {
            cout<<"+";
        }
    }
}
void showstatus()
{
    cout<<"\n The Queue status is : \n";
    deque<point>::iterator it;
    for (it=q.begin();it!=q.end();it++ )
    {
        temp=*it;
        cout<<temp.x<<" "<<temp.y<<endl;
    }
}
bool selfkill(int x,int y)
{
    deque<point>::iterator it;
    for (it=q.begin();it!=q.end();it++ )
    {
        temp=*it;
        if (temp.x==x && temp.y==y)
        {
            return true;
        }
    }
    return false;

}
bool dead(point p)
{
    if(bound(p.x,p.y))
    {
        system("cls");
        cout<<"Game over ..Out of bounds ";
        return true;
    }
    else if(selfkill(p.x,p.y))
    {
        system("cls");
        cout<<"Game over ..";
        return true;
    }
    else
        return false;
}
void food()
{
    a=random();
    b=random();
    if(selfkill(a,b))
    {
        food();
    }
}
void movement(point p)
{
    if(p.x==a && p.y==b)
    {
        //cout<<"\n pushing";
        //cout<<"\n P.x = "<<p.x<<" P.y = "<<p.y;
        q.push_front(p);
        //showstatus();
        food();
        /*a=random();
        b=random();
        cout<<"\n Food is at (x,y) = "<<a<<" "<<b;
    */}
    else
    {
        q.push_front(p);
        q.pop_back();
    }


}
void steps()
{
    DWORD start_time, check_time;
    int dflag=0;
    char n;
    food();

        /*a=random();
        b=random();
        cout<<"\n Food is at (x,y) = "<<a<<" "<<b;
    */
    while(n!='e' && dflag!=1 )
    {
        system("cls");
        bonds();
        gotoxy(a,b);
        cout<<"%";
        GUI();
        start_time=GetTickCount();
        check_time=start_time+700;
        temp=q.front();
        //cout<<"\n Front (x,y) = "<<temp.x<<" "<<temp.y<<endl;
        while(check_time>GetTickCount())
        {
            if (kbhit())
            {
				n=getch();
                break;
            }
        }
        //cout<<"pressed "<<n<<endl;
        switch (n)
        {
        case 'w':
            p.x=temp.x;
            p.y=temp.y-1;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {//cout<<"\nup";
                movement(p);
            }
            break;
        case 'a':
            p.x=temp.x-1;
            p.y=temp.y;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {//cout<<"\nleft";
                movement(p);
            }
            break;
        case 's':
            p.x=temp.x;
            p.y=temp.y+1;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {//cout<<"\ndown";
                movement(p);
            }
            break;
        case 'd':
            p.x=temp.x+1;
            p.y=temp.y;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {//cout<<"\nright";
                movement(p);
            }
            break;
        }
    }
}
int main()
{
    p.x=0;                              //initial position
    p.y=0;
    cout<<"Welcome to snake game..\nRules :-\nUse w,a,s,d to move snake..\n= represent head of snake\n+ represent rest part of snake\n% represent food of snake\nPress any key to continue..";
    while(!kbhit()){}
    q.push_front(p);
    steps();
    getch();
    return 0;
}
