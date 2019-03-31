#ifndef __GameStateMachine_H__
#define __GameStateMachine_H__
#include<vector>
/*用到unique_ptr*/
#include<memory>

#include "GameState.h"

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
#endif