#ifndef __TerrainMaker_H__
#define __TerrainMaker_H__
#include<cmath>
#include<functional>
#include "SDL_Engine/SDL_Engine.h"
#include "Terrain.h"

using namespace std;
using namespace SDL;
/*���е��εķ���,ÿ�½�һ���ͻص���������ֵ*/
class TerrainMaker
{
private:
	function<void (Terrain*)> m_callback;
public:
	TerrainMaker();
	//��ʼ����
	void startParse(TMXTiledMap*tiledMap,const function<void (Terrain*)>& callback);
private:
	void parseTileLayer(TMXLayer*layer,TMXTiledMap*tiledMap);
	void parseObjectGroup(TMXObjectGroup*objectGroup);
};
#endif