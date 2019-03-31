#ifndef __VillageScene_H__
#define __VillageScene_H__
#include "Scene.h"

class VillageScene : public Scene
{
/*private:
    bool isAlive;*/
public:
    VillageScene();
    ~VillageScene();
    void update();
    virtual bool init();
    static VillageScene*create();

    void draw();
};
#endif
