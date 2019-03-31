#include "GameLayer.h"
#include "PhysicalEngine.h"

GameLayer::GameLayer()
{
}
GameLayer::~GameLayer()
{
}
bool GameLayer::init()
{
	m_pFork = Fork::create();
	m_pFork->setAnchorPoint(Point(0.5f,0.f));
	m_pFork->setRotation(45.f);
	m_pFork->setVisible(false);
	//×îºó»æÖÆ
	m_pFork->setGlobalZOrder(20);
	
	this->addChild(m_pFork);
	PhysicalEngine::getInstance()->bindBodyForFork(m_pFork);

	return true;
}
Fork*GameLayer::getFork()const
{
	return m_pFork;
}