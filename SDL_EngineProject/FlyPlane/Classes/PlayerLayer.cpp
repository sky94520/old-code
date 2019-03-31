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

	//������ɫ
	m_pPlayer->getSprite()->setColorMod(0,255,255);
	//���÷���
	m_pPlayer->setFlyBehavior(new SteadyFly());

	m_pPlayer->setDelegate(this);
	//������Ӧ����
	m_pPlayer->setBulletNum(2);
	this->playerRevive();

	this->addChild(m_pPlayer);
	//�󶨸���
	this->bindPhysicalPlane(m_pPlayer);
	//���������ӵ�����
	b2Filter bulletFilter;
	bulletFilter.maskBits = GameScene::PLAYER_BULLET_MASKBIT;
	bulletFilter.categoryBits = GameScene::ENEMY_MASKBIT | GameScene::BORDER_MASKBIT | GameScene::ENEMY_BULLET_MASKBIT;

	m_pPlayer->setBulletFilter(bulletFilter);

	return true;
}
void PlayerLayer::update(float dt)
{
	//�ж��Ƿ��������
	if(m_pPlayer->isAlive() == false)
	{
		int life = DynamicData::getInstance()->getLife();
		//��Ϸ����
		if(life <= 0)
			m_pDelegate->gameEnd();
		else
		{
			DynamicData::getInstance()->alterLife(-1);//������һ
			m_pPlayer->revive();//����
			this->playerRevive();
		}
	}
	//��ɫ���������ٽ��հ���
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
	//ÿ�θ��¶�������Ϣ
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
	//������Ϣ
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
	//���ౣ���Է�������
	body->SetUserData(plane);
	plane->setUserData(body);
	//Ϊ��body���ó�ʼ�ٶ�
	/*body->SetLinearVelocity(b2Vec2(0,-1));
	//������
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

	//������Ӧ����
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

	//������Ӧ����
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