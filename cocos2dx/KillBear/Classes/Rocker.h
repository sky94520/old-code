#ifndef __Rocker_H__
#define __Rocker_H__
#include<string>
#include "cocos2d.h"
class Hero;
using namespace cocos2d;

class Rocker:public Node
{
private:
	//ҡ����ҡ�˱���
	Sprite*m_pRocker;
	Sprite*m_pRockerBG;
	//���� 
	Point m_cDirection;
	//�Ƿ�����
	bool m_bIsActive;
	//�¼�������
	EventListenerTouchOneByOne*m_pTouchListener;
	//�Ƿ���ƶ�
	bool m_bCanMove;
public:
	Rocker();
	CREATE_FUNC(Rocker);
	static Rocker*createRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position);
	virtual bool init();
	bool initRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position);
	//��ʼ/���� ҡ��
	void start();
	void stop();
	//���ƫ����
	Point getDirection();
	//
	virtual bool onTouchBegan(Touch*touch,Event*e);
	virtual void onTouchMoved(Touch*touch,Event*e);
	virtual void onTouchEnded(Touch*touch,Event*e);
};
#endif