#include "Fish.h"
#include "LuaEngine.h"
#include "RotateWithAction.h"

Fish::Fish()
	:m_nID(-1),m_name(""),m_desc(""),
	m_speed(0.f),m_nWeightMean(0),m_nGold(0),
	m_status(FishStatus::FishStatus_None)
	,m_pScheduler(nullptr),m_pActionManager(nullptr)
	,m_elapsed(0.f),m_pScaredBody(nullptr),m_pColliableBody(nullptr)
	,m_nRunningID(-1)
{
	//����Ψһ��ʶ����0��ʼ��������ʶ
	static int runningID = 0;
	m_nRunningID = runningID++;
}
Fish::~Fish()
{
	auto defaultScheduler = Director::getInstance()->getScheduler();
	defaultScheduler->unscheduleUpdate(m_pScheduler);

	m_pScheduler->unscheduleAll();
	CC_SAFE_RELEASE(m_pScheduler);
	CC_SAFE_RELEASE(m_pActionManager);
}
Fish*Fish::create(int id)
{
	auto fish = new Fish();
	if(fish && fish->init(id))
		fish->autorelease();
	else
		CC_SAFE_DELETE(fish);
	return fish;
}
bool Fish::init()
{
	//todo
	bindSprite(Sprite::createWithSpriteFrameName("fish04_00.png"));

	return true;
}
bool Fish::init(int id)
{
	m_nID = id;
	std::string fishName = StringUtils::format("Fish%d",m_nID);

	m_name = LuaEngine::getInstance()->getStringFromTable(fishName.c_str(),"name");
	m_desc = LuaEngine::getInstance()->getStringFromTable(fishName.c_str(),"desc");
	m_speed = LuaEngine::getInstance()->getFloatFromTable(fishName.c_str(),"speed");
	m_nWeightMean = LuaEngine::getInstance()->getIntegerFromTable(fishName.c_str(),"weightMean");
	m_nGold = LuaEngine::getInstance()->getIntegerFromTable(fishName.c_str(),"gold");
	//��ײ����;������
	auto colliableStr = LuaEngine::getInstance()->getStringFromTable(fishName.c_str(),"colliableRect");
	auto scaredStr = LuaEngine::getInstance()->getStringFromTable(fishName.c_str(),"scaredRect");

	m_colliableRect = this->getRectFromString(colliableStr);
	m_scaredRect = this->getRectFromString(scaredStr);
	//�󶨾���
	auto str = StringUtils::format("fish%02d_00.png",m_nID);
	bindSprite(Sprite::createWithSpriteFrameName(str));
	//���ü�ʱ��
	if(m_pScheduler)
	{
		m_pScheduler->setTimeScale(1.f);
	}
	else
	{
		m_pScheduler = new Scheduler();
		auto defaultScheduler = Director::getInstance()->getScheduler();
		defaultScheduler->scheduleUpdate(m_pScheduler,0,false);
		m_pActionManager = new ActionManager();
		m_pScheduler->scheduleUpdate(m_pActionManager,0,false);
		this->setActionManager(m_pActionManager);
	}
	//����Ȩֵ���ó���ʱ��

	return true;
}
void Fish::runNormalAnimation()
{
	if(changeStatus(FishStatus::FishStatus_Walk))
	{
		auto action = onNormalAnimation();
		//ֹͣ����
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(action);
	}
}
void Fish::runScaredAnimation()
{
	if(changeStatus(FishStatus::FishStatus_Scared))
	{
		m_pScheduler->setTimeScale(2.5f);
	}
}
FiniteTimeAction*Fish::runCaughtAnimation()
{
	if(changeStatus(FishStatus::FishStatus_Caught))
	{
		auto action = onCaughtAnimation();
		//ֹͣ����
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(action);
		return action;
	}
	return nullptr;
}
FiniteTimeAction*Fish::onNormalAnimation()
{
	auto str = StringUtils::format("fish%02d_%s.png",m_nID,"%02d");
	//"fish04_%02d.png"
	return Entity::createAnimate(str,0,9,0.1f,-1);
}
FiniteTimeAction*Fish::onScaredAnimation()
{
	log("the fish is scared");
	return nullptr;
}
FiniteTimeAction*Fish::onCaughtAnimation()
{
	auto str = StringUtils::format("fish%02d_%s.png",m_nID,"d%02d");
	log("the fish is caught");
	return Entity::createAnimate(str,0,1,0.1f,2);
}
void Fish::reset()
{
	this->getSprite()->stopAllActions();
	this->stopAllActions();
	m_status = FishStatus::FishStatus_None;
	m_pScheduler->setTimeScale(1.f);
	m_elapsed = 0.f;
}
void Fish::catched()
{
	//������Ѿ�����׽�ˣ�����������
	if(m_status == FishStatus::FishStatus_Caught)
		return;
	m_pScheduler->setTimeScale(1.f);
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//��ȡ��������ʱ��
	auto action = this->runCaughtAnimation();
	
	//�ӳٶ�������С�㲥������������������ʧ
	DelayTime*delay = DelayTime::create(action->getDuration());
	
	CallFunc*end = CallFunc::create([&](){
		this->setVisible(false);
	});
	this->runAction(Sequence::create(delay,end,nullptr));
}
bool Fish::changeStatus(FishStatus status)
{
	if(m_status == status || m_status == FishStatus::FishStatus_Caught)
		return false;
	m_status = status;
	return true;
}
Rect Fish::getRectFromString(const char*text)
{
	int x = 0,y=0,w=0,h=0;
	sscanf(text,"%d,%d,%d,%d",&x,&y,&w,&h);
	return Rect(x,y,w,h);
}