#include "Repeater.h"

Repeater::Repeater()
	:m_elapsed(0.f)
	,m_nCurBulletNum(0)
{
}

Repeater::~Repeater()
{
}

Repeater *Repeater::create(const string& plantName)
{
	auto plant = new Repeater();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Repeater::init(const string& plantName)
{
	m_plantName = plantName;

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	return true;
}

void Repeater::updateAttackState(float dt)
{
	m_elapsed += dt;
	//���﹥��ʱ�䣬����
	if (m_elapsed >= 0.15f)
	{
		int row = m_pCarrier->getRow();

		this->shootPeaBullet(row);

		m_elapsed -= 0.15f;
		m_nCurBulletNum -= 1;
		//������ɣ�ת������״̬
		if (m_nCurBulletNum <= 0)
		{
			m_nCurBulletNum = m_nBulletNumber;
			
			this->changeState(State::AttackEnd);
		}
	}
}

void Repeater::updateAttackEndState(float dt)
{
	this->changeState(State::Normal);
}