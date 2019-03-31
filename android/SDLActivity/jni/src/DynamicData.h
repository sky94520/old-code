#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nScore,Score);//����
	SDL_SYNTHESIZE(int,m_nLife,Life);//���ǵ�����
private:
	DynamicData();
	~DynamicData();
private:
	static DynamicData*m_pInstance;
	int m_nScorePerLife;
public:
	static DynamicData*getInstance()
	{
		if(m_pInstance == nullptr)
			m_pInstance = new DynamicData();
		return m_pInstance;
	}
	void purge();
	//�޸ķ���
	void alterScore(int score);
	//�޸�����
	void alterLife(int life);

	void reset();
};
#endif