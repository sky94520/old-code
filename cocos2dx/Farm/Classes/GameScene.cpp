#include "GameScene.h"
GameScene::GameScene()
	:m_pTouchLayer(nullptr),m_pMapLayer(nullptr)
	,m_pShopLayer(nullptr)
{
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	//添加触碰层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//地图层
	m_pMapLayer = MapLayer::create();
	this->addChild(m_pMapLayer);
	//商店层
	m_pShopLayer = ShopLayer::create();
	m_pShopLayer->setMapLayer(m_pMapLayer);
	this->addChild(m_pShopLayer);

	Node*layer = CSLoader::createNode("start_res/MainScene.csb");
	//this->addChild(layer);
	//ui::CheckBox
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources1.plist");
		//创建精灵动画 保存在AnimationCache中
	auto frameName = "fish01_%02d.png";
	auto frameCount = 9;

	Vector<SpriteFrame*> frames;
	for(int i = 0;i < frameCount;i++)
	{
		auto str = StringUtils::format(frameName,i);
		SpriteFrame*spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		frames.pushBack(spriteFrame);
	}
	Animation*a1 = Animation::createWithSpriteFrames(frames,0.1f,-1);

	Sprite*sprite = Sprite::createWithSpriteFrameName("fish01_00.png");
	sprite->setPosition(300,300);
	this->addChild(sprite);
	sprite->runAction(Animate::create(a1));

	this->scheduleUpdate();
	return true;
}
void GameScene::operateBackground(const std::vector<Touch*>&touches,Event*event)
{
	m_pMapLayer->operateMap(touches,event);
}
void GameScene::setScaleForBackground(EventMouse*event)
{
	m_pMapLayer->setScaleForMap(event);
}
void GameScene::update(float dt)
{

}