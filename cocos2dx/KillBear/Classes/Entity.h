#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "cocos2d.h"
using namespace cocos2d;
/*实体的状态*/
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
	//是否可以改变状态
	bool changeState(ActionType type);
public:
	Entity();
	~Entity();
	CC_SYNTHESIZE(std::string,m_name,Name);//主角名字
	CC_SYNTHESIZE(Point,m_velocity,Velocity);//速度
	CC_SYNTHESIZE(float,m_nCurLifeValue,CurLifeValue);//生命值
	CC_SYNTHESIZE(ActionType,m_type,ActionType);//当前状态类型
	CC_SYNTHESIZE(bool,m_bIsCanMove,IsCanMove);//是否可移动 受伤时不可移动
	//站立动画
	CC_SYNTHESIZE_RETAIN(Action*,m_pIdleAction,IdleAction);
	//行走动画
	CC_SYNTHESIZE_RETAIN(Action*,m_pWalkAction,WalkAction);
	//普通单次攻击动画
	CC_SYNTHESIZE_RETAIN(Action*,m_pAttackNormalActionA,AttackNormalActionA);
	//受伤动画
	CC_SYNTHESIZE_RETAIN(Action*,m_pHurtAction,HurtAction);
	//死亡动画
	CC_SYNTHESIZE_RETAIN(Action*,m_pDeadAction,DeadAction);
	//动画执行完毕后的通用调用函数
	void callbackAction(Ref*pRef){}
	//执行动画
	void runIdleAction();//闲置动画
	void runWalkAction();//行走动画
	void runAttackNormalActionA();//普通攻击A 
	void runHurtAction();//受伤动画
	void runDeadAction();//死亡动画
	//碰撞盒子
	BoundingBox createBoundingBox(const Vec2 &origin,const Size &size);
	CC_SYNTHESIZE(BoundingBox,m_bodyBox,BodyBox);
	CC_SYNTHESIZE(BoundingBox,m_hitBox,HitBox);
	//设置位置
	virtual void setPosition(Vec2&pos);
	void updateBoxes();
protected:
	static Animation*createNormalAction(const char*format,int count,int fps);
	static Animation*createAttackAction(const char*format,int frameCountBegin,int frameCountEnd,int fps);
	/*void setAnimation(const char*plistName,const char*pngName,const char*prefix,int counts,bool isRight)
	{
		//加载到内存
		SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(plistName,pngName);
		//取出帧
		Vector<SpriteFrame*> spriteFrames;
		for(int i=0;i<counts;i++)
		{
			SpriteFrame*frame = frameCache->getSpriteFrameByName(StringUtils::format("%s%d.png",prefix,i+1));
			spriteFrames.pushBack(frame);
		}
		//创建动画
		Animation*animation = Animation::createWithSpriteFrames(spriteFrames);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);
		//组装成动作
		Animate*act = Animate::create(animation);
		//运行动作
		m_pSprite->runAction(act);
	}
	void stopAnimation()
	{
		//停止当前动画
		m_pSprite->stopAllActions();
		//删除贴图
		this->removeChild(m_pSprite,true);
		//恢复到原来的贴图
		m_pSprite = Sprite::create(m_name);
		this->addChild(m_pSprite);
		m_pSprite->setFlippedX(!m_bRight);
		m_type = ActionType::ACTION_TYPE_NONE;
	}*/
};
#endif