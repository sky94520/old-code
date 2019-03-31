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
}
bool FishLayer::init()
{
	//目前仅添加一个
	for(int i=0;i<1;i++)
	{
		auto fish = Fish::create(1);
		fish->setVisible(false);
		this->addChild(fish);

		m_fishes.push_back(fish);
		//为fish绑定刚体
		PhysicalEngine::getInstance()->bindBodyForFish(fish);
		PhysicalEngine::getInstance()->bindScaredBodyForFish(fish);
	}
	//Fish*fish = Fish::create(1);
	return true;
}
void FishLayer::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Rect r1 = Rect(0,0,visibleSize.width,visibleSize.height);

	for(auto fish:m_fishes)
	{
		Point pos = fish->getPosition();
		//log("x:%.2f y:%.2f",pos.x,pos.y);

		Rect r2 = fish->getBoundingBox();

		if(r1.intersectsRect(r2) == false || fish->isVisible() == false)
		{
			fish->setVisible(true);
			fish->reset();

			fish->runNormalAnimation();

			auto r = 0;//rand()%2;
			if(r == 0)
				this->linerRoute(fish);
			else if(r == 1)
				this->bezierRoute(fish);
		}
	}
}
Vector<Fish*>& FishLayer::getFishes()
{
	return m_fishes;
}
void FishLayer::linerRoute(Fish*pFish)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size fishSize = pFish->getContentSize();
	
	int y1 = RANDOM_0_1() * (visibleSize.height - 100);
	int y2 = RANDOM_0_1() * (visibleSize.height - 100);

	Point startPos = Point(-fishSize.width/2 + 1,y1);
	Point endPos = Point(visibleSize.width + fishSize.width,y2);
	//todo 运动方向
	bool bLeft = false;
	//设置运动方向
	if(bLeft == false)
		pFish->getSprite()->setFlipX(true);
	else
		pFish->getSprite()->setFlipX(false);
	//设置当前位置
	pFish->setPosition(startPos);
	//动作
	auto delta = endPos - startPos;
	float speed = pFish->getSpeed();
	MoveTo*move = MoveTo::create(delta.length()/speed,endPos);
	
	ActionInterval*action = RotateWithAction::create(move);
	action->setTag(1);

	pFish->runAction(action);
}
void FishLayer::bezierRoute(Fish*pFish)
{
	//确定起始坐标和结束坐标
	int a[2]={0,0};
	Point points[4];

	Size size = pFish->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取开始坐标 0 左 1 下 2 右 上 3
	a[0] =a[1] = rand()%4;
	//结束坐标
	while(a[1] == a[0])
		a[1] = rand()%4;

	for(unsigned int i=0;i<2;i++)
	{
		Point pos;
		//左
		if(a[i] == 0)
		{
			pos.x = - size.width/2;
			pos.y = RANDOM_0_1()*visibleSize.height;
			if(i == 1)
				pos.x -= 1;
		}
		//下
		else if(a[i] == 1)
		{
			pos.x = RANDOM_0_1()*visibleSize.width;
			pos.y = - size.height/2;
			if(i==1)
				pos.y -= 1;
		}
		//右
		else if(a[i] == 2)
		{
			pos.x = visibleSize.width + size.width/2;
			pos.y = RANDOM_0_1()*visibleSize.height;
			if(i==1)
				pos.x += 1;
		}
		//上
		else if(a[i] == 3)
		{
			pos.x = RANDOM_0_1()*visibleSize.height;
			pos.y = visibleSize.height + size.height/2;
			if(i==1)
				pos.y += 1;
		}
		points[i] = pos;
		//确定贝塞尔曲线 控制点
		points[i+2].x = RANDOM_0_1()*visibleSize.width;
		points[i+2].x = RANDOM_0_1()*visibleSize.height;
	}
	/*ccBezierConfig config;
	config.controlPoint_1 = points[2];
	config.controlPoint_2 = points[3];
	config.endPosition = points[1];
	//鱼的初始位置
	pFish->setPosition(points[0]);
	
	//简单确定动作时间
	float distance = points[0].distance(points[1]);
	float speed = pFish->getSpeed() - 50;
	BezierTo*bezierTo = BezierTo::create(distance/speed,config);

	ActionInterval*action = RotateWithAction::create(bezierTo);
	action->setTag(1);
	pFish->runAction(action);*/
}
void FishLayer::createNextFish()
{
	auto luaState = LuaEngine::getInstance()->getLuaState();
	//清空栈顶
	lua_settop(luaState,0);
	//获取Level表
	lua_getglobal(luaState,"Level");
	//把表中的函数放到栈顶
	lua_pushstring(luaState,"getNextFishID");
	lua_gettable(luaState,-2);
	//执行函数
	lua_call(luaState,0,1);
	//获取栈顶元素
	int id = lua_tonumber(luaState,-1);
	//通过id创建fish
	//log("%d",id);
}