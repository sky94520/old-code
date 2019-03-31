#ifndef __GameObject_H__
#define __GameObject_H__
#include<memory>

#include "LoaderParams.h"
class GameObject
{
 public:
	virtual bool load(std::unique_ptr<LoaderParams> pParams) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;
};
#endif