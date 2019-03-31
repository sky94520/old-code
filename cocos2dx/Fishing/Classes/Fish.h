#ifndef __Fish_H__
#define __Fish_H__
#include<string>
#include "Entity.h"
#include "Box2D/Box2D.h"

typedef enum FishStatus
{
	FishStatus_None,//��״̬
	FishStatus_Walk,//�ζ�״̬
	FishStatus_Scared,//�ܵ�����״̬
	FishStatus_Caught,//����״̬
}FishStatus;

class Fish:public Entity
{
	CC_SYNTHESIZE(int,m_nID,ID);//id
	CC_SYNTHESIZE(std::string,m_name,FishName);//����
	CC_SYNTHESIZE(std::string,m_desc,Description);//����
	CC_SYNTHESIZE(float,m_speed,Speed);//�ٶ�
	CC_SYNTHESIZE(int,m_nWeightMean,WeightMean);//Ȩ��
	CC_SYNTHESIZE(int,m_nGold,Gold);//���
	CC_SYNTHESIZE(Rect,m_colliableRect,ColliableRect);//��ײ���
	CC_SYNTHESIZE(Rect,m_scaredRect,ScaredRect);//�������
	CC_SYNTHESIZE(float,m_elapsed,Elapsed);//ʲôʱ���ϳ�

	CC_SYNTHESIZE(b2Body*,m_pScaredBody,ScaredBody);//���Ÿ���
	CC_SYNTHESIZE(b2Body*,m_pColliableBody,ColliableBody);//��ײ����
	
	CC_SYNTHESIZE(int,m_nRunningID,RunningID);//����Ψһ��ʶ��
private:
	FishStatus m_status;
	Point m_endPos;
	int m_walkFrame;//����֡
	int m_deadFrame;//����֡
	Scheduler*m_pScheduler;
	ActionManager*m_pActionManager;

public:
	Fish();
	~Fish();
	CREATE_FUNC(Fish);
	static Fish*create(int id);

	bool init();
	bool init(int id);
	//�����ζ�����
	void runNormalAnimation();
	//�ܵ����Ŷ���
	void runScaredAnimation();
	//����׽����
	FiniteTimeAction*runCaughtAnimation();

	virtual FiniteTimeAction*onNormalAnimation();
	virtual FiniteTimeAction*onScaredAnimation();
	virtual FiniteTimeAction*onCaughtAnimation();
	//����
	void reset();
	//�㱻��׽
	void catched();
	FishStatus getStatus()const
	{
		return m_status;
	}
private:
	bool changeStatus(FishStatus status);//�л���ĵ�ǰ״̬
	//�ַ���ת��ΪRect
	Rect getRectFromString(const char*text);
};
#endif