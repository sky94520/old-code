#include "Cattail.h"
#include "ZombieBase.h"
#include "Carrier.h"

Cattail::Cattail()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_duration(0.f),m_pAim(nullptr)
	,m_nBulletNum(0),m_nCurBulletNum(0)
	,m_nDamage(20)
{
}

Cattail::~Cattail()
{
	SDL_SAFE_RELEASE_NULL(m_pAim);
}

Cattail*Cattail::create(const string& plantName)
{
	auto plant = new Cattail();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Cattail::init(const string& plantName)
{
	if (VesselPlant::init(TerrainType::LilyPad))
	{
		//�����ڲ����岻����ֲ
		this->getInnerCarrier()->setDestroyed(true);
		//����ֲ����
		this->setPlantName(plantName);
		//���ö�������ͼ
		auto animationName = plantName;
		auto animation = AnimationCache::getInstance()->getAnimation(animationName);
		auto animate = Animate::create(animation);

		animate->setTag(ANIMATION_TAG);
		//�󶨾���
		this->bindSpriteWithAnimate(animate);
		//���õ�ǰ״̬
		m_state = State::Normal;
		//���õ�ǰ�ӵ�����
		m_nBulletNum = 2;
		//��������λ��
		auto size = this->getContentSize();
		m_pSprite->setPosition(size.width/5 * 2,size.height/3);
	}
	return true;
}

void Cattail::updateHook(float dt)
{
	switch (m_state)
	{
	case State::Normal: this->updateNormalState(dt);break;
	case State::Attack: this->updateAtkState(dt); break;
	case State::AttackEnd: this->updateAtkEndState(dt); break;
	}
}

void Cattail::updateNormalState(float dt)
{
	if (m_elapsed < this->getColdDownTime())
	{
		m_elapsed += dt;
		return;
	}
	//���ֳ����Ƿ���ڽ�ʬ
	auto zombie = m_pDelegate->findFirstZombieOfRow(-1,this->getDir(),this->getPosition());

	if (zombie != nullptr)
	{
		SDL_SAFE_RETAIN(zombie);

		m_pAim = zombie;
		m_elapsed = 0.f;
		//���õ�ǰ�����ӵ�
		m_nCurBulletNum = 0;
		//ת������״̬
		this->changeState(State::Attack);
	}
}

void Cattail::updateAtkState(float dt)
{
	m_elapsed += dt;
	//���﹥��ʱ��
	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		//����ӵ�
		m_pDelegate->addCornpultBullet(m_pAim,false,m_nDamage,-1,this->getPosition());

		this->changeState(State::AttackEnd);
	}
}

void Cattail::updateAtkEndState(float dt)
{
	m_nCurBulletNum++;
	m_elapsed = 0.f;
	//���﹥������ �ı�״̬�����ͷŸý�ʬ
	if (m_nCurBulletNum >= m_nBulletNum)
	{
		this->changeState(State::Normal);
		SDL_SAFE_RELEASE_NULL(m_pAim);
	}
	else//��������
	{
		this->changeState(State::Attack);
	}
}

void Cattail::changeState(State state)
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
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAtk",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAtkEnd",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
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