#include "NeedfulFishCompent.h"
NeedfulFishCompent::NeedfulFishCompent()
	:m_pSprite(nullptr),m_pLabel(nullptr)
	,m_nCount(0),m_pBG(nullptr)
{
}
NeedfulFishCompent::~NeedfulFishCompent()
{
}
NeedfulFishCompent*NeedfulFishCompent::create(int id,int num)
{
	auto comp = new NeedfulFishCompent();
	if(comp && comp->init(id,num))
		comp->autorelease();
	else
		CC_SAFE_DELETE(comp);
	return comp;
}
bool NeedfulFishCompent::init(int id,int num)
{
	//加载背景
	m_pBG = Sprite::create("bk.png");
	Size size = m_pBG->getContentSize();
	m_pBG->setPosition(size.width/2,size.height/2);
	this->addChild(m_pBG,-1);
	//加载图片
	std::string spriteName = StringUtils::format("fish%02d_00.png",id);
	m_pSprite = Sprite::createWithSpriteFrameName(spriteName);
	m_pSprite->setPosition(size.width/2,size.height/2);

	this->addChild(m_pSprite);
	//加载字体
	m_pLabel = Label::createWithCharMap("LabelAtlas.png",21,21,'0');
	m_pLabel->setAnchorPoint(Point(1.f,0.f));
	m_pLabel->setPosition(size.width,0);
	this->addChild(m_pLabel);
	//设置个数
	this->setCount(num);
	this->setContentSize(size);

	return true;
}
void NeedfulFishCompent::setCount(int count)
{
	if(m_nCount == count)
		return;
	m_nCount = count;
	std::string text = StringUtils::format("%02d",count);
	m_pLabel->setString(text);
}
int NeedfulFishCompent::getCount()const
{
	return m_nCount;
}