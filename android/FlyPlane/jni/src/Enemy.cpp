#include "Enemy.h"
#include "EnemyStateFSM.h"

Enemy::Enemy()
	:m_elapsed(0.f),m_pPlayer(nullptr)
	,m_pFSM(nullptr)
{
}
Enemy::~Enemy()
{
	SDL_SAFE_RELEASE(m_pFSM);
}
Enemy*Enemy::create(Plane*player)
{
	auto enemy = new Enemy();
	if(enemy && enemy->init(player))
		enemy->autoRelease();
	else
		SDL_SAFE_DELETE(enemy);
	return enemy;
}
bool Enemy::init(Plane*player)
{
	m_pPlayer = player;
	//初始化状态机
	m_pFSM = EnemyStateFSM::create();
	m_pFSM->retain();
	this->bindSprite(Sprite::createWithSpriteFrameName("smallplane_1.png"));
	return true;
}
void Enemy::flee()
{
	m_pFSM->flee(this,m_pPlayer);
}
void Enemy::update(float dt)
{
	Entity::update(dt);
	m_elapsed += dt;
	//到了时间，尝试改变当前状态
	if(m_elapsed >= 1.2f)
	{
		m_elapsed = 0.f;

		int ran = rand()%2;
		switch(ran)
		{
		case 0:m_pFSM->chase(this,m_pPlayer);break;
		//case 1:m_pFSM->flee(this,m_pPlayer);break;
		case 1:m_pFSM->shoot(this,m_pPlayer);break;
		}
	}
}
void Enemy::onDead()
{
	//先停止所有动作
	//this->stopAllActions();
	//死亡动画
	auto deadAnimate = Entity::createAnimate("smallplane_d%d.png",1,4,0.1,1);
	auto delayTime = DelayTime::create(deadAnimate->getDuration());
	auto onAlive = CallFunc::create([this](){
		this->setAlive(false);
	});
	this->getSprite()->runAction(deadAnimate);
	this->runAction(Sequence::create(delayTime,onAlive,NULL));
	SoundManager::getInstance()->playEffect("music/bigplane_bomb.wav",0);
}