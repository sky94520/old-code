#ifndef __SemanticExpression_H__
#define __SemanticExpression_H__
#include<string>
using namespace std;
/*Ŀǰ������ʶ��+-/*()�������������*/
class SemanticExpression
{
private:
	string text;
	int index;
	bool bSucceed;
public:
	SemanticExpression();

	bool parse(const string&text);
private:
	void E();
	void T();
	void E1();
	void T1();
	void F();
};
#endif