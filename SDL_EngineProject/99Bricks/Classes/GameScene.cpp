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
	//初始化物理引擎
	this->initPhysicalWorld();
	//初始化方块层
	m_pBrickLayer = BrickLayer::create();
	this->addChild(m_pBrickLayer);

	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	//遍历物理模型 并进行更新
	/*for(auto body = PhysicalEngine::getInstance()->getBodyList();body;body = body->GetNext())
	{

	}*/
	//显示调试绘图
	PhysicalEngine::getInstance()->step(dt,6,2);
	PhysicalEngine::getInstance()->drawDebugData();
}
bool GameScene::initPhysicalWorld()
{
	Size s = Director::getInstance()->getVisibleSize();
	auto physicalEngine = PhysicalEngine::getInstance();

	physicalEngine->initPhysicalWorld();
	//设置边界
	b2Body*bottom = physicalEngine->createEdge(Point(0,s.height),Point(s.width,s.height),b2_staticBody);
	
	return true;
}