#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class BrickLayer;

class GameScene:public Scene
{
private:
	BrickLayer*m_pBrickLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	void update(float dt);
private:
	bool initPhysicalWorld();//初始化物理世界
};
#endif