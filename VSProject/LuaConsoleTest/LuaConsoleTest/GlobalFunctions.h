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
	/*��ȫ���*/
	int getcha();
}
/*����ײ�ӿڣ��������Ƿ�����ײ��������Ӧ���*/
class Colliabled
{
public:
	virtual ~Colliabled(){}
	virtual void collided()=0;
	virtual std::string getName()const=0;
};
#endif