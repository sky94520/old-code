#include "TowerBorder.h"
TowerBorder::TowerBorder():m_pHero(NULL)
{
}
TowerBorder::~TowerBorder()
{
}
bool TowerBorder::init()
{
	this->bindSprite(Sprite::create("sprite/hero/border.png"));
	return true;
}
bool TowerBorder::isClickMe(Point pos)
{
	return getBoundingBox().containsPoint(pos);
}
void TowerBorder::bindHero(Hero*hero)
{
	m_pHero = hero;
}
Hero* TowerBorder::getHero()
{
	return m_pHero;
}
void TowerBorder::deleteHero()
{
	if(m_pHero!=NULL)
		m_pHero->removeFromParent();
}
void TowerBorder::upgrade()
{
/*	if(getSprite() != NULL)
		getSprite()->stopAllActions();
	std::string sFilePath = StringUtils::format("sprite/hero/border_%d.png",m_nCurLevel);
	Sprite*sprite = Sprite::create(sFilePath);
	bindSprite(sprite);
	m_nCurLevel++;

	if(m_nCurLevel == 2)
	{
		auto rotateBy = RotateBy::create(25,360,360);
		auto repeat = RepeatForever::create(rotateBy);
		sFilePath = StringUtils::format("sprite/hero/magic_border_%d.png",m_nCurLevel);
		sprite = Sprite::create(sFilePath);
		sprite->setOpacity(80);
		sprite->runAction(repeat);
		this->addChild(sprite,10);
	}*/
}
/*void TowerBorder::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	//ÉèÖÃ»­±Ê´ÖÏ¸
	glLineWidth(5.f);
	Size size = getContentSize();
	//»æÖÆ¾ØÐÎ
	Point srcPos = Point(0,size.height);
	Point destPos = Point(size.width,0);
	DrawPrimitives::drawRect(srcPos,destPos);
	glLineWidth(1);
	//½áÊø»æÖÆ
	kmGLPopMatrix();
}
void TowerBorder::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	if(true)
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(TowerBorder::onDraw,this,transform,flags);
		renderer->addCommand(&_customCommand);
	}
}
*/