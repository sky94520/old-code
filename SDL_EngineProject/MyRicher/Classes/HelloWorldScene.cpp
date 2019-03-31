#include "HelloWorldScene.h"

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Director::getInstance()->getRenderer()->setRenderDrawColor(Color4B(0,255,255));

	auto tiledMap = TMXTiledMap::create("map/map1.tmx");
	this->addChild(tiledMap);

    return true;
}

void HelloWorld::update(float dt)
{
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
}
