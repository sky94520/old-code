#include "GameScene.h"
#include "StaticData.h"
#include "DynamicData.h"
#include "CardChooseLayer.h"
#include "CardLayer.h"
#include "PanelLayer.h"
#include "ProductLayer.h"
#include "Product.h"
#include "Plant.h"
#include "Carrier.h"
#include "ZombieBase.h"
#include "ZombieLayer.h"
#include "Terrain.h"
#include "Bullet.h"
#include "EffectLayer.h"
#include "HpBar.h"
#include "NightPlant.h"
#include "Garnishry.h"
#include "VesselPlant.h"
#include "ShooterPeaBullet.h"
#include "Defender.h"
#include "NameDef.h"

GameScene::GameScene()
	:m_pTouchLayer(nullptr),m_pLevelLayer(nullptr)
	,m_pPlantLayer(nullptr),m_pZombieLayer(nullptr)
	,m_pBulletLayer(nullptr),m_pEffectLayer(nullptr)
	,m_pCardLayer(nullptr),m_pCardChooseLayer(nullptr)
	,m_pPanelLayer(nullptr),m_pProductLayer(nullptr)
	,m_bSwallowTouch(false),m_gameState(GameState::None)
{
}

GameScene::~GameScene()
{
	StaticData::purge();
	DynamicData::getInstance()->purge();
}

bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->preloadResources();

	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//关卡层 todo
	m_pLevelLayer = LevelLayer::create("level/level3-1.tmx");
	m_pLevelLayer->setDelegate(this);
	m_pLevelLayer->setPosition(Point(-100.f,0.f));
	this->addChild(m_pLevelLayer);
	//植物层
	m_pPlantLayer = PlantLayer::create();
	m_pPlantLayer->setDelegate(this);
	this->addChild(m_pPlantLayer);
	//僵尸层
	m_pZombieLayer = ZombieLayer::create();
	m_pZombieLayer->setDelegate(this);
	this->addChild(m_pZombieLayer);
	//子弹层
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//特效层
	m_pEffectLayer = EffectLayer::create();
	this->addChild(m_pEffectLayer);
	//卡片选择层
	m_pCardChooseLayer = CardChooseLayer::create();
	m_pCardChooseLayer->setPosition(0.f,-visibleSize.height);
	m_pCardChooseLayer->setDelegate(this);

	this->addChild(m_pCardChooseLayer);
	//卡片层
	m_pCardLayer = CardLayer::create();
	this->addChild(m_pCardLayer);
	//添加面板层
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//产品层
	m_pProductLayer = ProductLayer::create();
	this->addChild(m_pProductLayer);
	//刷新面板
	m_pPanelLayer->updateUI();
	//进行一些初始化
	auto initialSun = m_pLevelLayer->getInitialSun();
	//添加阳光值
	this->addSun(initialSun);
	//根据当前关卡类型决定是否进行移动
	this->levelLoadCallback();

	return true;
}

void GameScene::update(float dt)
{
	m_pPlantLayer->update(dt);
	m_pZombieLayer->update(dt);
	m_pBulletLayer->update(dt);
	m_pCardLayer->update(dt);
	m_pLevelLayer->update(dt);
	m_pProductLayer->update(dt);
}

void GameScene::removePlant(Plant*plant)
{
	//TODO
	m_pPlantLayer->removePlant(plant);
	plant->removeFromParent();
}

