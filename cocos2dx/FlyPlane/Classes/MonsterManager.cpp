#include "MonsterManager.h"
#include "CsvUtil.h"
#include "PlaneAction.h"
#include "SaveData.h"

MonsterManager::MonsterManager()
{
	m_player = NULL;
	m_bulletMgr = NULL;
}
MonsterManager::~MonsterManager()
{
}
bool MonsterManager::init()
{
	//获取随机数
	 timeval psv;
	gettimeofday(&psv,NULL);
	unsigned int tran = psv.tv_sec * 1000 + psv.tv_usec/1000;
	srand(tran);

	createMonsters();
	this->scheduleUpdate();

	return true;
}
void MonsterManager::createMonsters()
{
	//load
	const char*sPath = "Plane.csv";
	CsvUtil::getInstance()->loadFile(sPath);

	//创建Small Plane quick 4 
	//获取ID
	std::string ID = std::string(CsvUtil::getInstance()->getValue(2,0,sPath).asString());
//	log(ID.c_str());
	//获取HP
	int HP = CsvUtil::getInstance()->getValue(2,2,sPath).asInt();
//	log(Value(HP).asString().c_str());
	//获取速度
	int speed = CsvUtil::getInstance()->getValue(2,3,sPath).asInt();
//	log(Value(speed).asString().c_str());
	//Sprite*sprite = Sprite::createWithSpriteFrameName("Small Plane.png");
	//log("go to ");

	for(int i =0;i < 8;i++)
	{
		Monster*monster = Monster::create();

		monster->bindSprite(Sprite::createWithSpriteFrameName("Small Plane-dead1.png"));
		monster->reset();
		monster->setID(ID);
		monster->setHitPoints(HP);
		monster->setSpeed(speed);

		this->addChild(monster);
		this->m_monsterArr.pushBack(monster);
	}// end for
	//创建Middle Plane
	//获取ID
	ID = std::string(CsvUtil::getInstance()->getValue(5,0,sPath).asString());
//	log(ID.c_str());
	//获取HP
	HP = CsvUtil::getInstance()->getValue(5,1,sPath).asInt();
//	log(Value(HP).asString().c_str());
	//获取速度
	speed = CsvUtil::getInstance()->getValue(5,3,sPath).asInt();
//	log(Value(speed).asString().c_str());
	//Sprite*sprite = Sprite::createWithSpriteFrameName("Small Plane.png");
	//log("go to ");

	for(int i =0;i < MAX_MONSTER - 8;i++)
	{
		Monster*monster = Monster::create();

		monster->bindSprite(Sprite::createWithSpriteFrameName("Middle Plane-dead1.png"));
		monster->reset();
		monster->setID(ID);
		monster->setHitPoints(HP);
		monster->setSpeed(speed);

		this->addChild(monster);
		this->m_monsterArr.pushBack(monster);
	}// end for

}
void MonsterManager::update(float dt)
{
	//
	for(auto monster : m_monsterArr)
	{
		if(monster->isAlive())
		{ 
			if(monster->getHitPoints() > 0)
			monster->setPositionY(monster->getPositionY() - monster->getSpeed());
			//如果敌机越界
			if(monster->getPositionY() <= 0)
				monster->hide();
			//如果敌机和我方飞机碰撞(后续测试)
			else if(m_player != NULL&&monster->isCollided(m_player))
			{
				if(monster->getHitPoints() - 1 == 0)
				{
				monster->setHitPoints(0);
				if(monster->getID() == std::string("Small Plane"))
					monster->run(PlaneAction::getInstance()->getActionByString("Small Plane-dead"));
				else if(monster->getID() == std::string("Middle Plane"))
					monster->run(PlaneAction::getInstance()->getActionByString("Small Plane-dead"));

				}
				else
					monster->setHitPoints(monster->getHitPoints() - 1);
				//monster->hide();
			}
			//如果敌机和子弹碰撞
			else if(m_bulletMgr != NULL&&m_bulletMgr->detecteCollided(monster) == true)
			{
				//monster->setHitPoints(monster->getHitPoints() - 1);
				//log(Value(monster->getID()).asString().c_str());
				//log(Value(monster->getHitPoints()).asString().c_str());

				if(monster->getHitPoints() - 1 == 0)
				{
					//如果为Small Plane
					if(monster->getID() == std::string("Small Plane"))
					{
						SaveData::getInstance()->setScore(SaveData::getInstance()->getScore() + 50);
						monster->setHitPoints(0);
						monster->run(PlaneAction::getInstance()->getActionByString("Small Plane-dead"));
					}
					else if(monster->getID() == std::string("Middle Plane"))
					{
						//log(Value(monster->getHitPoints()).asString().c_str());
					    SaveData::getInstance()->setScore(SaveData::getInstance()->getScore() + 100);
						monster->setHitPoints(0);
						monster->run(PlaneAction::getInstance()->getActionByString("Middle Plane-dead"));
					}
				}
				else
					monster->setHitPoints(monster->getHitPoints() - 1);
			}
		}
		else
			monster->show();
	}// end for
}
void MonsterManager::bindPlayer(Player*iPlayer)
{
	this->m_player = iPlayer;
}
void MonsterManager::bindBulletMgr(BulletManager*bulletManager)
{
	this->m_bulletMgr = bulletManager;
}