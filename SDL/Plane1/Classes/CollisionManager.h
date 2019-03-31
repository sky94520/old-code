#ifndef __CollisionManager_H__
#define __CollisionManager_H__

#include<vector>
#include "SDL2/SDL.h"

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:
    //player 和 enemyBullet 是否碰撞
    void checkPlayerEnemyBulletCollision(Player*pPlayer);
    //player enemy 是否碰撞
    void checkPlayerEnemyCollision(Player*pPlayer,const std::vector<GameObject*> &objects);
    //enemy 和playerBullets是否碰撞
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    //player 和 collision Layer 是否碰撞
    void checkPlayerTileCollision(Player*pPlayer,const std::vector<TileLayer*> &collisionLayers);
};
#endif
