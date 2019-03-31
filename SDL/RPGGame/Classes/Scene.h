#ifndef __Scene_H__
#define __Scene_H__
#include "Player.h"

#define W 40
#define H 20

class Scene
{
protected:
  bool m_isAlive;
  static Player*m_player;
  char m_map[W][H];
public:
  Scene();
  ~Scene();
  void update();
  static void bindPlayer(Player*iPlayer);
  bool isAlive();
  void setAlive(bool alive);
  //画出人物，怪物 背景
  void draw();
  virtual bool init();
  static Scene*create();
};
#endif
