#ifndef __Bird_H__
#define __Bird_H__
#include "Entity.h"

class Bird:public Entity
{
	SDL_BOOL_SYNTHESIZE(m_bFlying,Flying);//��ǰС���Ƿ����ڷ���
private:
	int m_id;//������ǰ������С��Ŀǰ������ͼ��ͬ
	float m_elapsed;//С���½���ʱ��
	bool m_bDead;//С���Ƿ�����
public:
	Bird();
	~Bird();
	static Bird*create(int id);
	bool init(int id);
	void fly();//�������
	void down(float dt);//С���½�
	void dead();//С������
};
#endif