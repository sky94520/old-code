#ifndef __SDL_FishingJoy_H__
#define __SDL_FishingJoy_H__
#include "SDL_Engine/SDL_Engine.h"
#include "sundry.h"
using namespace SDL;

class FishingJoyData:public Object
{
	SDL_SYNTHESIZE(int,m_nGold,Gold);//金币
	int m_nBulletCount_1;//第一个类型子弹数目 用作测试使用
	int m_nBulletCount_2;
	SDL_SYNTHESIZE(float,m_soundVolume,SounVolume);//音效 [0,1]
	SDL_SYNTHESIZE(float,m_musicVolume,MusicVolume);//音乐 [0,1]
private:
	static FishingJoyData*m_pInstance;
	FishingJoyData();
	~FishingJoyData();
public:
	static FishingJoyData*getInstance();
	bool init();
	void purge();
	//立即保存到xml文件
	void save();
	//修改金币文件
	void alterGold(Value value,bool bAdd);
	//获取相应子弹的数目
	int getBulletCountByType(BulletType type);
	void setBulletCountByType(BulletType type,int count);
};
#endif