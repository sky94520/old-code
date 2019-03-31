#ifndef __SemanticExpression_H__
#define __SemanticExpression_H__
#include<string>
using namespace std;
/*目前仅仅能识别+-/*()的四则运算分析*/
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