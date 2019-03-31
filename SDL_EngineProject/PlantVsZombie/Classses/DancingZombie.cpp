#include "DancingZombie.h"
#include "BackupDancer.h"
#include "NameDef.h"

DancingZombie::DancingZombie()
	:m_state(State::None),m_bDying(false)
	,m_bDirty(false),m_elapsed(0.f)
	,m_duration(0.f)
{
	memset(m_innerZombies,0,sizeof(m_innerZombies));
}

DancingZombie::~DancingZombie()
{
	for (unsigned int i = 0;i < 4;i++)
	{
		auto zombie = m_innerZombies[i];

		if (zombie != nullptr)
		{
			SDL_SAFE_RELEASE_NULL(zombie);
		}
	}
}

DancingZombie* DancingZombie::create(const string& zombieName)
{
	auto zombie = new DancingZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool DancingZombie::init(const string& zombieName)
{
	this->setZombieName(zombieName);
	//获取站立状态贴图
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	//运行站立动画
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	
	return true;
}

void DancingZombie::updateAlive(float dt)
{
	//自动转入SlidingStep
	if (m_state == State::None)
	{
		this->changeState(State::SlidingStep);
	}
	else if (m_state == State::Walk)
	{
		this->updateWalkState(dt);
	}
	else if (m_state == State::Dancing)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->changeState(State::Walk);
		}
	}
	else if (m_state == State::SlidingStep)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->changeState(State::Walk);
		}
	}
	//召唤状态
	else if (m_state == State::Summon)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			//this->summon();

			m_elapsed = 0.f;
			this->changeState(State::Walk);
		}
	}
	else if (m_state == State::Attack)
	{
		if (m_pAim == nullptr || m_pAim->isDead())
		{
			this->clearAim();
			this->changeState(State::Walk);
		}
		else
		{
			this->eatAim(dt);
		}
	}
}
bool DancingZombie::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::SlidingStep)
		return true;

	return false;
}

void DancingZombie::onNormalDead()
{
	m_bDying = true;
	m_bDirty = true;
}
void DancingZombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state && !m_bDirty)
		return ;

	m_bDirty = false;
	m_state = state;

	string animationName;

	if (m_state == State::Walk)
	{
		if (!m_bDying)
			animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sLostHeadWalk",m_zombieName.c_str());
		//行走几秒
		m_duration = 3.f;
	}
	else if (m_state == State::Attack)
	{
		if (!m_bDying)
			animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sLostHeadAttack",m_zombieName.c_str());
	}
	else if (m_state == State::Dancing)
	{
		if (!m_bDying)
			animationName = StringUtils::format("%sDancing",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sLostHeadDancing",m_zombieName.c_str());
		//跳舞几秒
		m_duration = 2.f;
	}
	else if (m_state == State::Summon)
	{
		if (!m_bDying)
			animationName = StringUtils::format("%sSummon",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sLostHeadSummon",m_zombieName.c_str());

		m_duration = 2.f;
	}
	else if (m_state == State::SlidingStep)
	{
		m_duration = 2.f;
	}
	if (animationName.empty())
	{
		return ;
	}

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void DancingZombie::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/4.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getLocalZOrder(),false);

}

void DancingZombie::updateWalkState(float dt)
{
	//召唤物死亡 转入召唤状态
	if (isDeadForInnerZombie())
	{
		m_elapsed = 0.f;

		this->changeState(State::Summon);
		//召唤
		this->scheduleOnce(schedule_selector(DancingZombie::summon),m_duration/2);
	}
	else if (m_pAim != nullptr)
	{
		this->changeState(State::Attack);
		m_elapsed = 0.f;
	}
	else
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->changeState(State::SlidingStep);
		}
	}
}

void DancingZombie::summon(float)
{
	auto pos = this->getPosition();
	auto size = Size(76,82);
	auto row = this->getRow();
	bool bConfused = this->isConfused();

	for (int i = 0; i < 4;i++)
	{
		auto innerZombie = m_innerZombies[i];
		//内部僵尸不存在或者死亡
		if (innerZombie == nullptr || innerZombie->isDead())
		{
			auto curPos = pos;
			int curRow = row;

			SDL_SAFE_RELEASE_NULL(innerZombie);
			//上
			if (i == 0)
			{
				curPos.y -= size.height;
				curRow -= 1;
			}
			//下
			else if (i == 2)
			{
				curPos.y += size.height;
				curRow += 1;
			}
			//左
			else if (i == 1)
			{
				curPos.x -= size.width;
			}
			//右
			else if (i == 3)
			{
				curPos.x += size.width;
			}
			//创建僵尸
			m_innerZombies[i] = static_cast<BackupDancer*>(m_pDelegate->makeZombie(BACKUP_ZOMBIE_NAME,curPos,curRow,bConfused));
			//保持引用
			SDL_SAFE_RETAIN(m_innerZombies[i]);
		}
	}
}

bool DancingZombie::isDeadForInnerZombie()
{
	for (unsigned int i = 0; i < 4;i++)
	{
		auto zombie = m_innerZombies[i];

		if (zombie == nullptr || zombie->isDead())
		{
			return true;
		}
	}
	return false;
}