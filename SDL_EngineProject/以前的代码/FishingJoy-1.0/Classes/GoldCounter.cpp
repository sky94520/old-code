#include "GoldCounter.h"
#include "Gold.h"
#include "FishingJoyData.h"
GoldCounter::GoldCounter()
	//金币数默认为200 在以后扩展
	:m_nCoinCount(200),m_pLabel(nullptr)
{
}
GoldCounter::~GoldCounter()
{
	NotificationCenter::getInstance()->removeObserver(this,"sub coin");
	NotificationCenter::getInstance()->removeObserver(this,"add coin");
}
bool GoldCounter::init()
{
	//读取金币数据
	m_nCoinCount = FishingJoyData::getInstance()->getGold();

	m_pLabel = LabelAtlas::create(getCoinCountString(),"common-font.png"
		,16,24,'0');
	this->addChild(m_pLabel);
	//添加 减少金币 观察者
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(GoldCounter::subCoinCount),"sub coin");
	//     增加金币 观察者
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(GoldCounter::addCoinCount),"add coin");

	setContentSize(m_pLabel->getContentSize());
	return true;
}
void GoldCounter::addCoinCount(Object*obj)
{
	//todo
	Value*value = (Value*)obj;
	std::string text = value->asString();
	int goldNum=0,x=0,y=0;
	sscanf(text.c_str(),"%d %d %d",&goldNum,&x,&y);
	//调用金币动画
	auto gold = Gold::create();
	//设置金币位置
	gold->setPosition(Point(x,y)-getWorldPosition());
	this->addChild(gold);
	//设置终点位置
	Point endPos =  Point(getContentSize().width/2,getContentSize().height/2);
	float duration = (endPos-gold->getPosition()).length();
	MoveTo*move = MoveTo::create(duration/200,endPos);
	CallFunc*func = CallFunc::create([&,gold,goldNum]()
	{
		//增加金币
		m_nCoinCount += goldNum;
		//增加金币
		FishingJoyData::getInstance()->setGold(m_nCoinCount);
		m_pLabel->setString(getCoinCountString());
		gold->removeFromParent();
	});
	gold->runAction(Sequence::create(move,func,nullptr));
}
void GoldCounter::subCoinCount(Object*obj)
{
	//todo
	//Value value = (Value)obj; ???
	Value*value = (Value*)obj;
	//减少金币
	m_nCoinCount -= value->asInt();
	FishingJoyData::getInstance()->setGold(m_nCoinCount);
	
	m_pLabel->setString(getCoinCountString());
}
std::string GoldCounter::getCoinCountString()
{
	return StringUtils::format("%06d",m_nCoinCount);
}