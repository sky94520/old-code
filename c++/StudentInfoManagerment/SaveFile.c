#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
//#include "Student.h"

FILE*openFile(char*fileName);

int main()
{
	FILE*fp = openFile("test.bin");
	fprintf(fp,"啊啊啊！");
	fclose(fp);
}
//打开文件，失败则创建文件,创建二进制文件
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