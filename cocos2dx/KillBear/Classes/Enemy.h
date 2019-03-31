#ifndef __Enemy_H__
#define __Enemy_H__
#include "Entity.h"
/*����AI*/
typedef enum
{
	AI_IDLE = 0,
	AI_PATROL,//Ѳ��
	AI_ATTACK,
	AI_PURSUIT//׷��
}AiState;
class Enemy : public Entity
{
private:
	//����״̬��
    void decide(const cocos2d::Vec2& target, float targetBodyWidth);
    void execute(const cocos2d::Vec2& target, float targetBodyWidth);
    unsigned int m_nextDecisionTime;
public:
	Enemy();
	~Enemy();
	CREATE_FUNC(Enemy);
	virtual bool init();

	CC_SYNTHESIZE(Vec2,m_moveDirection,MoveDirection);
	CC_SYNTHESIZE(float,m_fEyeArea,EyeArea);
	CC_SYNTHESIZE(float,m_fAttackArea,AttackArea);
	CC_SYNTHESIZE(AiState,m_aiState,AiState);
	void updateSelf();//ˢ���Լ�
	virtual void update(float dt);

	void attackCallbackAction(Ref*pRef);
};
#endif