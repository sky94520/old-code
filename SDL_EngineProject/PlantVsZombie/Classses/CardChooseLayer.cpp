#include "CardChooseLayer.h"
#include "LevelLayer.h"
#include "Card.h"
#include "StaticData.h"

CardChooseLayer::CardChooseLayer()
	:m_pSpriteBG(nullptr),m_pDelegate(nullptr)
	,m_pStartGameBtn(nullptr)
{
}

CardChooseLayer::~CardChooseLayer()
{
}

bool CardChooseLayer::init()
{
	//添加xml
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/CardChooseLayer.xml");
	this->addChild(node);
	//获取需要的控件
	m_pSpriteBG = node->getChildByName<Sprite*>("bg");
	m_pStartGameBtn = node->getChildByName<ui::Button*>("start_game");
	//绑定控件
	m_pStartGameBtn->addClickEventListener(SDL_CALLBACK_1(CardChooseLayer::start,this));

	return true;
}

void CardChooseLayer::setDelegate(CardChooseLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void CardChooseLayer::show(const vector<string>& cardNameList)
{
	int row = 0,column = 0;
	Point pos;
	Size bgSize = m_pSpriteBG->getContentSize();
	int localZOrder = 0;
	//遍历
	for (const auto& sName : cardNameList)
	{
		//生成对应卡片
		Card*card = m_pDelegate->makeCard(sName,CardType::Common);
		//生成对应背景
		Sprite*bg = card->getDisableSprite()->clone();
		//推导位置
		Size size = card->getContentSize();

		pos.y = row * size.height + size.height;
		pos.x = column * size.width + size.width/3 * 2;

		if (pos.x + size.width > bgSize.width)
		{
			row ++;
			column = 0;
		}
		else
		{
			column++;
		}
		//设置位置
		card->setPosition(pos);
		bg->setPosition(pos);
		//使card和bg相关联
		m_pSpriteBG->addChild(bg,localZOrder++,card->getUniqueID());
		m_pSpriteBG->addChild(card,localZOrder++);

		m_cards.push_back(card);
	}
}

Card* CardChooseLayer::getClickedCard(const Point&pos)
{
	//把该pos转为m_pSpriteBG
	auto nodePos = m_pSpriteBG->convertToNodeSpace(pos);

	for (auto card : m_cards)
	{
		auto rect = card->getBoundingBox();

		if (rect.containsPoint(nodePos))
			return card;
	}
	return nullptr;
}

bool CardChooseLayer::addCard(Card*card)
{
	bool ret = false;
	//根据卡片找打对应的背景
	auto uniqueID = card->getUniqueID();

	auto bg = m_pSpriteBG->getChildByTag<Sprite*>(uniqueID);

	if (bg != nullptr)
	{
		auto pos = bg->getPosition();

		card->setPosition(pos);

		m_cards.push_back(card);
		m_pSpriteBG->addChild(card,bg->getLocalZOrder() + 1);

		ret = true;
	}

	return ret;
}

bool CardChooseLayer::removeCard(Card*card)
{
	bool ret = false;
	//进行查找
	auto it = find(m_cards.begin(),m_cards.end(),card);

	if (it != m_cards.end())
	{
		m_cards.erase(it);
		card->removeFromParent();

		ret = true;
	}

	return ret;
}

void CardChooseLayer::setStartBtnEnable(bool enable)
{
	m_pStartGameBtn->setTouchEnabled(enable);
}

void CardChooseLayer::start(Object*sender)
{
	m_pDelegate->clickCardChooseStartBtn();
}