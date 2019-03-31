#include "ScaredyShroom.h"
#include "ZombieBase.h"

ScaredyShroom::ScaredyShroom()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_nDamage(0)
{
}

ScaredyShroom*ScaredyShroom::create(const string&plantName)
{
	auto plant = new ScaredyShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool ScaredyShroom::init(const string& plantName)
{
	//���������Ķ���
	this->setPlantName(plantName);
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	
	this->bindSpriteWithAnimate(animate);
	//����״̬Ϊ����״̬
	m_state = State::Normal;

	return true;
}

void ScaredyShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::Attack)
	{
		this->updateAtkState(dt);
	}
	else if (m_state == State::Scared)
	{
		this->updateScaredState(dt);
	}
}

void ScaredyShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void ScaredyShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void ScaredyShroom::updateAtkState(float dt)
{
	int damage = this->getDamage();
	int row = m_pCarrier->getRow();
	//ȷ������λ��
	auto bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/2;
	bornPos.y += size.height/5;
	//ֱ�ӽ��й���
	m_pDelegate->addShroomBullet(damage,row,bornPos,-1.f);
	//��������
	this->changeState(State::Normal);
}

void ScaredyShroom::changeState(State state)
{
	if (m_state == state)
		return;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		animationName = plantName;
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Sleeping)
	{
		animationName = StringUtils::format("%sSleep",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Scared)
	{
		animationName = StringUtils::format("%sCry",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	if (animation == nullptr)
		return;
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��������
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}

void ScaredyShroom::updateNormalState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//���ݵ�ǰ����ȷ����һ����ʬ
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);

	if (zombie == nullptr)
		return;
	//���ֽ�ʬ�ص����� ���ܻ���к���״̬
	this->findZombie(zombie);

	m_elapsed += dt;
	//���й���
	if (m_elapsed >= this->getColdDownTime())
	{
		m_elapsed -= this->getColdDownTime();
		//ת�빥��״̬
		this->changeState(State::Attack);
	}
}

void ScaredyShroom::updateScaredState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//���ݵ�ǰ����ȷ����һ����ʬ
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);
	
	//��ǰ��ʬΪ�ջ��߾����Զ�����˳�����״̬
	if (!isScared(zombie))
	{
		this->changeState(State::Normal);
	}
}

void ScaredyShroom::findZombie(ZombieBase*zombie)
{
	if (this->isScared(zombie))
	{
		this->changeState(State::Scared);
		//��ʱ���
		m_elapsed = 0.f;
	}
}

bool ScaredyShroom::isScared(ZombieBase*zombie)
{
	//�����ڽ�ʬ�����Ầ��
	if (zombie == nullptr)
		return false;

	auto zombiePosX = zombie->getCollisionBoundingBox().origin.x;
	auto plantPosX = this->getPositionX();

	auto delta = SDL_fabs(plantPosX - zombiePosX);
	//�ͽ�ʬ�ľ���ܽ���ת�뺦��״̬
	if (delta < 60.f)
		return true;
	else
		return false;
}