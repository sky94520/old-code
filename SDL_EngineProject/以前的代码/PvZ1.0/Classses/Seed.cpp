#include "Seed.h"
#include "SunFlower.h"
#include "PlantFactory.h"
#include "MainLua.h"
#include "DynamicData.h"
Seed::Seed():m_pNormalSprite(nullptr),m_pDisabledSprite(nullptr)
	,m_fCurCD(0.f),m_fSeedCD(0.f),m_nWorth(0),
	m_name(""),m_description(""),m_pLoadingBar(nullptr)
	,m_bFinished(false)
{
}
Seed::~Seed()
{
	//注销观察者
	NotificationCenter::getInstance()->removeObserver(this,"sunshine");
}
Seed*Seed::create(const std::string& name)
{
	auto seed = new Seed();
	if(seed && seed->init(name))
		seed->autoRelease();
	else
		SDL_SAFE_DELETE(seed);
	return seed;
}
bool Seed::init(const std::string& name)
{
	m_name = name;
	auto pL = MainLua::getInstance();

	std::string image = pL->getStringFromTable(name,"seedImage");
	m_fSeedCD = m_fCurCD = pL->getDoubleFromTable(name,"seedCD");
	m_nWorth = pL->getIntegerFromTable(name,"worth");
	m_description = pL->getStringFromTable(name,"description");
	//留待以后扩展
	m_pNormalSprite = Sprite::create(image,Rect(0,0,100,60));
	m_pDisabledSprite = Sprite::create(image,Rect(0,60,100,60));
	m_pLoadingBar = LoadingBar::create("Resources/Card/grey.png",1,Direction::UP);
	//获取大小
	setContentSize(m_pNormalSprite->getContentSize());

	m_pNormalSprite->setVisible(false);
	m_pDisabledSprite->setVisible(true);
	m_pLoadingBar->setVisible(true);
	m_pLoadingBar->setPercent(0.f);
	//添加
	this->addChild(m_pNormalSprite,1);
	this->addChild(m_pDisabledSprite,2);
	this->addChild(m_pLoadingBar,3);
	//添加label金钱
	LabelTTF*labelWorth = LabelTTF::createWithTTF(StringUtils::toString(m_nWorth).c_str(),
		"Resources/Marker Felt.ttf",20);
	//放置到合适位置
	Size size = getContentSize();
	Size fontSize = labelWorth->getContentSize();
	labelWorth->setPosition(size.width-fontSize.width,size.height-fontSize.height);
	this->addChild(labelWorth,2);
	//添加太阳光观察者
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(Seed::updateSelf),"sunshine");
	return true;
}
Plant*Seed::createPlant()
{
	//不可点击
	m_pNormalSprite->setVisible(false);
	m_pDisabledSprite->setVisible(true);
	m_pLoadingBar->setVisible(true);
	//重置Cd
	m_fCurCD = m_fSeedCD;
	m_bFinished = false;

	return PlantFactory::getInstance()->create(m_name);
}
bool Seed::canClicked()const
{
	return m_fCurCD == 0.f && m_pNormalSprite->isVisible();
}
void Seed::update(float dt)
{
	if(m_bFinished == false)
	{
		m_fCurCD -= dt;
		if(m_fCurCD <= 0.f)
		{
			m_fCurCD = 0.f;
			m_bFinished = true;
			updateSelf(this);//更新状态 传递的值无所谓
		}
		m_pLoadingBar->setPercent(m_fCurCD/m_fSeedCD);
	}
}
void Seed::updateSelf(Object*obj)
{
	//获取当前太阳数量
	auto sunNum = DynamicData::getInstance()->getSunNumber();
	//如果cd未完成，则不更新状态
	if(m_bFinished == false)
		return;
	//cd更新完成，检查是否更新 
	if(m_bFinished)
	{
		//设置可点击
		if(sunNum >= m_nWorth)
		{
			m_pNormalSprite->setVisible(true);
			m_pDisabledSprite->setVisible(false);
			m_pLoadingBar->setVisible(false);
		}
		else//不可点击
		{
			m_pNormalSprite->setVisible(false);
			m_pDisabledSprite->setVisible(true);
		}
	}
}