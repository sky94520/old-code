#include "Card.h"
#include "StaticData.h"
#include "DynamicData.h"

Card::Card()
	:m_pNormalSprite(nullptr),m_pDisableSprite(nullptr)
	,m_pNumberLabel(nullptr),m_type(CardType::Common)
	,m_fCurCD(0.f),m_fCD(0.f),m_nWorth(0)
	,m_description(""),m_pCDTimer(nullptr)
	,m_activeTime(ActiveTime::All)
{
}
Card::~Card()
{
}
Card*Card::createConsumableCard(const std::string& name)
{
	auto card = new Card();

	if(card && card->init(name))
		card->autorelease();
	else
		SDL_SAFE_DELETE(card);
	return card;
}

Card* Card::create(const string&name,int number)
{
	auto card = new Card();

	if (card && card->init(name,number))
		card->autorelease();
	else
		SDL_SAFE_DELETE(card);

	return card;
}
bool Card::init(const std::string& name)
{
	m_cardName = name;
	//设置卡片类型
	m_type = CardType::Consumable;
	//设置显示精灵
	this->setNormalSprite(name);

	return true;
}

bool Card::init(const string&name,int number)
{
	m_nWorth = number;
	m_cardName = name;
	//设置卡片类型
	m_type = CardType::Common;
	//设置显示精灵
	this->setNormalSprite(name);
	this->setDisableSprite(name);
	
	auto size = this->getContentSize();
	//创建cd timer
	auto greyName = STATIC_DATA_STRING("card_grey_sprite_name");
	Sprite*sprite = Sprite::createWithSpriteFrameName(greyName);
	m_pCDTimer = ProgressTimer::create(sprite);
	m_pCDTimer->setType(ProgressTimer::Type::BAR);
	m_pCDTimer->setBarChangeRate(Point(0,1.f));
	m_pCDTimer->setMidpoint(Point::ZERO);
	m_pCDTimer->setPosition(size.width/2,size.height/2);

	this->addChild(m_pCDTimer,CARD_CD_TIMER_TAG);
	//加载text
	auto text = StringUtils::toString(number);
	m_pNumberLabel = LabelAtlas::create(text,"card_images.png",16,16,'0');
	//设置位置
	auto labelSize = m_pNumberLabel->getContentSize();
	
	m_pNumberLabel->setPosition(size.width - labelSize.width/2,size.height - labelSize.height/2);

	this->addChild(m_pNumberLabel,CARD_NUMBER_LABEL_TAG);

	return true;
}

Sprite* Card::getDisableSprite()const
{
	return m_pDisableSprite;
}

void Card::setDarken()
{
	m_pNormalSprite->setVisible(false);
	m_pDisableSprite->setVisible(true);

	m_pCDTimer->setVisible(true);
	m_pCDTimer->setPercentage(100.f);
}

void Card::setNeedfulTerrains(const vector<TerrainType>&terrains)
{
	m_terrainTypes.clear();

	for (auto type:terrains)
	{
		m_terrainTypes.push_back(type);
	}
}

bool Card::isIncludeTerrain(TerrainType type)
{
	auto it = find(m_terrainTypes.begin(),m_terrainTypes.end(),type);

	return it != m_terrainTypes.end();
}

void Card::setEnabled(bool enabled)
{
	MenuItem::setEnabled(enabled);

	if (enabled)
	{
		m_pNormalSprite->setVisible(true);
	}
	else
	{
		m_pNormalSprite->setVisible(false);
		m_pDisableSprite->setVisible(true);
	}
}

void Card::update(float dt)
{
	m_fCurCD -= dt;
	//cd已经完成
	if (m_fCurCD <= 0.f)
	{
		m_fCurCD = 0.f;

		auto sunNum = DynamicData::getInstance()->getSunNumber();

		if (sunNum >= m_nWorth)
		{
			this->setEnabled(true);
		}
		else
		{
			this->setEnabled(false);
		}
	}
	else
	{
		this->setEnabled(false);
	}
	//设置percentage
	if (m_type == CardType::Common)
	{
		float percentage = m_fCurCD/m_fCD * 100.f;
		m_pCDTimer->setPercentage(percentage);
	}
}

void Card::setNormalSprite(const string&name)
{
	//获取对应格式
	auto format = STATIC_DATA_STRING("card_normal_sprite_fromat");
	auto spriteName = StringUtils::format(format.c_str(),name.c_str());
	//设置精灵
	m_pNormalSprite = Sprite::createWithSpriteFrameName(spriteName);

	auto size = m_pNormalSprite->getContentSize();

	m_pNormalSprite->setPosition(size.width/2,size.height/2);

	this->addChild(m_pNormalSprite,CARD_NORMAL_SPRITE_TAG);
	this->setContentSize(size);
}

void Card::setDisableSprite(const string&name)
{
	//获取对应格式
	auto format = STATIC_DATA_STRING("card_disable_sprite_format");
	auto spriteName = StringUtils::format(format.c_str(),name.c_str());
	//设置精灵
	m_pDisableSprite = Sprite::createWithSpriteFrameName(spriteName);

	auto size = this->getContentSize();

	m_pDisableSprite->setPosition(size.width/2,size.height/2);

	this->addChild(m_pDisableSprite,CARD_DISABLE_SPRITE_TAG);
}