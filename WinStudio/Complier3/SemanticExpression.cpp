#include "SemanticExpression.h"

SemanticExpression::SemanticExpression()
	:index(0),bSucceed(false)
{
}

bool SemanticExpression::parse(const string&text)
{
	this->text = text;
	index = 0;

	bSucceed = true;

	E();

	return bSucceed;
}
void SemanticExpression::E()
{
	T();
	E1();
}

void SemanticExpression::T()
{
	F();
	T1();
}

void SemanticExpression::E1()
{
	char sym = '\0';
	if(index < text.size())
		sym = text.at(index);

	if(sym == '+' || sym == '-')
	{
		index++;

		T();
		E1();
	}
}

void SemanticExpression::T1()
{
	char sym = '\0';

	if(index < text.size())
		sym = text.at(index);

	if(sym == '*' || sym == '/')
	{
		index++;

		F();
		T1();
	}
}

void SemanticExpression::F()
{
	char sym = '\0';
	if(index < text.size())
		sym = text.at(index);

	if(sym == 'i')
		index ++;
	else if(sym == '(')
	{
		index ++;
		E();

		if(sym == ')')
			index++;
		else
			bSucceed = false;
	}
	else
		bSucceed = false;
}
