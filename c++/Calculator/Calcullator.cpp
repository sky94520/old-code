#include "Calculator.h"

Calculator::Calculator()
{
}

void Calculator::run()
{
	char ch = '\0';
	double newOperand =0.0;
	string text = "3456-*+23/-#";
	int index = 0;

	while (index < text.size())
	{
		ch = text[index++];

		switch(ch)
		{
		case '+':
		case '-':
		case '*':
		case '/': this->doOperator(ch);break;
		default:this->addOperand(ch);break;
		}
	}
}

void Calculator::clear()
{
}

void Calculator::addOperand(double value)
{
	m_stack.push(value);
}

bool Calculator::get2Operand(double &left,double &right)
{
	if (m_stack.empty())
	{
		cerr<<"ȱ���������"<<endl;

		return false;
	}
	left = m_stack.top();
	m_stack.pop();

	if (m_stack.empty())
	{
		cerr<<"ȱ���Ҳ�����"<<endl;
		return false;
	}
	right = m_stack.top();
	m_stack.pop();

	return true;
}

void Calculator::doOperator(char op)
{
	//����op���м���
	double left = 0.0,right = 0.0,value = 0.0;
	//��ȡ����������
	bool ret = this->get2Operand(left,right);

	if (ret == false)
	{
		this->clear();
		return;
	}
	switch (op)
	{
	case '+':value = left + right;break;
	case '-':value = left - right;break;
	case '*':value = left * right;break;
	case '/':if (right == 0.0)
			{
				cerr<<"��������Ϊ0"<<endl;
				this->clear();
			 }
			 else
			 {
				 value = left / right;
			 }
			 break;
	default:
		break;
	}
	//�������ջ��
	m_stack.push(value);
}

string Calculator::postfix(const string& text)
{
	int index = 0;
	char ch = '\0';
	char ch1 = '\0';
	stack<char> s;

	s.push('#');

	do
	{
		ch = text.at(index);
		//������
		if (isDigit(ch))
		{
			cout<<ch;
			index++;
		}
		else
		{
			ch1 = s.top();
			//��ջ
			if (isp(ch1) < icp(ch))
			{
				s.push(ch);
				index++;
			}
			else if (isp(ch1) > icp(ch))
			{
				s.pop();
				cout<<ch1;
			}
			else
			{
				s.pop();
				index++;
			}
		}
	}while (!s.empty() && ch != '#');
}

int Calculator::isp(char ch)
{
	int priority = 0;

	switch (ch)
	{
	case '#':priority = 0;break;
	case '(':priority = 1;break;
	case '*':
	case '/':
	case '%':priority = 5;break;
	case '+':
	case '-':priority = 3;break;
	case ')':priority = 6;break;
	default:
		break;
	}

	return priority;
}

int Calculator::icp(char ch)
{
	int priority = 0;

	switch (ch)
	{
	case '#':priority = 0;break;
	case '(':priority = 6;break;
	case '*':
	case '/':
	case '%':priority = 4;break;
	case '+':
	case '-':priority = 2;break;
	case ')':priority = 1;break;
	default:
		break;
	}

	return priority;
}

bool Calculator::isDigit(char ch)
{
	if (ch >= '1' && ch <= '9')
		return true;
	else
		return false;
}