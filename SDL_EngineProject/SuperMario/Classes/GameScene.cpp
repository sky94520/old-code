#include "GameScene.h"
#include "Player.h"
#include "Entity.h"
#include "BehaviorManager.h"
#include "Item.h"
#include "Enemy.h"
#include "EffectBehavior.h"
#include "PanelLayer.h"
#include "DynamicData.h"

GameScene::GameScene()
	:m_pMapLayer(nullptr),m_pPlayerLayer(nullptr)
	,m_pEventLayer(nullptr),m_pItemLayer(nullptr)
	,m_pBulletLayer(nullptr),m_pEnemyLayer(nullptr)
	,m_pPanelLayer(nullptr)
{
}
GameScene::~GameScene()
{
	BehaviorManager::getInstance()->purge();
	DynamicData::purge();
}
bool GameScene::init()
{
	//加载资源
	auto frameCache = Director::getInstance()->getSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("image/resources.xml");
	//加载音乐
	auto soundManager = SoundManager::getInstance();
	soundManager->preloadBackgroundMusic("sound/supermario.ogg");
	soundManager->preloadEffect("sound/mario_collide_tile.ogg");
	soundManager->preloadEffect("sound/mario_jump.ogg");
	soundManager->preloadEffect("sound/item_present.ogg");
	soundManager->preloadEffect("sound/mario_eat_item.ogg");
	soundManager->preloadEffect("sound/mario_broke_tile.ogg");
	soundManager->preloadEffect("sound/mario_stamp_enemy.ogg");
	soundManager->preloadEffect("sound/shell.ogg");
	soundManager->preloadEffect("sound/mario_fire.ogg");
	soundManager->preloadEffect("sound/mario_bullet_tile_collided.ogg");
	soundManager->preloadEffect("sound/get_gold.ogg");
	//开始音乐
	soundManager->playBackgroundMusic("sound/supermario.ogg",-1);
	//设置行为管理器属性
	BehaviorManager::getInstance()->setGameScene(this);
	//事件层
	m_pEventLayer = KeyEventLayer::create();
	m_pEventLayer->setDelegate(this);
	this->addChild(m_pEventLayer);
	//地图层
	m_pMapLayer = MapLayer::create();
	m_pMapLayer->setDelegate(this);
	this->addChild(m_pMapLayer);
	//todo 根据tmx获取重力和背景颜色
	this->loadLevel();
	//主角层
	m_pPlayerLayer = PlayerLayer::create(this);
	this->addChild(m_pPlayerLayer);
	//道具层
	m_pItemLayer = ItemLayer::create();
	m_pItemLayer->setDelegate(this);
	this->addChild(m_pItemLayer);
	//子弹层
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//怪物层
	m_pEnemyLayer = EnemyLayer::create();
	m_pEnemyLayer->setDelegate(this);
	this->addChild(m_pEnemyLayer);
	//ui层
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//模型的初始化
	DynamicData::getInstance()->init();
	//添加回调函数
	this->scheduleUpdate();
	this->schedule(SDL_CALLBACK_1(GameScene::reduceTime,this),"time",1.f);

	return true;
}
void GameScene::update(float dt)
{
	m_pMapLayer->update(dt,m_pPlayerLayer->getPlayer());
	m_pPlayerLayer->update(dt);

	m_pItemLayer->update(dt);
	m_pBulletLayer->update(dt);
	m_pEnemyLayer->update(dt);
	//处理碰撞
	this->handleCollision(dt);
}
TMXLayer*GameScene::getEntityLayer()const
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();
	auto layer = tiledMap->getLayer("entity layer");
	return layer;
}
TMXLayer*GameScene::getCollidedLayer()const
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();
	auto layer = tiledMap->getLayer("collided layer");
	return layer;
}
TMXLayer*GameScene::getCoinLayer()const
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();
	auto layer = tiledMap->getLayer("coin layer");
	return layer;
}
Player*GameScene::getPlayer()const
{
	return m_pPlayerLayer->getPlayer();
}
void GameScene::loadLevel()
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();
	
	auto gravityStr = tiledMap->getPropertyForName("gravity").asString();
	auto bgColorStr = tiledMap->getPropertyForName("bg_color").asString();
	//设置重力
	m_gravity = Point(0,5.5);//Point(gravityStr);
	auto bgColor = Color4B(bgColorStr);
	//设置背景颜色
	Director::getInstance()->getRenderer()->setRenderDrawColor(bgColor);
}
void GameScene::handleCollision(float dt)
{
	this->handleCollisionBetweenPlayerAndItems(dt);
	this->handleCollisionBetweenPlayerAndEnemys(dt);
	this->handleCollisionBullets(dt);
}
void GameScene::handleCollisionBetweenPlayerAndItems(float dt)
{
	//mario和道具的碰撞
	Player*player = m_pPlayerLayer->getPlayer();
	auto r = player->getCollisionBoundingBox();

	vector<Item*>& items = m_pItemLayer->getItems();
	for(auto item:items)
	{
		auto r1 = item->getCollisionBoundingBox();
		if(r1.intersectsRect(r))
		{
			item->performEffect(player);
			item->hurt(1);
			//item->setDead(true);
			//设置当前状态为空
			player->setCurState(kPlayerState_None);
			//播放音效
			SoundManager::getInstance()->playEffect("sound/mario_eat_item.ogg",0);
			//重新设置碰撞面积
			r = player->getCollisionBoundingBox();
			//增加分数
			this->addScore(500,item);
		}
	}
}
void GameScene::handleCollisionBetweenPlayerAndEnemys(float dt)
{
	auto player = m_pPlayerLayer->getPlayer();
	auto r = player->getCollisionBoundingBox();
	//marioy轴碰撞高度
	auto collidedHeight = m_gravity.y/2;
	//mario和怪物的碰撞
	//怪物死亡有两种 1.被踩死 2.被射死
	auto enemys = m_pEnemyLayer->getEnemys();

	for(auto it = enemys.begin();it != enemys.end();it++)
	{
		auto enemy = *it;
		if(enemy->isDying())
			continue;
		//怪物的碰撞体积
		auto r1 = enemy->getCollisionBoundingBox();
		//处理怪物之间的碰撞
		auto iter = find_if(enemys.begin(),enemys.end(),[r1,enemy](Enemy*e)
		{
			return e != enemy && e->isDying() == false
				&& e->getCollisionBoundingBox().intersectsRect(r1);
		});
		//找到碰撞的敌人并且 碰撞标记为false
		if(iter != enemys.end())
		{
			auto e2 = *iter;
			//是否改变方向
			bool bChangeDir = true;
			//检测是否会伤害enemy
			if(enemy->isCanHurtEnemy())
			{
				e2->hurt(enemy,EnemyHurtType::Enemy);
				bChangeDir = false;
				SoundManager::getInstance()->playEffect("sound/shell.ogg",0);
				this->addScore(500,e2);
			}
			if(e2->isCanHurtEnemy())
			{
				enemy->hurt(e2,EnemyHurtType::Enemy);
				bChangeDir = false;
				SoundManager::getInstance()->playEffect("sound/shell.ogg",0);
				this->addScore(500,enemy);
			}
			if(bChangeDir && enemy->isCollidedWithEnemyFlag() == false
				&& e2->isCollidedWithEnemyFlag() == false)
			{
				enemy->changeDirectionX();
				e2->changeDirectionX();
			}
			enemy->setCollidedWithEnemyFlag(true);
			e2->setCollidedWithEnemyFlag(true);
		}
		else
			enemy->setCollidedWithEnemyFlag(false);
		//这两个条件就不再进行与player的碰撞检测
		if(player->isDying())
			break;
		auto invulnerType = player->getInvulnerableType();
		//主角是否能受到伤害
		bool bPlayerHurted = (invulnerType == InvulnerableType::kNone);
		//敌人是否应该受到伤害
		bool bEnemyHurted = (invulnerType == InvulnerableType::kCanHurtEnemy);
		//确定主角踩踏面积
		Rect playerStampRect = Rect(r.origin.x,r.origin.y + (r.size.height - collidedHeight),r.size.width,collidedHeight);
		Rect playerCollidedRect = Rect(r.origin.x,r.origin.y,r.size.width,r.size.height - collidedHeight);
		//确定敌人碰撞面积
		Rect enemyStampRect = Rect(r1.origin.x,r1.origin.y + collidedHeight,r1.size.width,collidedHeight);
		Rect enemyCollidedRect = Rect(r1.origin.x,r1.origin.y,r1.size.width,r1.size.height);
		//当前player处于无敌且能伤害敌人 并且发生碰撞 敌人受伤
		if(invulnerType == InvulnerableType::kCanHurtEnemy
			&& r.intersectsRect(r1))
		{
			enemy->hurt(player,EnemyHurtType::Star);
			this->addScore(200,enemy);
		}
		//只有踩到敌人并且 敌人不对踩 免疫 敌人受伤
		else if(player->getCurState() == kPlayerState_Falling
			&& playerStampRect.intersectsRect(enemyStampRect)
			&& enemy->isStampImmune() == false)
		{
			enemy->hurt(player,EnemyHurtType::Stamp);
			auto velocity = player->getVelocity();
			//设置主角跳跃高度
			velocity.y = -m_gravity.y;
			player->setVelocity(velocity);
			//todo
			m_pPlayerLayer->addPlayerRemantHeight(20);
			//播放怪物受伤音效
			SoundManager::getInstance()->playEffect("sound/mario_stamp_enemy.ogg",0);
			this->addScore(600,enemy);
		}
		//踩到敌人 并且 敌人对踩免疫 或者 碰撞到 player可能受伤
		else if((playerStampRect.intersectsRect(enemyStampRect) && enemy->isStampImmune())
			|| playerCollidedRect.intersectsRect(enemyCollidedRect)
			&& (enemy->isCollidedWithPlayerFlag() == false))
		{
			if(bPlayerHurted && enemy->getDamage() != 0)
			{
				player->hurt(enemy->getDamage());
			}
			enemy->hurt(player,EnemyHurtType::None);

			enemy->setCollidedWithPlayerFlag(true);
		}
		else if(r.intersectsRect(r1) == false)
			enemy->setCollidedWithPlayerFlag(false);
	}
}
void GameScene::handleCollisionBullets(float dt)
{
	auto &playerBullets = m_pBulletLayer->getPlayerBullets();
	auto &enemys = m_pEnemyLayer->getEnemys();

	for(auto bullet:playerBullets)
	{
		if(bullet->isDying())
			continue;
		Rect r = bullet->getCollisionBoundingBox();

		auto iter = std::find_if(enemys.begin(),enemys.end(),[bullet,r](Enemy*enemy)
		{
			return enemy->isDying() == false
				&& enemy->getCollisionBoundingBox().intersectsRect(r);
		});
		//发生碰撞
		if(iter != enemys.end())
		{
			auto enemy = *iter;
			bullet->hurt(bullet->getCurHp());//todo
			enemy->hurt(bullet,EnemyHurtType::Bullet);
			//播放音效
			SoundManager::getInstance()->playEffect("sound/shell.ogg",0);
			this->addScore(200,enemy);
		}
	}
}
int GameScene::collidedWithBlockCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity)
{
	auto gid = layer->getTileGIDAt(tileCoordinate);
	//对透明砖块进行特殊处理
	if(gid == 38)
	{
		return 0;
	}
	if(entity->isInteractiveWithBlock() == false)
		return gid;
	//判断是否是mario，如果是mario，会进行坐标调整
	auto player = m_pPlayerLayer->getPlayer();
	bool bRet = false;
	if(player == entity)
	{
		bRet = m_pMapLayer->optimizePlayerPos(player,layer->getTileAt(tileCoordinate));
	}
	if(bRet == false)
		return m_pMapLayer->entityInteractWithTile(entity,layer,tileCoordinate);
	return 0;
}
int GameScene::collidedWithCoinCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity)
{
	auto gid = layer->getTileGIDAt(tileCoordinate);
	//todo直接吃掉金币
	//add coin
	//printf("add coin");
	SoundManager::getInstance()->playEffect("sound/get_gold.ogg",0);
	//增加金币
	this->addCoin(1);

	layer->setTileGID(0,tileCoordinate);
	return gid;
}
void GameScene::reduceTime(float dt)
{
	this->alterRemantTime(-1);
}
Point GameScene::getPlayerBornPos()const
{
	return m_pMapLayer->getPlayerBornPos();
}

