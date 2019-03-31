#ifndef __PlayState_H__
#define __PlayState_H__

#include<iostream>
#include<vector>
//
#include<stdexcept>

#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "LevelParser.h"
//#include  "CollisionManager.h"
//class GameObject;

class PlayState:public GameState
{
  private:
	static const std::string s_playID;
//	CollisionManager m_collisionManager;

	//std::vector<GameObject*> m_gameObjects;

	Level*pLevel;
  public:
	 virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const
	{
		return s_playID;
	}
	bool checkCollision(ShooterObject*p1,ShooterObject*p2);
};
#endif
