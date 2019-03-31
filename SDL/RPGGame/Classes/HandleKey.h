#ifndef __HandleKey_H__
#define __HandleKey_H__
enum KEY
{
    ///人物属性
    PLAYER_PROPERTY = 0,
    //处理按键
    UP = 2,LEFT = 4,RIGHT = 6,DOWN = 8
};
class HandleKey
{
private:
  char key;
public:
  HandleKey();
  ~HandleKey();
  //检测按键
  void getKey();
  //处理按键
  KEY judgeKey();
};
#endif
