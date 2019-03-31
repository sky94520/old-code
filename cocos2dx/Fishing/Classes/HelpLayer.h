#ifndef __HelpLayer_H__
#define __HelpLayer_H__
#include "cocos2d.h"
USING_NS_CC;
/*���㸨������*/
/*
need:
	1.�ܻ�ȡ���ϵ����״̬	
	2.�ܻ������״̬
*/
/*���մ�����Ϣ����Ҫʱ���̵��������������¼�ʱ����������HelpfulComponent
������ײ����ִ����Ӧ���������̲��¼���Ĭ������ǲ�չ���ģ���ÿ�β��㶼��ʹ�����չ��
��������㣬����ʾ��Ӧ�Ĺ�������
*/
class Fish;
class Fork;
class HelpfulFish;

class HelpLayerDelegate
{
public:
	virtual ~HelpLayerDelegate(){}
	virtual Vector<Fish*>* getShowingFishes()= 0;
	virtual Fork*getShowingFork() = 0;
};
class HelpLayer:public Layer
{
private:
	HelpLayerDelegate*m_pDelegate;
	int m_nLength;
public:
	HelpLayer();
	~HelpLayer();
	CREATE_FUNC(HelpLayer);
	bool init();
	void setDelegate(HelpLayerDelegate*m_pDelegate);
	/*����,��onDraw�е���*/
	void debugDraw();
	//��С������ʾ���
	void showHelpfulFork(const Point&pos);

	virtual void update(float dt);
private:
	HelpfulFish*getHelpfulFishByTag(int tag);
};
#endif