#ifndef __Layer_H__
#define __Layer_H__

class Layer
{
  protected:
    virtual ~Layer(){}
  public:
    virtual void render() = 0;
    virtual void update() = 0;
};
#endif
