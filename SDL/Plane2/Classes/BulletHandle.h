#ifndef __BulletHandle_H__
#define __BulletHandle_H__

#include<vector>

#include "Bullet.h"

class BulletHandle
{
private:
    static BulletHandle*s_pInstance;
    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
public:
    static BulletHandle*Instance()
    {
        if(s_pInstance == NULL)
            s_pInstance = new BulletHandle();
        return  s_pInstance;
    }
    BulletHandle() {}
    void update();
    void draw();
    void clean();

    void addPlayerBullet(int x,int y,int width,int height,std::string textureID,int numFrames,Vector2D heading);
    void addEnemyBullet(int x,int y,int width,int height,std::string textureID,int numFrames,Vector2D heading);

};
typedef BulletHandle TheBulletHandle;
#endif
