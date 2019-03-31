#ifndef __Hero_H__
#define __Hero_H__
#include "Entity.h"
#define NORMAL_ATTACK_NUMBER 2
class Hero : public Entity
{
private:
	int m_nNormalAttackNum;
	//测试
	//设置普通攻击
	Vector<Action*> m_normalAttacks;
public:
	Hero();
	~Hero();
	CREATE_FUNC(Hero);
	virtual bool init();

	CC_SYNTHESIZE(std::string,m_name,Name);//主角名字
	
	void onMove(Vec2 velocity);//移动调用
	void onStop();//停止调用
	void onAttack(int number);//攻击
	
	//刷新自己
	void updateSelf();
	//技能A
	CC_SYNTHESIZE_RETAIN(Action*,m_pSkillAction,SkillAction);
	void runSkillAction();
	//普通攻击回调
	void attackCallbackAction(Ref*pRef);//test
	//数字淡出回调
	void fontCallbackAction(Node*pSender);
	//产生伤害数字动画
	void damageDisplay(int number,Vec2 point);
	void FontsCallBackAction(Node* pSender);
};
#endif