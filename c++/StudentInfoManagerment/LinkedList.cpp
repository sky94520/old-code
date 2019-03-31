#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "Student.h"
#include "string.h"

//#pragma pack(1)

Student *buildList();
void outputAllData(Student * iStu);
void outputOneData(char key,Student * iStu);

FILE*openFile(char*fileName);
void writeBinaryFile(Student*head,FILE*fp);
Student*readBinaryFile(FILE*fp);
void sort_ranking(Student*head);

/*int main()
{
	Student *stu;

	int key;

	FILE*fp = openFile("test.bin");
	while (1)
	{
		system("cls");
		printf("1 : �½�����\n2 :������� \n3: ����д�뵽�ļ���\n4 : ���ļ��ж�ȡ����\n0.EXIT\n");
		key = getchar();
		switch(key)
		{
		case '1' :  stu = buildList();
			break;
		case '2' :	outputAllData(stu); puts("�����������"); getch();
			break;
		case '3' :  writeBinaryFile(stu,fp); puts("����ɹ�,�����������"); getch();
			break;
		case '4' :  stu = readBinaryFile(fp); puts("��ȡ�ɹ�,�����������"); getch();
			break;
		case '0' :  fclose(fp); return 0;
			break;
//		default:puts("input error"); puts(",�����������"); getch();
		}

	}
	fclose(fp);
	return 0;
}*/
//�Զ����ƴ��ļ������ļ��������򴴽�
FILE*openFile(char*fileName)
{
	FILE*fp = NULL;

	if((fp = fopen(fileName,"a+b")) == NULL)
	{
		fprintf(stdout,"�ļ�����ʧ�ܣ�");
		return NULL;
	}
	return fp;
}
//д���ݵ��������ļ�
void writeBinaryFile(Student*head,FILE*fp)
{
	Student*p = head;

	while(p->next != NULL)
	{
		fwrite(p,sizeof(Student),1,fp);

		p = p->next;
	}
}
/*�Ӷ������ļ��ж�ȡ����,��������
�����������У����ڴ򿪳���ʱʹ��*/
Student*readBinaryFile(FILE*fp)
{
	if(fp == NULL)
		return NULL;

	//ʹ�ļ��ڲ�ָ��ָ��ͷ
	rewind(fp);

	Student *head = NULL;
	Student *p1 = NULL, *p2 = NULL;
	int n = 1;

	p1 = p2 = (Student *) malloc(sizeof(Student));

//	puts("������ѧ����ע��������ѧ��Ϊ0ʱ�������롣�Ա� 1 �С�0 Ů��\nѧ�� ���� �Ա� c���� �ߵ���ѧ Ӣ��");
	//��ֵ

	fread(p1,sizeof(Student),1,fp);
	while (!feof(fp))
	{
		if (1 == n)
		{
			head = p1;
			n++;
		}
		else
			p2->next = p1;
		p2 = p1;

		p1 = (Student *) malloc(sizeof(Student));
		fread(p1,sizeof(Student),1,fp);

	}
	p2->next = p1;
	p2 = p1;
	p2->next = NULL;
	/*
	p1 = (Student *) malloc(sizeof(Student));
	p2->next = p1;
	p1->next = NULL;
	*/

	return head;
}
Student *buildList()
{
	Student *head = NULL;
	Student *p1 = NULL, *p2 = NULL;
	int n = 1;
	puts("please input");
	//�����ڴ�
	p1 = p2 = (Student *) malloc(sizeof(Student));
	if (p1 == NULL)
		return NULL;
	puts("������ѧ����ע��������ѧ��Ϊ0ʱ�������롣�Ա� 1 �С�0 Ů��\nѧ�� ���� �Ա� c���� �ߵ���ѧ Ӣ��\nע �����ﲻ����ѧ���жϣ�����ȷ��д");
	if (scanf("%s%s%d%lf%lf%lf", p1->number, p1->name, &p1->sex, &p1->score.math, &p1->score.cProgram,&p1->score.english) != 6)
		 puts("input error");

	p1->average_score = (p1->score.math + p1->score.cProgram + p1->score.english)/3;
	p1->ranking = 0;
	while (1)					// strcmp("0", p1->number) != 0)
	{
		if (1 == n)
		{
			head = p1;
			n++;
		}
		else
			p2->next = p1;
		p2 = p1;

		p1 = (Student *) malloc(sizeof(Student));
		puts("ѧ�� ���� �Ա� c���� �ߵ���ѧ Ӣ��");
		// �ж��Ƿ��˳�ѭ��
		scanf("%s", p1->number);
		if (strcmp("0", p1->number) == 0)
		{
		   p2->next = p1;
		   p2 = p1;
		   //������뻺����
		   while (getchar() != '\n')
				continue;

			break;
		}
		else
		{
			scanf("%s%d%lf%lf%lf", p1->name, &p1->sex, &p1->score.cProgram, &p1->score.math,&p1->score.english);
			p1->average_score = (p1->score.math + p1->score.cProgram + p1->score.english)/3;
			p1->ranking = 0;

		}
	}
	p2->next = NULL;
	puts("end");
	//��������
	sort_ranking(head);
	return head;
}