void GameScene::preloadResources()
{
	//加载图片资源
	auto spriteCache = Director::getInstance()->getSpriteFrameCache();

	spriteCache->addSpriteFramesWithFile("sprite/card.xml");
	spriteCache->addSpriteFramesWithFile("sprite/ui.xml");
	spriteCache->addSpriteFramesWithFile("sprite/product.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant1.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant2.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant3.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant4.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant5.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant6.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant7.xml");
	spriteCache->addSpriteFramesWithFile("sprite/plant8.xml");

	spriteCache->addSpriteFramesWithFile("sprite/zombie1.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie2.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie3.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie4.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie5.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie6.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie7.xml");
	spriteCache->addSpriteFramesWithFile("sprite/zombie8.xml");

	spriteCache->addSpriteFramesWithFile("sprite/effect.xml");

	//AnimationCache::getInstance()->addAnimationsWithFile(STATIC_DATA_STRING("animation_plist_path"));
	AnimationCache::getInstance()->addAnimationsWithFile("data/animations.plist");

	AnimationCache::getInstance()->addAnimationsWithFile("data/plant_animations1.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("data/plant_animations2.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("data/plant_animations3.plist");

	AnimationCache::getInstance()->addAnimationsWithFile("data/zombie_animations1.plist");
	//todo
	StaticData::getInstance();
}

void GameScene::levelLoadCallback()
{
	//获取当前的关卡状态
	auto levelType = m_pLevelLayer->getLevelCardShowType();
	//向右移动，之后回调函数
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto size = m_pLevelLayer->getContentSize();
	//当前是植物，则向左移动，出现卡片
	if (levelType == LevelCardType::Plant)
	{
		auto move = MoveTo::create(3.f,visibleSize.width - size.width);
		CallFunc*end = CallFunc::create([this,levelType]()
		{
			this->loadCard(levelType);
		});
		auto seq = Sequence::createWithTwoActions(move,end);
		m_pLevelLayer->runAction(seq);
	}//当前是僵尸，直接开始游戏
	else if (levelType == LevelCardType::Zombie)
	{
		this->loadCard(levelType);
	}
}

void GameScene::loadCard(LevelCardType levelType)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取当前的数目和卡槽数目
	auto cardSlotNum = DynamicData::getInstance()->getCardVesselNum();
	vector<string> ownCards;
	//设置卡槽个数
	m_pCardLayer->setCardSlotNum(cardSlotNum,levelType);

	if (levelType == LevelCardType::Plant)
	{
		ownCards = DynamicData::getInstance()->getNameOfPlantCards();
	}
	else if (levelType == LevelCardType::Zombie)
	{
		ownCards = DynamicData::getInstance()->getNameOfZombieCards();
	}
	else
	{
		return;
	}
	//不显示卡片选择界面
	if (ownCards.size() <= cardSlotNum)
	{
		//添加卡片
		for (unsigned int i = 0;i < ownCards.size();i++)
		{
			//添加卡片到卡片层
			m_pCardLayer->addCard(ownCards.at(i),CardType::Common);
		}
		this->levelStart(levelType);
		//设置当前状态为 playing
		m_gameState = GameState::Play;
	}
	else//显示卡片选择界面
	{
		m_gameState = GameState::CardChoose;

		MoveBy*move = MoveBy::create(0.5f,Point(0,visibleSize.height));
		EaseExponentialOut*action = EaseExponentialOut::create(move);
		//显示出卡片选择界面
		m_pCardChooseLayer->runAction(action);
		//展示出卡片
		m_pCardChooseLayer->show(ownCards);
		//设置开始游戏可以使用
		bool enable = m_pCardLayer->isFullOfCardSlot();
		m_pCardChooseLayer->setStartBtnEnable(enable);
	}
}

void GameScene::levelStart(LevelCardType levelType)
{
	if (levelType == LevelCardType::Plant)
	{
		//镜头向左回转，之后开始游戏
		DelayTime*delayTime = DelayTime::create(0.5f);
		MoveTo*move = MoveTo::create(3.f,Point(-100,0));//-100,0
		CallFunc*end = CallFunc::create([this]()
		{
			this->scheduleUpdate();
		});
		auto seq = Sequence::create(delayTime,move,end,nullptr);
		m_pLevelLayer->runAction(seq);
	}
	else if (levelType == LevelCardType::Zombie)
	{
		this->scheduleUpdate();
	}

	//进行对象层的解析
	auto &groups = m_pLevelLayer->getEntityObjects();
	vector<Card*> cards;

	for (const auto&value : groups)
	{
		const auto& object = value.asValueMap();

		auto type = object.at("type").asString();
		auto name = object.at("name").asString();
		float x = (float)object.at("x").asInt();
		float y = (float)object.at("y").asInt();
		//获取对应的terrain
		auto terrain = m_pLevelLayer->getClickedTerrain(Point(x,y));
		//生成的植物也得符合地形
		if (type == "plant")
		{
			Card*card = nullptr;
			//先进行卡片查找
			auto it = find_if(cards.begin(),cards.end(),[&name](Card*temp)
			{
				return temp->getCardName() == name;
			});

			if (it != cards.end())
			{
				card = *it;
			}
			else
			{
				card = m_pCardLayer->makeCard(name,CardType::Consumable);
				cards.push_back(card);
			}

			bool bRet = this->tryPlanting(card,terrain);
		}
	}
	//清除卡片容器
	cards.clear();
	//隐藏未被使用的卡槽
	m_pCardLayer->hideUnusedCardSlot();
	//设置僵尸行走路径
	m_pZombieLayer->setZombiePaths(m_pLevelLayer->getZombiePaths());
}

void GameScene::collectProduct(Product*product)
{
	//点击了太阳
	if (product->getProductType() == ProductType::Sun)
	{
		//获取结束位置
		auto endPos = m_pPanelLayer->getSunBgPosition();
		auto deltaPos = product->getPosition() - endPos;

		auto length = deltaPos.length();

		MoveTo*move = MoveTo::create(length/400.f,endPos);
		CallFunc*end = CallFunc::create([this,product]()
		{
			this->addSun(product->getNumber());
			product->setDead(true);
		});
		auto seq = Sequence::createWithTwoActions(move,end);
		//运行动作
		product->stopAllActions();
		product->runAction(seq);
	}
}

