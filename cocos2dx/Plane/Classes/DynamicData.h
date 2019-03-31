#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "cocos2d.h"
#include "SystemHeader.h"
USING_NS_CC;

class DynamicData:public Ref
{
	MY_SYNTHESIZE_BOOL(m_soundVolume,SounVolume);//��Ч [0,1]
	MY_SYNTHESIZE_BOOL(m_musicVolume,MusicVolume);//���� [0,1]
	CC_SYNTHESIZE(int,m_nScore,Score);//����
	CC_SYNTHESIZE(float,m_bulletDuration,BulletDuration);//˫���ӵ�����ʱ��
	CC_SYNTHESIZE(int,m_nPlayerLives,PlayerLives);//���ǵ�����
private:
	static DynamicData*m_pInstance;
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	bool init();
	void purge();

	void alertScore(int nScore);
	//�������浽xml�ļ�
	void save();
};
#endif