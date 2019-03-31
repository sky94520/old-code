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
	Error = -1,//����
	None = 0,//û�й�ϵ
	Equal,//����
	Gt,//����
	Lt,//С��
};
//ȫ�ֱ���

//��ǰ���������ɵĲ���ʽ
map<char,vector<string> > g_inputs;
map<char,vector<char> > g_firstVT;
map<char,vector<char> > g_lastVT;
//���ȹ�ϵ��
vector<vector<PriorityType>> g_priorityTable;
//�������е��ս��
vector<char> g_terminals;

char getcharEx();
//���ڱ��ķ���˵���Ƿ����ս����
bool isTerminalSignal(char signal);
//Ϊʶ�����������һ����չ
bool isTerminalSignalEx(char signal);

int getExistTerminalIndex(const string&text,int first = 0);
//���ָ�ʽ�����
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

	cout<<"���ڴ��ⲿ�ļ��ж�ȡ�ķ�����"<<endl;
	ifstream file;
	file.open("test.txt");
	string text;
	//���ķ�������н���
	while (!file.eof())
	{
		file>>text;
		//���ַ������з���
		char left = text.at(0);
		vector<string> inputs = getInput(text);
		vector<string>& target = g_inputs[left];
		
		copy(inputs.begin(),inputs.end(),back_inserter(target));
	}
	//����first����
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//��ȡ����
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		//�ݹ��ȡ����
		handleFirstVT(element,vec);
	}
	//����last����
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//��ȡ����
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		//�ݹ��ȡ����
		handleLastVT(element,vec);
	}
	handlePriority();
	//����˵�
	menuOutput();

	while (loop)
	{
		cout<<"---------------------��ѡ����----------------"<<endl;

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
				cout<<"Ԥ�������"<<endl;
				formatPriorityTable();
			}break;
		case '4':
			{
				string text;
				cout<<"��������Ŵ�������#����"<<endl;
				cin>>text;
				//������뻺����
				while (getchar() != '\n')
					continue;

				bool bRet = recongise(text);

				if (bRet)
					cout<<"���ʶ��ɹ�"<<endl;
				else
					cout<<"���ʶ��ʧ��"<<endl;
			}break;
		case '5':loop = false;break;
		default:cout<<"���벻�Ϸ�������������"<<endl;
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
		//��ǰΪ������
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
//�÷����Ƿ����ս����
bool isTerminalSignal(char signal)
{
	return g_inputs.find(signal) == g_inputs.end();
}

bool isTerminalSignalEx(char signal)
{
	//�涨 NΪ���ս��ַ�
	if (signal == 'N')
		return false;

	return isTerminalSignal(signal);
}

//���ص�һ���ս����λ�ã���û�з���-1
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
	cout<<"1.���ս����FIRSTVT����"<<endl;
	cout<<"2.���ս����FIRSTVT����"<<endl;
	cout<<"3.������ȷ�����"<<endl;
	cout<<"4.�������ʶ��"<<endl;
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
	//ȷ�����ڸ�����
	vector<char>& vec = m[nonTerminal];

	vector<char>::iterator it = find(vec.begin(),vec.end(),terminal);
	//��ֻ֤���һ��
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
			//�÷������ս����
			if (isTerminalSignal(ch))
			{
				insertTerminalTo(ch,element,g_firstVT);
				break;
			}
			//�ݹ�
			else if (ch != element && !isTerminalSignal(ch))
			{
				//�ҵ���Ӧ��first����
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
			//�÷������ս����
			if (isTerminalSignal(ch))
			{
				insertTerminalTo(ch,element,g_lastVT);
				break;
			}
			//�ݹ�
			else if (ch != element && !isTerminalSignal(ch))
			{
				//�ҵ���Ӧ��first����
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
	//��ȡ���е��ս��
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//��ȡ����
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
	//���#
	g_terminals.push_back('#');
	//�����ֵ
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
	//���������ȷ�����
	//�ɹ�ʽ���� ���������
	for (map<char,vector<string>>::iterator mapIter = g_inputs.begin();mapIter != g_inputs.end();mapIter++)
	{
		//��ȡ����
		char element = mapIter->first;
		vector<string>& vec = mapIter->second;
		
		for (vector<string>::iterator vecIter = vec.begin();vecIter != vec.end();vecIter++)
		{
			string text = *vecIter;

			int index = getExistTerminalIndex(text);
			//��ǰ�ķ��в������ս����ֱ����һ��ѭ��
			if (index == -1)
				continue;
			//first��С�� TODO
			if (index + 1 < text.size())
			{
				//������ս��
				char non = text.at(index + 1);
				//��ȡ�÷��ս���ŵ�first����
				vector<char> first = g_firstVT[non];
				//���и�ֵ
				for (vector<char>::iterator it = first.begin();it != first.end();it++)
				{
					char signal = *it;
					
					setPriority(text.at(index),signal,PriorityType::Lt);
				}
			}//end if*/
			//������ڹ�ϵ
			for (int i = index + 1;i < text.size();i++)
			{
				char ch = text.at(i);

				if (isTerminalSignal(ch))
				{
					setPriority(text.at(index),ch,PriorityType::Equal);
				}
			}
			//last����
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
	//����# TODO
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
	//�ҳ����������ŵ�index
	int index1 = getIndexOfTerminalTable(ch1);
	int index2 = getIndexOfTerminalTable(ch2);

	//��ֵ
	g_priorityTable.at(index1).at(index2) = type;
}

PriorityType getPriority(char ch1,char ch2)
{
	//�ҳ����������ŵ�index
	int index1 = getIndexOfTerminalTable(ch1);
	int index2 = getIndexOfTerminalTable(ch2);

	if (index1 == -1 || index2 == -1)
		return PriorityType::Error;
	//���ض�Ӧ��ֵ
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
		//��Լ
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
		else if (getPriority(stack[j],r) != PriorityType::Error)//����
		{
			outputRecongise(stack,text.substr(index),true);

			i = i + 1;
			stack.push_back(r);
			//TODO ������
			if (index + 1 >= text.size())
			{
				bRet = false;
				break;
			}
			//��ȡ��һ����
			r = text.at(++index);
			//ջ�����ս���� ������#
			if (isTerminalSignalEx(stack[i]) || stack[i] == '#')
			{
				j = i;
			}
			else
			{
				j = i -1;
			}
		}
		else//��������ֱ�ӷ���
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
		cout<<"����"<<endl;
	else
		cout<<"��Լ"<<endl;
}