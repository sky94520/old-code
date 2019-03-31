#ifndef __TerrainMaker_H__
#define __TerrainMaker_H__
#include<cmath>
#include<functional>
#include "SDL_Engine/SDL_Engine.h"
#include "Terrain.h"

using namespace std;
using namespace SDL;
/*进行地形的分析,每新建一个就回调函数传递值*/
class TerrainMaker
{
private:
	function<void (Terrain*)> m_callback;
public:
	TerrainMaker();
	//开始解析
	void startParse(TMXTiledMap*tiledMap,const function<void (Terrain*)>& callback);
private:
	void parseTileLayer(TMXLayer*layer,TMXTiledMap*tiledMap);
	void parseObjectGroup(TMXObjectGroup*objectGroup);
};
#endif