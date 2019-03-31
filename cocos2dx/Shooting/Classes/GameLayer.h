#ifndef __GameLayer_H__
#define __GameLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class Player;
class Arrow;
class GameLayerDelegate
{
public:
	virtual ~GameLayerDelegate(){}
	virtual ValueMap getObject(const std::string&name)=0;
};
class GameLayer:public Layer
{
private:
	Player*m_pPlayer;
	Arrow*m_pArrow;
	GameLayerDelegate*m_pDelegate;
public:
	GameLayer();
	~GameLayer();
	static GameLayer*create(GameLayerDelegate*pDelegate);
	bool init(GameLayerDelegate*pDelegate);

	void aimAt(const Point&pos);
	void shootTo(const Point&pos);
	Arrow*getArrow()const;
};
#endif