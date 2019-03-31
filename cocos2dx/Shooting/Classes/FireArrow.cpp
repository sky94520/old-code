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
	//开始动画
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
	//调用死亡动画
	auto anim = Entity::createAnimate("arrowfire%d.png",1,6,0.05f,1);
	this->getSprite()->runAction(anim);
	//动画完成后隐藏
	DelayTime*delayTime = DelayTime::create(anim->getDuration());
	CallFunc*callfunc = CallFunc::create(CC_CALLBACK_0(FireArrow::onDeadCalback,this));
	this->runAction(Sequence::createWithTwoActions(delayTime,callfunc));
}
void FireArrow::onDeadCalback()
{
	m_bAlive = false;
	//停止一切动画
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//隐藏
	setVisible(false);
}
void FireArrow::end()
{
	m_bAlive = false;
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//箭保存一段时间后自动消失
	FadeIn*fade = FadeIn::create(1.f);
	CallFunc*callfunc = CallFunc::create([this]()
	{
		this->setVisible(false);
	});
	this->runAction(Sequence::createWithTwoActions(fade,callfunc));
}