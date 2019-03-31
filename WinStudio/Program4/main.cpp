#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
#include<fstream>

using namespace std;

enum PriorityType
{
	Error = -1,//错误
	None = 0,//没有关系
	Equal,//等于
	Gt,//大于
	Lt,//小于
};
//全局变量

//当前的输入生成的产生式
map<char,vector<string> > g_inputs;
map<char,vector<char> > g_firstVT;
map<char,vector<char> > g_lastVT;
//优先关系表
vector<vector<PriorityType>> g_priorityTable;
//保存所有的终结符
vector<char> g_terminals;

char getcharEx();
//对于本文法来说，是否是终结符号
bool isTerminalSignal(char signal);
//为识别程序所做的一个扩展
bool isTerminalSignalEx(char signal);

int getExistTerminalIndex(const string&text,int first = 0);
//各种格式化输出
void formatOutput(map<char,vector<char> > m);
void formatPriorityTable();
void menuOutput();
void outputRecongise(vector<char>&stack,const string&text,bool isIn);

void insertTerminalTo(char terminal,char nonTerminal,map<char,vector<char> >& m);
vector<char> handleFirstVT(char element,vector<string>& vec);
vector<char> handleLastVT(char element,vector<string>& vec);
void handlePriority();
void setPriority(char ch1,char ch2,PriorityType type);
int getIndexOfTerminalTable(char ch);
bool recongise(const string&text);

vector<string> getInput(const string&text);

int main()
{
	bool loop = true;

	cout<<"正在从外部文件中读取文法规则"<<endl;
	ifstream file;
	file.open("test.txt");
	string text;
	//对文法规则进行解析
	while (!file.eof())
	{
		file>>text;
		//对字符串进行分析
		char left = text.at(0);
		vector<string> inputs = getInput(text);
		vector<string>& target = g_inputs[left];
		
		copy(inputs.begin(),inputs.end(),back_inserter(target));
	}
	//生成first集合
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//获取数组
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		//递归获取依赖
		handleFirstVT(element,vec);
	}
	//生成last集合
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//获取数组
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		//递归获取依赖
		handleLastVT(element,vec);
	}
	handlePriority();
	//输出菜单
	menuOutput();

	while (loop)
	{
		cout<<"---------------------请选择功能----------------"<<endl;

		int key = getcharEx();

		switch (key)
		{
		case '1':
			{
				cout<<"FIRSTVT"<<endl;
				formatOutput(g_firstVT);
			 }break;
		case '2':
			{
				cout<<"LASTVT"<<endl;
				formatOutput(g_lastVT);
			}break;
		case '3':
			{
				cout<<"预测分析表"<<endl;
				formatPriorityTable();
			}break;
		case '4':
			{
				string text;
				cout<<"请输入符号串，并以#结束"<<endl;
				cin>>text;
				//清空输入缓冲区
				while (getchar() != '\n')
					continue;

				bool bRet = recongise(text);

				if (bRet)
					cout<<"语句识别成功"<<endl;
				else
					cout<<"语句识别失败"<<endl;
			}break;
		case '5':loop = false;break;
		default:cout<<"输入不合法，请重新输入"<<endl;
		}
	}
	
	return 0;
}

char getcharEx()
{
	char key = getchar();

	while (getchar() != '\n')
		continue;
	return key;
}

vector<string> getInput(const string&text)
{
	char left = '\0';
	int begin = 3;
	vector<string> vec;

	for (unsigned i = 0;i < text.size();i++)
	{
		char ch = text.at(i);
		//当前为左条件
		if (i == 0)
		{
			left = ch;
		}
		else if (ch == '-' || ch == '>')
			;
		else if (ch == '|')
		{
			string sub = text.substr(begin,i - begin);
			//cout<<sub<<" ";
			vec.push_back(sub);
			begin = i + 1;
		}
	}
	if (begin < text.size())
	{
		vec.push_back(text.substr(begin));
	}
	return vec;
}
//该符号是否是终结符号
bool isTerminalSignal(char signal)
{
	return g_inputs.find(signal) == g_inputs.end();
}

bool isTerminalSignalEx(char signal)
{
	//规定 N为非终结字符
	if (signal == 'N')
		return false;

	return isTerminalSignal(signal);
}

//返回第一个终结符的位置，若没有返回-1
int getExistTerminalIndex(const string&text,int first)
{
	for (int i = first; i < text.size();i++)
	{
		char ch = text.at(i);

		if (isTerminalSignal(ch))
			return i;
	}
	return -1;
}

