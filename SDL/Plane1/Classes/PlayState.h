#ifndef __PlayState_H__
#define __PlayState_H__

#include<iostream>
#include<vector>
#include<memory>
#include<stdexcept>

#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "LevelParser.h"
#include  "CollisionManager.h"
//class GameObject;

class PlayState:public GameState
{
  private:
	static const std::string s_playID;
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
	~PlayState(){delete pLevel;}
};
#endif
