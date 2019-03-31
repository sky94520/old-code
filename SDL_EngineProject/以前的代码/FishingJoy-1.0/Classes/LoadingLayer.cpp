#include "LoadingLayer.h"
#include "GameScene.h"
LoadingLayer::LoadingLayer()
	:m_allIndex(0),m_curIndex(0),
	m_pLoadingBar1(nullptr),m_pLoadingBar2(nullptr)
{
	//xml�ļ�
	std::vector<std::string>*xml = new std::vector<std::string>();
	xml->push_back("fishingjoy-resource1.xml");
	xml->push_back("fishingjoy-resource2.xml");
	xml->push_back("coin.xml");
	xml->push_back("bullet_button.xml");
	
	m_resources.insert(std::make_pair("xml",xml));
	//music
	std::vector<std::string>*music = new std::vector<std::string>();
	music->push_back("bg_music.mp3");
	m_resources.insert(std::make_pair("music",music));
	//effect
	std::vector<std::string>*effect = new std::vector<std::string>();
	effect->push_back("sound_shot.mp3");
	effect->push_back("bgm_fire.wav");
	effect->push_back("bgm_coin_01.mp3");
	effect->push_back("sound_button.mp3");
	m_resources.insert(std::make_pair("effect",effect));

	m_allIndex = xml->size() + music->size() + effect->size();
}
LoadingLayer::~LoadingLayer()
{
}
Scene*LoadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
bool LoadingLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite*bg = Sprite::create("loading_1.png");
	Size bgSize = bg->getContentSize();
	bg->setPositionX(visibleSize.width/2-bgSize.width/2);
	this->addChild(bg);
	//���loadingbar
	Sprite*loadingBarBg1 = Sprite::create("loading_2bg.png");
	m_pLoadingBar1 = LoadingBar::create("loading_2.png",0.f,Direction::LEFT);
	float x = visibleSize.width/2 - loadingBarBg1->getContentSize().width/2;
	m_pLoadingBar1->setPosition(x,bgSize.height);
	loadingBarBg1->setPosition(x,bgSize.height);
	this->addChild(loadingBarBg1);
	this->addChild(m_pLoadingBar1);

	Sprite*loadingBarBg2 = Sprite::create("loading_3bg.png");
	m_pLoadingBar2 = LoadingBar::create("loading_3.png",0.f,Direction::LEFT);
	float x2 = visibleSize.width/2 - m_pLoadingBar2->getContentSize().width/2;
	loadingBarBg2->setPosition(x2,300);
	m_pLoadingBar2->setPosition(x2,300);
	this->addChild(loadingBarBg2);
	this->addChild(m_pLoadingBar2);
	//����
	this->scheduleUpdate();
	//��ʼ������Դ
	m_iterMap = m_resources.begin();
	return true;
}
void LoadingLayer::update(float dt)
{
	//���õ�ǰ������
	m_pLoadingBar1->setPercent((float)m_curIndex/m_allIndex);
	m_pLoadingBar2->setPercent((float)m_curIndex/m_allIndex);
	////���������� ��ת����Ϸ����
	if(m_iterMap == m_resources.end())
	{
		
		this->unscheduleUpdate();
		Director::getInstance()->replaceScene(GameScene::create());
		return;
	}
	//��ȡ��Ӧ���͵���Դ����
	auto vec = m_iterMap->second;
	//��ĿΪ�գ�ɾ��
	if(vec->empty())
	{
		m_iterMap = m_resources.erase(m_iterMap);
		delete vec;
		return;
	}
	auto vecIter = vec->begin();
	auto path = *vecIter;
	auto type = m_iterMap->first;
	if(type == "xml")
	{
		Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile(path);
	}
	else if(type == "music")
	{
		SoundManager::getInstance()->preloadBackgroundMusic(path);
	}
	else if(type == "effect")
	{
		SoundManager::getInstance()->preloadEffect(path);
	}
	vec->erase(vecIter);
	m_curIndex++;
}