#include "RewardLayer.h"
#include "MenuItemReward.h"
#include "ScoreSprite.h"
#include "FishingJoyData.h"

RewardLayer::RewardLayer()
	:m_pChestMenu(nullptr),m_nChestChgNum(0)
	,m_pDelegate(nullptr),m_bOpenedChest(true)
{
}

RewardLayer::~RewardLayer()
{
}

bool RewardLayer::init()
{
	return true;
}

void RewardLayer::showChest()
{
	vector<MenuItem*> btns;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	for(int i = 0;i < 5;i++)
	{
		//�����ȡһ�����������ɶ�Ӧ�ľ���
		ChestReward& reward = this->getRandomChestReward();
		Node*node = this->getNodeByChestReward(reward);

		MenuItemReward*btn = MenuItemReward::create(node,reward);
		Size size = btn->getContentSize();
		//����λ��
		Point pos = Point(visibleSize.width/5*(i + 0.5f),visibleSize.height/2);
		btn->setPosition(pos);
		btn->setCallback(SDL_CALLBACK_1(RewardLayer::chestRewardBtnCallback,this));

		btns.push_back(btn);
	}
	m_pChestMenu = Menu::createWithArray(btns);
	//���ò��ɵ��
	m_pChestMenu->setEnable(false);

	this->addChild(m_pChestMenu);
	//���go ��ť
	ui::Button*goBtn = ui::Button::create("ui_box_go.png","ui_box_go_selected.png");
	Size goBtnSize = goBtn->getContentSize();

	goBtn->addClickEventListener(SDL_CALLBACK_1(RewardLayer::goBtnCallback,this));
	goBtn->setSwallowTouches(true);
	goBtn->setPosition(visibleSize.width/2,visibleSize.height/2 + goBtnSize.height/2);
	
	this->addChild(goBtn);
}

bool RewardLayer::isClickChest()
{
	if(m_pChestMenu)
		return false;

	return true;
}

void RewardLayer::setDelegate(RewardLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void RewardLayer::chestRewardBtnCallback(Object*sender)
{
	//�Ѿ����˱��䣬�����ٴ���������
	if (m_bOpenedChest)
	{
		return;
	}
	else
	{
		m_bOpenedChest = true;
	}

	float duration = 1.f;
	//ȷ������İ�ť
	MenuItemReward*btn = static_cast<MenuItemReward*>(sender);

	auto size = btn->getContentSize();
	auto pos = btn->getPosition();
	//������Ч
	btn->showUpperSprite(duration);
	btn->toggleSprite();

	m_pDelegate->addChestLightAnim("chest light",pos + Point(0,size.height/2));
	//�ָ���Ϸ
	m_pDelegate->gameResume();

	//�� duration���Ƴ�menu
	auto remove = [this,btn](float)
	{
		//������Ʒ
		ChestReward&reward = btn->getChestReward();
		auto itemName = reward.type;
		auto number = reward.number;
		auto size = btn->getContentSize();
		auto bornPos = btn->getPosition() - Point(0,size.height/2);

		m_pDelegate->addItem(itemName,bornPos,number);
		//�Ƴ���ť����
		m_pChestMenu->removeFromParent();
		m_pChestMenu = nullptr;

		m_pDelegate->removeChestLightAnim("chest light");
	};
	//�ڱ����Ƴ����������Ʒ
	this->scheduleOnce(remove,"remove",duration);
}

void RewardLayer::goBtnCallback(Object*sender)
{
	//�Ƴ� go ��ť
	auto btn = static_cast<ui::Button*>(sender);
	btn->removeFromParent();
	//���û�û�������
	m_bOpenedChest = false;
	//������Ч
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();
	if (bPlayingChunk)
	{
		auto sBtnGo = STATIC_DATA_STRING("btn_go_chunk");
		SoundManager::getInstance()->playEffect(sBtnGo,0);
	}

	auto children = m_pChestMenu->getChildren();
	float duration = 1.f;
	//��Ʒ���뱦�䶯��
	for(auto iter = children.begin();iter != children.end();iter++)
	{
		MenuItemReward*reward = static_cast<MenuItemReward*>(*iter);
		reward->hideUpperSprite(duration);
	}
	//��֮��ص������ƶ�����
	this->scheduleOnce(SDL_CALLBACK_1(RewardLayer::moveChestSchedule,this),"move chest",duration);
}

void RewardLayer::moveChestSchedule(float)
{
	//�Ƿ���������δ����������
	if (m_nChestChgNum++ <= 6)
	{
		//���ѡ��������ͬ������
		int index1 = rand()%5;
		int index2 = 0;

		do
		{
			index2 = rand()%5;

		}while(index1 == index2);
		//��ȡ������λ��
		auto &children = m_pChestMenu->getChildren();
		auto child1 = children.at(index1);
		auto child2 = children.at(index2);

		auto relativeX = child2->getPositionX() - child1->getPositionX();

		auto duration = SDL_fabs(relativeX)/800.f;

		MoveBy*move1 = MoveBy::create(duration,relativeX);
		MoveBy*move2 = MoveBy::create(duration,-relativeX);

		//���ж���
		child1->runAction(move1);
		//�ڶ�����ɺ����»ص�
		CallFunc*end = CallFunc::create(SDL_CALLBACK_0(RewardLayer::moveChestSchedule,this,duration));
		auto seq = Sequence::create(move2,end,nullptr);
		
		child2->runAction(seq);
	}
	//���ӿɵ��
	else
	{
		m_nChestChgNum = 0;
		m_pChestMenu->setEnable(true);
	}
}

ChestReward&RewardLayer::getRandomChestReward()
{
	auto &rewards = StaticData::getInstance()->getChestRewards();
	int size = rewards.size();
	int index = rand()%size;

	return rewards.at(index);
}

Node*RewardLayer::getNodeByChestReward(const ChestReward&reward)
{
	Node*node = nullptr;

	if(reward.type == "gold")
	{
		int score = reward.number;
		node = ScoreSprite::create(score);
	}
	else if(reward.type == "exp")
	{
		node = Sprite::createWithSpriteFrameName("exp.png");
	}
	else if(reward.type == "battery")
	{
		node = Sprite::createWithSpriteFrameName("battery.png");
	}
	else if(reward.type == "FogBullet")
	{
		node = Sprite::createWithSpriteFrameName("bullet_fog.png");
	}
	else if(reward.type == "PearlBullet")
	{
		node = Sprite::createWithSpriteFrameName("bullet_pearl.png");
	}
	else if(reward.type == "SterengthenBullet")
	{
		node = Sprite::createWithSpriteFrameName("bullet_strengthen.png");
	}
	
	return node;
}