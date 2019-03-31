#include "HelloWorldScene.h"

#include "AnimationUtil.h"

#include "GuideLayer.h"

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
	Director::getInstance()->getEventDispatcher();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   this,
                                           menu_selector(HelloWorld::menuCloseCallback));
    
	closeItem->setPosition(Vec2(50 ,visibleSize.height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 30);

    ///////////////////////////
	//Dictionary
	
	Sprite*bg = Sprite::create("TollgateBG.jpg");
	bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg);
	bg->runAction(createAnimation2());
	//Sprite*sp = Sprite::createWithSpriteFrame
	/*Sprite*runSp = Sprite::create("run1.png");
	runSp->setPosition(Point(300,100));
	this->addChild(runSp);

	runSp->runAction(createAnimation1());

	Sprite*runSp2 = Sprite::create("loading_1.png");
	runSp2->setPosition(Point(450,250));
	this->addChild(runSp2);

	runSp2->setFlipX(true);
	SpriteFrameCache*cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("loading/texture.plist","loading/texture.png");

	Animation*animation = AnimationUtil::createWithSingleFrameName("loading_",0.05f,-1);
	runSp2->runAction(Animate::create(animation));
	*/
	/*GuideLayer*guide =GuideLayer::create();//create(Rect(0,0,visibleSize.width/4,visibleSize.height/4));
	guide->setPosition(Vec2::ZERO);
	this->addChild(guide,50);*/
	//Director::getInstance()->drawScene
	//this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::update),2.f);
	return true;
}
void HelloWorld::update(float dt)
{
	log("%f",dt);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
	SpriteFrameCache*cache = SpriteFrameCache::getInstance();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
cocos2d::Animate*HelloWorld::createAnimation1()
{
	int iFrameNum = 15;

	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameVec;
	//
	for(int i = 1;i <= iFrameNum;i++)
	{
		frame = SpriteFrame::create(StringUtils::format("run%d.png",i),Rect(0,0,130,130));
		frameVec.pushBack(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(10);
	animation->setDelayPerUnit(0.05f);
	Animate*action = Animate::create(animation);

	return action;
}
cocos2d::Animate*HelloWorld::createAnimation2()
{
	//加载图片到缓存池
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	//frameCache->removeSpriteFramesFromFile
	frameCache->addSpriteFramesWithFile("loading/texture.plist","loading/texture.png");

	int iFrameNum = 12;
	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameVec;

	//用一个列表保存所有SpriteFrame对象
	for(int i =1;i <= iFrameNum;i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("loading_%d.png",i));
		frameVec.pushBack(frame);
	}
	//使用SpriteFrame列表动画对象
	Animation*animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.05f);

	//包装成一个动作
	Animate*action = Animate::create(animation);

	return action;
}
