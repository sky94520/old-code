#include "CollisionManager.h"

#include "Collision.h"

#include "Player.h"
#include "Enemy.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player*pPlayer)
{
}
void CollisionManager::checkPlayerEnemyCollision(Player*pPlayer,const std::vector<GameObject*> &objects)
{
    SDL_Rect A,B;
    A.x = pPlayer->getPosition().getX();
    A.y = pPlayer->getPosition().getY();
    A.w = pPlayer->getWidth();
    A.h = pPlayer->getHeight();
    for(int i = 0; i< objects.size(); i++)
    {
        B.x = objects[i]->getPosition().getX();
        B.y = objects[i]->getPosition().getY();
        B.w = objects[i]->getWidth();
        B.h = objects[i]->getHeight();
        //如果碰撞
        if(RectRect(&A,&B) == true)
        {
        	pPlayer->collision();
        }
    }
}
void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects)
{
}
void CollisionManager::checkPlayerTileCollision(Player*pPlayer,const std::vector<TileLayer*> &collisionLayers)
{
}
