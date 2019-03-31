#ifndef __MapLayer_H__
#define __MapLayer_H__
#include "cocos2d.h"
USING_NS_CC;
/*地图操作层，主要用于场景的缩放和移动*/
class MapLayer:public Layer
{
private:
	Point m_originPos;//原点位置
	//地图背景
	Sprite*m_pBgSprite;
	TMXTiledMap*m_pTiledMap;
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();

	Point getOriginalPosition()const;//获得偏移点位置
	float getMapScale()const;//获取地图的缩放倍数
	TMXTiledMap*getTMXTiledMap()const;//获得对应的图块层
	Sprite*getBgSprite()const;

	void operateMap(const std::vector<Touch*>&touches,Event*event);
	void setScaleForMap(EventMouse*event);
};
#endif