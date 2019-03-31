#include <stdio.h> 
#include <stdlib.h>

int Block[10][10];
int EachBlock[100][100];
int AvailCount=0;

typedef struct Page 
{ 
	int IDnum;
	int BlockSum;
	struct Page *next;
}Page;
Page *page=NULL;

//初始化二维矩阵表示的物理块号
void init()
{
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			Block[i][j]=(int)rand()%2;
			if(Block[i][j]==0)
				AvailCount++;
		}
	for(int m=0;m<100;m++)
		for(int n=0;n<100;n++)
			EachBlock[m][n]=0;
}

//为进程分配内存(当进程号重复时能提示错误信息)
void Create()
{
	int num,blockcount;
	Page *p,*q;
	p=page;
	printf("输入进程号:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->IDnum!=num)
			p=p->next;
		else
		{
			printf("该进程已存在并分配了物理块,重新输入:\n");
			scanf("%d",&num);
			p=page;
		}
	}
	printf("输入该进程所需要的物理块数目:");
	scanf("%d",&blockcount);
	if(blockcount>AvailCount)
		printf("内存物理块不足,不能完成分配!\n");
	else
	{
		q=new Page;
		q->IDnum=num;
		q->BlockSum=blockcount;
		q->next = NULL;
		int k=0;
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				if(Block[i][j]==0&&q->BlockSum>k)	
				{
					Block[i][j]=1;
					k++;
					for(int m=0;m<100;m++)
						for(int n=0;n<100;n++)
							if(m==q->IDnum)
								EachBlock[m][i*10+j]=1;
							AvailCount--;
				}
		if(page==NULL)
		{
			page=q;
			printf("\n分配成功!\n");
		}
		else
		{
			p=page;
			while(p->next != NULL)
				p = p->next;
			p->next=q;
			printf("\n分配成功!\n");
		}	
	}	
}

//显示分配情况函数
void Display()
{
	Page *p;
	p=page;	
	printf("内存物理块使用情况:\n");
	for(int i=0; i<10; i++)
	{
		for(int j=0;j<10;j++)	
			printf("  %d  ",Block[i][j]);
		printf("\n");
	}
	printf("还有 %d 个物理块未使用",AvailCount);
	printf("\n************各进程信息**************\n");
	printf("进程号\t   物理块数目\t物理块分布\n");
	while(p != NULL)
	{
		printf("%4d\t%5d\t\t",p->IDnum,p->BlockSum);
		for(int i=0;i<100; i++)
			for(int j=0;j<100;j++)
				if(p->IDnum==i&&EachBlock[i][j]==1)
					printf("%d,",j+1);
		printf("\n");
		p = p->next;
	}
}

//回收函数(当进程号不存在时能提示错误信息)
void Revoke()
{
	int num;
	Page *pre,*ptr;
	printf("输入要回收的进程号:");
	scanf("%d",&num);
	pre=page;
	ptr=pre;
	while(ptr!=NULL)
	{
		if(ptr->IDnum==num)
			break;
		else
		{
			pre=ptr;
			ptr=ptr->next;
		}
	}
	if(ptr==NULL)
		printf("\n该进程不存在!\n");
	else
	{
		AvailCount+=ptr->BlockSum;
		for(int i=0;i<100;i++)
			for(int j=0;j<100;j++)
				if(ptr->IDnum==i&&EachBlock[i][j]==1)
					Block[j/10][j%10]=0;
		if(ptr==page)
		{
			page=ptr->next;
			delete ptr;
			printf("\n该进程回收成功!\n");
		}
		else
		{
			pre->next=ptr->next;
			delete ptr;
			printf("\n该进程回收成功!\n");
		}
	}
}

//菜单显示函数
void Menu()
{
	printf(" *****基本分页存储管理***** \n");
	printf("┌────────────┐\n");
	printf("│     1.内存分配         │\n");
	printf("│     2.内存回收         │\n");
	printf("│     3.查看分配         │\n");
	printf("│     4.退    出         │\n");
	printf("└────────────┘\n");
}

void main()
{
	int i;
	init();
	Menu();
	while(1)
	{
		printf("\n请输入选择:");
		scanf("%d",&i);
	 	switch(i)
		{
		case 1:Create();break;
		case 2:Revoke();break;
		case 3:Display();break;
		case 0:exit(0);break;
		default:printf("\n输入有误,重新输入!\n");
		}
	}
}