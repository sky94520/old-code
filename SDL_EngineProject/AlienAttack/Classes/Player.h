#ifndef __Player_H__
#define __Player_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
using namespace SDL;

class Player:public Entity
{
	SDL_SYNTHESIZE(float,m_moveSpeed,MoveSpeed);//�ƶ��ٶ�
private:
	float m_invulnerableTime;//�������޵�ʱ��
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
	//����
	void ressurect(float invulnerableTime);
	//��������
	void runNormalAnimation();
	//�����Ƿ��޵�
	bool isInvulnerable()const;
	//������ת�Ƕ�
	void setPlayerRotation(float angle);

	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();
};
#endif