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
	//�ؿ��� todo
	m_pLevelLayer = LevelLayer::create("level/level3-1.tmx");
	m_pLevelLayer->setDelegate(this);
	m_pLevelLayer->setPosition(Point(-100.f,0.f));
	this->addChild(m_pLevelLayer);
	//ֲ���
	m_pPlantLayer = PlantLayer::create();
	m_pPlantLayer->setDelegate(this);
	this->addChild(m_pPlantLayer);
	//��ʬ��
	m_pZombieLayer = ZombieLayer::create();
	m_pZombieLayer->setDelegate(this);
	this->addChild(m_pZombieLayer);
	//�ӵ���
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//��Ч��
	m_pEffectLayer = EffectLayer::create();
	this->addChild(m_pEffectLayer);
	//��Ƭѡ���
	m_pCardChooseLayer = CardChooseLayer::create();
	m_pCardChooseLayer->setPosition(0.f,-visibleSize.height);
	m_pCardChooseLayer->setDelegate(this);

	this->addChild(m_pCardChooseLayer);
	//��Ƭ��
	m_pCardLayer = CardLayer::create();
	this->addChild(m_pCardLayer);
	//�������
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//��Ʒ��
	m_pProductLayer = ProductLayer::create();
	this->addChild(m_pProductLayer);
	//ˢ�����
	m_pPanelLayer->updateUI();
	//����һЩ��ʼ��
	auto initialSun = m_pLevelLayer->getInitialSun();
	//�������ֵ
	this->addSun(initialSun);
	//���ݵ�ǰ�ؿ����;����Ƿ�����ƶ�
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
	//����ͼƬ��Դ
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
	//��ȡ��ǰ�Ĺؿ�״̬
	auto levelType = m_pLevelLayer->getLevelCardShowType();
	//�����ƶ���֮��ص�����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto size = m_pLevelLayer->getContentSize();
	//��ǰ��ֲ��������ƶ������ֿ�Ƭ
	if (levelType == LevelCardType::Plant)
	{
		auto move = MoveTo::create(3.f,visibleSize.width - size.width);
		CallFunc*end = CallFunc::create([this,levelType]()
		{
			this->loadCard(levelType);
		});
		auto seq = Sequence::createWithTwoActions(move,end);
		m_pLevelLayer->runAction(seq);
	}//��ǰ�ǽ�ʬ��ֱ�ӿ�ʼ��Ϸ
	else if (levelType == LevelCardType::Zombie)
	{
		this->loadCard(levelType);
	}
}

void GameScene::loadCard(LevelCardType levelType)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ��ǰ����Ŀ�Ϳ�����Ŀ
	auto cardSlotNum = DynamicData::getInstance()->getCardVesselNum();
	vector<string> ownCards;
	//���ÿ��۸���
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
	//����ʾ��Ƭѡ�����
	if (ownCards.size() <= cardSlotNum)
	{
		//��ӿ�Ƭ
		for (unsigned int i = 0;i < ownCards.size();i++)
		{
			//��ӿ�Ƭ����Ƭ��
			m_pCardLayer->addCard(ownCards.at(i),CardType::Common);
		}
		this->levelStart(levelType);
		//���õ�ǰ״̬Ϊ playing
		m_gameState = GameState::Play;
	}
	else//��ʾ��Ƭѡ�����
	{
		m_gameState = GameState::CardChoose;

		MoveBy*move = MoveBy::create(0.5f,Point(0,visibleSize.height));
		EaseExponentialOut*action = EaseExponentialOut::create(move);
		//��ʾ����Ƭѡ�����
		m_pCardChooseLayer->runAction(action);
		//չʾ����Ƭ
		m_pCardChooseLayer->show(ownCards);
		//���ÿ�ʼ��Ϸ����ʹ��
		bool enable = m_pCardLayer->isFullOfCardSlot();
		m_pCardChooseLayer->setStartBtnEnable(enable);
	}
}

