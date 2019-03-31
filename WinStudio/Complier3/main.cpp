#include<iostream>
#include<string>
#include "SemanticExpression.h"

using namespace std;

int main()
{
	string text = "i+i*i-i/i-";

	SemanticExpression exp;

	bool ret = exp.parse(text);

	cout<<text<<endl;

	if(!ret)
		cout<<"error"<<endl;

	cout<<"press any key to continue"<<endl;

	getchar();

	return 0;
}