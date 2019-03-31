#include "Threepeater.h"

Threepeater::Threepeater()
{
}

Threepeater::~Threepeater()
{
}

Threepeater * Threepeater::create(const string& plantName)
{
	auto plant = new Threepeater();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Threepeater::init(const string& plantName)
{
	m_plantName = plantName;

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	return true;
}

void Threepeater::updateAttackState(float dt)
{
	//��ȡ��ǰ��
	int row = m_pCarrier->getRow();

	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//�Է����λ�ý���ȷ��
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//ÿ�η��������㶹
	for (int i = - 1;i <= 1;i++)
	{
		int r = i + row;
		//���Ǳ߽�����
		if (r < 0)
			continue;
		//��ȡ����λ��
		Point bornPos = startPos + Point(0.f,i * size.height);
		//�����㶹
		this->shootPeaBullet(r,bornPos);
	}
	//ת������״̬
	m_state = State::Normal;
}

void Threepeater::updateAttackEndState(float dt)
{
}

ZombieBase* Threepeater::findFirstZombie()
{
	//��ȡ��ǰ������
	int row = m_pCarrier->getRow();
	//ÿ�μ�������
	for (int i = row - 1;i <= row + 1;i++)
	{
		//���Ǳ߽�����
		if (i < 0)
			continue;
		//��ȡ��ǰ���Ƿ���ڽ�ʬ
		auto zombie = m_pDelegate->findFirstZombieOfRow(i,this->getDir(),this->getPosition());

		if (zombie != nullptr)
			return zombie;
	}

	return nullptr;
}