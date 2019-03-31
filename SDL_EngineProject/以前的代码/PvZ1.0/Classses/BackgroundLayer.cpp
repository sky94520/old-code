#include "BackgroundLayer.h"
#include "Lawn.h"
#include "MainLua.h"
BackgroundLayer::BackgroundLayer()
	:m_pBG(nullptr),m_startPos(256,80),m_size(80,100)
	,m_bDay(true),m_skillCD(0.f),m_elapsed(0.f)
	,m_zombiePath("")
{
	//初始化
	for(int i=0;i<5;i++)
		for(int j=0;j<9;j++)
			m_pCarriers[i][j] = nullptr;
}
BackgroundLayer::~BackgroundLayer()
{
}
bool BackgroundLayer::init()
{
	//todo
	//创建载体
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<9;j++)
		{
			auto carrier = Lawn::create();
			carrier->setPosition(m_startPos + Point(j*m_size.width,i*m_size.height));
			this->addChild(carrier);
			m_pCarriers[i][j] = carrier;
		}
	}
	return true;
}
void BackgroundLayer::update(float dt)
{

}
void BackgroundLayer::loadLevel(const std::string&level)
{
	MainLua::getInstance()->dofile(level.c_str());
	std::string bg = MainLua::getInstance()->getStringFromTable("level","background");
	m_bDay = MainLua::getInstance()->getBoolFromTable("level","bDay");
	m_zombiePath = MainLua::getInstance()->getStringFromTable("level","filepath");

	if(m_pBG)
		m_pBG->removeFromParent();
	m_pBG = Sprite::create(bg);
	this->addChild(m_pBG);

	this->setContentSize(m_pBG->getContentSize());
	initSkillCD();
}
void BackgroundLayer::initSkillCD()
{
	m_skillCD = MainLua::getInstance()->getDoubleFromTable("level","skillCD");
}
Carrier* BackgroundLayer::getCarrierByPos(const Point&pos)
{
	//获取指定载体
	int x = (pos.y - m_startPos.y)/m_size.height;
	int y = (pos.x - m_startPos.x)/m_size.width;
	//if()
	return m_pCarriers[x][y];
}
Rect BackgroundLayer::getLegalRect()const
{
	return Rect(m_startPos,Size(9*m_size.width,5*m_size.height));
}
bool BackgroundLayer::isDay()const
{
	return m_bDay;
}