bool GameScene::tryPlanting(Card*card,Terrain*terrain)
{
	Plant*newPlant = nullptr;
	auto topPlant = m_pLevelLayer->getTopPlant(terrain);
	//该卡片是咖啡豆 上层植物是夜晚植物并且未唤醒才种植
	if (card->getCardName() == "CoffeeBean"
		&& topPlant != nullptr && topPlant->getPlantType() == PlantType::NightPlant)
	{
		bool bRet = this->tryEatingCoffeeBean(static_cast<NightPlant*>(topPlant));
		
		return bRet;
	}
	//获取必要物品
	auto necessaryItem = card->getNecessoryItem();
	//升级植物
	if (!necessaryItem.empty() && topPlant != nullptr
		&& topPlant->getPlantName() == necessaryItem)
	{
		newPlant = this->upgradePlant(card,topPlant);
	}
	//种植保卫者
	if (StaticData::getInstance()->getPlantCsvStructForName(card->getCardName())->type == PlantType::Defender)
	{
		newPlant = this->plantDefender(card,terrain);
	}
	//种植植物
	else if (necessaryItem.empty())
	{
		newPlant = this->planting(card,terrain,topPlant);
	}
	//设置基础属性
	if (newPlant != nullptr)
	{
		newPlant->setActiveTime(card->getActiveTime());
		newPlant->setDelegate(this);
		//确定植物是否活动，并调用对应的方法
		this->judgeActivationForPlant(newPlant);
		//添加到entity layer 场景
		auto entityLayer = this->getEntityLayer();
		int localZOrder = m_pLevelLayer->getSumOfZOrderPlant(terrain,newPlant);
		//根据当前行再设置z order
		localZOrder += terrain->getRow() * Z_ORDER_INTERVAL;

		entityLayer->addChild(newPlant,localZOrder);
	}

	return newPlant != nullptr;
}

Plant*GameScene::planting(Card*card,Terrain*terrain,Plant*topPlant)
{
	Plant*newPlant = nullptr;
	Point newPos;
	//地形上的植物为空 地形符合 并且塔基没被破坏，则创建
	if (topPlant == nullptr && card->isIncludeTerrain(terrain->getTerrainType())
		&& !terrain->isDestroyed())
	{
		newPlant = m_pPlantLayer->makePlant(card->getCardName());
		newPlant->setLocatedCarrier(terrain);
		//再设置一些基础属性
		newPos = terrain->getPosition();
		//如果是保卫者
/*		if (newPlant->getPlantType() == PlantType::Defender 
			&& terrain->getDefender() == nullptr)
		{
			terrain->setDefender(static_cast<Defender*>(newPlant));
		}
		else//普通的植物*/
		{
			terrain->setInnerPlant(newPlant);
		}
		//新植物是容器植物，设置内部的carrier的row
		if (newPlant->getPlantType() == PlantType::Vessel)
		{
			static_cast<VesselPlant*>(newPlant)->setRow(terrain->getRow());
		}
	}
	//存在容器植物,继续判断
	else if(topPlant != nullptr && topPlant->getPlantType() == PlantType::Vessel)
	{
		auto height = topPlant->getContentSize().height;

		auto vessel = static_cast<VesselPlant*>(topPlant)->getInnerCarrier();
		auto offsetPos = Point(0.f,-height/2.f);

		if (card->isIncludeTerrain(vessel->getTerrainType()))
		{
			newPlant = m_pPlantLayer->makePlant(card->getCardName());
			//再设置一些基础属性
			newPos = topPlant->getPosition() + offsetPos;

			vessel->setInnerPlant(newPlant);
			newPlant->setVesselPlant(topPlant);
			newPlant->setLocatedCarrier(vessel);
		}

	}//end else if
	//设置位置
	if (newPlant != nullptr)
		newPlant->setPosition(newPos);

	return newPlant;
}

Plant* GameScene::plantDefender(Card*card,Terrain*terrain)
{
	Defender*defender = nullptr;
	auto innerPlant = terrain->getInnerPlant();
	Point newPos = terrain->getPosition();
	//塔基符合地形
	if (card->isIncludeTerrain(terrain->getTerrainType()))
	{
		//该塔基没有保卫者 就进行创建
		if (terrain->getDefender() == nullptr)
		{
			defender = static_cast<Defender*>(m_pPlantLayer->makePlant(card->getCardName()));

			terrain->setDefender(defender);
			defender->setLocatedCarrier(terrain);
		}
		else//已经有了保卫者
		{
			//TODO
		}
	}
	//存在内部容器植物
	else if (innerPlant != nullptr 
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto vesselPlant = static_cast<VesselPlant*>(innerPlant);
		auto carrier = vesselPlant->getInnerCarrier();
		//地形符合
		if (card->isIncludeTerrain(carrier->getTerrainType()))
		{
			//设置保卫者
			if (carrier->getDefender() == nullptr)
			{
				defender = static_cast<Defender*>(m_pPlantLayer->makePlant(card->getCardName()));

				carrier->setDefender(defender);
				defender->setLocatedCarrier(carrier);
				defender->setVesselPlant(innerPlant);

				auto size = terrain->getContentSize();
				newPos.y += size.height/2;
			}
			else
			{
				//TODO
			}
		}
	}
	if (defender != nullptr)
	{
		defender->setPosition(terrain->getPosition());
	}
	return defender;
}

