#ifndef __GameState_H__
#define __GameState_H__

#include<string>
class GameState
{
  protected:
  /*保存状态机资源id，便于资源释放*/
    std::vector<std::string> m_textureIDList;
  public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
};
#endif