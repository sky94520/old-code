#include "Fish.h"
#include "CsvUtil.h"
#include "RotateWithAction.h"
#include "FishingJoyData.h"
Fish::Fish()
	:m_bAlive(false),m_elpased(0.f),m_nScore(4),m_fSuccessRate(0.5)
	,m_nID(1),m_nRunFrame(0),m_nDeadFrame(0)
{
}
Fish::~Fish()
{
}
Fish*Fish::create(int id)
{
	auto fish = new Fish();
	if(fish && fish->init(id))
		fish->autoRelease();
	else
		SDL_SAFE_DELETE(fish);
	return fish;
}
bool Fish::init()
{
	//�󶨾���
	bindSprite(Sprite::createWithSpriteFrameName("fish01_00.png"));
	m_pSprite->setFlipX(true);
	//����
	return true;
}
bool Fish::init(int id)
{
	std::string fileName = "Resources/fish.csv";
	//�ҵ��������ڵ���
	unsigned int nLine = -1;
	if(nLine < 0)
		return false;
	m_nID = id;
	nLine = CsvUtil::getInstance()->findLineByValue(Value(id),0,fileName);
	std::string name = CsvUtil::getInstance()->getValue(nLine,1,fileName).asString();
	std::string description = CsvUtil::getInstance()->getValue(nLine,2,fileName).asString();
	m_nScore = CsvUtil::getInstance()->getValue(nLine,3,fileName).asInt();
	m_fSuccessRate = CsvUtil::getInstance()->getValue(nLine,4,fileName).asFloat();
	m_nRunFrame = CsvUtil::getInstance()->getValue(nLine,5,fileName).asInt();
	m_nDeadFrame = CsvUtil::getInstance()->getValue(nLine,6,fileName).asInt();
	m_nRareRate = CsvUtil::getInstance()->getValue(nLine,7,fileName).asInt();

	std::string format = StringUtils::format("fish%02d_00.png",id);
	bindSprite(Sprite::createWithSpriteFrameName(format));
	//m_pSprite->setFlipX(true);
	return true;
}
void Fish::reset()
{
	m_bAlive = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size fishSize = getContentSize();
	//����
	setVisible(false);
	setRotation(0);
	setFlipX(false);

	stopAllActions();
	getSprite()->stopAllActions();
	//���������Ŷ�ú����
	m_elpased = RANDOM_0_1()*3;
	//���ü�ʱ��
	this->scheduleOnce(schedule_selector(Fish::show),m_elpased);
}
void Fish::update(float dt)
{
	//������
	if(!m_bAlive)
		return;
	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���������Ļ��Χ������m_bAlive = false
	Rect rect=Rect(0,0,visibleSize.width,visibleSize.height);
	Rect fishRect=Rect(getWorldPosition(),getContentSize());
	if(!rect.intersectsRect(fishRect))
	{
		m_bAlive = false;
		
		reset();
	}*/
}
bool Fish::isAlive()const
{
	return m_bAlive;
}
float Fish::getSuccessRate()const
{
	return m_fSuccessRate;
}
unsigned int Fish::getRareRate()const
{
	return m_nRareRate;
}
int Fish::getID()const
{
	return m_nID;
}
void Fish::show(float dt)
{
	m_bAlive = true;
	setVisible(true);

	stopAllActions();
	getSprite()->stopAllActions();
	//��Ӷ���
	auto format = StringUtils::format("fish%02d_%s.png",m_nID,"%02d");
	auto anim = Entity::createAnimate(format,0,m_nRunFrame-1,0.1f);
	m_pSprite->runAction(anim);
	//ȷ��·�� z���Ժ���չ
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���ó�ʼλ��
	float x0 = visibleSize.width;
	float y0 = RANDOM(0,visibleSize.height - 100);
	
	float x1 = -getContentSize().width;
	float y1 = RANDOM(0,visibleSize.height - 100);
	int direction = RANDOM(0,2);
	ActionInterval*move = nullptr;
	if(direction)
		move=lineRoute(Point(x0,y0),Point(x1,y1),6,true);//����
	else
		move=lineRoute(Point(x1,y1),Point(x0,y0),6,false);//����

	this->runAction(move);
}
void Fish::catched()
{
	m_bAlive = false;
	//ֹͣ����
	this->getSprite()->setRotation(0);
	this->getSprite()->stopAllActions();
	this->stopAllActions();
	//��ı���׽����
	auto format = StringUtils::format("fish%02d_%s.png",m_nID,"d%02d");
	auto anim = Entity::createAnimate(format,0,m_nDeadFrame-1,0.15f);
	this->getSprite()->runAction(anim);

	CallFunc*getCoinFunc = CallFunc::create([&,this]()
	{
		auto pos = this->getWorldPosition();
		auto size = this->getContentSize();
		std::string text = StringUtils::format("%d %.0f %.0f",m_nScore,pos.x+size.width/2,pos.y+size.height/2);
		Value value = Value(text);
		FishingJoyData::getInstance()->alterGold(value,true);
		//�������ú���
		Fish::reset();
	});
	this->runAction(Sequence::create(DelayTime::create(m_nDeadFrame * 0.3),getCoinFunc,nullptr));
}
ActionInterval*Fish::lineRoute(const Point&from,const Point&to,float duration,bool direction)
{
	setPosition(from);
	this->getSprite()->setFlipX(!direction);
	MoveBy*move = MoveBy::create(duration,to - from);

	RotateWithAction*action = RotateWithAction::create(move);
	return Sequence::createWithTwoActions(action,CallFunc::create([&](){
		reset();
	}));
}
