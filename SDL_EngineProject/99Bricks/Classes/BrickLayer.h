#ifndef __BrickLayer_H__
#define __BrickLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Box2D/Box2D.h"

using namespace SDL;
using namespace std;
class Brick;
class BrickLayer:public Layer
{
private:
	vector<bool [9]> m_bricks;
public:
	BrickLayer();
	~BrickLayer();
	CREATE_FUNC(BrickLayer);
	bool init();
private:
	Brick*createBrick(bool arrays[9]);
};
#endif