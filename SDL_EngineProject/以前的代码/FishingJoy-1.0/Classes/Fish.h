#ifndef __Fish_H__
#define __Fish_H__
#include "Entity.h"
class Fish:public Entity
{
	SDL_SYNTHESIZE(int,m_nScore,Score);//������ķ���
private:
	bool m_bAlive;//������Ļ��Χ�򱻲�׽ʱΪfalse
	float m_elpased;//�ھ��� n������
	
	float m_fSuccessRate;//�������Ļ����ɹ���
	unsigned int m_nID;
	unsigned int m_nRunFrame;
	unsigned int m_nDeadFrame;
	unsigned int m_nRareRate;//ϡ���� ����ʾһ����������ܴ���������
public:
	Fish();
	~Fish();
	CREATE_FUNC(Fish);
	static Fish*create(int id);
	bool init();
	bool init(int id);
public:
	//���ӿ�������
	void reset();
	void show(float dt);//չʾ
	void catched();//����׽�����
public:
	virtual void update(float dt);
	bool isAlive()const;
	float getSuccessRate()const;
	unsigned int getRareRate()const;
	int getID()const;
private:
	ActionInterval*lineRoute(const Point&from,const Point&to,float duration,bool direction);
};
#endif