#ifndef __Hero_H__
#define __Hero_H__
#include "Entity.h"
#define NORMAL_ATTACK_NUMBER 2
class Hero : public Entity
{
private:
	int m_nNormalAttackNum;
	//����
	//������ͨ����
	Vector<Action*> m_normalAttacks;
public:
	Hero();
	~Hero();
	CREATE_FUNC(Hero);
	virtual bool init();

	CC_SYNTHESIZE(std::string,m_name,Name);//��������
	
	void onMove(Vec2 velocity);//�ƶ�����
	void onStop();//ֹͣ����
	void onAttack(int number);//����
	
	//ˢ���Լ�
	void updateSelf();
	//����A
	CC_SYNTHESIZE_RETAIN(Action*,m_pSkillAction,SkillAction);
	void runSkillAction();
	//��ͨ�����ص�
	void attackCallbackAction(Ref*pRef);//test
	//���ֵ����ص�
	void fontCallbackAction(Node*pSender);
	//�����˺����ֶ���
	void damageDisplay(int number,Vec2 point);
	void FontsCallBackAction(Node* pSender);
};
#endif