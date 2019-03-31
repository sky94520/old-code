#ifndef __PhysicalEngine_H__
#define __PhysicalEngine_H__
#include<vector>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;
using namespace std;

class GLESDebugDraw;
class Fish;
class Fork;
class PhysicalEngine:public Ref
{
private:
	static PhysicalEngine*m_pInstance;

	b2World*m_pWorld;
	GLESDebugDraw*m_pDebugDraw;
public:
	static const int PTM_RATIO;
public:
	PhysicalEngine();
	~PhysicalEngine();
	static PhysicalEngine*getInstance();
	void purge();
	bool init();
	void update(float time);
	void SetContactListener(b2ContactListener*listener);
	//为鱼绑定物体
	void bindBodyForFish(Fish*pFish);
	//为鱼绑定惊吓物体
	void bindScaredBodyForFish(Fish*pFish);
	//为叉子绑定物体
	void bindBodyForFork(Fork*pFork);

	void debugDraw();
};
#endif