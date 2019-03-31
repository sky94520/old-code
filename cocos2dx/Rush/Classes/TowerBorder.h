#ifndef __TowerBorder_H__
#define __TowerBorder_H__
#include "Entity.h"
#include "Hero.h"
class TowerBorder : public Entity
{
/*private:
	CustomCommand _customCommand;*/
private:
	Hero*m_pHero;
public:
	TowerBorder();
	~TowerBorder();

	CREATE_FUNC(TowerBorder);
	virtual bool init();
	//Éý¼¶
	void upgrade();
public:
	bool isClickMe(Point pos);
	void bindHero(Hero*hero);
	Hero*getHero();
	void deleteHero();
/*private:
	void onDraw(const kmMat4 &transform,bool transformUpdated);
	void draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags);*/
};
#endif