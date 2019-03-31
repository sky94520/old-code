#include "ShopLayer.h"
#include "StartScene.h"
#include "DynamicData.h"

ShopLayer::ShopLayer()
	:m_pDelegate(nullptr)
{
}
ShopLayer::~ShopLayer()
{
}
bool ShopLayer::init()
{
	//加载资源
	//加载场景
	Node*layer = UIWidgetManager::getInstance()->createWidgetsWithXml("scene/ShopLayer.xml");
	this->addChild(layer);
	//获取对应组件
	//获取返回上一级按钮
	Button*backBtn = layer->getChildByName<Button*>("back");
	backBtn->addClickEventListener(SDL_CALLBACK_1(ShopLayer::back,this));
	//更新状态
	this->updateStatusOfWidget(layer->getChildByName("shop_player_life"));
//	this->updateStatusOfWidget(layer->getChildByName("shop_player_ressurect"));

	return true;
}
void ShopLayer::setDelegate(BackDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void ShopLayer::back(Object*sender)
{
	m_pDelegate->backToStartMenuLayer();
}
void ShopLayer::updateStatusOfWidget(Node*parent)
{
	auto name = parent->getName();

	LabelAtlas*pCurState = parent->getChildByName<LabelAtlas*>("curState");
	LabelAtlas*pNextState = parent->getChildByName<LabelAtlas*>("nextState");
	LabelAtlas*pWorth = parent->getChildByName<LabelAtlas*>("worth");
	//获取按钮并绑定对应函数
	Button*buy = parent->getChildByName<Button*>("buy");
	buy->addClickEventListener(SDL_CALLBACK_1(ShopLayer::buyCallback,this));
	//获取状态
	int curState = 0,nextState = 0;
	int worth = 0;

	if(name == "shop_player_life")
	{
		int curLevel = DynamicData::getInstance()->getLifeLevel();
		int nextLevel = DynamicData::getInstance()->getNextLifeLevel();
		//判断是否到达满级
		if(nextLevel == -1)
		{
			curLevel = nextLevel;
			curState = nextState = DynamicData::getInstance()->getPlayerLives();
		}
		else//获取需要的价钱并设置
		{
			worth = DynamicData::getInstance()->getWorthByLifeLevel(nextLevel);
			curState = DynamicData::getInstance()->getPlayerLives();
			nextState = DynamicData::getInstance()->getPlayerLives(nextLevel);
		}
	}
	else if(name == "shop_player_ressurect")
	{
	}
	//如果当前等级 == 下一级，设为不可见
	if(nextState == curState)
		pWorth->setVisible(false);
	pCurState->setString(std::to_string(curState));
	pNextState->setString(std::to_string(nextState));
	pWorth->setString(to_string(worth));
}
void ShopLayer::buyCallback(Object*sender)
{
	//判断点击的是哪个函数
	Node*btn = dynamic_cast<Widget*>(sender);
	//获取父类控件的名称
	auto name = btn->getParent()->getName();
	//是否购买成功
	bool bRet = false;
	if(name == "shop_player_life")
	{
		int nextLifeLevel = DynamicData::getInstance()->getNextLifeLevel();
		if(nextLifeLevel == -1)
		{
			//购买失败
			return;
		}
		//获取金币数
		int price = DynamicData::getInstance()->getWorthByLifeLevel(nextLifeLevel);
		bRet = DynamicData::getInstance()->alterPlayerGold(-price);
		if(bRet)
			DynamicData::getInstance()->setLifeLevel(nextLifeLevel);
	}
	else if(name == "shop_player_ressurect")
	{
	}
	if(bRet)
	{
		//购买成功
	}
	else
		;//购买失败
}