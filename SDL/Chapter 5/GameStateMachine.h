#include<vector>
#include "GameState.h"

#pragma once
class GameStateMachine
{
	private:
	std::vector<GameState*> m_gameStates;
  public:
	void pushState(GameState * pState);
	void changeState(GameState * pState);
	void popState();

	void update();
	void render();
};
