#ifndef __Player_H__
#define __Player_H__
#include "cocos2d.h"
#include "Entity.h"
#include "FlowWord.h"

using namespace cocos2d;
class Player : public Entity
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	//跳跃
	void jump();
	//受伤
	void hit();
	//获得此时HP
	int getiHP();
private:
	void resetData();
private :
	bool m_isJumping;
	int m_iHP;

};
#endif