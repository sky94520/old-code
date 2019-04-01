/**
 * 拉丁猪文字游戏
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	string vowel = "aeiou";
	string str = "banana";
	stringstream buffer;
	string newStr;
	//存在命令行参数,仅仅获取第一个参数
	if (argc != 1)
	{
		str = argv[1];
	}

	//找到第一个辅音
	for (int i = 0; i <str.size(); i++)
	{
		char ch = str[i];
		auto index = vowel.find(ch);

		if (index == string::npos)
		{
			buffer<<str.substr(0, i);
			buffer<<str.substr(i + 1);
			buffer<<"-";
			buffer<<ch;
			buffer<<"ay";
			break;
		}
	}
	buffer>>newStr;
	cout<<newStr<<endl;
}
