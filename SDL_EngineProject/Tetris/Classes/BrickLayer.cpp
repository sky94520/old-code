#include "BrickLayer.h"
#include "DynamicData.h"

BrickLayer::BrickLayer()
	:m_pNowBrick(nullptr),m_pNextBrick(nullptr)
	,m_pDelegate(nullptr),m_elpased(0.f),m_interval(0.f)
{
	m_interval = DynamicData::getInstance()->getIntervalByLevel();
}
BrickLayer::~BrickLayer()
{
}
BrickLayer*BrickLayer::create(BrickLayerDelegate*pDelegate)
{
	auto layer = new BrickLayer();
	if(layer && layer->init(pDelegate))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool BrickLayer::init(BrickLayerDelegate*pDelegate)
{
	this->initBlockS();
	this->initBlockO();
	this->initBlockZ();
	this->initBlockI();
	this->initBlockL();
	this->initBlockJ();
	this->initBlockT();

	m_pDelegate = pDelegate;
	this->reset();
	//定时器
	//this->schedule(schedule_selector(BrickLayer::decline),0.5f,-1);
	return true;
}
void BrickLayer::update(float dt)
{
	//方块下落
	m_elpased += dt;
	if(m_elpased < m_interval)
		return;
	m_elpased = 0.f;
	//判断是否发生碰撞
	CollideResult result = m_pDelegate->isGameOver(m_pNowBrick);
	//仅仅发生碰撞
	if(kResult_OnlyCollided == result)
	{
		SoundManager::getInstance()->playEffect("down.ogg",0);
		//插入到map中
		m_pDelegate->insertBrick(m_pNowBrick);
		//判断是否可消除有可消除方块
		int line = m_pDelegate->clearUpLineNum();
		if(line > 0)
		{
			//todo 发送给DynamicData 赋值
			DynamicData::getInstance()->alterScore(line);

			SoundManager::getInstance()->playEffect("delete.ogg",0);
		}
		//方块下落间隔
		m_interval = DynamicData::getInstance()->getIntervalByLevel();

		const Rect clientRect = m_pDelegate->getClientRect();
		//清除原方块
		m_pNowBrick->removeFromParent();

		Point pos = m_pNextBrick->getPosition();
		m_pNowBrick = m_pNextBrick;
		m_pNowBrick->setPosition(clientRect.size.width/2,0);
		//生成新方块
		m_pNextBrick = this->getRandomBrick();
		m_pNextBrick->setPosition(pos);
		this->addChild(m_pNextBrick);
	}
	//游戏结束
	else if(kResult_GameOver == result)
	{
		m_pDelegate->gameOver();
	}
	else
	{
		m_pNowBrick->decline();
	}
}
Brick*BrickLayer::getRandomBrick()
{
	int i = rand()%m_blocks.size();
	Block&block = m_blocks.at(i);
	return Brick::create(block.shapes,block.spriteName);
}
void BrickLayer::reset()
{
	if(m_pNowBrick)
	{
		m_pNowBrick->removeFromParent();
	}
	if(m_pNextBrick)
		m_pNextBrick->removeFromParent();

	m_pNowBrick = this->getRandomBrick();
	m_pNextBrick = this->getRandomBrick();

	m_pNextBrick->setPosition(400,400);
	this->addChild(m_pNextBrick);
	this->addChild(m_pNowBrick);
	//设置位置
	Rect clientRect = m_pDelegate->getClientRect();
	m_pNowBrick->setPosition(clientRect.size.width/2,0);

	m_elpased = 0.f;
	m_interval = DynamicData::getInstance()->getIntervalByLevel();
}
void BrickLayer::onKeyPressed(SDL_Keycode keyCode,SDL_Event*event)
{
	if(keyCode == SDLK_UP)
	{
		if(this->transform())
			SoundManager::getInstance()->playEffect("rotate.ogg",0);
	}
	else if(keyCode == SDLK_LEFT)
	{
		if(this->left())
			SoundManager::getInstance()->playEffect("move.ogg",0);
	}
	else if(keyCode == SDLK_RIGHT)
	{
		if(this->right())
			SoundManager::getInstance()->playEffect("move.ogg",0);
	}
	else if(keyCode == SDLK_DOWN)
		m_interval = 0.f;
}
bool BrickLayer::left()
{
	m_pNowBrick->left();
	if(m_pDelegate->isCollided(m_pNowBrick))
	{
		m_pNowBrick->undo();
		return false;
	}
	return true;
}
bool BrickLayer::right()
{
	m_pNowBrick->right();
	if(m_pDelegate->isCollided(m_pNowBrick))
	{
		m_pNowBrick->undo();
		return false;
	}
	return true;
}
bool BrickLayer::transform()
{
	m_pNowBrick->transform();
	if(m_pDelegate->isCollided(m_pNowBrick))
	{
		m_pNowBrick->undo();
		return false;
	}
	return true;
}
void BrickLayer::initBlockS()
{
	//S 两种形状
	Block s;
	vector<Shape> shapes;
	Shape shape1,shape2;
	s.spriteName = "blue.png";
	shape1.p[0] = Point(0,-3);
	shape1.p[1] = Point(0,-2);
	shape1.p[2] = Point(1,-2);
	shape1.p[3] = Point(1,-1);

	shape2.p[0] = Point(1,-2);
	shape2.p[1] = Point(0,-2);
	shape2.p[2] = Point(0,-1);
	shape2.p[3] = Point(-1,-1);
	shapes.push_back(shape1);
	shapes.push_back(shape2);

	s.shapes = shapes;

	m_blocks.push_back(s);
}
void BrickLayer::initBlockO()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;

	s.spriteName = "orange.png";
	shape.p[0] = Point(0,-2);
	shape.p[1] = Point(1,-2);
	shape.p[2] = Point(0,-1);
	shape.p[3] = Point(1,-1);
	shapes.push_back(shape);
	s.shapes = shapes;

	m_blocks.push_back(s);
}
void BrickLayer::initBlockZ()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;
	s.spriteName = "purple.png";

	shape.p[0] = Point(1,-3);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(1,-2);
	shape.p[3] = Point(0,-1);

	shapes.push_back(shape);

	shape.p[0] = Point(-1,-2);
	shape.p[1] = Point(0,-1);
	shape.p[2] = Point(0,-2);
	shape.p[3] = Point(1,-1);
	shapes.push_back(shape);

	s.shapes = shapes;
	m_blocks.push_back(s);
}
void BrickLayer::initBlockI()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;
	s.spriteName = "red.png";

	shape.p[0] = Point(0,-4);
	shape.p[1] = Point(0,-3);
	shape.p[2] = Point(0,-2);
	shape.p[3] = Point(0,-1);
	shapes.push_back(shape);
	shape.p[0] = Point(2,-1);
	shape.p[1] = Point(1,-1);
	shape.p[2] = Point(0,-1);
	shape.p[3] = Point(-1,-1);
	shapes.push_back(shape);
	s.shapes = shapes;

	m_blocks.push_back(s);
}
void BrickLayer::initBlockL()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;
	s.spriteName = "black.png";
	//1
	shape.p[0] = Point(-1,-3);
	shape.p[1] = Point(-1,-2);
	shape.p[2] = Point(-1,-1);
	shape.p[3] = Point(0,-1);
	shapes.push_back(shape);
	//2
	shape.p[0] = Point(1,-2);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(-1,-2);
	shape.p[3] = Point(-1,-1);
	shapes.push_back(shape);
	//3
	shape.p[0] = Point(1,-1);
	shape.p[1] = Point(1,-2);
	shape.p[2] = Point(1,-3);
	shape.p[3] = Point(0,-3);
	shapes.push_back(shape);
	//4
	shape.p[0] = Point(-1,-1);
	shape.p[1] = Point(0,-1);
	shape.p[2] = Point(1,-1);
	shape.p[3] = Point(1,-2);
	shapes.push_back(shape);

	s.shapes = shapes;
	m_blocks.push_back(s);
}
void BrickLayer::initBlockJ()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;
	s.spriteName = "gray.png";
	//1
	shape.p[0] = Point(1,-3);
	shape.p[1] = Point(1,-2);
	shape.p[2] = Point(1,-1);
	shape.p[3] = Point(0,-1);
	shapes.push_back(shape);
	//2
	shape.p[0] = Point(1,-1);
	shape.p[1] = Point(0,-1);
	shape.p[2] = Point(-1,-1);
	shape.p[3] = Point(-1,-2);
	shapes.push_back(shape);
	//3
	shape.p[0] = Point(-1,-1);
	shape.p[1] = Point(-1,-2);
	shape.p[2] = Point(-1,-3);
	shape.p[3] = Point(0,-3);
	shapes.push_back(shape);
	//4
	shape.p[0] = Point(-1,-2);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(1,-2);
	shape.p[3] = Point(1,-1);
	shapes.push_back(shape);

	s.shapes = shapes;
	m_blocks.push_back(s);
}
void BrickLayer::initBlockT()
{
	Block s;
	vector<Shape> shapes;
	Shape shape;
	s.spriteName = "green.png";
	//1
	shape.p[0] = Point(0,-3);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(0,-1);
	shape.p[3] = Point(-1,-2);
	shapes.push_back(shape);
	//2
	shape.p[0] = Point(1,-1);
	shape.p[1] = Point(0,-1);
	shape.p[2] = Point(-1,-1);
	shape.p[3] = Point(0,-2);
	shapes.push_back(shape);
	//3
	shape.p[0] = Point(0,-1);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(0,-3);
	shape.p[3] = Point(1,-2);
	shapes.push_back(shape);
	//4
	shape.p[0] = Point(-1,-2);
	shape.p[1] = Point(0,-2);
	shape.p[2] = Point(1,-2);
	shape.p[3] = Point(0,-1);
	shapes.push_back(shape);

	s.shapes = shapes;
	m_blocks.push_back(s);
}