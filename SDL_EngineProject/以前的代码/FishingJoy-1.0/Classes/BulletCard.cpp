#include "BulletCard.h"
BulletCard::BulletCard()
	:m_nBulletCount(0),m_pDisabledSprite(nullptr),m_pLabel(nullptr)
{
}
BulletCard::~BulletCard()
{
}
BulletCard*BulletCard::create(BulletType type)
{
	auto bulletCard = new BulletCard();
	if(bulletCard && bulletCard->init(type))
		bulletCard->autoRelease();
	else
		SDL_SAFE_DELETE(bulletCard);
	return bulletCard;
}
bool BulletCard::init(BulletType type)
{
	 m_type = type;
	//����ӦͼƬ
	std::string filename = StringUtils::format("button_bullet_%d.png",m_type);
	bindSprite(Sprite::createWithSpriteFrameName(filename));
	
	//��ȡ��Ӧ�ӵ���
	m_nBulletCount = FishingJoyData::getInstance()->getBulletCountByType(m_type);
	//��ʾ��Ŀ
	m_pLabel = LabelAtlas::create(Value(m_nBulletCount).asString(),"fonts_bullet.png",
		15,15,'0');
	Size s = m_pLabel->getContentSize();
	m_pLabel->setPosition(getContentSize().width/2-s.width/2,-s.height/2);
	this->addChild(m_pLabel,10);
	
	m_pDisabledSprite = Sprite::createWithSpriteFrameName("ui_mission.png");
	this->addChild(m_pDisabledSprite,12);
	if(m_nBulletCount > 0)
		m_pDisabledSprite->setVisible(false);
	return true;
}
bool BulletCard::subBulletCount()
{
	//��������ڵ�ҩ
	if(m_nBulletCount - 1 >= 0)
	{
		m_nBulletCount -= 1;
		m_pLabel->setString(Value(m_nBulletCount).asString());
		//֪ͨFishingJoyData
		FishingJoyData::getInstance()->setBulletCountByType(m_type,m_nBulletCount);
		//���ɵ��
		if(m_nBulletCount == 0)
			m_pDisabledSprite->setVisible(true);
		return true;
	}
	return false;
}
BulletCard*BulletCard::clone()const
{
	/*auto bulletCard = new BulletCard();
	bulletCard->m_type = this->m_type;
	bulletCard->bindSprite(this->getSprite()->clone());
	bulletCard->m_pLabel*/
	return BulletCard::create(m_type);
}
bool BulletCard::isClicked()const
{
	return !m_pDisabledSprite->isVisible();
}
BulletType BulletCard::getType()const
{
	return m_type;
}