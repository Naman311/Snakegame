#include<bits/stdc++.h>
//include <iostream>
//#include <deque>
#include<conio.h>
//#include<stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int X=5;
int Y=5;
int a;
int b;
struct point
{
    int x;
    int y;
}p,temp;

deque<point> q;

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
        cout<<"\n Out of bounds ";
        return true;
    }
    else if(selfkill(p.x,p.y))
    {
        cout<<"\n Killed ";
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
    cout<<"\n Food is at (x,y) = "<<a<<" "<<b;
}
void movement(point p)
{
    if(p.x==a && p.y==b)
    {
        cout<<"\n pushing";
        cout<<"\n P.x = "<<p.x<<" P.y = "<<p.y;
        q.push_front(p);
        showstatus();
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
    char n,m='/0';
    food();

        /*a=random();
        b=random();
        cout<<"\n Food is at (x,y) = "<<a<<" "<<b;
    */
    while(n!='e' && dflag!=1 )
    {
        start_time=GetTickCount();
        check_time=start_time+2000;
        temp=q.front();cout<<"\n Front (x,y) = "<<temp.x<<" "<<temp.y<<endl;
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
            if(m=='s')
            {
                break;
            }
            else
            {
            p.x=temp.x-1;
            p.y=temp.y;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {cout<<"\nup";
                movement(p);
            }
            break;
            }
        case 'a':
            if(m=='d')
            {
                break;
            }
            else
            {
            p.x=temp.x;
            p.y=temp.y-1;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {cout<<"\nleft";
                movement(p);
            }
            break;
            }
        case 's':
            if(m=='w')
            {
                break;
            }
            else
            {
            p.x=temp.x+1;
            p.y=temp.y;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {cout<<"\ndown";
                movement(p);
            }
            break;
            }
        case 'd':
            if(m=='a')
            {
                break;
            }
            else
            {
            p.x=temp.x;
            p.y=temp.y+1;
            if(dead(p))
            {
                dflag=1;
            }
            else
            {cout<<"\nright";
                movement(p);
            }
            break;
            }
        }
        m=n;
    }
}
int main()
{
    p.x=0;                              //initial position
    p.y=0;
    q.push_front(p);
    steps();
    getch();
    return 0;
}
