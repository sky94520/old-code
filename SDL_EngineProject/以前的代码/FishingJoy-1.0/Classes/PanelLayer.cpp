#include "PanelLayer.h"
#include "GoldTimer.h"
#include "GoldCounter.h"
PanelLayer::PanelLayer()
	:m_pDelegate(nullptr),m_pGoldCounter(nullptr),m_pGoldTimer(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
		//ÉèÖÃÎ»ÖÃ
	Sprite*bg = Sprite::createWithSpriteFrameName("ui_end.png");
	Size bgSize = bg->getContentSize();
	//ÔİÍ£°´Å¥
	 auto pauseBtn = MenuItemSprite::create(
		 Sprite::createWithSpriteFrameName("pause_normal.png")
		 ,Sprite::createWithSpriteFrameName("pause_selected.png"),nullptr,
		 SDL_CALLBACK_1(PanelLayer::pauseCallback,this));
	 Size pauseBtnSize = pauseBtn->getContentSize();
	 pauseBtn->setPositionX(visibleSize.width - pauseBtnSize.width);
	 auto menu = Menu::create(pauseBtn,nullptr);
	 this->addChild(menu);
	 //½ğ±ÒÏÔÊ¾°å
	 m_pGoldCounter = GoldCounter::create();
	 m_pGoldCounter->setPosition(105,visibleSize.height-bgSize.height/2);
	 this->addChild(m_pGoldCounter);
	 //½ğ±Ò¼ÆÊ±Æ÷
	 m_pGoldTimer = GoldTimer::create();
	 Size size = m_pGoldTimer->getContentSize();
	 m_pGoldTimer->setPosition(105+m_pGoldCounter->getContentSize().width,visibleSize.height-bg->getContentSize().height);
	 this->addChild(m_pGoldTimer);
	return true;
}
void PanelLayer::setDelegate(PanelLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void PanelLayer::update(float dt)
{
	m_pGoldTimer->update(dt);
}
void PanelLayer::pauseCallback(Object*obj)
{
	m_pDelegate->pause();
}