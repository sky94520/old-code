#include "FishLayer.h"
#include "CsvUtil.h"
FishLayer::FishLayer()
	:m_nNotVisibleFishNum(10)
	,m_bReset(false)
{
}
FishLayer::~FishLayer()
{
	CsvUtil::getInstance()->purge();
}
bool FishLayer::init()
{
	CsvUtil::getInstance()->loadFile("Resources/fish.csv");

	std::vector<int> createdFishID;
	int id = RANDOM(1,15);
	createdFishID.push_back(id);
	for(int i=0;i<10;i++)
	{
		int line = CsvUtil::getInstance()->findLineByValue(Value(id),0,"Resources/fish.csv");
		int maxNum = CsvUtil::getInstance()->getValue(line,7,"Resources/fish.csv").asInt();
		for(int j=0;j<maxNum;j++)
		{
			Fish*fish = Fish::create(id);
			fish->reset();
			m_fishes.push_back(fish);
			this->addChild(fish);
		}
		bool bRet;
		do{
			bRet = false;
			id = RANDOM(1,15);
			for(int k = 0;k<createdFishID.size();k++)
				if(createdFishID.at(k) == id)
				{
					bRet = true;
					break;
				}
		}while(bRet);
		createdFishID.push_back(id);
	}
	//reset();
	return true;
}
void FishLayer::update(float dt)
{
	for(int i=0;i<m_fishes.size();i++)
	{
		auto fish = m_fishes.at(i);
		fish->update(dt);
	}
}
std::vector<Fish*> FishLayer::getFishes()const
{
	return m_fishes;
}