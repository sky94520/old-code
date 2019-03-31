#include "GameState.h"
#pragma once
class MenuState:public GameState
{
private:
	static const std::string s_menuID;
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const
	{
		return s_menuID;
	}
};
const std::string MenuState::s_menuID = "MENU";
void MenuState::update()
{
}
void MenuState::render()
{
}
bool MenuState::onEnter()
{
	std::cout<<"entering MenuState"<<std::endl;
	return true;
}
bool MenuState::onExit()
{
	std::cout<<"exiting MenuState"<<std::endl;
	return true;
}
