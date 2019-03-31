#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include<string>
#include<vector>

#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class ItemButton;
class GoldCounter;

class PanelLayerDelegate
{
public:
	virtual ~PanelLayerDelegate(){}
	virtual void addCannonLevel()=0;
	virtual void subCannonLevel()=0;
	virtual void pauseBtnCallback()=0;
	virtual void changeBullet(ItemButton*button,bool oldVisible,bool visible)=0;
	virtual void addEnergy(float delta)=0;
};

class PanelLayer:public Layer
{
private:
	Sprite*m_pDownUI;//�ײ�ui
	Sprite*m_pEnergyUI;//�����ۣ����𶯻�
	GoldCounter*m_pGoldCounter;
	LabelAtlas*m_pLvUI;

	ui::Button*m_pSubLevelBtn;
	ui::Button*m_pAddLevelBtn;
	ui::Button*m_pPauseBtn;
	//�����ۻ�����
	ProgressTimer*m_pEnergyProgress;
	ProgressTimer*m_pExpProgress;

	bool m_bBulletsVisible;//�ӵ���ť�����Ƿ��Ѿ���ʾ
	ItemButton*m_pSelectedBullet;//��ǰѡ�е��ӵ�
	ItemButton*m_pHalfEnergyBtn;//����������

	Menu*m_pBulletMenu;//�ӵ���ť����
	Menu*m_pBtnMenu;//��ť����

	PanelLayerDelegate*m_pDelegate;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();

	//��ȡ����������λ��
	Point getConnonBornPos()const;

	void setDelegate(PanelLayerDelegate*pDelegate);
	//�˶���������
	void runEnergyAnimation();
	//ֹͣ��������
	void stopEnergyAnimation();
	//��ʾadd sub��ť
	void showAddAndSubBtn();
	//����add sub��ť
	void hideAddAndSubBtn();
	//����������
	void updateEnergy();
	//���½������
	void updateGold();
	//���µȼ�
	void updateLevel();
	//���¾���ֵ
	void updateExp();
	//����ȫ��
	void updateSelf();
	void updateBulletBtns();//�����ӵ���ť
	void updateHalfEnergyBtn();
	//����ѡ�е�ǰ�ӵ�
	void setSelectedBulletBtn(const string&name);
	void setSelectedBulletBtn(ItemButton*button);
	//���ð�ť�Ƿ�ɵ��
	void setBtnEnable(bool enable);
private:
	void initBullets();

	void addBtnCallback(Object*sender);
	void subBtnCallback(Object*sender);
	void pauseBtnCallback(Object*sender);

	void handleSuperWeapon(ItemButton*button);
	void handleHalfEnergy(Object*sender);
	void handleBullet(Object*sender);
};
#endif