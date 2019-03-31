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
    std::vector<PlayerBullet*> & getPlayerBullets()
    {
    	return m_playerBullets;
    }
    std::vector<EnemyBullet*>& getEnemyBullets()
    {
    	return m_enemyBullets;
    }
    void clearBullets()
    {
    	for(unsigned i = 0;i < m_playerBullets.size();i++)
    	{
    		delete m_playerBullets[i];
    	}
    	m_playerBullets.clear();
    	for(unsigned i = 0;i < m_enemyBullets.size();i++)
    	{
    		delete m_enemyBullets[i];
    	}
    	m_enemyBullets.clear();
    }

};
typedef BulletHandle TheBulletHandle;
#endif
