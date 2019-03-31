#include "Bullet.h"
#include "CsvUtil.h"
#include "Entity.h"
#include "MonsterManager.h"
#include "Monster.h"

#include "Global.h"
Bullet::Bullet():m_bIsUsed(false),m_bIsArrived(false)
	,m_pSprite(nullptr),m_nAtkValue(0),m_nMoveDuration(0.1)
	,m_pRunAction(nullptr),m_pAtkAnimation(nullptr)
{
}
Bullet::~Bullet()
{
}
Bullet* Bullet::createFromCsvFileByID(int nBulletID)
{
	auto bullet = new Bullet();
	if(bullet && bullet->initWithCsvFileByID(nBulletID))
		bullet->autorelease();
	else
		CC_SAFE_DELETE(bullet);
	return bullet;
}
bool Bullet::initWithCsvFileByID(int nBulletID)
{
	bool bRet = false;
	do
	{
		CsvUtil*csvUtil = CsvUtil::getInstance();
		int nLine = csvUtil->findLineByValue(Value(nBulletID),enBulletPropConfType_ID,"csv/bullet.csv");
		//assert(nLine>0,"find the line failed!");
		std::string name1 = csvUtil->getValue(nLine,enBulletPropConfType_Name,"csv/bullet.csv").asString();
		int type = csvUtil->getValue(nLine,enBulletPropConfType_Type,"csv/bullet.csv").asInt();
		m_nRunFrame = csvUtil->getValue(nLine,enBulletPropConfType_RunFrame,"csv/bullet.csv").asInt();
		m_nAtkFrame = csvUtil->getValue(nLine,enBulletPropConfType_AtkFrame,"csv/bullet.csv").asInt();
		resource_name = csvUtil->getValue(nLine,enBulletPropConfType_Resource,"csv/bullet.csv").asString();
		//add sprites to SpriteFrameCache
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(resource_name + ".plist");
		//set this anchor point
		//这个得要，不然发出的炮弹会偏移
		int pos = resource_name.find_last_of('/');
		std::string name = resource_name.substr(pos+1);
		bindSprite(Sprite::createWithSpriteFrameName(name+"-run0.png"));
		m_pSprite->setVisible(false);
		m_colliableSize = (Sprite::createWithSpriteFrameName(name+"-end0.png"))->getContentSize();
		
		bRet = true;
	}while(0);
	return bRet;
}
void Bullet::bindSprite(Sprite*sprite)
{
	if(m_pSprite != NULL)
		this->removeChild(m_pSprite);
	this->m_pSprite = sprite;
	this->addChild(m_pSprite);
	setAnchorPoint(Point(0.5,0.5));
	Size size = m_pSprite->getContentSize();
	this->setContentSize(size);
	m_pSprite->setPosition(Point(size.width*0.5f,size.height*0.5f));
}
void Bullet::setRoute(Point startPos,Point endPos)
{
	m_startPos = startPos;
	m_endPos = endPos;
}
void Bullet::start()
{
	int pos = resource_name.find_last_of('/');
	std::string name = resource_name.substr(pos+1);
	Sprite*sprite = Sprite::createWithSpriteFrameName(name+"-run0.png");
	//JumpBy
	float height = sqrt(pow(m_endPos.x - m_startPos.x,2)+pow(m_endPos.y - m_startPos.y,2))/3;
	JumpBy*jump = JumpBy::create(0.5f,m_endPos-m_startPos,height,1);
	MoveBy*run = MoveBy::create(0.4f,m_endPos - m_startPos);
	//attack
	int half = m_nAtkFrame/2;
	Animate*attack1 = Animate::create(Entity::createNormalAction(name+"-end%d.png",0,half,m_nAtkFrame*2));
	Animate*attack2 = Animate::create(Entity::createNormalAction(name+"-end%d.png",half,m_nAtkFrame,m_nAtkFrame*2));
	Action*attack = Sequence::create(attack1,CallFunc::create([&](){this->attack();}),attack2,nullptr);
	this->addChild(sprite);
	sprite->runAction(Sequence::create(jump,attack,CallFunc::create([sprite]()
	{sprite->removeFromParent();}),nullptr));
}
void Bullet::attack()
{
	Point original = Point(m_endPos.x-m_colliableSize.width/2,m_endPos.y - m_colliableSize.height/2);
	Rect atkRect(original.x ,original.y,m_colliableSize.width,m_colliableSize.height);
	auto monsters = Global::getInstance()->_monsterManager->getMonsterList();
	for(auto monster : monsters)
	{
		if(!monster->isVisible())
			return;
		Rect monsterRect = monster->getBoundingBox();
		if(atkRect.intersectsRect(monsterRect))
			monster->hurtMe(getAtkValue());
	}
}