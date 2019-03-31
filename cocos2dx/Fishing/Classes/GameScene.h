#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "TouchLayer.h"
#include "GameLayer.h"
#include "HelpLayer.h"
#include "PauseLayer.h"
#include "PanelLayer.h"
#include "DefeatLayer.h"
#include "SuccessLayer.h"

#include "Box2D/Box2D.h"
class Fish;
class Fork;
class FishLayer;

USING_NS_CC;
enum GameState
{
	kOperateResume = 0,
	kOperatePause = 1
};
class GameScene:public Scene,public TouchLayerDelegate,HelpLayerDelegate
	,PanelLayerDelegate,PauseLayerDelegate,DefeatLayerDelegate,SuccessLayerDelegate
	,b2ContactListener
{
private:
	TouchLayer*m_pTouchLayer;//�¼��ַ���
	HelpLayer*m_pHelpLayer;//���������
	PanelLayer*m_pPanelLayer;//����
	GameLayer*m_pGameLayer;//��Ϸ��
	FishLayer*m_pFishLayer;//���
	PauseLayer*m_pPauseLayer;//��ͣ��
	DefeatLayer*m_pDefeatLayer;//ʧ�ܲ�
	SuccessLayer*m_pSuccessLayer;

	int m_nCurLevel;//��ǰ�ؿ�

	CustomCommand _command;
public:
	GameScene();
	~GameScene();
	static GameScene*create(int level);

	bool init(int level);

	virtual void update(float dt);
	//���عؿ��ű� ������
	void loadLevel(const std::string&filename);
private:
	//����
	virtual void shoot(const Point&targetPos);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	virtual Vector<Fish*>* getShowingFishes();
	virtual Fork*getShowingFork();

	virtual bool isClickComponents(const Point&pos);

	virtual void gamePause();//��Ϸ��ͣ
	virtual void gameResume();//��Ϸ�ָ�
	virtual void gameRestart();//��Ϸ���¿�ʼ
	virtual void nextLevel();//������һ��
	virtual void showQuestionLayer();

	virtual void turnToLevelLayer();//��ת���ؿ�ѡ�����

	void operateAllSchedulerAndActions(Node*node,int flag);
private:
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	void onDraw(const Mat4 &transform, uint32_t flags);
};
#endif