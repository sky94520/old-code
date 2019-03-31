#ifndef __GameScene_H__
#define __GameScene_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Box2D/Box2D.h"
#include "FishLayer.h"
#include "PanelLayer.h"
#include "TouchLayer.h"
#include "Cannon.h"
#include "BulletLayer.h"
#include "FishingEntityLayer.h"
#include "RewardLayer.h"
#include "PauseLayer.h"
#include "GoldTimer.h"

using namespace std;
using namespace SDL;

class LevelLayer;
class NetGunBullet;
class FishingNet;
class FishingEntity;
class EffectLayer;
class Bullet;
class ItemButton;

/*��Ϸ״̬*/
enum class GameState
{
	Resume,//�ָ�
	Pause,//��ͣ
};

class GameScene:public Scene
	,public PanelLayerDelegate,public TouchLayerDelegate,public CannonDelegate
	,public BultLayerDelegate,public FishingEntityLayerDelegate
	,public FishLayerDelegate,public RewardLayerDelegate
	,public PauseLayerDelegate,public GoldTimerDelegate
	,public b2ContactListener
{
private:
	LevelLayer*m_pLevelLayer;
	TouchLayer*m_pTouchLayer;
	PanelLayer*m_pPanelLayer;
	Cannon*m_pCannon;
	GoldTimer*m_pGoldTimer;
	BulletLayer*m_pBulletLayer;
	FishingEntityLayer*m_pFishingEntityLayer;
	FishLayer*m_pFishLayer;
	RewardLayer*m_pRewardLayer;
	PauseLayer*m_pPauseLayer;

	EffectLayer*m_pEffectLayer;
	//���е�GameScene����
	static b2World*s_pWorld;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

	virtual void update(float dt);

	void preloadResources();
	//��Ϸ�������ͷ�һЩ������
	static void gameExit();
	//��Ϸ��ͣ
	void gamePause();
	//��Ϸ�ָ�
	void gameResume();
	//���ű�������
	void playBackgroundMusic();
	static b2World*getWorld();
private://private
	void collisionOfBullet(Bullet*bullet,Entity*entity);
	void collisionOfFishingEntity(FishingEntity*fishingNet,Entity*entity);
	//�ݹ�ָ�����ͣ���ڵ��µ����нڵ�
	void operateAllSchedulerAndActions(Node*node,GameState state);
private://override
	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact);
	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact);
private://delegate
	virtual void addCannonLevel();
	virtual void subCannonLevel();
	virtual void pauseBtnCallback();
	virtual void continueGame();
	virtual void turnStartLayer();
	virtual void chooseTollgate();
	virtual void operateMusic();
	virtual void operateChunk();
	//�ı��ӵ�
	virtual void changeBullet(ItemButton*button,bool oldVisible,bool visible);

	virtual bool onTouchBegan(Touch*touch,SDL_Event*event);
	virtual void onTouchMoved(Touch*touch,SDL_Event*event);
	virtual void onTouchEnded(Touch*touch,SDL_Event*event);

	virtual void fireCallback(const Point&pos);
	//�������
	virtual void fireEnd();
	//�����ӵ�
	void shootAt(Bullet*bullet,Fish*fish);
	//��һ�ν�Ҷ��������ӽ��������ͬʱ��������
	void addGold(int number,const Point&pos);
	//��ʾ���˶�����ͬʱ��������
	void showWaveAction();
	//��ʾ�������Ч
	void addChestLightAnim(const string&name,const Point&pos);
	void removeChestLightAnim(const string&name);
	//���ٽ��
	bool subGold(int number);
	//��������,ֻ�Ǽ򵥵�����������
	void addEnergy(float delta);
	//���Ӿ���ֵ���ڲ����ж��Ƿ�����
	void addExp(float exp);
	//�����������
	void addBattery(int count,const Point&bornPos);
	void addBattery(int count);
	//�������鵯
	void addPearlBullet(int count,const Point&bornPos);
	void addPearlBullet(int count);
	//��������
	void addFogBullet(int count,const Point&bornPos);
	void addFogBullet(int count);
	//����ǿ����
	void addStrengthenBullet(int count,const Point&bornPos);
	void addStrengthenBullet(int count);
	//��ӵ���
	void addItem(const string&itemName,const Point&bornPos,int number);
	//��ȡ�ؿ��㳱��id
	int getRandomFishTideID()const;
	//����
	void levelUp();
	//�������
	void randomMakeFishingNets(float dt,int lv = 1);
	//�㱻��׽�ص�����
	void fishCaughtCallback(Fish*fish);
	//����ص�����
	void showChestCallback(Object*sender);
	//����������� �򵥵ط�װ
	void addFishingNet(int lv,const Point&pos,float rotation);

	virtual vector<int>& getShownFishIdVec();
	virtual vector<float>& getStartFishStartTimeVec();
	virtual void showGroupComeMoving();
};
#endif