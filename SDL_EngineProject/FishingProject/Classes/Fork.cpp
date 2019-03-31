#include "Fork.h"

Fork::Fork()
	:m_bShooting(false)
{
}
Fork::~Fork()
{
}
bool Fork::init()
{
	bindSprite(Sprite::create("fork.png"));
	return true;
}
void Fork::shoot(const Point&targetPos)
{
	m_targetPos = targetPos;

	Size s = this->getContentSize();
	//转化成本地坐标
	Point pos = targetPos;
	/*pos.y -= s.height/2;
	pos.x += s.width/4;*/

	//创建动画
	auto delta = Point(0,-50);
	this->setPosition(pos - delta);
	auto speed = 500;

	MoveBy*move = MoveBy::create(delta.length()/speed,delta);
	this->m_bShooting = true;
	CallFunc*endShooting = CallFunc::create([&](){
		this->setShooting(false);
	});
	CallFunc*end = CallFunc::create([&](){
		this->setVisible(false);
	});
	//运行动作
	DelayTime*delay = DelayTime::create(0.4f);
	this->runAction(Sequence::create(move,endShooting,delay,end,nullptr));
}
Rect Fork::getColliableRect()const
{
	//先获取世界坐标
	Point worldPos = m_targetPos;
	Size s = Size(1,1);

	worldPos.y -= s.height;

	return Rect(worldPos.x,worldPos.y,s.width,s.height);
}
std::vector<Rect> Fork::getColliableRects()const
{
	Size size = this->getContentSize();
	std::vector<Rect> rects;
	Rect rect(0,0,10,10);
	rects.push_back(rect);

	return rects;
}
void Fork::setShooting(bool shooting)
{
	m_bShooting = shooting;
}
bool Fork::isShooting()const
{
	return m_bShooting;
}