#ifndef __TankLayer_H__
#define __TankLayer_H__

#include <vector>
#include "SDL_Engine/SDL_Engine.h"
USING_NS_SDL;
using namespace std;

class Tank;

class TankLayer : public Layer
{
private:
	//保存坦克集合，规定 0为主角
	vector<Tank*> m_tanks;
public:
	TankLayer();
	~TankLayer();
	CREATE_FUNC(TankLayer);
	bool init();

	Tank* getPlayer() const {return m_tanks.front();}
};

#endif