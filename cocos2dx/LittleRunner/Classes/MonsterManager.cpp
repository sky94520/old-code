#include "MonsterManager.h"
#include "Player.h"

bool MonsterManager::init()
{
	createMonsters();
	this->scheduleUpdate();

	return true;
}
void MonsterManager::createMonsters()
{
	Monster*monster = NULL;
	Sprite*sprite = NULL;

	for (int i = 0;i < MAX_MONSTER_NUM;i++)
	{
		monster = Monster::create();
		monster->bindSprite(Sprite::create("monster.png"));
		monster->reset();
		this->addChild(monster);
		m_monsterArr.pushBack(monster);
	}
}
void MonsterManager::update(float dt)
{
	for(auto monster:m_monsterArr)
	{
		monster->setPositionX(monster->getPositionX()-4);
		if (monster->getPositionX() < 0)
			monster->hide();
		else if (monster->isCollideWithPlayer(m_player))
		{
			m_player->hit();
			monster->hide();
		}
		else
			monster->show();
	}
}
void MonsterManager::bindPlayer(Player*player)
{
	m_player = player;

}