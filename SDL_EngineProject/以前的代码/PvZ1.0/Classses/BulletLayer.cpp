#include "BulletLayer.h"
#include "Bullet.h"
BulletLayer::BulletLayer()
{
}
BulletLayer::~BulletLayer()
{
}
bool BulletLayer::init()
{
	return true;
}
void BulletLayer::update(float dt)
{
	for(int i=0;i<m_bullets.size();i++)
	{
		auto bullet = m_bullets.at(i);
		if(bullet->isDead())
		{
			//bullet->stopAllActions();
			m_bullets.eraseObject(bullet);
			this->removeChild(bullet);
		}
	}
}
void BulletLayer::shootTo(const Point&startPos,const Point&endPos,const std::string& bulletName,BulletRoute route)
{
	auto bullet = Bullet::create(bulletName);
	bullet->setPosition(startPos);
	//动作
	if(route == BulletRoute::kBulletRoute_line)
	{
		Size s = Director::getInstance()->getVisibleSize();
		auto delta = Point(s.width + bullet->getContentSize().width + 150,startPos.y);
      		MoveTo*move = MoveTo::create((delta.x - startPos.x)/bullet->getSpeed(),delta);
		//交由update统一管理
		CallFunc*end = CallFunc::create([&,bullet](){
			bullet->setDead(true);
		});
		bullet->runAction(Sequence::createWithTwoActions(move,end));
	}
	else if(route == BulletRoute::kBulletRoute_jump)
	{
	}
	m_bullets.push_back(bullet);
	this->addChild(bullet);
}