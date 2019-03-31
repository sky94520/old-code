#include "MonsterManager.h"
#include "PosLoadUtil.h"
#include "Monster.h"
#include "MonsterPos.h"
//
#include "Global.h"
MonsterManager::MonsterManager():
	m_fShowTimeCount(0.f)
{
	Global::getInstance()->_monsterManager = this;
}
MonsterManager::~MonsterManager()
{
}
MonsterManager*MonsterManager::createWithLevel(int nLevel)
{
	MonsterManager*monsterMgr = new MonsterManager();
	if(monsterMgr && monsterMgr->initWithLevel(nLevel))
		monsterMgr->autorelease();
	else
		CC_SAFE_DELETE(monsterMgr);
	return monsterMgr;
}
bool MonsterManager::initWithLevel(int nLevel)
{
	//创建怪物
	createMonsters(nLevel);
	return true;
}
void MonsterManager::createMonsters(int nCurLevel)
{
	//加载怪物坐标
	std::string sMonsterPosPath = StringUtils::format("tollgate/monsterPos_level_%d.plist",nCurLevel);
	auto posList = PosLoadUtil::getInstance()->loadPosWithFile(sMonsterPosPath.c_str(),
		PosType::kMonsterPos,this,10,false);
	m_monsterPosList.pushBack(posList);
	//读取配置文件
	std::string sMonsterConfPath = StringUtils::format("tollgate/monster_level_%d.plist",nCurLevel);
	ValueMap fileDataMap = FileUtils::getInstance()->getValueMapFromFile(sMonsterConfPath.c_str());
	int size = fileDataMap.size();
	for(int i=1;i<=size;i++)
	{
		Value value = fileDataMap.at(StringUtils::toString(i));
		ValueMap data = value.asValueMap();
		//从怪物出场配置文件中读取怪物ID和出场时间，保存所有怪物到未出场列表
		int id = data["id"].asInt();
		float fShowTime = data["showTime"].asFloat();
		//创建怪物
		Monster*monster = Monster::createFromCsvFileByID(id);
		monster->setShowTime(fShowTime);
		monster->setVisible(false);

		//保存
		m_monsterList.pushBack(monster);
		//设置localZOrder，这里以1000为准
		monster->setLocalZOrder(1000 - i);
		m_notShowMonsterList.pushBack(monster);
		this->addChild(monster);
	}
	//开始检测是否有新怪物入场
	this->schedule(schedule_selector(MonsterManager::showMonster));
}
void MonsterManager::showMonster(float dt)
{
	int nNotShowMonsterCount = m_notShowMonsterList.size();
	if(nNotShowMonsterCount > 0)
		m_fShowTimeCount += dt;
	//获取怪物的起始点
	auto monsterStartPos = getMonsterStartPos();

	Vector<Monster*> monsterWantDelete;
	for(auto monster : m_notShowMonsterList)
	{
		if(m_fShowTimeCount >= monster->getShowTime())
		{
			monsterWantDelete.pushBack(monster);

			monster->setVisible(true);
			//monster->setPosition(monsterStartPos->getPos());
			//让怪物按照指定坐标行走
			monster->moveByPosList(m_monsterPosList);
		}
	}
	//删除已经出场的怪物
	for(auto monster : monsterWantDelete)
		m_notShowMonsterList.eraseObject(monster);
}
int MonsterManager::getNotShowMonsterCount()
{
	return m_notShowMonsterList.size();
}
MonsterPos*MonsterManager::getMonsterStartPos()
{
	return (MonsterPos*)m_monsterPosList.at(0);
}
MonsterPos*MonsterManager::getMonsterEndPos()
{
	return (MonsterPos*)m_monsterPosList.at(m_monsterPosList.size()-1);
}