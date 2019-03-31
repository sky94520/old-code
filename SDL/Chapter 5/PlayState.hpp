#include "GameState.h"
#pragma once
class PlayState:public GameState
{
  private:
	static const std::string s_playID;
  public:
	 virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const
	{
		return s_playID;
	}
};
const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
}
void PlayState::render()
{
}
bool PlayState::onEnter()
{
	std::cout<<"entering PlayState"<<std::endl;
	return true;
}
bool PlayState::onExit()
{
	std::cout<<"exiting PlayState"<<std::endl;
	return true;
}