Plant*GameScene::upgradePlant(Card*card,Plant*topPlant)
{
	//创建新植物
	Plant*newPlant = m_pPlantLayer->makePlant(card->getCardName());
	//获取位置
	Point newPos = topPlant->getPosition();;
	Carrier*carrier = topPlant->getLocatedCarrier();
	//设置属性
	newPlant->setVesselPlant(topPlant->getVesselPlant());
	newPlant->setLocatedCarrier(carrier);
	//设置位置
	newPlant->setPosition(newPos);

	carrier->setInnerPlant(newPlant);
	//移除旧植物
	this->removePlant(topPlant);

	return newPlant;
}

bool GameScene::tryEatingCoffeeBean(NightPlant*plant)
{
	//如果该植物已经唤醒，则返回false
	if (!plant->isSleeping())
		return false;
	//TODO
	if (plant->getActionByTag(1) != nullptr)
		return false;
	//唤醒夜晚植物
	auto size = plant->getContentSize();
	auto pos = plant->getPosition() - Point(0,size.height/2.f);
	float duration = this->showCoffeeBeanEatAction(pos);
	//运行动作，在动作完成后植物被唤醒
	DelayTime*delayTime = DelayTime::create(duration);
	CallFunc*end = CallFunc::create([plant]()
	{
		plant->exitSleeping();
	});
	
	auto seq = Sequence::createWithTwoActions(delayTime,end);
	seq->setTag(1);

	plant->runAction(seq);

	return true;
}

bool GameScene::tryMakingZombie(Card*card,Terrain*terrain)
{
	bool bRet = false;
	//获取关卡对应的行数
	int row = terrain->getRow();
	//获取对应的路径
	const auto path = m_pLevelLayer->getZombiePathOfRow(row);
	//生成僵尸
	auto zombie = m_pZombieLayer->makeZombie(card->getCardName(),row);
	//设置位置
	auto pos = terrain->getPosition();

	auto terrainSize = terrain->getContentSize();
	auto zombieSize = zombie->getContentSize();

	pos.y -= (zombieSize.height - terrainSize.height)/2.f;

	zombie->setPosition(pos);
	zombie->setRow(row);
	zombie->setDelegate(this);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	//设置z order
	int localZOrder = ZOMBIE_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(zombie,localZOrder);
	
	bRet = true;
	return bRet;
}

void GameScene::judgeActivationForPlant(Plant*plant)
{
	//夜晚植物需要判断当前场景是否是夜晚
	if (plant->getPlantType() == PlantType::NightPlant)
	{
		auto curActiveTime = this->getCurActiveTime();

		if (!PlantLayer::isActiveTimeForPlant(plant,curActiveTime))
		{
			(static_cast<NightPlant*>(plant))->enterSleeping();
		}
	}
}

string GameScene::getSpriteFilenameOfGarnishry(Garnishry*garnishry)
{
	auto garnishry_sprite_format = STATIC_DATA_STRING("garnishry_sprite_format");
	//获取饰品名称
	auto garnishryName = garnishry->getGarnishryName();
	//对应的精灵名称
	string spriteFilename;
	//获取损伤点
	int index = 0;
	//避免血量小于0
	if (garnishry->getHitPoint() > 0)
	{
		index = garnishry->getMaxHitPoint() / garnishry->getHitPoint();
	}
	index += 1;

	spriteFilename = StringUtils::format(garnishry_sprite_format.c_str(),garnishryName.c_str(),index);
	//返回精灵文件名
	return spriteFilename;
}

void GameScene::addSun(int num)
{
	auto sun = DynamicData::getInstance()->getSunNumber();

	DynamicData::getInstance()->setSunNumber(sun + num);

	m_pCardLayer->updateSelf();
	m_pPanelLayer->updateSun();
}

void GameScene::subSun(int num)
{
	auto sun = DynamicData::getInstance()->getSunNumber();

	DynamicData::getInstance()->setSunNumber(sun - num);

	m_pCardLayer->updateSelf();
	m_pPanelLayer->updateSun();
}

void GameScene::makeSun(int number,FiniteTimeAction*action,const Point&bornPos)
{
	m_pProductLayer->makeSun(number,action,bornPos,m_pProductLayer);
}

TMXLayer* GameScene::getEntityLayer()
{
	return m_pLevelLayer->getEntityLayer();
}

Rect GameScene::getGameVisibleRect()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point pos = m_pLevelLayer->getPosition();

	//TODO
	pos.x = (float)SDL_fabs(pos.x);

	return Rect(pos,visibleSize);
}

void GameScene::confuseZombie(ZombieBase*zombie)
{
	//保存当前的zombie
	zombie->retain();
	//移除该僵尸
	m_pZombieLayer->removeZombie(zombie,false);
	//设置僵尸的颜色
	zombie->getSprite()->setColorMod(Color3B(0,0,0xff));
	//强制使僵尸的方向改为向右
	zombie->setDir(Direction::Right);
	//设置为迷惑状态
	zombie->setConfused(true);
	//添加到指定容器
	m_pPlantLayer->addItemToMovablePlants(zombie);
	//释放该僵尸的引用
	zombie->release();
}

