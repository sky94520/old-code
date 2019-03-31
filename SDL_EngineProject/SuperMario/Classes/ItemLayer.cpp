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
	//ש���ڵĽ�Һͱ�ĵ���������ͬ��������tile�����ģ�tile�ܵ���Ч��ײ�󣬾ͻᴫ�ݸ�tileCoin����
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
	//���߳�Ϊ�գ����´���
	if(m_itemPool.empty())
	{
		TMXLayer*entityLayer = m_pDelegate->getEntityLayer();
		item = Item::create();
		entityLayer->addChild(item);
	}
	else//ʣ��Ķ���
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
	//�����Ƿ��ж�Ӧ���͵Ķ���
	auto iter = std::find_if(m_itemPool.begin(),m_itemPool.end(),[&](Item*it)
	{
		return type == it->getItemType();
	});
	//û�в��ҵ�,��ֱ���½�
	if(iter == m_itemPool.end())
	{
		TMXLayer*entityLayer = m_pDelegate->getEntityLayer();
		
		switch(type)
		{
		case kItemType_Star://���������
			item = Star::create();break;
		case kItemType_TileCoin:
			item = TileCoin::create();break;
		default:
			item = Item::create();
		}
		entityLayer->addChild(item);
	}
	else//�ҵ������򷵻�
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
	//�Ե��߽�������
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
	//Ҫ���ŵ���Ч�ļ�
	string effect;
	auto behaviorManager = BehaviorManager::getInstance();
	//�����ɳ�����
	if(object->name == "mushroom")
	{
		item = this->popAvaiableItemFromPool<Item*>(kItemType_Mushroom);
		//��ȡ��ǰmario��Ҫ�ĵ������� todo
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
		//��������
		effect = "sound/item_present.ogg";
	}
	else if(object->name == "star")
	{
		item = this->popAvaiableItemFromPool<Star*>(kItemType_Star);
		item->setItemType(kItemType_Star);
		velocity = Point(-2.f,2.f);
		//������Ϊ
		moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithoutGravityType);
		effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerCanHurtEnemyEffectType);
	}
	else if(object->name == "up-mushroom")
	{
		item = this->popAvaiableItemFromPool<Item*>(kItemType_Mushroom);
		item->bindSprite(Sprite::createWithSpriteFrameName("item3.png"));
		//������item
		//������Ϊ
		moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithTileCollidedAndCanDropType);
		effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerLifeUpEffectType);
		velocity = Point(2.f,0);
	}
	//���ø�������
	item->setVelocity(velocity);
	item->runNormalAnimation();
	item->setMoveBehavior(moveBehavior);
	item->setEffectBehavior(effectBehavior);
	//����λ��
	item->setPosition(object->x+object->width/2,object->y+object->height/2);
	item->setVisible(true);
	//���õ��ߴ�ש���г��ֵĶ���
	MoveBy*move = MoveBy::create(.5f,Point(0,-object->height));
	//��ʼ�ƶ���Ϊ
	CallFunc*end = CallFunc::create([item](){
		item->setUpdate(true);
	});
	item->runAction(Sequence::createWithTwoActions(move,end));
	//�Ѷ������ˢ�³�
	m_items.push_back(item);
	//������Ч
	SoundManager::getInstance()->playEffect(effect,0);
	return true;
}
bool ItemLayer::createTileCoinItem(TMXObject*object)
{
	TileCoin*tileCoin = nullptr;
	//�ж��Ƿ��Ѿ���TileCoin�����object����
	auto iter = std::find_if(m_items.begin(),m_items.end(),[object](Item*item)
	{
		return item->getItemType() == kItemType_TileCoin &&
			static_cast<TileCoin*>(item)->getTMXObject() == object;
	});
	//û�ҵ���Ӧ��item �½�
	if(iter == m_items.end())
	{
		//��ȡ���õ�TileCoin
		tileCoin = this->popAvaiableItemFromPool<TileCoin*>(kItemType_TileCoin);
		tileCoin->associateWithTMXObject(object);
		tileCoin->setPosition(object->x+object->width/2,object->y+object->height/2);
		tileCoin->setUpdate(true);

		tileCoin->setItemType(kItemType_TileCoin);
		//���Ч����Ϊ
		auto effectBehavior = BehaviorManager::getInstance()->getEffectBehaviorByType(kPlayerAddCoinEffectType);
		tileCoin->setEffectBehavior(effectBehavior);

		m_items.push_back(tileCoin);
	}
	else
		tileCoin = static_cast<TileCoin*>(*iter);
	//�е��ƻ��ṹ
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
	//��ȡ���õĶ���
	item = this->popAvaiableItemFromPool();
	item->setItemType(itemType);

	if(itemType == kItemType_Flower)
	{
		item->bindSprite(Sprite::createWithSpriteFrameName("item1_00.png"));
		//���ж���
		auto animate = Entity::createAnimate("item1_%02d.png",0,1,1.f);
		item->getSprite()->runAction(animate);
	}
	else
	{
		//���þ���
		item->bindSprite(Sprite::createWithSpriteFrameName("item0.png"));
		//���ø�����Ϊ
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
	//��Ϊ������
	auto behaviorManager = BehaviorManager::getInstance();

	//��ȡ���õ�item
	item = this->popAvaiableItemFromPool<Star*>(kItemType_Star);
	item->setItemType(kItemType_Star);
	//����֡ͼ�Ͷ���
	item->bindSprite(Sprite::createWithSpriteFrameName("item4_00.png"));
	Animate*animate = Entity::createAnimate("item4_%02d.png",0,3,0.4f);
	item->getSprite()->runAction(animate);

	moveBehavior = behaviorManager->getMoveBehaviorByType(kMoveWithoutGravityType);
	effectBehavior = behaviorManager->getEffectBehaviorByType(kPlayerCanHurtEnemyEffectType);
	//������Ϊ
	item->setMoveBehavior(moveBehavior);
	item->setEffectBehavior(effectBehavior);

	return item;
}
TileCoin*ItemLayer::createCoin(TMXObject*object)
{
	//��ȡ���õ�TileCoin
	TileCoin*coin = this->popAvaiableItemFromPool<TileCoin*>(kItemType_TileCoin);
	//���ø�����Ϊ
	coin->associateWithTMXObject(object);

	coin->setItemType(kItemType_TileCoin);
	//���Ч����Ϊ
	auto effectBehavior = BehaviorManager::getInstance()->getEffectBehaviorByType(kPlayerAddCoinEffectType);
	coin->setEffectBehavior(effectBehavior);

	return coin;
}*/