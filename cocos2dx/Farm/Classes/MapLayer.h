#ifndef __MapLayer_H__
#define __MapLayer_H__
#include "cocos2d.h"
USING_NS_CC;
/*��ͼ�����㣬��Ҫ���ڳ��������ź��ƶ�*/
class MapLayer:public Layer
{
private:
	Point m_originPos;//ԭ��λ��
	//��ͼ����
	Sprite*m_pBgSprite;
	TMXTiledMap*m_pTiledMap;
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();

	Point getOriginalPosition()const;//���ƫ�Ƶ�λ��
	float getMapScale()const;//��ȡ��ͼ�����ű���
	TMXTiledMap*getTMXTiledMap()const;//��ö�Ӧ��ͼ���
	Sprite*getBgSprite()const;

	void operateMap(const std::vector<Touch*>&touches,Event*event);
	void setScaleForMap(EventMouse*event);
};
#endif