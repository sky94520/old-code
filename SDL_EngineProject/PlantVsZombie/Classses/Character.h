#ifndef __Character_H__
#define __Character_H__

#include "Entity.h"
/*��ǰ����*/
enum class Direction
{
	None,/*�޷���*/
	Left,/*����*/
	Right,/*����*/
	All,/*������None��Ϊ��Plant������,��ʬһ���ò���*/
};
/*��������*/
enum class AttackType
{
	Common,/*��Ч��,����Ч��*/
	Boom,/*��ըЧ��*/
	Ice,/*����*/
	Swallow,/*����Ч��*/
	Track,/*׷��Ч��*/
	Penetrate,/*��͸Ч��*/
	Magnet,/*������*/
	FireAndKillDeceleration,/*����������*/
	Deceleration,/*����*/
	TrackAndDeceleration,/*׷���Ҽ���*/
	TrackAndButter,/*׷���һ���*/
};
/*��ɫ����*/
enum class CharacterType
{
	None,
	Plant,
	Zombie,
	Bullet,
};

class Character : public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//��ǰѪ��
	SDL_SYNTHESIZE(int,m_nMaxHitPoint,MaxHitPoint);//���Ѫ��
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//��ǵ�ǰ�Ƿ�����
	SDL_SYNTHESIZE(Direction,m_dir,Dir);//��ǰ���� �ƶ�����ʱ��������
	SDL_SYNTHESIZE(CharacterType,m_characterType,CharacterType);//��ɫ����
protected:
	static const int ANIMATION_TAG;
public:
	Character();
	~Character();
	/*���˻ص�����*/
	virtual void hurt(int baseDamage,AttackType attackType);
	/*��Ҫ��������*/
	bool isDying()const;
public:
	/*��ȡ��׼����ײ���*/
	virtual Rect getCollisionBoundingBox()const;
protected:
	virtual void onHurt() = 0;
	/*��ȡ��ǰ��������*/
	virtual int getRow()const = 0;
};
#endif