Plant*GameScene::getTopPlant(Terrain*terrain)
{
	return m_pLevelLayer->getTopPlant(terrain);
}

Plant* GameScene::getTopPlantOfAttack(Terrain*terrain)
{
	return m_pLevelLayer->getTopPlantOfAttack(terrain);
}

ZombieBase*GameScene::findFirstZombieOfRow(int row,Direction attackDir,const Point&pos)
{
	auto zombies = this->getZombiesOfRow(row);
	ZombieBase*zombie = nullptr;

	if (attackDir == Direction::All && !zombies.empty())
	{
		zombie = zombies.front();
	}
	else if (attackDir == Direction::Right)
	{
		for (auto it = zombies.begin();it != zombies.end();it++)
		{
			auto zombiePos = (*it)->getPosition();

			if (zombiePos.x > pos.x)
			{
				zombie = (*it);
				break;
			}
		}
	}
	else if (attackDir == Direction::Left && !zombies.empty())
	{
		auto firstZombie = zombies.front();
		auto zombiePos = firstZombie->getPosition();

		if (zombiePos.x < pos.x)
		{
			zombie = firstZombie;
		}
	}
	return zombie;
}

ZombieBase*GameScene::findFirstCollidedZombie(int row,const Rect&rect)
{
	auto zombies = this->getZombiesOfRow(row);
	ZombieBase *zombie = nullptr;

	auto it = find_if(zombies.begin(),zombies.end(),[rect](ZombieBase*zombie)
	{
		return zombie->getCollisionBoundingBox().intersectRect(rect);
	});
	if (it != zombies.end())
	{
		zombie = *it;
	}
	return zombie;
}

vector<ZombieBase*> GameScene::findCollidedZombies(int row,const Rect& rect)
{
	auto zombies = this->getZombiesOfRow(row);
	ZombieBase *zombie = nullptr;
	vector<ZombieBase*> targets;
	//找到所以碰撞的僵尸
	for (auto zombie : zombies)
	{
		auto zombieRect = zombie->getCollisionBoundingBox();

		if (zombieRect.intersectRect(rect))
		{
			targets.push_back(zombie);
		}
	}
	return targets;
}

Character* GameScene::findFirsCollidedMovableCharacterOfRow(int row,Direction attackDir,const Rect&rect)
{
	auto vec = m_pPlantLayer->getMovablePlantList();
	Character*target = nullptr;

	for (auto it = vec.begin();it != vec.end();it++)
	{
		auto temp = *it;

		auto boundingBox = temp->getCollisionBoundingBox();

		if (rect.intersectRect(boundingBox))
		{
			target = temp;
			break;
		}
	}

	return target;
}

ZombieBase* GameScene::findFirstZombieOfIronGarnishry(const Rect& rect)
{
	//发现对应的僵尸
	auto zombies = this->getZombiesOfRow(-1);
	//找到碰撞的并且带有饰品的僵尸
	for (const auto& zombie : zombies)
	{
		auto zombieRect = zombie->getCollisionBoundingBox();
		//对碰撞的僵尸检测
		if (zombieRect.intersectRect(rect))
		{
			auto garnishry = zombie->getGarnishry();

			if (garnishry != nullptr && garnishry->getType() == Garnishry::Type::Iron 
				&& garnishry->getHitPoint() > 0)
			{
				return zombie;
			}
		}
	}
	return nullptr;
}

ShooterPeaBullet* GameScene::findFirstShooterPeaBullet(int row,const Rect&rect)
{
	auto &bullets = m_pBulletLayer->getBulletList();
	//遍历数组
	for (auto bullet : bullets)
	{
		auto r = bullet->getCollisionBoundingBox();
		//当前行数相同 类型是豌豆弹 产生矩形碰撞，并且可以进行转换
		if (bullet->getRow() == row 
			&& bullet->getBulletType() == BulletType::ShooterPeaBullet
			&& r.intersectRect(rect) 
			&& bullet->isCanTransform())
		{
			return static_cast<ShooterPeaBullet*>(bullet);
		}
	}
	return nullptr;
}

vector<Terrain*>& GameScene::getTerrainsOfRow(int row)
{
	return m_pLevelLayer->getTerrainsOfRow(row);
}

void GameScene::addPeaBullet(int damage,int row,const Point&startPos,bool bRight)
{
	auto type = ShooterPeaBullet::Type::PeaBullet;
	this->addShooterPeaBullet(type,row,startPos,bRight);
}

void GameScene::addSnowPeaBullet(int damage,int row,const Point&startPos)
{
	auto type = ShooterPeaBullet::Type::SnowPeaBullet;
	this->addShooterPeaBullet(type,row,startPos);
}

void GameScene::addFirePeaBullet(int damage,int row,const Point&startPos)
{
	auto type = ShooterPeaBullet::Type::FirePeaBullet;
	this->addShooterPeaBullet(type,row,startPos);
}

