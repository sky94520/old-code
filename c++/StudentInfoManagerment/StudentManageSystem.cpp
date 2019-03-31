// StudentManageSystem.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdio.h"
#include "stdlib.h"
#include "LinkedList.cpp"
#include "ScoreLevel.h"

#define N 20
#define FILE_NAME "test.bin"

int getLegalKey();

Student*init();
extern FILE*openFile(char*fileName);
extern Student*readBinaryFile(FILE*fp);
extern void outputAllData(Student * iStu);
extern void outputOneData(char key,Student * iStu);
extern void writeBinaryFile(Student*head,FILE*fp);
extern void sort_ranking(Student*head);

void mainScene();
void firstScene(Student*stu);
void secondScene();
void thirdScene();
void fourthScene();
void fifthScene();
void sixthScene();
void seventhScene();
void eighthScene();
void ninthScene();

void cleanPrint();
//ȫ�ֱ���
//���հ�������
int key = 0;
Student*headGloble = NULL;
FILE*fpGloble = NULL;

int main(int argc, char* argv[])
{

	headGloble = init();
	if(headGloble == NULL)
	{
		puts("����Ϊ�գ������������");
		getch();
	}
	while(1)
	{
	cleanPrint();
	mainScene();
	key = getLegalKey();
	switch(key)
	{
	case '0' :
		if(headGloble != NULL)
		{
			fpGloble = fopen(FILE_NAME,"wb");
			writeBinaryFile(headGloble,fpGloble);
		}
		fclose(fpGloble);
		return 0;//���������޸�
		break;
	case '1' : firstScene(headGloble);
		break;
	case '2' : secondScene();
		break;
	case '3' : thirdScene();
		break;
	case '4' : fourthScene();
		break;
	case '5' : fifthScene();
		break;
    case '6' : sixthScene();
        break;
    case '7': seventhScene();
		break;
    case '8':  eighthScene();
        break;
    case '9': ninthScene();
		break;
	default :  ;//
	}//end switch
	}
	return 0;
}
//��ȡ�Ϸ�����
int getLegalKey()
{
	//...
	int k = getchar();
	int c = 0;
	while((c = getchar()) != '\n')
        continue;
    return k;
}
//����������������ֲ
void cleanPrint()
{
    #ifdef __linux
    clrscr();
    #else
	system("cls");
	#endif
}
//��ʼ�������ļ�������ֵ������
Student*init()
{
	if((fpGloble = openFile(FILE_NAME)) == NULL)
	{
		fprintf(stdout,"�ļ������ڻ��ʧ��,����ȡ���˴�����");
		getch();
		return NULL;
	}
	return readBinaryFile(fpGloble);
}
//����������
void mainScene()
{
	puts("==========================================================================");
	puts("|                                                                        |");
	puts("|                      ��ӭʹ��ѧ���ɼ�����ϵͳ                          |");
	puts("|                                                                        |");
	puts("==========================================================================");
	puts("*          1.��ʾ����ѧ���ɼ�             6.ɾ��ȫ������                 *");
	puts("*                                                                        *");
	puts("*          2.��ʾĳһѧ���ɼ�             7.��ʾ���ֶγɼ�����           *");
	puts("*                                                                        *");
	puts("*          3.����ѧ������                 8.�����ļ���excel�ɴ��ļ���  *");
	puts("*                                                                        *");
	puts("*          4.ɾ��ѧ����Ϣ                 9.��������                     *");
	puts("*                                                                        *");
	puts("*          5.�޸�ѧ����Ϣ                                                *");
	puts("*                                                                        *");
	puts("*                      0.��ȫ�˳�ѧ���ɼ�����ϵͳ                        *");
	puts("==========================================================================");
}
//
void firstScene(Student*stu)
{
	Student*head = stu;
    Student*p = stu;

    int stu_num = 0;
    double math_average = 0,cProgram_average = 0,english_average = 0;

do{
        if(head == NULL)
          break;
            //����ÿ���ܳɼ�*/
        while(p->next != NULL)
        {
            math_average += p->score.math;
            cProgram_average += p->score.cProgram;
            english_average += p->score.english;
            stu_num++;

            p = p->next;
        }
        //����ƽ����
        math_average /= stu_num;
        cProgram_average /= stu_num;
        english_average /= stu_num;
    }while(0);

	while(1)
	{
		cleanPrint();
		if(head == NULL)
			printf("��ǰ�ļ�û�����ݣ�������������\n"
			"                  0.������һ���˵�\n");
		else
		{
			outputAllData(head);
			//��ʾƽ����
			puts("============================����ƽ������============================\n");
			printf("                        %-6.2lf\t%-6.2lf\t%-6.2lf\n",math_average,cProgram_average,english_average);
			puts("\n=======================0.������һ���˵�=======================");
		}
		key = getLegalKey();

		switch(key)
		{
		case '0' : return ;//������һ������
			break;
		case '1' :
			break;
		case '2' :
			break;
		case '3' :
			break;
		default : ;//
		}
	}
}
//�ڶ�����������
void secondScene()
{
    if(headGloble == NULL)
    {
        puts("��ǰ�����ݣ��޷����в�ѯ�������������������һ��");
        getch();
        return ;
    }

	while (1)
	{
	    cleanPrint();

		puts("                        ��.��ʾĳһѧ���ɼ�\n����\n"
			"                     1.ѧ��\n"
			"                     2.����\n"
			"                     3.����\n����ѧ����Ϣ");
		puts("                         0.������һ�˵�      ");
		puts("******************************************************");


		key = getLegalKey();

		if(key == '0')
            return ;
        else
            outputOneData(key,headGloble);
    }
}
//�����棬��̬�������
void thirdScene()
{
	while(1)
	{
	cleanPrint();

	if(headGloble == NULL)
	{
		puts("�ļ�Ϊ�գ�������.\nע����������һ��");
		headGloble = buildList();
		puts("����ɹ����������������һ�˵�");
		getch();
		return ;
	}
	else
	{
		puts("                       ��.����ѧ������");
		puts("����ʱ��ע��ѧ�Ų�����ͬ");
		puts("������ѧ�����ݣ���ע����ѧ��Ϊ0ʱ�˳�������ӣ�");

		while(1)
		{
		    puts("ѧ��     ����   �Ա�    ��ѧ   c����    Ӣ��");

			Student*p = headGloble;
			Student*p1 = (Student*)malloc(sizeof(Student));
			Student*p2 = headGloble;

			scanf("%s",p1->number);

			if(strcmp(p1->number,"0") == NULL)
			{
			    //�������Σ�
			    {
			                   //����һ�����������¸�����
			                   //int n = 1;
			        Student*q1 = headGloble,*q2 = headGloble;

			        while(q1->next != NULL)
                    {
                        q1->ranking = 0;
                        q1 = q1->next;
                    }
			        sort_ranking(q2);
			    }
			    //end sort
				//�˳�����
				free(p1);
				printf("���ݽ������룬�������������һ�˵�\n");
				//���������
				while (getchar() != '\n')
				continue;

				getch();
				return ;
			}
			else
				scanf("%s%d%lf%lf%lf", p1->name, &p1->sex, &p1->score.cProgram, &p1->score.math,&p1->score.english);
			//�ж��Ƿ�����ͬ��ѧ��
			while(p->next != NULL)
			{
				if(strcmp(p1->number,p->number) == NULL)
				{
					printf("�������ѧ����Ϣ��ѧ���Ѵ��ڣ����������룡\n");
					break;
				}
				p = p->next;
			}
			//�ж������ѧ���Ƿ��Ѿ����ڣ�������ڣ���ȡ���˴�ѭ��
			if(p->next != NULL)
                continue;
			while(p2->next->next != NULL)
				p2 = p2->next;
			//���뵽����
            p2->next = p1;
			p1->next = p;

//			p1->ranking = n;
			p1->average_score = (p1->score.math + p1->score.cProgram + p1->score.english)/3;

		}///end while(1)

	}//else
	}

}
//�Ľ��棬ɾ��ѧ����Ϣ
void fourthScene()
{
    char ch[20];
    Student*p1 = headGloble,*p2 = NULL;

	while(1)
	{
	cleanPrint();
	puts("                       ��.ɾ��ѧ������");
	puts("����");
	puts("                    1.ѧ��\n"
		 "                    2.ѧ������\n"
		 "                  ɾ��ѧ������");
	puts("======================0.������һ�˵�======================");

	if(p1 == NULL)
    {
        puts("��ǰ�����ݣ��޷�����ɾ���������������������һ��");
        getch();
        return ;
    }
	//�����޸�
	key = getLegalKey();

	switch(key)
	{
	case '0' : return ;//������һ������
		break;
	case '1' :
	    puts("������Ҫɾ����ѧ����ѧ��");
	    scanf("%s",ch);
	    //���ɾ������ͷ�ڵ�
	    if(strcmp(p1->number,ch) == NULL)
            {
                headGloble = headGloble->next;
                //�ͷ�ͷ�ڵ�ռ�
                free(p1);
                //������������
                Student*p = headGloble;
                while(p->next != NULL)
                {
                    p->ranking = 0;
                    p = p->next;
                }
                sort_ranking(headGloble);

                printf("��ѧ����Ϣ��ɾ���������������");
                getch();
                break;
            }
	    //�ҵ�Ҫɾ����ѧ����ǰһ��ѧ���ڵ�
	    while(p1->next->next != NULL)
        {
            if(strcmp(p1->next->number,ch) == NULL)
            {
                p2 = p1->next;
                p1->next = p2->next;

                free(p2);
                //������������
                Student*p = headGloble;
                while(p->next != NULL)
                {
                    p->ranking = 0;
                    p = p->next;
                }
                sort_ranking(headGloble);

                printf("��ѧ����Ϣ��ɾ���������������");
                getch();
                break;
            }
            p1 = p1->next;
        }//end while
        fprintf(stderr,"δ�ҵ������ѧ��ƥ���ѧ����Ϣ����˶Ժ��ٲ���\n�����������\n");
        getch();
		break;
	case '2' :
	    puts("������Ҫɾ����ѧ��������");
	    scanf("%s",ch);
	    //���ɾ������ͷ�ڵ�
	    if(strcmp(p1->name,ch) == NULL)
            {
                headGloble = headGloble->next;
                //�ͷ�ͷ�ڵ�ռ�
                free(p1);
                //������������
                Student*p = headGloble;
                while(p->next != NULL)
                {
                    p->ranking = 0;
                    p = p->next;
                }
                sort_ranking(headGloble);

                printf("��ѧ����Ϣ��ɾ���������������");
                getch();
                break;
            }
	    //�ҵ�Ҫɾ����ѧ����ǰһ��ѧ���ڵ�
	    while(p1->next->next != NULL)
        {
            if(strcmp(p1->next->name,ch) == NULL)
            {
                p2 = p1->next;
                p1->next = p2->next;

                free(p2);
                //������������
                Student*p = headGloble;
                while(p->next != NULL)
                {
                    p->ranking = 0;
                    p = p->next;
                }
                sort_ranking(headGloble);

                printf("��ѧ����Ϣ��ɾ���������������");
                getch();
                break;
            }
            p1 = p1->next;
        }//end while
        fprintf(stderr,"δ�ҵ������ѧ��ƥ���ѧ����Ϣ����˶Ժ��ٲ���\n�����������\n");
        getch();
		break;
	default : ;//
		}
	}

}
//����棬ɾ��ѧ����Ϣ
void fifthScene()
{
    Student*p = headGloble;

    Student stu;
	while(1)
	{
	cleanPrint();
	puts("                   ��.�޸�ѧ����Ϣ");
	puts("\n                     1.�޸���Ϣ\n");
//	puts("������ѧ��\nע����Ϊÿ����ѧ�Ź̶������������̶�������ֻ�ṩͨ��ѧ���޸�");
	puts("============================0.������һ�˵�==============================");
	//�����޸�
	key = getLegalKey();
	//
	if(key == '0')
        return ;
    else if(key == '1')
    {
        char num[20];
        puts("������Ҫ�޸ĵ�ѧ����Ϣ��ѧ��");
        scanf("%s",num);

        p = headGloble;
        //�ҵ�Ҫ�޸ĵ�����
        while(p->next != NULL)
        {
            if(strcmp(p->number,num) == NULL)
            {
                puts("ԭ����");
                puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");

                printf("%-4s\t%-4s\t", p->number, p->name);
                if (p->sex == 0)
                    printf("Ů");
                else
                    printf("��");
                printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);
                puts("������������(ע���벻Ҫ�޸�ѧ��)���Ա� 1Ϊ�� 0λŮ");
                puts("ѧ�� ���� �Ա� ���� c���� Ӣ��");

                scanf("%s%s%d%lf%lf%lf",stu.number,stu.name,&stu.sex,&stu.score.math,&stu.score.cProgram,&stu.score.english);

                for(int i = 0;i < 20;i++)
                p->name[i] = stu.name[i];

                p->sex = stu.sex;
                p->score.math = stu.score.math;
                p->score.cProgram = stu.score.cProgram;
                p->score.english = stu.score.english;
                //�޸�ƽ����
                p->average_score = (p->score.math + p->score.cProgram + p->score.english)/3;
                //�޸�����
                p = headGloble;
                while(p->next != NULL)
                {
                    p->ranking = 0;
                    p = p->next;
                }
                sort_ranking(headGloble);

                puts("�����޸ĳɹ��������������");
                getch();
                break;
            }
            p = p->next;
        }
        fprintf(stderr,"δ�ҵ���ѧ��ƥ���ѧ���������������\n");
        getch();
    }

	}//end while
}
//�������棬ɾ��ȫ������
void sixthScene()
{
    Student* p = headGloble,*head = headGloble;

    if(headGloble == NULL)
    {
        cleanPrint();

        puts("��ǰ�����ݣ��޷�����ɾ���������������������һ��");
        getch();
        return ;
    }
    while(1)
    {
        cleanPrint();
        printf("             ����ɾ��ȫ������\n");
        puts("�Ƿ�ɾ��ȫ�����ݣ�ע����պ���ɾ��ȫ�����ݣ����޷��һأ��Ƿ������\n"
             "                                   1.��\n"
             "                                   2.��");
        key = getLegalKey();
        if(key == '1')
        {
          //�ͷ�����ȫ���ռ�
          while(head->next != NULL)
          {
              head = head->next;
              free(p);
              p = head;
          }
          //����ļ�����
          fpGloble = fopen(FILE_NAME,"wb");

          headGloble = NULL;

          puts("��������գ��������������һ��");
        }
        else
        {
            puts("ȡ��ɾ�����������������������һ��");
        }
        getch();
        return ;
    }
}
//���߽��棬��ʾ���ֶ�����
void seventhScene()
{
    void put(char num[]);
    void add(char number[],int*stu_num,char scoreLevel[]);

    //����ÿ���ֶΣ���ͬ��Ŀ�µ�����
    int a[4][3] = {0};
    struct Level level = {0};
    Student*p = headGloble;

    if(p == NULL)
    {
        puts("����û�����ݣ��޷����в���\n�����������");
        getch();
    }

    while(p->next != NULL)
    {
        //��ѧ
        if(p->score.math > 90.0 && p->score.math <= 100.0)
            add(p->number,&a[0][0],level.A.math_num);
        else if(p->score.math > 70.0 && p->score.math <= 90.0)
            add(p->number,&a[1][0],level.B.math_num);
        else if(p->score.math > 60.0 && p->score.math <= 70.0)
            add(p->number,&a[2][0],level.C.math_num);
        else if(p->score.math >= 0.0 && p->score.math <= 60.0)
            add(p->number,&a[3][0],level.D.math_num);
        //c����
       if(p->score.cProgram > 90.0 && p->score.cProgram <= 100.0)
            add(p->number,&a[0][1],level.A.cProgram_num);
        else if(p->score.cProgram > 70.0 && p->score.cProgram <= 90.0)
            add(p->number,&a[1][1],level.B.cProgram_num);
        else if(p->score.cProgram > 60.0 && p->score.cProgram <= 70.0)
            add(p->number,&a[2][1],level.C.cProgram_num);
        else if(p->score.cProgram >= 0.0 && p->score.cProgram <= 60.0)
            add(p->number,&a[3][1],level.D.cProgram_num);
        //Ӣ��
        if(p->score.english > 90.0 && p->score.english <= 100.0)
            add(p->number,&a[0][2],level.A.english_num);
        else if(p->score.english > 70.0 && p->score.english <= 90.0)
            add(p->number,&a[1][2],level.B.english_num);
        else if(p->score.english > 60.0 && p->score.english <= 70.0)
            add(p->number,&a[2][2],level.C.english_num);
        else if(p->score.english >= 0.0 && p->score.english <= 60.0)
            add(p->number,&a[3][2],level.D.english_num);

        p = p->next;
    }//end ����׼���׶�
    while(1)
    {
        cleanPrint();

        puts("======================0.������һ�˵�====================");
        printf("���ֶ�����\t����\tc����\tӢ��\n");
        printf("90��x��100\t%d\t%d\t%d\t\n",a[0][0],a[0][1],a[0][2]);
        puts("");
        printf("70��x��90\t%d\t%d\t%d\t\n",a[1][0],a[1][1],a[1][2]);
        puts("");
        printf("60��x��70\t%d\t%d\t%d\t\n",a[2][0],a[2][1],a[2][2]);
        puts("");
        printf("��60\t\t%d\t%d\t%d\t\n",a[3][0],a[3][1],a[3][2]);
        puts("");
        puts("1.��ѯĳһ�������µ�ѧ��");
        puts("========================================================");
        key = getLegalKey();
        switch(key)
        {
        case '0': return;
            break;
        case '1':
            puts("������Ҫ��ѯ�ķ����Σ�\n"
                 "\t\t1:90��x��100\n"
                 "\t\t2:70��x��90\n"
                 "\t\t3:60��x��70\n"
                 "\t\t4:��60");
            key = getLegalKey();
            switch(key)
            {
            case '1':
                puts("������Ҫ��ѯ�Ŀ�Ŀ\n"
                     "1.��ѧ\t2.c����\t3.Ӣ��");
                key = getLegalKey();
                if(key == '1')
                    put(level.A.math_num);
                else if(key == '2')
                    put(level.A.cProgram_num);
                else if(key == '3')
                    put(level.A.english_num);
                else
                    fprintf(stderr,"��������");
                puts("�����������");
                getch();
                break;
            case '2':
                puts("������Ҫ��ѯ�Ŀ�Ŀ\n"
                     "1.��ѧ\t2.c����\t3.Ӣ��");
                key = getLegalKey();
                if(key == '1')
                    put(level.B.math_num);
                else if(key == '2')
                    put(level.B.cProgram_num);
                else if(key == '3')
                    put(level.B.english_num);
                else
                    fprintf(stderr,"��������");
                puts("�����������");
                getch();
                break;
            case '3':
                puts("������Ҫ��ѯ�Ŀ�Ŀ\n"
                     "1.��ѧ\t2.c����\t3.Ӣ��");
                key = getLegalKey();
                if(key == '1')
                    put(level.C.math_num);
                else if(key == '2')
                    put(level.C.cProgram_num);
                else if(key == '3')
                    put(level.C.english_num);
                else
                    fprintf(stderr,"��������");
                puts("�����������");
                getch();
                break;
            case '4':
               puts("������Ҫ��ѯ�Ŀ�Ŀ\n"
                     "1.��ѧ\t2.c����\t3.Ӣ��");
                key = getLegalKey();
                if(key == '1')
                    put(level.D.math_num);
                else if(key == '2')
                    put(level.D.cProgram_num);
                else if(key == '3')
                    put(level.D.english_num);
                else
                    fprintf(stderr,"��������");
                puts("�����������");
                getch();
                break;
            }//end switch
            break;
        }
    }
}
void add(char number[],int*stu_num,char scoreLevel[])
{
    *stu_num += 1;

    sprintf(&scoreLevel[strlen(scoreLevel)],"%s ",number);

    if(strlen(scoreLevel) >= sizeof(scoreLevel))
        fprintf(stderr,"�洢�ռ䲻�㣡");
}
//������ѧ�Ŷ�Ӧ��ѧ����Ϣ
void put(char num[])
{
    Student*p = headGloble;
    char number[20] = {'\0'};
    int i = 0;
    //����
    if(strlen(num) == 0)
        printf("�÷�Χ��û��ѧ������˶Ժ�����\n");
    else
    puts("ѧ��\t����\t�Ա�\t����\tc����\tӢ��\t�ܷ�\tƽ����\t����");
    //ƥ��ѧ��
    while(num[i] != '\0')
    {
        //��ȡ�ַ���
        sscanf(&num[i],"%s",number);

        while(p->next != NULL)
        {
            if(strcmp(p->number,number) == NULL)
            {
                    printf("%-4s\t%-4s\t", p->number, p->name);
                    if (p->sex == 0)
                        printf("Ů");
                    else
                        printf("��");
                    printf("\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%-6.2lf\t%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);
                    break;
            }
            p = p->next;
        }
        i += strlen(number) + 1;
    }
}
void eighthScene()
{
    Student*p = headGloble;

    if(p == NULL)
    {
        puts("��ǰ�����ݣ��޷����е����������������������һ��");
        getch();
        return;
    }
 while(1)
    {
        cleanPrint();
        puts("                        �ˡ������ļ�");
        printf("�Ƿ񵼳��ļ���\nע��������.csv�ļ� .csv�ļ����Ա�excel�򿪣�����Ҫ��������Ϊ���߼��ģ���������������\n��");
        puts("�����ļ��Ḳ�ǵ�ǰ�ļ����ļ���Ϊ ѧ����Ϣ.csv");
        puts("1.ȷ������ \n0.������һ��");
        key = getLegalKey();
        if(key == '1')
        {
            FILE*fp = fopen("ѧ����Ϣ.csv","w");

            fprintf(fp,"ѧ��,����,�Ա�,����,c����,Ӣ��,�ܷ�,ƽ����,����\n");

            while(p->next != NULL)
            {
                fprintf(fp,"%s,%s,", p->number, p->name);

                if (p->sex == 0)
                    fprintf(fp,"Ů,");
                else
                    fprintf(fp,"��,");

                fprintf(fp,"%lf,%lf,%lf,%lf,%lf,%d\n", p->score.cProgram, p->score.math, p->score.english,p->score.math + p->score.cProgram + p->score.english,p->average_score,p->ranking);

                p = p->next;
            }
            printf("�ļ������ɹ������������������һ��");
            fclose(fp);
            getch();
            return ;
        }
        else if(key == '0')
            return ;
        puts("�������������һ��");

        getch();
        return;
    }
}
void ninthScene()
{
    while(1)
    {
        cleanPrint();
        puts("                        �š�����");
        puts("�����������㿪����Ա ��Сţ ��ʱ���Լ�����2000000000000000000000\nʵ�˾Ӽ����У�ɱ�˱ر���Ʒ��");
        puts("����\n              \t����ʫ ���� ����\n\n");
        puts("\t\t�ҵ�С�������ˣ�����ʶ�糿�� \n"
             "\t\t��ҹ������˵ ԸҹĻ�������� \n"
             "\t\t��������� ���Ử��� ������� �����ҵ���\n"
             "\t\t�����Ǳ���Ǹ����� �����Ѿ��޹����� \n"
             "\t\t�ҵ�ָ�⻹������ ����ҵ����� \n"
             "\t\t����������� ��һ�Ƴ���ƮƮ\n");
        puts("�������������һ��");
        getch();
        return;
    }
}
