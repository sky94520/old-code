#ifndef __Seed_H__
#define __Seed_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Plant;
class Seed : public Node
{
private:
	Sprite*m_pNormalSprite;//正常的图片
	Sprite*m_pDisabledSprite;//无法点击的图片
	LoadingBar* m_pLoadingBar;//显示cd
	bool m_bFinished;//cd是否完成

	SDL_SYNTHESIZE(float,m_fCurCD,CurCD);//当前cd
	SDL_SYNTHESIZE(float,m_fSeedCD,SeedCD);//冷却时间
	SDL_SYNTHESIZE(int,m_nWorth,Worth);//花费
	SDL_SYNTHESIZE(std::string,m_description,Description);//描述
	SDL_SYNTHESIZE(std::string,m_name,Name);//名称
public:
	Seed();
	virtual ~Seed();
	static Seed* create(const std::string &name);
	bool init(const std::string& name);

	Plant*createPlant();//种植植物
	//返回是否可以点击
	bool canClicked()const;

	virtual void update(float dt);
private:
	void updateSelf(Object*);//检查
};
#endif