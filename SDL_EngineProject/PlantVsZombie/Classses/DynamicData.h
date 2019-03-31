#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<vector>
#include<string>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;
class DynamicData:public Object
{
	//������ʹ��
	SDL_SYNTHESIZE(float,m_soundVolume,SounVolume);//��Ч [0,1]
	SDL_SYNTHESIZE(float,m_musicVolume,MusicVolume);//���� [0,1]

	SDL_SYNTHESIZE(int,m_nSunNumber,SunNumber);//̫������
	SDL_SYNTHESIZE(unsigned int,m_nCardVesselNum,CardVesselNum);//���۸���
private:
	static DynamicData*m_pInstance;
	vector<string> m_plants;//ӵ�е�ֲ����������
	vector<string> m_zombieCards;//ӵ�еĽ�ʬ��Ƭ
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	bool init();
	void purge();
	//��ȡӵ�е�ֲ������
	vector<string>& getNameOfPlantCards();
	//��ȡӵ�еĽ�ʬ��Ƭ����
	vector<string>& getNameOfZombieCards();
};
#endif