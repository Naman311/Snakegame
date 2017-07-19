#include<bits/stdc++.h>
#include<conio.h>
#include <windows.h>
//#include <stdio.h>
//#include <iostream>
//#include <deque>
//#include<stdlib.h>

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

void gotoxy(int x,int y)                                        //gotoxy Function definition.
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void show_bounds()                                                    //Output the bounds of game
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
int random()                                                        //Generate random values for program
{
    return(rand()%X+1);
}
bool bound(int x,int y)                                             //Checking out of bounds condition
{
    if( x<0 || y<0 || x>X || y>Y)
    {
        return true;
    }
    else
        return false;
}
void show_snake()                                                          //Show the snake
{
    deque<point>::iterator it;
    for (it=q.begin();it!=q.end();it++ )
    {
        temp=*it;
        gotoxy(temp.x,temp.y);
        if(it==q.begin())
        {
            cout<<"=";                                                     //Head of snake
        }
        else if((it+1)==q.end())                                           //output cursor
        {
            cout<<"+";
            gotoxy(X+2,Y+2);
            cout<<" ";
        }
        else                                                               //rest body of snake
        {
            cout<<"+";
        }
    }
}
/*void showstatus()                                                        //show dequeue status used for snake
{
    cout<<"\n The Queue status is : \n";
    deque<point>::iterator it;
    for (it=q.begin();it!=q.end();it++ )
    {
        temp=*it;
        cout<<temp.x<<" "<<temp.y<<endl;
    }
}*/
bool selfkill(int x,int y)                                               //check for collisions
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
bool dead(point p)                                                      //Game over check
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
void food()                                                             //place food in bounds
{
    a=random();
    b=random();
    if(selfkill(a,b))
    {
        food();
    }
}
void movement(point p)                                          //Snake movement
{
    if(p.x==a && p.y==b)                                        //if at food
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
    else                                                        //if not at food
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
    while(n!='e' && dflag!=1 )                                  //press e to quit in between
    {
        system("cls");
        show_bounds();
        gotoxy(a,b);
        cout<<"%";
        show_snake();
        start_time=GetTickCount();
        check_time=start_time+700;
        temp=q.front();
        //cout<<"\n Front (x,y) = "<<temp.x<<" "<<temp.y<<endl;
        while(check_time>GetTickCount())                        //input within time period
        {
            if (kbhit())
            {
				n=getch();
                break;
            }
        }
        //cout<<"pressed "<<n<<endl;
        switch (n)                                      //movement according key pressed
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
    cout<<"Welcome to snake game..\nRules :-\nUse w,a,s,d to move snake..\n= represent head of snake\n+ represent rest part of snake\n% represent food of snake\nPress enter to continue..";
    while(!kbhit()){}
    q.push_front(p);
    steps();
    getch();
    return 0;
}
