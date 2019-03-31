#include "Mutou.h"
#include "StateManager.h"
Mutou::Mutou()
	:m_pStateMgr(nullptr)
{
}
Mutou::~Mutou()
{
}
bool Mutou::init()
{
	m_pStateMgr = StateManager::create(this);
	m_pStateMgr->retain();

	return true;
}
bool Mutou::isTired()const
{
	return true;
}
bool Mutou::isWantToWriteArticle()const
{
	float ran = CCRANDOM_0_1();
	if(ran < 0.1f)
		return true;
	return false;
}
void Mutou::writeCode()
{
	log("xiao niu is writing codes!");
}
void Mutou::writeArticle()
{
	log("xiao niu is writing article");
}
void Mutou::rest()
{
	log("xiao niu is resting");
}
StateManager*Mutou::getFSM()const
{
	return m_pStateMgr;
}
//---------------------StateWriteCode-------------------------------
void StateWriteCode::execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev)
{
	switch(type)
	{
	case en_Msg_WantToRest:
		pMutou->rest();
		pMutou->getFSM()->changeState(new StateRest());
		break;
	}
}
void StateWriteArticle::execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev)
{
	switch(type)
	{
	case en_Msg_WantToRest:
		pMutou->rest();
		pMutou->getFSM()->changeState(new StateRest());
		break;
	}
}
void StateRest::execute(Mutou*pMutou,EnumMsgType type,cocos2d::EventCustom*ev)
{
	switch(type)
	{
	case en_Msg_WantToWriteCode:
		pMutou->writeCode();
		pMutou->getFSM()->changeState(new StateWriteCode());
		break;
	case en_Msg_WantToWriteArticle:
		pMutou->writeArticle();
		pMutou->getFSM()->changeState(new StateWriteArticle());
		break;
	}
}