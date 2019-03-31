#include "GameScene.h"
#include "FishingJoyData.h"
#include "LevelLayer.h"
#include "StaticData.h"
#include "GB2ShapeCache-x.h"
#include "B2EntityFactory.h"
#include "NetGunBullet.h"
#include "FishingNet.h"
#include "EffectLayer.h"
#include "SDL.h"
#include "Fish.h"
#include "Bullet.h"
#include "ItemButton.h"
#include "StartScene.h"

b2World*GameScene::s_pWorld = nullptr;

GameScene::GameScene()
	:m_pLevelLayer(nullptr),m_pTouchLayer(nullptr)
	,m_pPanelLayer(nullptr),m_pCannon(nullptr)
	,m_pGoldTimer(nullptr),m_pBulletLayer(nullptr)
	,m_pFishingEntityLayer(nullptr),m_pFishLayer(nullptr)
	,m_pRewardLayer(nullptr),m_pEffectLayer(nullptr)
	,m_pPauseLayer(nullptr)
{
}
GameScene::~GameScene()
{
	B2EntityFactory::getInstance()->purge();
	SDL_SAFE_DELETE(s_pWorld);
}
bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ʼ����������
	b2Vec2 gravity(0.f,0.f);
	s_pWorld = new b2World(gravity);
	s_pWorld->SetAllowSleeping(true);//��������
	s_pWorld->SetContinuousPhysics(true);//�����������
	s_pWorld->SetContactListener(this);
	//Ԥ���� todo
	this->preloadResources();
	//�ؿ���
	int tollgateIndex = FishingJoyData::getInstance()->getTollgateIndex();
	auto tollgateName = StringUtils::format("level/level%d.tmx",tollgateIndex + 1);
	m_pLevelLayer = LevelLayer::create(tollgateName);
	this->addChild(m_pLevelLayer);
	//ui
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	m_pPanelLayer->setDelegate(this);
	//�¼���
	m_pTouchLayer = TouchLayer::create();
	this->addChild(m_pTouchLayer);
	m_pTouchLayer->setDelegate(this);

	//���
	m_pFishLayer = FishLayer::create();
	m_pFishLayer->setDelegate(this);
	m_pFishLayer->reset();
	this->addChild(m_pFishLayer);
	//��ǹ����
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//������
	m_pFishingEntityLayer = FishingEntityLayer::create();
	m_pFishingEntityLayer->setDelegate(this);
	this->addChild(m_pFishingEntityLayer);	
	//���ڲ�
	m_pCannon = Cannon::create();
	m_pCannon->setDelegate(this);
	m_pCannon->setNetGunBullets(m_pLevelLayer->getNetGunBulletVec());

	this->addChild(m_pCannon);
	//����λ��
	m_pCannon->setPosition(m_pPanelLayer->getConnonBornPos());
	//��ӽ�Ҽ�����
	m_pGoldTimer = GoldTimer::create();
	m_pGoldTimer->setDelegate(this);
	m_pGoldTimer->setPosition(STATIC_DATA_POINT("gold_timer_pos"));

	this->addChild(m_pGoldTimer);
	//Ч����
	m_pEffectLayer = EffectLayer::create();
	this->addChild(m_pEffectLayer);
	//������
	m_pRewardLayer = RewardLayer::create();
	m_pRewardLayer->setDelegate(this);
	this->addChild(m_pRewardLayer);
	//��ͣ��
	m_pPauseLayer = PauseLayer::create();
	m_pPauseLayer->setDelegate(this);
	m_pPauseLayer->updateUI();
	//����λ�ó���
	m_pPauseLayer->setPosition(0,-visibleSize.height);

	this->addChild(m_pPauseLayer);
	//ˢ�µ�ǰ�����ʾ����
	m_pPanelLayer->updateSelf();
	//���ű�������
	this->playBackgroundMusic();

	this->scheduleUpdate();

	return true;
}
void GameScene::update(float dt)
{
	//��shape���澫���ƶ�
	const int PTM_RATIO = GB2ShapeCache::getInstance()->getPtmRatio();
	//PhysicalEngine::getInstance()->PTM_RATIO;

	for(b2Body* body = s_pWorld->GetBodyList();body;body = body->GetNext())
	{
		if(body->GetUserData())
		{
			Entity*node = static_cast<Entity*>(body->GetUserData());
			b2Vec2 position = b2Vec2(node->getPositionX()/PTM_RATIO,node->getPositionY()/PTM_RATIO);
			//��ȡ�Ƕȣ��Ƕȸ����ڲ�����
			auto sprite = node->getSprite();
			//��ʱ���� Ӧ������y�ᷭת
			//todo ��B2Entity��д������ͼƬ��С��������λ��
			float32 angle = SDL_ANGLE_TO_DEGREE(sprite->getRotation() + 180.f);

			body->SetTransform(position,angle);
		}
	}

	//�ٶȺ�λ�ö������и���
	s_pWorld->Step(dt,0,0);

	m_pGoldTimer->update(dt);
	m_pFishLayer->update(dt);
	m_pBulletLayer->update(dt);
	m_pFishingEntityLayer->update(dt);
}
void GameScene::preloadResources()
{
	//��ȡͼƬ��Դ����
	auto spriteFrameCache = Director::getInstance()->getSpriteFrameCache();
	ValueVector values = StaticData::getInstance()->getValueForKey("fish_src_filepath").asValueVector();
	
	for(auto value:values)
	{
		auto filename = value.asString();
		spriteFrameCache->addSpriteFramesWithFile(filename);
	}
	//���ض���
	AnimationCache::getInstance()->addAnimationsWithFile(STATIC_DATA_STRING("animation_filepath"));
}

