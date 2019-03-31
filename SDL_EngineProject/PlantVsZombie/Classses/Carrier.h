#ifndef __Carrier_H__
#define __Carrier_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*地形类型*/
enum class TerrainType
{
	None,
	Lawn,//草地
	Water,//水面
	Stone,//石面
	FlowerPot,//花盆
	LilyPad,//莲叶
};
class Plant;
class Defender;

class Carrier
{
	SDL_SYNTHESIZE(TerrainType,m_terrainType,TerrainType);//该地形的类型
	SDL_BOOL_SYNTHESIZE(m_bDestroyed,Destroyed);//当前的地形是否被毁坏
	SDL_SYNTHESIZE(int,m_nRow,Row);
protected:
	Plant*m_pInnerPlant;
	Defender*m_pDefender;
public:
	Carrier();
	~Carrier();
	//设置内部植物，并保存它的引用
	void setInnerPlant(Plant*plant);
	//清除内部植物，并释放它的引用
	void clearInnerPlant();
	Plant*getInnerPlant()const;
	//设置保卫者
	void setDefender(Defender*defender);
	Defender*getDefender()const;
	void clearDefender();
};
#endif