#include "Pearl.h"
#include "StaticData.h"

Pearl::Pearl()
	:m_speed(0.f)
{
}

Pearl::~Pearl()
{
}

bool Pearl::init()
{
	//�󶨾���
	auto spriteName = STATIC_DATA_STRING("pearl_sprite_name");
	this->bindSpriteWithSpriteFrameName(spriteName);

	m_speed = 6.f;

	return true;
}

void Pearl::setDelat(float rotation)
{
	auto degree = SDL_ANGLE_TO_DEGREE(rotation);

	m_delta.x = SDL_sinf(degree);
	m_delta.y = SDL_cosf(degree) * -1.f;
}

float Pearl::showAt()
{
	return 0.f;
}

void Pearl::collided()
{
	auto afterHP = m_nHP - 1;
	
	if(afterHP <= 0)
	{
		afterHP = 0;
	}

	this->setHP(afterHP);
	//��Ҫ������������������
	if(afterHP > 0)
	{
		return;
	}
	//���ŵ�������
	FadeOut*fade = FadeOut::create(1.f);

	DelayTime*delayTime = DelayTime::create(fade->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDead(true);
	});
	//���ж���
	auto seq = Sequence::create(delayTime,end,nullptr);

	this->runAction(seq);
	this->getSprite()->runAction(fade);
}

void Pearl::update(float dt)
{
	//�����ƶ�
	bool bChangeDir = false;

	//�ж��Ƿ�ͱ߽緢����ײ
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Rect r1(0,0,visibleSize.width,1);//�ϱ߽�
	Rect r3(0,visibleSize.height,visibleSize.width,1);//�±߽�
	Rect r2(0,0,1,visibleSize.height);//��߽�
	Rect r4(visibleSize.width,0,1,visibleSize.height);//�ұ߽�

	Rect r = this->getBoundingBox();
	//�����±߽���ײ
	if (r1.intersectsRect(r) || r3.intersectsRect(r))
	{
		bChangeDir = true;
		m_delta.y = -m_delta.y;
	}
	//�����ұ߽緢����ײ
	if (r2.intersectsRect(r) || r4.intersectsRect(r))
	{
		bChangeDir = true;
		m_delta.x = -m_delta.x;
	}
	//��ײ���߽磬����������1
	if(bChangeDir)
	{
		this->collided();
	}
	//�����ƶ�
	Point nextPos = this->getPosition() + Point(m_speed * m_delta.x,m_speed * m_delta.y);

	this->setPosition(nextPos);
}