void GameScene::gameExit()
{
	//ɾ��������
	FishingJoyData::purge();
	StaticData::purge();
	GB2ShapeCache::getInstance()->purge();
}

void GameScene::operateAllSchedulerAndActions(Node*node,GameState state)
{
	switch(state)
	{
	case GameState::Pause:node->pauseSchedulerAndActions();
		break;
	case GameState::Resume:node->resumeSchedlerAndActions();
		break;
	}
	const std::vector<Node*>& children = node->getChildren();

	for(auto child:children)
	{
		this->operateAllSchedulerAndActions(child,state);
	}
}

void GameScene::gamePause()
{
	this->operateAllSchedulerAndActions(m_pBulletLayer,GameState::Pause);
	this->operateAllSchedulerAndActions(m_pFishingEntityLayer,GameState::Pause);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::Pause);
	this->operateAllSchedulerAndActions(m_pCannon,GameState::Pause);

	this->unscheduleUpdate();

	m_pTouchLayer->setTouchEnable(false);
	m_pPanelLayer->setBtnEnable(false);
}

void GameScene::gameResume()
{
	this->operateAllSchedulerAndActions(m_pBulletLayer,GameState::Resume);
	this->operateAllSchedulerAndActions(m_pFishingEntityLayer,GameState::Resume);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::Resume);
	this->operateAllSchedulerAndActions(m_pCannon,GameState::Resume);

	this->scheduleUpdate();

	m_pTouchLayer->setTouchEnable(true);
	m_pPanelLayer->setBtnEnable(true);
}

void GameScene::playBackgroundMusic()
{
	bool bPlayingMusic = FishingJoyData::getInstance()->isPlayingMusic();

	if (bPlayingMusic)
	{
		auto sBGM = m_pLevelLayer->getBGM();

		SoundManager::getInstance()->playBackgroundMusic(sBGM,-1);
	}
	else if (SoundManager::getInstance()->isBackgroundPlaying())
	{
		SoundManager::getInstance()->stopBackgroundMusic();
	}
}

b2World*GameScene::getWorld()
{
	return s_pWorld;
}

void GameScene::collisionOfBullet(Bullet*bullet,Entity*entity)
{
	//��Fish������ײ
	if(entity->getType() == Entity::Type::Fish)
	{
		Fish*fish = static_cast<Fish*>(entity);
		bullet->collided(fish);
		//�����ǹ��������ײ,ֻ�в���Groupʱ�Żᴦ���߼�
		if(m_pFishLayer->getCurState() != FishLayer::State::Group)
			fish->collided(TriggingType::NetGunBullet);
		//����ͺ�����ײ
		if(fish->getFishType() == FishType::StarFish)
		{
			fish->caught();
			//����������
			bullet->setMakeFishingEntity(false);
		}

	}
}

