#ifndef __Card_H__
#define __Card_H__
#include<string>
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "StaticData.h"

using namespace std;
using namespace SDL;

enum class CardType
{
	Common,
	Consumable,//消耗品
};
#define CARD_DISABLE_SPRITE_TAG 1
#define CARD_NORMAL_SPRITE_TAG 2
#define CARD_NUMBER_LABEL_TAG 3
#define CARD_CD_TIMER_TAG 4
/*专门用于植物卡片和僵尸卡片*/
class Card : public MenuItem
{
	SDL_SYNTHESIZE(CardType,m_type,CardType);//卡片类型

	SDL_SYNTHESIZE(float,m_fCurCD,CurCD);//当前cd
	SDL_SYNTHESIZE(float,m_fCD,CD);//冷却时间
	SDL_SYNTHESIZE(int,m_nWorth,Worth);//花费
	SDL_SYNTHESIZE(std::string,m_description,Description);//描述
	SDL_SYNTHESIZE(std::string,m_cardName,CardName);//卡片名称
	SDL_SYNTHESIZE(string,m_necessoryItem,NecessoryItem);
	SDL_SYNTHESIZE(ActiveTime,m_activeTime,ActiveTime);
private:
	Sprite*m_pNormalSprite;//正常的图片
	Sprite*m_pDisableSprite;//无法点击的图片
	ProgressTimer*m_pCDTimer;//显示cd
	LabelAtlas*m_pNumberLabel;//显示数字
	vector<TerrainType> m_terrainTypes;
public:
	Card();
	virtual ~Card();
	//创建消耗性卡片，这种卡片不消耗阳光，但是一次性用品
	static Card* createConsumableCard(const std::string &name);
	//正常卡片
	static Card* create(const string&name,int number);

	bool init(const std::string& name);
	bool init(const string&name,int number);

	Sprite*getDisableSprite()const;
	//使当前变暗，仅仅适用于卡片选择场景
	void setDarken();
	void setNeedfulTerrains(const vector<TerrainType>&terrains);
	//是否包含地形
	bool isIncludeTerrain(TerrainType type);

	virtual void setEnabled(bool enabled);

	virtual void update(float dt);
private:
	void setNormalSprite(const string&name);
	void setDisableSprite(const string&name);
};
#endif