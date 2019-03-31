#include "ZombieLayer.h"
#include "ZombieFactory.h"
#include "NameDef.h"
#include "ZombieBase.h"
#include "LevelLayer.h"
#include "MoveBehavior.h"
#include "Plant.h"
#include "ConeheadZombie.h"
#include "PaperZombie.h"
#include "PoleVaultingZombie.h"
#include "BucketheadZombie.h"
#include "Character.h"

ZombieLayer::ZombieLayer()
	:m_pZombieFactory(nullptr),m_pDelegate(nullptr)
{
}

ZombieLayer::~ZombieLayer()
{
	SDL_SAFE_RELEASE_NULL(m_pZombieFactory);
}

bool ZombieLayer::init()
{
	m_pZombieFactory = ZombieFactory::create();
	m_pZombieFactory->retain();

	return true;
}

void ZombieLayer::update(float dt)
{
	for (auto mapIter = m_zombies.begin(); mapIter != m_zombies.end();mapIter++)
	{
		auto &vec = mapIter->second;
		//每次都根据x轴进行排序
		sort(vec.begin(),vec.end(),zombieComparisonLess);

		for (auto vecIter = vec.begin();vecIter != vec.end();)
		{
			auto zombie = *vecIter;
			//当前僵尸已经死亡
			if (zombie->isDead())
			{
				vecIter = vec.erase(vecIter);
				zombie->removeFromParent();
			}
			else
			{
				this->zombieUpdate(zombie,dt);
				vecIter++;
			}
		}
	}
}

ZombieBase*ZombieLayer::makeZombie(const string&zombieName,int row)
{
	ZombieBase* zombie = m_pZombieFactory->makeZombie(zombieName);

	zombie->setRow(row);
	m_zombies[row].push_back(zombie);

	return zombie;
}

void ZombieLayer::setZombiePaths(const vector<ZombiePath*>& paths)
{
	//先清除原有路径
	m_zombiePaths.clear();

	for (auto path : paths)
	{
		m_zombiePaths.push_back(path);
	}
}

void ZombieLayer::setDelegate(ZombieLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

vector<ZombieBase*> ZombieLayer::getZombiesOfRow(int row)
{
	auto it = m_zombies.find(row);

	if (it != m_zombies.end())
	{
		auto vec = it->second;
		return vec;
	}
	return vector<ZombieBase*>();
}

map<int,vector<ZombieBase*> >& ZombieLayer::getZombies()
{
	return m_zombies;
}

bool ZombieLayer::removeZombie(ZombieBase*zombie,bool cleanup)
{
	auto row = zombie->getRow();
	//获取僵尸所在行的vector
	auto& vec = m_zombies.at(row);
	//在容器中进行查找
	auto it = find(vec.cbegin(),vec.cend(),zombie);

	if (it != vec.cend())
	{
		vec.erase(it);

		//从父亲中移除自己
		if (cleanup)
		{
			zombie->removeFromParent();
		}

		return true;
	}
	return false;
}

void ZombieLayer::zombieUpdate(ZombieBase*zombie,float dt)
{
	//僵尸死亡或者当前已经有目标，则不进行更新
	if (zombie->isDying())
	{
		return;
	}
	auto terrain = m_pDelegate->findTerrainOfZombieCollision(zombie);
	//是否发现目标
	bool bFoundTarget = false;

	if (terrain != nullptr)
	{
		auto plant = m_pDelegate->getTopPlantOfAttack(terrain);

		if (plant != nullptr)
		{
			bFoundTarget = true;

			zombie->setAim(plant);
		}
	}
	//没发现目标，则clear 目标
	if (!bFoundTarget)
	{
		auto row = zombie->getRow();
		Direction dir = zombie->getDir();
		auto rect = zombie->getCollisionBoundingBox();
		//进行检测
		auto target = m_pDelegate->findFirsCollidedMovableCharacterOfRow(row,dir,rect);

		if (target != nullptr)
			zombie->setAim(target);
		else
			zombie->clearAim();
	}
	zombie->update(dt);
}

bool ZombieLayer::zombieComparisonLess(ZombieBase* n1, ZombieBase* n2)
{
	return n1->getPositionX() < n2->getPositionX();
}