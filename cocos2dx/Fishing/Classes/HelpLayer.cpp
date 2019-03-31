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
	//绘制位置
	auto size = visibleSize/4;
	//绘制人物区
	/*Point personPos1 = Point(visibleSize.width - size.width,visibleSize.height);
	Point personPos2 = Point(visibleSize.width,visibleSize.height - m_nLength);
	glLineWidth(5.f);
	DrawPrimitives::drawRect(personPos1,personPos2);*/
	//绘制鱼区
	Point fishPos1 = Point(visibleSize.width - size.width,visibleSize.height - m_nLength);
	Point fishPos2 = Point(visibleSize.width,visibleSize.height - size.height - m_nLength);
	glLineWidth(1.f);
	DrawPrimitives::drawRect(fishPos1,fishPos2);
	
}
void HelpLayer::showHelpfulFork(const Point&pos)
{
	//把坐标转换为小图坐标
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//绘制位置
	auto size = visibleSize/4;
	//捕鱼帮助区的原点
	Point center = Point(visibleSize.width - size.width,visibleSize.height - size.height - m_nLength);
	//设置真实坐标 设置结束坐标 endPos1 为真实鱼叉 endPos2为虚假鱼叉位置
	Point endPos1 = Point(pos.x/4,0) + center;

	Point startPos = endPos1 + Point(size.height,size.height);

	Point endPos2 = endPos1 + DynamicData::getInstance()->getOffsetRefraction()/4;
	//显示鱼叉
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
	//捕鱼帮助区的原点
	Point center = Point(visibleSize.width - size.width,visibleSize.height - size.height - m_nLength);
	//获得出现在场上的鱼的位置
	auto fishes = m_pDelegate->getShowingFishes();
	
	for(int i=0;i<fishes->size();i++)
	{
		auto fish = fishes->at(i);
		//根据鱼的唯一运行ID获取对应的辅助鱼
		HelpfulFish*helpfulFish = this->getHelpfulFishByTag(fish->getRunningID());
		//不存在则创建
		if(helpfulFish == nullptr)
		{
			helpfulFish = HelpfulFish::create(fish);
			helpfulFish->runNormalAnimation(fish);
			helpfulFish->setTag(fish->getRunningID());
			helpfulFish->setScale(0.5f);

			this->addChild(helpfulFish);
		}
		//如果已经被捕捉，则位置和状态都不再更新
		if(helpfulFish->getCaught())
			continue;
		//更新位置
		Point pos = center;
		pos.x += fish->getPosition().x/4;
		pos.y += size.height/15;//size.height/fish->getWeightMean();
		helpfulFish->setPosition(pos);
		//更新精灵
		helpfulFish->updateSpriteStatus(fish);
		//更新状态
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