void GameScene::collisionOfFishingEntity(FishingEntity*fishingEntity,Entity*entity)
{

	Fish*fish = nullptr;
	//�������㷢����ײ
	if(entity->getType() == Entity::Type::Fish)
	{
		fish = static_cast<Fish*>(entity);
	}
	if(fish == nullptr)
		return ;

	float scope = 0.f;
	//����Ǽ��⣬��ô�ɹ���Ϊ1
	if(fishingEntity->getFishingType() == FishingType::Laser)
	{
		scope = 1.f;
	}
	//��ʱ�㴦���޵гɹ���Ϊ0
	else if(fish->isInvulnerable())
	{
		scope = 0.f;
	}
	else if(fishingEntity->getFishingType() == FishingType::FishingNet)
	{
		auto fishingNet = static_cast<FishingNet*>(fishingEntity);

		int ratio = m_pLevelLayer->getRatio();
		int gold = STATIC_FISH_GOLD(fish->getID()) * ratio;
		//���ֵ ��ؿ���ͬ����ͬ
		float tax = m_pLevelLayer->getTax();

		scope = fishingNet->getLevel() * (1 - tax)/gold;
	}
	//todo
	else if(fishingEntity->getFishingType() == FishingType::Pearl)
	{
		scope = 0.4f;
	}
	else if(fishingEntity->getFishingType() == FishingType::Fog)
	{
		scope = 0.4f;
	}
	//������ײ
	fishingEntity->collided();

	float success = RANDOM_0_1();
	//�㱻��׽�ɹ�
	if(success < scope)
	{
		fish->caught();
		//��ȡ������ľ���ֵ �����Ӿ���
		auto exp = STATIC_FISH_EXP(fish->getID());
		this->addExp(exp);
		//ֻ�в��Ǽ������������
		if(fishingEntity->getFishingType() != FishingType::Laser)
		{
			auto energy = STATIC_FISH_ENERGY(fish->getID());
			this->addEnergy(energy);
		}
	}
	//�㲶׽ʧ��
	else if(m_pFishLayer->getCurState() != FishLayer::State::Group)
	{
		fish->collided(TriggingType::Fishing);
	}
}

void GameScene::BeginContact(b2Contact* contact)
{
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();

	auto bodyA = fixtureA->GetBody();
	auto bodyB = fixtureB->GetBody();


	B2Entity*entityA = static_cast<B2Entity*>(bodyA->GetUserData());
	B2Entity*entityB = static_cast<B2Entity*>(bodyB->GetUserData());

	//�������� ��֤ÿ֡����һ��
	if(!entityA->isCollided() && entityA->getType() == Entity::Type::Fish)
	{
		entityA->setCollided(true);

		if(entityB->getType() == Entity::Type::Fishing)
			this->collisionOfFishingEntity(static_cast<FishingEntity*>(entityB),entityA);
		else if(entityB->getType() == Entity::Type::Bullet)
			this->collisionOfBullet(static_cast<Bullet*>(entityB),entityA);
	}
	else if(!entityB->isCollided() && entityB->getType() == Entity::Type::Fish)
	{
		entityB->setCollided(true);

		if(entityA->getType() == Entity::Type::Fishing)
			this->collisionOfFishingEntity(static_cast<FishingEntity*>(entityA),entityB);
		else if(entityA->getType() == Entity::Type::Bullet)
			this->collisionOfBullet(static_cast<Bullet*>(entityA),entityB);
	}
	else if(entityA->getType() == Entity::Type::Fishing)
	{
		this->collisionOfFishingEntity(static_cast<FishingEntity*>(entityA),entityB);
	}
	else if(entityA->getType() == Entity::Type::Bullet)
	{
		this->collisionOfBullet(static_cast<Bullet*>(entityA),entityB);
	}
}
void GameScene::EndContact(b2Contact* contact)
{
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();

	auto bodyA = fixtureA->GetBody();
	auto bodyB = fixtureB->GetBody();

	B2Entity*entityA = static_cast<B2Entity*>(bodyA->GetUserData());
	B2Entity*entityB = static_cast<B2Entity*>(bodyB->GetUserData());

	entityA->setCollided(false);
	entityB->setCollided(false);
}

