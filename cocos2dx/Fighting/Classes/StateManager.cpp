#include "StateManager.h"
#include "Mutou.h"

StateManager::StateManager()
	:m_pMutou(nullptr),m_pCurState(nullptr)
{
}
StateManager::~StateManager()
{
	auto NOTIFY = NotificationCenter::getInstance();
	NOTIFY->removeObserver(this,StringUtils::toString(en_Msg_WantToRest));
	NOTIFY->removeObserver(this,StringUtils::toString(en_Msg_WantToWriteArticle));
	NOTIFY->removeObserver(this,StringUtils::toString(en_Msg_WantToWriteCode));

}
StateManager*StateManager::create(Mutou*pMutou)
{
	auto mgr = new StateManager();
	if(mgr && mgr->init(pMutou))
		mgr->autorelease();
	else
		CC_SAFE_DELETE(mgr);
	return mgr;
}
bool StateManager::init(Mutou*pMutou)
{
	m_pMutou = pMutou;
	//×¢²á¹Û²ìÕß
	/*auto NOTIFY = NotificationCenter::getInstance();
	NOTIFY->addObserver(this,callfuncO_selector(StateManager::onRecvWantToRest),
		StringUtils::toString(en_Msg_WantToRest),NULL);
	NOTIFY->addObserver(this,callfuncO_selector(StateManager::onRecvWantToWriteArticle),
		StringUtils::toString(en_Msg_WantToWriteArticle),NULL);
	NOTIFY->addObserver(this,callfuncO_selector(StateManager::onRecvWantToWriteCode),
		StringUtils::toString(en_Msg_WantToWriteCode),NULL);*/

	auto listener1 = EventListenerCustom::create(StringUtils::toString(en_Msg_WantToRest),
		CC_CALLBACK_1(StateManager::onRecvWantToRest,this));
	auto listener2 = EventListenerCustom::create(StringUtils::toString(en_Msg_WantToWriteArticle),
		CC_CALLBACK_1(StateManager::onRecvWantToWriteArticle,this));
	auto listener3 = EventListenerCustom::create(StringUtils::toString(en_Msg_WantToWriteCode),
		CC_CALLBACK_1(StateManager::onRecvWantToWriteCode,this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3,this);

	return true;
}
void StateManager::changeState(State*state)
{
	CC_SAFE_DELETE(m_pCurState);
	m_pCurState = state;
}
void StateManager::onRecvWantToRest(cocos2d::EventCustom*ev)
{
	this->m_pCurState->execute(m_pMutou,en_Msg_WantToRest,ev);
}
void StateManager::onRecvWantToWriteArticle(cocos2d::EventCustom*ev)
{
	this->m_pCurState->execute(m_pMutou,en_Msg_WantToWriteArticle,ev);
}
void StateManager::onRecvWantToWriteCode(cocos2d::EventCustom*ev)
{
	this->m_pCurState->execute(m_pMutou,en_Msg_WantToWriteCode,ev);
}