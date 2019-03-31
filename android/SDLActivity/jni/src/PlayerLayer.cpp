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

	//������ɫ
	m_pPlayer->getSprite()->setColorMod(0,255,255);
	//���÷���
	m_pPlayer->setFlyBehavior(new SteadyFly());
	//���÷����ӵ�
	m_pPlayer->setBulletNum(2);
	m_pPlayer->setDelegate(this);
	//������Ӧ����
	this->reset();

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
			this->reset();
		}
	}
	//��ɫ���������ٽ��հ���
	if(m_pPlayer->isDead())
		return;
	//��Ҫ����λ��
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
	//ÿ�θ��¶�������Ϣ
	_eventDispatcher->dispatchCustomEvent("player",m_pPlayer);
}
void PlayerLayer::degreeUpdate(const Point&pos)
{
	/*float x = degree.x * 3 + 1;
	float y = degree.y * 3 + 1;*/
	//ת���ɻ���
	float degree = SDL_atan2(pos.y,pos.x);
	float angle = SDL_DEGREE_TO_ANGLE(degree);
	//�ٶ�
	float speed = sqrt(pow(pos.x,2) + pow(pos.y,2))*3 + 1;

	//m_pPlayer->getSprite()->stopAllActions();
	//ʹ����ת��Ϊ[0,360]
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
	m_pPlayer->getSprite()->setRotation(-90.f);
	m_pPlayer->setPosition(visibleSize.width/2,visibleSize.height - size.height);
}
