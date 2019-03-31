#ifndef __StarFish_H__
#define __StarFish_H__

#include<vector>
#include "Fish.h"
using namespace std;
class StarFishDelegate
{
public:
	virtual ~StarFishDelegate(){}
	virtual void starFishDeadCallback()=0;
};

class StarFish:public Fish
{
private:
	float m_elpased;
	float m_deadTime;//����ʱ��
	vector<float> m_durations;
	int m_index;
	bool m_dirty;

	StarFishDelegate*m_pDelegate;
public:
	StarFish();
	~StarFish();
	/*startTime 0~1*/
	static StarFish*create(float startTime);
	bool init(float startTime);
	void dead();//������ʱ����
	void setDelegate(StarFishDelegate*pDelegate);
public:
	virtual void update(float dt);
	virtual void reset();
	virtual void clear();

	virtual void caught();//����׽�ص�����
	virtual void collided(TriggingType type);//��ײ�ص�����
};
#endif