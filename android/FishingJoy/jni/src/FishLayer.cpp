#include "FishLayer.h"
#include "StaticData.h"
#include "FishingJoyData.h"
#include "B2EntityFactory.h"
#include "RotateAndSpeed.h"

FishLayer::FishLayer()
	:m_pDelegate(nullptr),m_state(State::Normal)
	,m_makeFishElapsed(0.f),m_groupComeElapsed(0.f)
	,m_fishTideCount(0),m_fishTidePathID(0)
	,m_starFishElapsed(0.f),m_starFishNum(0)
{
}

FishLayer::~FishLayer()
{
}

bool FishLayer::init()
{
	m_starFishNum = 5;

	return true;
}

void FishLayer::update(float dt)
{
	for(auto iter = m_fishes.begin();iter != m_fishes.end();)
	{
		auto fish = *iter;
		auto curState = fish->getState();
		//��ǰ�Ѿ�����׽�����ٽ�����ײ
		if(curState == Fish::State::Caught && fish->isActive())
		{
			fish->setActive(false);
		}

		if(fish->isDead())
		{
			//����������Ϣ
			auto uniqueID = StringUtils::toString(fish->getUniqueID());
			_eventDispatcher->dispatchCustomEvent(uniqueID);

			if(curState == Fish::State::Caught)
			{
				m_pDelegate->fishCaughtCallback(fish);
			}
			fish->setActive(false);
			//�Ƴ�
			iter = m_fishes.erase(iter);
			//���������뻺��أ������Ժ�ʹ��
			if(fish->getFishType() == FishType::Fish)
			{
				B2EntityFactory::getInstance()->pushFishToPool(fish);
			}
			else//�Ƴ�,�������������
			{
				fish->removeFromParent();
			}
		}
		else
		{
			fish->update(dt);
			iter++;
		}
	}
	this->updateOfState(dt);
	this->updateStarFishes(dt);
}
std::vector<Fish*> FishLayer::getFishes()const
{
	return m_fishes;
}

