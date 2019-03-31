#include "GameScene.h"
#include "BackgroundLayer.h"
#include "Arrow.h"
GameScene::GameScene()
	:m_pBackgroundLayer(nullptr),m_pTiledMapLayer(nullptr)
	,m_pGameLayer(nullptr),m_pTouchLayer(nullptr)
{
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	//������Դ
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("texture.plist","texture.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��������
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//������ͼ
	m_pTiledMapLayer = TiledMapLayer::create("map1.tmx");
	this->addChild(m_pTiledMapLayer);
	//������Ϸ������
	m_pGameLayer = GameLayer::create(this);
	this->addChild(m_pGameLayer);
	//���Ŵ���
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//��ȡƫ��λ��
	//auto offsetX = -(m_pTiledMap->getContentSize().width - visibleSize.width)/2;
	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	//�����ײ
	checkCollistion();
}
void GameScene::checkCollistion()
{
	auto pArrow = m_pGameLayer->getArrow();
	//������Ѿ�����ż��
	if(pArrow->isAlive())
	{
		//��ȡ��������
		auto pos = pArrow->getPosition();
		//��ȡ�������µ�GID
		auto valueMap = m_pTiledMapLayer->getValueMapByPosition("logicLayer",pos);
		if(valueMap.empty())
			return;
		else
			pArrow->end();
	}
}
ValueMap GameScene::getObject(const std::string&name)
{
	return m_pTiledMapLayer->getObject(name);
}
void GameScene::arrowAimAt(const Point&pos)
{
	m_pGameLayer->aimAt(pos);
}
void GameScene::arrowShootTo(const Point&pos)
{
	m_pGameLayer->shootTo(pos);
}