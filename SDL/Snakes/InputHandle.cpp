#include "InputHandle.h"
#include "Game.h"

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
        if (SDL_WINDOWEVENT_SIZE_CHANGED)
             TheGame::Instance()->updateWindowSize();
        /**更新按键*/
        switch(event.type)
        {
            ///exit
            case SDL_QUIT:
            TheGame::Instance()->quit();
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
            case SDL_FINGERDOWN:
            addTouchState(event);
            break;
            case SDL_FINGERMOTION:
            changeTouchState(event);
            break;
            case SDL_FINGERUP:
            removeTouchState(event);
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
//private end
bool InputHandle::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}
void InputHandle::reset()
{
    for(int i = 0;i < m_mouseButtonStates.size();i++)
    {
        m_mouseButtonStates[i] = false;
    }
}
//private
void InputHandle::addTouchState(SDL_Event &event)
{
    Touch touchState;
    touchState.type = SDL_FINGERDOWN;
    touchState.id = event.tfinger.fingerId;
    touchState.x = event.tfinger.x;
    touchState.y = event.tfinger.y;

    m_vTouchStates.push_back(touchState);
}
void InputHandle::changeTouchState(SDL_Event &event)
{
    //匹配是哪个"手指改变了状态"
    SDL_FingerID id = event.tfinger.fingerId;
    for (int i = 0; i < m_vTouchStates.size();i++)
    {
        if (m_vTouchStates[i].id == id)
        {
            m_vTouchStates[i].type = SDL_FINGERMOTION;
            m_vTouchStates[i].x = event.tfinger.x;
            m_vTouchStates[i].y = event.tfinger.y;
        }
    }
}
void InputHandle::removeTouchState(SDL_Event &event)
{
     SDL_FingerID id = event.tfinger.fingerId;
     std::vector<Touch>::iterator it;

     for (it = m_vTouchStates.begin();it != m_vTouchStates.end();)
     {
         if (it->id == id)
         {
             m_vTouchStates.erase(it);
             it = m_vTouchStates.begin();
         }
         else
         it++;
     }

}
//private end
//public
const std::vector<Touch>& InputHandle::getTouchStates()
{
    return m_vTouchStates;
}
