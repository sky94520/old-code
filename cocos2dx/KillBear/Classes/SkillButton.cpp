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
	//��Ӽ��ܰ�ť
	m_pButtonSkill = ui::Button::create(normalFile,selectedFile);
	//���Ӽ�����
	m_pButtonSkill->addClickEventListener(CC_CALLBACK_1(SkillButton::clickCallback,this));
	m_pButtonSkill->setPosition(Vec2::ZERO);
	//����ɰ�
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
	//�����ת������
	m_pProgressTimer = ProgressTimer::create(Sprite::create(normalFile));
	//����Ϊ�������
	m_pProgressTimer->setType(ProgressTimer::Type::RADIAL);
	m_pProgressTimer->setPosition(Vec2::ZERO);
	m_pProgressTimer->setVisible(false);
	
	this->setCurCDTime(cdTime);
	m_fCDTime = cdTime;

	m_pCurTimeLabel = Label::create();
	m_pCurTimeLabel->setSystemFontSize(m_pMask->getContentSize().width/3);
	m_pCurTimeLabel->setColor(Color3B(0,0,0));
	m_pCurTimeLabel->setVisible(false);
	//���Ԫ��
	this->addChild(m_pButtonSkill);
	this->addChild(m_pMask);
	this->addChild(m_pProgressTimer);
	this->addChild(m_pCurTimeLabel);
	return true;
}
void SkillButton::clickCallback(Ref*pRef)
{
	Global::getInstance()->m_pHero->runSkillAction();
		//���ü��ܰ�ť���ɵ��
	m_pButtonSkill->setEnabled(false);
	//�����ɰ�ɼ�
	m_pMask->setVisible(true);
	//���ý������ɼ�
	m_pProgressTimer->setVisible(true);
	//����ʣ��ʱ��ɼ�
	m_pCurTimeLabel->setVisible(true);
	//������ʱ��
	this->schedule(schedule_selector(SkillButton::coolDownReduce),0.1f);
	//����һ������
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
	//���ü��ܿɵ��
	m_pButtonSkill->setEnabled(true);
	//���������Ĳ��ɼ�
	m_pProgressTimer->setVisible(false);
	m_pProgressTimer->setPercentage(0);
	m_pCurTimeLabel->setVisible(false);
	m_fCurCDTime = m_fCDTime;
	//ȡ����ʱ��
	this->unschedule(schedule_selector(SkillButton::coolDownReduce));
}