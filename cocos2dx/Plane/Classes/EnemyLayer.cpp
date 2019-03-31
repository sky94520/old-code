#include "EnemyLayer.h"
#include "Enemy.h"
#include "StaticData.h"
#include "Box2D/Box2D.h"
#include "GameLayer.h"
EnemyLayer::EnemyLayer()
	:m_pDelegate(nullptr)
{
}
EnemyLayer::~EnemyLayer()
{
}
bool EnemyLayer::init()
{
	//2s后开始出现敌机
	scheduleOnce(schedule_selector(EnemyLayer::initEnemy),2.f);
	//initEnemy(1);
	return true;
}
void EnemyLayer::initEnemy(float dt)
{
	const int PTM_RATIO = StaticData::getInstance()->getValueForKey("PTM_RATIO").asInt();
	Size size = Director::getInstance()->getVisibleSize();
	int id = 1;
	for(int i=0;i<8;i++)
	{
		if(i == 5)
			id = 2;
		auto enemy = Enemy::createWithID(id);
		//todo 添加物理碰撞模型
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		m_pDelegate->bindPhysicalBody(enemy,enemy->getName(),&bodyDef);

		this->addChild(enemy);
		//resetEnemy(enemy);
		m_enemyList.push_back(enemy);
	}
}
void EnemyLayer::update(float dt)
{
	for(int i=0;i<m_enemyList.size();++i)
	{
		auto enemy = m_enemyList.at(i);
		/*处理敌机的出现*/
		if(!enemy->isAlive() && !enemy->isVisible())
		{
			auto elapased = enemy->getElapased() + dt;
			enemy->setElapased(elapased);
			if(enemy->getElapased() >= enemy->getTime())
				resetEnemy(enemy);
		}
	}
}
void EnemyLayer::resetEnemy(Enemy*enemy)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size size = enemy->getContentSize();
	//开始位置
	float x = CCRANDOM_0_1()*visibleSize.width;
	float y = CCRANDOM_0_1()*visibleSize.height + visibleSize.height;
	//设置飞机的血量
	enemy->setCurHP(enemy->getHitPoints());
	enemy->setVisible(true);
	
	enemy->setElapased(0.f);
	enemy->stopAllActions();
	enemy->getSprite()->stopAllActions();
	//设置飞行路径
	Vec2 to = ccp(x,-size.height/2);
	float time = (y - to.y)/enemy->getSpeed();
	MoveTo*move = MoveTo::create(time,to);
	CallFunc*end = CallFunc::create([enemy](){
		enemy->setCurHP(0);
		enemy->setVisible(false);
	});
	enemy->setPosition(ccp(x,y));
	enemy->runAction(Sequence::createWithTwoActions(move,end));
}
void EnemyLayer::setDelegate(GameLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}