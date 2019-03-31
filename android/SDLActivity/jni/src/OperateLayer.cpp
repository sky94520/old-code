#include "OperateLayer.h"
#include "VirtualStick.h"
#include "Button.h"

OperateLayer::OperateLayer()
	:m_pStick(nullptr),m_pAtkItem(nullptr)
	,m_pDelegate(nullptr)
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

	//ҡ��
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pStick = VirtualStick::create(Sprite::create("button/shot_stick.png"),Sprite::create("button/shot_stick_bg.png"));
	Size size = m_pStick->getContentSize();
	m_pStick->setPosition(size.width/2,visibleSize.height - size.height/2);
	this->addChild(m_pStick);
	//������ť
	m_pAtkItem = Button::create(Sprite::create("button/attack.png",Rect(0,0,106,103)),Sprite::create("button/attack.png",Rect(0,106,106,103)));
	Size atkSize = m_pAtkItem->getContentSize();
	m_pAtkItem->setPosition(visibleSize.width - atkSize.width/2,visibleSize.height - atkSize.height/2);
	m_pAtkItem->setCallback(SDL_CALLBACK_1(OperateLayer::updateAtk,this));
	this->addChild(m_pAtkItem);

	return true;
}
void OperateLayer::onTouchesBegan(vector<Touch*>touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		Point pos = touch->getLocation();
		//�Ƿ��Ѿ�����
		if(m_pStick->getFingerId() == -1)
		{
			//�����ҡ�� ����Ч�����ݸ�PlayerLayer
			Rect rect1 = m_pStick->getBoundingBox();
			if(rect1.containsPoint(pos))
			{
				m_pStick->setFingerId(touch->getID());
				m_pStick->selected(touch->getLocation());
				Point dir = m_pStick->getDirection();

				m_pDelegate->degreeUpdate(dir);
				continue;
			}
		}
		//������ӵ���ť
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
		{
			m_pStick->selected(touch->getLocation());
			Point dir = m_pStick->getDirection();
			m_pDelegate->degreeUpdate(dir);
			//__android_log_print(ANDROID_LOG_WARN,"Operate","x=%.2f,y=%.2f",m_dir.x,m_dir.y);
		}
		else if(touch->getID() == m_pAtkItem->getFingerId())
			m_pAtkItem->selected();
	}
}
void OperateLayer::onTouchesEnded(vector<Touch*>touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		if(touch->getID() == m_pStick->getFingerId()&& touch->getStatus() == TouchStatus::TOUCH_UP)
		{
			m_pStick->unselected();
			//m_pDelegate->degreeUpdate(Point::ZERO);
		}
		else if(touch->getID() == m_pAtkItem->getFingerId())
		{
			m_pAtkItem->activate();
			m_pAtkItem->unselected();
		}
	}
}
void OperateLayer::setDelegate(OperateLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void OperateLayer::updateAtk(Object*sender)
{
	m_pDelegate->wantShooting();
}
