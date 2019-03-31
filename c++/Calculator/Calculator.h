#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;
/*��������*/
class Calculator
{
private:
	stack<double> m_stack;
public:
	Calculator();
	//ִ�б��ʽ����
	void run();
	//���������
	void clear();
private:
	//��������ջ
	void addOperand(double value);
	//��ջ���˳���������������
	bool get2Operand(double &left,double &right);
	//���м���
	void doOperator(char op);
	//��׺ -�� ��׺
	string postfix(const string& text);

	int isp(char ch);
	int icp(char ch);
	bool isDigit(char ch);
};