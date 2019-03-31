#include "Bullet.h"
#include "Fish.h"
Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}
bool Bullet::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("bullet_level_1.png"));
	return true;
}
void Bullet::setDelegate(BulletDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
Rect Bullet::getBulletCollisionRect()const
{
	Rect boundingBox = getBoundingBox();
	boundingBox.origin = getWorldPosition();
	return boundingBox;
}
void Bullet::flyTo(const Point&target,float angle)
{
	//�����ӵ�ͼƬ
	//�����������ӵ�������չ
	std::string format = StringUtils::format("bullet_level_%d.png",m_pDelegate->getCannonType());
	bindSprite(Sprite::createWithSpriteFrameName(format));
	//������ת��
	getSprite()->setRotation(angle);
	this->setVisible(true);
	CallFunc*callfunc = CallFunc::create(SDL_CALLBACK_0(Bullet::end,this));
	//�ٶȺ㶨
	float times = sqrt(pow(target.x,2)+pow(target.y,2))/300.f;

	this->runAction(Sequence::createWithTwoActions(MoveBy ::create(times,target),callfunc));
}
void Bullet::end()
{
	//ֹͣ���ж���
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//��ת����Ϊ0
	getSprite()->setRotation(0);
	this->setVisible(false);
	//��������
	Size size = getContentSize();
	Point pos = getPosition() - Point(size.width/2,size.height/2);
	m_pDelegate->showAt(getPosition());
}