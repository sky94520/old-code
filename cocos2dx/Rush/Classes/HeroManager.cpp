#include "HeroManager.h"
#include "PosLoadUtil.h"
#include "CannonsHero.h"
HeroManager::HeroManager()
{
}
HeroManager::~HeroManager()
{
}
HeroManager*HeroManager::createWithLevel(int nCurLevel)
{
	HeroManager*manager = new HeroManager();
	if(manager && manager->initWithLevel(nCurLevel))
	{
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}
bool HeroManager::initWithLevel(int nCurLevel)
{
	std::string towerFileName = StringUtils::format("tollgate/towerPos_level_%d.plist",nCurLevel);
	auto towerList = PosLoadUtil::getInstance()->loadPosWithFile
		(towerFileName.c_str(),PosType::kTowerPos,this,nCurLevel,false);
	//添加坑
	m_towerPosList.pushBack(towerList);
	//创建炮台
	createTowerBorder(nCurLevel);
	//添加触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*touch,Event*event)
	{
		return true;
	};
	listener->onTouchEnded =[&](Touch*touch,Event*event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		//获取被单击的塔的坐标
		auto clickBorder = findClickTowerBorder(pos);
		if(clickBorder == NULL)
			return;
		//当前没有英雄，添加英雄
		if(clickBorder->getHero() == NULL)
		{
			Hero*hero = CannonsHero::createFromCsvFileByID(6);
			hero->setPosition(clickBorder->getPosition());
			this->addChild(hero,TOWER_LAYER_LVL);
			//绑定到炮台
			clickBorder->bindHero(hero);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void HeroManager::createTowerBorder(int nCurBorder)
{
	for(auto pos : m_towerPosList)
	{
		TowerBorder*border = TowerBorder::create();
		border->setPosition(pos->getPos());
		this->addChild(border);
		m_towerBorderList.pushBack(border);
	}
}
void HeroManager::createTowerPos(Point pos)
{
	TowerPos*towerPos = TowerPos::create(pos,false);
	this->addChild(towerPos,TOWER_POS_LAYER_LVL);
	m_towerPosList.pushBack(towerPos);
}
TowerBorder*HeroManager::findClickTowerBorder(Point pos)
{
	for(auto tBorder : m_towerBorderList)
		if(tBorder->isClickMe(pos))
			return tBorder;
	return NULL;
}
void HeroManager::logic(float dt,Vector<Monster*>& monsterList)
{
	for(auto towerBorder:m_towerBorderList)
	{
		auto hero = towerBorder->getHero();
		if(hero !=	nullptr)
			hero->logic(dt,monsterList);
	}
}