void GameScene::addShooterPeaBullet(ShooterPeaBullet::Type type,int row,const Point&startPos,bool bRight)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point deltaPos;
	auto bullet = m_pBulletLayer->addShooterPeaBullet(type);
	//设置基础属性
	bullet->setRow(row);
	//bullet->setDamage(damage);
	bullet->setPosition(startPos);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	//设置z order
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(bullet,localZOrder);
	//设置位置
	if (bRight)
	{
		deltaPos.x = visibleSize.width - startPos.x;
		deltaPos = m_pLevelLayer->convertToNodeSpace(deltaPos);
	}
	else
	{
		deltaPos.x = -startPos.x;
	}

	auto action = BulletLayer::lineRoute(bullet,deltaPos,300.f,true);
	bullet->runAction(action);
}


void GameScene::addBoom(int damage,int row,const Rect&rect)
{
	auto boom = m_pBulletLayer->addBoom();

	boom->setRow(row);
	boom->setDamage(damage);
	boom->setCollisionRect(rect);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	entityLayer->addChild(boom,BULLET_Z_ORDER);
}

void GameScene::addCabbageBullet(ZombieBase*zombie,int damage,int row,const Point&startPos)
{
	auto bullet = m_pBulletLayer->addCabbageBullet();

	bullet->setDamage(damage);
	bullet->setRow(row);
	bullet->setPosition(startPos);
	bullet->setAimZombie(zombie);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(bullet,localZOrder);
	//设置动作
	auto endPos = zombie->getPosition();
	
	auto seq = BulletLayer::jumpRoute(bullet,startPos,endPos,300.f);
	bullet->runAction(seq);
}

void GameScene::addCornpultBullet(ZombieBase*zombie,bool isButter,int damage,int row,const Point&startPos)
{
	auto bullet = m_pBulletLayer->addCornpultBullet(isButter);

	bullet->setDamage(damage);
	bullet->setRow(row);
	bullet->setPosition(startPos);
	bullet->setAimZombie(zombie);
	//设置类型
	if (isButter)
	{
		bullet->setAttackType(AttackType::TrackAndButter);
		bullet->setDuration(4.f);
	}
	else
	{
		bullet->setAttackType(AttackType::Track);
	}
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;
	
	entityLayer->addChild(bullet,localZOrder);
	//设置动作
	auto endPos = zombie->getPosition();

	auto seq = BulletLayer::jumpRoute(bullet,startPos,endPos,300.f);
	bullet->runAction(seq);
}

void GameScene::addFumeShroomBullet(int damage,int row,const Point&startPos,float atkScope)
{
	auto bullet = m_pBulletLayer->addFumeShroomBullet();

	bullet->setRow(row);
	bullet->setDamage(damage);
	bullet->setPosition(startPos);
	bullet->setAtkScope(atkScope);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;
	
	entityLayer->addChild(bullet,localZOrder);
}

void GameScene::addShroomBullet(int damage,int row,const Point &startPos,float atkScope)
{
	auto bullet = m_pBulletLayer->addShroomBullet();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point deltaPos;
	//确定结束位置
	if (atkScope < 0.f)
	{
		deltaPos.x = visibleSize.width - startPos.x;
		deltaPos = m_pLevelLayer->convertToNodeSpace(deltaPos);
	}
	else
	{
		deltaPos.x = atkScope;
	}
	//设置动作
	auto seq = BulletLayer::lineRoute(bullet,deltaPos,300.f,true);
	bullet->runAction(seq);

	bullet->setRow(row);
	bullet->setDamage(damage);
	bullet->setPosition(startPos);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(bullet,localZOrder);
}

void GameScene::showZombieDie(const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->showZombieDie(layer,zombieName,pos,localZOrder,flipX);
}

void GameScene::showZombieBoom(const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->showZombieBoom(layer,zombieName,pos,localZOrder,flipX);
}

void GameScene::showZombieHead(const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->showZombieHead(layer,zombieName,pos,localZOrder,flipX);
}

void GameScene::showGarnishryFallAction(Garnishry*garnishry,const Point&pos,int localZOrder,bool flipX)
{
	auto layer = this->getEntityLayer();

	if (garnishry != nullptr)
	{
		string spriteFilename = this->getSpriteFilenameOfGarnishry(garnishry);

		m_pEffectLayer->showGarnishryFallAction(layer,spriteFilename,pos,localZOrder,flipX);
	}
}

void GameScene::addButterSplat(const Point&pos,int localZOrder,int uniqueID)
{
	auto layer = this->getEntityLayer();


	m_pEffectLayer->addButterSplat(pos,layer,localZOrder,uniqueID);
}

void GameScene::removeButterSplat(int uniqueID)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->removeButterSplat(layer,uniqueID);
}

void GameScene::addIceTrap(const Point&pos,int localZOrder,int uniqueID)
{
	auto layer = this->getEntityLayer();
	m_pEffectLayer->addIceTrap(pos,layer,localZOrder,uniqueID);
}

void GameScene::removeIceTrap(int uniqueID)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->removeIceTrap(layer,uniqueID);
}

void GameScene::addGarnishryEffect(int uniqueID,const Point&pos,Garnishry*garnishry)
{
	auto layer = this->getEntityLayer();
	auto str = this->getSpriteFilenameOfGarnishry(garnishry);

	m_pEffectLayer->addGarnishryEffect(uniqueID,pos,str,layer,EFFECT_Z_ORDER);
}

