#include "TollgateMapLayer.h"
#include "MonsterManager.h"
TollgateMapLayer::TollgateMapLayer():
	m_nCurLevel(1),m_pHeroMgr(NULL)
{
}
TollgateMapLayer::~TollgateMapLayer()
{
}
bool TollgateMapLayer::init()
{
	if(!Layer::init())
		return false;
	loadConfig();

	return true;
}
Scene*TollgateMapLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateMapLayer::create();
	scene->addChild(layer);
	return scene;
}
void TollgateMapLayer::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite*bg = Sprite::create("tollgate/level_bg_1.png");
	bg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg);

	m_pHeroMgr = HeroManager::createWithLevel(m_nCurLevel);
	this->addChild(m_pHeroMgr,HERO_LAYER_LVL);

	 m_pMonsterMgr = MonsterManager::createWithLevel(m_nCurLevel);
	this->addChild(m_pMonsterMgr,MONSTER_LAYER_LVL);
	//execute
	this->schedule(schedule_selector(TollgateMapLayer::logic));
}
void TollgateMapLayer::logic(float dt)
{
	m_pHeroMgr->logic(dt,m_pMonsterMgr->getMonsterList());
}