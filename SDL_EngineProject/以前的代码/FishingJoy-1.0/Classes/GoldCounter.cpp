#include "GoldCounter.h"
#include "Gold.h"
#include "FishingJoyData.h"
GoldCounter::GoldCounter()
	//�����Ĭ��Ϊ200 ���Ժ���չ
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
	//��ȡ�������
	m_nCoinCount = FishingJoyData::getInstance()->getGold();

	m_pLabel = LabelAtlas::create(getCoinCountString(),"common-font.png"
		,16,24,'0');
	this->addChild(m_pLabel);
	//��� ���ٽ�� �۲���
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(GoldCounter::subCoinCount),"sub coin");
	//     ���ӽ�� �۲���
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
	//���ý�Ҷ���
	auto gold = Gold::create();
	//���ý��λ��
	gold->setPosition(Point(x,y)-getWorldPosition());
	this->addChild(gold);
	//�����յ�λ��
	Point endPos =  Point(getContentSize().width/2,getContentSize().height/2);
	float duration = (endPos-gold->getPosition()).length();
	MoveTo*move = MoveTo::create(duration/200,endPos);
	CallFunc*func = CallFunc::create([&,gold,goldNum]()
	{
		//���ӽ��
		m_nCoinCount += goldNum;
		//���ӽ��
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
	//���ٽ��
	m_nCoinCount -= value->asInt();
	FishingJoyData::getInstance()->setGold(m_nCoinCount);
	
	m_pLabel->setString(getCoinCountString());
}
std::string GoldCounter::getCoinCountString()
{
	return StringUtils::format("%06d",m_nCoinCount);
}