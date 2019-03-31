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

	bool isTired()const;//每次问都说累
	bool isWantToWriteArticle()const;//是否想写教程
	void writeCode();//写代码
	void writeArticle();//写教程
	void rest();//休息

	StateManager*getFSM()const;
};
//状态类
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