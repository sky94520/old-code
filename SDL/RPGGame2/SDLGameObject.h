#pragma once

#include "GameObject.h"
#include "TextureManager.h"
#include "Vector2D.h"

class Game;

class SDLGameObject:public GameObject
{
  protected:
  //坐标
	Vector2D m_position;
	//速度
	Vector2D m_velocity;
	//加速度
	Vector2D m_acceleration;

	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;

	int m_numFrames;
//  private:

  public:
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams*pParams);

	SDLGameObject();
	virtual ~SDLGameObject();

    Vector2D& getPosition()
	{
	    return m_position;
	}
	int getWidth(){return m_width;}
	int getHeight(){return m_height;}
};
