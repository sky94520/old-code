#include <vector>
#include "GameState.h"

#pragma once
class MenuState:public GameState
{
private:
	static const std::string s_menuID;
	//std::vector<GameObject*> m_gameObjects;
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
	TheErrorInfo::Instance()->log("entering MenuState");
	return true;
}
bool MenuState::onExit()
{
	TheErrorInfo::Instance()->log("exiting MenuState");
	return true;
}
