#ifndef __CeilingFan_H__
#define __CeilingFan_H__
#include<iostream>
#include<string>
using namespace std;

enum CeilingFanSpeed
{
	OFF,
	LOW,
	MEDIUM,
	HIGH,
};
class CeilingFan
{
private:
	string location;
	CeilingFanSpeed speed;
public:
	CeilingFan(const string&location);
	void high();
	void medium();
	void low();
	void off();
	CeilingFanSpeed getSpeed()const;
};
#endif