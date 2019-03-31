#include "StartScene.h"
#include "GameScene.h"
#include "ShopLayer.h"
#include "DynamicData.h"
#include "CsvUtil.h"

StartScene::StartScene()
	:m_pStartMenuLayer(nullptr),m_pShopLayer(nullptr)
	,m_pActiveLayer(nullptr)
{
}
StartScene::~StartScene()
{
	DynamicData::getInstance()->purge();
	CsvUtil::getInstance()->purge();
}
bool StartScene::init()
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	//���ز�����Դ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("button/start_resources.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/shop_resources.xml");
	//���ؿ�ʼ�˵���
	m_pStartMenuLayer = StartMenuLayer::create();
	m_pStartMenuLayer->setDelegate(this);
	this->addChild(m_pStartMenuLayer);
	//�̵��
	m_pShopLayer = ShopLayer::create();
	m_pShopLayer->setVisible(false);
	m_pShopLayer->setDelegate(this); 
	this->addChild(m_pShopLayer); 
	//����Ĭ����ʾ��
	this->selectActiveLayer(m_pStartMenuLayer);
	return true;
}
void StartScene::selectActiveLayer(Layer*layer)
{
	if(layer == m_pActiveLayer)
		return;
	//����Ϊ���ɻ
	if(m_pActiveLayer)
	{
		m_pActiveLayer->setVisible(false);
	}
	m_pActiveLayer = layer;
	layer->setVisible(true);
}
void StartScene::gameStart()
{
	Director::getInstance()->replaceScene(GameScene::create("level/map1.tmx"));
}
void StartScene::gotoShop()
{
	this->selectActiveLayer(m_pShopLayer);
}
void StartScene::gameExit()
{
	//Director::getInstance()->gameOver();
}
void StartScene::backToStartMenuLayer()
{
	this->selectActiveLayer(m_pStartMenuLayer);
}