
#ifndef __Food_H__
#define __Food_H__
#include "GameObject.h"
#include "Vector2D.h"
class Food:public GameObject 
{
private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;

  std::string m_textureID;
  bool m_bIsExisted;
private:
   void updatePosition();
public:
  Food();
  virtual bool load(std::unique_ptr < LoaderParams > pParams);
  virtual void update();
  virtual void draw();
  virtual void clean();
};
#endif