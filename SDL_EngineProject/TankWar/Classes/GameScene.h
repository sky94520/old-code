#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
USING_NS_SDL;

class EventLayer;
class TankLayer;
enum class Direction;

class GameScene : public Scene
{
	SDL_SYNTHESIZE_READONLY(EventLayer*, m_pEventLayer, EventLayer);
	SDL_SYNTHESIZE_READONLY(TankLayer*, m_pTankLayer, TankLayer);
private:
	static GameScene* s_pInstance;
private:
	GameScene();
	~GameScene();
	bool init();
public:
	static GameScene* getInstance();
	static void purge();

	void update(float dt);
	//�����ƶ�
	void moveBegin(Direction direction);
	void moveEnd();
	void fire();
private:
	//������Դ
	void preloadResources();
};

#endif