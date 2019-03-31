#include "PlayerLayer.h"
#include "GameScene.h"
#include "FlyBehavior.h"
#include "Player.h"
#include "DynamicData.h"

PlayerLayer::PlayerLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
	,m_bAdjustPos(false),m_endAngle(0.f)
{
}
PlayerLayer::~PlayerLayer()
{
}
bool PlayerLayer::init()
{

	m_pPlayer = Player::create();

	//设置颜色
	m_pPlayer->getSprite()->setColorMod(0,255,255);
	//设置飞行
	m_pPlayer->setFlyBehavior(new SteadyFly());
	//设置发射子弹
	m_pPlayer->setBulletNum(2);
	m_pPlayer->setDelegate(this);
	//设置相应参数
	this->reset();

	this->addChild(m_pPlayer);
	//绑定刚体
	this->bindPhysicalPlane(m_pPlayer);
	//设置主角子弹属性
	b2Filter bulletFilter;
	bulletFilter.maskBits = GameScene::PLAYER_BULLET_MASKBIT;
	bulletFilter.categoryBits = GameScene::ENEMY_MASKBIT | GameScene::BORDER_MASKBIT | GameScene::ENEMY_BULLET_MASKBIT;

	m_pPlayer->setBulletFilter(bulletFilter);

	return true;
}
void PlayerLayer::update(float dt)
{
	//判断是否可以重生
	if(m_pPlayer->isAlive() == false)
	{
		int life = DynamicData::getInstance()->getLife();
		//游戏结束
		if(life <= 0)
			m_pDelegate->gameEnd();
		else
		{
			DynamicData::getInstance()->alterLife(-1);//生命减一
			m_pPlayer->revive();//重生
			this->reset();
		}
	}
	//角色死亡，不再接收按键
	if(m_pPlayer->isDead())
		return;
	//需要调整位置
	/*if(m_bAdjustPos)
	{
		float curAngle = m_pPlayer->getSprite()->getRotation();
		if(m_endAngle > curAngle)
		{
			curAngle += 5;
			if(curAngle > m_endAngle)
				m_bAdjustPos = false;
		}
		else
		{
			curAngle -= 5;
			if(curAngle < m_endAngle)
				m_bAdjustPos = false;
		}
		m_pPlayer->getSprite()->setRotation(curAngle);
	}*/
	m_pPlayer->update(dt);
	//每次更新都更新信息
	_eventDispatcher->dispatchCustomEvent("player",m_pPlayer);
}
void PlayerLayer::degreeUpdate(const Point&pos)
{
	/*float x = degree.x * 3 + 1;
	float y = degree.y * 3 + 1;*/
	//转化成弧度
	float degree = SDL_atan2(pos.y,pos.x);
	float angle = SDL_DEGREE_TO_ANGLE(degree);
	//速度
	float speed = sqrt(pow(pos.x,2) + pow(pos.y,2))*3 + 1;

	//m_pPlayer->getSprite()->stopAllActions();
	//使弧度转化为[0,360]
	/*if(angle > -180.f && angle < -90.f)
		m_endAngle = 360 + angle;
	else
		m_endAngle = angle;*/
	m_bAdjustPos = true;
	m_pPlayer->getSprite()->setRotation(angle);
	m_pPlayer->setCurSpeed(speed);
	//__android_log_print(ANDROID_LOG_WARN,"Operate","angle=%.2f",angle);
}
void PlayerLayer::wantShooting()
{
	m_pPlayer->shoot();
}
void PlayerLayer::shooting(Plane*plane,BulletType type)
{
	m_pDelegate->shooting(plane,type);
}
void PlayerLayer::bindPhysicalPlane(Plane*plane)
{
	b2Body*body = PhysicalEngine::getInstance()->createBox(plane->getContentSize(),b2_dynamicBody);
	b2Fixture*fixture = body->GetFixtureList();
	b2Filter filter;

	filter.maskBits = GameScene::PLAYER_MASKBIT;
	filter.categoryBits = GameScene::ENEMY_MASKBIT | GameScene::ENEMY_BULLET_MASKBIT | GameScene::BORDER_MASKBIT;

	fixture->SetFilterData(filter);
	body->ResetMassData();
	//互相保留对方的引用
	body->SetUserData(plane);
	plane->setUserData(body);
	//为该body设置初始速度
	/*body->SetLinearVelocity(b2Vec2(0,-1));
	//无阻尼
	body->SetLinearDamping(0.f);*/
}
 Plane* PlayerLayer::getPlayer()const
{
	return m_pPlayer;
}
void PlayerLayer::setDelegate(PlayerLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void PlayerLayer::reset()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size size = m_pPlayer->getContentSize();

	//设置相应参数
	m_pPlayer->setCurSpeed(1.f);
	//
	m_pPlayer->setCurHp(1);
	m_pPlayer->setMaxHp(1);
	m_pPlayer->setAtk(1);
	m_pPlayer->setAlive(true);
	m_pPlayer->setVisible(true);
	m_pPlayer->getSprite()->setRotation(-90.f);
	m_pPlayer->setPosition(visibleSize.width/2,visibleSize.height - size.height);
}
