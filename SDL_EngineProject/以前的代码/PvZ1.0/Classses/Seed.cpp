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
	//ע���۲���
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
	//�����Ժ���չ
	m_pNormalSprite = Sprite::create(image,Rect(0,0,100,60));
	m_pDisabledSprite = Sprite::create(image,Rect(0,60,100,60));
	m_pLoadingBar = LoadingBar::create("Resources/Card/grey.png",1,Direction::UP);
	//��ȡ��С
	setContentSize(m_pNormalSprite->getContentSize());

	m_pNormalSprite->setVisible(false);
	m_pDisabledSprite->setVisible(true);
	m_pLoadingBar->setVisible(true);
	m_pLoadingBar->setPercent(0.f);
	//���
	this->addChild(m_pNormalSprite,1);
	this->addChild(m_pDisabledSprite,2);
	this->addChild(m_pLoadingBar,3);
	//���label��Ǯ
	LabelTTF*labelWorth = LabelTTF::createWithTTF(StringUtils::toString(m_nWorth).c_str(),
		"Resources/Marker Felt.ttf",20);
	//���õ�����λ��
	Size size = getContentSize();
	Size fontSize = labelWorth->getContentSize();
	labelWorth->setPosition(size.width-fontSize.width,size.height-fontSize.height);
	this->addChild(labelWorth,2);
	//���̫����۲���
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(Seed::updateSelf),"sunshine");
	return true;
}
Plant*Seed::createPlant()
{
	//���ɵ��
	m_pNormalSprite->setVisible(false);
	m_pDisabledSprite->setVisible(true);
	m_pLoadingBar->setVisible(true);
	//����Cd
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
			updateSelf(this);//����״̬ ���ݵ�ֵ����ν
		}
		m_pLoadingBar->setPercent(m_fCurCD/m_fSeedCD);
	}
}
void Seed::updateSelf(Object*obj)
{
	//��ȡ��ǰ̫������
	auto sunNum = DynamicData::getInstance()->getSunNumber();
	//���cdδ��ɣ��򲻸���״̬
	if(m_bFinished == false)
		return;
	//cd������ɣ�����Ƿ���� 
	if(m_bFinished)
	{
		//���ÿɵ��
		if(sunNum >= m_nWorth)
		{
			m_pNormalSprite->setVisible(true);
			m_pDisabledSprite->setVisible(false);
			m_pLoadingBar->setVisible(false);
		}
		else//���ɵ��
		{
			m_pNormalSprite->setVisible(false);
			m_pDisabledSprite->setVisible(true);
		}
	}
}