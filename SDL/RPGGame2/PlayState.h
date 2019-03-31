#pragma once
#include<iostream>
#include<vector>

#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "LevelParser.h"
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
	bool checkCollision(SDLGameObject*p1,SDLGameObject*p2);
};
