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
	//��������
	createMonsters(nLevel);
	return true;
}
void MonsterManager::createMonsters(int nCurLevel)
{
	//���ع�������
	std::string sMonsterPosPath = StringUtils::format("tollgate/monsterPos_level_%d.plist",nCurLevel);
	auto posList = PosLoadUtil::getInstance()->loadPosWithFile(sMonsterPosPath.c_str(),
		PosType::kMonsterPos,this,10,false);
	m_monsterPosList.pushBack(posList);
	//��ȡ�����ļ�
	std::string sMonsterConfPath = StringUtils::format("tollgate/monster_level_%d.plist",nCurLevel);
	ValueMap fileDataMap = FileUtils::getInstance()->getValueMapFromFile(sMonsterConfPath.c_str());
	int size = fileDataMap.size();
	for(int i=1;i<=size;i++)
	{
		Value value = fileDataMap.at(StringUtils::toString(i));
		ValueMap data = value.asValueMap();
		//�ӹ�����������ļ��ж�ȡ����ID�ͳ���ʱ�䣬�������й��ﵽδ�����б�
		int id = data["id"].asInt();
		float fShowTime = data["showTime"].asFloat();
		//��������
		Monster*monster = Monster::createFromCsvFileByID(id);
		monster->setShowTime(fShowTime);
		monster->setVisible(false);

		//����
		m_monsterList.pushBack(monster);
		//����localZOrder��������1000Ϊ׼
		monster->setLocalZOrder(1000 - i);
		m_notShowMonsterList.pushBack(monster);
		this->addChild(monster);
	}
	//��ʼ����Ƿ����¹����볡
	this->schedule(schedule_selector(MonsterManager::showMonster));
}
void MonsterManager::showMonster(float dt)
{
	int nNotShowMonsterCount = m_notShowMonsterList.size();
	if(nNotShowMonsterCount > 0)
		m_fShowTimeCount += dt;
	//��ȡ�������ʼ��
	auto monsterStartPos = getMonsterStartPos();

	Vector<Monster*> monsterWantDelete;
	for(auto monster : m_notShowMonsterList)
	{
		if(m_fShowTimeCount >= monster->getShowTime())
		{
			monsterWantDelete.pushBack(monster);

			monster->setVisible(true);
			//monster->setPosition(monsterStartPos->getPos());
			//�ù��ﰴ��ָ����������
			monster->moveByPosList(m_monsterPosList);
		}
	}
	//ɾ���Ѿ������Ĺ���
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