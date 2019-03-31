#include "CannonsHero.h"
#include "CsvUtil.h"
CannonsHero::CannonsHero()
	:Hero(),m_pAttackAction(nullptr)
{
	FILE_PATH = "csv/cannonshero.csv";
}
CannonsHero::~CannonsHero()
{
}
CannonsHero*CannonsHero::createFromCsvFileByID(int nHeroID)
{
	auto hero = new CannonsHero();
	if(hero && hero->initWithCsvFileByID(nHeroID))
		hero->autorelease();
	else
		CC_SAFE_DELETE(hero);
	return hero;
}
bool CannonsHero::initWithCsvFileByID(int nHeroID)
{
	bool bRet = false;
	do{
		CsvUtil*csvUtil = CsvUtil::getInstance();
		//获取所在行数
		int nLine = csvUtil->findLineByValue(Value(nHeroID),enCannonsHeroPropConfType_ID,"csv/cannonshero.csv");
		CC_BREAK_IF(nLine < 0);
		//ID
		setModelID(csvUtil->getValue(nLine,enCannonsHeroPropConfType_ModelID,FILE_PATH.c_str()).asInt());
		setBaseAtk(csvUtil->getValue(nLine,enCannonsHeroPropConfType_BaseAtk,FILE_PATH.c_str()).asInt());
		setCurAtk(getBaseAtk());
		setAtkSpeed(csvUtil->getValue(nLine,enCannonsHeroPropConfType_AtkSpeed,FILE_PATH.c_str()).asFloat());
		setAtkRange(csvUtil->getValue(nLine,enCannonsHeroPropConfType_AtkRange,FILE_PATH.c_str()).asInt());
		setUpgradeCostBase(csvUtil->getValue(nLine,enCannonsHeroPropConfType_UpgradeCostBase,FILE_PATH.c_str()).asInt());
		//load the resources
		m_resource = csvUtil->getValue(nLine,enCannonsHeroPropConfType_Resources,FILE_PATH.c_str()).asString();
		//load the bullet
		int nBulletID = csvUtil->getValue(nLine,enCannonsHeroPropConfType_Bullet,FILE_PATH.c_str()).asInt();
		//Load 加载资源
		auto frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(m_resource + ".plist");
		//set the sprite
		int pos_tower = m_resource.find_last_of('/');
		std::string name_tower = m_resource.substr(pos_tower+1);
		//initlize the tower of sprite
		m_initSpriteName = StringUtils::format("%s-level%d-tower0.png",name_tower.c_str(),m_nCurLevel);
		bindSprite(Sprite::createWithSpriteFrameName(m_initSpriteName));
		//get the numbers fron csv file
		float allFrameNum = csvUtil->getValue(nLine,enCannonsHeroPropConfType_AllAttackNum,FILE_PATH.c_str()).asInt();
		int attackFrameNum = csvUtil->getValue(nLine,enCannonsHeroPropConfType_AttackNum,FILE_PATH.c_str()).asInt();
		int refillBulletNum = csvUtil->getValue(nLine,enCannonsHeroPropConfType_refillNum,FILE_PATH.c_str()).asInt();
		
		std::string fileName = std::string(name_tower+"-level"+Value(m_nCurLevel).asString()+"-tower%d.png");
		
		Animate*attackAction1 = Animate::create(Entity::createNormalAction(fileName.c_str(),0,attackFrameNum,allFrameNum));
		Animate*attackAction2 = Animate::create(Entity::createNormalAction(fileName.c_str(),attackFrameNum,refillBulletNum,allFrameNum));
		Animation*anim3 = Entity::createNormalAction(fileName.c_str(),refillBulletNum,allFrameNum,allFrameNum);
		anim3->setRestoreOriginalFrame(true);
		Animate*attackAction3 = Animate::create(anim3);
		
		CallFunc*launchBulletFunc =CallFunc::create([&](){attackCallBack();});
		Action*attackAction = Sequence::create(attackAction1,launchBulletFunc,attackAction2,attackAction3,nullptr);
		setAttackAction(attackAction);
		//加载子弹
		m_pBullet = Bullet::createFromCsvFileByID(nBulletID);
		this->addChild(m_pBullet);
		m_pBullet->setVisible(false);
		bRet = true;
	}while(0);
	return bRet;
}
void CannonsHero::onBindSprite()
{
}
void CannonsHero::attack()
{
	//这里必须先加上这个语句，因为先设置成不可攻击，然后判断就不会重复进入，不加会错误
	m_bIsCanAttack = false;
	Action*action = Sequence::create((Animate*)getAttackAction(),CallFunc::create([&]()
	{
		
		m_pSprite->setSpriteFrame(m_initSpriteName);
	}),nullptr);
	m_pSprite->runAction(getAttackAction());
}
void CannonsHero::onHurt(int nValue)
{
}
void CannonsHero::onDead()
{
}
void CannonsHero::attackCallBack()
{
	if(m_pAtkMonster == nullptr)
	{
		m_bIsCanAttack = true;
		return;
	}
	/*m_bIsCanAttack = false;
	Size size = getContentSize();
	m_pBullet->setPosition(Point(size.width/2,size.height));
	m_pBullet->setVisible(true);
	Vec2 relativePos = m_pAtkMonster->getPosition() - getPosition();
	MoveBy*moveBy = MoveBy::create(0.4f,relativePos);

	CallFunc*attackCallFunc = CallFunc::create([&,size]()
	{
		//if the monster has dead,break
		if(m_pAtkMonster != nullptr)
		{
			Point pos = m_pBullet->getPosition();
			Rect r1 = m_pBullet->getBoundingBox();
			Rect r2 = m_pAtkMonster->getBoundingBox();
			//log("%.2f,%.2f,%.2f,%.2f",r1.origin.x,r1.origin.y,r1.size.width,r1.size.height);
			//log("%.2f,%.2f,%.2f,%.2f",r2.origin.x,r2.origin.y,r2.size.width,r2.size.height);
			Rect r3=Rect(r1.origin.x+getPosition().x -size.width/2,r1.origin.y+getPosition().y-size.height/2,r1.size.width,r1.size.height);
			//log("%.2f,%.2f,%.2f,%.2f",r3.origin.x,r3.origin.y,r3.size.width,r3.size.height);
			if(r3.intersectsRect(m_pAtkMonster->getBoundingBox()))
			{
				m_pAtkMonster->hurtMe(getCurAtk());
			}
		}
		//m_bIsCanAttack = true;
		m_pBullet->setVisible(false);
	});
	m_pBullet->runAction(Sequence::create(moveBy,attackCallFunc,NULL));*/
	Point monsterPos = m_pAtkMonster->getPosition();
	//set the position of bullet
	Size size = getContentSize();
	m_pBullet->setPosition(Point(size.width/2,size.height));
	m_pBullet->setVisible(true);
	//set the end pos
	Point startPos = Point(getPosition().x,getPosition().y + size.height/2);
	m_pBullet->setRoute(getPosition(),monsterPos);
	m_pBullet->setAtkValue(5);
	m_pBullet->start();
	this->scheduleOnce([&](float)
	{
		m_bIsCanAttack = true;
	},getAtkSpeed(),"mm");
}