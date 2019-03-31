#include "GameLayer.h"
#include "Player.h"
#include "FireArrow.h"
GameLayer::GameLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr),m_pArrow(nullptr)
{
}
GameLayer::~GameLayer()
{
}
GameLayer*GameLayer::create(GameLayerDelegate*pDelegate)
{
	auto layer = new GameLayer();
	if(layer && layer->init(pDelegate))
		layer->autorelease();
	else
		CC_SAFE_DELETE(layer);
	return layer;
}
bool GameLayer::init(GameLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
	ValueMap playerMap = m_pDelegate->getObject("player");
	m_pPlayer = Player::create();
	Size s = m_pPlayer->getContentSize();
	int x = playerMap.at("x").asInt() + s.width/2;
	int y = playerMap.at("y").asInt() + s.height/2;
	m_pPlayer->setPosition(ccp(x,y));
	this->addChild(m_pPlayer);
	//´´½¨¼ý
	m_pArrow = FireArrow::create();
	this->addChild(m_pArrow);
	return true;
}
void GameLayer::aimAt(const Point&pos)
{
	m_pPlayer->aimAt(pos);
}
void GameLayer::shootTo(const Point&pos)
{
	if(m_pArrow->isAlive() == false)
	{
		m_pPlayer->shootTo(pos);
		m_pArrow->start(m_pPlayer->getPosition(),pos);
	}
}
Arrow* GameLayer::getArrow()const
{
	return m_pArrow;
}