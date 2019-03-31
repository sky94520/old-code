#include "SingleSpriteHero.h"
#include "CsvUtil.h"
SingleSpriteHero::SingleSpriteHero()
	:Hero(),m_pAttackAction(nullptr)
{
}
SingleSpriteHero::~SingleSpriteHero()
{
}
SingleSpriteHero*SingleSpriteHero::createFromCsvFileByID(int nHeroID)
{
	auto hero = new SingleSpriteHero();
	if(hero && hero->initWithCsvFileByID(nHeroID))
		hero->autorelease();
	else
		CC_SAFE_DELETE(hero);
	return hero;
}
bool SingleSpriteHero::initWithCsvFileByID(int nHeroID)
{
	bool bRet = false;
	do{
		CsvUtil*csvUtil = CsvUtil::getInstance();
		//获取所在行数
		int nLine = csvUtil->findLineByValue(Value(nHeroID),enHeroPropConfType_ID,"csv/hero.csv");
		CC_BREAK_IF(nLine < 0);
		//ID
		setModelID(csvUtil->getValue(nLine,enHeroPropConfType_ModelID,"csv/hero.csv").asInt());
		setBaseAtk(csvUtil->getValue(nLine,enHeroPropConfType_BaseAtk,"csv/hero.csv").asInt());
		setCurAtk(getBaseAtk());
		setAtkSpeed(csvUtil->getValue(nLine,enHeroPropConfType_AtkSpeed,"csv/hero.csv").asInt());
		setAtkRange(csvUtil->getValue(nLine,enHeroPropConfType_AtkRange,"csv/hero.csv").asInt());
		setUpgradeAtkBase(csvUtil->getValue(nLine,enHeroPropConfType_UpgradeAtkBase,"csv/hero.csv").asInt());
		setUpgradeCostBase(csvUtil->getValue(nLine,enHeroPropConfType_UpgradeCostBase,"csv/hero.csv").asInt());
		//load the resources
		m_resource = csvUtil->getValue(nLine,enHeroPropConfType_Resources,"csv/hero.csv").asString();
		auto frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(m_resource + ".plist");
		//set the sprite
		int pos_tower = m_resource.find_last_of('/');
		std::string name_tower = m_resource.substr(pos_tower+1);
		//Animation*attackAction1 = Entity::createNormalAction(name_tower+"",0,);
		//initlize the tower of sprite
		bindSprite(Sprite::createWithSpriteFrameName(StringUtils::format("%s-level%d-tower0.png",name_tower.c_str(),m_nCurLevel)));
		//load the bullet
		m_bulletResource = csvUtil->getValue(nLine,enHeroPropConfType_Bullet,"csv/hero.csv").asString();
		frameCache->addSpriteFramesWithFile(m_bulletResource+".plist");
		bRet = true;
	}while(0);
	return bRet;
}
void SingleSpriteHero::onBindSprite()
{
	int pos_bullet = m_bulletResource.find_last_of('/');
	std::string name_bullet = m_bulletResource.substr(pos_bullet + 1);
	m_pBullet = Sprite::createWithSpriteFrameName(StringUtils::format("%s-run0.png",name_bullet.c_str()));
	this->addChild(m_pBullet);
	m_pBullet->setVisible(false);
}
void SingleSpriteHero::onHurt(int nValue)
{
}
void SingleSpriteHero::onDead()
{
}