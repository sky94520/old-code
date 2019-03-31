#include "Enemy.h"
#include "Global.h"
#include "Hero.h"
Enemy::Enemy()
{
	Global::getInstance()->m_enemyVector.pushBack(this);
}
Enemy::~Enemy()
{
}
bool Enemy::init()
{
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("enemy.plist","enemy.png");
	//��ʼ�����̳�Sprite ��ȱ��
	this->initWithSpriteFrameName("bear_idle_00.png");
	//վ������
	Animate*idleAction = Animate::create(Entity::createNormalAction("bear_idle_%02d.png",3,6));
	//���߶���
	Animate*walkAction = Animate::create(Entity::createNormalAction("bear_run_%02d.png",4,6));
	//���˶���
	Action*hurtAction = Animate::create(Entity::createNormalAction("bear_hurt_%02d.png",2,2));
	//��������
	Action*deadAction = Animate::create(Entity::createNormalAction("bear_dead_%02d.png",2,2));
	//��ͨ����
	Animate*attack1 = Animate::create(Entity::createAttackAction("bear_attack_00_%02d.png",0,9,10));
	Animate*attack2 = Animate::create(Entity::createAttackAction("bear_attack_01_%02d.png",0,9,15));
	
	Action*attack = Sequence::create(attack1,
		CallFuncN::create(CC_CALLBACK_1(Enemy::attackCallbackAction,this)),
		attack2,
		CallFunc::create([&](){runIdleAction();}),NULL);
	
	this->setIdleAction(RepeatForever::create(idleAction));
	this->setWalkAction(RepeatForever::create(walkAction));
	this->setAttackNormalActionA(attack);

	this->setHurtAction(hurtAction);
	this->setDeadAction(deadAction);
	//վ��
	this->runIdleAction();
	this->m_aiState = AI_IDLE;
	m_nextDecisionTime = 0;
	//�����ƶ��ٶ�
	m_velocity = Vec2(0.5f,0.5f);
	//��ײ�����趨
	this->m_bodyBox = this->createBoundingBox(Vec2(0,0), Size(50,60));
	this->m_hitBox = this->createBoundingBox(Vec2(0,60), Size(60,80));
	//����׷������
	this->setAttackArea(10);
	this->setEyeArea(100);
	//����update
	this->scheduleUpdate();
	//����Ѫ��Ϊ100
	m_nCurLifeValue = 100;
	return true;
}
void Enemy::updateSelf()
{
    //this->execute(global->hero->getPosition() + global->hero->getBodyBox().actual.origin , global->hero->getBodyBox().actual.size.width);
    this->execute(Global::getInstance()->m_pHero->getPosition(), Global::getInstance()->m_pHero->getBodyBox().actual.size.width);//�������꼰body���
    if(this->getActionType() == ActionType::ACTION_TYPE_WALK)
    {
        Vec2 location = this->getPosition();
        Vec2 direction = this->getMoveDirection();
        Vec2 expectP = location + direction;
		if(expectP.x <0 || expectP.x > 640 || expectP.y <0 || expectP.y >300)
			return ;
        this->setFlippedX(direction.x < 0 ? true : false);
        this->setPosition(expectP);
        this->updateBoxes();
    }
	else if(this->getActionType() == ACTION_TYPE_NORMAL_ATTACK_A) 
    {
        this->runAttackNormalActionA();
    }
}
void Enemy::execute(const Vec2& target, float targetBodyWidth)
{
    if(m_nextDecisionTime == 0)//lazy��ʱ��0ִ����һ�������ж�
    {
        this->decide(target, targetBodyWidth);
    }else 
	{
        -- m_nextDecisionTime;
    }
}
void Enemy::decide(const Vec2 &target,float targetBodyWidth)
{
	//����Լ�������
	Point location = this->getPosition();
	//��target�ľ���
	float distance = location.getDistance(target);
	//���뷽���ȥ������
	distance -= targetBodyWidth;
	//�Ƿ�ת
	bool isFlipped = this->isFlippedX();
	//�����ж� �ж������� this���ĸ�λ��
	bool isOnTargetLeft = location.x < target.x?true:false;
	//�������ǰ��
	if((isFlipped && isOnTargetLeft) || (!isFlipped && !isOnTargetLeft)) 
	{
        this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
    }else 
	{
        if(distance < m_fEyeArea)
        {
            this->m_aiState = (distance < m_fAttackArea)&&((fabsf(location.y - target.y) < 15)) ? AI_ATTACK : AI_PURSUIT;
        }else {
            this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
        }
    }
	//FSM
	switch(m_aiState)
	{
	case AI_ATTACK:
		this->runAttackNormalActionA();
		this->m_nextDecisionTime = 50;
		break;
	case AI_IDLE:
		this->runIdleAction();
		this->m_nextDecisionTime = CCRANDOM_0_1()*100;
		break;
	case AI_PATROL:
		this->runWalkAction();
        this->m_moveDirection.x = CCRANDOM_MINUS1_1();
        this->m_moveDirection.y = CCRANDOM_MINUS1_1();
        m_moveDirection.x  = m_moveDirection.x > 0 ? (m_moveDirection.x + m_velocity.x) : (m_moveDirection.x -m_velocity.x);
        m_moveDirection.y  = m_moveDirection.y > 0 ? (m_moveDirection.y +m_velocity.y) : (m_moveDirection.y -m_velocity.y);
        this->m_nextDecisionTime = CCRANDOM_0_1() * 100;
		break;
	case AI_PURSUIT:
		this->runWalkAction();
		//�ۻ��ɱ�׼����
        this->m_moveDirection = (target - location).getNormalized();
        this->setFlippedX(m_moveDirection.x < 0 ? true : false);
        m_moveDirection.x  = m_moveDirection.x > 0 ? (m_moveDirection.x +m_velocity.x) : (m_moveDirection.x -m_velocity.x);
        m_moveDirection.y  = m_moveDirection.y > 0 ? (m_moveDirection.y +m_velocity.y) : (m_moveDirection.y -m_velocity.y);
        this->m_nextDecisionTime = 10;
		break;
	}
}
void Enemy::update(float dt)
{
	this->updateSelf();
}
void Enemy::attackCallbackAction(Ref*pRef)
{
	Hero*pHero = Global::getInstance()->m_pHero;
    Rect attackReck = m_hitBox.actual;//���﹥������
    Rect hurtReck = pHero->getBodyBox().actual;//Ӣ����������

    if(attackReck.intersectsRect(hurtReck))
    {
        //pEnemy->setAllowMove(false);
        pHero->runHurtAction();
		int damage = 10 * CCRANDOM_0_1();
        pHero->setCurLifeValue(pHero->getCurLifeValue() - damage);
        if(pHero->getCurLifeValue() <= 0)
        {
            pHero->runDeadAction();
            pHero->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
        }
    }
}