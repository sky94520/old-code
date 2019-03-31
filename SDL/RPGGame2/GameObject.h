#include "LoaderParams.h"

#pragma once
class GameObject
{
  public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load(const LoaderParams*pParams) = 0;

	virtual ~GameObject(){}
  protected:
	GameObject(){}
};
