#include "MapLayer.h"
MapLayer::MapLayer()
	:m_pBgSprite(nullptr),m_pTiledMap(nullptr)
{
}
MapLayer::~MapLayer()
{
}
bool MapLayer::init()
{
	//��ͼ����
	LayerColor*mapLayer = LayerColor::create(Color4B(78,127,41,255));
	this->addChild(mapLayer,-1);

	m_pBgSprite = Sprite::create("2.jpg");
	m_pBgSprite->setAnchorPoint(Point(0.f,0.f));
	m_pBgSprite->setPosition(Point::ZERO);
	m_originPos = Point::ZERO;

	mapLayer->addChild(m_pBgSprite);
	//���tmx
	m_pTiledMap = TMXTiledMap::create("mymap8.tmx");
	m_pBgSprite->addChild(m_pTiledMap);

	mapLayer->setContentSize(m_pTiledMap->getContentSize());

	Sprite*treeSprite = Sprite::create("1.png");
	treeSprite->setAnchorPoint(Point(0.f,0.f));
	treeSprite->setPosition(0.f,0.f);
	treeSprite->setScale(2.f);

	m_pBgSprite->addChild(treeSprite);

	return true;
}
Point MapLayer::getOriginalPosition()const
{
	return this->m_originPos;
}
float MapLayer::getMapScale()const
{
	return m_pBgSprite->getScale();
}
TMXTiledMap*MapLayer::getTMXTiledMap()const
{
	return m_pTiledMap;
}
Sprite*MapLayer::getBgSprite()const
{
	return m_pBgSprite;
}
//public
void MapLayer::operateMap(const std::vector<Touch*>&touches,Event*event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//˫ָ����
	if(touches.size() > 1)
	{
	}
	//��ָ�϶�
	else if(touches.size() == 1)
	{
		auto touch = touches.at(0);
		//�϶�����
		auto delta = touch->getDelta();
		//ͼƬ��ǰλ��
		auto curPos = m_pBgSprite->getPosition();
		//�������λ��
		auto pos = curPos + delta;
		//��ǰ�ߴ�
		auto bgSpriteSize = m_pBgSprite->getBoundingBox().size;
		//����
		pos.x = MIN(pos.x,bgSpriteSize.width*m_pBgSprite->getAnchorPoint().x);
		pos.x = MAX(pos.x,-bgSpriteSize.width + visibleSize.width+bgSpriteSize.width*m_pBgSprite->getAnchorPoint().x);
		pos.y = MIN(pos.y,bgSpriteSize.height*m_pBgSprite->getAnchorPoint().y);
		pos.y = MAX(pos.y,-bgSpriteSize.height + visibleSize.height+bgSpriteSize.height*m_pBgSprite->getAnchorPoint().y);

		m_pBgSprite->setPosition(pos);
		//����ԭ��λ��
		if(pos.x >= bgSpriteSize.width*m_pBgSprite->getAnchorPoint().x
			||pos.x <= -bgSpriteSize.width + visibleSize.width + bgSpriteSize.width*m_pBgSprite->getAnchorPoint().x)
		{
			delta.x = 0;
		}
		if(pos.y >= bgSpriteSize.height*m_pBgSprite->getAnchorPoint().y
			||pos.y <= -bgSpriteSize.height + visibleSize.height + bgSpriteSize.height*m_pBgSprite->getAnchorPoint().y)
		{
			delta.y = 0;
		}
		m_originPos += delta;
		//log("%.2f %.2f",m_originPos.x,m_originPos.y);
	}
}
void MapLayer::setScaleForMap(EventMouse*event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point center = Point(event->getCursorX(),event->getCursorY());
	Size bgSize = m_pBgSprite->getBoundingBox().size;
	
	Point anchorPos = Point((center.x - m_originPos.x)/bgSize.width
		,(center.y - m_originPos.y)/bgSize.height);

	//��ȡ��껬�ֵ�ǰ״̬ �Ƿ���С
	bool zoomOut = event->getScrollY() == -1.f;
	float scale = m_pBgSprite->getScale();
	if(zoomOut)
		scale += 0.1f;
	else
		scale -= 0.1f;
	scale = MAX(1,MIN(4,scale));

	if( m_originPos.x > 0)
    {
        center.x -= m_originPos.x;
		m_originPos.x = 0;
    }
	if( m_originPos.x < -bgSize.width + visibleSize.width )
    {
        center.x +=  -bgSize.width + visibleSize.width - m_originPos.x;
		m_originPos.x = -bgSize.width + visibleSize.width;
    }
    if( m_originPos.y > 0 )
    {
        center.y -= m_originPos.y;
		m_originPos.y = 0;
    }
    if( m_originPos.y < -bgSize.height + visibleSize.height )
    {
        center.y +=  -bgSize.height + visibleSize.height - m_originPos.y;
		m_originPos.y = -bgSize.height + visibleSize.height;
    }
	m_pBgSprite->setAnchorPoint(anchorPos);
	m_pBgSprite->setScale(scale);

	m_pBgSprite->setPosition(center);
	 // ����ԭ��λ��
	Size s = m_pBgSprite->getBoundingBox().size;
	m_originPos = center - Vec2(s.width * anchorPos.x, s.height * anchorPos.y);
}