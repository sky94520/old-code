#include "TollgateScene.h"
#include "Player.h"
//#include "SimpleMoveController.h"
#include "ThreeDirectionController.h"

Scene* TollgateScene::createScene() 
{
    auto scene = Scene::create();
    auto layer = TollgateScene::create();
    scene->addChild(layer);

    return scene;
}

bool TollgateScene::init() 
{
    if (!Layer::init())
    {
        return false;
    }
    /* �����ͼ���ֺڱߣ�����ʹ���������� */
    Director::getInstance()->setProjection(Director::Projection::_2D);

    /* ����Tiled��ͼ����ӵ������� */
    TMXTiledMap* map = TMXTiledMap::create("map/level01.tmx"); 
	if(map == NULL)
		return false;

	addPlayer(map);
	
    this->addChild(map);


    return true;
}
void TollgateScene::addPlayer(TMXTiledMap*map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite*playerSprite = Sprite::create("player.png");

	//������󶨵���Ҷ�����,������Player����ʵ��run����()
	Player*mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);

	mPlayer->run();
	mPlayer->setTiledMap(map);
		/*��Ҽ��ƶ�*/
	auto*moveControll = ThreeDirectionController::create();
	moveControll->setiXSpeed(1);
	moveControll->setiYSpeed(0);
	//������Ҫ��ӵ������в��ܻ��update�¼�
	this->addChild(moveControll);
	//���ÿ�����������
	mPlayer->setController(moveControll);
	//���ض����
	TMXObjectGroup*objGroup = map->getObjectGroup("objects");
	//�����������
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();

	mPlayer->setPosition(Point(playerX,playerY));
	map->addChild(mPlayer);
	

}
