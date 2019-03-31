#include "HelloWorldScene.h"
#include "SDL_gfx.h"
#include "GB2ShapeCache-x.h"
#include "StaticData.h"
#include "RotateSpeedSprite.h"
#include "Entity.h"
#include "GoldCounter.h"
#include "ScrollLabel.h"
#include "LevelLayer.h"
#include "FishingJoyData.h"

HelloWorld::HelloWorld()
{
}
HelloWorld::~HelloWorld()
{
}
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);

	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("start_ui.xml");

	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/StartLayer.xml");
	this->addChild(node);

	m_pStartBtn = node->getChildByName<ui::Button*>("start_btn");
	m_pStartBtn->addTouchEventListener(SDL_CALLBACK_2(HelloWorld::touchCallback,this));
	m_pStartBtn->addClickEventListener(SDL_CALLBACK_1(HelloWorld::touchTest,this));

	m_pLabel = LabelAtlas::create("0","ui_text_01.png",26,34,'0');
	m_pLabel->setPosition(100,100);
	this->addChild(m_pLabel);

	m_pLabel2 = LabelAtlas::create("0","ui_text_01.png",26,34,'0');
	m_pLabel2->setPosition(100,200);
	this->addChild(m_pLabel2);

	this->scheduleUpdate();
	b2Vec2 gravity(0.f,0.f);
	m_pWorld = new b2World(gravity);

	return true;
}
void HelloWorld::update(float dt)
{
	//PhysicalEngine::getInstance()->drawDebugData();
}

bool HelloWorld::onTouchBegan(Touch*touch,SDL_Event*event)
{

	return true;
}

void HelloWorld::onTouchMoved(Touch*touch,SDL_Event*event)
{
}

void HelloWorld::onTouchEnded(Touch*touch,SDL_Event*event)
{
}

void HelloWorld::touchCallback(Object*,ui::TouchEventType type)
{
	if (type == ui::TouchEventType::BEGAN)
	{
		m_pLabel->setString("1");
	}
	else if (type == ui::TouchEventType::MOVED)
	{
		m_pLabel->setString("2");
	}
	else if (type == ui::TouchEventType::ENDED)
	{
		m_pLabel->setString("3");
	}
	else
	{
		m_pLabel->setString("4");
	}
}

void HelloWorld::touchTest(Object*sender)
{
	//m_pLabel2->setString("3");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//´´½¨¸ÕÌå
	auto body = m_pWorld->CreateBody(&bodyDef);//PhysicalEngine::getInstance()->createBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = 7.f;
	//body->CreateFixture(&shape,1.f);

	GB2ShapeCache::getInstance()->addFixturesToBody(body,"star_fish");
}
