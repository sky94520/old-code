#ifndef __TallNut_H__
#define __TallNut_H__
#include<string>
#include "WallNut.h"
using namespace std;

class TallNut : public WallNut
{
public:
	TallNut();
	~TallNut();
	static TallNut*create(const string&plantName);
	bool init(const string&plantName);
};
#endif