#include "PlayerLayer.h"
#include "StaticData.h"
#include "Player.h"
#include "GameScene.h"

PlayerLayer::PlayerLayer()
	:m_nCurPlayer(-1)
	,m_bRoundOver(false)
{
}

PlayerLayer::~PlayerLayer()
{
}

bool PlayerLayer::init()
{

	return true;
}

void PlayerLayer::update(float dt)
{
	//�غϻ�δ����
	if (!m_bRoundOver)
		return;
	//��ʼ�µ�һ��
	m_bRoundOver = false;
	m_nCurPlayer = (m_nCurPlayer + 1) % m_players.size();
	auto player = m_players.at(m_nCurPlayer);
	//���в��� �����ί�У��򽻸���Ӧ�Ľű� TODO
	if (player->isDelegated())
	{
		//TODO
		m_bRoundOver = true;
	}
	else//��ť����
	{
		GameScene::getInstance()->setGameState(GameState::Normal);
	}
}

void PlayerLayer::createAnimationOfPlayer(Texture*texture,const string& playerName)
{
	//��ȡ��ɫ���򶯻��ַ���
	auto format = STATIC_DATA_STRING("character_walking_animation_name_format");
	auto array = STATIC_DATA_ARRAY("character_dir_array");

	//��Ӷ���
	auto callback = [&format,&array,&playerName](int i,const vector<SpriteFrame*>& frames)
	{
		auto sDir = array.at(i).asString();
		auto animationName = StringUtils::format(format.c_str(),playerName.c_str(),sDir.c_str());
		Animation* animation = Animation::createWithSpriteFrames(frames,0.1f,-1);
		AnimationCache::getInstance()->addAnimation(animation,animationName);
	};

	StaticData::getInstance()->split(texture,nullptr,Size(32,48),callback);
}

void PlayerLayer::addPlayer(Player* player)
{
	m_players.push_back(player);

	this->addChild(player);
}