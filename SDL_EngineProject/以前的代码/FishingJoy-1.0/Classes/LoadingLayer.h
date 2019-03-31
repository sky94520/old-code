#ifndef __LoadingLayer_H__
#define __LoadingLayer_H__
#include<vector>
#include<map>
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class LoadingLayer:public Layer
{
private:
	std::map<std::string,std::vector<std::string>*> m_resources;
	std::map<std::string,std::vector<std::string>*>::iterator m_iterMap;
	int m_allIndex;
	int m_curIndex;

	LoadingBar*m_pLoadingBar1;
	LoadingBar*m_pLoadingBar2;
public:
	LoadingLayer();
	~LoadingLayer();
	static Scene*createScene();
	CREATE_FUNC(LoadingLayer);
	bool init();
	virtual void update(float dt);
};
#endif