#ifndef __MapLayer_H__
#define __MapLayer_H__
#include <string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class MapLayer : public Layer
{
private:
	TMXTiledMap* m_pTiledMap;
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	static MapLayer* createWithLevel(const string& levelName);
	
	bool init();
	bool initWithLevel(const string& levelName);
	//获取对象层
	TMXObjectGroup* getObjectGroup()const;
};
#endif