#include "GlobalFunctions.h"
namespace GlobalFunctions
{
	int getLegalKey()
	{
		int key = 0;
		std::string str;
	
		getline(std::cin,str,'\n');
		//todo �Ժ����Ƿ�ϸ�
		key = atoi(str.c_str());

		return key;
	}
	int getcha()
	{
		return getch();
	}
}