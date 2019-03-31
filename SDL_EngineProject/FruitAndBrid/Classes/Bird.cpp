#include "Bird.h"
Bird::Bird()
	:m_bFlying(false),m_id(1)
	,m_elapsed(0.f),m_bDead(false)
{
}
Bird::~Bird()
{
}
Bird*Bird::create(int id)
{
	auto bird = new Bird();
	if(bird && bird->init(id))
		bird->autoRelease();
	else
		SDL_SAFE_DELETE(bird);
	return bird;
}
bool Bird::init(int id)
{
	m_id = id;
	
	bindSprite(Sprite::createWithSpriteFrameName(StringUtils::format("bird%d_1.png",id)));
	return true;
}
void Bird::fly()
{
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//��������
	auto str = StringUtils::format("bird%d_%s.png",m_id,"%d");
	auto flyAnimate = Entity::createAnimate(str,1,3,0.1f,1);

	this->getSprite()->runAction(flyAnimate);
	//����
	this->m_bFlying = true; 
	//����
	JumpBy*jump = JumpBy::create(0.4f,Point(0,0),-70,1);
	CallFunc*end = CallFunc::create([this]()
	{
		this->setFlying(false);
	});
	this->runAction(Sequence::createWithTwoActions(jump,end));
	//�½��ٶ�����
	m_elapsed = 0.f;
}
void Bird::down(float dt)
{
	float g = 9.8f;
	//�����һʱ�̵��ٶ�
	m_elapsed += dt;
	float v = g * m_elapsed;

	//��þ���
	float distance = 4 + 0.5 * g * m_elapsed * m_elapsed;
	//���þ���
	this->setPositionY(this->getPositionY() + distance);
}
void Bird::dead()
{
	m_bDead = true;
	//todo 
	//С���½�������󵯳�������

}