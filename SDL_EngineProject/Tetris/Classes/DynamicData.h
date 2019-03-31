#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nLevel,Level);//��ǰ����
	SDL_SYNTHESIZE(int,m_nScore,Score);//��ǰ����
private:
	static DynamicData*m_pInstance;
	int m_nLevelUpLine;//��ʣ����������
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance()
	{
		if(m_pInstance == nullptr)
			m_pInstance = new DynamicData();
		return m_pInstance;
	}
	void purge();
	void reset();
	void alterScore(int brickLines);//���ӷ���,��������Ϣ��ͬʱ�ж��Ƿ�Ӧ�������͸ı��ٶ�
	float getIntervalByLevel()const;//ͨ����ǰ�ȼ����interval
};
#endif