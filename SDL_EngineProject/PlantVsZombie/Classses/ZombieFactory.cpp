#include "ZombieFactory.h"
#include "Zombie.h"
#include "HpBar.h"
#include "ConeheadZombie.h"
#include "NameDef.h"
#include "Garnishry.h"
#include "PaperZombie.h"
#include "PoleVaultingZombie.h"
#include "BucketheadZombie.h"
#include "FootballZombie.h"
#include "ScreenDoorZombie.h"
#include "BackupDancer.h"
#include "DancingZombie.h"
#include "MoveBehavior.h"
#include "StaticData.h"

ZombieFactory::ZombieFactory()
{
}

ZombieFactory::~ZombieFactory()
{
}

bool ZombieFactory::init()
{
	return true;
}

ZombieBase* ZombieFactory::makeZombie(const string& zombieName)
{
	auto zombieStruct = StaticData::getInstance()->getZombieStructForName(zombieName);

	if (zombieStruct == nullptr)
		return nullptr;

	ZombieBase*zombie = nullptr;
	MoveBehavior*moveBehavior = nullptr;
	Point *hpBarPos = nullptr;
	//对应生成僵尸，同时设置一些属性
	if (zombieName == ZOMBIE_NAME)
	{
		zombie = Zombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		zombie->setDir(Direction::Left);
	}
	else if (zombieName == CONEHEADZOMBIE_NAME)
	{
		auto temp = ConeheadZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		temp->setDir(Direction::Left);
		//设置额外属性
		temp->setNextZombieName(ZOMBIE_NAME);

		zombie = temp;
	}
	else if (zombieName == PAPERZOMBIE_NAME)
	{
		zombie = PaperZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		zombie->setDir(Direction::Left);
	}
	else if (zombieName == POLEVAULTINGZOMBIE_NAME)
	{
		zombie = PoleVaultingZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();
		//对血条的位置进行调整
		Size size = zombie->getContentSize();
		Rect rect = zombie->getSprite()->getSpriteFrameRect();

		hpBarPos = new Point(size.width*0.75f,rect.origin.y);
		
		zombie->setDir(Direction::Left);

	}
	else if (zombieName == BUCKETHEADZOMBIE_NAME)
	{
		auto temp = BucketheadZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		temp->setDir(Direction::Left);
		temp->setNextZombieName(ZOMBIE_NAME);

		zombie = temp;
	}
	else if (zombieName == FOOTBALL_ZOMBIE_NAME)
	{
		auto temp = FootballZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		temp->setDir(Direction::Left);

		zombie = temp;
	}
	else if (zombieName == SCREEN_DOOR_ZOMBIE_NAME)
	{
		auto temp = ScreenDoorZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		temp->setDir(Direction::Left);
		temp->setNextZombieName(ZOMBIE_NAME);

		zombie = temp;
	}
	else if (zombieName == BACKUP_ZOMBIE_NAME)
	{
		zombie = BackupDancer::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		zombie->setDir(Direction::Left);
	}
	else if (zombieName == DANCING_ZOMBIE_NAME)
	{
		zombie = DancingZombie::create(zombieName);
		moveBehavior = new LineMoveBehavior();

		zombie->setDir(Direction::Left);
	}
	//设置基础属性
	zombie->setDead(false);
	zombie->setCriticalPoint(70.f);
	zombie->setColdDownTime(1.f);
	zombie->setDamage(100);

	zombie->setHitPoint(zombieStruct->hp);
	zombie->setBaseSpeed(zombieStruct->speed);
	zombie->setVertexBox(zombieStruct->rect);
	//绑定对应的饰品
	this->bindGarnihryForZombie(zombie,zombieStruct->garnishry);
	//绑定血量条
	if (zombie != nullptr)
	{
		//设置行走类型
		zombie->setMoveBehavior(moveBehavior);
		//设置血条
		if (hpBarPos != nullptr)
		{
			this->bindHpBarForZombie(zombie,*hpBarPos);

			delete hpBarPos;
		}
		else
		{
			this->bindHpBarForZombie(zombie);
		}
	}
	return zombie;
}

Point ZombieFactory::bindHpBarForZombie(ZombieBase*zombie)
{
	//设置血条位置
	auto rect = zombie->getSprite()->getSpriteFrameRect();

	Point pos = Point(rect.origin.x + rect.size.width,rect.origin.y);

	return this->bindHpBarForZombie(zombie,pos);
}

Point ZombieFactory::bindHpBarForZombie(ZombieBase*zombie,const Point&pos)
{
	float hp = (float)zombie->getHitPoint();
	HpBar*hpBar = HpBar::create("hpBar1.png","hpBarBG.png",hp);

	hpBar->setPosition(pos);

	zombie->bindHpBar(hpBar);

	return pos;
}

void ZombieFactory::bindGarnihryForZombie(ZombieBase*zombie,const string&garnishryName)
{
	//饰品名为空或者为null，不去绑定
	if (garnishryName.empty() || garnishryName == "null")
		return;
	Garnishry*garnishry = nullptr;
	Point pos;

	if (garnishryName == "cone")
	{
		//设置装饰品
		garnishry = Conehead::create(370);
		auto size = garnishry->getContentSize();
		//设置血条位置
		pos = this->bindHpBarForZombie(zombie);
		pos.y -= size.height;
	}
	else if (garnishryName == "paper")
	{
		garnishry = Paper::create(150);
		auto rect = zombie->getSprite()->getSpriteFrameRect();
		auto paperSize = garnishry->getContentSize();

		pos = Point(rect.origin.x + rect.size.width,rect.origin.y - paperSize.height);
	}
	else if (garnishryName == "pole")
	{
		garnishry = Pole::create();
	}
	else if (garnishryName == "bucket")
	{
		garnishry = Bucket::create(1100);
		auto size = garnishry->getContentSize();
		auto rect = zombie->getSprite()->getSpriteFrameRect();
		pos = Point(rect.origin.x + rect.size.width,rect.origin.y - size.height);
	}
	else if (garnishryName == "helmet")
	{
		garnishry = Helmet::create(1400);
		auto size = garnishry->getContentSize();
		auto rect = zombie->getSprite()->getSpriteFrameRect();
		pos = Point(rect.origin.x + rect.size.width,rect.origin.y - size.height);
	}
	else if (garnishryName == "screendoor")
	{
		garnishry = ScreenDoor::create(1100);
		auto size = garnishry->getContentSize();
		auto rect = zombie->getSprite()->getSpriteFrameRect();
		pos = Point(rect.origin.x + rect.size.width,rect.origin.y - size.height);
	}
	zombie->addGarnishry(garnishry);

	garnishry->setPosition(pos);
	garnishry->setGarnishryName(garnishryName);
}