void GameScene::addCannonLevel()
{
	if(m_pCannon->isCanFire())
	{
		m_pCannon->addLevel();

		bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

		if (bPlayingChunk)
		{
			auto sChangeNetGun = STATIC_DATA_STRING("change_net_gun");
			SoundManager::getInstance()->playEffect(sChangeNetGun,0);
		}
	}
}

void GameScene::subCannonLevel()
{
	if(m_pCannon->isCanFire())
	{
		m_pCannon->subLevel();
		
		bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

		if (bPlayingChunk)
		{
			auto sChangeNetGun = STATIC_DATA_STRING("change_net_gun");
			SoundManager::getInstance()->playEffect(sChangeNetGun,0);
		}
	}
}

void GameScene::pauseBtnCallback()
{
	//��ͣ��Ϸ
	this->gamePause();
	//������ʾѡ�����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveBy*move = MoveBy::create(0.5f,Point(0,visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pPauseLayer->runAction(action);
}

void GameScene::continueGame()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��Ϸ�ָ�
	this->gameResume();
	//������ʾѡ�����
	MoveBy*move = MoveBy::create(0.5f,Point(0,-visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pPauseLayer->runAction(action);
}

void GameScene::turnStartLayer()
{
	StartScene*scene = StartScene::create();

	Director::getInstance()->replaceScene(scene);
}

void GameScene::chooseTollgate()
{
	StartScene*scene = StartScene::create();
	scene->enterTollgateLayer();

	Director::getInstance()->replaceScene(scene);
}

void GameScene::operateMusic()
{
	auto soundManager = SoundManager::getInstance();
	bool playingMusic = FishingJoyData::getInstance()->isPlayingMusic();
	playingMusic = !playingMusic;
	//��д
	FishingJoyData::getInstance()->setPlayingMusic(playingMusic);
	//�ڲ����лص����ж��Ƿ񲥷ű�������
	this->playBackgroundMusic();
}

void GameScene::operateChunk()
{
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();
	bPlayingChunk = ! bPlayingChunk;
	//��д
	FishingJoyData::getInstance()->setPlayingChunk(bPlayingChunk);
}

void GameScene::changeBullet(ItemButton*button,bool oldVisible,bool visible)
{
	auto selectedBulletName = button->getName();
	auto pos = button->getPosition();

	//todo
	auto spriteName = "bullet";
	//�ı���Чλ��
	if(oldVisible == visible)
	{
		m_pEffectLayer->changeSelectedMark(spriteName,pos);
		//���õ�ǰѡ�е��ӵ�
		FishingJoyData::getInstance()->setSelectedBullet(selectedBulletName);
	}
	else if(visible)
	{
		m_pEffectLayer->addSelectedMark(spriteName,pos);
	}
	else
	{
		m_pEffectLayer->removeSelectedMark(spriteName);
	}
}

bool GameScene::onTouchBegan(Touch*touch,SDL_Event*event)
{
	if(m_pCannon->isCanFire() == false)
		return true;

	auto pos = touch->getLocation();

	m_pCannon->aimAt(pos);

	auto fishingJoyData = FishingJoyData::getInstance();
	//�Ƿ񲥷���Ч
	bool bPlayingChunk = fishingJoyData->isPlayingChunk();

	if(!m_pCannon->isCanFire())
		return true;
	//��ȡ��ǰѡ�е��ӵ�����
	auto bulletName = fishingJoyData->getSelectedBullet();
	//����������
	if(m_pCannon->getType() == Cannon::Type::Laser)
	{
		auto afterEnergy = fishingJoyData->getEnergy() - 100;
		
		fishingJoyData->setEnergy(afterEnergy);
		m_pPanelLayer->updateEnergy();
		m_pPanelLayer->stopEnergyAnimation();
		//���ż�������ת����Ч
		if(bPlayingChunk)
		{
			auto laserFire = STATIC_DATA_STRING("laser_fire_chunk");
			SoundManager::getInstance()->playEffect(laserFire,0);
		}
	}
	//������ӵ�
	else
	{
		//��ȡ��ǰ�ӵ�����Ŀ
		auto curBulletNum = fishingJoyData->getBulletNumByName(bulletName);
		//����һ
		auto afterBulletNum = curBulletNum - 1;
		//���ٶ�Ӧ���ӵ�����Ŀ
		fishingJoyData->alterSelectedBulletNum(-1);
	}
	//����װ��ʲô �� ���Ľ��
	if(m_pCannon->isBelongNetBulletType(m_pCannon->getType()))
	{
		//��ȡ��Ҫ�Ľ��
		//��ȡ��ǰ����
		int ratio = m_pLevelLayer->getRatio();
		int needGold = fishingJoyData->getGoldByCannon(m_pCannon) * ratio;
		bool bRet = this->subGold(needGold);
		//��ǰ�Ľ�Ҳ�������ֱ���˳�
		if(!bRet)
			return true;

		if (bPlayingChunk)
		{
			auto netGunShoot = STATIC_DATA_STRING("net_gun_shoot_chunk");
			SoundManager::getInstance()->playEffect(netGunShoot,0);
		}
	}
	m_pPanelLayer->updateBulletBtns();
	//���� ���䶯��
	m_pCannon->fire(pos);

	return true;
}

void GameScene::onTouchMoved(Touch*touch,SDL_Event*event)
{
	if(m_pCannon->isCanFire() == false)
		return;

	auto pos = touch->getLocation();
	
	m_pCannon->aimAt(pos);
}

void GameScene::onTouchEnded(Touch*touch,SDL_Event*event)
{
}

void GameScene::fireCallback(const Point&pos)
{
	auto type = m_pCannon->getType();
	auto bornPos = m_pCannon->getPosition();
	auto rotation = m_pCannon->getRotation();
	//����ȷ������λ��
	auto degree = SDL_ANGLE_TO_DEGREE(rotation);
	Size cannonSize = m_pCannon->getContentSize();

	bornPos.x += SDL_sinf(degree)*cannonSize.height/2;
	bornPos.y -= SDL_cosf(degree) * cannonSize.height/2;
	//���伤��
	if(m_pCannon->getType() == Cannon::Type::Laser)//����FishingNetLayer
	{
		m_pFishingEntityLayer->addLaser(bornPos,rotation);
	}
	else
	{
		//��ȡ��ǰѡ�е��ӵ�����
		auto bulletName = FishingJoyData::getInstance()->getSelectedBullet();
		auto netGunBullet = STATIC_DATA_STRING("NetGunBullet");
		auto strengthenBullet = STATIC_DATA_STRING("SterengthenBullet");
		auto fogBullet = STATIC_DATA_STRING("FogBullet");
		auto pearlBullet = STATIC_DATA_STRING("PearlBullet");

		//�����������
		if(bulletName == netGunBullet)
		{
			auto bulletLv = m_pCannon->getNetGunBulletLv();

			m_pBulletLayer->addNetGunBullet(bulletLv,bornPos,pos,rotation);
		}
		//��ǿ��
		else if(bulletName == strengthenBullet)
		{
			m_pBulletLayer->addStrengthenBullet(bornPos,pos,rotation);
		}
		//����
		else if(bulletName == fogBullet)
		{
			m_pBulletLayer->addFogBullet(bornPos,pos,rotation);
		}
		//���鵯
		else if(bulletName == pearlBullet)
		{
			m_pFishingEntityLayer->addPearl(bornPos,rotation);
		}

		this->fireEnd();
	}
}

void GameScene::fireEnd()
{
	m_pCannon->fireEnd();
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	//�Ƿ��л�����
	if(m_pCannon->getType() == Cannon::Type::Laser)
	{
		//�ص���һ��״̬
		auto oldType = m_pCannon->getLastType();

		m_pCannon->setType(oldType);
		
		m_pPanelLayer->showAddAndSubBtn();
		//�Ƿ񲥷���Ч
		if (bPlayingChunk)
		{
			auto sChangeLaser = STATIC_DATA_STRING("change_laser_chunk");
			SoundManager::getInstance()->playEffect(sChangeLaser,0);
		}
	}
	auto fishingJoyData = FishingJoyData::getInstance();
	auto bulletNum = fishingJoyData->getSelectedBulletNum();
	//û�е�ǰ�ڵ������Զ��л��� ��ǹ��
	if(bulletNum <= 0)
	{
		auto netGunBullet = STATIC_DATA_STRING("NetGunBullet");
		//PanleLayer �޸���ͼ ��Ŀ name
		fishingJoyData->setSelectedBullet(netGunBullet);
		m_pPanelLayer->setSelectedBulletBtn(netGunBullet);
	}
}

void GameScene::shootAt(Bullet*bullet,Fish*fish)
{
	switch(bullet->getBulletType())
	{
	case BulletType::NetGunBullet://������
		{
			int lv = static_cast<NetGunBullet*>(bullet)->getLevel();
			this->addFishingNet(lv,bullet->getPosition(),0);
		}break;
	case BulletType::StrengthenBullet://ǿ����
		{
			//���1~7������ todo
			int lv = rand()%7 + 1;
			//���յ�����һ������
			this->addFishingNet(lv,bullet->getPosition(),0);
			//�������һ���ַ���
			auto totalFrames = Director::getInstance()->getTotalFrames();
			auto key = StringUtils::format("strengthen%d",totalFrames);
			//�ص�����
			this->schedule(SDL_CALLBACK_1(GameScene::randomMakeFishingNets,this,lv),key,0.2f,8);
		}break;
	case BulletType::FogBullet://����
		{
			int lv = rand()%7 + 1;
			auto pos = bullet->getPosition();
			//���յ�����һ������
			this->addFishingNet(lv,pos,0);
			
			if(fish == nullptr)
				break;
			//������㷢����ײ������������
			m_pFishingEntityLayer->addFog(fish,pos,bullet->getRotation());
			//�������״̬Ϊ�޵�
			fish->setInvulnerable(true);
		}break;
	}
}

void GameScene::addGold(int number,const Point&pos)
{
	//��ʾ��Ҷ���
	m_pEffectLayer->addGoldAnimation(pos);
	//��ʾƮ����ֵ
	m_pEffectLayer->addFadeScoreAction(number,pos);
	//���ӽ��
	auto fishingJoy = FishingJoyData::getInstance();
	auto gold = fishingJoy->getGold() + number;

	fishingJoy->setGold(gold);
	//����panel
	m_pPanelLayer->updateGold();
	//�Ƿ񲥷���Ч
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	if (bPlayingChunk)
	{
		auto sGetGold = STATIC_DATA_STRING("get_gold_chunk");
		SoundManager::getInstance()->playEffect(sGetGold,0);
	}
}

void GameScene::showWaveAction()
{
	m_pEffectLayer->showWaveAction();
	//�Ƿ񲥷���Ч
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	if (bPlayingChunk)
	{
		auto sWaveComing = STATIC_DATA_STRING("wave_coming_chunk");
		SoundManager::getInstance()->playEffect(sWaveComing,0);
	}
}

void GameScene::addChestLightAnim(const string&name,const Point&pos)
{
	m_pEffectLayer->addChestLightAnim(name,pos);
	//�Ƿ񲥷���Ч��Ч
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	if (bPlayingChunk)
	{
		auto sOpenChest = STATIC_DATA_STRING("open_chest_chunk");
		SoundManager::getInstance()->playEffect(sOpenChest,0);
	}
}

void GameScene::removeChestLightAnim(const string&name)
{
	m_pEffectLayer->removeChestLightAnim(name);
}

bool GameScene::subGold(int number)
{
	auto fishingJoy = FishingJoyData::getInstance();
	auto gold = fishingJoy->getGold() - number;
	bool bRet = false;

	if(gold < 0)
	{
		//todo ��ʾ
		bRet = false;
	}
	else
	{
		fishingJoy->setGold(gold);
		//����panel
		m_pPanelLayer->updateGold();

		bRet = true;
	}
	return true;
}

void GameScene::addEnergy(float delta)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	auto curEnergy = fishingJoyData->getEnergy();
	auto afterEnergy = curEnergy + delta;
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();
	//�����ﵽ100����
	if(afterEnergy >= 100)
	{
		//չʾ������������
		m_pPanelLayer->runEnergyAnimation();
		m_pPanelLayer->hideAddAndSubBtn();
		//�л���������
		m_pCannon->setType(Cannon::Type::Laser);

		if (bPlayingChunk)
		{
			auto sChangeLaser = STATIC_DATA_STRING("change_laser_chunk");
			SoundManager::getInstance()->playEffect(sChangeLaser,0);
		}
	}
	//���õ�ǰ����
	fishingJoyData->setEnergy(afterEnergy);

	m_pPanelLayer->updateEnergy();
}

