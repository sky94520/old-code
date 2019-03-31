#include "VillageScene.h"

VillageScene::VillageScene() : Scene()
{
    this->m_isAlive = true;
}
VillageScene::~VillageScene()
{

}
bool VillageScene::init()
{
    for(int i = 0;i < W;i++)
    {
        m_map[i][0] = '#';
        m_map[i][H - 1] = '#';
    }
    return true;
}
void VillageScene::update()
{
    ///

}
VillageScene*VillageScene::create()
{
    VillageScene*scene = new VillageScene();
    if (scene != NULL && scene->init())
    return scene;

    return NULL;
}
void VillageScene::draw()
{
    ///
    for(int i = 0;i < W ;i++)
    {
        for(int j = 0;j < H ;j++)
        {
            if(m_map[i][j] != '\0')
            {
                gotoXY(i,j);
                cout<<m_map[i][j];
            }
        }
    }
	if (this->m_player != NULL)
	{
		//»­³öÈËÎï
		gotoXY(m_player->getPositionX(),m_player->getPositionY());
	    cout<<m_player->getSprite();
	    }
}
