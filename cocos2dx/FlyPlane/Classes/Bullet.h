#ifndef __Bullet_H__
#define __Bullet_H__
/*�ӵ���*/
#include "Entity.h"

class Bullet : public Entity
{
public:
	CREATE_FUNC(Bullet);
	virtual bool init();

	Bullet();
	~Bullet();

public:
	void show();
	void hide();
	//���ݸ�����������������Ϊ���
	void reset(Point point);
	int getSpeed();
	bool isAlive();
	
private:
	int m_speed;
	bool m_isAlive;

};
#endif