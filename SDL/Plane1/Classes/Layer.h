#ifndef __Layer_H__
#define __Layer_H__

class Level;

class Layer
{
  protected:
    virtual ~Layer(){}
  public:
    virtual void render() = 0;
    virtual void update(Level*pLevel) = 0;
};
#endif
