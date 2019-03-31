#ifndef __GameScene_H__
#define __GameScene_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
#include "KeyboardLayer.h"
#include "GameOverLayer.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"

using namespace SDL;
using namespace std;

class MapLayer;
class BulletLayer;
class PanelLayer;
/*��Ϸ״̬*/
enum GameState
{
	kGameState_Resume,//�ָ�
	kGameState_Pause,//��ͣ
};
class GameScene:public Scene
	,public EventDelegate,public PlayerLayerDelegate,public GameOverDelegate
	,public EnemyLayerDelegate
{
private:
	KeyboardLayer*m_pEventLayer;
	MapLayer*m_pMapLayer;
	PlayerLayer*m_pPlayerLayer;
	BulletLayer*m_pBulletLayer;
	EnemyLayer*m_pEnemyLayer;
	PanelLayer*m_pPanelLayer;
	GameOverLayer*m_pGameOverLayer;
public:
	GameScene();
	~GameScene();
	static GameScene*create(const string&level);
	bool init(const string&level);

	virtual void update(float dt);
	//�ݹ�ָ�����ͣ���ڵ��µ����нڵ�
	void operateAllSchedulerAndActions(Node*node,GameState state);
	//��Ϸ��ͣ
	void gamePause();
	//��Ϸ�ָ�
	void gameResume();
	//getter
	MapLayer*getMapLayer();
	BulletLayer*getBulletLayer();
private:
	void handleCollision();//������ײ
	void nextLevel();//��һ�ؿ�
private://delegate
	virtual void playerMove(const Point&velocity);
	virtual  void playerWantShooting();
	virtual void gameOver();
	virtual void gameRestart();
	virtual float getMapScrollSpeed();
	virtual bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading);
};
#endif