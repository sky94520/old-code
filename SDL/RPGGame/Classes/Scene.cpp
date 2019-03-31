#include "Scene.h"

Player*Scene::m_player = NULL;
Scene::Scene()
{
    this->m_isAlive = true;
    this->m_player = NULL;
    //给地图初始化为0
    for (int i = 0;i < W;i++)
    for (int j = 0;j < H;j++)
    m_map[i][j] = '\0';
}
Scene::~Scene()
{

}
Scene*Scene::create()
{
    Scene*scene = new Scene();
    if (scene != NULL && scene->init())
    return scene;

    return NULL;
}
bool Scene::init()
{
    return true;
}
void Scene::update()
{
}
bool Scene::isAlive()
{
	return this->m_isAlive;
}
void Scene::setAlive(bool alive)
{
	this->m_isAlive = alive;
}
void Scene::bindPlayer(Player*iPlayer)
{
	m_player = iPlayer;
}
void Scene::draw()
{
	if (this->m_player != NULL)
	{
		//画出人物
		gotoXY(m_player->getPositionX(),m_player->getPositionY());
	    printf("%c",m_player->getSprite());
	}
}
