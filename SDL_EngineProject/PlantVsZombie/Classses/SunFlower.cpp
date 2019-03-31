#include "SunFlower.h"

SunFlower::SunFlower()
	:m_curState(State::Normal)
	,m_produceSunDuration(0.f),m_elapsed(0.f)
{
}

SunFlower::~SunFlower()
{
}

SunFlower*SunFlower::create(const string&plantName)
{
	auto plant = new SunFlower();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SunFlower::init(const string&plantName)
{
	m_plantName = plantName;
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	//����λ��
	auto size = m_pSprite->getContentSize();
	size.height /= 2.f;

	m_pSprite->setPosition(Point::ZERO);
	m_pSprite->setAnchorPoint(Point::ZERO);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//�������ж���
	Animate*animate = Animate::create(animation);
	this->getSprite()->runAction(animate);

	m_produceSunDuration = 2.f;
	return true;
}

void SunFlower::updateHook(float dt)
{
	//�����ͼ�ĸ���
	//��ǰ��������״̬
	if (m_curState == State::Normal)
	{
		m_elapsed += dt;
		//�л�״̬
		if (m_elapsed >= this->getColdDownTime() - m_produceSunDuration)
		{
			m_curState = State::ProducingSun;
			//�ı��ڲ�����λ��
			auto pos = m_pSprite->getPosition();
			auto size = this->getContentSize();

			m_pSprite->setPosition(pos - Point(0.f,size.height));
		}
	}
	else if (m_curState == State::ProducingSun)
	{
		m_elapsed += dt;
		//�ָ�����״̬
		if (m_elapsed >= this->getColdDownTime())
		{
			m_elapsed = 0.f;

			m_curState = State::Normal;
			//�ı��ڲ�����λ��
			auto pos = m_pSprite->getPosition();
			auto size = this->getContentSize();

			m_pSprite->setPosition(pos + Point(0.f,size.height));
			//��������
			this->productSun();
		}
	}
}

void SunFlower::visit()
{
	auto size = this->getContentSize();
	auto pos = this->getWorldPosition();

	SDL_Rect rect = {int(pos.x),int(pos.y),(int)size.width,(int)size.height};

	Director::getInstance()->getRenderer()->renderSetClipRect(&rect);
	Node::visit();
	Director::getInstance()->getRenderer()->renderSetClipRect(nullptr);
}

void SunFlower::productSun()
{
	//����һ������
	Size size = this->getContentSize(); 
	auto x = RANDOM(0.f,size.width);
	auto y = 0.f;
	
	JumpBy*jump = JumpBy::create(0.8f,Point(x,y),-size.height,1);
	auto pos = this->getPosition();
	auto realPos = this->getParent()->convertToWorldSpace(pos);

	m_pDelegate->makeSun(25,jump,realPos);
}

//---------------------------------TwinSunflower------------------
TwinSunflower::TwinSunflower()
{
}

TwinSunflower::~TwinSunflower()
{
}

TwinSunflower*TwinSunflower::create(const string&plantName)
{
	auto plant = new TwinSunflower();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool TwinSunflower::init(const string&plantName)
{
	return SunFlower::init(plantName);
}
void TwinSunflower::updateHook(float dt)
{
	SunFlower::updateHook(dt);
}

void TwinSunflower::productSun()
{
	//��������
	for (auto i = 0;i < 2;i++)
	{
		SunFlower::productSun();
	}
}