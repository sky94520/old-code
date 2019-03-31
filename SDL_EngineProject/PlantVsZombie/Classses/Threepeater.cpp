#include "Threepeater.h"

Threepeater::Threepeater()
{
}

Threepeater::~Threepeater()
{
}

Threepeater * Threepeater::create(const string& plantName)
{
	auto plant = new Threepeater();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Threepeater::init(const string& plantName)
{
	m_plantName = plantName;

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	return true;
}

void Threepeater::updateAttackState(float dt)
{
	//获取当前行
	int row = m_pCarrier->getRow();

	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//对发射的位置进行确定
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//每次发射三个豌豆
	for (int i = - 1;i <= 1;i++)
	{
		int r = i + row;
		//考虑边界问题
		if (r < 0)
			continue;
		//获取发射位置
		Point bornPos = startPos + Point(0.f,i * size.height);
		//发射豌豆
		this->shootPeaBullet(r,bornPos);
	}
	//转入正常状态
	m_state = State::Normal;
}

void Threepeater::updateAttackEndState(float dt)
{
}

ZombieBase* Threepeater::findFirstZombie()
{
	//获取当前所在行
	int row = m_pCarrier->getRow();
	//每次检索三行
	for (int i = row - 1;i <= row + 1;i++)
	{
		//考虑边界问题
		if (i < 0)
			continue;
		//获取当前行是否存在僵尸
		auto zombie = m_pDelegate->findFirstZombieOfRow(i,this->getDir(),this->getPosition());

		if (zombie != nullptr)
			return zombie;
	}

	return nullptr;
}