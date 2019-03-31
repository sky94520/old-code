#ifndef __Bullet_H__
#define __Bullet_H__
#include "Entity.h"
class Bullet:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//hp
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�ӵ��˺�
	SDL_SYNTHESIZE(int,m_nSpeed,Speed);//�ӵ��ٶ�
	SDL_SYNTHESIZE(int,m_nAtkRange,AtkRange);//������Χ
	SDL_SYNTHESIZE(std::string,m_normalImage,NormalImage);//����ͼƬ
	SDL_SYNTHESIZE(std::string,m_deadImage,DeadImage);//����ͼƬ
	SDL_BOOL_SYNTHESIZE(m_bAvailable,Available);//�Ƿ����
private:
	bool m_bDead;//�Ƿ�����
public:
	Bullet();
	~Bullet();
	static Bullet*create(const std::string&name);
	bool init(const std::string&name);

	void hurt(int damage);
	void dead();
	FiniteTimeAction* onDeadAction();
	void setDead(bool dead);
	bool isDead()const;
};
#endif