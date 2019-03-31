#include "PanelLayer.h"
#include "Entity.h"
#include "StaticData.h"
#include "FishingJoyData.h"
#include "ItemButton.h"
#include "GoldCounter.h"

PanelLayer::PanelLayer()
	:m_pDownUI(nullptr),m_pEnergyUI(nullptr)
	,m_pSubLevelBtn(nullptr),m_pEnergyProgress(nullptr)
	,m_pAddLevelBtn(nullptr),m_pDelegate(nullptr)
	,m_pGoldCounter(nullptr),m_pLvUI(nullptr)
	,m_pExpProgress(nullptr),m_bBulletsVisible(false)
	,m_pSelectedBullet(nullptr),m_pBulletMenu(nullptr)
	,m_pHalfEnergyBtn(nullptr),m_pBtnMenu(nullptr)
	,m_pPauseBtn(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	//����ⲿ����
	auto xml = STATIC_DATA_STRING("PanelLayer");
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml(xml);
	this->addChild(node);
	//��ȡ���ֿ��ÿؼ�
	m_pDownUI = node->getChildByName<Sprite*>(STATIC_DATA_STRING("ui_down_name"));

	m_pLvUI = node->getChildByName<LabelAtlas*>(STATIC_DATA_STRING("ui_lv_name"));
	//������ Ĭ����ת90�ȣ�����ֻ�����������˺�Ż���ֲ����ж���
	m_pEnergyUI = node->getChildByName<Sprite*>(STATIC_DATA_STRING("ui_energy_name"));
	m_pEnergyUI->setVisible(false);

	m_pSubLevelBtn = node->getChildByName<ui::Button*>(STATIC_DATA_STRING("sub_btn_name"));
	m_pAddLevelBtn = node->getChildByName<ui::Button*>(STATIC_DATA_STRING("add_btn_name"));
	//���ûص�����
	m_pSubLevelBtn->addClickEventListener(SDL_CALLBACK_1(PanelLayer::subBtnCallback,this));
	m_pAddLevelBtn->addClickEventListener(SDL_CALLBACK_1(PanelLayer::addBtnCallback,this));
	//��ȡ��ͣ��ť�ؼ�
	m_pPauseBtn = node->getChildByName<ui::Button*>(STATIC_DATA_STRING("pause_btn_name"));
	m_pPauseBtn->addClickEventListener(SDL_CALLBACK_1(PanelLayer::pauseBtnCallback,this));
	//��ӿؼ�
	auto energyProgressSpriteName = STATIC_DATA_STRING("energy_progress_sprite_name");
	m_pEnergyProgress = ProgressTimer::create(Sprite::create(energyProgressSpriteName));
	//[50,100]
	m_pEnergyProgress->setPercentage(50);

	m_pEnergyProgress->setRotation(90);
	//����λ��
	auto energyPos = STATIC_DATA_POINT("energy_progress_pos");
	m_pEnergyProgress->setPosition(energyPos);

	this->addChild(m_pEnergyProgress,-1);
	//��Ӿ���ؼ�
	auto expSpriteName = STATIC_DATA_STRING("exp_sprite_name");
	Point expProgressPos = STATIC_DATA_POINT("exp_progress_pos");

	m_pExpProgress = ProgressTimer::create(Sprite::create(expSpriteName));

	m_pExpProgress->setType(ProgressTimer::Type::BAR);
	m_pExpProgress->setMidpoint(Point::ZERO);
	m_pExpProgress->setBarChangeRate(Point(1.f,0));
	m_pExpProgress->setPosition(expProgressPos);

	this->addChild(m_pExpProgress);
	//���չʾ�� todo
	m_pGoldCounter = GoldCounter::create(200);
	m_pGoldCounter->setPosition(140,594);
	m_pGoldCounter->scheduleUpdate();
	this->addChild(m_pGoldCounter);
	//����ӵ���ť
	m_pSelectedBullet = ItemButton::create();
	//����λ��,λ�ò��䣬����Ǿ��������
	auto bulletPos = STATIC_DATA_POINT("bullet_button_pos");

	m_pSelectedBullet->setPosition(bulletPos);
	m_pSelectedBullet->setButtonType(ButtonType::Bullet);
	//�������ֵ��ť
	auto halfEnergyPos = PointFromString(STATIC_DATA_STRING("energy_button_pos"));
	auto halfEnergySpriteName = STATIC_DATA_STRING("energy_sprite_name");
	Sprite*halfEnergySprite = Sprite::createWithSpriteFrameName(halfEnergySpriteName);
	int halfEnergyNum = FishingJoyData::getInstance()->getHalfEnergyNum();

	m_pHalfEnergyBtn = ItemButton::create(halfEnergySprite,halfEnergyNum,ButtonType::HalfEnergy);
	m_pHalfEnergyBtn->setPosition(halfEnergyPos);
	m_pHalfEnergyBtn->setCallback(SDL_CALLBACK_1(PanelLayer::handleHalfEnergy,this));
	m_pHalfEnergyBtn->setSwallowed(true);

	m_pBtnMenu = Menu::create(m_pSelectedBullet,m_pHalfEnergyBtn,nullptr);
	this->addChild(m_pBtnMenu);

	this->initBullets();
	
	this->updateBulletBtns();

	return true;
}
Point PanelLayer::getConnonBornPos()const
{
	return m_pDownUI->getPosition();
}

