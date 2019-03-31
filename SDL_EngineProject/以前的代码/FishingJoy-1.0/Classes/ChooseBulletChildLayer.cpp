#include "ChooseBulletChildLayer.h"
#include "BulletCard.h"
ChooseBulletChildLayer::ChooseBulletChildLayer()
{
}
ChooseBulletChildLayer::~ChooseBulletChildLayer()
{
}
bool ChooseBulletChildLayer::init()
{
	//添加子弹卡片
	BulletCard*b1 = BulletCard::create(BulletType::kBulletType_1);
	this->addChild(b1);
	BulletCard*b2 = BulletCard::create(BulletType::kBulletType_2);
	Size s = b2->getContentSize()+Size(5,0);
	b2->setPosition(s.width,0);
	this->addChild(b2);
	m_bulletCardVector.push_back(b1);
	m_bulletCardVector.push_back(b2);
	return true;
}
BulletCard* ChooseBulletChildLayer::getSelectedItem(const Point&pos)
{
	for(unsigned int i=0;i<m_bulletCardVector.size();i++)
	{
		auto bulletCard = m_bulletCardVector.at(i);
		//如果不可点击，则取消掉这次点击
		if(bulletCard->isClicked() == false)
			continue;
		Rect rect = bulletCard->getBoundingBox();
		rect.origin = bulletCard->getWorldPosition();

		if(rect.containsPoint(pos))
			return bulletCard;
	}
	return nullptr;
}
BulletCard*ChooseBulletChildLayer::getItemByType(BulletType type)
{
	return m_bulletCardVector.at(type - 1);
}