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
	Consumable,//����Ʒ
};
#define CARD_DISABLE_SPRITE_TAG 1
#define CARD_NORMAL_SPRITE_TAG 2
#define CARD_NUMBER_LABEL_TAG 3
#define CARD_CD_TIMER_TAG 4
/*ר������ֲ�￨Ƭ�ͽ�ʬ��Ƭ*/
class Card : public MenuItem
{
	SDL_SYNTHESIZE(CardType,m_type,CardType);//��Ƭ����

	SDL_SYNTHESIZE(float,m_fCurCD,CurCD);//��ǰcd
	SDL_SYNTHESIZE(float,m_fCD,CD);//��ȴʱ��
	SDL_SYNTHESIZE(int,m_nWorth,Worth);//����
	SDL_SYNTHESIZE(std::string,m_description,Description);//����
	SDL_SYNTHESIZE(std::string,m_cardName,CardName);//��Ƭ����
	SDL_SYNTHESIZE(string,m_necessoryItem,NecessoryItem);
	SDL_SYNTHESIZE(ActiveTime,m_activeTime,ActiveTime);
private:
	Sprite*m_pNormalSprite;//������ͼƬ
	Sprite*m_pDisableSprite;//�޷������ͼƬ
	ProgressTimer*m_pCDTimer;//��ʾcd
	LabelAtlas*m_pNumberLabel;//��ʾ����
	vector<TerrainType> m_terrainTypes;
public:
	Card();
	virtual ~Card();
	//���������Կ�Ƭ�����ֿ�Ƭ���������⣬����һ������Ʒ
	static Card* createConsumableCard(const std::string &name);
	//������Ƭ
	static Card* create(const string&name,int number);

	bool init(const std::string& name);
	bool init(const string&name,int number);

	Sprite*getDisableSprite()const;
	//ʹ��ǰ�䰵�����������ڿ�Ƭѡ�񳡾�
	void setDarken();
	void setNeedfulTerrains(const vector<TerrainType>&terrains);
	//�Ƿ��������
	bool isIncludeTerrain(TerrainType type);

	virtual void setEnabled(bool enabled);

	virtual void update(float dt);
private:
	void setNormalSprite(const string&name);
	void setDisableSprite(const string&name);
};
#endif