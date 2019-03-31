#include "GameScene.h"
#include "Weapon.h"
#include "FishingJoyData.h"
GameScene::GameScene()
	:m_pBackgroundLayer(nullptr),m_pPanelLayer(nullptr)
	,m_pMenuLayer(nullptr),m_pCannonLayer(nullptr)
	,m_pFishLayer(nullptr),m_pTouchLayer(nullptr)
	,m_pChooseBulletLayer(nullptr)
{
}
GameScene::~GameScene()
{
	//ɾ��������
	FishingJoyData::getInstance()->purge();
	SDL_SAFE_RELEASE(m_pMenuLayer);
}
bool GameScene::init()
{
	//������
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer);
	//���
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	this->scheduleUpdate();
	//��̨��
	m_pCannonLayer = CannonLayer::create();
	this->addChild(m_pCannonLayer);
	//�ӵ�ѡ���
	m_pChooseBulletLayer = ChooseBulletLayer::create();
	m_pChooseBulletLayer->setDelegate(this);
	this->addChild(m_pChooseBulletLayer);
	//״̬��
	m_pPanelLayer = PanelLayer::create();
	m_pPanelLayer->setDelegate(this);
	this->addChild(m_pPanelLayer);
	//�˵���
	m_pMenuLayer = MenuLayer::create();
	m_pMenuLayer->setDelegate(this);
	m_pMenuLayer->retain();
	//������
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//��ʼ��������
	SoundManager::getInstance()->playBackgroundMusic("bg_music.mp3",1);
	return true;
}
void GameScene::update(float dt)
{
	m_pFishLayer->update(dt);
	//m_pCannonLayer->logic(m_pFishLayer->getFishes(),dt);
	m_pPanelLayer->update(dt);
	//printf("%f",dt);
	checkOutCollision();
}
void GameScene::checkOutCollision()
{
	//����ӵ��Ƿ���
	auto weapon = m_pCannonLayer->getWeapon();
	if(weapon->isShooting())
	{
		bool flag = checkOutCollisionBetweenFishesAndBullet();
		if(flag)
			checkOutCollisionBetwwenFishesAndFishingNet();
	}
}
bool GameScene::checkOutCollisionBetweenFishesAndBullet()
{
	//��ȡ��
	auto fishes = m_pFishLayer->getFishes();
	//��ȡ��ǰ�ӵ��ľ���λ��
	auto weapon = m_pCannonLayer->getWeapon();
	Rect collisionRect = weapon->getBulletCollisionRect();
	//�ж�
	for(int i=0;i<fishes.size();i++)
	{
		auto fish = fishes.at(i);
		Rect rect = fish->getBoundingBox();
		rect.origin = fish->getWorldPosition();
		if(fish->isAlive() && collisionRect.intersectsRect(rect))
		{
			//�ӵ���ʧ,��������
			weapon->end();
			return true;
		}
	}
	return false;
}
void GameScene::checkOutCollisionBetwwenFishesAndFishingNet()
{
	auto fishes = m_pFishLayer->getFishes();
	auto weapon = m_pCannonLayer->getWeapon();
	Rect collisionRect = weapon->getFishingNetCollisionRect();
	//��ȡ�����
	float random = RANDOM_0_1();
	for(int i=0;i<fishes.size();i++)
	{
		auto fish = fishes.at(i);
		//������Ѿ�����׽���򲻴���
		if(fish->isAlive() == false)
			continue;
		Rect rect = fish->getBoundingBox();
		rect.origin = fish->getWorldPosition();
		//�Ƿ�׽�õ�
		auto score = static_cast<int>(fabs((float)fish->getScore()));

		float success = weapon->getCannonLevel() * (1 - 0.1)/score;
		if(collisionRect.intersectsRect(rect) && random < success)
		{
			//��Ч
			SoundManager::getInstance()->playEffect("bgm_coin_01.mp3",0);
			fish->catched();
		}
	}
}
void GameScene::pause()
{
	//��Ӳ˵���
	this->addChild(m_pMenuLayer);
	//�����㲻�ɻ���
	m_pTouchLayer->onExit();
	m_pPanelLayer->onExit();
	m_pFishLayer->onExit();

	this->unscheduleUpdate();
}
void GameScene::resume()
{
	m_pMenuLayer->removeFromParent();
	//������ɻ���
	m_pTouchLayer->onEnter();
	m_pPanelLayer->onEnter();
	m_pFishLayer->onEnter();
	this->scheduleUpdate();
}
void GameScene::cannonAimAt(const Point&target)
{
	m_pCannonLayer->aimAt(target);
}
void GameScene::cannonShootTo(const Point&target)
{
	auto weapon = m_pCannonLayer->getWeapon();
	//����ӵ��Ѿ����䣬�����ٴη���
	if(weapon->isShooting())
		return ;
	//��ȡ��ǰ�������
	int goldCount = FishingJoyData::getInstance()->getGold();
	//��ȡ�����ȼ�
	auto cannonType = weapon->getCannonType();
	//�ж����������Ժ���չ
	//������Ӧ�ĵ�ҩ��
	bool bRet = m_pChooseBulletLayer->subBulletCount();
	if(bRet && goldCount - cannonType)
	{
		Value sub = Value(cannonType);
		FishingJoyData::getInstance()->alterGold(sub,false);//���ٽ��
	}
	else
		return;
	m_pCannonLayer->shootTo(target);
}
void GameScene::chooseBullet(const Point&pos)
{
	m_pChooseBulletLayer->chooseBullet(pos);
}
void GameScene::setBulletType(BulletType type)
{
	auto weapon = m_pCannonLayer->getWeapon();
	weapon->setBulletType(type);
}