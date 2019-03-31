#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

void handleString(const string&word,vector<string>&words);
bool isSymbols(char ch);
bool isSymbols(const string&str);
bool isKeyword(const string&str);
bool isIdentity(const string&str);
//global
map<string,int> keywords;
map<string,int> symbols;
//保存标识符
map<string,int> identitys;
//常量
map<string,int> constant;

int main()
{
	keywords.insert(make_pair("int",5));
	keywords.insert(make_pair("main",6));
	keywords.insert(make_pair("return",7));


	symbols.insert(make_pair("(",10));
	symbols.insert(make_pair(")",11));
	symbols.insert(make_pair("{",12));
	symbols.insert(make_pair("}",13));
	symbols.insert(make_pair(",",14));
	symbols.insert(make_pair(";",15));
	symbols.insert(make_pair("+",16));
	symbols.insert(make_pair("++",17));
	symbols.insert(make_pair("=",18));

	//string symbols = "(){},;";
	vector<string> words;

	fstream file("test.c",ios::in);

	while(file.eof() == false)
	{
		string word;
		char ch =0;
		//保证只读取一次

		while(file.eof() == false && (ch = file.get()) != ' ' && ch != '\n' && ch != '	')
		{
			 word.append(1,ch);
		}
		//对字符串进行进一步的分析
		if(!word.empty() && ch != -1)
		{
			//words.push_back(word);
			handleString(word,words);
		}
	}
	for(int i=0;i<words.size();i++)
	{
		auto text = words.at(i);
		//是否是关键字
		auto it1 = keywords.find(text);
		if(it1 != keywords.end())
		{
			cout<<"关键字 "<<it1->first<<"优先级:"<<it1->second<<endl;
			continue;
		}
		auto it2 = symbols.find(text);
		if(it2 != symbols.end())
		{
			cout<<"专用符号 "<<it2->first<<"优先级:"<<it2->second<<endl;
			continue;
		}
		auto it3 = identitys.find(text);
		if(it3 != identitys.end())
		{
			cout<<"标识符 "<<it3->first<<"优先级:"<<it3->second<<endl;
			continue;
		}
		auto it4 = constant.find(text);
		if(it4 != constant.end())
		{
			cout<<"常量 "<<it4->first<<"优先级:"<<it4->second<<endl;
		}
	}
	getchar();
	return 0;
}
//对字符串进行进一步的拆分
void handleString(const string&word,vector<string>&words)
{
	if(word.size() == 1)
	{
		words.push_back(word);
		return;
	}
	//文本
	string text;

	for(auto it = word.begin();it != word.end();it++)
	{
		//当前字符
		char ch = *it;
		text.push_back(ch);
		//是关键字
		if(isKeyword(text))
		{
			//下一个是专有符号或者到底 则是关键字
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				words.push_back(text);
				text = "";
			}
		}
		//专有符号
		else if(isSymbols(text))
		{
			bool ret = false;
			if(it == (word.end() - 1))
				ret = true;
			else
			{
				auto nextCh = *(it+1);
				if(text == "+" && nextCh == '+')
					ret = false;
				else
					ret = true;
			}
			if(ret)
			{
				words.push_back(text);
				text = "";
			}
		}
		//标识符已存在
		else if(isIdentity(text))
		{
			//到底或者下一个是专有符号
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				words.push_back(text);
				text = "";
			}
		}
		//放入标识符或者常量
		else if(!words.empty())
		{
			//下一个到底或者是专有符号
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				//常量
				if(text.at(0) >= '0' && text.at(0) <= '9')
				{
					constant.insert(make_pair(text,1));
				}
				else
				{
					identitys.insert(make_pair(text,1));
				}
				words.push_back(text);
				text = "";
			}
		}
	}
}
bool isSymbols(char ch)
{
	//转化成字符串
	string tmp;
	tmp = ch;
	return isSymbols(tmp);
}
bool isSymbols(const string&str)
{
	auto it = symbols.find(str);
	return it != symbols.end();
}
bool isKeyword(const string&str)
{
	auto it = keywords.find(str);
	return it != keywords.end();
}
bool isIdentity(const string&str)
{
	return identitys.find(str) != identitys.end();
}
/*
		if(isSymbols(ch) == true)
		{
			//文本不为空并且是关键字或者专用符号 放入words中
			if(!text.empty() && (isSymbols(text) || isKeywords(text)))
			{
				words.push_back(text);
				text = "";
			}
			string tmp;
			tmp = ch;
			words.push_back(tmp);
		}
		else
		{
			text.push_back(ch);
			if(!text.empty() && it == (word.end() -1) && (isSymbols(text) || isKeywords(text)))
			{
				words.push_back(text);
				text = "";
			}
		}
	}
	if(!text.empty())
		words.push_back(text);
*/