#include<stdio.h> 
#include<math.h> 
#include<stdlib.h>
#include <iostream>
using namespace std;
#define W 15   //���ϰ벿������С��Բ�İ뾶
#define R 30   //���°벿��Բ�����߰뾶
int main(){
    int i=0,j=0,time;
    char a[W][4*W],b[R][2*R];
    int k,l;
    char c[]="��ô��Ů��ϲ������";
    for (i=0;i<W;i++)     //���ϲ���ȫ����*���
    {
	for (j=0;j<4*W;j++)
	{   
	    a[i][j]='*';

	}
    }
    for (i=0;i<R;i++)     //���²���ȫ����*���
    {
	for (j=0;j<2*R;j++)
	{   
	    b[i][j]='*';

	}
    }
    for (i=0;i<W;i++)    //�ϲ�������ѭ��
    {
	k=(int)(W-sqrt(2*W*i-i*i));
	for (j=0;j<k;j++)
	{
	    a[i][j]=' ';            //���ո񲿷�
	    a[i][j+2*W]=' ';
	    a[i][W+(W-k)+j]=' ';
	    a[i][3*W+(W-k)+j]=' ';
	}
    }

    for (i=0;i<R;i++)
    {
	l=(int)(R-sqrt((R*R)-(i*i)));

	for (j=0;j<=l;j++)
	{
	    b[i][j]=' ';
	    b[i][R+(R-l)+j]=' ';
	}
    }

    for (i=0;i<10;i++)     //����ϲ���
    {
	for (j=0;j<4*W;j++)
	{   
	    cout<<a[i][j];
	}
	cout<<endl;
    }
    for (i=0;i<R;i++)     //����²���
    {
	for (j=0;j<2*R;j++)
	{   
	    cout<<b[i][j];

	}
	cout<<endl;
    }
    for (;;)
    {   
	COORD coord = {0, 41};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	Sleep(500);
	system("color fa");
	cout<<c[0]<<c[1]<<"\t";
	coord.X=25;
	coord.Y=10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<"^*(- -)*^"<<endl;
	coord.X=10;
	coord.Y=41;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	Sleep(500);
	system("color 6b");
	cout<<c[2]<<c[3]<<"\t";
	coord.X=24;
	coord.Y=12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<"|.�ި�ss.��ou"<<endl;
	coord.X=20;
	coord.Y=41;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	Sleep(500);
	system("color 4c");
	cout<<c[4]<<c[5]<<"\t";
	coord.X=20;
	coord.Y=15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<"(^_^)�ϡ� ����һ����"<<endl;
	coord.X=30;
	coord.Y=41;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	Sleep(500);
	system("color 7d");
	cout<<c[6]<<c[7]<<"\t";
	Sleep(500);
	system("color 1e");
	cout<<c[8]<<c[9]<<"\t";
	Sleep(500);
	system("color 2f");
	cout<<c[10]<<c[11]<<"\t";
	Sleep(500);
	system("color 51");
	cout<<c[12]<<c[13]<<"\t";
	Sleep(500);
	system("color 12");
	cout<<c[14]<<c[15]<<"\t";
	Sleep(500);
	system("color 63");
	cout<<c[16]<<c[17]<<"\t";
	Sleep(500);
	system("color 94");
	cout<<c[18]<<c[19]<<"\t"; 
	Sleep(500);
	coord.X=0;
	coord.Y=41;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<"                                                                          ";
    }
    return 0;
}

