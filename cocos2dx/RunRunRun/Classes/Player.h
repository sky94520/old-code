#ifndef __Player_H__
#define __Player_H__

#include "Entity.h"

class Player : public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

	void run();

	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap*map);
private:
	void setViewPointByPlayer();
	//����������ת��Ϊ��ͼ��������
	Point tileCoordForPosition(Point);

	TMXTiledMap*m_map;
	//�����ײ�ĵ�ͼ��
	TMXLayer*meta;
	//��������Ƿ���ײ���ϰ���ڷ�����
	bool isJumping;
};
#endif