void formatOutput(map<char,vector<char> > m)
{
	for (map<char,vector<char>>::iterator it = m.begin();it != m.end();it++)
	{
		cout<<it->first<<"= { ";
		vector<char> vec = it->second;

		for (unsigned i = 0;i < vec.size();i++)
		{
			cout<<vec.at(i)<<" ";
		}
		cout<<"}"<<endl;
	}
}

void menuOutput()
{
	cout<<"----------------------------------------------"<<endl;
	cout<<"1.非终结符的FIRSTVT集合"<<endl;
	cout<<"2.非终结符的FIRSTVT集合"<<endl;
	cout<<"3.算符优先分析表"<<endl;
	cout<<"4.算符优先识别"<<endl;
	cout<<"5.EXIT"<<endl;

}

void formatPriorityTable()
{
	cout<<"\t";
	for (int i = 0; i < g_terminals.size();i++)
	{
		cout <<g_terminals.at(i)<<"\t";
	}
	cout<<endl;

	for (int i = 0 ;i < g_priorityTable.size();i++)
	{
		cout<<g_terminals.at(i)<<"\t";

		vector<PriorityType>& vec = g_priorityTable.at(i);

		for (int j = 0;j < vec.size();j++)
		{
			PriorityType type = vec.at(j);
			string output;

			if (type == PriorityType::Gt)
				output = ">";
			else if (type == PriorityType::Lt)
				output = "<";
			else if (type == PriorityType::Equal)
				output = "=";

			cout<<output<<"\t";
		}
		cout<<endl;
	}
}

void insertTerminalTo(char terminal,char nonTerminal,map<char,vector<char>>& m)
{
	//确保存在该数组
	vector<char>& vec = m[nonTerminal];

	vector<char>::iterator it = find(vec.begin(),vec.end(),terminal);
	//保证只添加一次
	if (it == vec.end())
	{
		vec.push_back(terminal);
	}
}

vector<char> handleFirstVT(char element,vector<string>& vec)
{
	for (vector<string>::iterator vecIter = vec.begin();vecIter != vec.end();vecIter++)
	{
		string text = *vecIter;

		for (unsigned i = 0;i < text.size();i++)
		{
			char ch = text.at(i);
			//该符号是终结符号
			if (isTerminalSignal(ch))
			{
				insertTerminalTo(ch,element,g_firstVT);
				break;
			}
			//递归
			else if (ch != element && !isTerminalSignal(ch))
			{
				//找到对应的first集合
				vector<char> &result = handleFirstVT(ch,g_inputs[ch]);

				for (vector<char>::iterator it = result.begin();it != result.end();it++)
				{
					insertTerminalTo(*it,element,g_firstVT);
				}
			}
		}
	}
	return g_firstVT[element];
}

vector<char> handleLastVT(char element,vector<string>& vec)
{
	for (vector<string>::iterator vecIter = vec.begin();vecIter != vec.end();vecIter++)
	{
		string text = *vecIter;

		for (int i = text.size() - 1;i >= 0;i--)
		{
			char ch = text.at(i);
			//该符号是终结符号
			if (isTerminalSignal(ch))
			{
				insertTerminalTo(ch,element,g_lastVT);
				break;
			}
			//递归
			else if (ch != element && !isTerminalSignal(ch))
			{
				//找到对应的first集合
				vector<char> &result = handleLastVT(ch,g_inputs[ch]);

				for (vector<char>::iterator it = result.begin();it != result.end();it++)
				{
					insertTerminalTo(*it,element,g_lastVT);
				}
			}
		}
	}
	return g_lastVT[element];
}

