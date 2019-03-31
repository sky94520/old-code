#ifndef __SDL_FishingJoy_H__
#define __SDL_FishingJoy_H__
#include "SDL_Engine/SDL_Engine.h"
#include "sundry.h"
using namespace SDL;

class FishingJoyData:public Object
{
	SDL_SYNTHESIZE(int,m_nGold,Gold);//���
	int m_nBulletCount_1;//��һ�������ӵ���Ŀ ��������ʹ��
	int m_nBulletCount_2;
	SDL_SYNTHESIZE(float,m_soundVolume,SounVolume);//��Ч [0,1]
	SDL_SYNTHESIZE(float,m_musicVolume,MusicVolume);//���� [0,1]
private:
	static FishingJoyData*m_pInstance;
	FishingJoyData();
	~FishingJoyData();
public:
	static FishingJoyData*getInstance();
	bool init();
	void purge();
	//�������浽xml�ļ�
	void save();
	//�޸Ľ���ļ�
	void alterGold(Value value,bool bAdd);
	//��ȡ��Ӧ�ӵ�����Ŀ
	int getBulletCountByType(BulletType type);
	void setBulletCountByType(BulletType type,int count);
};
#endif