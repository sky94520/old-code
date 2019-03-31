#include "HelloWorldScene.h"
#include "OperateLayer.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	OperateLayer*layer2 = OperateLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(layer2);
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
    
	/*auto listener = EventListenerAllAtOnce::create();
	listener->onTouchesBegan = SDL_CALLBACK_2(HelloWorld::onTouchesBegan,this);
	listener->onTouchesMoved = SDL_CALLBACK_2(HelloWorld::onTouchesMoved,this);
	_eventDispatcher->addEventListener(listener,this);
	*/
	return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
}
void HelloWorld::onTouchesBegan(std::vector<SDL::Touch*> touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		auto point = touch->getLocation();
		auto id = touch->getID();
		auto text = StringUtils::format("%.2f,%.2f",point.x,point.y);
		auto label = (LabelAtlas*)this->getChildByTag(id);
		if(label)
		{
			label->setString(text);
			label->setPosition(point);
		}
		else
		{
			label = LabelAtlas::create("FPS:59","lazyfont.png",39,55,0);
			label->setFontKerning(0.5);
			label->setPosition(point);
			label->setTag(id);
			this->addChild(label);
		}
	}
}
void HelloWorld::onTouchesMoved(std::vector<SDL::Touch*> touches,SDL_Event*)
{
	for(auto touch:touches)
	{
		auto point = touch->getLocation();
		auto id = touch->getID();
		auto text = StringUtils::format("%.2f,%.2f",point.x,point.y);
		auto label = (LabelAtlas*)this->getChildByTag(id);
		if(label)
		{
			label->setString(text);
			label->setPosition(point);
		}
	}
}
void HelloWorld::onTouchesEnded(std::vector<SDL::Touch*> touches,SDL_Event*event)
{
	for(auto touch:touches)
	{
		if(touch->getStatus() != SDL::TouchStatus::TOUCH_UP)
			continue;
		auto id = touch->getID();
		auto label = (LabelAtlas*)this->getChildByTag(id);
		if(label)
			label->removeFromParent();
	}
}