void GameScene::addExp(float exp)
{
	//��ȡ��ǰ�ȼ����ܾ���ֵ
	auto exps = FishingJoyData::getInstance()->getExpOfCurLevel();
	//��ǰ�ľ���ֵ
	auto curExp = FishingJoyData::getInstance()->getExp();
	auto afterExp = curExp + exp;
	//�Ƿ�����
	if(afterExp >= exps)
	{
		afterExp = afterExp - exps;

		this->levelUp();
	}
	FishingJoyData::getInstance()->setExp(afterExp);

	m_pPanelLayer->updateExp();
	m_pPanelLayer->updateLevel();
}

void GameScene::addBattery(int count,const Point&bornPos)
{
	//�Ȳ��ŵ����Ч
	float delay = m_pEffectLayer->showBatteryMoving(bornPos);
	auto frames = Director::getInstance()->getTotalFrames();
	//���ƶ���ɺ����ӵ�ǰ����
	string key = StringUtils::format("battery%d",frames);
	auto lambda = [this,count](float dt)
	{
		this->addBattery(count);
	};
	this->scheduleOnce(lambda,key,delay);
}

void GameScene::addBattery(int count)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	fishingJoyData->setHalfEnergyNum(fishingJoyData->getHalfEnergyNum() + count);

	m_pPanelLayer->updateHalfEnergyBtn();
}

