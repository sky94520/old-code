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
	//�����ӵ���ĿΪ2
	m_nBulletNumber = m_nCurBulletNum = 2;
	//����ȷ��λ��
	m_pSprite->setAnchorPoint(Point(0.6f,0.5f));

	return true;
}

void SplitPea::updateAttackState(float dt)
{
	m_elapsed += dt;
	//���﹥��ʱ�䣬����
	if (m_elapsed >= 0.15f)
	{
		int row = m_pCarrier->getRow();

		Point startPos = this->getPosition();
		Size size = this->getContentSize();
		//�Է����λ�ý���ȷ��
		startPos.x += size.width/2.f;
		startPos.y -= size.height/4;
		
		Point bornPos = startPos;
		//��ǰΪ��һ�Σ�������������һ���㶹
		if (m_nCurBulletNum == m_nBulletNumber)
		{
			this->shootPeaBullet(row,bornPos);
		}
		//���䷴�����㶹
		bornPos.x -= size.width/2.f;

		this->shootPeaBullet(row,bornPos,false);

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

void SplitPea::updateAttackEndState(float dt)
{
	this->changeState(State::Normal);
}