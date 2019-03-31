#ifndef __OperateLayer_H__
#define __OperateLayer_H__
#include<vector>
#include<android/log.h>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class VirtualStick;
class Button;

class OperateLayerDelegate
{
public:
	virtual ~OperateLayerDelegate(){}
	virtual void degreeUpdate(const Point&degree)=0;
	virtual void wantShooting()=0;
};
class OperateLayer:public Layer
{
private:
	VirtualStick*m_pStick;
	Button*m_pAtkItem;
	OperateLayerDelegate*m_pDelegate;
public:
	OperateLayer();
	~OperateLayer();
	CREATE_FUNC(OperateLayer);
	bool init();

	virtual void onTouchesBegan(vector<Touch*>,SDL_Event*);
	virtual void onTouchesMoved(vector<Touch*>touch,SDL_Event*);
	virtual void onTouchesEnded(vector<Touch*>,SDL_Event*);

	void updateAtk(Object*sender);
	void setDelegate(OperateLayerDelegate*pDelegate);
};
#endif
