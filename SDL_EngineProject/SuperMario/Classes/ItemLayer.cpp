#include "ItemLayer.h"
#include "BehaviorManager.h"
#include "Player.h"
#include "MoveBehavior.h"

ItemLayer::ItemLayer()
	:m_pDelegate(nullptr)
{
}
ItemLayer::~ItemLayer()
{
}
bool ItemLayer::init()
{
	return true;
}
void ItemLayer::update(float dt)
{
	for(auto iter = m_items.begin();iter != m_items.end();)
	{
		auto item = *iter;
		if(this->isObsolete(item))
		{
			iter = m_items.erase(iter);
			this->pushItemToPool(item);
		}
		else if(item->isUpdate())
		{
			item->performMove(dt);
			iter++;
		}
		else
			iter++;
	}
}
bool ItemLayer::produceItemByType(TMXObject*object)
{
	bool bRet = true;
	if(object->name != "coin")
	{
		bRet = this->createCommonItem(object);
	}
	//砖块内的金币和别的道具有所不同，它是由tile驱动的，tile受到有效碰撞后，就会传递给tileCoin对象
	else if(object->name == "coin")
	{
		bRet = this->createTileCoinItem(object);
	}
	return bRet;
}
void ItemLayer::setDelegate(ItemLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
vector<Item*> &ItemLayer::getItems()
{
	return m_items;
}
//private
bool ItemLayer::isObsolete(Item*item)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Rect r = item->getCollisionBoundingBox();

	return item->isDead()
		|| r.origin.y > visibleSize.height;
}
Item*ItemLayer::popAvaiableItemFromPool()
{
	Item*item = nullptr;
	//道具池为空，重新创建
	if(m_itemPool.empty())
	{
		TMXLayer*entityLayer = m_pDelegate->getEntityLayer();
		item = Item::create();
		entityLayer->addChild(item);
	}
	else//剩余的对象
	{
		auto iter = m_itemPool.begin();
		item = *iter;
		m_itemPool.erase(iter);
	}
	item->setCurHp(1);
	item->setMaxHp(1);
	item->setDead(false);
	item->setUpdate(false);

	return item;
}
template<typename T>
T ItemLayer::popAvaiableItemFromPool(ItemType type)
{
	Item*item = nullptr;
	//查找是否有对应类型的对象
	auto iter = std::find_if(m_itemPool.begin(),m_itemPool.end(),[&](Item*it)
	{
		return type == it->getItemType();
	});
	//没有查找到,则直接新建
	if(iter == m_itemPool.end())
	{
		TMXLayer*entityLayer = m_pDelegate->getEntityLayer();
		
		switch(type)
		{
		case kItemType_Star://如果是星星
			item = Star::create();break;
		case kItemType_TileCoin:
			item = TileCoin::create();break;
		default:
			item = Item::create();
		}
		entityLayer->addChild(item);
	}
	else//找到可用则返回
	{
		item = *iter;
		iter = m_itemPool.erase(iter);
	}
	item->setCurHp(1);
	item->setMaxHp(1);
	item->setDead(false);
	item->setUpdate(false);

	return static_cast<T>(item);
}
void ItemLayer::pushItemToPool(Item*item)
{
	//对道具进行重置
	item->reset();
	item->setVisible(false);
	m_itemPool.push_back(item);
}
bool ItemLayer::createCommonItem(TMXObject*object)
{
	Item*item = nullptr;
	MoveBehavior*moveBehavior = nullptr;
	EffectBehavior*effectBehavior = nullptr;
	Point velocity;
	//要播放的音效文件
	string effect;
	auto behaviorManager = BehaviorManager::getInstance();
	//创建成长道具
	if(object->name == "mushroom")
	{
		item = this->popAvaiableItemFromPool<Item*>(kItemType_Mushroom);
		//获取当前mario需要的道具类型 todo
		auto growingItemType = m_pDelegate->getPlayer()->getGrowingItemType();
		item->setItemType(growingItemType);
		if(growingItemType == kItemType_Mushroom)
		{
			item->bindSprite(Sprite::createWithSpriteFrameName("item0.png"));
			moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithTileCollidedAndCanDropType);
			velocity = Point(3.f,0);
		}
		else if(growingItemType == kItemType_Flower)
		{
			item->bindSprite(Sprite::createWithSpriteFrameName("item1_00.png"));
		}
		effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerLevelUpEffectType);
		//播放声音
		effect = "sound/item_present.ogg";
	}
	else if(object->name == "star")
	{
		item = this->popAvaiableItemFromPool<Star*>(kItemType_Star);
		item->setItemType(kItemType_Star);
		velocity = Point(-2.f,2.f);
		//设置行为
		moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithoutGravityType);
		effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerCanHurtEnemyEffectType);
	}
	else if(object->name == "up-mushroom")
	{
		item = this->popAvaiableItemFromPool<Item*>(kItemType_Mushroom);
		item->bindSprite(Sprite::createWithSpriteFrameName("item3.png"));
		//不更改item
		//设置行为
		moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithTileCollidedAndCanDropType);
		effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerLifeUpEffectType);
		velocity = Point(2.f,0);
	}
	//设置各种属性
	item->setVelocity(velocity);
	item->runNormalAnimation();
	item->setMoveBehavior(moveBehavior);
	item->setEffectBehavior(effectBehavior);
	//设置位置
	item->setPosition(object->x+object->width/2,object->y+object->height/2);
	item->setVisible(true);
	//设置道具从砖块中出现的动作
	MoveBy*move = MoveBy::create(.5f,Point(0,-object->height));
	//开始移动行为
	CallFunc*end = CallFunc::create([item](){
		item->setUpdate(true);
	});
	item->runAction(Sequence::createWithTwoActions(move,end));
	//把对象放入刷新池
	m_items.push_back(item);
	//播放音效
	SoundManager::getInstance()->playEffect(effect,0);
	return true;
}
bool ItemLayer::createTileCoinItem(TMXObject*object)
{
	TileCoin*tileCoin = nullptr;
	//判断是否已经有TileCoin对象和object联结
	auto iter = std::find_if(m_items.begin(),m_items.end(),[object](Item*item)
	{
		return item->getItemType() == kItemType_TileCoin &&
			static_cast<TileCoin*>(item)->getTMXObject() == object;
	});
	//没找到对应的item 新建
	if(iter == m_items.end())
	{
		//获取可用的TileCoin
		tileCoin = this->popAvaiableItemFromPool<TileCoin*>(kItemType_TileCoin);
		tileCoin->associateWithTMXObject(object);
		tileCoin->setPosition(object->x+object->width/2,object->y+object->height/2);
		tileCoin->setUpdate(true);

		tileCoin->setItemType(kItemType_TileCoin);
		//添加效果行为
		auto effectBehavior = BehaviorManager::getInstance()->getEffectBehaviorByType(kPlayerAddCoinEffectType);
		tileCoin->setEffectBehavior(effectBehavior);

		m_items.push_back(tileCoin);
	}
	else
		tileCoin = static_cast<TileCoin*>(*iter);
	//有点破坏结构
	tileCoin->performEffect(m_pDelegate->getPlayer());
	SoundManager::getInstance()->playEffect("sound/get_gold.ogg",0);
	tileCoin->hurt(1);
	if(tileCoin->isDying())
		return true;
	return false;
}
/*Item*ItemLayer::createMushroom()
{
	MoveBehavior*moveBehavior = nullptr;
	EffectBehavior*effectBehavior = nullptr;
	auto behaviorManager = BehaviorManager::getInstance();
	Item*item = nullptr;

	auto itemType = m_pDelegate->getPlayer()->getGrowingItemType();
	//获取可用的对象
	item = this->popAvaiableItemFromPool();
	item->setItemType(itemType);

	if(itemType == kItemType_Flower)
	{
		item->bindSprite(Sprite::createWithSpriteFrameName("item1_00.png"));
		//运行动画
		auto animate = Entity::createAnimate("item1_%02d.png",0,1,1.f);
		item->getSprite()->runAction(animate);
	}
	else
	{
		//设置精灵
		item->bindSprite(Sprite::createWithSpriteFrameName("item0.png"));
		//设置各种行为
		moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithTileCollidedAndCanDropType);
	}
	effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerLevelUpEffectType);

	item->setMoveBehavior(moveBehavior);
	item->setEffectBehavior(effectBehavior);

	return item;
}
Item*ItemLayer::createStar()
{
	Star*item = nullptr;
	MoveBehavior*moveBehavior = nullptr;
	EffectBehavior*effectBehavior = nullptr;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//行为管理器
	auto behaviorManager = BehaviorManager::getInstance();

	//获取可用的item
	item = this->popAvaiableItemFromPool<Star*>(kItemType_Star);
	item->setItemType(kItemType_Star);
	//设置帧图和动画
	item->bindSprite(Sprite::createWithSpriteFrameName("item4_00.png"));
	Animate*animate = Entity::createAnimate("item4_%02d.png",0,3,0.4f);
	item->getSprite()->runAction(animate);

	moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithoutGravityType);
	effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerCanHurtEnemyEffectType);
	//设置行为
	item->setMoveBehavior(moveBehavior);
	item->setEffectBehavior(effectBehavior);

	return item;
}
TileCoin*ItemLayer::createCoin(TMXObject*object)
{
	//获取可用的TileCoin
	TileCoin*coin = this->popAvaiableItemFromPool<TileCoin*>(kItemType_TileCoin);
	//设置各种行为
	coin->associateWithTMXObject(object);

	coin->setItemType(kItemType_TileCoin);
	//添加效果行为
	auto effectBehavior = BehaviorManager::getInstance()->getEffectBehaviorByType(kPlayerAddCoinEffectType);
	coin->setEffectBehavior(effectBehavior);

	return coin;
}*/