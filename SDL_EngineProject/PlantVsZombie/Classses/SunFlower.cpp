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
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	//设置位置
	auto size = m_pSprite->getContentSize();
	size.height /= 2.f;

	m_pSprite->setPosition(Point::ZERO);
	m_pSprite->setAnchorPoint(Point::ZERO);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//设置运行动画
	Animate*animate = Animate::create(animation);
	this->getSprite()->runAction(animate);

	m_produceSunDuration = 2.f;
	return true;
}

void SunFlower::updateHook(float dt)
{
	//负责绘图的更新
	//当前处于正常状态
	if (m_curState == State::Normal)
	{
		m_elapsed += dt;
		//切换状态
		if (m_elapsed >= this->getColdDownTime() - m_produceSunDuration)
		{
			m_curState = State::ProducingSun;
			//改变内部精灵位置
			auto pos = m_pSprite->getPosition();
			auto size = this->getContentSize();

			m_pSprite->setPosition(pos - Point(0.f,size.height));
		}
	}
	else if (m_curState == State::ProducingSun)
	{
		m_elapsed += dt;
		//恢复正常状态
		if (m_elapsed >= this->getColdDownTime())
		{
			m_elapsed = 0.f;

			m_curState = State::Normal;
			//改变内部精灵位置
			auto pos = m_pSprite->getPosition();
			auto size = this->getContentSize();

			m_pSprite->setPosition(pos + Point(0.f,size.height));
			//生产阳光
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
	//设置一个动作
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
	//调用两次
	for (auto i = 0;i < 2;i++)
	{
		SunFlower::productSun();
	}
}