#include "GameScene.h"
#include "Player.h"
#include "PackageLayer.h"
#include "Item.h"
#include "Weapon.h"
#include "FightLayer.h"
#include "DynamicData.h"
#include "GlobalFunctions.h"
#include "Size.h"
#include "TextureManager.h"
GameScene::GameScene()
	:m_pPlayer(nullptr),m_pPackageLayer(nullptr),m_pMap(nullptr)
	,m_pFightLayer(nullptr),m_pColliabledEntity(nullptr)
{
	DynamicData::getInstance();
	srand(time(0));
}
GameScene::~GameScene()
{
	SDL_SAFE_DELETE(m_pPackageLayer);
	SDL_SAFE_DELETE(m_pPlayer);
	SDL_SAFE_DELETE(m_pMap);
	SDL_SAFE_DELETE(m_pFightLayer);

	DynamicData::getInstance()->purge();
	//UserDefault::getInstance()->purge();
}
bool GameScene::init()
{
	//读取存档
	//todo
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	m_pPlayer = new Player();
	m_pPlayer->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	m_pPlayer->bindSprite('@');
	//背包界面
	m_pPackageLayer = new PackageLayer();
	//m_pPackageLayer->init(m_pPlayer->getPackages());
	m_pPackageLayer->setDelegate(this);
	//战斗界面
	m_pFightLayer = new FightLayer();
	//地图
	m_pMap = new FieldMap();
	m_pMap->setDelegate(this);
	m_pMap->init("map/map1.lua");
	return true;
}
void GameScene::render()
{
	m_pPlayer->render();
	//画出当前地图属性
	m_pMap->render();
	//获取当前碰撞项
	cout<<"sky小助手:";
	if(m_pColliabledEntity)
		cout<<m_pColliabledEntity->getName();
	cout<<endl;
}
Player* GameScene::getPlayer()const
{
	return m_pPlayer;
}
std::vector<Monster*>* GameScene::getMonsters()
{
	return m_pMap->getMonsters();
}
void GameScene::showPackage()
{
	m_pPackageLayer->show();
}
void GameScene::setColliabledEntity(Colliabled*pColliabled)
{
	m_pColliabledEntity = pColliabled;
}
Colliabled* GameScene::getColliabledEntity()const
{
	return m_pColliabledEntity;
}
bool GameScene::use(Item*pItem)
{
	//武器，则装备
	if(pItem->getItemType() == ItemType::kItemType_Weapon)
	{
		auto weapon = m_pPlayer->getWeapon();
		if(weapon == pItem)
		{
			return false;
		}
		m_pPlayer->setWeapon(static_cast<Weapon*>(pItem));
		return true;
	}
	return false;
}
int GameScene::sell(Item*pItem)
{
	//出售的是武器
	if(pItem->getItemType() == ItemType::kItemType_Weapon)
	{
		//如果主角已经佩戴，则无法出售
		if(pItem == m_pPlayer->getWeapon())
			return -1;
		return DynamicData::getInstance()->sellItem(pItem);
	}
}
void GameScene::fight()
{
	m_pFightLayer->fight(m_pPlayer,m_pMap->getMonsters());
}
void GameScene::toggleLayer(const std::string&filename,const Point&playerPos)
{
	m_pMap->init(filename);
	//每次传送都是在地图中间
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	m_pPlayer->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
}