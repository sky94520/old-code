#include "EnemyLayer.h"
#include "Enemy.h"
#include "GameScene.h"
#include "BehaviorManager.h"

EnemyLayer::EnemyLayer()
	:m_pDelegate(nullptr)
{
}
EnemyLayer::~EnemyLayer()
{
}
bool EnemyLayer::init()
{
	return true;
}
void EnemyLayer::update(float dt)
{
	//对怪物进行更新
	for(auto iter = m_enemys.begin();iter != m_enemys.end();)
	{
		auto enemy = *iter;
		if(this->isObsolete(enemy))
		{
			iter = m_enemys.erase(iter);
			enemy->removeFromParent();
		}
		else
		{
			enemy->performMove(dt);
			++iter;
		}
	}
}
vector<Enemy*>& EnemyLayer::getEnemys()
{
	return m_enemys;
}
void EnemyLayer::enemyBorn(TMXObject*object,Layer*layer)
{
	ValueVector strs = StringUtils::split(object->name.c_str(),'-');
	//获取属性列表
	auto properties = object->getProperties();

	Enemy*enemy = nullptr;
	//智能生成对象 从后向前遍历
	while(!strs.empty())
	{
		auto enemyName = strs.back().asString();
		strs.pop_back();
		//赋予属性
		auto behaviorStr = StringUtils::format("%s-behavior",enemyName.c_str());
		auto velocityStr = StringUtils::format("%s-velocity",enemyName.c_str());
		//查找属性并赋值
		Point velocity = Point::ZERO;
		MoveBehavior*behavior = nullptr;

		auto behaviorIter = properties.find(behaviorStr);
		if(behaviorIter != properties.end())
		{
			behavior = BehaviorManager::getInstance()->getMoveBehaviorByType(behaviorIter->second);
		}
		auto velocityIter = properties.find(velocityStr);
		if(velocityIter != properties.end())
		{
			const char*text = velocityIter->second.c_str();
			SDL_sscanf(text,"%f,%f",&velocity.x,&velocity.y);
		}
		//尝试创建对象
		if(enemyName == "trimushroom")
		{
			enemy = TriMushroom::create();
		}
		else if(enemyName == "tortoise")
		{
			auto temp = Tortoise::create();
			temp->setOldVelocity(Point(SDL_fabs(velocity.x),velocity.y));
			enemy = temp;
		}
		else if(enemyName == "chomper")
		{
			auto e = Chomper::create();
			//获取最高位置
			auto maxHeight = SDL_atof(properties.at("max-jump-height").c_str());
			e->setMaxJumpHeight(maxHeight);
			e->setDelegate(m_pDelegate);
			e->setShapeRect(Rect(object->x,object->y,object->width,object->height));
			e->setStampImmune(true);
			enemy = e;
		}
		else if(enemyName == "fly")
		{
			enemy = WingEnemyDecorator::create(enemy);
		}
		enemy->setMaxHp(1);
		enemy->setCurHp(1);
		enemy->setDamage(1);
		enemy->setVelocity(velocity);
		enemy->setMoveBehavior(behavior);
	}
	enemy->setPosition(object->x + object->width/2,object->y + object->height/2);

	enemy->runRunnableAnimation();
	m_enemys.push_back(enemy);
	layer->addChild(enemy);
}
void EnemyLayer::setDelegate(EnemyDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
bool EnemyLayer::isObsolete(Enemy*enemy)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return enemy->isDead()
		||(enemy->getPositionY() > visibleSize.height);
}