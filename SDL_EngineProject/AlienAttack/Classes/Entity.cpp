#include "Entity.h"

Entity::Entity()
	:m_pSprite(nullptr),m_nCurHp(0),m_nMaxHp(0)
	,m_bDead(false)
{
}
Entity::~Entity()
{
}
void Entity::bindSprite(Sprite*sprite)
{
	this->m_pSprite = sprite;
	this->addChild(m_pSprite);

	Size size = m_pSprite->getContentSize();

	m_pSprite->setPosition(size.width/2,size.height/2);
	this->setContentSize(size);
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}
Animate*Entity::createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops)
{
	vector<SpriteFrame*> frames;
	auto spriteFrameCache = Director::getInstance()->getSpriteFrameCache();
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.push_back(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	if(loops == 1)
		animation->setRestoreOriginalFrame(true);
	return Animate::create(animation);
}
void Entity::hurt(int damage)
{
	//�����ʱ�Ѿ����������ٵ���
	if(this->isDying() || this->isDead())
		return;
	int curHp = this->getCurHp();
	int afterHp = curHp - damage;
	//ֻҪ���˾͵����������
	onHurt(damage);
	setCurHp(afterHp);
	if(afterHp <= 0)
		onDead();//����ʱ����
}
bool Entity::isDying()const
{
	return m_nCurHp <= 0;
}

void Entity::onBindSprite()
{
}
void Entity::onHurt(int damage)
{
}
void Entity::onDead()
{
}