#ifndef __Mutou_H__
#define __Mutou_H__
#include "cocos2d.h"
#include "State.h"
class StateManager;

USING_NS_CC;
class Mutou:public Node
{
private:
	StateManager*m_pStateMgr;
public:
	Mutou();
	~Mutou();
	CREATE_FUNC(Mutou);
	bool init();

	bool isTired()const;//ÿ���ʶ�˵��
	bool isWantToWriteArticle()const;//�Ƿ���д�̳�
	void writeCode();//д����
	void writeArticle();//д�̳�
	void rest();//��Ϣ

	StateManager*getFSM()const;
};
//״̬��
class StateWriteCode:public State
{
public:
	virtual void execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev);
};
class StateWriteArticle:public State
{
public:
	virtual void execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev);
};
class StateRest:public State
{
public:
	virtual void execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev);
};

#endif