#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"

class Game;
#pragma once
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
   public:
	  SDLGameObject(const LoaderParams * pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
};