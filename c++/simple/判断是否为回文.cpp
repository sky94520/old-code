/**
 * 判断是否为回文
 */
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	string str = "anana";
	//存在命令行参数,仅仅获取第一个参数
	if (argc != 1)
	{
		str = argv[1];
	}
	//判断 o(n/2)
	bool flag = true;
	for (unsigned i = 0; i < str.size() / 2 && flag; i++)
	{
		if (str[i] != str[str.size() - i - 1])
		{
			flag = false;
		}
	}
	//output
	cout<<str;
	if (flag)
	{
		cout<<": is palindrome"<<endl;
	}
	else
	{
		cout<<": is not palindrome"<<endl;
	}
	return 0;
}
