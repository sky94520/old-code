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

//��ʬ���ڲ�
#define ZOMBIE_Z_ORDER 4
//�ӵ����ڵ�tag
#define BULLET_Z_ORDER 5
//��Ч���ڲ�
#define EFFECT_Z_ORDER 6
//������֮���ZOrder���
#define Z_ORDER_INTERVAL 10

enum class GameState
{
	None,
	Play,/*������Ϸ��*/
	CardChoose,/*��Ƭѡ��*/
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
	//ɾ��ֲ��
	void removePlant(Plant*plant);
private://�ڲ�ʹ��
	void preloadResources();
	//���عؿ��ص�����
	void levelLoadCallback();
	//���ؿ�Ƭ
	void loadCard(LevelCardType levelType);
	//�ؿ���ʼ
	void levelStart(LevelCardType levelType);
	void collectProduct(Product*product);
	//���Դ���ֲ��
	bool tryPlanting(Card*card,Terrain*terrain);
	//��ֲֲ��
	Plant*planting(Card*card,Terrain*terrain,Plant*topPlant);
	//��ֲ������
	Plant*plantDefender(Card*card,Terrain*terrain);
	//����ֲ��
	Plant*upgradePlant(Card*card,Plant*topPlant);
	//���ԳԿ��ȶ�
	bool tryEatingCoffeeBean(NightPlant*plant);
	//���Դ�����ʬ
	bool tryMakingZombie(Card*card,Terrain*terrain);
	//ֲ���Ƿ��ǻ��
	void judgeActivationForPlant(Plant*plant);
	//������Ʒ��ȡ��Ӧ�ľ����ļ���
	string getSpriteFilenameOfGarnishry(Garnishry*garnishry);
private:
	//todo
	void addSun(int num);
	void subSun(int num);
	//��������
	void makeSun(int number,FiniteTimeAction*action,const Point&bornPos);
	TMXLayer* getEntityLayer();
	//��ȡ��ǰ����Ϸ�����С
	virtual Rect getGameVisibleRect();
	//�Ȼ�ʬ
	virtual void confuseZombie(ZombieBase*zombie);

	virtual Plant*getTopPlant(Terrain*terrain);
	virtual Plant*getTopPlantOfAttack(Terrain*terrain);
	//��ȡ�����еĵ�һ����ʬ�����û�У��򷵻�nullptr
	virtual ZombieBase*findFirstZombieOfRow(int row,Direction attackDir,const Point&pos);
	//��һ������ һ�������ڻ�ȡ��һ����ײ�Ľ�ʬ
	ZombieBase*findFirstCollidedZombie(int row,const Rect&rect);
	vector<ZombieBase*> findCollidedZombies(int row,const Rect& rect);
	//��ȡָ���еĵ�һ��Ŀ��
	virtual Character*findFirsCollidedMovableCharacterOfRow(int row,Direction attackDir,const Rect& rect);
	//����һ����Χ�ڴ���������Ʒ�Ľ�ʬ
	ZombieBase* findFirstZombieOfIronGarnishry(const Rect& rect);
	//���ֵ�һ�����õĲ��ҷ�����ײ���㶹�ӵ�
	ShooterPeaBullet* findFirstShooterPeaBullet(int row,const Rect&rect);
	//��ȡһ�е�����
	virtual vector<Terrain*>& getTerrainsOfRow(int row);

	//����㶹�ӵ� TODO
	void addPeaBullet(int damage,int row,const Point&startPos,bool bRight = true);
	//��Ӻ����ӵ�
	void addSnowPeaBullet(int damage,int row,const Point&startPos);
	//��ӻ��㶹
	void addFirePeaBullet(int damage,int row,const Point&startPos);
	//��������ӵ�
	void addShooterPeaBullet(ShooterPeaBullet::Type type,int row,const Point&startPos,bool bRight = true);
	//��ӱ�ը
	void addBoom(int damage,int row,const Rect&rect);
	//��Ӿ��Ĳ��ӵ�
	void addCabbageBullet(ZombieBase*zombie,int damage,int row,const Point&startPos);
	void addCornpultBullet(ZombieBase*zombie,bool isButter,int damage,int row,const Point&startPos);
	//��Ӵ��繽�ӵ�
	void addFumeShroomBullet(int damage,int row,const Point&startPos,float atkScope);
	//���Ģ���ӵ� atkScope С��0ʱ����߾��� TODO
	void addShroomBullet(int damage,int row,const Point& startPos,float atkScope);	
	
	//չʾ��ʬ��������
	virtual void showZombieDie(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//չʾ��ʬ��ը��������
	virtual void showZombieBoom(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//չʾ��ʬͷ���䶯��
	virtual void showZombieHead(const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	//չʾ��Ʒ���䶯��
	virtual void showGarnishryFallAction(Garnishry*garnishry,const Point&pos,int localZOrder,bool flipX);
	//��ӻ�����Ч
	virtual void addButterSplat(const Point&pos,int localZOrder,int uniqueID);
	virtual void removeButterSplat(int uniqueID);
	//��ӱ�����Ч
	virtual void addIceTrap(const Point&pos,int localZOrder,int uniqueID);
	virtual void removeIceTrap(int uniqueID);
	//�����Ʒ��Ч
	virtual void addGarnishryEffect(int uniqueID,const Point&pos,Garnishry*garnishry);
	virtual void removeGarnishryEffect(int uniqueID);

	virtual void showRisingDirt(const Point&pos,int localZOrder);
	virtual void showExplosionSpudow(const Point&pos);
	virtual float showCoffeeBeanEatAction(const Point&pos);
	virtual void showSnow();
	virtual void showBoom(const Point&pos);
	virtual void showFire(const Point&pos,int localZOrder);

	virtual Card*makeCard(const std::string& name,CardType type);
	//��ȡ��ǰ��Ϸ״̬
	virtual GameState getGameState()const;
	//��ȡ��ǰ�ؿ�״̬
	virtual LevelCardType getLevelCardShowType()const;
	//������ʬ
	virtual ZombieBase*makeZombie(const string& zombieName,const Point&pos,int row,bool bConfused);
private://delegate
	//play״̬
	virtual bool touchBeganOfPlayState(Touch*,SDL_Event*);
	virtual void touchMovedOfPlayState(Touch*touch,SDL_Event*event);
	virtual void touchEndedOfPlayState(Touch*touch,SDL_Event*event);
	//��Ƭѡ��״̬
	virtual bool touchBeganOfCardChooseState(Touch*touch,SDL_Event*event);
	virtual void touchMovedOfCardChooseState(Touch*touch,SDL_Event*evnet);
	virtual void touchEndedOfCardChooseState(Touch*touch,SDL_Event*evnet);
	//����˿�Ƭѡ��ʼ����
	virtual void clickCardChooseStartBtn();

	virtual Terrain*findTerrainOfZombieCollision(ZombieBase*zombie);
	virtual vector<ZombieBase*> getZombiesOfRow(int row);
	virtual ActiveTime getCurActiveTime()const;
};
#endif