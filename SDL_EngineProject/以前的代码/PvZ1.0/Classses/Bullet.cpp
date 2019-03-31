#include "Bullet.h"
#include "MainLua.h"
Bullet::Bullet()
	:m_nDamage(0),m_nSpeed(0),m_nAtkRange(0),m_normalImage(""),m_deadImage("")
	,m_nHitPoint(1),m_bDead(false),m_bAvailable(true)
{
}
Bullet::~Bullet()
{
}
Bullet*Bullet::create(const std::string&name)
{
	auto bullet = new Bullet();
	if(bullet && bullet->init(name))
		bullet->autoRelease();
	else
		SDL_SAFE_DELETE(bullet);
	return bullet;
}
bool Bullet::init(const std::string&name)
{
	//��ȡ�����ļ�
	m_nDamage = MainLua::getInstance()->getIntegerFromTable(name,"damage");
	m_nSpeed = MainLua::getInstance()->getIntegerFromTable(name,"speed");
	m_nAtkRange = MainLua::getInstance()->getIntegerFromTable(name,"distance");
	m_normalImage = MainLua::getInstance()->getStringFromTable(name,"normalImage");
	m_deadImage = MainLua::getInstance()->getStringFromTable(name,"deadImage");
	//��ͼƬ
	bindSprite(Sprite::createWithSpriteFrameName(m_normalImage));
	
	//Director::getInstance()->getSpriteFrameCache()->addImage(m_deadImage);
	return true;
}
void Bullet::hurt(int damage)
{
	auto hp = m_nHitPoint - damage;
	
	setHitPoint(hp);

	if(hp <=0)
	{
		m_bAvailable = false;
		onDeadAction();
	}
}
FiniteTimeAction* Bullet::onDeadAction()
{
	//������������ ����ڽ�ʬ��ֲ�����ʱ�ᷢ���ڴ�й©��Ī������
	//bindSprite(Sprite::create(m_deadImage));
	auto anim = Entity::createAnimation(m_deadImage,1,1,0.1f,1);
	this->stopAllActions();
	this->getSprite()->runAction(anim);
	DelayTime*delay = DelayTime::create(anim->getDuration());
	CallFunc*dead = CallFunc::create([&,this]()
	{
		this->m_bDead = true;
	});
	this->runAction(Sequence::createWithTwoActions(delay,dead));
	return nullptr;
}
void Bullet::setDead(bool dead)
{
	m_bDead = dead;
}
bool Bullet::isDead()const
{
	return m_bDead;
}