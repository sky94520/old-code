#ifndef __Command_H__
#define __Command_H__
#include "SDL_Engine/SDL_Engine.h"
#include<vector>
using namespace SDL;
using namespace std;

class Brick;
class Command
{
public:
	virtual ~Command(){}
	virtual void execute()=0;
	virtual void undo()=0;
};
//-------------------LeftCommand---------------------------------
class LeftCommand:public Command
{
private:
	Brick*m_pBrick;
	Point m_prePosition;
public:
	LeftCommand(Brick*pBrick);
	virtual void execute();
	virtual void undo();
};
//-------------------RightCommand---------------------------------
class RightCommand:public Command
{
private:
	Brick*m_pBrick;
	Point m_prePosition;
public:
	RightCommand(Brick*pBrick);
	virtual void execute();
	virtual void undo();
};
//------------------TransformCommand-------------------------------
class TransformCommand:public Command
{
private:
	Brick*m_pBrick;
	int m_nPreIndex;
public:
	TransformCommand(Brick*pBrick);
	virtual void execute();
	virtual void undo();
};
#endif