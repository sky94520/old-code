#include "HelloWorldScene.h"

USING_NS_CC;

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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

	Sprite*sp1 = Sprite::create("sprite1.png");
	sp1->setPosition(Point(visibleSize.width*0.5f,visibleSize.height*0.5f));
	this->addChild(sp1);
	
	Sprite*sp2 = Sprite::create("sprite2.png");
	sp2->setPosition(Point(visibleSize.width*0.5f,visibleSize.height*0.5f));
	this->addChild(sp2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*touch,Event*event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	//判断单击的坐标是否在精灵的范围内
	if(target->getBoundingBox().containsPoint(pos))
		target->setOpacity(100);
	return true;

	return false;
	};

	listener->onTouchEnded = [](Touch*touch,Event*event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setOpacity(255);
	};

	
	//注册监听事件，绑定精灵1
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,sp1);
	//注册监听事件，帮顶精灵2，复制一份listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),sp2);
	listener->setSwallowTouches(true);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
