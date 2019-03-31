#include "SecondLayer.h"
#include "Text.h"

Scene* SecondLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondLayer::create();

	scene->addChild(layer);
	return scene;
}

SecondLayer::SecondLayer()
	:m_pText(nullptr)
{
}

SecondLayer::~SecondLayer()
{
}

bool SecondLayer::init()
{
/*	Director::getInstance()->getRenderer()->setRenderDrawColor(Color4B(0, 255, 255, 255));
	m_pText = Text::create("fonts/DroidSansFallback.ttf", 14);
	m_pText->setPosition(150,150);
	this->addChild(m_pText);

	auto ptr = FileUtils::getInstance()->getUniqueDataFromFile("test.txt");
	m_pText->wind(ptr.get(), Size(300,300), Color4B(0, 0, 0, 255), true);

	ptr.reset();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = SDL_CALLBACK_2(SecondLayer::onTouchBegan, this);
	_eventDispatcher->addEventListener(listener, this);

	this->scheduleUpdate();*/

	return true;
}

void SecondLayer::update(float dt)
{
	m_pText->windRun(dt);
}

bool SecondLayer::onTouchBegan(Touch* touch, SDL_Event* event)
{
	m_pText->windOver();

	return true;
}