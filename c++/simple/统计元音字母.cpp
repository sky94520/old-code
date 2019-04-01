/**
 * 统计元音字母
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
	string text = "I want to say is that we should never give up";
	string vowel = "aeiou";
	map<char, int> counts;
	//是否有命令行参数
	if (argc != 1)
	{
		text = argv[1];
	}
	
	for (int i = 0;i < text.size(); i++)
	{
		char ch = text[i];
		//是元音
		if (vowel.find(ch) != string::npos)
		{
			if (counts.find(ch) != counts.end())
				counts[ch] += 1;
			else
				counts[ch] = 1;
		}
	}
	//输出
	cout<<"the text is:"<<endl;
	cout<<text<<endl;
	cout<<"frequency:"<<endl;
	for (auto it = counts.begin(); it != counts.end(); it++)
	{
		char ch = it->first;
		int count = it->second;

		cout<<ch<<"\t"<<count<<endl;
	}

	return 0;
}
