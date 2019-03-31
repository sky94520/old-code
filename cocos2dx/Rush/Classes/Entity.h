#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"

USING_NS_CC;
class Entity : public Node
{
protected:
	Sprite*m_pSprite;
	bool m_bIsDead;//�Ƿ�����
protected:
	virtual void onDead();//ʵ������ʱ����
	virtual void onBindSprite();//�󶨾���ʱ����
	virtual void onHurt(int nHurtValue);//����ʱ����
public:
	Entity();
	~Entity();
	CREATE_FUNC(Entity);
	virtual bool init();
	//��ȡ�������
	Sprite*getSprite();
	//�ﶥ�������
	void bindSprite(Sprite*sprite);
	//������
	void hurtMe(int nHurtValue);
	//�Ƿ�����
	bool isDead();
	static Animation*createNormalAction(std::string format,int frameCountBegin,int frameCountEnd,int fps);

	CC_SYNTHESIZE(int,m_nID,ID);//ʵ��ID
	CC_SYNTHESIZE(int,m_nModelID,ModelID);//��ԴID
	CC_SYNTHESIZE(std::string,m_type,Type);//���
	CC_SYNTHESIZE(std::string,m_name,Name);//����
	CC_SYNTHESIZE(int,m_nHP,HP);
	CC_SYNTHESIZE(int,m_nDefense,Defense);//����
	CC_SYNTHESIZE(float,m_nSpeed,Speed);//�ٶ�
	CC_SYNTHESIZE(int,m_nCurLevel,CurLevel);//�ȼ�
};
#endif