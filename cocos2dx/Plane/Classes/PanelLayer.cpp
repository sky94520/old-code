#include "PanelLayer.h"
#include "DynamicData.h"
PanelLayer::PanelLayer()
	:m_pShowScore(nullptr),m_pBulletLabel(nullptr),m_pDelegate(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//score
	Label*pScore = Label::createWithSystemFont("score:","Marker Felt.ttf",25);
	pScore->setPosition(pScore->getContentSize().width/2,visibleSize.height-pScore->getContentSize().height/2);
	this->addChild(pScore);

	m_pShowScore = LabelAtlas::create("000","fps_images.png",16,32,'.');
	m_pShowScore->setPosition(pScore->getContentSize().width,visibleSize.height - m_pShowScore->getContentSize().height);
	this->addChild(m_pShowScore);
	//双发子弹持续时间倒计时
	m_pBulletLabel = LabelAtlas::create("","fps_images.png",16,32,'.');
	m_pBulletLabel->setPosition(visibleSize.width/2,visibleSize.height - m_pBulletLabel->getContentSize().height);
	m_pBulletLabel->setVisible(false);
	this->addChild(m_pBulletLabel);
	//暂停按钮
	auto pauseNormalSprite = Sprite::createWithSpriteFrameName("pause_normal.png");
	auto pauseSelectedSprite = Sprite::createWithSpriteFrameName("pause_selected.png");
	auto pauseBtn = MenuItemSprite::create(pauseNormalSprite,pauseSelectedSprite);
	auto size = pauseBtn->getContentSize();

	pauseBtn->setCallback(CC_CALLBACK_1(PanelLayer::gamePause,this));
	auto menu = Menu::create(pauseBtn,nullptr);
	menu->setPosition(visibleSize.width - size.width/2,visibleSize.height - size.height/2);
	this->addChild(menu);
	return true;
}
void PanelLayer::update(float dt)
{
	int score = DynamicData::getInstance()->getScore();
	m_pShowScore->setString(Value(score).asString());

	float bulletDuration = DynamicData::getInstance()->getBulletDuration();
	if(bulletDuration <= 0.f)
	{
		m_pBulletLabel->setVisible(false);
	}
	else
	{
		m_pBulletLabel->setVisible(true);
		char text[10];
		sprintf(text,"%.1f",bulletDuration);
		m_pBulletLabel->setString(text);
	}
}
void PanelLayer::setDelegate(PanelLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void PanelLayer::gamePause(Ref*)
{
	m_pDelegate->gamePause();
}