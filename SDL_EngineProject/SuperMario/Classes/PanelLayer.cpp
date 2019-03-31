#include "PanelLayer.h"
#include "Entity.h"
#include "DynamicData.h"

PanelLayer::PanelLayer()
	:m_pScoreLabel(nullptr),m_pLevelLabel(nullptr)
	,m_pLifeLabel(nullptr),m_pCoinLabel(nullptr)
	,m_pTimeLabel(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	//添加外部界面
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/PanelLayer.xml");
	this->addChild(node);
	//获取对应的label
	m_pScoreLabel = node->getChildByName<LabelDotChar*>("score");
	m_pCoinLabel = node->getChildByName<LabelDotChar*>("coin");
	m_pLevelLabel = node->getChildByName<LabelDotChar*>("level");
	m_pLifeLabel = node->getChildByName<LabelDotChar*>("life");
	m_pTimeLabel = node->getChildByName<LabelDotChar*>("time");
	//添加事件
	_eventDispatcher->addEventCustomListener("score",SDL_CALLBACK_1(PanelLayer::scoreCallback,this),this);
	_eventDispatcher->addEventCustomListener("coin",SDL_CALLBACK_1(PanelLayer::coinCallback,this),this);
	_eventDispatcher->addEventCustomListener("level",SDL_CALLBACK_1(PanelLayer::levelCallback,this),this);
	_eventDispatcher->addEventCustomListener("life",SDL_CALLBACK_1(PanelLayer::lifeCallback,this),this);
	_eventDispatcher->addEventCustomListener("time",SDL_CALLBACK_1(PanelLayer::timeCallback,this),this);

	return true;
}

void PanelLayer::flowTextAction(Layer*parent,const string&text,const Point&positon)
{
	LabelDotChar*label = LabelDotChar::create(text,2,Color3B(255,255,255));
	label->setPosition(positon);
	parent->addChild(label);
	//添加动作
	MoveBy*move = MoveBy::create(1.f,Point(0,-30.f));
	RemoveSelf*removeSelf = RemoveSelf::create();
	
	Sequence*sequence = Sequence::createWithTwoActions(move,removeSelf);
	label->runAction(sequence);
}
void PanelLayer::blockBrokenAction(Layer*parent,Sprite*sprite)
{
	auto pos = sprite->getPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto spriteFrame = sprite->getSpriteFrame();
	auto r = spriteFrame->getRect();

	auto texture = sprite->getTexture();
	auto originalSize = spriteFrame->getOriginalSize();
	Sprite*sp1 = Sprite::createWithTexture(texture,Rect(r.origin.x,r.origin.y,r.size.width/2,r.size.height/2));
	Sprite*sp2 = Sprite::createWithTexture(texture,Rect(r.origin.x + r.size.width/2,r.origin.y,r.size.width/2,r.size.height/2));
	Sprite*sp3 = Sprite::createWithTexture(texture,Rect(r.origin.x,r.origin.y + r.size.height/2,r.size.width/2,r.size.height/2));
	Sprite*sp4 = Sprite::createWithTexture(texture,Rect(r.origin.x + r.size.width/2,r.origin.y + r.size.height/2,r.size.width/2,r.size.height/2));

	auto w = r.size.width/4;
	auto h = r.size.height/4;

	sp1->setPosition(pos + Point(-w,-h));
	sp2->setPosition(pos + Point(w,-h));
	sp3->setPosition(pos + Point(-w,h));
	sp4->setPosition(pos + Point(w,h));

	parent->addChild(sp1);
	parent->addChild(sp2);
	parent->addChild(sp3);
	parent->addChild(sp4);
	//运行动画
	float duration = 1.f;
	JumpTo*jump1 = JumpTo::create(duration,Point(pos.x - 100,visibleSize.height),-160,1);
	JumpTo*jump2 = JumpTo::create(duration,Point(pos.x + 100,visibleSize.height),-160,1);
	JumpTo*jump3 = JumpTo::create(duration,Point(pos.x - 80,visibleSize.height),-100,1);
	JumpTo*jump4 = JumpTo::create(duration,Point(pos.x + 80,visibleSize.height),-100,1);

	RotateBy*rotate1 = RotateBy::create(duration,180);
	RotateBy*rotate2 = RotateBy::create(duration,-180);
	RemoveSelf*remove = RemoveSelf::create();

	sp1->runAction(Sequence::createWithTwoActions(Spawn::createWithTwoActions(rotate1,jump1),remove));
	sp2->runAction(Sequence::createWithTwoActions(Spawn::createWithTwoActions(rotate2,jump2),remove->clone()));
	sp3->runAction(Sequence::createWithTwoActions(Spawn::createWithTwoActions(rotate1->clone(),jump3),remove->clone()));
	sp4->runAction(Sequence::createWithTwoActions(Spawn::createWithTwoActions(rotate2->clone(),jump4),remove->clone()));
}
void PanelLayer::goldAction(Layer*parent,const Point&position)
{
	Sprite*sprite = Sprite::createWithSpriteFrameName("gold00.png");
	sprite->setPosition(position);
	parent->addChild(sprite);
	//获取金币动画
	Animate* animate = Entity::createAnimate("gold%02d.png",0,3,0.03f,1);
	//上升动画
	MoveBy*up = MoveBy::create(animate->getDuration(),Point(0,-60.f));
	Spawn*spawn = Spawn::createWithTwoActions(animate,up);
	RemoveSelf*removeSelf = RemoveSelf::create();

	auto sequence = Sequence::create(spawn,removeSelf,NULL);
	sprite->runAction(sequence);
}
void PanelLayer::scoreCallback(EventCustom*eventCustom)
{
	auto score = DynamicData::getInstance()->getScore();
	auto text = StringUtils::format("%06d",score);
	m_pScoreLabel->setString(text);
}
void PanelLayer::coinCallback(EventCustom*eventCustom)
{
	auto coin = DynamicData::getInstance()->getCoin();
	auto text = StringUtils::format("%03d",coin);
	m_pCoinLabel->setString(text);
}
void PanelLayer::levelCallback(EventCustom*eventCustom)
{
}
void PanelLayer::lifeCallback(EventCustom*eventCustom)
{
	auto life = DynamicData::getInstance()->getLife();
	m_pLifeLabel->setString(to_string(life));
}
void PanelLayer::timeCallback(EventCustom*eventCustom)
{
	auto time = DynamicData::getInstance()->getRemainTime();
	m_pTimeLabel->setString(to_string(time));
}