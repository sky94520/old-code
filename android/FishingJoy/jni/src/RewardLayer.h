#ifndef __RewardLayer_H__
#define __RewardLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "StaticData.h"

using namespace SDL;

class RewardLayerDelegate
{
public:
	virtual ~RewardLayerDelegate(){}
	virtual void gameResume()=0;

	virtual void addItem(const string&itemName,const Point&bornPos,int number)=0;
	virtual void addChestLightAnim(const string&name,const Point&pos)=0;
	virtual void removeChestLightAnim(const string&name)=0;
};

class RewardLayer:public Layer
{
private:
	Menu*m_pChestMenu;
	int m_nChestChgNum;
	RewardLayerDelegate*m_pDelegate;
	//�Ƿ��Ѿ����˱��䣬Ϊ�˱�֤����ֻ�ܴ�һ��
	bool m_bOpenedChest;
public:
	RewardLayer();
	~RewardLayer();
	CREATE_FUNC(RewardLayer);
	bool init();

	void showChest();
	//��ǰ�Ƿ���Ե�����䣬Ϊ�˱����ظ�������õı���
	bool isClickChest();
	void setDelegate(RewardLayerDelegate*pDelegate);
private:
	void chestRewardBtnCallback(Object*sender);
	void goBtnCallback(Object*sender);
	void moveChestSchedule(float);

	ChestReward&getRandomChestReward();
	Node*getNodeByChestReward(const ChestReward&reward);
};
#endif