Point GameScene::getGravity()const
{
	return m_gravity;
}
ValueMap GameScene::getTilePropertiesForGID(int gid)
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();
	return tiledMap->getTilePropertiesForGID(gid);
}
int GameScene::isCollidedTileWithCollidedLayer(const Rect&r,char dir)const
{
	auto layer = this->getCollidedLayer();
	return m_pMapLayer->isCollidedTile(r,dir,layer);
}
int GameScene::isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir)
{
	auto layer = this->getCollidedLayer();
	//回调函数
	TileCollidedCallback callback = nullptr;
	//判断该entity是否可以和方块交互
	//if(entity->isInteractiveWithBlock())
	callback = SDL_CALLBACK_2(GameScene::collidedWithBlockCallback,this,entity);

	return m_pMapLayer->isCollidedTile(r,dir,layer,callback);
}
int GameScene::isCollidedTileWithCoinLayer(const Rect&r,char dir)
{
	auto layer = this->getCoinLayer();
	//todo
	TileCollidedCallback callback = SDL_CALLBACK_2(GameScene::collidedWithCoinCallback,this,nullptr);
	return m_pMapLayer->isCollidedTile(r,dir,layer,callback);
}
int GameScene::isCollidedTileWithCoinLayer(const Rect&r,Entity*entity,char dir)
{
	auto layer = this->getCoinLayer();
	TileCollidedCallback callback = SDL_CALLBACK_2(GameScene::collidedWithCoinCallback,this,entity);
	return m_pMapLayer->isCollidedTile(r,dir,layer,callback);
}
void GameScene::goldAction(const Point&position)
{
	auto layer = this->getEntityLayer();
	m_pPanelLayer->goldAction(layer,position);
}
void GameScene::blockBrokenAction(Sprite*sprite)
{
	auto layer = this->getEntityLayer();
	m_pPanelLayer->blockBrokenAction(layer,sprite);
}
void GameScene::flowTextAction(const string&text,const Point&position)
{
	auto layer = this->getEntityLayer();
	m_pPanelLayer->flowTextAction(layer,text,position);
}
void GameScene::addCoin(int coin,Node*node)
{
	//修改金币数目
	DynamicData::getInstance()->alterCoin(1);
	//尝试金币动画
	if(node)
	{
		auto position = node->getPosition() + Point(0,-node->getContentSize().height/2);
		this->goldAction(position);
	}
}
void GameScene::addScore(int score,Node*node)
{
	DynamicData::getInstance()->alterScore(score);
	if(node)
	{
		auto size = node->getContentSize();
		auto position = node->getPosition() + Point(size.width/2,0);
		this->flowTextAction(to_string(score),position);
	}
}
void GameScene::alterRemantTime(int time)
{
	DynamicData::getInstance()->alterTime(time);
}
void GameScene::alterLife(int life)
{
	DynamicData::getInstance()->alterLife(life);
}
void GameScene::keyPressed(EventType eventType)
{
	m_pPlayerLayer->keyPressed(eventType);
}
void GameScene::keyReleased(EventType eventType)
{
	m_pPlayerLayer->keyReleased(eventType);
}
bool GameScene::createObjectByTypeAndName(TMXObject*object)
{
	if(object->type == "item")
	{
		return m_pItemLayer->produceItemByType(object);
	}
	return false;
}
void GameScene::createEntityByTMXObject(TMXObject*object)
{
	//根据当前类型交给对应的层
//	if(object->type == "player")
//		m_pPlayerLayer->playerBorn(object,this->getEntityLayer());
	if(object->type == "enemy")
		m_pEnemyLayer->enemyBorn(object,this->getEntityLayer());
}
void GameScene::addPlayerBullet(BulletType bulletType,const Point&startPos,const Point&heading,const string&customName)
{
	m_pBulletLayer->addPlayerBullet(bulletType,startPos,heading,customName);
	SoundManager::getInstance()->playEffect("sound/mario_fire.ogg",0);
}
int GameScene::collidedConsumeable(const ValueMap&properties,const Point&tileCoordinate,TMXLayer*layer)
{
	auto type = properties.at("type").asString();
	if(type == "coin")
	{
		SoundManager::getInstance()->playEffect("sound/get_gold.ogg",0);
		//增加金币
		layer->setTileGID(0,tileCoordinate);
		return 0;
	}
	return -1;
}
void GameScene::blockUpCallback(Sprite*tileSprite)
{
	auto r = tileSprite->getBoundingBox();
	//是否和金币发生碰撞
	int ret = this->isCollidedTileWithCoinLayer(r,0x8);
	if(ret > 0)
	{
/*		//对金币出现位置进行调整
		auto position = tileSprite->getPosition() - Point(0,tileSprite->getContentSize().height);
		//播放金币特效
		this->getGoldAction(position);
		//test
		m_pPanelLayer->flowScoreAction(this->getEntityLayer(),100,position + Point(50,0));*/
		_eventDispatcher->dispatchCustomEvent("coin",tileSprite);
	}
}