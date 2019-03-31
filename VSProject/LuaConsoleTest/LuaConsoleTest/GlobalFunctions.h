#ifndef __GlobalFunctions_H__
#define __GlobalFunctions_H__

#include<string>
#include<cstdlib>
#include<iostream>
#include<conio.h>
#include<vector>
#include "PlatformMarcos.h"
#include "Value.h"
class Monster;
namespace GlobalFunctions
{
	int getLegalKey();
	/*安全获得*/
	int getcha();
}
/*可碰撞接口，可与主角发生碰撞并产生相应后果*/
class Colliabled
{
public:
	virtual ~Colliabled(){}
	virtual void collided()=0;
	virtual std::string getName()const=0;
};
#endif