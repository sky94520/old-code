#include "PlantLayer.h"
#include "Plant.h"
#include "Zombie.h"
#include "PotatoMine.h"
PlantLayer::PlantLayer()
	:m_pDelegate(nullptr)
{
}
PlantLayer::~PlantLayer()
{
}
bool PlantLayer::init()
{
	return true;
}
void PlantLayer::update(float dt)
{
	for(auto iter = m_plants.begin();iter != m_plants.end();)
	{
		auto plant = *iter;
		//����ֲ��״̬
		auto elapsed = dt + plant->getElapsed();
		//���＼���ͷ�ʱ��
		if(elapsed >= plant->getInterval())
		{
			elapsed = 0.f;
			plant->initInterval();
			//�ͷ���Ӧ�ļ���
			switch(plant->getPlantType())
			{
			case PlantType::kPlantType_Shooter://����
				lineShootTo(plant);
				break;
			case PlantType::kPlantType_Producer://������
				//���ܶ���
				{
					Sequence*sequence = Sequence::createWithTwoActions(plant->onSkillAction(),CallFunc::create([&,this,plant](){
					this->sunshine(plant);
					}));
					plant->getSprite()->runAction(sequence);
				}
				break;
			case PlantType::kPlantType_Bomb://ը��
				bomb(plant);
				break;
			}
		}
		plant->setElapsed(elapsed);
		++iter;
	}
}
void PlantLayer::bindPlant(Plant*plant)
{
	this->addChild(plant);
	m_plants.push_back(plant);
}
void PlantLayer::deletePlant(Plant*plant)
{
	m_plants.eraseObject(plant);
	plant->removeFromParent();
}
void PlantLayer::setDelegate(PlantLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void PlantLayer::lineShootTo(Plant*plant)
{
	//����ֲ���yֵ��ȡ��Ӧ������
	int line = plant->getLine();
	//��ȡ�����ڳ��ֵ����н�ʬ
	Vector<Zombie*>* zombies = m_pDelegate->getZombies(line);
	//zombies[line].empty() Ϊʲô��Ϸ�
	if(zombies->empty())
		return;
	//shoot
	if(plant->getName() == "Peashooter")
	{
		Size s = Director::getInstance()->getVisibleSize();
		auto endPos = Point(s.width,0);
		auto startPos = plant->getPosition() + Point(plant->getContentSize().width,0);
		m_pDelegate->shootTo(startPos,endPos,"ProjectilePea",BulletRoute::kBulletRoute_line);
	}
}
void PlantLayer::sunshine(Plant*plant)
{
	if(plant->getName() == "SunFlower")
	{
		m_pDelegate->produceSunshine(plant->getPosition(),SunshineType::kSunshineType_25,SunshineRoute::kSunshineRoute_jump);
	}
}
void PlantLayer::bomb(Plant*plant)
{
	if(plant->getName() == "CherryBomb")
	{
		cherryBomb(plant);
	}//������
	else if(plant->getName() == "PotatoMine")
	{
		potatoMine(plant);
	}
}
void PlantLayer::cherryBomb(Plant*plant)
{
	//����ը������
	auto anim = plant->onSkillAction();
	DelayTime*delay = DelayTime::create(anim->getDuration());
	CallFunc*end = CallFunc::create([plant,this](){
		plant->setCurHP(0);
		this->deletePlant(plant);
	});
	plant->getSprite()->stopAllActions();
	plant->getSprite()->runAction(anim);
	plant->runAction(Sequence::createWithTwoActions(delay,end));
	//��ȡ��ײ���  *1.5 ��ʱ��������
	Rect r1 = plant->getBoundingBox();
	r1.size= Size(r1.size.width*1.5f,r1.size.height*1.5f);
	//ѭ��
	for(int i=0;i<5;i++)
	{
		auto zombies = m_pDelegate->getZombies(i);
		for(int j=0;j<zombies->size();j++)
		{
			auto zombie = zombies->at(j);
			Rect r2 = zombie->getSprite()->getSpriteFrameRect();
			r2.origin += zombie->getPosition();
			if(r1.intersectsRect(r2))
			{
				auto deadAnimate = zombie->onDeadBombAction();
				DelayTime*delay = DelayTime::create(deadAnimate->getDuration());
				CallFunc*end = CallFunc::create([zombie](){
					zombie->hurt(1500);
				});
				zombie->runDeadBombAction();
				zombie->runAction(Sequence::create(delay,end,nullptr));
			}
		}
	}
}
void PlantLayer::potatoMine(Plant*plant)
{
	PotatoMine*potatoMine = dynamic_cast<PotatoMine*>(plant);
	//׼������
	if(potatoMine->isReady() == false)
	{
		potatoMine->setReady(true);
		plant->getSprite()->runAction(plant->onNormalAction());
	}//�������Ѿ����� ��׼������
	else
	{
		Rect r1 = plant->getBoundingBox();
		auto zombies = m_pDelegate->getZombies(plant->getLine());
		for(int j=0;j<zombies->size();j++)
		{
			auto zombie = zombies->at(j);
			Rect r2 = zombie->getSprite()->getSpriteFrameRect();
			r2.origin += zombie->getPosition() - Point(10,0);
			if(r1.intersectsRect(r2))
			{
				//�����ױ�ը
				DelayTime*delayTime = DelayTime::create(plant->onSkillAction()->getDuration());
				CallFunc*dead = CallFunc::create([this,plant](){
					plant->setCurHP(0);
					this->deletePlant(plant);
				});
				plant->getSprite()->stopAllActions();
				plant->getSprite()->runAction(plant->onSkillAction());
				plant->runAction(Sequence::create(delayTime,dead,nullptr));
				//��ʬ����
				auto deadAnimate = zombie->onDeadBombAction();
				DelayTime*delay = DelayTime::create(deadAnimate->getDuration());
				CallFunc*end = CallFunc::create([zombie](){
					zombie->hurt(1500);
				});
				zombie->runDeadBombAction();
				zombie->runAction(Sequence::create(delay,end,nullptr));
			}
		}
	}
}