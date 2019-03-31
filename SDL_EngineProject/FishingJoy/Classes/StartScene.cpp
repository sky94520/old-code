#include "StartScene.h"
#include "GameScene.h"
#include "LevelChooseLayer.h"
#include "LoadingLayer.h"
#include "FishingJoyData.h"
#include "Toast.h"

StartScene::StartScene()
	:m_pStartLayer(nullptr),m_pLevelChooseLayer(nullptr)
	,m_pHelpLayer(nullptr)
{
}
StartScene::~StartScene()
{
}
bool StartScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//����ͼƬ��Դ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("start_ui.xml");
	//���뱳��
	Sprite*bg = Sprite::create("start.jpg");
	bg->setAnchorPoint(Point::ZERO);
	this->addChild(bg);
	//��ʼ����
	m_pStartLayer = StartLayer::create();
	m_pStartLayer->setDelegate(this);
	this->addChild(m_pStartLayer);
	//�ؿ�ѡ�����
	m_pLevelChooseLayer = LevelChooseLayer::create();
	m_pLevelChooseLayer->setPosition(0,-visibleSize.height);
	m_pLevelChooseLayer->setVisible(false);
	m_pLevelChooseLayer->setDelegate(this);
	this->addChild(m_pLevelChooseLayer);
	//��������
	m_pHelpLayer = HelpLayer::create();
	m_pHelpLayer->setDelegate(this);
	m_pHelpLayer->setVisible(false);
	m_pHelpLayer->setPosition(0,-visibleSize.height);

	this->addChild(m_pHelpLayer);
	//����ui
	m_pStartLayer->updateUI();
	m_pLevelChooseLayer->updateUI();
	//��������
	SoundManager::getInstance()->addSoundAsync("sound/bgm_start_scene.ogg",Music::TYPE
		,SDL_CALLBACK_2(StartScene::asyncLoadMusicCallback,this));

	return true;
}

void StartScene::enterTollgateLayer()
{
	this->startGame();
}

void StartScene::startGame()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pStartLayer->setActive(false);

	m_pLevelChooseLayer->setVisible(true);
	m_pLevelChooseLayer->setPosition(0,-visibleSize.height);
	//������ʾѡ�����
	MoveBy*move = MoveBy::create(0.5f,Point(0,visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pLevelChooseLayer->runAction(action);
}

void StartScene::helpGame()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pStartLayer->setActive(false);

	m_pHelpLayer->setVisible(true);
	m_pHelpLayer->setPosition(0,-visibleSize.height);
	//������ʾѡ�����
	MoveBy*move = MoveBy::create(0.5f,Point(0,visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pHelpLayer->runAction(action);
}

void StartScene::exitGame()
{
	Director::getInstance()->setRunning(false);
}

void StartScene::changeMusic()
{
	auto soundManager = SoundManager::getInstance();
	bool playingMusic = FishingJoyData::getInstance()->isPlayingMusic();
	playingMusic = !playingMusic;
	//��Ҫ��������
	if(playingMusic)
		soundManager->playBackgroundMusic("sound/bgm_start_scene.ogg",-1);
	else
		soundManager->stopBackgroundMusic();
	//��д
	FishingJoyData::getInstance()->setPlayingMusic(playingMusic);
}

void StartScene::changeSound()
{
	bool bPlayingChunk = FishingJoyData::getInstance()->isPlayingChunk();
	bPlayingChunk = ! bPlayingChunk;
	//��д
	FishingJoyData::getInstance()->setPlayingChunk(bPlayingChunk);
}

void StartScene::asyncLoadMusicCallback(Object*sound,const std::string&type)
{
	//���ű�������
	if(type == Music::TYPE)
	{
		Music*music = static_cast<Music*>(sound);
		bool bPlayingMusic = FishingJoyData::getInstance()->isPlayingMusic();

		if (bPlayingMusic)
			music->playMusic(-1);
	}
}

void StartScene::closeLevelChooseLevel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pStartLayer->setActive(true);

	//������ʾѡ�����
	MoveBy*move = MoveBy::create(0.5f,Point(0,-visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pLevelChooseLayer->runAction(action);
}

void StartScene::closeHelpLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pStartLayer->setActive(true);

	//������ʾѡ�����
	MoveBy*move = MoveBy::create(0.5f,Point(0,-visibleSize.height));
	EaseExponentialOut*action = EaseExponentialOut::create(move);

	m_pHelpLayer->runAction(action);
}

void StartScene::enterLoadingLayer()
{
	//������Դ��ж�� todo
	//����һЩ��Ҫ���ж�
	int tollgateIndex = m_pLevelChooseLayer->getTollgateIndex();
	int needfulGold = 0;
	int allGold = FishingJoyData::getInstance()->getGold();
	//todo ��ȡ����˹ؿ�����Ҫ�Ľ��
	if(tollgateIndex == 0)
		needfulGold = 10;
	else if(tollgateIndex == 1)
		needfulGold = 50;
	else if (tollgateIndex == 2)
		needfulGold = 100;
	//����Ƿ��㹻
	if(allGold >= needfulGold)
	{
		//���ٽ�Ҳ���д
		FishingJoyData::getInstance()->setGold(allGold - needfulGold);
		//���½���
		m_pLevelChooseLayer->updateUI();
		//д�뵽�ĵ���
		FishingJoyData::getInstance()->setTollgateIndex(tollgateIndex);

		auto scene = LoadingLayer::createScene();
		Director::getInstance()->replaceScene(scene);
		//�ɹ�����
		Sprite*sprite = Sprite::createWithSpriteFrameName("UI_enterSuccess.png");

		Toast::makeSprite(scene,sprite,1.5f);
	}
	else//����ʧ��
	{
		Sprite*sprite = Sprite::createWithSpriteFrameName("UI_enterDefault.png");
		Toast::makeSprite(this,sprite,1.5f);
	}
}