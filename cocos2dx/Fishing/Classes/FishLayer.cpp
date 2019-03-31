#include "FishLayer.h"
#include "Fish.h"
#include "RotateWithAction.h"
#include "LuaEngine.h"
#include "PhysicalEngine.h"

FishLayer::FishLayer()
{
}
FishLayer::~FishLayer()
{
	m_fishes.clear();
	m_willShowFishes.clear();
	m_showingFishes.clear();
}
bool FishLayer::init()
{
	//Ŀǰ�����һ��
	for(int i=0;i<4;i++)
	{
		auto fish = Fish::create(1);
		fish->setVisible(false);
		fish->setGlobalZOrder(0);

		this->addChild(fish);

		m_willShowFishes.pushBack(fish);
		m_fishes.pushBack(fish);

		initFish(fish);
		//Ϊfish�󶨸���
		PhysicalEngine::getInstance()->bindBodyForFish(fish);
		PhysicalEngine::getInstance()->bindScaredBodyForFish(fish);
	}
	//Fish*fish = Fish::create(1);
	return true;
}
void FishLayer::reset()
{
	//���
	m_showingFishes.clear();
	m_willShowFishes.clear();
	//������
	for(auto fish:m_fishes)
	{
		fish->setVisible(false);
		fish->setElapsed(0.f);
		fish->stopAllActions();

		this->initFish(fish);
		//��ӽ�Ҫ�ϳ�����
		m_willShowFishes.pushBack(fish);
	}
}
void FishLayer::update(float dt)
{
	for(auto iter = m_willShowFishes.begin();iter != m_willShowFishes.end();)
	{
		auto fish = *iter;

		auto elapsed = fish->getElapsed() - dt;
		//�����Ҫ����
		if(elapsed <= 0.f)
		{
			fish->setVisible(true);
			fish->reset();
			//�����㵽��һ��vector
			m_showingFishes.pushBack(fish);
			iter = m_willShowFishes.erase(iter);

			fish->runNormalAnimation();
			auto r = 1;//rand()%2;
			if(r == 0)
				this->linerRoute(fish);
			else if(r == 1)
				this->bezierRoute(fish);
		}
		else
		{
			fish->setElapsed(elapsed);
			++iter;
		}
	}
	//�����ڳ��ϵ���
	for(auto iter = m_showingFishes.begin();iter != m_showingFishes.end();)
	{
		auto fish = *iter;
		//�ȴ���һ�γ���
		if(fish->isVisible() == false)
		{
			initFish(fish);
			m_willShowFishes.pushBack(fish);
			iter = m_showingFishes.erase(iter);
		}
		else
			++iter;
	}
}
void FishLayer::linerRoute(Fish*pFish)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size fishSize = pFish->getContentSize();
	
	int y1 = CCRANDOM_0_1() * (visibleSize.height - 100);
	int y2 = CCRANDOM_0_1() * (visibleSize.height - 100);

	Point startPos = Point(-fishSize.width/2 + 1,y1);
	Point endPos = Point(visibleSize.width + fishSize.width,y2);
	//todo �˶�����
	bool bLeft = false;
	//�����˶�����
	if(bLeft == false)
		pFish->getSprite()->setFlippedX(true);
	else
		pFish->getSprite()->setFlippedX(false);
	//���õ�ǰλ��
	pFish->setPosition(startPos);
	//����
	auto delta = endPos - startPos;
	float speed = pFish->getSpeed();
	MoveTo*move = MoveTo::create(delta.getLength()/speed,endPos);
	
	ActionInterval*action = RotateWithAction::create(move);
	CallFunc*end = CallFunc::create([&,pFish](){
		pFish->setVisible(false);
	});
	auto seq = Sequence::createWithTwoActions(action,end);

	pFish->runAction(seq);
}
void FishLayer::bezierRoute(Fish*pFish)
{
	//ȷ����ʼ����ͽ�������
	int a[2]={0,0};
	Point points[4];

	Size size = pFish->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ��ʼ���� 0 �� 1 �� 2 �� �� 3
	a[0] =a[1] = rand()%4;
	//��������
	while(a[1] == a[0])
		a[1] = rand()%4;

	for(unsigned int i=0;i<2;i++)
	{
		Point pos;
		//��
		if(a[i] == 0)
		{
			pos.x = - size.width/2;
			pos.y = CCRANDOM_0_1()*visibleSize.height;
			if(i == 1)
				pos.x -= 1;
		}
		//��
		else if(a[i] == 1)
		{
			pos.x = CCRANDOM_0_1()*visibleSize.width;
			pos.y = - size.height/2;
			if(i==1)
				pos.y -= 1;
		}
		//��
		else if(a[i] == 2)
		{
			pos.x = visibleSize.width + size.width/2;
			pos.y = CCRANDOM_0_1()*visibleSize.height;
			if(i==1)
				pos.x += 1;
		}
		//��
		else if(a[i] == 3)
		{
			pos.x = CCRANDOM_0_1()*visibleSize.height;
			pos.y = visibleSize.height + size.height/2;
			if(i==1)
				pos.y += 1;
		}
		points[i] = pos;
		//ȷ������������ ���Ƶ�
		points[i+2].x = CCRANDOM_0_1()*visibleSize.width;
		points[i+2].y = CCRANDOM_0_1()*visibleSize.height;
	}
	ccBezierConfig config;
	config.controlPoint_1 = points[2];
	config.controlPoint_2 = points[3];
	config.endPosition = points[1];
	//��ĳ�ʼλ��
	pFish->setPosition(points[0]);
	
	//��ȷ������ʱ��
	float distance = points[0].distance(points[2]) + points[2].distance(points[1]); 
	float speed = pFish->getSpeed();
	BezierTo*bezierTo = BezierTo::create(distance/speed,config);

	ActionInterval*action = RotateWithAction::create(bezierTo);
	CallFunc*end = CallFunc::create([&,pFish](){
		pFish->setVisible(false);
	});
	Sequence*seq = Sequence::createWithTwoActions(action,end);
	pFish->runAction(seq);
}
void FishLayer::initFish(Fish*pFish)
{
	auto luaState = LuaEngine::getInstance()->getLuaState();
	//���ջ��
	lua_settop(luaState,0);
	//��ȡLevel��
	lua_getglobal(luaState,"Level");
	//�ѱ��еĺ����ŵ�ջ��
	lua_pushstring(luaState,"getNextFishID");
	lua_gettable(luaState,-2);
	//�ж�ջ���Ƿ�Ϊ����
	bool ret = lua_isfunction(luaState,-1);
	//ִ�к���
	lua_call(luaState,0,2);
	//��ȡջ��Ԫ��
	int id = lua_tonumber(luaState,-2);//��һ������ֵ
	float elapsed = lua_tonumber(luaState,-1);//�ڶ�������ֵ
	//ͨ��id����fish
	//log("%d",id);
	pFish->init(id);
	pFish->setElapsed(elapsed);
	//������ײ������� todo
	const int PTM_RATIO = PhysicalEngine::getInstance()->PTM_RATIO;
	
	b2Body*colliableBody = pFish->getColliableBody();
	if(colliableBody)
	{
		b2PolygonShape*shape = dynamic_cast<b2PolygonShape*>(colliableBody->GetFixtureList()->GetShape());
		//b2CircleShape*shape = dynamic_cast<b2CircleShape*>(colliableBody->GetFixtureList()->GetShape());
		//shape->m_radius = pFish->getColliableRect().size.width/PTM_RATIO/2;
		Size s = pFish->getColliableRect().size;
		shape->SetAsBox(s.width/PTM_RATIO/2,s.height/PTM_RATIO/2);
	}
	//���þ������
	b2Body*scaredBody = pFish->getScaredBody();
	if(scaredBody)
	{
		b2CircleShape*shape = dynamic_cast<b2CircleShape*>(scaredBody->GetFixtureList()->GetShape());
		shape->m_radius = pFish->getScaredRect().size.width/PTM_RATIO/2;
	}
}
Vector<Fish*>* FishLayer::getFishes()
{
	return &m_fishes;
}