#ifndef __HandleKey_H__
#define __HandleKey_H__
enum KEY
{
    ///��������
    PLAYER_PROPERTY = 0,
    //������
    UP = 2,LEFT = 4,RIGHT = 6,DOWN = 8
};
class HandleKey
{
private:
  char key;
public:
  HandleKey();
  ~HandleKey();
  //��ⰴ��
  void getKey();
  //������
  KEY judgeKey();
};
#endif
