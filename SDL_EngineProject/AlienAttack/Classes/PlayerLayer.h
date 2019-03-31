#ifndef __PlayerLayer_H__
#define __PlayerLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Player;
class PlayerLayerDelegate
{
public:
	virtual ~PlayerLayerDelegate(){}
	virtual void gameOver()=0;
};
class PlayerLayer:public Layer
{
private:
	Player*m_pPlayer;
	PlayerLayerDelegate*m_pDelegate;
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();

	void update(float dt);
	void playerMove(const Point&velocity);
	//��������
	void resetPlayer();

	Player*getPlayer();
	void setDelegate(PlayerLayerDelegate*pDelegate);
private:
	void ressurect();//��������
};
#endif