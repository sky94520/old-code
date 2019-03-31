#include "Enemy.h"
#include "CsvUtil.h"
#include "StaticData.h"
#include "DynamicData.h"
#include "StringUtil.h"
Enemy::Enemy()
	:m_elapased(0.f),m_nDeadFrameNum(0)
{
}
Enemy*Enemy::createWithID(int id)
{
	auto enemy = new Enemy();
	if(enemy && enemy->initWithID(id))
		enemy->autorelease();
	else
		CC_SAFE_DELETE(enemy);
	return enemy;
}
bool Enemy::initWithID(int id)
{
	std::string csv = StaticData::getInstance()->getStringForKey("enemyPath");
	//该ID所在的行数
	int nLine = -1;
	nLine = CsvUtil::getInstance()->findLineByValue(Value(id),0,csv);
	if(nLine < 0)
		return false;
	setID(id);
	m_name = CsvUtil::getInstance()->getValue(nLine,1,csv).asString();
	m_nHitPoints = CsvUtil::getInstance()->getValue(nLine,2,csv).asInt();
	m_speed = CsvUtil::getInstance()->getValue(nLine,3,csv).asFloat();
	m_nScore = CsvUtil::getInstance()->getValue(nLine,4,csv).asInt();
	m_time = CsvUtil::getInstance()->getValue(nLine,5,csv).asFloat();
	m_nDamage = CsvUtil::getInstance()->getValue(nLine,6,csv).asInt();
	m_nDefense = CsvUtil::getInstance()->getValue(nLine,7,csv).asInt();
	m_nDeadFrameNum = CsvUtil::getInstance()->getValue(nLine,8,csv).asInt();
	//绑定精灵
	bindSprite(Sprite::createWithSpriteFrameName(m_name + ".png"));

	m_nCurHP = 0;
	setVisible(false);
	return true;
}
void Enemy::update(float dt)
{
}
void Enemy::onHurt()
{
}
void Enemy::onDead()
{
	//增加分数
	DynamicData::getInstance()->alertScore(this->getScore());
	//停止所有动画和动作
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//死亡动画
	std::string format = m_name + "-dead%d.png";
	auto deadAnim = Entity::createAnimate(format,1,m_nDeadFrameNum,0.1f,1);
	CallFunc*callfunc = CallFunc::create([this]()
	{
		this->setVisible(false);
	});
	DelayTime*delay = DelayTime::create(deadAnim->getDuration());
	this->getSprite()->runAction(deadAnim);
	this->runAction(Sequence::createWithTwoActions(delay,callfunc));
}