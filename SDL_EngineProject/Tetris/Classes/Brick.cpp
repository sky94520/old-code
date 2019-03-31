#include "Brick.h"
#include "RemoteControl.h"

Brick::Brick()
	:m_nCurIndex(0),m_pControl(nullptr)
{
}
Brick::~Brick()
{
	SDL_SAFE_DELETE(m_pControl);
}
Brick*Brick::create(const vector<Shape>&shapes,const string&spriteName)
{
	auto brick = new Brick();
	if(brick && brick->init(shapes,spriteName))
		brick->autoRelease();
	else
		SDL_SAFE_DELETE(brick);
	return brick;
}
bool Brick::init(const vector<Shape>&shapes,const string&spriteName)
{
	m_spriteName = spriteName;
	m_shapes = shapes;
	//随机
	m_nCurIndex = rand()%m_shapes.size();
	Shape shape = shapes.at(m_nCurIndex);

	for(int i=0;i<4;i++)
	{
		Point point = shape.p[i];
		Sprite*sprite = Sprite::createWithSpriteFrameName(spriteName);
		Size s = sprite->getContentSize();
		sprite->setTag(i);
		sprite->setAnchorPoint(Point(0.f,0.f));
		//设置位置
		sprite->setPosition(point.x*s.width,point.y*s.height);
		this->addChild(sprite);
	}
	//设置遥控
	m_pControl = new RemoteControl();
	m_pControl->addCommand("left", new LeftCommand(this));
	m_pControl->addCommand("right", new RightCommand(this));
	m_pControl->addCommand("transform", new TransformCommand(this));

	return true;
}
void Brick::decline()
{
	auto node = this->getChildByTag(0);
	Size s = node->getContentSize();
	Point nextPos = this->getPosition() + Point(0,s.height);

	this->setPosition(nextPos);
}
void Brick::left()
{
	m_pControl->onButtonPressed("left");
}
void Brick::right()
{
	m_pControl->onButtonPressed("right");
}
void Brick::transform()
{
	m_pControl->onButtonPressed("transform");
}
void Brick::undo()
{
	m_pControl->undoButtonPressed();
}
Shape&Brick::getShape()
{
	return m_shapes.at(m_nCurIndex);
}
Size Brick::getTileSize()
{
	auto node = this->getChildByTag(0);
	return node->getContentSize();
}