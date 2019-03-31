#ifndef __GoldTimer_H__
#define __GoldTimer_H__
/*��Ҽ�ʱ��*/
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class GoldTimerDelegate
{
public:
	virtual ~GoldTimerDelegate(){}
	virtual void addGold(int number,const Point&pos)=0;
};

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
	GoldTimerDelegate*m_pDelegate;
public:
	GoldTimer();
	~GoldTimer();
	CREATE_FUNC(GoldTimer);
	bool init();
	void setDelegate(GoldTimerDelegate*pDelegate);
	virtual void update(float dt);
};
#endif