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
	//初始化随机种子
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
	cout<<"***************************银行家算法自动演示**********************"<<endl;
	cout<<"*******************************************************************"<<endl;
	cout<<"各进程最大需求资源情况如下："<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|                 |  磁带机  |  绘图机  |  打印机  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"|        进程"<<i+1<<"    |     ";
		for(j=0;j<3;j++)
		{
			cout<<claim[i][j]<<"    |     ";
		}
		cout<<endl;
		cout<<"---------------------------"<<endl;
	}

	cout<<"当前进程占用系统子资源情况分布如下:"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|                 |  磁带机  |  绘图机  |  打印机  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"系统资源总数      |    "<<resource[0]<<"    |    "<<resource[1]<<"    |    "<<resource[2]<<"    |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"|        进程"<<i+1<<"    |     ";
		for(j=0;j<3;j++)
		{
			cout<<allocation[i][j]<<"    |     ";
		}
		cout<<endl;
		cout<<"---------------------------"<<endl;
	}
	cout<<"|      已使用     |   "<<useall[0]<<"    |     "<<useall[1]<<"    |    "<<useall[2]<<"  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"|剩余资源|"<<available[0]<<" | "<<available[1]<<" | "<<available[2]<<"  |"<<endl;
	cout<<"----------------------------------------------------"<<endl;

	if(available[0]<0 || available[1]<0 || available[2]<0)
	{
		cout<<"系统随机数申请不当|系统剩余资源为负"<<endl;
	}
	else
	{
		cout<<"各进程仍需资源申请情况如下："<<endl;
		cout<<"----------------------------------------------------"<<endl;
		cout<<"|                 |  磁带机  |  绘图机  |  打印机  |"<<endl;
		cout<<"----------------------------------------------------"<<endl;
		for(i=0;i<n;i++)
		{
			cout<<"|        进程"<<i+1<<"    |     ";
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
			cout<<"信号量a为："<<a<<endl;
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
			cout<<"当前系统请求安全！"<<endl;
			cout<<"进程"<<i+1<<"可以申请到系统资源"<<endl;
			cout<<"进程"<<i+1<<"运行结束，并释放系统资源"<<endl;
			cout<<"当前系统剩余资源情况如下："<<endl;
			cout<<"----------------------------------------------------"<<endl;
			cout<<"|                 |  磁带机  |  绘图机  |  打印机  |"<<endl;
			cout<<"----------------------------------------------------"<<endl;
			cout<<"|剩余资源|"<<available[0]<<" | "<<available[1]<<" | "<<available[2]<<"  |"<<endl;
			cout<<"----------------------------------------------------"<<endl;
			a = 0;
		}
		else
		{
			cout<<"进程"<<i+1<<"申请失败！"<<endl;
			b++;
		}
		a = 0;
		if(b == n)
			cout<<"当前系统申请不安全！"<<endl;
		if(available[0] == resource[0] &&available[1] == resource[1] &&available[2] == resource[2])
			cout<<"演示结束！"<<endl;
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