void GameScene::removeGarnishryEffect(int uniqueID)
{
	auto layer = this->getEntityLayer();

	m_pEffectLayer->removeGarnishryEffect(layer,uniqueID);
}

void GameScene::showRisingDirt(const Point&pos,int localZOrder)
{
	auto entityLayer = this->getEntityLayer();

	m_pEffectLayer->showRisingDirt(pos,entityLayer,localZOrder);
}

void GameScene::showExplosionSpudow(const Point&pos)
{
	auto entityLayer = this->getEntityLayer();

	m_pEffectLayer->showExplosionSpudow(pos,entityLayer,EFFECT_Z_ORDER);
}

float GameScene::showCoffeeBeanEatAction(const Point&pos)
{
	auto entityLayer = this->getEntityLayer();

	return m_pEffectLayer->showCoffeeBeanEatAction(pos,entityLayer,EFFECT_Z_ORDER);
}

void GameScene::showSnow()
{
	auto entityLayer = this->getEntityLayer();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point pos = Point(visibleSize.width/2,visibleSize.height/2);

	m_pEffectLayer->showSnow(pos,entityLayer,EFFECT_Z_ORDER);
}

void GameScene::showBoom(const Point&pos)
{
	auto entityLayer = this->getEntityLayer();

	m_pEffectLayer->showBoom(pos,entityLayer,EFFECT_Z_ORDER);
}

void GameScene::showFire(const Point&pos,int localZOrder)
{
	auto entityLayer = this->getEntityLayer();
	
	m_pEffectLayer->showFire(pos,entityLayer,localZOrder);
}

Card* GameScene::makeCard(const std::string& name,CardType type)
{
	return m_pCardLayer->makeCard(name,type);
}

GameState GameScene::getGameState()const
{
	return m_gameState;
}

LevelCardType GameScene::getLevelCardShowType()const
{
	return m_pLevelLayer->getLevelCardShowType();
}

ZombieBase*GameScene::makeZombie(const string& zombieName,const Point&pos,int row,bool bConfused)
{
	auto zombie = m_pZombieLayer->makeZombie(zombieName,row);
	//设置属性
	zombie->setPosition(pos);
	zombie->setRow(row);
	zombie->setDelegate(this);
	//添加到场景中
	auto entityLayer = this->getEntityLayer();
	//设置z order
	int localZOrder = ZOMBIE_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(zombie,localZOrder);
	//僵尸是否迷惑
	if (bConfused)
		this->confuseZombie(zombie);

	return zombie;
}

bool GameScene::touchBeganOfPlayState(Touch*touch,SDL_Event*event)
{
	auto pos = touch->getLocation();
	bool bRet = false;
	m_bSwallowTouch = false;
	//是否点击了卡片层
	auto clickedCard = m_pCardLayer->getClickedCard(pos);

	if (clickedCard && clickedCard->isEnabled())
	{
		auto selectedCard = m_pCardLayer->getSelectedCard();
		//取消选中
		if (clickedCard == selectedCard)
		{
			m_pCardLayer->unselectedCard();
		}
		else//重新设置选中
		{
			m_pCardLayer->setSelectedCard(clickedCard);
		}
		bRet = true;
		m_bSwallowTouch = true;
		//与铲子互斥
		m_pPanelLayer->unselectShovel();
	}
	//点击了铲子
	else if (m_pPanelLayer->isClickShovel(pos))
	{
		//已经选中铲子，取消选中
		if (m_pPanelLayer->isSelectedShovel())
		{
			m_pPanelLayer->unselectShovel();
		}
		else
		{
			m_pPanelLayer->seletcShovel();
		}
		bRet = true;
		m_bSwallowTouch = true;
		//与卡片层互斥
		m_pCardLayer->unselectedCard();
	}

	return bRet;
}

void GameScene::touchMovedOfPlayState(Touch*touch,SDL_Event*event)
{
}

