#include "HelloWorldScene.h"

HelloWorld::HelloWorld()
	:m_elapsed(0.f),m_bSkill(false)
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
    return true;
}

void HelloWorld::update(float dt)
{
	if (!m_bSkill)
	{
		m_elapsed += dt;
		if (m_elapsed >= 1.4f)
		{
			m_bSkill = true;
			m_elapsed -= 1.4f;

			//改变动画
			m_pSprite->stopActionByTag(1);

			Animation*attack = AnimationCache::getInstance()->getAnimation("PeashooterAttack");
			m_pSprite->runAction(Animate::create(attack));
		}
	}
	else
	{
		m_elapsed += dt;

		if (m_elapsed >= 1.1f)
		{
			m_bSkill = false;
			m_elapsed -= 1.1f;

			//改变动画
			Animation*animation = AnimationCache::getInstance()->getAnimation("Peashooter");
			auto attack = Animate::create(animation);
			attack->setTag(1);

			m_pSprite->stopActionByTag(1);
			m_pSprite->runAction(attack);
		}
	}

}

void HelloWorld::menuCloseCallback(Object* pSender)
{
}
