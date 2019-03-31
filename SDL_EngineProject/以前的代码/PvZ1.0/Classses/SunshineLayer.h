#ifndef __SunshineLayer_H__
#define __SunshineLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Sunshine.h"

using namespace SDL;
class Sunshine;
typedef enum SunshineRoute
{
	kSunshineRoute_line,//笔直落下，如白天
	kSunshineRoute_jump//跳着落下，如向日葵
};
class SunshineLayer:public Layer
{
private:
	Vector<Sunshine*> m_sunshines;
public:
	SunshineLayer();
	~SunshineLayer();
	CREATE_FUNC(SunshineLayer);
	bool init();

	virtual void update(float dt);
public:
	void produceSunshine(const Point&startPos,SunshineType type,SunshineRoute route);
	bool collectSunshine(const Point&pos);//收集太阳光
};
#endif