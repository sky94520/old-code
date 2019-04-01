/**
 * 统计字符串中的单词数目
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
	string text = "I want to say is that we should never give up";
	map<string, int> counts;
	//存在命令行参数,仅仅获取第一个参数
	if (argc != 1)
	{
		text = argv[1];
	}
	//计算频率
	size_t before = 0;
	for (size_t after = text.find(' '); ; after = text.find(' ', after + 1))
	{
		//获取单词
		string word;
		if (after == string::npos)
			word = text.substr(before);	
		else
			word = text.substr(before, after - before);

		//统计
		if (counts.find(word) != counts.end())
			counts[word]++;
		else
			counts[word] = 1;
		before = after + 1;

		if (after == string::npos)
			break;
	}
	//输出
	cout<<"the text is:"<<endl;
	cout<<text<<endl;
	cout<<"frequency:"<<endl;
	for (auto it = counts.begin(); it != counts.end(); it++)
	{
		string word = it->first;
		int count = it->second;

		cout<<word<<"\t"<<count<<endl;
	}
	return 0;
}
