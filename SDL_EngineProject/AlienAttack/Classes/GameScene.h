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
/*游戏状态*/
enum GameState
{
	kGameState_Resume,//恢复
	kGameState_Pause,//暂停
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
	//递归恢复或暂停本节点下的所有节点
	void operateAllSchedulerAndActions(Node*node,GameState state);
	//游戏暂停
	void gamePause();
	//游戏恢复
	void gameResume();
	//getter
	MapLayer*getMapLayer();
	BulletLayer*getBulletLayer();
private:
	void handleCollision();//处理碰撞
	void nextLevel();//下一关卡
private://delegate
	virtual void playerMove(const Point&velocity);
	virtual  void playerWantShooting();
	virtual void gameOver();
	virtual void gameRestart();
	virtual float getMapScrollSpeed();
	virtual bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading);
};
#endif