#ifndef __GoldTimer_H__
#define __GoldTimer_H__
/*��Ҽ�ʱ��*/
#include "Entity.h"
class GoldTimer:public Node
{
private:
	//ÿ��Ҫ�����Ľ����Ŀ
	int m_nGold;
	//ÿ��������������ӽ��
	int m_nSecond;
	float m_elpased;//��ǰ����ʱ��
	//��ʾʱ���Label
	LabelAtlas*m_pLabel;
public:
	GoldTimer();
	~GoldTimer();
	CREATE_FUNC(GoldTimer);
	bool init();
	virtual void update(float dt);
};
#endif