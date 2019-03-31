#ifndef __TiledMapLayer_H__
#define __TiledMapLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class TiledMapLayer:public Layer
{
private:
	TMXTiledMap*m_pTiledMap;
public:
	TiledMapLayer();
	~TiledMapLayer();
	static TiledMapLayer*create(const std::string&tmx);
	bool init(const std::string&tmx);
public:
	ValueMap getObject(const std::string&name)const;
	TMXLayer*getLayer(const std::string&name)const;
	//pos¾ø¶Ô×ø±ê
	ValueMap getValueMapByPosition(const std::string&name,const Point&pos);
private:
	Vec2 tileCoordFromPosition(const Vec2&pos);
};
#endif