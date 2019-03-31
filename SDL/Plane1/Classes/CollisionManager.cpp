#include "CollisionManager.h"
#include "BulletHandle.h"
#include "Collision.h"
#include "TileLayer.h"

#include "Player.h"
#include "Enemy.h"

/**player enemy bullet*/
void CollisionManager::checkPlayerEnemyBulletCollision(Player*pPlayer)
{
	///player rect
	SDL_Rect rect1 = {(int)pPlayer->getPosition().getX(),(int)pPlayer->getPosition().getY(),pPlayer->getWidth(),pPlayer->getHeight()};
	SDL_Rect rect2;
	for(unsigned int i = 0;i < TheBulletHandle::Instance()->getEnemyBullets().size();i++)
	{
		EnemyBullet*enemyBullet = TheBulletHandle::Instance()->getEnemyBullets()[i];

		rect2.x = (int)enemyBullet->getPosition().getX();
		rect2.y = (int)enemyBullet->getPosition().getY();
		rect2.w = enemyBullet->getWidth();
		rect2.h = enemyBullet->getHeight();
		if(RectRect(&rect1,&rect2))
		{
			pPlayer->collision();
			enemyBullet->collision();
		}
	}
}
/**player  enemy*/
void CollisionManager::checkPlayerEnemyCollision(Player*pPlayer,const std::vector<GameObject*> &objects)
{
    SDL_Rect A,B;
    A.x = pPlayer->getPosition().getX();
    A.y = pPlayer->getPosition().getY();
    A.w = pPlayer->getWidth();
    A.h = pPlayer->getHeight();

    //std::cout<<"A.x "<<A.x<<" A.y "<<A.y<<" A.w"<<A.w<<" A.h"<<A.h<<std::endl;

    for(unsigned int i = 1; i< objects.size(); i++)
    {
        B.x = objects[i]->getPosition().getX();
        B.y = objects[i]->getPosition().getY();
        B.w = objects[i]->getWidth();
        B.h = objects[i]->getHeight();
        //std::cout<<"B.x "<<B.x<<" B.y "<<B.y<<" B.w"<<B.w<<" B.h"<<B.h<<std::endl;

        //如果碰撞
        if(RectRect(&A,&B) == true)
        {
        	std::cout<<"player enemy is collisioned!\n";
        	pPlayer->collision();
        }
    }
}
/**enemy and player bullet*/
void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects)
{
    for(unsigned int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];

        for(unsigned int j = 0; j < TheBulletHandle::Instance()->getPlayerBullets().size(); j++)
        {
            if(pObject->type() != std::string("Enemy") )///|| !pObject->updating())
            {
                continue;
            }

            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = pObject->getPosition().getX();
            pRect1->y = pObject->getPosition().getY();
            pRect1->w = pObject->getWidth();
            pRect1->h = pObject->getHeight();

            PlayerBullet* pPlayerBullet = TheBulletHandle::Instance()->getPlayerBullets()[j];

            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = pPlayerBullet->getPosition().getX();
            pRect2->y = pPlayerBullet->getPosition().getY();
            pRect2->w = pPlayerBullet->getWidth();
            pRect2->h = pPlayerBullet->getHeight();

            if(RectRect(pRect1, pRect2))
            {
                if(!pObject->dying() && !pPlayerBullet->dying())
                {
                	std::cout<<"player bullet and enemy is collided!\n";
                    pPlayerBullet->collision();
                    pObject->collision();
                }

            }

            delete pRect1;
            delete pRect2;
        }
    }
}
void CollisionManager::checkPlayerTileCollision(Player*pPlayer,const std::vector<TileLayer*> &collisionLayers)
{
	///iterate through collision layers
	for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin();it != collisionLayers.end();++it)
	{
		TileLayer*pTileLayer = (*it);
		std::vector<std::vector<int> > tiles = pTileLayer->getTileIDs();
		///get this layers position
		Vector2D layerPos = pTileLayer->getPosition();

		int x,y,tileColumn,tileRow,tileid = 0;
		///calculate position on tile map
		x = layerPos.getX()/pTileLayer->getTileSize();
		y = layerPos.getY()/pTileLayer->getTileSize();
		///if moving forward or upwards
		if(pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
		{
			tileColumn = (pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize();
			tileRow = (pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];
		}
		///if moving backwards or downwards
		else if(pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
		{
			tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
			tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
		}
		if(tileid != 0)
		{
			pPlayer->collision();
		}
	}
}