void handlePriority()
{
	g_terminals.clear();
	//获取所有的终结符
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//获取数组
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		
		for (vector<string>::iterator vecIter = vec.begin();vecIter != vec.end();vecIter++)
		{
			string text = *vecIter;

			for (string::iterator strIter = text.begin();strIter != text.end();strIter++)
			{
				char ch = *strIter;

				if (isTerminalSignal(ch))
				{
					g_terminals.push_back(ch);
				}
			}
		}
	}
	//添加#
	g_terminals.push_back('#');
	//简单添加值
	for (int i = 0;i < g_terminals.size();i++)
	{
		char ch = g_terminals.at(i);

		vector<PriorityType> types;
		for (int j = 0;j < g_terminals.size();j++)
		{
			types.push_back(None);
		}
		g_priorityTable.push_back(types);
	}
	//求出算符优先分析表
	//由公式驱动 求出分析表
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//获取数组
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		
		for (vector<string>::iterator vecIter = vec.begin();vecIter != vec.end();vecIter++)
		{
			string text = *vecIter;

			int index = getExistTerminalIndex(text);
			//当前文法中不存在终结符，直接下一次循环
			if (index == -1)
				continue;
			//first求小于 TODO
			if (index + 1 < text.size())
			{
				//求出非终结符
				char non = text.at(index + 1);
				//获取该非终结符号的first集合
				vector<char> first = g_firstVT[non];
				//进行赋值
				for (vector<char>::iterator it = first.begin();it != first.end();it++)
				{
					char signal = *it;
					
					setPriority(text.at(index),signal,PriorityType::Lt);
				}
			}//end if*/
			//处理等于关系
			for (int i = index + 1;i < text.size();i++)
			{
				char ch = text.at(i);

				if (isTerminalSignal(ch))
				{
					setPriority(text.at(index),ch,PriorityType::Equal);
				}
			}
			//last大于
			index = -1;
			do
			{
				index = getExistTerminalIndex(text,index + 1);

				if (index - 1 >= 0)
				{
					char non = text.at(index - 1);
					vector<char> last = g_lastVT[non];

					for (vector<char>::iterator it = last.begin();it != last.end();it++)
					{
						char signal = *it;
						
						setPriority(signal,text.at(index),PriorityType::Gt);
					}
				}
			}while(index != -1);
		}//end for
	}
	//处理# TODO
	int index = getIndexOfTerminalTable('#');

	for (int i = 0 ;i < g_terminals.size();i++)
	{
		for (int j = 0;j < g_terminals.size();j++)
		{
			setPriority(g_terminals.at(j),'#',PriorityType::Gt);
		}
		if (i == g_terminals.size() - 1)
			setPriority('#',g_terminals.at(i),PriorityType::Equal);
		else
			setPriority('#',g_terminals.at(i),PriorityType::Lt);
	}
}

int getIndexOfTerminalTable(char ch)
{
	for (int i = 0;i < g_terminals.size();i++)
	{
		if (g_terminals.at(i) == ch)
			return i;
	}
	return -1;
}

void setPriority(char ch1,char ch2,PriorityType type)
{
	//找出这两个符号的index
	int index1 = getIndexOfTerminalTable(ch1);
	int index2 = getIndexOfTerminalTable(ch2);

	//赋值
	g_priorityTable.at(index1).at(index2) = type;
}

PriorityType getPriority(char ch1,char ch2)
{
	//找出这两个符号的index
	int index1 = getIndexOfTerminalTable(ch1);
	int index2 = getIndexOfTerminalTable(ch2);

	if (index1 == -1 || index2 == -1)
		return PriorityType::Error;
	//返回对应的值
	return g_priorityTable.at(index1).at(index2);
}

bool recongise(const string&text)
{
	vector<char> stack;
	int index = 0;
	int i = 0,j = 0;
	char r = text.at(index);
	char q = '\0';
	bool bRet = true;

	stack.push_back('#');
	
	do
	{
		//归约
		if (getPriority(stack[j],r) == PriorityType::Gt)
		{
			do
			{
				q = stack[j];
				j = j - 1;

				if (!isTerminalSignalEx(stack[j]))
					j = j - 1;
				if (getPriority(stack[j],q) == PriorityType::Lt)
				{
					outputRecongise(stack,text.substr(index),false);

					i = j + 1;
					stack[i] = 'N';

					while (stack.size() - 1 > i)
						stack.pop_back();
				}

			}while(getPriority(stack[j],q) != PriorityType::Lt);
		}
		else if (getPriority(stack[j],r) != PriorityType::Error)//移入
		{
			outputRecongise(stack,text.substr(index),true);

			i = i + 1;
			stack.push_back(r);
			//TODO 错误处理
			if (index + 1 >= text.size())
			{
				bRet = false;
				break;
			}
			//获取下一符号
			r = text.at(++index);
			//栈顶是终结符号 或者是#
			if (isTerminalSignalEx(stack[i]) || stack[i] == '#')
			{
				j = i;
			}
			else
			{
				j = i -1;
			}
		}
		else//发生错误，直接返回
		{
			bRet = false;
			break;
		}
	}while(!(i == 1 && r == '#'));

	outputRecongise(stack,text.substr(index),true);
	return bRet;
}

void outputRecongise(vector<char>&stack,const string&text,bool isIn)
{
	static int step = 0;

	cout<<step++<<"\t";

	for (vector<char>::iterator it = stack.begin();it != stack.end();it++)
		cout<<*it;
	cout<<"\t\t"<<text<<"\t\t";

	if (isIn)
		cout<<"移入"<<endl;
	else
		cout<<"归约"<<endl;
}