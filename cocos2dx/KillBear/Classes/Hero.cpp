#include "Hero.h"
#include "OperatorLayer.h"
#include "Global.h"
Hero::Hero():Entity()
	,m_name("")
	,m_pSkillAction (NULL)
	,m_nNormalAttackNum(1)
{
	Global::getInstance()->m_pHero = this;
}
Hero::~Hero()
{
}
bool Hero::init()
{
	//加载动画帧
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("boy.plist","boy.png");
	Action*idleAction = RepeatForever::create(Animate::create(Entity::createNormalAction("boy_idle_%02d.png",3,3)));
	Action*walkAction = RepeatForever::create(Animate::create(Entity::createNormalAction("boy_run_%02d.png",8,8)));

	//受伤动画
	Animate*hurtAction = Animate::create(Entity::createNormalAction("boy_hurt_%02d.png",2,20));
	//死亡动画
	Action*deadAction = Animate::create(Entity::createNormalAction("boy_dead_%02d.png",3,2));
	//普攻1
	Sequence*attack1 = Sequence::create(Animate::create(Entity::createAttackAction("boy_attack_00_%02d.png",0,4,15)),
		CallFuncN::create(CC_CALLBACK_1(Hero::attackCallbackAction,this)),
		Animate::create(Entity::createAttackAction("boy_attack_00_%02d.png",4,8,15)),NULL);
	//普攻2
	Sequence*attack2 = Sequence::create(Animate::create(Entity::createAttackAction("boy_attack_01_%02d.png",0,4,15)),
		CallFuncN::create(CC_CALLBACK_1(Hero::attackCallbackAction,this)),
		Animate::create(Entity::createAttackAction("boy_attack_01_%02d.png",4,8,15)),
		NULL);
	//test
	m_normalAttacks.pushBack(attack1);
	m_normalAttacks.pushBack(attack2);
	//技能
	Animate*skillAction = Animate::create(Entity::createNormalAction("boy_change_attack_%02d.png",12,20));

	this->setIdleAction(idleAction);
	this->setWalkAction(walkAction);
	//普通攻击
	this->setAttackNormalActionA(Sequence::create(attack1,CallFunc::create([&,attack2]()
	{
		if(Global::getInstance()->m_pOperatorLayer->m_bTouched)
			runAction(attack2);
		else
			runIdleAction();
	}),CallFunc::create(CC_CALLBACK_0(Hero::runIdleAction,this)),NULL));

	this->setSkillAction(Sequence::create(skillAction,
		CallFuncN::create(CC_CALLBACK_1(Hero::attackCallbackAction,this)),
		CallFunc::create(CC_CALLBACK_0(Hero::runIdleAction,this)),
		NULL));

	this->setHurtAction(Sequence::create(hurtAction,
		CallFunc::create(CC_CALLBACK_0(Hero::runIdleAction,this)),NULL));
	this->setDeadAction(deadAction);
	//碰撞盒子设定
	this->m_bodyBox = this->createBoundingBox(Vec2(0,30), Size(30,60));
	this->m_hitBox = this->createBoundingBox(Vec2(35,50), Size(80, 90));
	//Sprite必须得初始化
	this->initWithSpriteFrameName("boy_idle_00.png");
	this->runIdleAction();
	return true;
}

void Hero::onMove(Vec2 velocity)
{
	this->setFlippedX(velocity.x>0?false:true);
	this->m_velocity = velocity;
	this->runWalkAction();
}
void Hero::onStop()//站立
{
    this->runIdleAction();
	this->m_velocity = Vec2::ZERO;
}
void Hero::onAttack(int number)
{
	/*if(Entity::changeState(ActionType(ACTION_TYPE_NORMAL_ATTACK_A + number - 1)))
	{
		this->stopAllActions();
		this->runAction(m_normalAttacks.at(number - 1));
	}
	return (m_normalAttacks.at(number - 1))->isDone();*/
	this->runAttackNormalActionA();
}
void Hero::updateSelf()
{
	if(m_type == ActionType::ACTION_TYPE_WALK)
	{
		this->setFlippedX(m_velocity.x>0?false:true);
		//当前坐标
		Vec2 curPos = getPosition();
		//期望坐标
		Vec2 expectPos = curPos + m_velocity*2;
		//实际坐标
		Vec2 actualPos = expectPos;
		this->setPosition(actualPos);
	}
	///log("%f %f",_position.x,_position.y);
	//log("%f %f",getBoundingBox().origin.x,getBoundingBox().origin.y);
	//log("body x:%fy:%f hitx:%fy:%f\n",m_bodyBox.actual.origin.x,m_bodyBox.actual.origin.y,m_hitBox.actual.origin.x,m_hitBox.actual.origin.y);
}
void Hero::attackCallbackAction(Ref*pRef)
{
	Vector<Enemy*> allEnemys = Global::getInstance()->m_enemyVector;
	for(int i=0;i<allEnemys.size();i++)
	{
		Enemy*pEnemy = allEnemys.at(i);
		 if(fabsf(this->getPosition().y - pEnemy->getPosition().y) < 20)
        {
            Rect attackReck = m_hitBox.actual;//英雄攻击区域
            Rect hurtReck = pEnemy->getBodyBox().actual;;//怪物受伤区域
			//log("hero x:%fy:%fw:%fh:%f",attackReck.origin.x,attackReck.origin.y,attackReck.size.width,attackReck.size.height);
			//log("enemy x:%fy:%fw:%fh:%f",hurtReck.origin.x,hurtReck.origin.y,hurtReck.size.width,hurtReck.size.height);

            if(attackReck.intersectsRect(hurtReck))
            {
                //pEnemy->setAllowMove(false);
                pEnemy->runHurtAction();
				int damage = 40 * CCRANDOM_0_1();
                pEnemy->setCurLifeValue(pEnemy->getCurLifeValue() - damage);
				damageDisplay(damage , pEnemy->getBodyBox().actual.origin);
				//log("%f",pEnemy->getCurLifeValue());
                if(pEnemy->getCurLifeValue() <= 0)
                {
                    pEnemy->runDeadAction();
                    pEnemy->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
                }
            }
        }
	}
}
//数字淡出回调
void Hero::FontsCallBackAction(Node* pSender)
{
	Global::getInstance()->m_pGameLayer->removeChild(pSender);
}
void Hero::damageDisplay(int number,Vec2 point)
{
    //产生数字动画
    auto atLabel = Label::create();
    //char ch[100]={0};
    //sprintf(ch,"-%d",number);
    atLabel->setString(__String::createWithFormat("-%d",number)->getCString());
    atLabel->setSystemFontSize(18);
    atLabel->setColor(Color3B(255,0,0));
    atLabel->setPosition(point);
	Global::getInstance()->m_pGameLayer->addChild(atLabel,200);
    FiniteTimeAction * callFuncN = CallFuncN::create(atLabel, callfuncN_selector(Hero::FontsCallBackAction));
	//auto test = CallFuncN::create(CC_CALLBACK_1(Hero::FontsCallBackAction,atLabel));
    FiniteTimeAction *sequence = Sequence::create(
        //FadeIn::create(1.5f),
        ScaleTo::create(0.2f,1.3f),
        MoveBy::create(0.2f,Vec2(0,30)),
        FadeOut::create(0.5f),
        callFuncN,
        NULL); 
    atLabel->runAction(sequence);
}
void Hero::runSkillAction()
{
	if(changeState(ActionType::ACTION_TYPE_SKILL_1))
		this->runAction(m_pSkillAction);
}