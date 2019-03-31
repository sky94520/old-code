#ifndef __GameScene_H__
#define __GameScene_H__
#include<string>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "TouchLayer.h"
#include "LevelLayer.h"
#include "PlantLayer.h"
#include "ZombieLayer.h"
#include "Plant.h"
#include "ZombieBase.h"
#include "BulletLayer.h"
#include "ShooterPeaBullet.h"
#include "CardChooseLayer.h"

using namespace std;
using namespace SDL;

class CardLayer;
class PanelLayer;
class ProductLayer;
class Product;
class Card;
class Terrain;
class ZombieLayer;
class EffectLayer;
class ZombieBase;
class Garnishry;
class ShooterPeaBullet;

enum class CardType;

//僵尸所在层
#define ZOMBIE_Z_ORDER 4
//子弹所在的tag
#define BULLET_Z_ORDER 5
//特效所在层
#define EFFECT_Z_ORDER 6
//行与行之间的ZOrder间隔
#define Z_ORDER_INTERVAL 10

enum class GameState
{
	None,
	Play,/*正在游戏中*/
	CardChoose,/*卡片选择*/
};

class GameScene : public Scene
	,public TouchLayerDelegate,public LevelLayerDelegate,public PlantDelegate
	,public ZombieLayerDelegate,public ZombieDelegate,public BulletLayerDelegate
	,public PlantLayerDelegate,public CardChooseLayerDelegate
{
private:
	TouchLayer*m_pTouchLayer;
	LevelLayer*m_pLevelLayer;
	PlantLayer*m_pPlantLayer;
	ZombieLayer*m_pZombieLayer;
	BulletLayer*m_pBulletLayer;
	EffectLayer*m_pEffectLayer;
	CardChooseLayer*m_pCardChooseLayer;
	CardLayer*m_pCardLayer;
	PanelLayer*m_pPanelLayer;
	ProductLayer*m_pProductLayer;

	bool m_bSwallowTouch;
	GameState m_gameState;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void update(float dt);
	//删除植物
	void removePlant(Plant*plant);
private://内部使用
	void preloadResources();
	//加载关卡回调函数
	void levelLoadCallback();
	//加载卡片
	void loadCard(LevelCardType levelType);
	//关卡开始
	void levelStart(LevelCardType levelType);
	void collectProduct(Product*product);
	//尝试创建植物
	bool tryPlanting(Card*card,Terrain*terrain);
	//种植植物
	Plant*planting(Card*card,Terrain*terrain,Plant*topPlant);
	//种植保卫者
	Plant*plantDefender(Card*card,Terrain*terrain);
	//升级植物
	Plant*upgradePlant(Card*card,Plant*topPlant);
	//尝试吃咖啡豆
	bool tryEatingCoffeeBean(NightPlant*plant);
	//尝试创建僵尸
	bool tryMakingZombie(Card*card,Terrain*terrain);
	//植物是否是活动的
	void judgeActivationForPlant(Plant*plant);
	//根据饰品获取对应的精灵文件名
	string getSpriteFilenameOfGarnishry(Garnishry*garnishry);
private:
	//todo
	void addSun(int num);
	void subSun(int num);
	//生成阳光
	void makeSun(int number,FiniteTimeAction*action,const Point&bornPos);
	TMXLayer* getEntityLayer();
	//获取当前的游戏区域大小
	virtual Rect getGameVisibleRect();
	//魅惑僵尸
	virtual void confuseZombie(ZombieBase*zombie);

	virtual Plant*getTopPlant(Terrain*terrain);
	virtual Plant*getTopPlantOfAttack(Terrain*terrain);
	//获取所在行的第一个僵尸，如果没有，则返回nullptr
	virtual ZombieBase*findFirstZombieOfRow(int row,Direction attackDir,const Point&pos);
	//在一定行数 一定矩形内获取第一个碰撞的僵尸
	ZombieBase*findFirstCollidedZombie(int row,const Rect&rect);
	vector<ZombieBase*> findCollidedZombies(int row,const Rect& rect);
	//获取指定行的第一个目标
	virtual Character*findFirsCollidedMovableCharacterOfRow(int row,Direction attackDir,const Rect& rect);
	//发现一定范围内存在铁质饰品的僵尸
	ZombieBase* findFirstZombieOfIronGarnishry(const Rect& rect);
	//发现第一个可用的并且发生碰撞的豌豆子弹
	ShooterPeaBullet* findFirstShooterPeaBullet(int row,const Rect&rect);
	//获取一行的塔基
	virtual vector<Terrain*>& getTerrainsOfRow(int row);

	//添加豌豆子弹 TODO
	void addPeaBullet(int damage,int row,const Point&startPos,bool bRight = true);
	//添加寒冰子弹
	void addSnowPeaBullet(int damage,int row,const Point&startPos);
	//添加火豌豆
	void addFirePeaBullet(int damage,int row,const Point&startPos);
	//添加射手子弹
	void addShooterPeaBullet(ShooterPeaBullet::Type type,int row,const Point&startPos,bool bRight = true);
	//添加爆炸
	void addBoom(int damage,int row,const Rect&rect);
	//添加卷心菜子弹
	void addCabbageBullet(ZombieBase*zombie,int damage,int row,const Point&startPos);
	void addCornpultBullet(ZombieBase*zombie,bool isButter,int damage,int row,const Point&startPos);
	//添加大喷菇子弹
	void addFumeShroomBullet(int damage,int row,const Point&startPos,float atkScope);
	//添加蘑菇子弹 atkScope 小于0时是最高距离 TODO
	void addShroomBullet(int damage,int row,const Point& startPos,float atkScope);	
	
	//展示僵尸死亡动画
	virtual void showZombieDie(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//展示僵尸爆炸死亡动画
	virtual void showZombieBoom(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//展示僵尸头掉落动画
	virtual void showZombieHead(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//展示饰品掉落动画
	virtual void showGarnishryFallAction(Garnishry*garnishry,const Point&pos,int localZOrder,bool flipX);
	//添加黄油特效
	virtual void addButterSplat(const Point&pos,int localZOrder,int uniqueID);
	virtual void removeButterSplat(int uniqueID);
	//添加冰冻特效
	virtual void addIceTrap(const Point&pos,int localZOrder,int uniqueID);
	virtual void removeIceTrap(int uniqueID);
	//添加饰品特效
	virtual void addGarnishryEffect(int uniqueID,const Point&pos,Garnishry*garnishry);
	virtual void removeGarnishryEffect(int uniqueID);

	virtual void showRisingDirt(const Point&pos,int localZOrder);
	virtual void showExplosionSpudow(const Point&pos);
	virtual float showCoffeeBeanEatAction(const Point&pos);
	virtual void showSnow();
	virtual void showBoom(const Point&pos);
	virtual void showFire(const Point&pos,int localZOrder);

	virtual Card*makeCard(const std::string& name,CardType type);
	//获取当前游戏状态
	virtual GameState getGameState()const;
	//获取当前关卡状态
	virtual LevelCardType getLevelCardShowType()const;
	//创建僵尸
	virtual ZombieBase*makeZombie(const string& zombieName,const Point&pos,int row,bool bConfused);
private://delegate
	//play状态
	virtual bool touchBeganOfPlayState(Touch*,SDL_Event*);
	virtual void touchMovedOfPlayState(Touch*touch,SDL_Event*event);
	virtual void touchEndedOfPlayState(Touch*touch,SDL_Event*event);
	//卡片选择状态
	virtual bool touchBeganOfCardChooseState(Touch*touch,SDL_Event*event);
	virtual void touchMovedOfCardChooseState(Touch*touch,SDL_Event*evnet);
	virtual void touchEndedOfCardChooseState(Touch*touch,SDL_Event*evnet);
	//点击了卡片选择开始界面
	virtual void clickCardChooseStartBtn();

	virtual Terrain*findTerrainOfZombieCollision(ZombieBase*zombie);
	virtual vector<ZombieBase*> getZombiesOfRow(int row);
	virtual ActiveTime getCurActiveTime()const;
};
#endif