#ifndef __Fish_H__
#define __Fish_H__
#include<string>
#include "Entity.h"

typedef enum FishStatus
{
	FishStatus_None,//��״̬
	FishStatus_Walk,//�ζ�״̬
	FishStatus_Scared,//�ܵ�����״̬
	FishStatus_Caught,//����״̬
}FishStatus;

class Fish:public Entity
{
	SDL_SYNTHESIZE(int,m_nID,ID);//id
	SDL_SYNTHESIZE(std::string,m_name,Name);//����
	SDL_SYNTHESIZE(std::string,m_desc,Description);//����
	SDL_SYNTHESIZE(float,m_speed,Speed);//�ٶ�
	SDL_SYNTHESIZE(int,m_nWeightMean,WeightMean);//Ȩ��
	SDL_SYNTHESIZE(int,m_nGold,Gold);//���
	SDL_SYNTHESIZE(Rect,m_colliableRect,ColliableRect);//��ײ���
	SDL_SYNTHESIZE(Rect,m_scaredRect,ScaredRect);//�������
private:
	FishStatus m_status;
	Point m_endPos;
	int m_walkFrame;//����֡
	int m_deadFrame;//����֡

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
	//��ȡ��ľ��䷶Χ ��������ϵ
	/*Rect getScaredRect()const;
	//��ȡ��ײ���
	Rect getColliableRect()const;*/
private:
	bool changeStatus(FishStatus status);//�л���ĵ�ǰ״̬
	//�ַ���ת��ΪRect
	Rect getRectFromString(const char*text);
};
#endif