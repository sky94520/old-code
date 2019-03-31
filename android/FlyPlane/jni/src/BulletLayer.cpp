#include "BulletLayer.h"
#include "Bullet.h"
#include "Plane.h"

BulletLayer::BulletLayer()
	:m_pFactory(nullptr)
{
}
BulletLayer::~BulletLayer()
{
	SDL_SAFE_DELETE(m_pFactory);
}
bool BulletLayer::init()
{
	//�����ӵ�����
	m_pFactory = BulletFactory::create();
	m_pFactory->retain();

	return true;
}
void BulletLayer::update(float dt)
{
	for(auto iter = m_bullets.begin();iter != m_bullets.end();)
	{
		auto bullet = *iter;
		if(bullet->isDead() == false)
			bullet->update(dt);
		//ɾ�����bullet
		if(bullet->isAlive() == false)
		{
			//ɾ��body
			auto body = static_cast<b2Body*>(bullet->getUserData());
			PhysicalEngine::getInstance()->destroyBody(body);
			//�ӳ�����ɾ��
			iter = m_bullets.erase(iter);
			bullet->removeFromParent();
		}
		else
			++iter;
	}
}
void BulletLayer::shooting(Plane*plane,BulletType type)
{
	auto bullet = m_pFactory->orderBullet(type);
	this->addChild(bullet);
	m_bullets.push_back(bullet);
	//�����������
	b2Body*body = PhysicalEngine::getInstance()->createBox(bullet->getContentSize(),b2_dynamicBody);

	b2Fixture*fixture = body->GetFixtureList();
	
	fixture->SetFilterData(plane->getBulletFilter());
	body->SetUserData(bullet);
	bullet->setUserData(body);
	body->ResetMassData();
	//�����ӵ���λ�ú���ת�Ƕ�
	float curAngle = plane->getSprite()->getRotation();
	Point pos = plane->getPosition();
	Size size = plane->getContentSize();

	float degree = 3.1415926/180 * curAngle;
	//��ȡx y�ϵķ���
	float x = cos(degree) * size.height/2;
	float y = sin(degree) * size.height/2;

	Point curPos = pos + Point(x,y);
	
	bullet->getSprite()->setRotation(curAngle);
	bullet->setPosition(curPos);
	bullet->setOwner(plane);
}
void BulletLayer::reset()
{
	for(auto iter = m_bullets.begin();iter != m_bullets.end();)
	{
		auto bullet = *iter;
		iter = m_bullets.erase(iter);
		//ɾ��body
		auto body = static_cast<b2Body*>(bullet->getUserData());
		PhysicalEngine::getInstance()->destroyBody(body);
		bullet->removeFromParent();
	}
}