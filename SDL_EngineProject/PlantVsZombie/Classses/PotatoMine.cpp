#include "PotatoMine.h"
#include "StaticData.h"
#include "ZombieBase.h"

PotatoMine::PotatoMine()
	:m_state(State::Ready),m_elapsed(0.f)
	,m_nDamage(0),m_duration(0.f)
{
}

PotatoMine::~PotatoMine()
{
}

PotatoMine*PotatoMine::create(const string&plantName)
{
	auto plant = new PotatoMine();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool PotatoMine::init(const string&plantName)
{
	this->setPlantName(plantName);
	//设置贴图
	auto spriteName = STATIC_DATA_STRING("potato_mine_not_ready_sprite_name");
	
	this->bindSpriteWithSpriteFrameName(spriteName);

	return true;
}

void PotatoMine::updateHook(float dt)
{
	//当前处于准备阶段
	if (m_state == State::Ready)
	{
		m_elapsed += dt;
		//到达破土时间，破土
		if (m_elapsed >= this->getColdDownTime())
		{
			this->readySuccess();

			m_elapsed = 0.f;
			this->changeState(State::Rising);
			//开启遮罩
			this->setOpenShade(true);
		}
	}
	else if (m_state == State::Rising)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->changeState(State::ReadySuccess);
			//关闭遮罩
			this->setOpenShade(false);
		}
	}
	else if (m_state == State::ReadySuccess)
	{
		//进行僵尸的检测
		this->checkCollision();
	}
}

void PotatoMine::readySuccess()
{
	//显示破土特效
	auto pos = this->getPosition();
	Size size = this->getContentSize();
	auto localZOrder = this->getLocalZOrder();

	m_pDelegate->showRisingDirt(pos + Point(0,size.height/3),localZOrder + 1);
}

void PotatoMine::checkCollision()
{
	auto row = m_pCarrier->getRow();
	auto rect = this->getBoundingBox();
	auto pos = this->getPosition();

	auto zombie = m_pDelegate->findFirstCollidedZombie(row,rect);
	//发生碰撞，炸死僵尸
	if (zombie != nullptr && zombie->getHitPoint() > 0)
	{
		//展示特效
		m_pDelegate->showExplosionSpudow(pos);
		//直接死亡
		this->setHitPoint(0);
		this->setDead(true);
		//爆炸
		m_pDelegate->addBoom(this->getDamage(),row,rect);
	}
}

void PotatoMine::changeState(State state)
{
	if (state == m_state)
		return;

	m_state = state;
	//上升特效
	if (m_state == State::Rising)
	{
		//获取破土后的动画
		auto animation = AnimationCache::getInstance()->getAnimation(this->getPlantName());
		auto firstFrame = animation->getFrames().front()->getSpriteFrame();

		this->getSprite()->setSpriteFrame(firstFrame);
		//设置持续时间
		m_duration = 0.4f;
		//设置位置
		auto size = this->getSprite()->getContentSize();
		auto pos = this->getSprite()->getPosition();

		this->getSprite()->setPosition(pos + Point(0.f,size.height/2));
		//设置上升动画
		MoveBy*move = MoveBy::create(m_duration,Point(0.f,-size.height/2));

		this->getSprite()->runAction(move);
	}
	else if (m_state == State::ReadySuccess)
	{
		//获取破土后的动画
		auto animation = AnimationCache::getInstance()->getAnimation(this->getPlantName());
		auto animate = Animate::create(animation);
		this->getSprite()->runAction(animate);
	}

}