#include "FireArrow.h"
#include "RotateWithAction.h"
FireArrow::FireArrow()
{
}
FireArrow::~FireArrow()
{
}
bool FireArrow::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("arrow1.png"));
	setVisible(false);
	return true;
}
void FireArrow::start(const Point&from,const Point&to)
{
	m_bAlive = true;
	this->setPosition(from);
	this->setVisible(true);
	//��ʼ����
	auto vector = to - from;
	_ccBezierConfig bezierConfig;
	bezierConfig.controlPoint_1 = bezierConfig.controlPoint_2 = vector;
	bezierConfig.endPosition = to-from;

	BezierBy*bezier = BezierBy::create(vector.length()/200.f,bezierConfig);
	CallFunc*callfunc = CallFunc::create(CC_CALLBACK_0(FireArrow::end,this));
	this->runAction(Sequence::create(RotateWithAction::create(bezier),callfunc,nullptr));
}
void FireArrow::dead()
{
	//������������
	auto anim = Entity::createAnimate("arrowfire%d.png",1,6,0.05f,1);
	this->getSprite()->runAction(anim);
	//������ɺ�����
	DelayTime*delayTime = DelayTime::create(anim->getDuration());
	CallFunc*callfunc = CallFunc::create(CC_CALLBACK_0(FireArrow::onDeadCalback,this));
	this->runAction(Sequence::createWithTwoActions(delayTime,callfunc));
}
void FireArrow::onDeadCalback()
{
	m_bAlive = false;
	//ֹͣһ�ж���
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//����
	setVisible(false);
}
void FireArrow::end()
{
	m_bAlive = false;
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//������һ��ʱ����Զ���ʧ
	FadeIn*fade = FadeIn::create(1.f);
	CallFunc*callfunc = CallFunc::create([this]()
	{
		this->setVisible(false);
	});
	this->runAction(Sequence::createWithTwoActions(fade,callfunc));
}