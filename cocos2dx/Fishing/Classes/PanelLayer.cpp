#include "PanelLayer.h"
#include "DynamicData.h"
#include "NeedfulFishCompent.h"

PanelLayer::PanelLayer()
	:m_pTimesLabel(nullptr),m_pDelegate(nullptr)
	,m_bShowAllComp(false)
{
}
PanelLayer::~PanelLayer()
{
	//注销观察者
	NotificationCenter::getInstance()->removeObserver(this,"dynamic data");
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加剩余步数Label
	//this->initWithTimes();
	//添加胜利条件
	//this->initWithNeedfulFishes();
	//添加观察者
	NotificationCenter::getInstance()->addObserver(this,
		CC_CALLFUNCO_SELECTOR(PanelLayer::updateSelf),"dynamic data",NULL);
	//更新一次自己
	//updateSelf(this);
	//添加暂停按钮
	MenuItemImage*pauseBtn = MenuItemImage::create("pause_normal.png","pause_selected.png");
	pauseBtn->setCallback(CC_CALLBACK_1(PanelLayer::gamePause,this));
	Size size = pauseBtn->getContentSize();
	pauseBtn->setPosition(visibleSize.width/2 - size.width/2,visibleSize.height/2 - size.height/2);
	//添加获取更多步数按钮
	MenuItemImage*questionBtn = MenuItemImage::create("gift.png","gift.png");
	//MenuItemLabel*questionBtn = MenuItemLabel::create(Label::create("more","fonts/DroidSansFallback.ttf",30));
	questionBtn->setAnchorPoint(Point(0.f,1.f));
	questionBtn->setPosition(-visibleSize.width/4,visibleSize.height/2);
	questionBtn->setCallback(CC_CALLBACK_1(PanelLayer::showQuestionLayer,this));

	Menu*menu = Menu::create(pauseBtn,questionBtn,NULL);
	/*现在menu的位置默认为屏幕中间*/
	//menu->setPosition(visibleSize.width - size.width/2,visibleSize.height - size.height/2);
	this->addChild(menu);

	return true;
}
void PanelLayer::clean()
{
	for(auto iter=m_compents.begin();iter != m_compents.end();)
	{
		auto id = iter->first;
		//auto child = iter->second;
		//清除孩子
		this->removeChildByTag(id);
		iter = m_compents.erase(iter);
	}
	if(m_pTimesLabel)
	{
		this->removeChild(m_pTimesLabel);
		m_pTimesLabel = nullptr;
	}
}
void PanelLayer::setDelegate(PanelLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void PanelLayer::showAllNeedfulFishesComp()
{
	for(auto iter = m_compents.begin();iter != m_compents.end();++iter)
	{
		auto comp = iter->second;
		//动作
		MoveTo*move = MoveTo::create(0.5f,comp->getCompPosition());
		comp->runAction(move);
	}
}
void PanelLayer::hideAllNeedfulFishesComp()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for(auto iter = m_compents.begin();iter != m_compents.end();++iter)
	{
		auto comp = iter->second;
		//动作
		MoveTo*move = MoveTo::create(0.5f,Point(visibleSize.width/2,visibleSize.height));
		comp->runAction(move);
	}
}
bool PanelLayer::isClickedComponents(const Point&pos)const
{
	for(auto iter = m_compents.begin();iter != m_compents.end();++iter)
	{
		auto comp = iter->second;
		Rect r = comp->getBoundingBox();
		if(r.containsPoint(pos))
			return true;
	}
}
bool PanelLayer::isShowAllComp()const
{
	return m_bShowAllComp;
}
void PanelLayer::setShowAllComp(bool c)
{
	m_bShowAllComp = c;
}
void PanelLayer::updateSelf(Ref*sender)
{
	//更新剩余出手次数
	int times = DynamicData::getInstance()->getAtkTimes();
	std::string text = StringUtils::format("%d",times);
	m_pTimesLabel->setString(text);
	//判断当前出手次数是否到达临界值 1/4
	int nLimitTimes = 1/4.f * DynamicData::getInstance()->getAtkAllTimes();
	if(times <= nLimitTimes)
	{
		//不在运动中
		if(m_pTimesLabel->getActionByTag(1) == nullptr)
		{
			RepeatForever*action = RepeatForever::create(Blink::create(1.f,1));
			action->setTag(1);
			m_pTimesLabel->runAction(action);
		}
	}
	else
	{
		//在运动中，停止动画
		if(m_pTimesLabel->getActionByTag(1))
		{
			m_pTimesLabel->stopActionByTag(1);
			m_pTimesLabel->setVisible(true);
		}
	}
	//更新过关条件
	auto needfulFishes = DynamicData::getInstance()->getNeedfulFishes();
	for(auto iter = needfulFishes.begin();iter != needfulFishes.end();iter++)
	{
		int id = iter->first;
		int count = iter->second;
		//获取到对应的组件 todo
		NeedfulFishCompent*comp = m_compents.find(id)->second;//dynamic_cast<NeedfulFishCompent*>(this->getChildByTag(id));
		
		int lastCount = comp->getCount();
		if(lastCount == count)
		{
			comp->setLocalZOrder(1);
		}
		else
		{
			comp->setCount(count);
			comp->setLocalZOrder(2);
		}
	}
}
bool PanelLayer::initWithTimes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label*step = Label::createWithTTF("step:","fonts/Marker Felt.ttf",20);
	Size stepSize = step->getContentSize();
	step->setPosition(stepSize.width/2,visibleSize.height - stepSize.height/2);
	this->addChild(step);
	
	//添加剩余步数Label
	int nStep = DynamicData::getInstance()->getAtkTimes();

	m_pTimesLabel = Label::createWithCharMap("LabelAtlas.png",21,21,'0');
	m_pTimesLabel->setString(Value(nStep).asString());
	m_pTimesLabel->setAnchorPoint(Point(0.f,1.f));
	m_pTimesLabel->setPosition(stepSize.width,visibleSize.height);
	this->addChild(m_pTimesLabel);

	return true;
}
bool PanelLayer::initWithNeedfulFishes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float height = visibleSize.height;

	map<int,int> needfulFishes = DynamicData::getInstance()->getNeedfulFishes();
	for(auto iter = needfulFishes.begin();iter != needfulFishes.end();iter++)
	{
		int id = iter->first;
		int num = iter->second;
		//加载图片
		NeedfulFishCompent*comp = NeedfulFishCompent::create(id,num);
		
		m_compents.insert(make_pair(id,comp));

		comp->setTag(id);//能保证id绝对不同
		comp->setAnchorPoint(Point(0.5f,1.f));
		//设置位置
		comp->setPosition(visibleSize.width/2,visibleSize.height);
		comp->setCompPosition(Point(visibleSize.width/2,height));
		height -= comp->getContentSize().height;
		this->addChild(comp);
	}
	return true;
}
void PanelLayer::gamePause(Ref*sender)
{
	m_pDelegate->gamePause();
}
void PanelLayer::showQuestionLayer(Ref*sender)
{
	m_pDelegate->showQuestionLayer();
}