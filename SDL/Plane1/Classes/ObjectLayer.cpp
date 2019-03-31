#include "ObjectLayer.h"
#include "GameObject.h"
#include "Level.h"
#include "Game.h"
#include "Player.h"

void ObjectLayer::render()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}
void ObjectLayer::update(Level*pLevel)
{
    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(),m_gameObjects);
    m_collisionManager.checkEnemyPlayerBulletCollision(m_gameObjects);
    m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
    {
    	m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(),pLevel->getCollidableLayers());
    }
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end();)
    {
        if(!(*it)->dead())
		{
			(*it)->update();
			++it;
		}
        else
		{
			(*it)->clean();
			it = m_gameObjects.erase(it);
		}
    }

}
