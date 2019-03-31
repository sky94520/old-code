#include "PanelLayer.h"
#include "Player.h"
#include "DynamicData.h"

PanelLayer::PanelLayer()
	:m_pScoreLabel(nullptr),m_pLifeLabel(nullptr)
	,m_pBulletLabel(nullptr),m_pSpeedLabel(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//分数
	m_pScoreLabel = LabelAtlas::create("SCORE:00","lazyfont.png",39,55,0);
	m_pScoreLabel->setFontKerning(0.5);
	m_pScoreLabel->setColorKey(0,255,255);
	m_pScoreLabel->setPosition(visibleSize.width/3*2,m_pScoreLabel->getContentSize().height/2);

	this->addChild(m_pScoreLabel);
	//生命
	m_pLifeLabel = LabelAtlas::create("LIFE:2","lazyfont.png",39,55,0);
	m_pLifeLabel->setFontKerning(0.5);
	m_pLifeLabel->setColorKey(0,255,255);
	m_pLifeLabel->setPosition(visibleSize.width/3*2,m_pScoreLabel->getContentSize().height);
	this->addChild(m_pLifeLabel);
	//子弹
	m_pBulletLabel = LabelAtlas::create("bullet:2","lazyfont.png",39,55,0);
	m_pBulletLabel->setFontKerning(0.5);
	m_pBulletLabel->setColorKey(0,255,255);
	m_pBulletLabel->setPosition(visibleSize.width/3*2,m_pScoreLabel->getContentSize().height/2*3);
	this->addChild(m_pBulletLabel);
	//速度
	m_pSpeedLabel = LabelAtlas::create("speed:1","lazyfont.png",39,55,0);
	m_pSpeedLabel->setFontKerning(0.5);
	m_pSpeedLabel->setColorKey(0,255,255);
	m_pSpeedLabel->setPosition(visibleSize.width/3*2,m_pScoreLabel->getContentSize().height*2);
	this->addChild(m_pSpeedLabel);
	//添加事件监听
	_eventDispatcher->addEventCustomListener("dynamic data",SDL_CALLBACK_1(PanelLayer::updateDynamicData,this),this);
	_eventDispatcher->addEventCustomListener("player",SDL_CALLBACK_1(PanelLayer::updatePlayer,this),this);
	return true;
}
void PanelLayer::updateDynamicData(EventCustom*custom)
{
	int life = DynamicData::getInstance()->getLife();
	int score = DynamicData::getInstance()->getScore();

	string text1 = StringUtils::format("life:%d",life);
	string text2 = StringUtils::format("score:%d",score);

	m_pLifeLabel->setString(text1);
	m_pScoreLabel->setString(text2);
}

void PanelLayer::updatePlayer(EventCustom*custom)
{
	auto player = static_cast<Player*>(custom->getUserData());
	int speed = player->getCurSpeed();
	int bullet = player->getBulletNum();
	//更新
	std::string text1 = StringUtils::format("speed:%d",speed);
	std::string text2 = StringUtils::format("bullet:%d",bullet);

	m_pSpeedLabel->setString(text1);
	m_pBulletLabel->setString(text2);
}