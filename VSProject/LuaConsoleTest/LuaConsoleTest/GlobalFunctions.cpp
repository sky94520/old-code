#include "GlobalFunctions.h"
namespace GlobalFunctions
{
	int getLegalKey()
	{
		int key = 0;
		std::string str;
	
		getline(std::cin,str,'\n');
		//todo 以后检测是否合格
		key = atoi(str.c_str());

		return key;
	}
	int getcha()
	{
		return getch();
	}
}