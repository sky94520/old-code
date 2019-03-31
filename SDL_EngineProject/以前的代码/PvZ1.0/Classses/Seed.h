#ifndef __Seed_H__
#define __Seed_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Plant;
class Seed : public Node
{
private:
	Sprite*m_pNormalSprite;//������ͼƬ
	Sprite*m_pDisabledSprite;//�޷������ͼƬ
	LoadingBar* m_pLoadingBar;//��ʾcd
	bool m_bFinished;//cd�Ƿ����

	SDL_SYNTHESIZE(float,m_fCurCD,CurCD);//��ǰcd
	SDL_SYNTHESIZE(float,m_fSeedCD,SeedCD);//��ȴʱ��
	SDL_SYNTHESIZE(int,m_nWorth,Worth);//����
	SDL_SYNTHESIZE(std::string,m_description,Description);//����
	SDL_SYNTHESIZE(std::string,m_name,Name);//����
public:
	Seed();
	virtual ~Seed();
	static Seed* create(const std::string &name);
	bool init(const std::string& name);

	Plant*createPlant();//��ֲֲ��
	//�����Ƿ���Ե��
	bool canClicked()const;

	virtual void update(float dt);
private:
	void updateSelf(Object*);//���
};
#endif