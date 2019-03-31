#include "PotatoMine.h"
#include "StaticData.h"
#include "ZombieBase.h"

PotatoMine::PotatoMine()
	:m_state(State::Ready),m_elapsed(0.f)
	,m_nDamage(0),m_duration(0.f)
{
}

PotatoMine::~PotatoMine()
{
}

PotatoMine*PotatoMine::create(const string&plantName)
{
	auto plant = new PotatoMine();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool PotatoMine::init(const string&plantName)
{
	this->setPlantName(plantName);
	//������ͼ
	auto spriteName = STATIC_DATA_STRING("potato_mine_not_ready_sprite_name");
	
	this->bindSpriteWithSpriteFrameName(spriteName);

	return true;
}

void PotatoMine::updateHook(float dt)
{
	//��ǰ����׼���׶�
	if (m_state == State::Ready)
	{
		m_elapsed += dt;
		//��������ʱ�䣬����
		if (m_elapsed >= this->getColdDownTime())
		{
			this->readySuccess();

			m_elapsed = 0.f;
			this->changeState(State::Rising);
			//��������
			this->setOpenShade(true);
		}
	}
	else if (m_state == State::Rising)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->changeState(State::ReadySuccess);
			//�ر�����
			this->setOpenShade(false);
		}
	}
	else if (m_state == State::ReadySuccess)
	{
		//���н�ʬ�ļ��
		this->checkCollision();
	}
}

void PotatoMine::readySuccess()
{
	//��ʾ������Ч
	auto pos = this->getPosition();
	Size size = this->getContentSize();
	auto localZOrder = this->getLocalZOrder();

	m_pDelegate->showRisingDirt(pos + Point(0,size.height/3),localZOrder + 1);
}

void PotatoMine::checkCollision()
{
	auto row = m_pCarrier->getRow();
	auto rect = this->getBoundingBox();
	auto pos = this->getPosition();

	auto zombie = m_pDelegate->findFirstCollidedZombie(row,rect);
	//������ײ��ը����ʬ
	if (zombie != nullptr && zombie->getHitPoint() > 0)
	{
		//չʾ��Ч
		m_pDelegate->showExplosionSpudow(pos);
		//ֱ������
		this->setHitPoint(0);
		this->setDead(true);
		//��ը
		m_pDelegate->addBoom(this->getDamage(),row,rect);
	}
}

void PotatoMine::changeState(State state)
{
	if (state == m_state)
		return;

	m_state = state;
	//������Ч
	if (m_state == State::Rising)
	{
		//��ȡ������Ķ���
		auto animation = AnimationCache::getInstance()->getAnimation(this->getPlantName());
		auto firstFrame = animation->getFrames().front()->getSpriteFrame();

		this->getSprite()->setSpriteFrame(firstFrame);
		//���ó���ʱ��
		m_duration = 0.4f;
		//����λ��
		auto size = this->getSprite()->getContentSize();
		auto pos = this->getSprite()->getPosition();

		this->getSprite()->setPosition(pos + Point(0.f,size.height/2));
		//������������
		MoveBy*move = MoveBy::create(m_duration,Point(0.f,-size.height/2));

		this->getSprite()->runAction(move);
	}
	else if (m_state == State::ReadySuccess)
	{
		//��ȡ������Ķ���
		auto animation = AnimationCache::getInstance()->getAnimation(this->getPlantName());
		auto animate = Animate::create(animation);
		this->getSprite()->runAction(animate);
	}

}