void GameScene::addPearlBullet(int count,const Point&bornPos)
{
	//�Ȳ�����Ч
	float delay = m_pEffectLayer->showPearlBulletMoving(bornPos);
	auto frames = Director::getInstance()->getTotalFrames();
	//���ƶ���ɺ����ӵ�ǰ����
	string key = StringUtils::format("pearl%d",frames);
	auto lambda = [this,count](float dt)
	{
		this->addPearlBullet(count);
	};
	this->scheduleOnce(lambda,key,delay);
}

void GameScene::addPearlBullet(int count)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	fishingJoyData->setPearlBullet(fishingJoyData->getPearlBullet() + count);
	//ˢ��
	m_pPanelLayer->updateBulletBtns();
}

void GameScene::addFogBullet(int count,const Point&bornPos)
{
	//�Ȳ�����Ч
	float delay = m_pEffectLayer->showFogBulletMoving(bornPos);
	auto frames = Director::getInstance()->getTotalFrames();
	//���ƶ���ɺ����ӵ�ǰ����
	string key = StringUtils::format("fog%d",frames);
	auto lambda = [this,count](float dt)
	{
		this->addFogBullet(count);
	};
	this->scheduleOnce(lambda,key,delay);
}

void GameScene::addFogBullet(int count)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	fishingJoyData->setFogBullet(fishingJoyData->getFogBullet() + count);
	//ˢ��
	m_pPanelLayer->updateBulletBtns();
}

