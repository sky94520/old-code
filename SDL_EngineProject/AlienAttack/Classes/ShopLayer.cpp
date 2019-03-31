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
	//������Դ
	//���س���
	Node*layer = UIWidgetManager::getInstance()->createWidgetsWithXml("scene/ShopLayer.xml");
	this->addChild(layer);
	//��ȡ��Ӧ���
	//��ȡ������һ����ť
	Button*backBtn = layer->getChildByName<Button*>("back");
	backBtn->addClickEventListener(SDL_CALLBACK_1(ShopLayer::back,this));
	//����״̬
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
	//��ȡ��ť���󶨶�Ӧ����
	Button*buy = parent->getChildByName<Button*>("buy");
	buy->addClickEventListener(SDL_CALLBACK_1(ShopLayer::buyCallback,this));
	//��ȡ״̬
	int curState = 0,nextState = 0;
	int worth = 0;

	if(name == "shop_player_life")
	{
		int curLevel = DynamicData::getInstance()->getLifeLevel();
		int nextLevel = DynamicData::getInstance()->getNextLifeLevel();
		//�ж��Ƿ񵽴�����
		if(nextLevel == -1)
		{
			curLevel = nextLevel;
			curState = nextState = DynamicData::getInstance()->getPlayerLives();
		}
		else//��ȡ��Ҫ�ļ�Ǯ������
		{
			worth = DynamicData::getInstance()->getWorthByLifeLevel(nextLevel);
			curState = DynamicData::getInstance()->getPlayerLives();
			nextState = DynamicData::getInstance()->getPlayerLives(nextLevel);
		}
	}
	else if(name == "shop_player_ressurect")
	{
	}
	//�����ǰ�ȼ� == ��һ������Ϊ���ɼ�
	if(nextState == curState)
		pWorth->setVisible(false);
	pCurState->setString(std::to_string(curState));
	pNextState->setString(std::to_string(nextState));
	pWorth->setString(to_string(worth));
}
void ShopLayer::buyCallback(Object*sender)
{
	//�жϵ�������ĸ�����
	Node*btn = dynamic_cast<Widget*>(sender);
	//��ȡ����ؼ�������
	auto name = btn->getParent()->getName();
	//�Ƿ���ɹ�
	bool bRet = false;
	if(name == "shop_player_life")
	{
		int nextLifeLevel = DynamicData::getInstance()->getNextLifeLevel();
		if(nextLifeLevel == -1)
		{
			//����ʧ��
			return;
		}
		//��ȡ�����
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
		//����ɹ�
	}
	else
		;//����ʧ��
}