#include "OperatorLayer.h"
#include "Hero.h"
#include "Global.h"
#include "SkillButton.h"
#include "GamePause.h"
OperatorLayer::OperatorLayer()
{
	Global::getInstance()->m_pOperatorLayer = this;
	m_pRocker = NULL;
	ControlButton*m_pNormalAttackBtn = NULL;
	m_bTouched = false;
}
OperatorLayer::~OperatorLayer()
{
}
bool OperatorLayer::init()
{
	if(!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//摇杆
	m_pRocker = Rocker::createRocker("Direction_bt.png","Direction_bc.png",&Point(50,0));
	m_pRocker->start();
	this->addChild(m_pRocker);
	//攻击按钮

	m_pNormalAttackBtn = ControlButton::create(Label::create("A","Market Felt",30),Scale9Sprite::create("attackbutton.png"));
	this->addChild(m_pNormalAttackBtn);
	Size attackBtnSize = m_pNormalAttackBtn->getContentSize();
	m_pNormalAttackBtn->setPosition(Point(visibleSize.width - attackBtnSize.width,attackBtnSize.height));
	
	m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::touchDown),Control::EventType::TOUCH_DOWN);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::dragInside),Control::EventType::DRAG_INSIDE);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::dragOutside ),Control::EventType::DRAG_OUTSIDE );  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::dragEnter),Control::EventType::DRAG_ENTER);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::dragExit),Control::EventType::DRAG_EXIT);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::touchUpInside),Control::EventType::TOUCH_UP_INSIDE);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::touchUpOutside ),Control::EventType::TOUCH_UP_OUTSIDE );  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::touchCancel),Control::EventType::TOUCH_CANCEL);  
    m_pNormalAttackBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(OperatorLayer::valueChanged),Control::EventType::VALUE_CHANGED);  
  
	//m_pNormalAttackBtn->addClickEventListener(ui::Widget::ccWidgetClickCallback(&OperatorLayer::attackButton));
	//添加技能按钮
	SkillButton*skillBtn = SkillButton::create("SkillNormal.png","SkillClicked.png","SkillNormal.png",1);
	skillBtn->setPosition(m_pNormalAttackBtn->getPosition() - Vec2(100,0));
	this->addChild(skillBtn);
	//返回层
	auto backBtn = ui::Button::create("back1.png","back2.png");
	Size backSize = backBtn->getContentSize();
	backBtn->setPosition(ccp(visibleSize.width - backSize.width,
		visibleSize.height - backSize.height));
	this->addChild(backBtn);
	backBtn->addClickEventListener([&](Ref*)
	{
		addChild(GamePause::create());
		Director::getInstance()->pause();

	});
	return true;
}
void OperatorLayer::normalAttackCallback(Ref* pSender,Control::EventType event)
{
	switch(event)
	{
	case Control::EventType::TOUCH_DOWN:
	case Control::EventType::DRAG_INSIDE:
		Global::getInstance()->m_pHero->onAttack(1);
		break;
	default:;
	}
}
void OperatorLayer::touchDown(Ref* pSender,Control::EventType event)
{
	/*if(Global::getInstance()->m_pHero->onAttack(m_nHeroNormalTime))
		m_nHeroNormalTime++;
	if(m_nHeroNormalTime>2)
	{
		m_nHeroNormalTime = 1;
		Global::getInstance()->m_pHero->onStop();
	}*/
	if(!m_bTouched)
		Global::getInstance()->m_pHero->onAttack(1);
	m_bTouched = true;
}
void OperatorLayer::dragInside(Ref* pSender,Control::EventType event)
{
	m_bTouched=true;
}
void OperatorLayer::dragOutside(Ref* pSender,Control::EventType event)
{
	m_bTouched =false;
}
void OperatorLayer::dragEnter(Ref* pSender,Control::EventType event)
{
}
void OperatorLayer::dragExit(Ref* pSender,Control::EventType event)
{
	m_bTouched = false;
}
void OperatorLayer::touchUpInside(Ref* pSender,Control::EventType event)
{
	m_bTouched = false;
}
void OperatorLayer::touchUpOutside(Ref* pSender,Control::EventType event)
{
	m_bTouched = false;
}
void OperatorLayer::touchCancel(Ref* pSender,Control::EventType event)
{
}
void OperatorLayer::valueChanged(Ref* pSender,Control::EventType event)
{
}
