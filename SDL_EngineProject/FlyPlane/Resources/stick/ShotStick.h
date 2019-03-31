#pragma once

#include<cmath>

#include "SDL2/SDL.h"
#include "GameObject.h"
#include "Vector2D.h"

#define PI 3.1415926

typedef struct Cicrcle
{
	int x;
	int y;
	double radius;
}Circle;
typedef struct Point
{
	double x;
	double y;
}Point;
/*虚拟摇杆*/
class ShotStick : public GameObject
{
 private:
 //外圆
    Circle m_outCircle;
    //内方形
    Circle m_inCircle;
    //有效相对于圆心触屏坐标,
    Point m_relativePoint;
    //绑定一个有效的手指
    SDL_FingerID m_fingerId;
    static ShotStick*s_pInstance;
    private:
	ShotStick();
	public:
	static ShotStick*Instance();
	virtual bool load(LoaderParams*pParams);
	virtual void draw(SDL_Renderer*ren);
	virtual void update();
	virtual void clean();
	
	Vector2D getVelocity();
	/*手指三个状态 按下 移动 放开
	对应三个函数
	*/
};
typedef ShotStick TheShotStick;