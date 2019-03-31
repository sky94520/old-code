#ifndef __EffectLayer_H__
#define __EffectLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"

#define EFFECT_ANIMATE_TAG 1
using namespace std;
using namespace SDL;

class EffectLayer:public Layer
{
private:
	Vector<Sprite*> m_sprites;
public:
	EffectLayer();
	~EffectLayer();
	CREATE_FUNC(EffectLayer);
	bool init();
public:
	void addGoldAnimation(const Point&pos);
	void addFadeScoreAction(int score,const Point&pos);
	//�㳱���ٵĺ��˶���
	void showWaveAction();
	//�㳱���� �ƶ�����
	void showGroupComeMoving();
	//���ѡ����Ч
	void addSelectedMark(const string&name,const Point&pos);
	void changeSelectedMark(const string&name,const Point&pos);
	void removeSelectedMark(const string&name);
	//��ʾ��������
	void showLevelUpAction();
	//��ӱ������Ч
	void addChestLightAnim(const string&name,const Point&pos);
	void removeChestLightAnim(const string&name);
	//��ػ�ȡ���ƶ���Ч
	float showBatteryMoving(const Point&bornPos);
	//�����ӵ���ȡ���ƶ���Ч
	float showPearlBulletMoving(const Point&bornPos);
	float showFogBulletMoving(const Point&bornPos);
	float showSterengthenBulletMoving(const Point&bornPos);
private:
	float itemMove(Sprite*sprite,const Point&bornPos,const Point&endPos);
};
#endif