#ifndef __SDL_FishingJoy_H__
#define __SDL_FishingJoy_H__
#include<string>

#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class Cannon;

class FishingJoyData:public Object
{
	//SDL_SYNTHESIZE(int,m_nGold,Gold);//���
	SDL_SYNTHESIZE(float,m_energy,Energy);//��ǰ�����۵�ֵ
	SDL_SYNTHESIZE(int,m_nLevel,Level);//��ǰ�ȼ�
	SDL_SYNTHESIZE(int,m_nExp,Exp);//��ǰ����ֵ
	SDL_SYNTHESIZE(string,m_selectedBullet,SelectedBullet);//���õ�ǰѡ�е��ӵ�����
	SDL_SYNTHESIZE(int,m_nSterengthenBullet,SterengthenBullet);//��ǿ������
	SDL_SYNTHESIZE(int,m_nFogBullet,FogBullet);//�����ӵ�
	SDL_SYNTHESIZE(int,m_nPearlBullet,PearlBullet);//���鵯
	SDL_SYNTHESIZE(int,m_nHalfEnergyNum,HalfEnergyNum);//half energy
	SDL_SYNTHESIZE(int,m_nTollgateIndex,TollgateIndex);//��ǰ�Ĺؿ�

	SDL_BOOL_SYNTHESIZE(m_isBeginner,Beginner);//�Ƿ��ǵ�һ����
	SDL_BOOL_SYNTHESIZE(m_bChunk,PlayingChunk);//��Ч
	SDL_BOOL_SYNTHESIZE(m_bMusic,PlayingMusic);//����
private:
	static FishingJoyData*m_pInstance;
private:
	int m_nGold;
private:
	FishingJoyData();
	~FishingJoyData();
public:
	static FishingJoyData*getInstance();
	static void purge();

	bool init();
	//�������浽xml�ļ�
	void flush();
	//����
	void reset();

	//��ȡ��ǰ�ȼ����ܾ���ֵ
	int getExpOfCurLevel()const;
	//���ݵ�ǰ��ǹ��ȡ��Ӧ����Ľ����
	int getGoldByCannon(Cannon*pCannon);
	//��ȡ��ǰѡ�е��ӵ�������
	unsigned int getBulletNumByName(const string&bulletName);
	//��ȡ��ǰ��ѡ���ӵ�����Ŀ
	unsigned int getSelectedBulletNum();
	//����ѡ�е��ӵ�����Ŀ
	void alterSelectedBulletNum(int num);

	int getGold()const;
	void setGold(int gold);
};
#endif