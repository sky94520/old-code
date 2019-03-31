#ifndef __FishLayer_H__
#define __FishLayer_H__
#include<map>
#include<string>
#include<vector>
#include<numeric>
#include "SDL_Engine/SDL_Engine.h"
#include "Fish.h"
#include "StaticData.h"
#include "StarFish.h"

using namespace std;
using namespace SDL;

class Fish;

class FishLayerDelegate
{
public:
	virtual ~FishLayerDelegate(){}
	virtual void showWaveAction()=0;
	virtual vector<int>& getShownFishIdVec()=0;
	virtual int getRandomFishTideID()const=0;
	virtual vector<float>& getStartFishStartTimeVec()=0;
	virtual void fishCaughtCallback(Fish*fish)=0;
	virtual void showGroupComeMoving() = 0;
};

class FishLayer:public Layer,public StarFishDelegate
{
public:
	enum class State
	{
		GroupCome,
		Group,
		Normal,
	};
private:
	std::vector<Fish*> m_fishes;
	map<int,int> m_weightOfFishes;//���Ȩ��
	State m_state;
	//�����������ʱ��
	float m_makeFishElapsed;
	//�㳱���ж������
	float m_groupComeElapsed;
	//���ǵĳ���ʱ��
	float m_starFishElapsed;
	//���ǵĸ���
	int m_starFishNum;
	//�㳱ʣ�����
	int m_fishTideCount;
	//�㳱��·������
	int m_fishTidePathID;
	//�㳱�����Ϣ
	vector<FishBornConfig> m_fishTideConfig;
	//��ǰ�㳱����λ��
	Point m_fishTidePos;

	FishLayerDelegate*m_pDelegate;
public:
	FishLayer();
	~FishLayer();
	CREATE_FUNC(FishLayer);
	bool init();
public:
	virtual void update(float dt);

	std::vector<Fish*> getFishes()const;
	void setDelegate(FishLayerDelegate*pDelegate);

	void reset();
	State getCurState()const;
private:
	void updateOfState(float dt);

	void groupCome();
	void duringGroupState();
	void duringNormalState(float dt);
	//���ɺ���
	void updateStarFishes(float dt);
	//���ݵ�ǰ��Ȩ������Ȩ�� ��ȡ��ǰȨ������Ӧ��id
	int getIDForWeight(int weight,const map<int,int>&weights);
	//��ȡ����Ϊ��id���������
	int getCountOfShownByID(int id)const;

	Point getRandonOffsetPos();
	//��ȡ�����·��id
	int getRandomPathID(int fishID)const;
private:
	virtual void starFishDeadCallback();
};
#endif