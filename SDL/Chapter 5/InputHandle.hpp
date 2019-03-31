#include "SDL2/SDL.h"
#include "Vector2D.hpp"

#pragma once

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};
class InputHandle
{
private:
    InputHandle();
    ~InputHandle();

    static InputHandle*s_pInstance;

    std::vector<bool> m_mouseButtonStates;

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
public:
    static InputHandle*Instance();

    void update();
    void clean();
    ///判断某一案件是否按下
    bool isKeyDown(SDL_Scancode key);
    Vector2D*getMousePosition();
};
typedef InputHandle TheInputHandle;
InputHandle*InputHandle::s_pInstance = NULL;

InputHandle*InputHandle::Instance()
{
    if(s_pInstance == NULL)
    {
        s_pInstance = new InputHandle();
    }
    return s_pInstance;
}
///构造函数
InputHandle::InputHandle():m_keystates(SDL_GetKeyboardState(0))
{
    for(int i = 0;i < 3;i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    ///分配内存
    m_mousePosition = new Vector2D();
}
InputHandle::~InputHandle()
{
    delete m_mousePosition;
}
void InputHandle::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        /**更新按键*/
        switch(event.type)
        {
            ///exit
            case SDL_QUIT:
            Game::Instance()->quit();
            break;
            ///Mouse motion
            case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
            ///Mouse Button
            case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
            case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
            ///Keyboard
            case SDL_KEYDOWN:
            onKeyDown();
            break;
            case SDL_KEYUP:
            onKeyUp();
            break;
            default:
            break;
        }
    }
}
void InputHandle::clean()
{
}
Vector2D*InputHandle::getMousePosition()
{
    return m_mousePosition;
}
bool InputHandle::isKeyDown(SDL_Scancode key)
{
    if(m_keystates != NULL)
    {
        if(m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
///private
void InputHandle::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}
void InputHandle::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}
void InputHandle::onMouseButtonDown(SDL_Event&event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}
void InputHandle::onMouseButtonUp(SDL_Event&event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}
void InputHandle::onMouseMove(SDL_Event&event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}