void GameScene::addStrengthenBullet(int count,const Point&bornPos)
{
	//�Ȳ�����Ч
	float delay = m_pEffectLayer->showSterengthenBulletMoving(bornPos);
	auto frames = Director::getInstance()->getTotalFrames();
	//���ƶ���ɺ����ӵ�ǰ����
	string key = StringUtils::format("strength%d",frames);
	auto lambda = [this,count](float dt)
	{
		this->addStrengthenBullet(count);
	};
	this->scheduleOnce(lambda,key,delay);
}

void GameScene::addStrengthenBullet(int count)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	fishingJoyData->setSterengthenBullet(fishingJoyData->getSterengthenBullet() + count);
	//ˢ��
	m_pPanelLayer->updateBulletBtns();
}

void GameScene::addItem(const string&itemName,const Point&bornPos,int number)
{
	//���Ӷ�Ӧ����Ʒ
	if(itemName == "gold")
	{
		this->addGold(number,bornPos);
	}
	else if(itemName == "exp")
	{
		this->addExp(number);
	}
	else if (itemName == "battery")
	{
		this->addBattery(number,bornPos);
	}
	else if(itemName == "FogBullet")
	{
		this->addFogBullet(number,bornPos);
	}
	else if(itemName == "PearlBullet")
	{
		this->addPearlBullet(number,bornPos);
	}
	else if(itemName == "SterengthenBullet")
	{
		this->addStrengthenBullet(number,bornPos);
	}
	else if(itemName == "energy")
	{
		this->addEnergy(number);
	}
}

