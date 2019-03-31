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
    ///����
    const Uint8*m_keystates;
public:
    static InputHandle*Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new InputHandle();
        }
        return s_pInstance;
    }
    void update();
    void clean();
    Vector2D * getMousePosition();
    bool getMouseButtonState(mouse_buttons buttonNumber);
    ///��������
    bool isKeyDown(SDL_Scancode key);

};
typedef InputHandle TheInputHandle;
InputHandle*InputHandle::s_pInstance = NULL;
///���캯��
InputHandle::InputHandle():m_keystates(SDL_GetKeyboardState(0))
{
    for(int i = 0;i < 3;i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    ///�����ڴ�
    m_mousePosition = new Vector2D();
    ///��ð���
    ///m_keystates = SDL_GetKeyboardState(0);
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
        ///quit
        if(event.type == SDL_QUIT)
        {
            Game::Instance()->quit();
            return ;
        }
        ///button
        if(event.type == SDL_MOUSEBUTTONDOWN)
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
        if(event.type == SDL_MOUSEBUTTONUP)
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
        ///move
        if(event.type == SDL_MOUSEMOTION)
        {
            m_mousePosition->setX(event.motion.x);
            m_mousePosition->setY(event.motion.y);
        }

    }
}
Vector2D * InputHandle::getMousePosition()
{
    return m_mousePosition;
}
bool InputHandle::getMouseButtonState(mouse_buttons buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}
void InputHandle::clean()
{
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
