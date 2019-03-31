#include "HelloWorldScene.h"
#include "DebugDraw.h"
#include "TMXTiledMap.h"

HelloWorld::HelloWorld()
	:m_pWorld(nullptr),m_pDebugDraw(nullptr)
{
}
HelloWorld::~HelloWorld()
{
	SDL_SAFE_DELETE(m_pWorld);
	SDL_SAFE_DELETE(m_pDebugDraw);
}
Scene*HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	initPhysics();
	//加载资源
	Director::getInstance()->getRenderer()->setRenderDrawColor(128,111,255,255);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = SDL_CALLBACK_2(HelloWorld::onTouchBegan,this);
	_eventDispatcher->addEventListener(listener,this);

	TMXTiledMap*tiledMap = TMXTiledMap::create("Resources/4.tmx");
	this->addChild(tiledMap);
	this->scheduleUpdate();
	return true;
}
void HelloWorld::update(float dt)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_pWorld->Step(dt,velocityIterations,positionIterations);
	for(b2Body*body = m_pWorld->GetBodyList();body;body = body->GetNext())
	{
		if(body->GetUserData())
		{
			Sprite*sprite = static_cast<Sprite*>(body->GetUserData());
			auto angle = body->GetAngle();
			auto pos = body->GetPosition();
			Size size = sprite->getContentSize();
			sprite->setPosition(pos.x*PTM_RATIO-size.width/2,pos.y*PTM_RATIO-size.height/2);
			sprite->setRotation(angle * 57.29577951f);
		}
	}
	auto renderer = TheDirector::getInstance()->getRenderer()->getSDL_Renderer();
	circleRGBA(renderer,200,200,50,255,0,0,128);

	m_pWorld->DrawDebugData();
}
bool HelloWorld::onTouchBegan(Touch*touch,SDL_Event*)
{
	auto pos = touch->getLocation();
	//生成一个球
	Sprite*sprite = Sprite::create("Resources/bullet.png");
	sprite->setPosition(pos);
	sprite->setVisible(true);
	this->addChild(sprite);
	Size size = sprite->getContentSize();
	//添加物理
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(sprite->getPositionX()/PTM_RATIO+size.width/2/PTM_RATIO,
		sprite->getPositionY()/PTM_RATIO + size.height/2/PTM_RATIO);
	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	body->SetUserData(sprite);
	b2CircleShape shape;
	shape.m_radius = size.width/PTM_RATIO/2;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.restitution = 0.6f;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3;
	body->CreateFixture(&fixtureDef);
	
	return true;
}
void HelloWorld::initPhysics()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	b2Vec2 gravity(0,9.8f);
	m_pWorld = new b2World(gravity);
	
	m_pWorld->SetAllowSleeping(true);//允许休眠
	m_pWorld->SetContinuousPhysics(true);//连续物理测试
	m_pWorld->SetContactListener(this);
	//开启调试模式
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_pDebugDraw = new DebugDraw(flags);
	m_pWorld->SetDebugDraw(m_pDebugDraw);
	//设置边缘
	b2BodyDef bodyDef;
	
	bodyDef.position.Set(0.f,0.f);
	b2Body*ground = m_pWorld->CreateBody(&bodyDef);
	b2EdgeShape shape;
	//下
	shape.Set(b2Vec2(0,visibleSize.height/PTM_RATIO),b2Vec2(visibleSize.width/PTM_RATIO,visibleSize.height/PTM_RATIO));
	ground->CreateFixture(&shape,1.f);
	//右
	shape.Set(b2Vec2(visibleSize.width/PTM_RATIO,0),b2Vec2(visibleSize.width/PTM_RATIO,visibleSize.height/PTM_RATIO));
	ground->CreateFixture(&shape,1.f);
	//左
	shape.Set(b2Vec2(0,0),b2Vec2(0,visibleSize.height/PTM_RATIO));
	ground->CreateFixture(&shape,1.f);
}
void HelloWorld::BeginContact(b2Contact*contact)
{
}