#ifndef __Light_H__
#define __Light_H__
#include<iostream>
#include<string>
using namespace std;

class Light
{
private:
	string name;
public:
	Light(const string&name);
	void on();
	void off();
};
#endif