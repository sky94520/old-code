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
//�����ʶ��
map<string,int> identitys;
//����
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
		//��ֻ֤��ȡһ��

		while(file.eof() == false && (ch = file.get()) != ' ' && ch != '\n' && ch != '	')
		{
			 word.append(1,ch);
		}
		//���ַ������н�һ���ķ���
		if(!word.empty() && ch != -1)
		{
			//words.push_back(word);
			handleString(word,words);
		}
	}
	for(int i=0;i<words.size();i++)
	{
		auto text = words.at(i);
		//�Ƿ��ǹؼ���
		auto it1 = keywords.find(text);
		if(it1 != keywords.end())
		{
			cout<<"�ؼ��� "<<it1->first<<"���ȼ�:"<<it1->second<<endl;
			continue;
		}
		auto it2 = symbols.find(text);
		if(it2 != symbols.end())
		{
			cout<<"ר�÷��� "<<it2->first<<"���ȼ�:"<<it2->second<<endl;
			continue;
		}
		auto it3 = identitys.find(text);
		if(it3 != identitys.end())
		{
			cout<<"��ʶ�� "<<it3->first<<"���ȼ�:"<<it3->second<<endl;
			continue;
		}
		auto it4 = constant.find(text);
		if(it4 != constant.end())
		{
			cout<<"���� "<<it4->first<<"���ȼ�:"<<it4->second<<endl;
		}
	}
	getchar();
	return 0;
}
//���ַ������н�һ���Ĳ��
void handleString(const string&word,vector<string>&words)
{
	if(word.size() == 1)
	{
		words.push_back(word);
		return;
	}
	//�ı�
	string text;

	for(auto it = word.begin();it != word.end();it++)
	{
		//��ǰ�ַ�
		char ch = *it;
		text.push_back(ch);
		//�ǹؼ���
		if(isKeyword(text))
		{
			//��һ����ר�з��Ż��ߵ��� ���ǹؼ���
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				words.push_back(text);
				text = "";
			}
		}
		//ר�з���
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
		//��ʶ���Ѵ���
		else if(isIdentity(text))
		{
			//���׻�����һ����ר�з���
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				words.push_back(text);
				text = "";
			}
		}
		//�����ʶ�����߳���
		else if(!words.empty())
		{
			//��һ�����׻�����ר�з���
			if(it ==(word.end() - 1) || isSymbols(*(it+1)))
			{
				//����
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
	//ת�����ַ���
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
			//�ı���Ϊ�ղ����ǹؼ��ֻ���ר�÷��� ����words��
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