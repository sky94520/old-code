#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
class DynamicData:public Object
{
	//������ʹ��
	SDL_SYNTHESIZE(float,m_soundVolume,SounVolume);//��Ч [0,1]
	SDL_SYNTHESIZE(float,m_musicVolume,MusicVolume);//���� [0,1]
	SDL_SYNTHESIZE(int,m_nSunNumber,SunNumber);//̫������
private:
	static DynamicData*m_pInstance;
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	bool init();
	void purge();
	void alertSunNum(int num);
};
#endif