#include "Hero.h"
#include "CsvUtil.h"
Hero::Hero():m_nBaseAtk(0),m_nCurAtk(0),m_nAtkSpeed(0),m_nAtkRange(0),
	m_nUpgradeCostBase(0),m_fUpgradeAtkBase(0),m_pAtkMonster(nullptr)
	,m_bIsCanAttack(true)
{
	FILE_PATH = "";
}
Hero::~Hero()
{
}
bool Hero::initWithCsvFileByID(int nHeroID)
{
	return true;
}
/*Hero*Hero::createFromCsvFileByID(int nHeroID)
{
	Hero*_hero = new Hero();
	if(_hero&&_hero->initWithCsvFileByID(nHeroID))
	{
		_hero->autorelease();
		return _hero;
	}
	CC_SAFE_DELETE(_hero);
	return NULL;
}
bool Hero::initWithCsvFileByID(int nHeroID)
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
		m_resource = csvUtil->getValue(nLine,enHeroPropConfType_Resources,"csv/hero.csv").asString();
		
		bindSprite(Sprite::create(m_resource.c_str()));
		bRet = true;
	}while(0);
	return bRet;
}*/
void Hero::logic(float dt,Vector<Monster*>& monsterList)
{
	if(m_pAtkMonster !=nullptr)
	{
		//delete the object
		if(m_pAtkMonster->isDead())
		{
			monsterList.eraseObject(m_pAtkMonster);
			m_pAtkMonster = nullptr;
			return;
		}
		//if the monster is not dead,and whether can attack
		if(m_bIsCanAttack)
			attack();
		//judge the locked monster is out of the range
		checkAimIsOutOfRange(monsterList);
	}
	else//choose one monster
	{
		chooseAim(monsterList);
	}
}
void Hero::attack()
{
}
void Hero::checkAimIsOutOfRange(Vector<Monster*> monsterList)
{
	if(m_pAtkMonster != nullptr)
	{
		if(isInAtkRange(m_pAtkMonster->getPosition()) == false)
		{
			log("out of range");
			m_pAtkMonster = nullptr;
		}
	}
}
bool Hero::isInAtkRange(Point pos)
{
	int atkRange = getAtkRange();
	Point heroPos = getPosition();

	float length = pos.getDistanceSq(heroPos);
	if(length <= atkRange*atkRange)
		return true;
	return false;
}
void Hero::chooseAim(Vector<Monster*>& monsterList)
{
	for(auto monster:monsterList)
	{
		//if the monster is visible and in range
		if(monster->isVisible() && isInAtkRange(monster->getPosition()))
		{
			log("lock!");
			m_pAtkMonster = monster;
			break;
		}
	}
}
void Hero::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	if(true)
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(Hero::onDraw,this,transform,flags);
		renderer->addCommand(&_customCommand);
	}
}
void Hero::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	//设置画笔粗细
	glLineWidth(1.f);
	//绘制圆形
	Size size = getContentSize();
	DrawPrimitives::drawCircle(Point(size.width/2,size.height/2),getAtkRange(),360,20,false);
	glLineWidth(1);
	//结束绘制
	kmGLPopMatrix();
}
void Hero::attackEnd(float dt)
{
	m_bIsCanAttack = true;
}
void Hero::onBindSprite()
{
}