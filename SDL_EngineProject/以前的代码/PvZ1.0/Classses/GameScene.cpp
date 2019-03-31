#include "GameScene.h"
#include "Carrier.h"
#include "DynamicData.h"
#include "MainLua.h"
#include "Seed.h"
#include "Plant.h"
#include "Bullet.h"
#include "PlantFactory.h"
#include "Shovel.h"
#include "Zombie.h"
GameScene::GameScene()
	:m_pTouchLayer(nullptr),m_pBackgroundLayer(nullptr)
	,m_pSeedLayer(nullptr),m_pPanelLayer(nullptr)
	,m_pSunshineLayer(nullptr),m_pBulletLayer(nullptr)
	,m_pPlantLayer(nullptr),m_pZombieLayer(nullptr)
{
}
GameScene::~GameScene()
{
	DynamicData::getInstance()->purge();
	MainLua::getInstance()->purge();
}
bool GameScene::init()
{
	//��ȡSeed.lua
	MainLua::getInstance()->dofile("Resources/Seed.lua");
	MainLua::getInstance()->dofile("Resources/Bullet.lua");
	MainLua::getInstance()->dofile("Resources/Zombie.lua");
	//���ض���֡
	auto spriteCache = Director::getInstance()->getSpriteFrameCache();
	spriteCache->addSpriteFramesWithFile("Resources/Plant/SunFlower.xml","Resources/Plant/SunFlower.png");
	spriteCache->addSpriteFramesWithFile("Resources/Plant/Sun.xml","Resources/Plant/Sun.png");
	spriteCache->addSpriteFramesWithFile("Resources/Plant/Peashooter.xml","Resources/Plant/Peashooter.png");
	spriteCache->addSpriteFramesWithFile("Resources/Zombie/Zombie.xml","Resources/Zombie/Zombie.png");
	spriteCache->addSpriteFramesWithFile("Resources/bullet.xml","Resources/bullet.png");
	spriteCache->addSpriteFramesWithFile("Resources/Zombie/ZombieCommon.xml","Resources/Zombie/ZombieCommon.png");
	spriteCache->addSpriteFramesWithFile("Resources/Plant/WallNut.xml","Resources/Plant/WallNut.png");
	spriteCache->addSpriteFramesWithFile("Resources/Plant/CherryBomb.xml","Resources/Plant/CherryBomb.png");
	spriteCache->addSpriteFramesWithFile("Resources/Plant/PotatoMine.xml","Resources/Plant/PotatoMine.png");
	
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	//�����¼��ַ���
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//����
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//���Ӱ�
	m_pSeedLayer = SeedLayer::create();
	this->addChild(m_pSeedLayer);
	//����
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//̫����
	m_pSunshineLayer = SunshineLayer::create();
	this->addChild(m_pSunshineLayer,80);
	//�ӵ���
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);
	//ֲ���
	m_pPlantLayer = PlantLayer::create();
	m_pPlantLayer->setDelegate(this);
	this->addChild(m_pPlantLayer);
	//��ʬ��
	m_pZombieLayer = ZombieLayer::create();
	this->addChild(m_pZombieLayer);
	//��ʼ������
	m_pBackgroundLayer->loadLevel("Resources/Level/level1-1.lua");
	//��ʼ����ʬ
	m_pZombieLayer->createZombiesFromXml(m_pBackgroundLayer->getZombiePath());

	this->scheduleUpdate();

	//������Ӱ� todo
	m_pSeedLayer->addSeed("SunFlower");
	m_pSeedLayer->addSeed("Peashooter");
	m_pSeedLayer->addSeed("WallNut");
	m_pSeedLayer->addSeed("CherryBomb");
	m_pSeedLayer->addSeed("PotatoMine");
	//todo
	this->move(Point(-200,0));
	return true;
}
void GameScene::update(float dt)
{
	m_pSeedLayer->update(dt);
	m_pPlantLayer->update(dt);
	m_pSunshineLayer->update(dt);
	m_pZombieLayer->update(dt);
	//���� ��������
	if(m_pBackgroundLayer->isDay())
	{
		auto elapsed = dt + m_pBackgroundLayer->getElapsed();
		if(elapsed >= m_pBackgroundLayer->getSkillCD())
		{
			elapsed = 0.f;
			Rect rect = m_pBackgroundLayer->getLegalRect();
			//����̫��
			auto x = RANDOM(rect.origin.x,rect.size.width);
			auto y = -80;
			this->produceSunshine(Point(x,y),SunshineType::kSunshineType_25,SunshineRoute::kSunshineRoute_line);
			//
			m_pBackgroundLayer->initSkillCD();
		}
		m_pBackgroundLayer->setElapsed(elapsed);
	}
	m_pBulletLayer->update(dt);
	//���� �ӵ��뽩ʬ����ײ�� ��ʬ��ֲ�����ײ
	handleCollisionAndUpdate(dt);
}
void GameScene::move(const Point&pos)
{
	m_pBackgroundLayer->setPosition(pos);
	m_pPlantLayer->setPosition(pos);
	m_pSunshineLayer->setPosition(pos);
	m_pBulletLayer->setPosition(pos);
	m_pZombieLayer->setPosition(pos);
}
void GameScene::handleCollisionAndUpdate(float dt)
{
	Vector<Bullet*>* bullets = m_pBulletLayer->getBullets();
	bool bZombieUpdated = false;
	for(int i=0;i < bullets->size() || !bZombieUpdated;i++)
	{
		Bullet*bullet = bullets->size()>0?bullets->at(i):nullptr;
		//���½�ʬ״̬
		for(int j=0;j<5;j++)
		{
			auto zombies = m_pZombieLayer->getZombies(j);
			for(int k=0;k < zombies->size();k++)
			{
				auto zombie = zombies->at(k);                                                  
				Rect r3 = zombie->getSprite()->getSpriteFrameRect();
				r3.origin += zombie->getPosition();
				//ֻ�л���ʱ�Ŵ�����ֲ����ײ
				if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Attack
				|| zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Walk)
				{
					//�ж��Ƿ��ֲ����ײ
					auto carrier = m_pBackgroundLayer->getCarrierByPos(r3.origin+ Point(-10,zombie->getContentSize().height/2));
					auto plant = carrier->getPlant();
					//����ֲ���ʬ��ʼ��ֲ��
					if(plant)
					{
						Rect r4 = plant->getBoundingBox();//plant->getSprite()->getSpriteFrameRect();
						//r4.origin += plant->getPosition();
						if(r3.intersectsRect(r4))
						{
							//��������
							zombie->runAttackAction();
							zombie->attack(plant,dt);
							//ֲ������
							if(plant->isDead())
							{
								carrier->setPlant(nullptr);
								m_pPlantLayer->deletePlant(plant);
							}
						}
					}
					else//��ͼת��Ϊ����״̬
						zombie->runWalkAction();
				}//end zombie plant collision
				//�ж��ӵ��ͽ�ʬ ����ӵ�Ϊ�ջ����ӵ������ã����ж��߼�
				if(bullet == nullptr || !bullet->isAvailable())
					continue;//��ʬֻ��������������ʱ��Ų�����ӵ�������ײ
				if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_EntireDead)
					continue;
				Rect r2 = bullet->getBoundingBox();
				//��ײ����ʬ���ˣ��ӵ�����
				if(r3.intersectsRect(r2))
				{
					zombie->hurt(bullet->getDamage());
					bullet->hurt(1);
				}
			}//end for zombine
			bZombieUpdated = true;
		}//end for
	}//end for
}
void GameScene::shootTo(const Point&startPos,const Point&endPos,const std::string&bulletName,BulletRoute routeType)
{
	m_pBulletLayer->shootTo(startPos,endPos,bulletName,routeType);
}
void GameScene::produceSunshine(const Point&startPos,SunshineType type,SunshineRoute route)
{
	m_pSunshineLayer->produceSunshine(startPos,type,route);
}
bool GameScene::clickSunshine(const Point&location)
{
	auto pos = location - m_pBackgroundLayer->getPosition();
	//�ռ�̫��
	return m_pSunshineLayer->collectSunshine(pos);
}
bool GameScene::clickSeed(const Point&pos)
{
	bool bRet = m_pSeedLayer->setSelectedSeed(pos);
	if(bRet)
		m_pPanelLayer->getShovel()->clear();
	return bRet;
}
bool GameScene::clickShovel(const Point&pos)
{
	bool bRet = m_pPanelLayer->isClickedShovel(pos);
	if(bRet)
		m_pSeedLayer->clearClickHigh();
	return bRet;
}
void GameScene::clickGround(const Point&location)
{
	//��ȡ��������
	auto pos = location - m_pBackgroundLayer->getPosition();
	auto rect = m_pBackgroundLayer->getLegalRect();
	//��֤��Ϸ�
	if(rect.containsPoint(pos) == false)
		return ;
	//��ѡ�������Ӱ� �ҵ���ĵط��пյ� ���� ̫���㹻����ֲ��
	auto seed = m_pSeedLayer->getSelectedSeed();
	//��ȡ���λ�ö�Ӧ������
	auto carrier = m_pBackgroundLayer->getCarrierByPos(pos);
	int line = (pos.y - m_pBackgroundLayer->getLegalRect().origin.y)/carrier->getContentSize().height;
	if(seed)
	{
		//����û��ֲ��
		if(carrier && carrier->getPlant() == nullptr)
		{
			auto sunNum = DynamicData::getInstance()->getSunNumber();
			//Ǯ�㹻������ֲ
			if(sunNum - seed->getWorth() >= 0)
			{
				//ȡ��ѡ��
				m_pSeedLayer->clearClickHigh();
				DynamicData::getInstance()->alertSunNum(-seed->getWorth());
				auto plant = seed->createPlant();
				
				plant->setPosition(carrier->getPosition());
				plant->setLine(line);//������������
				//���ݸ� ����� PlantLayer
				carrier->setPlant(plant);
				m_pPlantLayer->bindPlant(plant);
				return;
			}
		}
	}
	//���Ѿ�ѡ���˲��Ӳ��ҵ���ĵط���ֲ������ֲ��
	auto shovel = m_pPanelLayer->getShovel();
	if(shovel && shovel->isSelected())
	{
		//���в������� ������ֻ꣬���漰����λ�ã������漰�߼�
		shovel->runKillPlantAction(location);
		//����������ֲ�ɾ��
		if(carrier && carrier->getPlant())
		{
			m_pPlantLayer->deletePlant(carrier->getPlant());
			carrier->setPlant(nullptr);
			return ;
		}
	}
}