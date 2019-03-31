#ifndef __SeedLayer_H__
#define __SeedLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Seed;
class SeedLayer:public Node
{
private:
	int m_selectedIndex;//��ǰѡ����
	Vector<Seed*> m_seeds;//���Ӱ�
	Sprite*m_pSelectedHigh;//ѡ�и���
public:
	SeedLayer();
	~SeedLayer();
	CREATE_FUNC(SeedLayer);
	bool init();
	virtual void update(float dt);
	//������Ӱ�
	bool addSeed(const std::string &name);
	//�Ƴ����Ӱ�
	void removeSeed(const std::string &name);
	//���õ�ǰѡ������޲�������false
	bool setSelectedSeed(const Point&pos);
	//��ȡ��ǰѡ�е����Ӱ�
	Seed*getSelectedSeed();
	//���ѡ��
	void clearClickHigh();
private:
	Seed*getItemForTouch(Touch*touch);
};
#endif