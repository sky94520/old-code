#include "SplitPea.h"

SplitPea::SplitPea()
	:m_elapsed(0.f),m_nCurBulletNum(0)
	,m_nBulletNumber(0)
{
}

SplitPea::~SplitPea()
{
}

SplitPea* SplitPea::create(const string& plantName)
{
	auto plant = new SplitPea();
	
	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SplitPea::init(const string &plantName)
{
	m_plantName = plantName;

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);
	//设置子弹数目为2
	m_nBulletNumber = m_nCurBulletNum = 2;
	//重新确定位置
	m_pSprite->setAnchorPoint(Point(0.6f,0.5f));

	return true;
}

void SplitPea::updateAttackState(float dt)
{
	m_elapsed += dt;
	//到达攻击时间，攻击
	if (m_elapsed >= 0.15f)
	{
		int row = m_pCarrier->getRow();

		Point startPos = this->getPosition();
		Size size = this->getContentSize();
		//对发射的位置进行确定
		startPos.x += size.width/2.f;
		startPos.y -= size.height/4;
		
		Point bornPos = startPos;
		//当前为第一次，发射正常方向一个豌豆
		if (m_nCurBulletNum == m_nBulletNumber)
		{
			this->shootPeaBullet(row,bornPos);
		}
		//发射反方向豌豆
		bornPos.x -= size.width/2.f;

		this->shootPeaBullet(row,bornPos,false);

		m_elapsed -= 0.15f;
		m_nCurBulletNum -= 1;
		//攻击完成，转到正常状态
		if (m_nCurBulletNum <= 0)
		{
			m_nCurBulletNum = m_nBulletNumber;
			this->changeState(State::AttackEnd);
		}
	}
}

void SplitPea::updateAttackEndState(float dt)
{
	this->changeState(State::Normal);
}