void GameScene::levelStart(LevelCardType levelType)
{
	if (levelType == LevelCardType::Plant)
	{
		//��ͷ�����ת��֮��ʼ��Ϸ
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

	//���ж����Ľ���
	auto &groups = m_pLevelLayer->getEntityObjects();
	vector<Card*> cards;

	for (const auto&value : groups)
	{
		const auto& object = value.asValueMap();

		auto type = object.at("type").asString();
		auto name = object.at("name").asString();
		float x = (float)object.at("x").asInt();
		float y = (float)object.at("y").asInt();
		//��ȡ��Ӧ��terrain
		auto terrain = m_pLevelLayer->getClickedTerrain(Point(x,y));
		//���ɵ�ֲ��Ҳ�÷��ϵ���
		if (type == "plant")
		{
			Card*card = nullptr;
			//�Ƚ��п�Ƭ����
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
	//�����Ƭ����
	cards.clear();
	//����δ��ʹ�õĿ���
	m_pCardLayer->hideUnusedCardSlot();
	//���ý�ʬ����·��
	m_pZombieLayer->setZombiePaths(m_pLevelLayer->getZombiePaths());
}

void GameScene::collectProduct(Product*product)
{
	//�����̫��
	if (product->getProductType() == ProductType::Sun)
	{
		//��ȡ����λ��
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
		//���ж���
		product->stopAllActions();
		product->runAction(seq);
	}
}

bool GameScene::tryPlanting(Card*card,Terrain*terrain)
{
	Plant*newPlant = nullptr;
	auto topPlant = m_pLevelLayer->getTopPlant(terrain);
	//�ÿ�Ƭ�ǿ��ȶ� �ϲ�ֲ����ҹ��ֲ�ﲢ��δ���Ѳ���ֲ
	if (card->getCardName() == "CoffeeBean"
		&& topPlant != nullptr && topPlant->getPlantType() == PlantType::NightPlant)
	{
		bool bRet = this->tryEatingCoffeeBean(static_cast<NightPlant*>(topPlant));
		
		return bRet;
	}
	//��ȡ��Ҫ��Ʒ
	auto necessaryItem = card->getNecessoryItem();
	//����ֲ��
	if (!necessaryItem.empty() && topPlant != nullptr
		&& topPlant->getPlantName() == necessaryItem)
	{
		newPlant = this->upgradePlant(card,topPlant);
	}
	//��ֲ������
	if (StaticData::getInstance()->getPlantCsvStructForName(card->getCardName())->type == PlantType::Defender)
	{
		newPlant = this->plantDefender(card,terrain);
	}
	//��ֲֲ��
	else if (necessaryItem.empty())
	{
		newPlant = this->planting(card,terrain,topPlant);
	}
	//���û�������
	if (newPlant != nullptr)
	{
		newPlant->setActiveTime(card->getActiveTime());
		newPlant->setDelegate(this);
		//ȷ��ֲ���Ƿ��������ö�Ӧ�ķ���
		this->judgeActivationForPlant(newPlant);
		//��ӵ�entity layer ����
		auto entityLayer = this->getEntityLayer();
		int localZOrder = m_pLevelLayer->getSumOfZOrderPlant(terrain,newPlant);
		//���ݵ�ǰ��������z order
		localZOrder += terrain->getRow() * Z_ORDER_INTERVAL;

		entityLayer->addChild(newPlant,localZOrder);
	}

	return newPlant != nullptr;
}

Plant*GameScene::planting(Card*card,Terrain*terrain,Plant*topPlant)
{
	Plant*newPlant = nullptr;
	Point newPos;
	//�����ϵ�ֲ��Ϊ�� ���η��� ��������û���ƻ����򴴽�
	if (topPlant == nullptr && card->isIncludeTerrain(terrain->getTerrainType())
		&& !terrain->isDestroyed())
	{
		newPlant = m_pPlantLayer->makePlant(card->getCardName());
		newPlant->setLocatedCarrier(terrain);
		//������һЩ��������
		newPos = terrain->getPosition();
		//����Ǳ�����
/*		if (newPlant->getPlantType() == PlantType::Defender 
			&& terrain->getDefender() == nullptr)
		{
			terrain->setDefender(static_cast<Defender*>(newPlant));
		}
		else//��ͨ��ֲ��*/
		{
			terrain->setInnerPlant(newPlant);
		}
		//��ֲ��������ֲ������ڲ���carrier��row
		if (newPlant->getPlantType() == PlantType::Vessel)
		{
			static_cast<VesselPlant*>(newPlant)->setRow(terrain->getRow());
		}
	}
	//��������ֲ��,�����ж�
	else if(topPlant != nullptr && topPlant->getPlantType() == PlantType::Vessel)
	{
		auto height = topPlant->getContentSize().height;

		auto vessel = static_cast<VesselPlant*>(topPlant)->getInnerCarrier();
		auto offsetPos = Point(0.f,-height/2.f);

		if (card->isIncludeTerrain(vessel->getTerrainType()))
		{
			newPlant = m_pPlantLayer->makePlant(card->getCardName());
			//������һЩ��������
			newPos = topPlant->getPosition() + offsetPos;

			vessel->setInnerPlant(newPlant);
			newPlant->setVesselPlant(topPlant);
			newPlant->setLocatedCarrier(vessel);
		}

	}//end else if
	//����λ��
	if (newPlant != nullptr)
		newPlant->setPosition(newPos);

	return newPlant;
}

Plant* GameScene::plantDefender(Card*card,Terrain*terrain)
{
	Defender*defender = nullptr;
	auto innerPlant = terrain->getInnerPlant();
	Point newPos = terrain->getPosition();
	//�������ϵ���
	if (card->isIncludeTerrain(terrain->getTerrainType()))
	{
		//������û�б����� �ͽ��д���
		if (terrain->getDefender() == nullptr)
		{
			defender = static_cast<Defender*>(m_pPlantLayer->makePlant(card->getCardName()));

			terrain->setDefender(defender);
			defender->setLocatedCarrier(terrain);
		}
		else//�Ѿ����˱�����
		{
			//TODO
		}
	}
	//�����ڲ�����ֲ��
	else if (innerPlant != nullptr 
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto vesselPlant = static_cast<VesselPlant*>(innerPlant);
		auto carrier = vesselPlant->getInnerCarrier();
		//���η���
		if (card->isIncludeTerrain(carrier->getTerrainType()))
		{
			//���ñ�����
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
	//������ֲ��
	Plant*newPlant = m_pPlantLayer->makePlant(card->getCardName());
	//��ȡλ��
	Point newPos = topPlant->getPosition();;
	Carrier*carrier = topPlant->getLocatedCarrier();
	//��������
	newPlant->setVesselPlant(topPlant->getVesselPlant());
	newPlant->setLocatedCarrier(carrier);
	//����λ��
	newPlant->setPosition(newPos);

	carrier->setInnerPlant(newPlant);
	//�Ƴ���ֲ��
	this->removePlant(topPlant);

	return newPlant;
}

bool GameScene::tryEatingCoffeeBean(NightPlant*plant)
{
	//�����ֲ���Ѿ����ѣ��򷵻�false
	if (!plant->isSleeping())
		return false;
	//TODO
	if (plant->getActionByTag(1) != nullptr)
		return false;
	//����ҹ��ֲ��
	auto size = plant->getContentSize();
	auto pos = plant->getPosition() - Point(0,size.height/2.f);
	float duration = this->showCoffeeBeanEatAction(pos);
	//���ж������ڶ�����ɺ�ֲ�ﱻ����
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
	//��ȡ�ؿ���Ӧ������
	int row = terrain->getRow();
	//��ȡ��Ӧ��·��
	const auto path = m_pLevelLayer->getZombiePathOfRow(row);
	//���ɽ�ʬ
	auto zombie = m_pZombieLayer->makeZombie(card->getCardName(),row);
	//����λ��
	auto pos = terrain->getPosition();

	auto terrainSize = terrain->getContentSize();
	auto zombieSize = zombie->getContentSize();

	pos.y -= (zombieSize.height - terrainSize.height)/2.f;

	zombie->setPosition(pos);
	zombie->setRow(row);
	zombie->setDelegate(this);
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	//����z order
	int localZOrder = ZOMBIE_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(zombie,localZOrder);
	
	bRet = true;
	return bRet;
}

void GameScene::judgeActivationForPlant(Plant*plant)
{
	//ҹ��ֲ����Ҫ�жϵ�ǰ�����Ƿ���ҹ��
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
	//��ȡ��Ʒ����
	auto garnishryName = garnishry->getGarnishryName();
	//��Ӧ�ľ�������
	string spriteFilename;
	//��ȡ���˵�
	int index = 0;
	//����Ѫ��С��0
	if (garnishry->getHitPoint() > 0)
	{
		index = garnishry->getMaxHitPoint() / garnishry->getHitPoint();
	}
	index += 1;

	spriteFilename = StringUtils::format(garnishry_sprite_format.c_str(),garnishryName.c_str(),index);
	//���ؾ����ļ���
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
	//���浱ǰ��zombie
	zombie->retain();
	//�Ƴ��ý�ʬ
	m_pZombieLayer->removeZombie(zombie,false);
	//���ý�ʬ����ɫ
	zombie->getSprite()->setColorMod(Color3B(0,0,0xff));
	//ǿ��ʹ��ʬ�ķ����Ϊ����
	zombie->setDir(Direction::Right);
	//����Ϊ�Ի�״̬
	zombie->setConfused(true);
	//��ӵ�ָ������
	m_pPlantLayer->addItemToMovablePlants(zombie);
	//�ͷŸý�ʬ������
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
	//�ҵ�������ײ�Ľ�ʬ
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
	//���ֶ�Ӧ�Ľ�ʬ
	auto zombies = this->getZombiesOfRow(-1);
	//�ҵ���ײ�Ĳ��Ҵ�����Ʒ�Ľ�ʬ
	for (const auto& zombie : zombies)
	{
		auto zombieRect = zombie->getCollisionBoundingBox();
		//����ײ�Ľ�ʬ���
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
	//��������
	for (auto bullet : bullets)
	{
		auto r = bullet->getCollisionBoundingBox();
		//��ǰ������ͬ �������㶹�� ����������ײ�����ҿ��Խ���ת��
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
	//���û�������
	bullet->setRow(row);
	//bullet->setDamage(damage);
	bullet->setPosition(startPos);
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	//����z order
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(bullet,localZOrder);
	//����λ��
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
	//��ӵ�������
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
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(bullet,localZOrder);
	//���ö���
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
	//��������
	if (isButter)
	{
		bullet->setAttackType(AttackType::TrackAndButter);
		bullet->setDuration(4.f);
	}
	else
	{
		bullet->setAttackType(AttackType::Track);
	}
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;
	
	entityLayer->addChild(bullet,localZOrder);
	//���ö���
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
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	int localZOrder = BULLET_Z_ORDER + row * Z_ORDER_INTERVAL;
	
	entityLayer->addChild(bullet,localZOrder);
}

void GameScene::addShroomBullet(int damage,int row,const Point &startPos,float atkScope)
{
	auto bullet = m_pBulletLayer->addShroomBullet();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point deltaPos;
	//ȷ������λ��
	if (atkScope < 0.f)
	{
		deltaPos.x = visibleSize.width - startPos.x;
		deltaPos = m_pLevelLayer->convertToNodeSpace(deltaPos);
	}
	else
	{
		deltaPos.x = atkScope;
	}
	//���ö���
	auto seq = BulletLayer::lineRoute(bullet,deltaPos,300.f,true);
	bullet->runAction(seq);

	bullet->setRow(row);
	bullet->setDamage(damage);
	bullet->setPosition(startPos);
	//��ӵ�������
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
	//��������
	zombie->setPosition(pos);
	zombie->setRow(row);
	zombie->setDelegate(this);
	//��ӵ�������
	auto entityLayer = this->getEntityLayer();
	//����z order
	int localZOrder = ZOMBIE_Z_ORDER + row * Z_ORDER_INTERVAL;

	entityLayer->addChild(zombie,localZOrder);
	//��ʬ�Ƿ��Ի�
	if (bConfused)
		this->confuseZombie(zombie);

	return zombie;
}

bool GameScene::touchBeganOfPlayState(Touch*touch,SDL_Event*event)
{
	auto pos = touch->getLocation();
	bool bRet = false;
	m_bSwallowTouch = false;
	//�Ƿ����˿�Ƭ��
	auto clickedCard = m_pCardLayer->getClickedCard(pos);

	if (clickedCard && clickedCard->isEnabled())
	{
		auto selectedCard = m_pCardLayer->getSelectedCard();
		//ȡ��ѡ��
		if (clickedCard == selectedCard)
		{
			m_pCardLayer->unselectedCard();
		}
		else//��������ѡ��
		{
			m_pCardLayer->setSelectedCard(clickedCard);
		}
		bRet = true;
		m_bSwallowTouch = true;
		//����ӻ���
		m_pPanelLayer->unselectShovel();
	}
	//����˲���
	else if (m_pPanelLayer->isClickShovel(pos))
	{
		//�Ѿ�ѡ�в��ӣ�ȡ��ѡ��
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
		//�뿨Ƭ�㻥��
		m_pCardLayer->unselectedCard();
	}

	return bRet;
}

void GameScene::touchMovedOfPlayState(Touch*touch,SDL_Event*event)
{
}

void GameScene::touchEndedOfPlayState(Touch*touch,SDL_Event*event)
{
	//�����¼�
	if (m_bSwallowTouch)
		return;

	auto pos = touch->getLocation();
	auto nodePos = m_pLevelLayer->convertToNodeSpace(pos);
	//�Ƿ�����ProductLayer
	auto product = m_pProductLayer->getClickedProduct(pos);
	if (product)
	{
		product->setClicked(true);
		this->collectProduct(product);

		return;
	}
	//�Ƿ�����ĳһ��terrain
	auto terrain = m_pLevelLayer->getClickedTerrain(nodePos);
	//���в�����Ҫ����terrain
	if (terrain == nullptr)
		return;

	auto selectedCard = m_pCardLayer->getSelectedCard();
	//����ѡ�еĿ�Ƭ���������㹻��cd���
	if (selectedCard)
	{
		bool bRet = false;
		//��ȡ��ǰ�Ĺؿ����ͣ���������ֲ�ﻹ�ǽ�ʬ
		auto levelType = m_pLevelLayer->getLevelCardShowType();
		
		if (levelType == LevelCardType::Plant)
			bRet = this->tryPlanting(selectedCard,terrain);
		else if (levelType == LevelCardType::Zombie)
			bRet = this->tryMakingZombie(selectedCard,terrain);
		//�������,���ж�������ʲô
		if (bRet)
		{
			auto cardType = selectedCard->getCardType();
			if (cardType == CardType::Common)
			{
				//��������ֵ
				this->subSun(selectedCard->getWorth());
				//ȡ�����
				m_pCardLayer->unselectedCard();
				//�ÿ�Ƭ��ʼcd
				selectedCard->setCurCD(selectedCard->getCD());
			}
			else if (cardType == CardType::Consumable)
			{
				m_pCardLayer->removeCard(selectedCard);
			}
		}
	}//ѡ���˲���
	else if (m_pPanelLayer->isSelectedShovel())
	{
		//��ȡ����ֲ��
		auto topPlant = m_pLevelLayer->getTopPlantOfRemoval(terrain);
		
		if (topPlant != nullptr)
		{
			//��ȡ����ֲ�������
			auto vessel = topPlant->getLocatedCarrier();
			//��ֲ���Ǳ����ߣ�ɾ��������
			if (topPlant->getPlantType() == PlantType::Defender)
				vessel->clearDefender();
			else
				vessel->clearInnerPlant();
			//�Ƴ���ֲ��
			this->removePlant(topPlant);
			//ȡ�����ӵ�ѡ��
			m_pPanelLayer->unselectShovel();
		}
	}
}

bool GameScene::touchBeganOfCardChooseState(Touch*touch,SDL_Event*event)
{
	auto pos = touch->getLocation();
	//�Ƿ����˿�Ƭѡ������е�ĳһ��Ƭ
	auto clickedCard = m_pCardChooseLayer->getClickedCard(pos);

	if (clickedCard != nullptr)
	{
		if (!m_pCardLayer->isFullOfCardSlot())
		{
			clickedCard->retain();
			//��CardChooseLayer�Ƴ���Ƭ
			m_pCardChooseLayer->removeCard(clickedCard);
			//��ӵ���Ƭ��
			m_pCardLayer->addCard(clickedCard);
			//�Ƴ�
			clickedCard->release();
		}
		//������￨������ ���ÿ�ʼ��Ϸ��ť����
		if (m_pCardLayer->isFullOfCardSlot())
			m_pCardChooseLayer->setStartBtnEnable(true);

		return true;
	}
	//�Ƿ����˿�Ƭ��
	clickedCard = m_pCardLayer->getClickedCard(pos);

	if (clickedCard != nullptr)
	{
		clickedCard->retain();
		//�ӿ�Ƭ���Ƴ�
		m_pCardLayer->removeCard(clickedCard);
		//��ӵ���Ƭѡ���
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
	//��ʾ����Ƭѡ�����
	m_pCardChooseLayer->runAction(action);
	//��ʼ��Ϸ
	//��ȡ��ǰ�Ĺؿ�״̬
	auto levelType = m_pLevelLayer->getLevelCardShowType();

	this->levelStart(levelType);

	m_gameState = GameState::Play;
}

Terrain*GameScene::findTerrainOfZombieCollision(ZombieBase*zombie)
{
	//��ȡ��ǰ��ʬ���ڵ���
	auto row = zombie->getRow();
	auto dir = zombie->getDir();
	auto r = zombie->getCollisionBoundingBox();

	const auto&terrains = m_pLevelLayer->getTerrainsOfRow(row);
	Terrain*terrain = nullptr;
	//���δ������ұ���
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
	//���δ����������
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