void FishLayer::setDelegate(FishLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void FishLayer::reset()
{
	m_weightOfFishes.clear();

	auto vec = m_pDelegate->getShownFishIdVec();
	for(auto id:vec)
	{
		auto weight = STATIC_FISH_WEIGHT(id);

		m_weightOfFishes.insert(make_pair(id,weight));
	}
}

FishLayer::State FishLayer::getCurState()const
{
	return m_state;
}

void FishLayer::updateOfState(float dt)
{
	switch(m_state)
	{
	case State::GroupCome:this->groupCome();break;
	case State::Group:this->duringGroupState();break;
	case State::Normal:
		{
			this->duringNormalState(dt);

			m_groupComeElapsed+= dt;

			auto time = STATIC_DATA_INT("group_come_time");
			//�л�״̬
			if(m_groupComeElapsed >= time )
			{
				m_state = State::GroupCome;
				m_groupComeElapsed = 0.f;
				//�����㳱���� ����
				m_pDelegate->showGroupComeMoving();
			}
		}break;
	}

}

void FishLayer::groupCome()
{
	//����㶼�뿪����ת��״̬
	if (m_fishes.empty())
	{
		m_state = State::Group;
		//�����ȡ�㳱 todo
		int fishTideID = m_pDelegate->getRandomFishTideID();
		auto&fishTideConfig = StaticData::getInstance()->getFishTideByID(fishTideID);
		//��ȡ�㳱����
		m_fishTideCount = fishTideConfig.count;
		//��ȡ�㳱��·��id
		m_fishTidePathID = fishTideConfig.path_id;
		//��ȡ�㳱�������Ϣ
		m_fishTideConfig = fishTideConfig.fishes;
		//�����㳱 ��Ч
		m_pDelegate->showWaveAction();

		return;
	}

	for(auto iter = m_fishes.begin();iter != m_fishes.end();iter++)
	{
		auto fish = *iter;

		fish->collided(TriggingType::GroupCome);
	}
}

void FishLayer::duringGroupState()
{
	//�㳱��һ���Ƿ����
	if(m_fishTideConfig.empty() && m_fishes.empty())
	{
		m_fishTideCount--;
		//�����µ��㳱
		if(m_fishTideCount > 0)
		{
			//todo
			auto&fishTideConfig = StaticData::getInstance()->getFishTideByID(1);
			m_fishTideConfig = fishTideConfig.fishes;

			m_fishTidePos = Point::ZERO;
		}
		else//�㳱����
		{
			m_state = State::Normal;
			return;
		}
	}
	m_fishTidePos.x += 1.f;
	//�Ƿ���
	bool reverse = m_fishTideCount%2 == 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//�鿴�Ƿ�����ǳ�
	for(auto iter = m_fishTideConfig.begin();iter != m_fishTideConfig.end();)
	{
		auto config = *iter;
		//������
		if(m_fishTidePos.x >= config.pos.x)
		{
			//���б���ɾ��
			iter = m_fishTideConfig.erase(iter);
			//������
			Fish*fish = B2EntityFactory::getInstance()->createFishForID(config.fishID);
			//ȷ������λ��
			Point pos = config.pos;
			Size size = fish->getContentSize();

			if(reverse)
				pos.x = visibleSize.width + size.width/2;
			else
				pos.x = -size.width/2;

			//ȷ������
			auto action = StaticData::getInstance()->getActionByPathID(m_fishTidePathID,size,0,0,reverse);
			
			fish->setPosition(pos);
			fish->runAction(action);

			this->addChild(fish);
			m_fishes.push_back(fish);
		}
		else
			iter++;
	}
}

void FishLayer::duringNormalState(float dt)
{
	m_makeFishElapsed += dt;

	if(m_makeFishElapsed < 1.f)
		return ;
	m_makeFishElapsed -= 1.f;

	auto fishMaxNum = STATIC_DATA_INT("fish_max_num");
	//�����������ﵽ����
	if(m_fishes.size() >= fishMaxNum)
		return;

	map<int,int> weightOfFishes;

	//��ȥ����ĳ���Ѿ��ﵽ���޵����id
	for(auto iter = m_weightOfFishes.begin();iter != m_weightOfFishes.end();iter++)
	{
		auto id = iter->first;
		int shownNum = this->getCountOfShownByID(id);
		//��ȡ�������������
		int max = STATIC_FISH_MAX(id);

		if(max > shownNum)
		{
			weightOfFishes.insert(make_pair(iter->first,iter->second));
		}
	}

	//û�п��ϳ�����
	if(weightOfFishes.empty())
		return ;
	//��ȡ�ܼ�Ȩ��
	int sumWeight = 0;
	for(auto iter = weightOfFishes.begin();iter != weightOfFishes.end();iter++)
	{
		sumWeight += iter->second;
	}

	//��ǰ�ܳ������������
	int shownMax = 0;
	//��ȡ��ǰȨ��
	int weight = rand()%sumWeight;

	int id = this->getIDForWeight(weight,weightOfFishes);
	//��ȡ���ϵĸ�id�������Ŀ
	int shownNum = this->getCountOfShownByID(id);

	//��ȡ�������������
	int max = STATIC_FISH_MAX(id);

	shownMax = max - shownNum;
	//��ȡÿ���ܳ��ֵ����ֵ
	int maxPerTime = STATIC_FISH_MAX_PER_TIME(id);
	//���ݵ�ǰ�����ֵ��ÿ���ܳ��ֵ����ֵ��ȡ��С���Ǹ�
	shownMax = std::min(shownMax,maxPerTime);

	//�������id�����ȡһ��·��id
	int pathID = this->getRandomPathID(id);
	//�Ƿ���
	bool reverse = rand()%2 == 1;

	//��ȡ�������Ŀ
	int count = rand()%shownMax + 1;

	Point bornPos = StaticData::getInstance()->getStartPosByPathID(pathID,reverse);

	for(int i = 0;i < count;i++)
	{
		Point offset;
		float randomY = rand()%200 - 100;

		Fish*fish = B2EntityFactory::getInstance()->createFishForID(id);
		Size size = fish->getContentSize();
		//���ÿ�ʼλ��
		if(i != 0)
			offset = this->getRandonOffsetPos();

		if(reverse)
			fish->setPosition(bornPos + offset + Point(size.width/2,size.height/2));
		else
			fish->setPosition(bornPos -offset - Point(size.width/2,size.height/2));

		//����·��id��ȡ����
		RotateAndSpeed* action = StaticData::getInstance()->getActionByPathID(pathID,size,offset.x,randomY,reverse);

		fish->runAction(action);

		this->addChild(fish);
		m_fishes.push_back(fish);
	}
}

void FishLayer::updateStarFishes(float dt)
{
	//ֻ���ں���ȫ��������Ž��е���ʱ
	if(m_starFishNum != 5)
		return;
	auto time = STATIC_DATA_INT("star_fish_interval");
	m_starFishElapsed += dt;
	//������n����������
	if(m_starFishElapsed >= time)
	{
		m_starFishNum = 0;
		m_starFishElapsed -= time;

		auto posFormat = STATIC_DATA_STRING("star_fish_pos_format");
		auto &startTimes = m_pDelegate->getStartFishStartTimeVec();

		for(int i=0;i < 5;i++)
		{
			auto text = StringUtils::format(posFormat.c_str(),i+1);
			//��ȡ����λ��
			Point pos = STATIC_DATA_POINT(text);
			//��ȡ��ʼʱ��
			float startTime = startTimes.at(i);
			//����
			auto fish = B2EntityFactory::getInstance()->createStarFish(startTime);
			fish->setPosition(pos);
			fish->setDelegate(this);

			this->addChild(fish);
			m_fishes.push_back(fish);
		}
	}
}

int FishLayer::getIDForWeight(int weight,const map<int,int>&weights)
{
	int curWeight = 0;

	for(auto iter = weights.begin();iter != weights.end();iter++)
	{
		if(curWeight <= weight && weight <= curWeight + iter->second)
			return iter->first;

		curWeight += iter->second;
	}

	return 0;
}

int FishLayer::getCountOfShownByID(int id)const
{
	int count = 0;

	for(auto iter = m_fishes.begin();iter != m_fishes.end();iter++)
	{
		auto fish = *iter;
		if(id == fish->getID())
			count++;
	}

	return count;
}

Point FishLayer::getRandonOffsetPos()
{
	//todo
	Size size = Size(100,100);

	int x = RANDOM_0_1() * size.width;
	int y = RANDOM_0_1() * size.height;

	return Point(x,y);
}

int FishLayer::getRandomPathID(int fishID)const
{
	const vector<int>* path = StaticData::getInstance()->getTotalPathes(fishID);

	SDL_assert(!path->empty());

	int size = path->size();

	int pathID = rand()%size;

	return path->at(pathID);
}

void FishLayer::starFishDeadCallback()
{
	m_starFishNum++;
	printf("star fish dead\n");
}
