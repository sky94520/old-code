#include "Monster.h"
#include "CsvUtil.h"
#include "PosBase.h"
Monster::Monster():m_nLevel(0),m_nMoveTimeCount(0),
	m_fShowTime(0),m_nRandonOffsetX(0),m_nLocation(1)
	,m_pHpBar(nullptr),m_type(enActionType_up)
	,m_pHorizontalWalkAction(nullptr),m_pUpWalkAction(nullptr)
	,m_pDownWalkAction(nullptr),m_pDeadAction(nullptr)
{
	time(0);
	m_nRandonOffsetX = rand()%RODE_WEIGHT - RODE_WEIGHT/2;
}
Monster::~Monster()
{
}
Monster*Monster::createFromCsvFileByID(int nMonsterID)
{
	Monster*monster = new Monster();
	if(monster && monster->initFromCsvFileByID(nMonsterID))
		monster->autorelease();
	else
		CC_SAFE_DELETE(monster);
	return monster;
}
bool Monster::initFromCsvFileByID(int nMonsterID)
{
	bool bRet = false;
	do{
		CsvUtil*csvUtil = CsvUtil::getInstance();
		//获取所在行数
		int nLine = csvUtil->findLineByValue(Value(nMonsterID),enMonsterPropConfType_ID,"csv/monster.csv");
		CC_BREAK_IF(nLine < 0);
		setID(nMonsterID);
		setName(csvUtil->getValue(nLine,enMonsterPropConfType_Name,"csv/monster.csv").asString());			
		setLevel(csvUtil->getValue(nLine,enMonsterPropConfType_Level,"csv/monster.csv").asInt());
		setType(csvUtil->getValue(nLine,enMonsterPropConfType_Type,"csv/monster.csv").asString());
		setModelID(csvUtil->getValue(nLine,enMonsterPropConfType_ModelID,"csv/monster.csv").asInt());
		setDefense(csvUtil->getValue(nLine,enMonsterPropConfType_Defense,"csv/monster.csv").asInt());
		setHP(csvUtil->getValue(nLine,enMonsterPropConfType_Hp,"csv/monster.csv").asInt());
		setSpeed(csvUtil->getValue(nLine,enMonsterPropConfType_Speed,"csv/monster.csv").asInt());
		//set the monster speed
		m_nMoveTimeCount = getSpeed();
		//resources
		m_resource = csvUtil->getValue(nLine,enMonsterPropConfType_Resources,"csv/monster.csv").asString();
		//frames
		m_monsterFrame.up = csvUtil->getValue(nLine,enMonsterPropConfType_Up,"csv/monster.csv").asInt();
		m_monsterFrame.down = csvUtil->getValue(nLine,enMonsterPropConfType_Down,"csv/monster.csv").asInt();
		m_monsterFrame.horizontal = csvUtil->getValue(nLine,enMonsterPropConfType_Horizontal,"csv/monster.csv").asInt();
		m_monsterFrame.attack = csvUtil->getValue(nLine,enMonsterPropConfType_Attack,"csv/monster.csv").asInt();
		m_monsterFrame.dead = csvUtil->getValue(nLine,enMonsterPropConfType_Dead,"csv/monster.csv").asInt();
		//load pictures
		std::string plist = m_resource + ".plist";
		SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(plist);
		//set the initlize sprite
		int pos = m_resource.find_last_of('/');
		std::string name = m_resource.substr(pos+1);
		bindSprite(Sprite::createWithSpriteFrameName(StringUtils::format("%s-horizontal0.png",name.c_str())));
		bRet = true;
	}while(0);
	return bRet;
}
void Monster::moveByPosList(Vector<PosBase*>& posList)
{
	m_monsterPosList = posList;
	Point pos = posList.at(0)->getPos();
	setPosition(Point(pos.x + m_nRandonOffsetX,pos.y));
	this->schedule(schedule_selector(Monster::updateSelf));
	
}
void Monster::updateSelf(float dt)
{
	//if the monster arrive the end
	if(m_nLocation >= m_monsterPosList.size())
	{
		this->unschedule(schedule_selector(Monster::updateSelf));
		return;
	}
	if(m_nMoveTimeCount < 10)
	{
		m_nMoveTimeCount +=1;
		return; 
	}
	m_nMoveTimeCount = getSpeed();
	//update the position
	Point nextLocation = m_monsterPosList.at(m_nLocation)->getPos();
	Point curPos = this->getPosition() - Point(m_nRandonOffsetX,0);
	Point nextPos = curPos;
	
	//move to the end
	if(curPos == nextLocation)
		++m_nLocation;
	else
	{
		//handle x pos
		if(curPos.x > nextLocation.x)
			nextPos.x -= 1;
		else if(curPos.x < nextLocation.x)
			nextPos.x += 1;
		// y pos
		if(curPos.y > nextLocation.y)
			nextPos.y -= 1;
		else if(curPos.y < nextLocation.y)
			nextPos.y += 1;
		this->setPosition(nextPos + Point(m_nRandonOffsetX,0));
	}
	//update the animation
	Point velocity = nextPos - curPos;
	if(velocity.x < 0)
	{
		runHorizontalWalkAction();
		m_pSprite->setFlippedX(true);
	}
	else if(velocity.x > 0)
	{
		runHorizontalWalkAction();
		m_pSprite->setFlippedX(false);
	}
	else if(velocity.y < 0)
	{
		runDownWalkAction();
	}
	else if(velocity.y > 0)
		runUpWalkAction();
}
void Monster::hurtMe(int nHurtValue)
{
	m_pHpBar->setValue(m_nHP - nHurtValue);
	Entity::hurtMe(nHurtValue);
}
void Monster::onDead()
{
	//delete from parent
	runDeadAction();
}
void Monster::onHurt(int nHurtValue)
{
}
void Monster::onBindSprite()
{
	//create hp bar
	m_pHpBar = HpBar::create("sprite/hpBar.png","sprite/hpBarBG.png",m_nHP);
	this->addChild(m_pHpBar);
	//set the hpbar to a good position
	Size size = getContentSize();
	m_pHpBar->setPosition(ccp(size.width/2,size.height));
	//load action
	int pos = m_resource.find_last_of('/');
	std::string name = m_resource.substr(pos+1);
	//load action
	//horizontcal
	Animation* horizontalAction = Entity::createNormalAction(std::string(name+"-horizontal%d.png").c_str(),0,m_monsterFrame.horizontal,m_monsterFrame.horizontal*2);
	setHorizontalWalkAction(RepeatForever::create(Animate::create(horizontalAction)));
	//up
	Animation*upAction = Entity::createNormalAction(std::string(name+"-up%d.png").c_str(),0,m_monsterFrame.up,m_monsterFrame.up*2);
	setUpWalkAction(RepeatForever::create(Animate::create(upAction)));
	//down
	Animation*downAction = Entity::createNormalAction(std::string(name+"-down%d.png").c_str(),0,m_monsterFrame.down,m_monsterFrame.down*2);
	setDownWalkAction(RepeatForever::create(Animate::create(downAction)));
	//dead
	Animation*deadAction = Entity::createNormalAction(std::string(name+"-dead%d.png").c_str(),0,m_monsterFrame.dead,m_monsterFrame.dead*2);
	CallFunc*deadCall = CallFunc::create([&](){
		this->unschedule(schedule_selector(Monster::updateSelf));
		this->removeFromParent();
	});
	setDeadAction(Sequence::create(Animate::create(deadAction),deadCall,nullptr));
}
bool Monster::changeState(EnumMonsterActionType type)
{
	if(m_type != EnumMonsterActionType::enActionType_dead && m_type != type)
	{
		m_pSprite->stopAllActions();
		m_type = type;
		return true;
	}
	return false;
}
void Monster::runHorizontalWalkAction()
{
	if(changeState(EnumMonsterActionType::enActionType_horizontal))
	{
		m_pSprite->runAction(m_pHorizontalWalkAction);
	}
}
void Monster::runUpWalkAction()
{
	if(changeState(EnumMonsterActionType::enActionType_up))
	{
		m_pSprite->runAction(m_pUpWalkAction);
	}
}
void Monster::runDownWalkAction()
{
	if(changeState(EnumMonsterActionType::enActionType_down))
	{
		m_pSprite->runAction(m_pDownWalkAction);
	}
}
void Monster::runDeadAction()
{
	if(changeState(EnumMonsterActionType::enActionType_dead))
	{
		m_pSprite->runAction(m_pDeadAction);
	}
}