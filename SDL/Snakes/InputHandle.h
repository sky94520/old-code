#ifndef __InputHandle_H__
#define __InputHandle_H__
#include<vector>

#include "SDL2/SDL.h"
#include "Vector2D.h"

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};
typedef struct Touch
{
    /*坐标,0-1*/
    float x;
    float y;
    /*id*/
    SDL_FingerID id;
    /*触屏类型*/
    int type;
}Touch;
class InputHandle
{
private:
    InputHandle();
    ~InputHandle();

    static InputHandle*s_pInstance;
    //鼠标按键状态
    std::vector<bool> m_mouseButtonStates;
    //触屏状态
    std::vector<Touch> m_vTouchStates;
    
    Vector2D *m_mousePosition;
    ///按键 keyboard specific
    const Uint8*m_keystates;
private:
    ///按键处理 keyboard events
    void onKeyDown();
    void onKeyUp();
    ///handle mouse events
    void onMouseMove(SDL_Event&event);
    void onMouseButtonDown(SDL_Event&event);
    void onMouseButtonUp(SDL_Event&event);
    //触屏状态
    void addTouchState(SDL_Event &event);
    void changeTouchState(SDL_Event &event);
    void removeTouchState(SDL_Event &event);
public:
    static InputHandle*Instance();

    void update();
    void clean();
    ///判断某一案件是否按下
    bool isKeyDown(SDL_Scancode key);
    Vector2D*getMousePosition();
    bool getMouseButtonState(int buttonNumber);
    //reset the mouse button states to false
    void reset();
    //获得触屏信息api
    const std::vector<Touch>& getTouchStates();
};
typedef InputHandle TheInputHandle;
#endif