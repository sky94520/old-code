#include "LoadingLayer.h"
#include "GameScene.h"

LoadingLayer::LoadingLayer()
	:m_pProgress1(nullptr),m_pProgress2(nullptr)
	,m_nCurIndex(0),m_nSize(0)
{
}
LoadingLayer::~LoadingLayer()
{
}

Scene* LoadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingLayer::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("loading.xml");
	//���ͼƬ
	Sprite*background = Sprite::create("start.jpg");
	background->setAnchorPoint(Point::ZERO);
	this->addChild(background);

	Sprite*bg = Sprite::createWithSpriteFrameName("loading_1.png");
	bg->setPosition(visibleSize.width/2,0);
	bg->setAnchorPoint(Point(0.5f,0.f));
	this->addChild(bg);
	//����loading����
	Sprite*loadingSprite = Sprite::createWithSpriteFrameName("loading_3.png");
	loadingSprite->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(loadingSprite);
	//����������
	m_pProgress1 = ProgressTimer::create(Sprite::createWithSpriteFrameName("loading_2.png"));
	m_pProgress1->setType(ProgressTimer::Type::BAR);
	m_pProgress1->setBarChangeRate(Point(1.f,0.f));
	m_pProgress1->setMidpoint(Point(0.f,0.5f));
	m_pProgress1->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(m_pProgress1);
	//������
	Size size = loadingSprite->getContentSize();

	Sprite*barSprite = Sprite::createWithSpriteFrameName("loading_4.png");
	barSprite->setPosition(visibleSize.width/2,visibleSize.height/2 + size.height);
	this->addChild(barSprite);
	//����������
	m_pProgress2 = ProgressTimer::create(Sprite::createWithSpriteFrameName("loading_5.png"));
	m_pProgress2->setType(ProgressTimer::Type::BAR);
	m_pProgress2->setBarChangeRate(Point(1.f,0.f));
	m_pProgress2->setMidpoint(Point(0.f,0.5f));
	m_pProgress2->setPosition(visibleSize.width/2,visibleSize.height/2 + size.height);
	this->addChild(m_pProgress2);

	//��ȡ����
	auto valueMap = FileUtils::getInstance()->getValueMapFromFile("data/load_res.plist");

	for(auto dict:valueMap)
	{
		auto key = dict.first;
		auto &vec = dict.second.asValueVector();
		m_nSize += vec.size();

		for (auto value:vec)
		{
			auto filename = value.asString();
			
			if (key == "png")
			{
				m_images.push_back(filename);
			}
			else if (key == Music::TYPE)
			{
				m_musics.push_back(filename);
			}
			else if (key == Chunk::TYPE)
			{
				m_chunks.push_back(filename);
			}
		}
	}
	//�ȼ��ص�һ��ͼƬ
	//���صĹ���Ϊ ͼƬ=> ���� => ��Ч
	//this->loadImageCallback(nullptr);

	auto callback = [this](float)
	{
		this->loadImageCallback(nullptr);
	};

	this->scheduleOnce(callback,"loading");
	//this->loadImageCallback(nullptr);

	return true;
}
void LoadingLayer::loadImageCallback(Texture*texture)
{
	//ͼƬ������ɣ��������ֵļ���
	if (m_images.empty())
	{
		this->loadMusicCallback(nullptr,"");
	}
	else
	{
		auto filename = m_images.front();
		//�����첽����
		Director::getInstance()->getTextureCache()->addImageAsync(filename,
			SDL_CALLBACK_1(LoadingLayer::loadImageCallback,this));
		m_images.pop_front();
	}
	//��ǰָ��Ϊ�գ������и���
	if(!m_images.empty())
		this->loadResAsyncCallback();
}

void LoadingLayer::loadMusicCallback(Object*sound,const string&type)
{
	if (m_musics.empty())
	{
		this->loadChunkCallback(nullptr,"");
	}
	else
	{
		auto filename = m_musics.front();

		SoundManager::getInstance()->addSoundAsync(filename,Music::TYPE
			,SDL_CALLBACK_2(LoadingLayer::loadMusicCallback,this));
		m_musics.pop_front();
	}

	if (!m_musics.empty())
		this->loadResAsyncCallback();
}

void LoadingLayer::loadChunkCallback(Object*sound,const string&type)
{
	//��Դȫ���������,����ҳ�����ת
	if (m_chunks.empty())
	{
		auto scene = GameScene::create();

		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		auto filename = m_chunks.front();

		SoundManager::getInstance()->addSoundAsync(filename,Chunk::TYPE
			,SDL_CALLBACK_2(LoadingLayer::loadChunkCallback,this));
		m_chunks.pop_front();
	}

	if (!m_chunks.empty())
		this->loadResAsyncCallback();
}

void LoadingLayer::loadResAsyncCallback()
{
	float percentage = 100.f * (m_nCurIndex + 1)/m_nSize;

	m_pProgress1->setPercentage(percentage);
	m_pProgress2->setPercentage(percentage);

	m_nCurIndex++;
}