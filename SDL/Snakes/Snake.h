#ifndef __Player_H__
#define __Player_H__
#include<vector>

#include "GameObject.h"
#include "Timer.h"
/*蛇节点*/
struct SnakeNode
{
    int x;
    int y;
};
/*蛇头方向*/
enum SNAKE_DIRECTION
{
    HEAD_RIGHT,
    HEAD_DOWN,
    HEAD_LEFT,
    HEAD_UP
};
class Snake : public GameObject
{
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;

    std::string m_textureID;
    std::vector<SnakeNode> m_node;
    //蛇头方向 默认为右
    enum SNAKE_DIRECTION m_headDirection;
    //计时器，每1秒
    Timer m_timer;
 private:
     /*接收并处理事件*/
    bool handleInput();
    public:
    Snake();
    ~Snake();
	virtual bool load(std::unique_ptr<LoaderParams> pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

};
#endif
