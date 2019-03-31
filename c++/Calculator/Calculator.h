#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;
/*计算器类*/
class Calculator
{
private:
	stack<double> m_stack;
public:
	Calculator();
	//执行表达式计算
	void run();
	//清除计算结果
	void clear();
private:
	//操作数进栈
	void addOperand(double value);
	//从栈中退出两个两个操作数
	bool get2Operand(double &left,double &right);
	//进行计算
	void doOperator(char op);
	//中缀 -》 后缀
	string postfix(const string& text);

	int isp(char ch);
	int icp(char ch);
	bool isDigit(char ch);
};