void outputAllData(Student * iStu)
{
	Student *p = iStu;
	int n = 1;
	puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");

    puts("=======================================================================");
	while (p->next != NULL)
	{
		printf("%-4s\t%-4s\t", p->number, p->name);
		if (p->sex == 0)
			printf("Ů");
		else
			printf("��");
		printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);

		p = p->next;
		puts("");
//		puts("=======================================================================");
		}
}

void outputOneData(char key,Student * iStu)
{
    char ch[20];
    Student*p = iStu;

    switch(key)
    {
    case '1':
        puts("������Ҫ��ѯ��ѧ����ѧ��");
        scanf("%s",ch);
        //
        while(p->next != NULL)
        {
            if(strcmp(p->number,ch) == NULL)
                {
                    puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");

                    printf("%-4s\t%-4s\t", p->number, p->name);
                    if (p->sex == 0)
                        printf("Ů");
                    else
                        printf("��");
                    printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);

                    puts("�����������");
                    getch();

                    break;
                }
            p = p->next;
        }
        printf("δ��ѯ����ѧ����Ϣ����˶Ժ����룡��");
        break;
    case '2':
        puts("������Ҫ��ѯ��ѧ��������");
        scanf("%s",ch);
        //
        while(p->next != NULL)
        {
            if(strcmp(p->name,ch) == NULL)
                {
                   puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");

                   printf("%-4s\t%-4s\t", p->number, p->name);
                   if (p->sex == 0)
                      printf("Ů");
                    else
                        printf("��");
                    printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);

                    puts("�����������");
                    getch();

                    break;
                }
            p = p->next;
        }
        printf("δ��ѯ����ѧ����Ϣ����˶Ժ����룡��");
        break;
    case '3':
        puts("������Ҫ��ѯ��ѧ��������");
        scanf("%s",ch);
        //
        while(p->next != NULL)
        {
            if(p->ranking == atoi(ch))
                {
                    puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");

                    printf("%-4s\t%-4s\t", p->number, p->name);
                    if (p->sex == 0)
                        printf("Ů");
                    else
                        printf("��");
                    printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);

                    puts("�����������");
                    getch();

                    break;
                }
            p = p->next;
        }
        printf("δ��ѯ����ѧ����Ϣ����˶Ժ����룡��");

        break;
    default :
        ;
       // fprintf(stderr,"������������������\n");
    }

}
//��������
void sort_ranking(Student*head)
{
	Student*p1 = head;

	int len = 0;

	double maxNum = 0;
	//ʹranking��Ϊ0
	while(p1->next != NULL)
    {
        p1->ranking = 0;
        p1 = p1->next;
    }
    p1 = head;
	//��ȡ������
	while(p1->next != NULL)
    {
        p1 = p1->next;
        len++;
    }
	int n = 0;

	while(len > 0)
	{
	    Student*q = head;
	    //�ҳ�δ�ó����εĳ�Ա
	    while(q->next != NULL)
        {
            if(q->ranking == 0)
                {
                    maxNum = q->average_score;
                    break;
                }
            q = q->next;
        }
	    n++;
        Student*p2 = head;
        //ֻ��δ�������˽��бȽ�
		while(p2->next != NULL)
		{
		    if(p2->ranking == 0)
            {
                maxNum = maxNum > p2->average_score?maxNum:p2->average_score;
  /*              if(maxNum > p2->average_score)
                    continue;
                else if(maxNum < p2->average_score)
                    maxNum = p2->average_score;
                else
                    continue;//*/
            }
            p2 = p2->next;
		}
		p2 = head;
		//ƥ�����ֵ������ֵ������
		while(p2->next != NULL)
        {
            if(p2->ranking == 0 && maxNum == p2->average_score)
            {
                p2->ranking = n;
                printf("%s�������%d\n",p2->name,p2->ranking);
                break;
            }
            p2 = p2->next;
        }
		len--;
	}//end len(1)
}
