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
	//������Դ
	auto frameCache = Director::getInstance()->getSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("image/resources.xml");
	//��������
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
	//��ʼ����
	soundManager->playBackgroundMusic("sound/supermario.ogg",-1);
	//������Ϊ����������
	BehaviorManager::getInstance()->setGameScene(this);
	//�¼���
	m_pEventLayer = KeyEventLayer::create();
	m_pEventLayer->setDelegate(this);
	this->addChild(m_pEventLayer);
	//��ͼ��
	m_pMapLayer = MapLayer::create();
	m_pMapLayer->setDelegate(this);
	this->addChild(m_pMapLayer);
	//todo ����tmx��ȡ�����ͱ�����ɫ
	this->loadLevel();
	//���ǲ�
	m_pPlayerLayer = PlayerLayer::create(this);
	this->addChild(m_pPlayerLayer);
	//���߲�
	m_pItemLayer = ItemLayer::create();
	m_pItemLayer->setDelegate(this);
	this->addChild(m_pItemLayer);
	//�ӵ���
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//�����
	m_pEnemyLayer = EnemyLayer::create();
	m_pEnemyLayer->setDelegate(this);
	this->addChild(m_pEnemyLayer);
	//ui��
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//ģ�͵ĳ�ʼ��
	DynamicData::getInstance()->init();
	//��ӻص�����
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
	//������ײ
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
	//��������
	m_gravity = Point(0,5.5);//Point(gravityStr);
	auto bgColor = Color4B(bgColorStr);
	//���ñ�����ɫ
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
	//mario�͵��ߵ���ײ
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
			//���õ�ǰ״̬Ϊ��
			player->setCurState(kPlayerState_None);
			//������Ч
			SoundManager::getInstance()->playEffect("sound/mario_eat_item.ogg",0);
			//����������ײ���
			r = player->getCollisionBoundingBox();
			//���ӷ���
			this->addScore(500,item);
		}
	}
}
void GameScene::handleCollisionBetweenPlayerAndEnemys(float dt)
{
	auto player = m_pPlayerLayer->getPlayer();
	auto r = player->getCollisionBoundingBox();
	//marioy����ײ�߶�
	auto collidedHeight = m_gravity.y/2;
	//mario�͹������ײ
	//�������������� 1.������ 2.������
	auto enemys = m_pEnemyLayer->getEnemys();

	for(auto it = enemys.begin();it != enemys.end();it++)
	{
		auto enemy = *it;
		if(enemy->isDying())
			continue;
		//�������ײ���
		auto r1 = enemy->getCollisionBoundingBox();
		//�������֮�����ײ
		auto iter = find_if(enemys.begin(),enemys.end(),[r1,enemy](Enemy*e)
		{
			return e != enemy && e->isDying() == false
				&& e->getCollisionBoundingBox().intersectsRect(r1);
		});
		//�ҵ���ײ�ĵ��˲��� ��ײ���Ϊfalse
		if(iter != enemys.end())
		{
			auto e2 = *iter;
			//�Ƿ�ı䷽��
			bool bChangeDir = true;
			//����Ƿ���˺�enemy
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
		//�����������Ͳ��ٽ�����player����ײ���
		if(player->isDying())
			break;
		auto invulnerType = player->getInvulnerableType();
		//�����Ƿ����ܵ��˺�
		bool bPlayerHurted = (invulnerType == InvulnerableType::kNone);
		//�����Ƿ�Ӧ���ܵ��˺�
		bool bEnemyHurted = (invulnerType == InvulnerableType::kCanHurtEnemy);
		//ȷ�����ǲ�̤���
		Rect playerStampRect = Rect(r.origin.x,r.origin.y + (r.size.height - collidedHeight),r.size.width,collidedHeight);
		Rect playerCollidedRect = Rect(r.origin.x,r.origin.y,r.size.width,r.size.height - collidedHeight);
		//ȷ��������ײ���
		Rect enemyStampRect = Rect(r1.origin.x,r1.origin.y + collidedHeight,r1.size.width,collidedHeight);
		Rect enemyCollidedRect = Rect(r1.origin.x,r1.origin.y,r1.size.width,r1.size.height);
		//��ǰplayer�����޵������˺����� ���ҷ�����ײ ��������
		if(invulnerType == InvulnerableType::kCanHurtEnemy
			&& r.intersectsRect(r1))
		{
			enemy->hurt(player,EnemyHurtType::Star);
			this->addScore(200,enemy);
		}
		//ֻ�вȵ����˲��� ���˲��Բ� ���� ��������
		else if(player->getCurState() == kPlayerState_Falling
			&& playerStampRect.intersectsRect(enemyStampRect)
			&& enemy->isStampImmune() == false)
		{
			enemy->hurt(player,EnemyHurtType::Stamp);
			auto velocity = player->getVelocity();
			//����������Ծ�߶�
			velocity.y = -m_gravity.y;
			player->setVelocity(velocity);
			//todo
			m_pPlayerLayer->addPlayerRemantHeight(20);
			//���Ź���������Ч
			SoundManager::getInstance()->playEffect("sound/mario_stamp_enemy.ogg",0);
			this->addScore(600,enemy);
		}
		//�ȵ����� ���� ���˶Բ����� ���� ��ײ�� player��������
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
		//������ײ
		if(iter != enemys.end())
		{
			auto enemy = *iter;
			bullet->hurt(bullet->getCurHp());//todo
			enemy->hurt(bullet,EnemyHurtType::Bullet);
			//������Ч
			SoundManager::getInstance()->playEffect("sound/shell.ogg",0);
			this->addScore(200,enemy);
		}
	}
}
int GameScene::collidedWithBlockCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity)
{
	auto gid = layer->getTileGIDAt(tileCoordinate);
	//��͸��ש��������⴦��
	if(gid == 38)
	{
		return 0;
	}
	if(entity->isInteractiveWithBlock() == false)
		return gid;
	//�ж��Ƿ���mario�������mario��������������
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
	//todoֱ�ӳԵ����
	//add coin
	//printf("add coin");
	SoundManager::getInstance()->playEffect("sound/get_gold.ogg",0);
	//���ӽ��
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
	//�ص�����
	TileCollidedCallback callback = nullptr;
	//�жϸ�entity�Ƿ���Ժͷ��齻��
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
	//�޸Ľ����Ŀ
	DynamicData::getInstance()->alterCoin(1);
	//���Խ�Ҷ���
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
	//���ݵ�ǰ���ͽ�����Ӧ�Ĳ�
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
		//���ӽ��
		layer->setTileGID(0,tileCoordinate);
		return 0;
	}
	return -1;
}
void GameScene::blockUpCallback(Sprite*tileSprite)
{
	auto r = tileSprite->getBoundingBox();
	//�Ƿ�ͽ�ҷ�����ײ
	int ret = this->isCollidedTileWithCoinLayer(r,0x8);
	if(ret > 0)
	{
/*		//�Խ�ҳ���λ�ý��е���
		auto position = tileSprite->getPosition() - Point(0,tileSprite->getContentSize().height);
		//���Ž����Ч
		this->getGoldAction(position);
		//test
		m_pPanelLayer->flowScoreAction(this->getEntityLayer(),100,position + Point(50,0));*/
		_eventDispatcher->dispatchCustomEvent("coin",tileSprite);
	}
}