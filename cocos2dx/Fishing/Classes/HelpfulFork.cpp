#include "HelpfulFork.h"
HelpfulFork::HelpfulFork()
	:m_pRealSprite(nullptr)
{
}
HelpfulFork::~HelpfulFork()
{
}
bool HelpfulFork::init()
{
	//³õÊ¼»¯
	bindSprite(Sprite::create("fork.png"));

	m_pRealSprite = Sprite::create("fork.png");
	Size s = this->getContentSize();

	m_pRealSprite->setPosition(Point(s.width/2,s.height/2));
	m_pRealSprite->setOpacity(100);
	this->addChild(m_pRealSprite);
	
	return true;
}
float HelpfulFork::runMovingAction(const Point&endPos1,const Point&endPos2)
{
	float delay = 0.05f;
	//m_pSpriteÐé¼ÙÓã²æ
	MoveBy*move1 = MoveBy::create(delay,this->convertToNodeSpace(endPos1));
	MoveBy*move2 = MoveBy::create(delay,this->convertToNodeSpace(endPos2));

	m_pRealSprite->runAction(move1);
	m_pSprite->runAction(move2);

	return delay;
}