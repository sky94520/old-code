#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>

using namespace std;
int xtzy();
int yyzy();
int zdxq();
int main()
{
	const int n = 3;
	int i=0,j=0;

	int pneed[n][3],claim[n][3],allocation[n][3],resource[3],available[3],useall[3]={0,0,0};
	//��ʼ���������
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		resource[i] = xtzy();
		for(j=0;j<3;j++)
		{
			claim[i][j] = zdxq();
			allocation[i][j] = yyzy();
		}
	}
	allocation[0][0] = 2;
	allocation[0][1] = 5;
	int temp[3] = {0,0,0};
	for(j=0;j<3;j++)
	{
		for(i=0;i<n;i++)
		{
			useall[j] = useall[j] + allocation[i][j];
			pneed[i][j] = claim[i][j] - allocation[i][j];
		}
		available[j] = resource[j] - useall[j];
	}
	cout<<"*******************************************************************"<<endl;
	cout<<"***************************���м��㷨�Զ���ʾ**********************"<<endl;
	cout<<"*******************************************************************"<<endl;
	cout<<"���������������Դ������£�"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|                 |  �Ŵ���  |  ��ͼ��  |  ��ӡ��  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"|        ����"<<i+1<<"    |     ";
		for(j=0;j<3;j++)
		{
			cout<<claim[i][j]<<"    |     ";
		}
		cout<<endl;
		cout<<"---------------------------"<<endl;
	}

	cout<<"��ǰ����ռ��ϵͳ����Դ����ֲ�����:"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|                 |  �Ŵ���  |  ��ͼ��  |  ��ӡ��  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"ϵͳ��Դ����      |    "<<resource[0]<<"    |    "<<resource[1]<<"    |    "<<resource[2]<<"    |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"|        ����"<<i+1<<"    |     ";
		for(j=0;j<3;j++)
		{
			cout<<allocation[i][j]<<"    |     ";
		}
		cout<<endl;
		cout<<"---------------------------"<<endl;
	}
	cout<<"|      ��ʹ��     |   "<<useall[0]<<"    |     "<<useall[1]<<"    |    "<<useall[2]<<"  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|ʣ����Դ|"<<available[0]<<" | "<<available[1]<<" | "<<available[2]<<"  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;

	if(available[0]<0 || available[1]<0 || available[2]<0)
	{
		cout<<"ϵͳ��������벻��|ϵͳʣ����ԴΪ��"<<endl;
	}
	else
	{
		cout<<"������������Դ����������£�"<<endl;
		cout<<"----------------------------------------------------"<<endl;
		cout<<"|                 |  �Ŵ���  |  ��ͼ��  |  ��ӡ��  |"<<endl;
		cout<<"----------------------------------------------------"<<endl;
		for(i=0;i<n;i++)
		{
			cout<<"|        ����"<<i+1<<"    |     ";
			for(j=0;j<3;j++)
			{
				cout<<pneed[i][j]<<"    |     ";
			}
			cout<<endl;
			cout<<"---------------------------"<<endl;
		}
	}
	int a=0,b=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			if(pneed[i][j] <= available[j])
				a++;
			else
				a = 0;
			cout<<"�ź���aΪ��"<<a<<endl;
		}
		if(a == 3)
		{
			for(j=0;j<3;j++)
			{
				available[j] = available[j] + allocation[i][j];
				pneed[i][j]=100;
				if(available[j] > resource[j])
					available[j] = resource[j];
			}
			cout<<"��ǰϵͳ����ȫ��"<<endl;
			cout<<"����"<<i+1<<"�������뵽ϵͳ��Դ"<<endl;
			cout<<"����"<<i+1<<"���н��������ͷ�ϵͳ��Դ"<<endl;
			cout<<"��ǰϵͳʣ����Դ������£�"<<endl;
			cout<<"----------------------------------------------------"<<endl;
			cout<<"|                 |  �Ŵ���  |  ��ͼ��  |  ��ӡ��  |"<<endl;
			cout<<"----------------------------------------------------"<<endl;
			cout<<"|ʣ����Դ|"<<available[0]<<" | "<<available[1]<<" | "<<available[2]<<"  |"<<endl;
			cout<<"----------------------------------------------------"<<endl;
			a = 0;
		}
		else
		{
			cout<<"����"<<i+1<<"����ʧ�ܣ�"<<endl;
			b++;
		}
		a = 0;
		if(b == n)
			cout<<"��ǰϵͳ���벻��ȫ��"<<endl;
		if(available[0] == resource[0] &&available[1] == resource[1] &&available[2] == resource[2])
			cout<<"��ʾ������"<<endl;
	}
	_getch();
	return 0;
}
int xtzy()
{
	int xtzys = rand()%10 + 20;
	return xtzys;
}
int yyzy()
{
	int yyzys = rand()%3 + 3;
	return yyzys;
}
int zdxq()
{
	int zdxqs = rand()%3 + 6;
	return zdxqs;
}