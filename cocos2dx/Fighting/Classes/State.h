#ifndef __State_H__
#define __State_H__
#include "cocos2d.h"
USING_NS_CC;

enum EnumMsgType
{
	en_Msg_WantToRest,
	en_Msg_WantToWriteCode,
	en_Msg_WantToWriteArticle
};
class Mutou;
class EventCustom;
class State
{
public:
	~State(){}
	virtual void execute(Mutou*pMutou,EnumMsgType state,cocos2d::EventCustom*ev)=0;
};
#endif