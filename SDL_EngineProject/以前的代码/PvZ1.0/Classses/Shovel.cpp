#include "Shovel.h"
Shovel::Shovel()
	:m_pSprite(nullptr),m_pBackground(nullptr),m_bSelected(false)
{
}
Shovel::~Shovel()
{
}
bool Shovel::init()
{
	m_pBackground = Sprite::create("Resources/ShovelBack.png");
	m_pSprite = Sprite::create("Resources/Shovel.png");
	setContentSize(m_pSprite->getContentSize());
	//add
	this->addChild(m_pBackground);
	this->addChild(m_pSprite,2);

	return true;
}
void Shovel::clear()
{
	m_pSprite->stopAllActions();
	m_pSprite->setOpacity(255);
	m_pSprite->setPosition(0,0);
	m_pSprite->setRotation(0);
	m_bSelected = false;
}
bool Shovel::isSelected()const
{
	return m_bSelected;
}
void Shovel::setSelected(bool selected)
{
	m_bSelected = selected;
}
Sprite* Shovel::getSprite()const
{
	return m_pSprite;
}
void Shovel::runBlinkAction()
{
	auto fade = FadeOut::create(0.5f);
	ActionInterval* sequence = static_cast<ActionInterval*>(Sequence::create(fade,fade->reverse(),nullptr));
	//ActionInterval*blink = Blink::create(1.f,2);
	m_pSprite->runAction(RepeatForever::create(sequence));
}
void Shovel::runKillPlantAction(const Point&pos)
{
	m_pSprite->stopAllActions();
	m_pSprite->setOpacity(255);
	m_pSprite->setRotation(-30);
	CallFunc*callfunc = CallFunc::create([&,this](){
		this->clear();
	});
	MoveBy*move = MoveBy::create(0.15f,Point(-50,25));
	m_pSprite->runAction(Sequence::createWithTwoActions(move,callfunc));
	//ÉèÖÃ²ù×ÓÎ»ÖÃ
	auto p2 = this->getWorldPosition();
	auto p3 = pos - p2 + Point(50,-25);
	//printf("%.2f %.2f",p3.x,p3.y);
	m_pSprite->setPosition(p3);
}