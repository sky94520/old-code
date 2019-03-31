#include "TiledMapAnimationTest.h"
TiledMapAnimationTest::TiledMapAnimationTest()
{
}
TiledMapAnimationTest::~TiledMapAnimationTest()
{
}
Scene*TiledMapAnimationTest::createScene()
{
	Scene*scene = Scene::create();
	auto layer = TiledMapAnimationTest::create();
	scene->addChild(layer);
	return scene;
}
bool TiledMapAnimationTest::init()
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(107,140,255,255);

	TMXTiledMap*tiledMap = TMXTiledMap::create("1.tmx");
	this->addChild(tiledMap);
	//创建动画
	vector<SpriteFrame*> frames;
	SpriteFrame*frame1 = SpriteFrame::create("mario_0_run00.png",Rect(0,0,16,31));
	SpriteFrame*frame2 = SpriteFrame::create("mario_0_run01.png",Rect(0,0,16,31));
	frames.push_back(frame1);
	frames.push_back(frame2);
	//生成动画
	Animation*animation = Animation::createWithSpriteFrames(frames,0.1f,-1);
	Animate*animate = Animate::create(animation);

	Sprite*sprite = Sprite::create("mario_0_run01.png");
	sprite->setPosition(300,300);
	sprite->runAction(animate);
	this->addChild(sprite);
	return true;
}