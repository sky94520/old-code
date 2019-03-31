#include "PlayerLayer.h"
#include "GameScene.h"
#include "FlyBehavior.h"
#include "Player.h"
#include "DynamicData.h"

PlayerLayer::PlayerLayer()
	:m_pPlayer(nullptr),m_bRightPressed(false)
	,m_bLeftPressed(false),m_pDelegate(nullptr)
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

	m_pPlayer->setDelegate(this);
	//设置相应参数
	m_pPlayer->setBulletNum(2);
	this->playerRevive();

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
			this->playerRevive();
		}
	}
	//角色死亡，不再接收按键
	if(m_pPlayer->isDead())
		return;
	if(m_bRightPressed)
	{
		auto angle = m_pPlayer->getSprite()->getRotation();
		auto curAngle = angle + 5;
		if(curAngle > 360)
			curAngle -= 360;
		m_pPlayer->getSprite()->setRotation(curAngle);
	}
	if(m_bLeftPressed)
	{
		auto angle = m_pPlayer->getSprite()->getRotation();
		auto curAngle = angle - 5;
		if(curAngle < -360)
			curAngle += 360;
		m_pPlayer->getSprite()->setRotation(curAngle);
	}
	m_pPlayer->update(dt);
	//每次更新都更新信息
	_eventDispatcher->dispatchCustomEvent("player",m_pPlayer);
}
void PlayerLayer::onKeyPressed(SDL_Keycode keycode,SDL_Event*)
{
	if(keycode == SDLK_RIGHT)
	{
		m_bRightPressed = true;
		m_bLeftPressed = false;
	}
	else if(keycode == SDLK_LEFT)
	{
		m_bRightPressed = false;
		m_bLeftPressed = true;
	}
	else if(keycode == SDLK_UP)
	{
		m_pPlayer->setCurSpeed(m_pPlayer->getCurSpeed() + 1);
	}
	else if(keycode == SDLK_DOWN)
	{
		int curSpeed = m_pPlayer->getCurSpeed();
		int nextSpeed = curSpeed  - 1;
		if(nextSpeed < 1)
			nextSpeed = 1;
		m_pPlayer->setCurSpeed(nextSpeed);
	}
	else if(keycode == SDLK_SPACE)
	{
		m_pPlayer->shoot();
	}
	//发送消息
	if(keycode == SDLK_UP || keycode == SDLK_DOWN || keycode == SDLK_SPACE)
		_eventDispatcher->dispatchCustomEvent("player",m_pPlayer);
}
void PlayerLayer::onKeyReleased(SDL_Keycode keycode,SDL_Event*)
{
	if(keycode == SDLK_RIGHT)
		m_bRightPressed = false;
	else if(keycode == SDLK_LEFT)
		m_bLeftPressed = false;
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
void PlayerLayer::playerRevive()
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
	m_pPlayer->setBulletNum(2);
	m_pPlayer->getSprite()->setRotation(-90.f);
	m_pPlayer->setPosition(visibleSize.width/2,visibleSize.height - size.height);
}