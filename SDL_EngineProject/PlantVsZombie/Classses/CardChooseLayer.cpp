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
	//���xml
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/CardChooseLayer.xml");
	this->addChild(node);
	//��ȡ��Ҫ�Ŀؼ�
	m_pSpriteBG = node->getChildByName<Sprite*>("bg");
	m_pStartGameBtn = node->getChildByName<ui::Button*>("start_game");
	//�󶨿ؼ�
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
	//����
	for (const auto& sName : cardNameList)
	{
		//���ɶ�Ӧ��Ƭ
		Card*card = m_pDelegate->makeCard(sName,CardType::Common);
		//���ɶ�Ӧ����
		Sprite*bg = card->getDisableSprite()->clone();
		//�Ƶ�λ��
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
		//����λ��
		card->setPosition(pos);
		bg->setPosition(pos);
		//ʹcard��bg�����
		m_pSpriteBG->addChild(bg,localZOrder++,card->getUniqueID());
		m_pSpriteBG->addChild(card,localZOrder++);

		m_cards.push_back(card);
	}
}

Card* CardChooseLayer::getClickedCard(const Point&pos)
{
	//�Ѹ�posתΪm_pSpriteBG
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
	//���ݿ�Ƭ�Ҵ��Ӧ�ı���
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
	//���в���
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