#include "CardLayer.h"
#include "Card.h"
#include "StaticData.h"
#include "LevelLayer.h"

CardLayer::CardLayer()
	:m_pSelectedCard(nullptr),m_pSelectedHigh(nullptr)
{
}
CardLayer::~CardLayer()
{
}
bool CardLayer::init()
{
	//选中高亮的初始化
	auto spriteFrameName = STATIC_DATA_STRING("selected_high_sprite_name");
	m_pSelectedHigh = Sprite::createWithSpriteFrameName(spriteFrameName);
	m_pSelectedHigh->setVisible(false);

	this->addChild(m_pSelectedHigh,999);

	return true;
}
void CardLayer::update(float dt)
{
	for(unsigned int i = 0;i < m_cards.size();i++)
	{
		auto card = m_cards.at(i);
		card->update(dt);
	}
}

bool CardLayer::addCard(const std::string &name,CardType type)
{
	auto card = this->makeCard(name,type);

	this->addCard(card);

	return true;
}

void CardLayer::addCard(Card*card)
{
	auto index = m_cards.size();
	//根据卡片槽获取对应位置
	auto pos = m_cardSlotBGList.at(index)->getPosition();
	card->setPosition(pos);

	m_cards.push_back(card);
	this->addChild(card);
}

void CardLayer::removeCard(Card*card)
{
	//当前选中了该卡片，则先取消选中
	if (card == m_pSelectedCard)
		this->unselectedCard();

	unsigned int index = 0;

	auto it = find(m_cards.begin(),m_cards.end(),card);

	if (it != m_cards.end())
	{
		//获取index
		index = it - m_cards.begin();
		//重新排序
		for (;index + 1 < m_cards.size();index++)
		{
			auto temp = m_cards.at(index + 1);
			auto pos = m_cardSlotBGList.at(index)->getPosition();

			temp->setPosition(pos);
		}
		//移除
		m_cards.erase(it);

		card->removeFromParent();
	}
}

Card*CardLayer::makeCard(const std::string& name,CardType type)
{
	Card*card = nullptr;
	//获取加载的对应的结构体
	auto cardStruct = StaticData::getInstance()->getCardStruct(name);

	if (cardStruct == nullptr)
	{
		return nullptr;
	}

	if (type == CardType::Common)
	{
		card = Card::create(name,cardStruct->worth);
		//设置准备时间
		card->setCurCD(cardStruct->readyTime);
		card->setCD(cardStruct->cd);
	}
	else if (type == CardType::Consumable)
	{
		card = Card::createConsumableCard(name);
	}
	//设置一些基础属性
	card->setNeedfulTerrains(cardStruct->terrains);
	card->setNecessoryItem(cardStruct->necessoryItem);
	card->setActiveTime(cardStruct->active);

	return card;
}

void CardLayer::setCardSlotNum(unsigned int num,LevelCardType levelType)
{
	unsigned int curCardSlotNum = m_cardSlotBGList.size();
	//开始位置
	Point startPos(50.f,50.f);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//确定卡槽位置
	if (levelType == LevelCardType::Zombie)
	{
		startPos.x = visibleSize.width - startPos.x;
	}
	//添加卡片
	for (unsigned int i = curCardSlotNum;i < num;i++)
	{
		Sprite*cardSlot = Sprite::create("card_slot.png");
		auto size = cardSlot->getContentSize();
		//推导位置
		auto pos = startPos + Point(0,i*size.height);
		
		cardSlot->setPosition(pos);
		//添加
		this->addChild(cardSlot);
		m_cardSlotBGList.push_back(cardSlot);
	}
}

void CardLayer::hideUnusedCardSlot()
{
	unsigned int index = m_cards.size();
	//隐藏未使用的卡槽
	for (;index < m_cardSlotBGList.size();index++)
	{
		auto sprite = m_cardSlotBGList.at(index);
		sprite->setVisible(false);
	}
}

bool CardLayer::isFullOfCardSlot()const
{
	auto num = m_cardSlotBGList.size();

	return m_cards.size() >= num;
}

Card* CardLayer::getClickedCard(const Point&pos)
{
	for (auto card : m_cards)
	{
		auto rect = card->getBoundingBox();

		if (rect.containsPoint(pos))
			return card;
	}
	return nullptr;
}

Card* CardLayer::getSelectedCard()
{
	return m_pSelectedCard;
}

void CardLayer::setSelectedCard(Card*card)
{
	//如果当前已经选中，则取消选中
	m_pSelectedCard = card;
	//设置选中
	auto pos = m_pSelectedCard->getPosition();

	m_pSelectedHigh->setVisible(true);
	m_pSelectedHigh->setPosition(pos);
}

void CardLayer::unselectedCard()
{
	m_pSelectedHigh->setVisible(false);
	m_pSelectedCard = nullptr;
}

void CardLayer::updateSelf()
{
	this->update(0.f);
}
