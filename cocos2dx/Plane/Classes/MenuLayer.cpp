#include "MenuLayer.h"
#include "DynamicData.h"
#include "MyUtility.h"
MenuLayer::MenuLayer()
	:m_pDelegate(nullptr),m_pScoreLabel(nullptr),m_pContinueBtn(nullptr)
{
}
MenuLayer::~MenuLayer()
{
}
bool MenuLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	LayerColor*greyLayer = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(greyLayer);

	Scale9Sprite*bg = Scale9Sprite::create("texture/dialog_bg.png");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg);
	//分数面板
	m_pScoreLabel = Label::createWithTTF("","fonts/hanyi.ttf",25);
	m_pScoreLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	m_pScoreLabel->setColor(Color3B(0,0,0));
	//m_pScoreLabel->setAnchorPoint(Vec2(0.f,0.f));
	m_pScoreLabel->setVisible(false);
	this->addChild(m_pScoreLabel);
	//添加继续按钮
	Label*continueLabel = Label::createWithTTF(MyUtility::gbk_to_utf8("继续"),"fonts/hanyi.ttf",25);
	continueLabel->setColor(Color3B(0,0,0));
	m_pContinueBtn = MenuItemLabel::create(continueLabel);
	m_pContinueBtn->setCallback(CC_CALLBACK_1(MenuLayer::gameResume,this));
	//重新开始
	Label*restartLabel = Label::createWithTTF(MyUtility::gbk_to_utf8("重新开始"),"fonts/hanyi.ttf",25);
	restartLabel->setColor(Color3B(0,0,0));
	auto*restartBtn = MenuItemLabel::create(restartLabel);
	restartBtn->setCallback(CC_CALLBACK_1(MenuLayer::gameRestart,this));
	//回到主界面
	Label*returnLabel = Label::createWithTTF(MyUtility::gbk_to_utf8("主界面"),"fonts/hanyi.ttf",25);
	returnLabel->setColor(Color3B(0,0,0));
	MenuItemLabel*returnBtn = MenuItemLabel::create(returnLabel);
	returnBtn->setCallback(CC_CALLBACK_1(MenuLayer::gameEnd,this));

	Menu*menu = Menu::create(m_pContinueBtn,restartBtn,returnBtn,nullptr);
	menu->setPosition(bg->getPosition());
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu);
	return true;
}
void MenuLayer::setDelegate(MenuLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void MenuLayer::gameOver()
{
	int score = DynamicData::getInstance()->getScore();
	char text[40];
	sprintf(text,"分数:%d",score);

	m_pContinueBtn->setVisible(false);
	m_pScoreLabel->setVisible(true);
	m_pScoreLabel->setString(MyUtility::gbk_to_utf8(text));
	m_pScoreLabel->setPosition(m_pContinueBtn->convertToWorldSpace(Vec2(0,0)));
}
void MenuLayer::gameResume(Ref*)
{
	m_pDelegate->gameResume();
}
void MenuLayer::gameRestart(Ref*)
{
	m_pDelegate->gameRestart();
}
void MenuLayer::gameEnd(Ref*)
{
	m_pDelegate->gameEnd();
}