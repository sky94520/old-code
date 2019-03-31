#ifndef __ChooseLayer_H__
#define __ChooseLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*游戏类型选择界面*/
class ChooseLayer:public Layer
{
private:
	Sprite*m_pBackground;
	Sprite*m_pFloor;
	Sprite*m_pTitle;
public:
	ChooseLayer();
	~ChooseLayer();
	CREATE_FUNC(ChooseLayer);
	static Scene*createScene();
	bool init();
private:
	void startBirdGame(Object*);
	void backToMainLayer(Object*);
};
#endif