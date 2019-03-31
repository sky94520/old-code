#include "OperateLayer.h"
#include "VirtualStick.h"
#include "Button.h"

OperateLayer::OperateLayer()
	:m_pStick(nullptr),m_pAtkItem(nullptr)
	,m_pHero(nullptr),m_bUpdated(false),m_degree(0.f)
{
}
OperateLayer::~OperateLayer()
{
}
bool OperateLayer::init()
{
	auto listener = EventListenerAllAtOnce::create();
	listener->onTouchesBegan = SDL_CALLBACK_2(OperateLayer::onTouchesBegan,this);
	listener->onTouchesMoved = SDL_CALLBACK_2(OperateLayer::onTouchesMoved,this);
	listener->onTouchesEnded = SDL_CALLBACK_2(OperateLayer::onTouchesEnded,this);

	_eventDispatcher->addEventListener(listener,this);

	//摇杆
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pStick = VirtualStick::create(Sprite::create("button/shot_stick.png"),Sprite::create("button/shot_stick_bg.png"));
	Size size = m_pStick->getContentSize();
	m_pStick->setPosition(size.width/2,visibleSize.height - size.height/2);
	this->addChild(m_pStick);
	//攻击按钮
	m_pAtkItem = Button::create(Sprite::create("button/attack.png",Rect(0,0,106,103)),Sprite::create("button/attack.png",Rect(0,106,106,103)));
	Size atkSize = m_pAtkItem->getContentSize();
	m_pAtkItem->setPosition(visibleSize.width - atkSize.width/2,visibleSize.height - atkSize.height/2);
	m_pAtkItem->setCallback(SDL_CALLBACK_1(OperateLayer::updateAtk,this));
	this->addChild(m_pAtkItem);
	//test
	m_pHero = Sprite::create("icon.png");
	this->addChild(m_pHero);

	this->scheduleUpdate();

	return true;
}
void OperateLayer::update(float dt)
{
	if(m_bUpdated)
	{
		float x = SDL_cosf(m_degree);
		float y = SDL_sinf(m_degree);
		auto pos = m_pHero->getPosition() + Point(x,y);
		m_pHero->setPosition(pos);
	}
}
void OperateLayer::onTouchesBegan(vector<Touch*>touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		Point pos = touch->getLocation();
		//是否已经松手
		if(m_pStick->getFingerId() == -1)
		{
			//点击了摇杆 若有效，传递给PlayerLayer
			Rect rect1 = m_pStick->getBoundingBox();
			if(rect1.containsPoint(pos))
			{
				m_pStick->setFingerId(touch->getID());
				m_degree = m_pStick->selected(touch->getLocation());
				continue;
			}
		}
		//点击了子弹按钮
		Rect rect2 = m_pAtkItem->getBoundingBox();
		if(rect2.containsPoint(pos))
		{
			m_pAtkItem->setFingerId(touch->getID());
			m_pAtkItem->selected();
		}
	}
}
void OperateLayer::onTouchesMoved(vector<Touch*> touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		if(touch->getID() == m_pStick->getFingerId())
			m_degree = m_pStick->selected(touch->getLocation());
		else if(touch->getID() == m_pAtkItem->getFingerId())
			m_pAtkItem->selected();
	}
}
void OperateLayer::onTouchesEnded(vector<Touch*>touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		if(touch->getID() == m_pStick->getFingerId() && touch->getStatus() == TouchStatus::TOUCH_UP)
			m_pStick->unselected();
		else if(touch->getID() == m_pAtkItem->getFingerId())
		{
			m_pAtkItem->activate();
			m_pAtkItem->unselected();
		}
	}
}
void OperateLayer::updateAtk(Object*sender)
{
	m_bUpdated = !m_bUpdated;
}