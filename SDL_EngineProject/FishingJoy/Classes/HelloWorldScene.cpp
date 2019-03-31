#include "HelloWorldScene.h"
#include "SDL_gfx.h"
#include "GB2ShapeCache-x.h"
#include "StaticData.h"
#include "RotateSpeedSprite.h"
#include "Entity.h"
#include "GoldCounter.h"
#include "ScrollLabel.h"

HelloWorld::HelloWorld()
{
}
HelloWorld::~HelloWorld()
{
}
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);

	//Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("resources1.xml");
	

/*	ccBezierConfig config;
	config.controlPoint_1 = Point(300,-500);
	config.controlPoint_2 = Point(800,-200);

	config.endPosition = Point(960,-640);

	auto bezier = BezierBy::create(20.f,config);

	auto move = MoveBy::create(3.f,Point(100,0));
	auto move2 = MoveBy::create(3.f,Point(100,100));

	RotateSpeedSprite*action = RotateSpeedSprite::create(bezier);

	vector<FiniteTimeAction*> vecs;
	vecs.push_back(move);

	m_pSprite->runAction(RotateSpeedSprite::create(action));*/

/*	auto callback = [this](float dt)
	{
		//Òì²½¼ÓÔØÉùÒô
		SoundManager::getInstance()->addSoundAsync("sound/music_1.ogg",Music::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/music_2.ogg",Music::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/music_3.ogg",Music::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		//ÒôÐ§
		SoundManager::getInstance()->addSoundAsync("sound/sound_box_01.wav",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_change_cannon.ogg",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_coin_01.ogg",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_go.wav",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_laser.ogg",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_net.ogg",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/bgm_so.wav",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/sound_LevelUp.ogg",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/sound_OpenChest_0.wav",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
		SoundManager::getInstance()->addSoundAsync("sound/sound_shot.wav",Chunk::TYPE,SDL_CALLBACK_2(HelloWorld::asyncLoadSoundCallback,this));
	};*/

	return true;
}
void HelloWorld::update(float dt)
{
}