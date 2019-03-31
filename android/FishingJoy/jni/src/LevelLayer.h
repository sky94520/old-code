#ifndef __LevelLayer_H__
#define __LevelLayer_H__
#include<vector>
#include<string>

#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

class LevelLayer:public SDL::Layer
{
	SDL_SYNTHESIZE(int,m_nRatio,Ratio);//��ǰ�ؿ��ı���
	SDL_SYNTHESIZE(float,m_fTax,Tax);//��ǰ˰ֵ
private:
	vector<int> m_netGunLevelIDs;//��ǹid����
	vector<int> m_fishIDs;//���id����
	vector<int> m_fishTideIDs;//�㳱��id����
	vector<float> m_starFishStartTimes;

	TMXTiledMap*m_pTiledMap;
public:
	LevelLayer();
	~LevelLayer();
	static LevelLayer*create(const string&levelName);
	bool initWithLevelName(const string&levelName);

	vector<int>& getShownFishIdVec();
	vector<int>& getNetGunBulletVec();
	vector<int>& getFishTideVec();
	vector<float>& getStartFishStartTimeVec();

	string getBGM();
private:
	void parseFishID();
	void parseNetGun();
	void parseFishTide();
	void parseStarFishStartTime();

	template<typename T>
	void parse(const string&src,const string&token,vector<T>&vect);
};
#endif