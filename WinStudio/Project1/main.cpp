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

//��ʼ����ά�����ʾ��������
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

//Ϊ���̷����ڴ�(�����̺��ظ�ʱ����ʾ������Ϣ)
void Create()
{
	int num,blockcount;
	Page *p,*q;
	p=page;
	printf("������̺�:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->IDnum!=num)
			p=p->next;
		else
		{
			printf("�ý����Ѵ��ڲ������������,��������:\n");
			scanf("%d",&num);
			p=page;
		}
	}
	printf("����ý�������Ҫ���������Ŀ:");
	scanf("%d",&blockcount);
	if(blockcount>AvailCount)
		printf("�ڴ�����鲻��,������ɷ���!\n");
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
			printf("\n����ɹ�!\n");
		}
		else
		{
			p=page;
			while(p->next != NULL)
				p = p->next;
			p->next=q;
			printf("\n����ɹ�!\n");
		}	
	}	
}

//��ʾ�����������
void Display()
{
	Page *p;
	p=page;	
	printf("�ڴ������ʹ�����:\n");
	for(int i=0; i<10; i++)
	{
		for(int j=0;j<10;j++)	
			printf("  %d  ",Block[i][j]);
		printf("\n");
	}
	printf("���� %d �������δʹ��",AvailCount);
	printf("\n************��������Ϣ**************\n");
	printf("���̺�\t   �������Ŀ\t�����ֲ�\n");
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

//���պ���(�����̺Ų�����ʱ����ʾ������Ϣ)
void Revoke()
{
	int num;
	Page *pre,*ptr;
	printf("����Ҫ���յĽ��̺�:");
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
		printf("\n�ý��̲�����!\n");
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
			printf("\n�ý��̻��ճɹ�!\n");
		}
		else
		{
			pre->next=ptr->next;
			delete ptr;
			printf("\n�ý��̻��ճɹ�!\n");
		}
	}
}

//�˵���ʾ����
void Menu()
{
	printf(" *****������ҳ�洢����***** \n");
	printf("����������������������������\n");
	printf("��     1.�ڴ����         ��\n");
	printf("��     2.�ڴ����         ��\n");
	printf("��     3.�鿴����         ��\n");
	printf("��     4.��    ��         ��\n");
	printf("����������������������������\n");
}

void main()
{
	int i;
	init();
	Menu();
	while(1)
	{
		printf("\n������ѡ��:");
		scanf("%d",&i);
	 	switch(i)
		{
		case 1:Create();break;
		case 2:Revoke();break;
		case 3:Display();break;
		case 0:exit(0);break;
		default:printf("\n��������,��������!\n");
		}
	}
}