#include "iostream"
#include "cmath"

#include "windows.h"
#include "stdio.h"
#include "conio.h"

using namespace std;

DWORD WINAPI GetKeys();
void getKeys();
char ch;
//int ch;
int main()
{
    //cout<<sizeof(short)<<endl;
        GetKeys();
        if(ch == 72)
        cout<<"up"<<endl;
        cout<<ch<<endl;
}
DWORD WINAPI GetKeys()
{
	while(true)
	{
		ch = getch();
		printf("%ld ",ch);
		if(ch == 72)
		cout<<"up"<<endl;
		else if(ch == 75)
		cout<<"left"<<endl;
		else if(ch == 77)
		cout<<"right"<<endl;
		else if(ch == 80)
		cout<<"down"<<endl;
	}
}
void getKeys()
{
	while(true)
	{
		ch = getch();
		ch = getch();
		printf("%ld ",ch);
		ch = (char)ch;
		if(ch == 72)
		cout<<"up"<<endl;
		else if(ch == 75)
		cout<<"left"<<endl;
		else if(ch == 77)
		cout<<"right"<<endl;
		else if(ch == 80)
		cout<<"down"<<endl;
	}
}
