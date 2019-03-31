#pragma once

#include "SDLGameObject.h"
#include "InputHandle.h"
#include "GameObjectFactory.h"

class Player:public SDLGameObject
{
  private:
    void handleInput();
  public:
    Player();
    ~Player();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams*pParams);
};
class PlayerCreator : public BaseCreator
{
  public:
    PlayerCreator(){}
    GameObject* createGameObject() const
    {
        return new Player();
    }
};
