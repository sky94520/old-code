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
	//删除单例类
	FishingJoyData::getInstance()->purge();
	SDL_SAFE_RELEASE(m_pMenuLayer);
}
bool GameScene::init()
{
	//背景层
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer);
	//鱼层
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	this->scheduleUpdate();
	//炮台层
	m_pCannonLayer = CannonLayer::create();
	this->addChild(m_pCannonLayer);
	//子弹选择层
	m_pChooseBulletLayer = ChooseBulletLayer::create();
	m_pChooseBulletLayer->setDelegate(this);
	this->addChild(m_pChooseBulletLayer);
	//状态层
	m_pPanelLayer = PanelLayer::create();
	m_pPanelLayer->setDelegate(this);
	this->addChild(m_pPanelLayer);
	//菜单层
	m_pMenuLayer = MenuLayer::create();
	m_pMenuLayer->setDelegate(this);
	m_pMenuLayer->retain();
	//触摸层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//开始背景音乐
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
	//检测子弹是否发射
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
	//获取鱼
	auto fishes = m_pFishLayer->getFishes();
	//获取当前子弹的矩形位置
	auto weapon = m_pCannonLayer->getWeapon();
	Rect collisionRect = weapon->getBulletCollisionRect();
	//判断
	for(int i=0;i<fishes.size();i++)
	{
		auto fish = fishes.at(i);
		Rect rect = fish->getBoundingBox();
		rect.origin = fish->getWorldPosition();
		if(fish->isAlive() && collisionRect.intersectsRect(rect))
		{
			//子弹消失,渔网出现
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
	//获取随机数
	float random = RANDOM_0_1();
	for(int i=0;i<fishes.size();i++)
	{
		auto fish = fishes.at(i);
		//如果鱼已经被捕捉，则不处理
		if(fish->isAlive() == false)
			continue;
		Rect rect = fish->getBoundingBox();
		rect.origin = fish->getWorldPosition();
		//是否捕捉得到
		auto score = static_cast<int>(fabs((float)fish->getScore()));

		float success = weapon->getCannonLevel() * (1 - 0.1)/score;
		if(collisionRect.intersectsRect(rect) && random < success)
		{
			//音效
			SoundManager::getInstance()->playEffect("bgm_coin_01.mp3",0);
			fish->catched();
		}
	}
}
void GameScene::pause()
{
	//添加菜单层
	this->addChild(m_pMenuLayer);
	//其他层不可互动
	m_pTouchLayer->onExit();
	m_pPanelLayer->onExit();
	m_pFishLayer->onExit();

	this->unscheduleUpdate();
}
void GameScene::resume()
{
	m_pMenuLayer->removeFromParent();
	//其他层可互动
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
	//如果子弹已经发射，则不能再次发射
	if(weapon->isShooting())
		return ;
	//获取当前金币数量
	int goldCount = FishingJoyData::getInstance()->getGold();
	//获取武器等级
	auto cannonType = weapon->getCannonType();
	//判断条件，在以后扩展
	//减少相应的弹药量
	bool bRet = m_pChooseBulletLayer->subBulletCount();
	if(bRet && goldCount - cannonType)
	{
		Value sub = Value(cannonType);
		FishingJoyData::getInstance()->alterGold(sub,false);//减少金币
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