void PanelLayer::setDelegate(PanelLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void PanelLayer::runEnergyAnimation()
{
	m_pEnergyUI->setVisible(true);
	auto animationName = STATIC_DATA_STRING("energy_full_anim");

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	m_pEnergyUI->runAction(animate);
	//����Բ�ν�����
	m_pEnergyProgress->setVisible(false);
}

void PanelLayer::stopEnergyAnimation()
{
	m_pEnergyUI->stopAllActions();
	m_pEnergyUI->setVisible(false);

	m_pEnergyProgress->setVisible(true);
}

void PanelLayer::showAddAndSubBtn()
{
	m_pAddLevelBtn->setVisible(true);
	m_pSubLevelBtn->setVisible(true);
}

void PanelLayer::hideAddAndSubBtn()
{
	m_pAddLevelBtn->setVisible(false);
	m_pSubLevelBtn->setVisible(false);
}

void PanelLayer::updateEnergy()
{
	auto energy = FishingJoyData::getInstance()->getEnergy();

	//ת��Ϊ
	auto delta = energy / 2.f;
	auto percentage = 50 + delta;

	m_pEnergyProgress->setPercentage(percentage);
}

void PanelLayer::updateGold()
{
	auto gold = FishingJoyData::getInstance()->getGold();

	m_pGoldCounter->setGoldNumber(gold);
}

void PanelLayer::updateLevel()
{
	auto level = FishingJoyData::getInstance()->getLevel();

	auto text = StringUtils::format("%02d",level);

	m_pLvUI->setString(text);
}

void PanelLayer::updateExp()
{
	auto exp = FishingJoyData::getInstance()->getExp();
	//���ݵ�ǰ�ȼ�����ת��
	auto exps = FishingJoyData::getInstance()->getExpOfCurLevel();

	auto percentage = 100.f * exp / exps;

	m_pExpProgress->setPercentage(percentage);
}

void PanelLayer::updateSelf()
{
	this->updateEnergy();
	this->updateExp();
	this->updateGold();
	this->updateLevel();

	this->updateBulletBtns();
	this->updateHalfEnergyBtn();
}

void PanelLayer::updateBulletBtns()
{
	auto children = m_pBulletMenu->getChildren();

	for(auto child:children)
	{
		auto btn = static_cast<ItemButton*>(child);

		auto bulletName = btn->getName();
		auto number = FishingJoyData::getInstance()->getBulletNumByName(bulletName);
		bool enable = number > 0?true:false;

		btn->setNumber(number);
		btn->setEnabled(enable);

		if(bulletName == m_pSelectedBullet->getName())
		{
			m_pSelectedBullet->setNumber(number);
		}
	}
	//�����ǰѡ�������ʾ������Ϊ����
	if(m_bBulletsVisible)
	{
		this->handleBullet(m_pSelectedBullet);
	}
}

void PanelLayer::updateHalfEnergyBtn()
{
	//����half energy
	auto halfEnergyNum = FishingJoyData::getInstance()->getHalfEnergyNum();
	
	if(halfEnergyNum <= 0)
		m_pHalfEnergyBtn->setEnabled(false);
	else
		m_pHalfEnergyBtn->setEnabled(true);

	m_pHalfEnergyBtn->setNumber(halfEnergyNum);
}

void PanelLayer::setSelectedBulletBtn(const string&name)
{
	if(m_pSelectedBullet->getName() == name)
		return;
	ItemButton*selectedButton = nullptr;
	//�ҳ���Ӧ�İ�ť
	auto children = m_pBulletMenu->getChildren();

	for(auto btn:children)
	{
		if(btn->getName() == name)
		{
			selectedButton = static_cast<ItemButton*>(btn);
		}
	}

	this->setSelectedBulletBtn(selectedButton);
}

void PanelLayer::setSelectedBulletBtn(ItemButton*button)
{
	Sprite*sprite = button->getNormalSprite()->clone();
	int number = button->getNumber();
	string selectedBulletName = button->getName();
	//�ı�ѡ�еİ�ť�� ���� ��Ŀ ������
	m_pSelectedBullet->setNormalSprite(sprite);
	m_pSelectedBullet->setNumber(number);
	m_pSelectedBullet->setName(selectedBulletName);
}

void PanelLayer::setBtnEnable(bool enable)
{
	m_pBulletMenu->setEnable(enable);
	m_pBtnMenu->setEnable(enable);
	m_pPauseBtn->setTouchEnabled(enable);

	this->updateBulletBtns();
	this->updateHalfEnergyBtn();
}

void PanelLayer::initBullets()
{
	//��ȡ��ť�Ű�
	auto valueVector = StaticData::getInstance()->getValueForKey("bullets").asValueVector();
	//��ȡ��ǰѡ�е��ӵ�����
	
	auto selectedBulletName = FishingJoyData::getInstance()->getSelectedBullet();

	vector<MenuItem*> buttons;

	for(auto value:valueVector)
	{
		auto config = value.asValueMap();

		auto bulletName = config.at("name").asString();
		auto position = PointFromString(config.at("position").asString());
		auto normalSpriteFrameName = config.at("normalSpriteFrameName").asString();

		Sprite*normalSprite = Sprite::createWithSpriteFrameName(normalSpriteFrameName);
		unsigned int number = FishingJoyData::getInstance()->getBulletNumByName(bulletName);
		
		ItemButton*btn = ItemButton::create(normalSprite,number,ButtonType::Bullet);
		
		btn->setName(bulletName);
		btn->setPosition(position);
		btn->setCallback(SDL_CALLBACK_1(PanelLayer::handleBullet,this));
		btn->setSwallowed(true);
		
		buttons.push_back(btn);

		if(selectedBulletName == bulletName)
		{
			this->setSelectedBulletBtn(btn);

			m_pSelectedBullet->setSwallowed(true);
			m_pSelectedBullet->setCallback(SDL_CALLBACK_1(PanelLayer::handleBullet,this));
		}
	}

	m_pBulletMenu = Menu::createWithArray(buttons);
	m_pBulletMenu->setVisible(false);
	this->addChild(m_pBulletMenu);
}

void PanelLayer::addBtnCallback(Object*sender)
{
	m_pDelegate->addCannonLevel();
}

void PanelLayer::subBtnCallback(Object*sender)
{
	m_pDelegate->subCannonLevel();
}

void PanelLayer::pauseBtnCallback(Object*sender)
{
	m_pDelegate->pauseBtnCallback();
}

void PanelLayer::handleSuperWeapon(ItemButton*button)
{
}

void PanelLayer::handleHalfEnergy(Object*sender)
{
	auto fishingJoyData = FishingJoyData::getInstance();
	//��ȡ��ǰ����ֵ
	auto energy = fishingJoyData->getEnergy();
	//���ӵ���ֵ
	m_pDelegate->addEnergy(100.f - energy);
	//����ֵ
	auto halfEnergyNum = FishingJoyData::getInstance()->getHalfEnergyNum();
	FishingJoyData::getInstance()->setHalfEnergyNum(halfEnergyNum - 1);
	
	//���и���
	this->updateHalfEnergyBtn();
}

void PanelLayer::handleBullet(Object*sender)
{
	ItemButton*button = static_cast<ItemButton*>(sender);
	bool oldVisible = m_bBulletsVisible;
	//��ȡҪ�����Ķ���
	ItemButton*selectedButton = nullptr;
	//���ӽ���Ĳ���
	if(button == m_pSelectedBullet)
	{
		//todo ��ʾ��Ч����ʾѡ��ĳ��ѡ��
		m_bBulletsVisible = !m_bBulletsVisible;

		m_pBulletMenu->setVisible(m_bBulletsVisible);
		auto children = m_pBulletMenu->getChildren();

		for(auto btn:children)
		{
			//btn->setVisible(m_bBulletsVisible);
			//���õ�ǰѡ��
			if(btn->getName() == m_pSelectedBullet->getName())
			{
				selectedButton = static_cast<ItemButton*>(btn);
			}
		}
	}
	//�������ͬ�İ�ť��������
	else if(button->getName() == m_pSelectedBullet->getName())
	{
		;
	}
	else//�ı�ѡ��
	{
		this->setSelectedBulletBtn(button);
		//���õ�ǰѡ��
		selectedButton = button;
	}

	if(selectedButton)
		m_pDelegate->changeBullet(selectedButton,oldVisible,m_bBulletsVisible);

}