void GameScene::touchEndedOfPlayState(Touch*touch,SDL_Event*event)
{
	//拦截事件
	if (m_bSwallowTouch)
		return;

	auto pos = touch->getLocation();
	auto nodePos = m_pLevelLayer->convertToNodeSpace(pos);
	//是否点击了ProductLayer
	auto product = m_pProductLayer->getClickedProduct(pos);
	if (product)
	{
		product->setClicked(true);
		this->collectProduct(product);

		return;
	}
	//是否点击了某一个terrain
	auto terrain = m_pLevelLayer->getClickedTerrain(nodePos);
	//所有操作对要经过terrain
	if (terrain == nullptr)
		return;

	auto selectedCard = m_pCardLayer->getSelectedCard();
	//存在选中的卡片，则阳光足够，cd完成
	if (selectedCard)
	{
		bool bRet = false;
		//获取当前的关卡类型，来创建是植物还是僵尸
		auto levelType = m_pLevelLayer->getLevelCardShowType();
		
		if (levelType == LevelCardType::Plant)
			bRet = this->tryPlanting(selectedCard,terrain);
		else if (levelType == LevelCardType::Zombie)
			bRet = this->tryMakingZombie(selectedCard,terrain);
		//创建完成,则判断消耗了什么
		if (bRet)
		{
			auto cardType = selectedCard->getCardType();
			if (cardType == CardType::Common)
			{
				//减少阳光值
				this->subSun(selectedCard->getWorth());
				//取消点击
				m_pCardLayer->unselectedCard();
				//该卡片开始cd
				selectedCard->setCurCD(selectedCard->getCD());
			}
			else if (cardType == CardType::Consumable)
			{
				m_pCardLayer->removeCard(selectedCard);
			}
		}
	}//选中了铲子
	else if (m_pPanelLayer->isSelectedShovel())
	{
		//获取顶层植物
		auto topPlant = m_pLevelLayer->getTopPlantOfRemoval(terrain);
		
		if (topPlant != nullptr)
		{
			//获取顶层植物的容器
			auto vessel = topPlant->getLocatedCarrier();
			//该植物是保卫者，删除保卫者
			if (topPlant->getPlantType() == PlantType::Defender)
				vessel->clearDefender();
			else
				vessel->clearInnerPlant();
			//移除该植物
			this->removePlant(topPlant);
			//取消铲子的选中
			m_pPanelLayer->unselectShovel();
		}
	}
}

bool GameScene::touchBeganOfCardChooseState(Touch*touch,SDL_Event*event)
{
	auto pos = touch->getLocation();
	//是否点击了卡片选择界面中的某一卡片
	auto clickedCard = m_pCardChooseLayer->getClickedCard(pos);

	if (clickedCard != nullptr)
	{
		if (!m_pCardLayer->isFullOfCardSlot())
		{
			clickedCard->retain();
			//从CardChooseLayer移除卡片
			m_pCardChooseLayer->removeCard(clickedCard);
			//添加到卡片层
			m_pCardLayer->addCard(clickedCard);
			//移除
			clickedCard->release();
		}
		//如果到达卡槽上限 设置开始游戏按钮可用
		if (m_pCardLayer->isFullOfCardSlot())
			m_pCardChooseLayer->setStartBtnEnable(true);

		return true;
	}
	//是否点击了卡片层
	clickedCard = m_pCardLayer->getClickedCard(pos);

	if (clickedCard != nullptr)
	{
		clickedCard->retain();
		//从卡片层移除
		m_pCardLayer->removeCard(clickedCard);
		//添加到卡片选择层
		m_pCardChooseLayer->addCard(clickedCard);

		clickedCard->release();

		m_pCardChooseLayer->setStartBtnEnable(false);
	}

	return true;
}

void GameScene::touchMovedOfCardChooseState(Touch*touch,SDL_Event*evnet)
{
}

void GameScene::touchEndedOfCardChooseState(Touch*touch,SDL_Event*evnet)
{
}

void GameScene::clickCardChooseStartBtn()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveBy*move = MoveBy::create(0.5f,Point(0,-visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);
	//显示出卡片选择界面
	m_pCardChooseLayer->runAction(action);
	//开始游戏
	//获取当前的关卡状态
	auto levelType = m_pLevelLayer->getLevelCardShowType();

	this->levelStart(levelType);

	m_gameState = GameState::Play;
}

Terrain*GameScene::findTerrainOfZombieCollision(ZombieBase*zombie)
{
	//获取当前僵尸所在的行
	auto row = zombie->getRow();
	auto dir = zombie->getDir();
	auto r = zombie->getCollisionBoundingBox();

	const auto&terrains = m_pLevelLayer->getTerrainsOfRow(row);
	Terrain*terrain = nullptr;
	//地形从左向右遍历
	if (dir == Direction::Left)
	{
		for (auto it = terrains.begin();it != terrains.end();it++)
		{
			auto t = *it;
			auto rect = t->getBoundingBox();

			if (r.intersectRect(rect))
			{
				terrain = t;
				break;
			}
		}
	}
	//地形从右向左遍历
	else if (dir == Direction::Right)
	{
		for (auto it = terrains.end();it != terrains.begin();it--)
		{
			auto t = *it;
			auto rect = t->getBoundingBox();

			if (r.intersectRect(rect))
			{
				terrain = t;
				break;
			}
		}
	}

	return terrain;
}

vector<ZombieBase*> GameScene::getZombiesOfRow(int row)
{
	const auto&allZombies = m_pZombieLayer->getZombies();
	vector<ZombieBase*> zombies;

	for (auto mapIter = allZombies.begin();mapIter != allZombies.end();mapIter++)
	{
		auto curRow = mapIter->first;
		auto &lineZombies = mapIter->second;

		if (row == curRow)
		{
			return lineZombies;
		}
		else if (row == -1)
		{
			copy(lineZombies.begin(),lineZombies.end(),back_inserter(zombies));
		}
	}
	return zombies;
}

ActiveTime GameScene::getCurActiveTime()const
{
	return m_pLevelLayer->getCurActiveTime();
}