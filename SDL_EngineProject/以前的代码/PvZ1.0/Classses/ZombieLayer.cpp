#include "ZombieLayer.h"
#include "Zombie.h"
ZombieLayer::ZombieLayer()
{
	for(int i=0;i<5;i++)
	{
		m_zombies[i] = nullptr;
		m_zombies[i] = new Vector<Zombie*>();
	}
}
ZombieLayer::~ZombieLayer()
{
	for(int i=0;i<5;i++)
	{
		m_zombies[i]->clear();
		delete m_zombies[i];
	}
}
bool ZombieLayer::init()
{
	return true;
}
bool ZombieLayer::createZombiesFromXml(const std::string&filepath)
{
	xml_document<> doc;
	file<> file(filepath.c_str());
	//解析
	doc.parse<0>(file.data());
	//获取root
	xml_node<>*root = doc.first_node();
	//zombie
	for(xml_node<>*node = root->first_node();node;node = node->next_sibling())
	{
		std::string name = node->first_node("name")->value();
		//std::string name = node->first_attribute("name")->value();
		float showTime = atof(node->first_node("elapsed")->value());
		int route = atoi(node->first_node("route")->value());
		auto zombie = Zombie::create();
		zombie->setShowTime(showTime);
		zombie->setRoute(route);
		//设置位置
		int x = RANDOM(1000,1300);
		int y = RANDOM(100,500);
		zombie->setPosition(x,y);
		zombie->runIdleAction();
		//添加到场景
		this->addChild(zombie,route);
		m_notShowZombies.push_back(zombie);
	}
	return true;
}
void ZombieLayer::update(float dt)
{
	//每次都是当一个僵尸出场后，才计算后面的僵尸
	for(auto iter = m_notShowZombies.begin();iter != m_notShowZombies.end();)
	{
		auto zombie = *iter;
		auto elapsed = dt + zombie->getElapsed();
		zombie->setElapsed(elapsed);
		//使僵尸出场
		if(elapsed >= zombie->getShowTime())
		{
			auto route = zombie->getRoute();
			zombie->setPosition(950,30 + route*100);
			zombie->runWalkAction();

			m_zombies[route]->push_back(zombie);
			iter = m_notShowZombies.erase(iter);
			//continue;
		}
		break;//iter++;
	}
	//对出场的僵尸状态更新
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<m_zombies[i]->size();j++)
		{
			auto zombie = m_zombies[i]->at(j);
			auto hp = zombie->getHitPoint();
			if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Walk
				|| zombie->getZombieStatus() == ZombieStatus::kZombieStatus_DeadWalk)
				zombie->setPositionX(zombie->getPositionX() - zombie->getSpeed());
			//半死
			if(hp <= 0 && hp > -100)
			{
				if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Walk)
					zombie->runLostHeadAction();
				else if(zombie->getZombieStatus() == ZombieStatus::kZombieStatus_Attack)
					zombie->runLostAttackAction();
				zombie->setHitPoint(--hp);
			}
			//完全死亡
			if(hp <= -100 && hp>-200 && zombie->getZombieStatus() != ZombieStatus::kZombieStatus_EntireDead)
			{
				auto anim = zombie->onEntireDeadAction();
				auto delay = DelayTime::create(anim->getDuration());
				CallFunc*dead = CallFunc::create([&,zombie,i](){
					m_zombies[i]->eraseObject(zombie);
					this->removeChild(zombie);
				});
				//改变状态
				zombie->changeState(ZombieStatus::kZombieStatus_EntireDead);
				zombie->getSprite()->stopAllActions();
				zombie->getSprite()->runAction(anim);
				zombie->runAction(Sequence::createWithTwoActions(delay,dead));
			}
			//定义为炸弹死亡
			else if(zombie->getHitPoint() <= -200)
			{
				m_zombies[i]->eraseObject(zombie);
				this->removeChild(zombie);
			}
		}
	}
}