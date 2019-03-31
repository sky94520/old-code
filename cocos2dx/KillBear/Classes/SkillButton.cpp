#include "SkillButton.h"
#include "Global.h"
#include "Hero.h"
SkillButton::SkillButton():
	m_pButtonSkill(NULL),
	m_pMask(NULL),
	m_pProgressTimer(NULL),
	m_pCurTimeLabel(NULL),
	m_fCDTime(1.f)
{
}
SkillButton::~SkillButton()
{
}
SkillButton*SkillButton::create(const char*normalFile,const char*selectedFile,const char*mask,float cdTime)
{
	SkillButton*_class = new SkillButton();
	if(_class && _class->init(normalFile,selectedFile,mask,cdTime))
		_class->autorelease();
	else
		CC_SAFE_DELETE(_class);
	return _class;
}
bool SkillButton::init(const char*normalFile,const char*selectedFile,const char*mask,float cdTime)
{
	if(!Node::init())
		return false;
	//添加技能按钮
	m_pButtonSkill = ui::Button::create(normalFile,selectedFile);
	//增加监听器
	m_pButtonSkill->addClickEventListener(CC_CALLBACK_1(SkillButton::clickCallback,this));
	m_pButtonSkill->setPosition(Vec2::ZERO);
	//添加蒙版
	if(mask == normalFile)
	{
		m_pMask = Sprite::create();
		m_pMask->setTexture(mask);
		m_pMask->setColor(Color3B(0,0,0));
		m_pMask->setOpacity(100);
	}
	else
		m_pMask = Sprite::create(mask);
	m_pMask->setPosition(Vec2::ZERO);
	//添加旋转进度条
	m_pProgressTimer = ProgressTimer::create(Sprite::create(normalFile));
	//设置为轴进度条
	m_pProgressTimer->setType(ProgressTimer::Type::RADIAL);
	m_pProgressTimer->setPosition(Vec2::ZERO);
	m_pProgressTimer->setVisible(false);
	
	this->setCurCDTime(cdTime);
	m_fCDTime = cdTime;

	m_pCurTimeLabel = Label::create();
	m_pCurTimeLabel->setSystemFontSize(m_pMask->getContentSize().width/3);
	m_pCurTimeLabel->setColor(Color3B(0,0,0));
	m_pCurTimeLabel->setVisible(false);
	//添加元素
	this->addChild(m_pButtonSkill);
	this->addChild(m_pMask);
	this->addChild(m_pProgressTimer);
	this->addChild(m_pCurTimeLabel);
	return true;
}
void SkillButton::clickCallback(Ref*pRef)
{
	Global::getInstance()->m_pHero->runSkillAction();
		//设置技能按钮不可点击
	m_pButtonSkill->setEnabled(false);
	//设置蒙版可见
	m_pMask->setVisible(true);
	//设置进度条可见
	m_pProgressTimer->setVisible(true);
	//设置剩余时间可见
	m_pCurTimeLabel->setVisible(true);
	//开启定时器
	this->schedule(schedule_selector(SkillButton::coolDownReduce),0.1f);
	//创建一个动画
	ActionInterval*actionProgressTo = Sequence::create(ProgressTo::create(this->getCurCDTime(),100),NULL);
	CallFunc*call = CallFuncN::create(CC_CALLBACK_1(SkillButton::coolDownCallback,this));
	m_pProgressTimer->runAction(Sequence::create(actionProgressTo,call,NULL));
}
void SkillButton::coolDownReduce(float dt)
{
	m_pCurTimeLabel->setString(StringUtils::format("%.1f",m_fCurCDTime -= 0.1f));
}
void SkillButton::coolDownCallback(Node*pNode)
{
	//设置技能可点击
	m_pButtonSkill->setEnabled(true);
	//设置其他的不可见
	m_pProgressTimer->setVisible(false);
	m_pProgressTimer->setPercentage(0);
	m_pCurTimeLabel->setVisible(false);
	m_fCurCDTime = m_fCDTime;
	//取消定时器
	this->unschedule(schedule_selector(SkillButton::coolDownReduce));
}