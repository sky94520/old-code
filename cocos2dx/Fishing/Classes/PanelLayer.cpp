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
	//ע���۲���
	NotificationCenter::getInstance()->removeObserver(this,"dynamic data");
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���ʣ�ಽ��Label
	//this->initWithTimes();
	//���ʤ������
	//this->initWithNeedfulFishes();
	//��ӹ۲���
	NotificationCenter::getInstance()->addObserver(this,
		CC_CALLFUNCO_SELECTOR(PanelLayer::updateSelf),"dynamic data",NULL);
	//����һ���Լ�
	//updateSelf(this);
	//�����ͣ��ť
	MenuItemImage*pauseBtn = MenuItemImage::create("pause_normal.png","pause_selected.png");
	pauseBtn->setCallback(CC_CALLBACK_1(PanelLayer::gamePause,this));
	Size size = pauseBtn->getContentSize();
	pauseBtn->setPosition(visibleSize.width/2 - size.width/2,visibleSize.height/2 - size.height/2);
	//��ӻ�ȡ���ಽ����ť
	MenuItemImage*questionBtn = MenuItemImage::create("gift.png","gift.png");
	//MenuItemLabel*questionBtn = MenuItemLabel::create(Label::create("more","fonts/DroidSansFallback.ttf",30));
	questionBtn->setAnchorPoint(Point(0.f,1.f));
	questionBtn->setPosition(-visibleSize.width/4,visibleSize.height/2);
	questionBtn->setCallback(CC_CALLBACK_1(PanelLayer::showQuestionLayer,this));

	Menu*menu = Menu::create(pauseBtn,questionBtn,NULL);
	/*����menu��λ��Ĭ��Ϊ��Ļ�м�*/
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
		//�������
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
		//����
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
		//����
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
	//����ʣ����ִ���
	int times = DynamicData::getInstance()->getAtkTimes();
	std::string text = StringUtils::format("%d",times);
	m_pTimesLabel->setString(text);
	//�жϵ�ǰ���ִ����Ƿ񵽴��ٽ�ֵ 1/4
	int nLimitTimes = 1/4.f * DynamicData::getInstance()->getAtkAllTimes();
	if(times <= nLimitTimes)
	{
		//�����˶���
		if(m_pTimesLabel->getActionByTag(1) == nullptr)
		{
			RepeatForever*action = RepeatForever::create(Blink::create(1.f,1));
			action->setTag(1);
			m_pTimesLabel->runAction(action);
		}
	}
	else
	{
		//���˶��У�ֹͣ����
		if(m_pTimesLabel->getActionByTag(1))
		{
			m_pTimesLabel->stopActionByTag(1);
			m_pTimesLabel->setVisible(true);
		}
	}
	//���¹�������
	auto needfulFishes = DynamicData::getInstance()->getNeedfulFishes();
	for(auto iter = needfulFishes.begin();iter != needfulFishes.end();iter++)
	{
		int id = iter->first;
		int count = iter->second;
		//��ȡ����Ӧ����� todo
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
	
	//���ʣ�ಽ��Label
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
		//����ͼƬ
		NeedfulFishCompent*comp = NeedfulFishCompent::create(id,num);
		
		m_compents.insert(make_pair(id,comp));

		comp->setTag(id);//�ܱ�֤id���Բ�ͬ
		comp->setAnchorPoint(Point(0.5f,1.f));
		//����λ��
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