#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
//#include "Student.h"

FILE*openFile(char*fileName);

int main()
{
	FILE*fp = openFile("test.bin");
	fprintf(fp,"��������");
	fclose(fp);
}
//���ļ���ʧ���򴴽��ļ�,�����������ļ�
FILE*openFile(char*fileName)
{
	FILE*fp = NULL;

	if((fp = fopen(fileName,"r+")) == NULL)
	{
		if(fp = fopen(fileName,"w") == NULL)
			return NULL;
	}

	return fp;
}