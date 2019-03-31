#ifndef __Global_H__
#define __Global_H__
#include "cocos2d.h"
#include "Enemy.h"
//单例类，保存数据，进行数据交换
class Hero;
class OperatorLayer;
class StateLayer;
class Rocker;
#include "cocos2d.h"
using namespace cocos2d;
class Global
{
private:
	static Global*m_pInstance;
public:
	Hero*m_pHero;
	OperatorLayer*m_pOperatorLayer;
	StateLayer*m_pStateLayer;
	Rocker*m_pRocker;
	Vector<Enemy*> m_enemyVector;
	Layer*m_pGameLayer;
public:
	Global();
	~Global();
	inline static Global*getInstance()
	{
		if(m_pInstance==NULL)
			m_pInstance = new Global();
		return m_pInstance;
	}

};
#endif