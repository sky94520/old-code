#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "cocos2d.h"
using namespace cocos2d;
/*ʵ���״̬*/
typedef enum
{
	ACTION_TYPE_NONE,
	ACTION_TYPE_IDLE,
	ACTION_TYPE_WALK,
	ACTION_TYPE_NORMAL_ATTACK_A,
	ACTION_TYPE_NORMAL_ATTACK_B,
	ACTION_TYPE_SKILL_1,
	ACTION_TYPE_HURT,
	ACTION_TYPE_DEAD
}ActionType;
typedef struct _BoundingBox
{
	Rect actual;
	Rect original;
}BoundingBox;
class Entity:public Sprite
{ 
protected:
	//�Ƿ���Ըı�״̬
	bool changeState(ActionType type);
public:
	Entity();
	~Entity();
	CC_SYNTHESIZE(std::string,m_name,Name);//��������
	CC_SYNTHESIZE(Point,m_velocity,Velocity);//�ٶ�
	CC_SYNTHESIZE(float,m_nCurLifeValue,CurLifeValue);//����ֵ
	CC_SYNTHESIZE(ActionType,m_type,ActionType);//��ǰ״̬����
	CC_SYNTHESIZE(bool,m_bIsCanMove,IsCanMove);//�Ƿ���ƶ� ����ʱ�����ƶ�
	//վ������
	CC_SYNTHESIZE_RETAIN(Action*,m_pIdleAction,IdleAction);
	//���߶���
	CC_SYNTHESIZE_RETAIN(Action*,m_pWalkAction,WalkAction);
	//��ͨ���ι�������
	CC_SYNTHESIZE_RETAIN(Action*,m_pAttackNormalActionA,AttackNormalActionA);
	//���˶���
	CC_SYNTHESIZE_RETAIN(Action*,m_pHurtAction,HurtAction);
	//��������
	CC_SYNTHESIZE_RETAIN(Action*,m_pDeadAction,DeadAction);
	//����ִ����Ϻ��ͨ�õ��ú���
	void callbackAction(Ref*pRef){}
	//ִ�ж���
	void runIdleAction();//���ö���
	void runWalkAction();//���߶���
	void runAttackNormalActionA();//��ͨ����A 
	void runHurtAction();//���˶���
	void runDeadAction();//��������
	//��ײ����
	BoundingBox createBoundingBox(const Vec2 &origin,const Size &size);
	CC_SYNTHESIZE(BoundingBox,m_bodyBox,BodyBox);
	CC_SYNTHESIZE(BoundingBox,m_hitBox,HitBox);
	//����λ��
	virtual void setPosition(Vec2&pos);
	void updateBoxes();
protected:
	static Animation*createNormalAction(const char*format,int count,int fps);
	static Animation*createAttackAction(const char*format,int frameCountBegin,int frameCountEnd,int fps);
	/*void setAnimation(const char*plistName,const char*pngName,const char*prefix,int counts,bool isRight)
	{
		//���ص��ڴ�
		SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(plistName,pngName);
		//ȡ��֡
		Vector<SpriteFrame*> spriteFrames;
		for(int i=0;i<counts;i++)
		{
			SpriteFrame*frame = frameCache->getSpriteFrameByName(StringUtils::format("%s%d.png",prefix,i+1));
			spriteFrames.pushBack(frame);
		}
		//��������
		Animation*animation = Animation::createWithSpriteFrames(spriteFrames);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);
		//��װ�ɶ���
		Animate*act = Animate::create(animation);
		//���ж���
		m_pSprite->runAction(act);
	}
	void stopAnimation()
	{
		//ֹͣ��ǰ����
		m_pSprite->stopAllActions();
		//ɾ����ͼ
		this->removeChild(m_pSprite,true);
		//�ָ���ԭ������ͼ
		m_pSprite = Sprite::create(m_name);
		this->addChild(m_pSprite);
		m_pSprite->setFlippedX(!m_bRight);
		m_type = ActionType::ACTION_TYPE_NONE;
	}*/
};
#endif