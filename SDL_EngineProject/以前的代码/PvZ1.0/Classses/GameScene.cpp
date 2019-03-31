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
	//读取Seed.lua
	MainLua::getInstance()->dofile("Resources/Seed.lua");
	MainLua::getInstance()->dofile("Resources/Bullet.lua");
	MainLua::getInstance()->dofile("Resources/Zombie.lua");
	//加载动画帧
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
	//触摸事件分发器
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//背景
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//种子包
	m_pSeedLayer = SeedLayer::create();
	this->addChild(m_pSeedLayer);
	//面板层
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//太阳层
	m_pSunshineLayer = SunshineLayer::create();
	this->addChild(m_pSunshineLayer,80);
	//子弹层
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);
	//植物层
	m_pPlantLayer = PlantLayer::create();
	m_pPlantLayer->setDelegate(this);
	this->addChild(m_pPlantLayer);
	//僵尸层
	m_pZombieLayer = ZombieLayer::create();
	this->addChild(m_pZombieLayer);
	//初始化背景
	m_pBackgroundLayer->loadLevel("Resources/Level/level1-1.lua");
	//初始化僵尸
	m_pZombieLayer->createZombiesFromXml(m_pBackgroundLayer->getZombiePath());

	this->scheduleUpdate();

	//添加种子包 todo
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
	//场景 产生阳光
	if(m_pBackgroundLayer->isDay())
	{
		auto elapsed = dt + m_pBackgroundLayer->getElapsed();
		if(elapsed >= m_pBackgroundLayer->getSkillCD())
		{
			elapsed = 0.f;
			Rect rect = m_pBackgroundLayer->getLegalRect();
			//产生太阳
			auto x = RANDOM(rect.origin.x,rect.size.width);
			auto y = -80;
			this->produceSunshine(Point(x,y),SunshineType::kSunshineType_25,SunshineRoute::kSunshineRoute_line);
			//
			m_pBackgroundLayer->initSkillCD();
		}
		m_pBackgroundLayer->setElapsed(elapsed);
	}
	m_pBulletLayer->update(dt);
	//处理 子弹与僵尸的碰撞， 僵尸与植物的碰撞
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
		//更新僵尸状态
		for(int j=0;j<5;j++)
		{
			auto zombies = m_pZombieLayer->getZombies(j);
			for(int k=0;k < zombies->size();k++)
			{
				auto zombie = zombies->at(k);                                                  
				Rect r3 = zombie->getSprite()->getSpriteFrameRect();
				r3.origin += zombie->getPosition();
				//只有活着时才处理与植物碰撞
				if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Attack
				|| zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Walk)
				{
					//判断是否和植物碰撞
					auto carrier = m_pBackgroundLayer->getCarrierByPos(r3.origin+ Point(-10,zombie->getContentSize().height/2));
					auto plant = carrier->getPlant();
					//存在植物，僵尸开始吃植物
					if(plant)
					{
						Rect r4 = plant->getBoundingBox();//plant->getSprite()->getSpriteFrameRect();
						//r4.origin += plant->getPosition();
						if(r3.intersectsRect(r4))
						{
							//攻击动画
							zombie->runAttackAction();
							zombie->attack(plant,dt);
							//植物死亡
							if(plant->isDead())
							{
								carrier->setPlant(nullptr);
								m_pPlantLayer->deletePlant(plant);
							}
						}
					}
					else//试图转换为行走状态
						zombie->runWalkAction();
				}//end zombie plant collision
				//判断子弹和僵尸 如果子弹为空或者子弹不可用，则不判断逻辑
				if(bullet == nullptr || !bullet->isAvailable())
					continue;//僵尸只有在真正死亡的时候才不会和子弹发生碰撞
				if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_EntireDead)
					continue;
				Rect r2 = bullet->getBoundingBox();
				//碰撞，僵尸受伤，子弹死亡
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
	//收集太阳
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
	//获取世界坐标
	auto pos = location - m_pBackgroundLayer->getPosition();
	auto rect = m_pBackgroundLayer->getLegalRect();
	//保证点合法
	if(rect.containsPoint(pos) == false)
		return ;
	//若选中了种子包 且点击的地方有空地 并且 太阳足够，种植物
	auto seed = m_pSeedLayer->getSelectedSeed();
	//获取点击位置对应的载体
	auto carrier = m_pBackgroundLayer->getCarrierByPos(pos);
	int line = (pos.y - m_pBackgroundLayer->getLegalRect().origin.y)/carrier->getContentSize().height;
	if(seed)
	{
		//载体没有植物
		if(carrier && carrier->getPlant() == nullptr)
		{
			auto sunNum = DynamicData::getInstance()->getSunNumber();
			//钱足够，则种植
			if(sunNum - seed->getWorth() >= 0)
			{
				//取消选中
				m_pSeedLayer->clearClickHigh();
				DynamicData::getInstance()->alertSunNum(-seed->getWorth());
				auto plant = seed->createPlant();
				
				plant->setPosition(carrier->getPosition());
				plant->setLine(line);//设置所在行数
				//传递给 载体和 PlantLayer
				carrier->setPlant(plant);
				m_pPlantLayer->bindPlant(plant);
				return;
			}
		}
	}
	//若已经选中了铲子并且点击的地方有植物，则铲除植物
	auto shovel = m_pPanelLayer->getShovel();
	if(shovel && shovel->isSelected())
	{
		//运行铲除动画 相对坐标，只是涉及动画位置，并不涉及逻辑
		shovel->runKillPlantAction(location);
		//如果载体存在植物，删除
		if(carrier && carrier->getPlant())
		{
			m_pPlantLayer->deletePlant(carrier->getPlant());
			carrier->setPlant(nullptr);
			return ;
		}
	}
}