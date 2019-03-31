#include "BulletHandle.h"
#include "Game.h"

BulletHandle*BulletHandle::s_pInstance = NULL;
void BulletHandle::update()
{
    for(std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end();)
    {
        if((*p_it)->getPosition().getX() < 0 ||
		(*p_it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
        (*p_it)->getPosition().getY() < 0 ||
		(*p_it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
		(*p_it)->dead())
		{
			delete *p_it;
			p_it = m_playerBullets.erase(p_it);
		}
		else
		{
			(*p_it)->update();
			p_it++;
		}
	}
    for(std::vector<EnemyBullet*>::iterator p_it = m_enemyBullets.begin(); p_it != m_enemyBullets.end();)
    {
        if((*p_it)->getPosition().getX() < 0 ||
		(*p_it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
        (*p_it)->getPosition().getY() < 0 ||
		(*p_it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
		(*p_it)->dead())
		{
			delete *p_it;
			p_it = m_enemyBullets.erase(p_it);
		}
		else
		{
			(*p_it)->update();
			p_it++;
		}
	}
}
void BulletHandle::draw()
{
	for(auto it = m_playerBullets.begin();it != m_playerBullets.end();it++)
	{
		(*it)->draw();
	}
	for(auto it = m_enemyBullets.begin();it != m_enemyBullets.end();it++)
	{
		(*it)->draw();
	}
}
void BulletHandle::clean()
{
	/*Release*/
	for(auto it = m_playerBullets.begin();it != m_playerBullets.end();it++)
	{
		(*it)->clean();
		delete * it;
	}
	for(auto it = m_enemyBullets.begin();it != m_enemyBullets.end();it++)
	{
		(*it)->clean();
		delete * it;
	}
}
void BulletHandle::addPlayerBullet(int x,int y,int width,int height,std::string textureID,int numFrames,Vector2D heading)
{
    PlayerBullet*pPlayerBullet = new PlayerBullet();
    pPlayerBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x,y,width,height,textureID,numFrames)),heading);
    m_playerBullets.push_back(pPlayerBullet);
}
void BulletHandle::addEnemyBullet(int x,int y,int width,int height,std::string textureID,int numFrames,Vector2D heading)
{
    EnemyBullet*pEnemyBullet = new EnemyBullet();
    pEnemyBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x,y,width,height,textureID,numFrames)),heading);
    m_enemyBullets.push_back(pEnemyBullet);
}
