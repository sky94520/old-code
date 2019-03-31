#ifndef __Plant_H__
#define __Plant_H__
#include<string>
#include "Entity.h"

typedef enum PlantType
{
	kPlantType_Shooter,//�㶹���� �������� ������
	kPlantType_Producer, //���տ�
	kPlantType_Wall,     //����ǽ ����ǽ ����ǽ
	kPlantType_Bomb     //ը�� ��ӣ��ը��
}PlantType;
class Plant:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//��Ѫ��
	SDL_SYNTHESIZE(int,m_nCurHP,CurHP);//��ǰѪ��
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//����ֵ
	SDL_SYNTHESIZE(float,m_interval,Interval);//���ܼ��ʱ��
	SDL_SYNTHESIZE(int,m_nLine,Line);//��ֲ����������
public:
	Plant();
	~Plant();
	void hurt(int damage);//����ʱ����
	void dead();//����ʱ����
	bool isDead()const;//�Ƿ�����

	//�������������Ƕ�m_pSprite����
	virtual FiniteTimeAction*onNormalAction()=0;//��������
	virtual FiniteTimeAction*onSkillAction()=0;//���ܶ���
	virtual void onHurt()=0;
	virtual void onDead()=0;
	virtual void initInterval()=0;
	virtual PlantType getPlantType()const=0;
	virtual std::string getName()const=0;
};
#endif