int GameScene::getRandomFishTideID()const
{
	auto vec = m_pLevelLayer->getFishTideVec();

	int index = rand()%vec.size();

	return vec.at(index);
}

void GameScene::levelUp()
{
	auto lv = FishingJoyData::getInstance()->getLevel();
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	FishingJoyData::getInstance()->setLevel(lv + 1);
	//�������� ͼƬ
	m_pEffectLayer->showLevelUpAction();
	//�����������
	string key = "levelUp";
	this->schedule(SDL_CALLBACK_1(GameScene::randomMakeFishingNets,this,1),key,0.5f,8);

	if (bPlayingChunk)
	{
		auto sLevelUp = STATIC_DATA_STRING("level_up_chunk");
		SoundManager::getInstance()->playEffect(sLevelUp,0);
	}
}

void GameScene::randomMakeFishingNets(float dt,int lv)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float x = RANDOM_0_1() * visibleSize.width;
	float y = RANDOM_0_1() * visibleSize.height;
	
	this->addFishingNet(lv,Point(x,y),0);
}

void GameScene::fishCaughtCallback(Fish*fish)
{
	//�㱻��׽
	//��ȡ��ǰ����
	int ratio = m_pLevelLayer->getRatio();
	auto fishID = fish->getID();
	//��ӽ��
	auto gold = STATIC_FISH_GOLD(fishID);
	this->addGold(gold * ratio,fish->getPosition());

	//���ݵ�ǰ�����id���ж��Ƿ��б������
	auto&fishRewardVec = StaticData::getInstance()->getFishRewards();
	auto iter = find_if(fishRewardVec.begin(),fishRewardVec.end(),[fishID](const FishReward&fishReward)
	{
		return fishReward.fishID == fishID;
	});
	//�Ƿ��ǳ��ֱ���
	if(iter == fishRewardVec.end())
	{
		return;
	}
	auto &fishReward = *iter;
	auto itemName = fishReward.type;
	auto number = fishReward.number;
	auto scope = fishReward.scope;

	if(itemName == "chest")
	{
		ui::Button*btn = ui::Button::create("chest.png");

		btn->setPosition(fish->getPosition());
		btn->setSwallowTouches(true);
		btn->addClickEventListener(SDL_CALLBACK_1(GameScene::showChestCallback,this));
		
		this->addChild(btn);
	}
	else//������������ ��ӳɹ����ж�
	{
		float success = RANDOM_0_1();

		if(success < scope)
			this->addItem(itemName,fish->getPosition(),number);
	}

}

void GameScene::showChestCallback(Object*sender)
{
	if(!m_pRewardLayer->isClickChest())
		return;

	//�Ƴ������ť
	Node*node = static_cast<Node*>(sender);
	node->removeFromParent();

	this->gamePause();

	m_pRewardLayer->showChest();

}

void GameScene::addFishingNet(int lv,const Point&pos,float rotation)
{
	m_pFishingEntityLayer->addFishingNet(lv,pos,rotation);

	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();

	if (bPlayingChunk)
	{
		auto sFishingNet = STATIC_DATA_STRING("fishing_net_show_chunk");
		SoundManager::getInstance()->playEffect(sFishingNet,0);
	}
}

vector<int>& GameScene::getShownFishIdVec()
{
	return m_pLevelLayer->getShownFishIdVec();
}

vector<float>& GameScene::getStartFishStartTimeVec()
{
	return m_pLevelLayer->getStartFishStartTimeVec();
}

void GameScene::showGroupComeMoving()
{
	m_pEffectLayer->showGroupComeMoving();
}