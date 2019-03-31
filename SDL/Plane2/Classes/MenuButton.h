#ifndef __MenuButton_H__
#define __MenuButton_H__

#include "ShooterObject.h"
#include "InputHandle.h"
#include "GameObjectFactory.h"

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};
class MenuButton : public ShooterObject
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
	virtual void load(std::unique_ptr<LoaderParams> const&pParams);

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
#endif
