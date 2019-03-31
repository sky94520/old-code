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
    /* 如果地图出现黑边，尝试使用这句代码解决 */
    Director::getInstance()->setProjection(Director::Projection::_2D);

    /* 加载Tiled地图，添加到场景中 */
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

	//将精灵绑定到玩家对象上,方便在Player类中实现run函数()
	Player*mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);

	mPlayer->run();
	mPlayer->setTiledMap(map);
		/*玩家简单移动*/
	auto*moveControll = ThreeDirectionController::create();
	moveControll->setiXSpeed(1);
	moveControll->setiYSpeed(0);
	//控制器要添加到场景中才能获得update事件
	this->addChild(moveControll);
	//设置控制器到主角
	mPlayer->setController(moveControll);
	//加载对象层
	TMXObjectGroup*objGroup = map->getObjectGroup("objects");
	//加载玩家坐标
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();

	mPlayer->setPosition(Point(playerX,playerY));
	map->addChild(mPlayer);
	

}
