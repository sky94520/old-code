#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "cocos2d.h"
#include "SystemHeader.h"
USING_NS_CC;

class DynamicData:public Ref
{
	MY_SYNTHESIZE_BOOL(m_soundVolume,SounVolume);//音效 [0,1]
	MY_SYNTHESIZE_BOOL(m_musicVolume,MusicVolume);//音乐 [0,1]
	CC_SYNTHESIZE(int,m_nScore,Score);//分数
	CC_SYNTHESIZE(float,m_bulletDuration,BulletDuration);//双发子弹持续时间
	CC_SYNTHESIZE(int,m_nPlayerLives,PlayerLives);//主角的生命
private:
	static DynamicData*m_pInstance;
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	bool init();
	void purge();

	void alertScore(int nScore);
	//立即保存到xml文件
	void save();
};
#endif