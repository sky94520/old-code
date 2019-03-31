#include "GameScene.h"
#include "BrickLayer.h"

GameScene::GameScene()
	:m_pBrickLayer(nullptr)
{
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	//��ʼ����������
	this->initPhysicalWorld();
	//��ʼ�������
	m_pBrickLayer = BrickLayer::create();
	this->addChild(m_pBrickLayer);

	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	//��������ģ�� �����и���
	/*for(auto body = PhysicalEngine::getInstance()->getBodyList();body;body = body->GetNext())
	{

	}*/
	//��ʾ���Ի�ͼ
	PhysicalEngine::getInstance()->step(dt,6,2);
	PhysicalEngine::getInstance()->drawDebugData();
}
bool GameScene::initPhysicalWorld()
{
	Size s = Director::getInstance()->getVisibleSize();
	auto physicalEngine = PhysicalEngine::getInstance();

	physicalEngine->initPhysicalWorld();
	//���ñ߽�
	b2Body*bottom = physicalEngine->createEdge(Point(0,s.height),Point(s.width,s.height),b2_staticBody);
	
	return true;
}