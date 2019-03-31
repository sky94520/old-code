#include "HelpLayer.h"
#include "Fish.h"
#include "Fork.h"
#include "HelpfulFish.h"
#include "HelpfulFork.h"
#include "DynamicData.h"

HelpLayer::HelpLayer()
	:m_pDelegate(nullptr),m_nLength(100)
{
}
HelpLayer::~HelpLayer()
{
}
bool HelpLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite*bg = Sprite::create("small.jpg");
	Size s = bg->getContentSize();

	bg->setAnchorPoint(Point(1.f,1.f));
	bg->setPosition(visibleSize);

	this->addChild(bg);
	return true;
}
void HelpLayer::debugDraw()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//����λ��
	auto size = visibleSize/4;
	//����������
	/*Point personPos1 = Point(visibleSize.width - size.width,visibleSize.height);
	Point personPos2 = Point(visibleSize.width,visibleSize.height - m_nLength);
	glLineWidth(5.f);
	DrawPrimitives::drawRect(personPos1,personPos2);*/
	//��������
	Point fishPos1 = Point(visibleSize.width - size.width,visibleSize.height - m_nLength);
	Point fishPos2 = Point(visibleSize.width,visibleSize.height - size.height - m_nLength);
	glLineWidth(1.f);
	DrawPrimitives::drawRect(fishPos1,fishPos2);
	
}
void HelpLayer::showHelpfulFork(const Point&pos)
{
	//������ת��ΪСͼ����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//����λ��
	auto size = visibleSize/4;
	//�����������ԭ��
	Point center = Point(visibleSize.width - size.width,visibleSize.height - size.height - m_nLength);
	//������ʵ���� ���ý������� endPos1 Ϊ��ʵ��� endPos2Ϊ������λ��
	Point endPos1 = Point(pos.x/4,0) + center;

	Point startPos = endPos1 + Point(size.height,size.height);

	Point endPos2 = endPos1 + DynamicData::getInstance()->getOffsetRefraction()/4;
	//��ʾ���
	HelpfulFork*helpFork = HelpfulFork::create();
	helpFork->setRotation(45.f);
	helpFork->setAnchorPoint(Point(0.5f,0.f));
	helpFork->setScale(0.5f);
	helpFork->setPosition(startPos);

	this->addChild(helpFork);

	float delay = helpFork->runMovingAction(endPos1,endPos2);

	DelayTime*delayTime = DelayTime::create(delay+0.5f);
	CallFunc*end = CallFunc::create([&,helpFork](){
		helpFork->removeFromParent();
	});
	helpFork->runAction(Sequence::create(delayTime,end,nullptr));
}
void HelpLayer::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto size = visibleSize/4;
	//�����������ԭ��
	Point center = Point(visibleSize.width - size.width,visibleSize.height - size.height - m_nLength);
	//��ó����ڳ��ϵ����λ��
	auto fishes = m_pDelegate->getShowingFishes();
	
	for(int i=0;i<fishes->size();i++)
	{
		auto fish = fishes->at(i);
		//�������Ψһ����ID��ȡ��Ӧ�ĸ�����
		HelpfulFish*helpfulFish = this->getHelpfulFishByTag(fish->getRunningID());
		//�������򴴽�
		if(helpfulFish == nullptr)
		{
			helpfulFish = HelpfulFish::create(fish);
			helpfulFish->runNormalAnimation(fish);
			helpfulFish->setTag(fish->getRunningID());
			helpfulFish->setScale(0.5f);

			this->addChild(helpfulFish);
		}
		//����Ѿ�����׽����λ�ú�״̬�����ٸ���
		if(helpfulFish->getCaught())
			continue;
		//����λ��
		Point pos = center;
		pos.x += fish->getPosition().x/4;
		pos.y += size.height/15;//size.height/fish->getWeightMean();
		helpfulFish->setPosition(pos);
		//���¾���
		helpfulFish->updateSpriteStatus(fish);
		//����״̬
		if(fish->getStatus() == FishStatus::FishStatus_Caught)
		{
			auto duration = helpfulFish->runDeadAnimation(fish);
			DelayTime*delay = DelayTime::create(duration);
			CallFunc*end = CallFunc::create([&,helpfulFish](){
				helpfulFish->removeFromParent();
			});
			helpfulFish->setCaught(true);
			helpfulFish->runAction(Sequence::create(delay,end,NULL));
		} 
		if(fish->isVisible() == false)
		{
			helpfulFish->removeFromParent();
		}
	}
}
void HelpLayer::setDelegate(HelpLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
HelpfulFish*HelpLayer::getHelpfulFishByTag(int tag)
{
	auto node = this->getChildByTag(tag);
	if(node)
	{
		auto helpfulFish = dynamic_cast<HelpfulFish*>(node);
		return helpfulFish;
	}
	return nullptr;
}
