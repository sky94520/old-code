#pragma once
#include "SDLGameObject.h"
#include "InputHandle.h"
#include "GameObjectFactory.h"

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};
class MenuButton : public SDLGameObject
{
 private:
    void (*m_callback)();
    bool m_bReleased;
    int m_callbackID;
 public:
	MenuButton();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams*pParams);

	void setCallback(void (*callback)()){m_callback = callback;}
	int getCallbackID(){return m_callbackID;}
};
class MenuButtonCreator : public BaseCreator
{
  public:
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};
