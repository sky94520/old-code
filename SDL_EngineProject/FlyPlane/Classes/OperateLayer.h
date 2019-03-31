#ifndef __OperateLayer_H__
#define __OperateLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class VirtualStick;
class Button;
class OperateLayerDelegate
{
public:
	~OperateLayerDelegate(){}
	//弧度，速度的比[0,1]
	virtual void degreeUpdate(float degree,float speed)=0;
	virtual void shooting()=0;
};
class OperateLayer:public Layer
{
private:
	VirtualStick*m_pStick;
	Button*m_pAtkItem;

	Sprite*m_pHero;
	bool m_bUpdated;
	float m_degree;
public:
	OperateLayer();
	~OperateLayer();
	CREATE_FUNC(OperateLayer);
	bool init();
	void update(float dt);

	virtual void onTouchesBegan(vector<Touch*>,SDL_Event*);
	virtual void onTouchesMoved(vector<Touch*>touch,SDL_Event*);
	virtual void onTouchesEnded(vector<Touch*>,SDL_Event*);

	void updateAtk(Object*sender);
};
#endif