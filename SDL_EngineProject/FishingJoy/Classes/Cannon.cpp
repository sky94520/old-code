#include "Cannon.h"
#include "StaticData.h"

Cannon::Cannon()
	:m_type(Type::None),m_bCanFire(true)
	,m_pSprite(nullptr),m_lastType(Type::None)
	,m_pDelegate(nullptr)
{
}

Cannon::~Cannon()
{
}

bool Cannon::init()
{
	//�Ծ����ʼ��
	auto spriteName = this->getSpriteName(Type::Lv1);
	m_pSprite = Sprite::createWithSpriteFrameName(spriteName);
	this->addChild(m_pSprite);

	Size size = m_pSprite->getContentSize();
	m_pSprite->setPosition(size.width/2,size.height/2);

	this->setContentSize(size);

	m_type = Type::Lv1;

	return true;
}

void Cannon::aimAt(const Point&target)
{
	//���ó���
	auto delta = this->convertToNodeSpaceAR(target);

	float degree = std::atan2f((delta.y),delta.x);
	//���ýǶ� ����һ��ʼ���ڵ��Ǵ�ֱ�ģ����Լ���90��
	float rotation = SDL_DEGREE_TO_ANGLE(degree) + 90.f;
	
	m_pSprite->setRotation(rotation);
}

void Cannon::fire(const Point&pos)
{
	//���ò��ɷ���״̬
	this->setCanFire(false);
	std::string animationName;

	if(m_type == Type::Laser)
	{
		animationName = STATIC_DATA_STRING("laser_fire_anim");

	}
	else
	{
		auto animationFormat = STATIC_DATA_STRING("cannon_fire_anim");
		int level = static_cast<int>(m_type);
		animationName = StringUtils::format(animationFormat.c_str(),level);
	}
	//��ȡ����
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate*animate = Animate::create(animation);
	//�ص����ຯ�����з���
	CallFunc*end = CallFunc::create([this,pos]()
	{
		m_pDelegate->fireCallback(pos);
	});
	//���ж���
	auto seq = Sequence::create(animate,end,NULL);
	m_pSprite->runAction(seq);
}
void Cannon::fireEnd()
{
	//�ɼ�������
	this->setCanFire(true);
	//������ͼ
	auto spriteName = this->getSpriteName(m_type);
	m_pSprite->setSpriteFrame(spriteName);
}
void Cannon::addLevel()
{
	Type type = Type::None;
	//��ȡ��ǰ���������
	auto iter = find(m_netBulletTypes.cbegin(),m_netBulletTypes.cend(),m_type);
	//��ǰ���Ͳ�����֮�У�ֱ�ӷ���
	if(iter == m_netBulletTypes.end())
	{
		//todo
		return ;
	}
	++iter;
	//�������һ������ص���һ��
	if(iter == m_netBulletTypes.end())
		type = m_netBulletTypes.front();
	else
		type = *iter;

	this->setType(type);
}

void Cannon::subLevel()
{
	Type type = Type::None;
	//��ȡ��ǰ���������
	auto iter = find(m_netBulletTypes.cbegin(),m_netBulletTypes.cend(),m_type);
	//���δ�ҵ�����ֱ�ӷ���
	if(iter == m_netBulletTypes.end())
	{
		//todo
		return;
	}
	//����ǵ�һ������ص����һ��
	if(iter == m_netBulletTypes.cbegin())
	{
		type = m_netBulletTypes.back();
	}
	else
	{
		--iter;
		type = *iter;
	}

	this->setType(type);
}

float Cannon::getRotation()const
{
	return m_pSprite->getRotation();
}

void Cannon::setType(Cannon::Type type)
{
	//��ǰ���ͺ͸ı��������ͬ���򲻸ı�
	if(m_type == type)
		return;

	m_lastType = m_type;
	//�����ǰ���ͺ͸ı�����Ͷ�����ͨ�ӵ�����
	if(this->isBelongNetBulletType(type) && this->isBelongNetBulletType(m_type))
	{
		this->setCanFire(false);
		//��С����
		ScaleTo*scale1 = ScaleTo::create(0.25f,0.f,0.f);

		CallFunc*setSpCallback = CallFunc::create([type,this]()
		{
			auto spriteName = this->getSpriteName(type);
			this->m_pSprite->setSpriteFrame(spriteName);
		});
		ScaleTo*scale2 = ScaleTo::create(0.25f,1.f,1.f);

		CallFunc*end = CallFunc::create([this]()
		{
			this->setCanFire(true);
		});

		auto seq = Sequence::create(scale1,setSpCallback,scale2,end,NULL);

		m_pSprite->runAction(seq);
	}
	else
	{
		this->setCanFire(false);
		//����ԭ��������
		Size size = m_pSprite->getContentSize();

		MoveBy*move1 = MoveBy::create(1.f,Point(0,size.height));
		CallFunc*toogleImage = CallFunc::create([type,this]()
		{
			auto spriteName = this->getSpriteName(type);
			this->m_pSprite->setSpriteFrame(spriteName);
		});
		MoveBy*move2 = MoveBy::create(1.f,Point(0,-size.height));
		CallFunc*end = CallFunc::create([this]()
		{
			this->setCanFire(true);
		});

		auto seq = Sequence::create(move1,toogleImage,move2,end,NULL);
		m_pSprite->runAction(seq);
	}
	m_type = type;
}

Cannon::Type Cannon::getType()const
{
	return m_type;
}

void Cannon::setDelegate(CannonDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

bool Cannon::isBelongNetBulletType(Cannon::Type type)
{
	auto iter = find(m_netBulletTypes.begin(),m_netBulletTypes.end(),type);
	return iter != m_netBulletTypes.end();
}

int Cannon::getNetGunBulletLv()const
{
	return static_cast<int>(m_type);
}

Cannon::Type Cannon::getLastType()const
{
	return m_lastType;
}

void Cannon::setNetGunBullets(const vector<int>&vec)
{
	for(auto lv : vec)
	{
		m_netBulletTypes.push_back(static_cast<Cannon::Type>(lv));
	}
}

string Cannon::getSpriteName(Type type)
{
	if(type == Type::Laser)
		return STATIC_DATA_STRING("laster_sprite_name");

	auto spriteFormat = STATIC_DATA_STRING("cannon_sprite_format");
	int cannonLevel = static_cast<int>(type);
	auto spriteName = StringUtils::format(spriteFormat.c_str(),cannonLevel);

	return spriteName;
}
