#ifndef __StateManager_H__
#define __StateManager_H__
#include "cocos2d.h"
#include "State.h"
USING_NS_CC;
class Mutou;

class StateManager:public Node
{
private:
	Mutou*m_pMutou;
	State*m_pCurState;
public:
	StateManager();
	~StateManager();
	static StateManager*create(Mutou*pMutou);
	bool init(Mutou*pMutou);

	void changeState(State*state);
private:
	void onRecvWantToRest(cocos2d::EventCustom*ev);
	void onRecvWantToWriteArticle(cocos2d::EventCustom*ev);
	void onRecvWantToWriteCode(cocos2d::EventCustom*ev);
};
#endif