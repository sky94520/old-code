#ifndef __TowerPosEditorScene_H__
#define __TowerPosEditorScene_H__
#include<string>
#include "cocos2d.h"
#include "TowerPos.h"
#include "MonsterPos.h"
USING_NS_CC;
/*�ӵ�����*/
typedef enum
{
	kTowerPos = 0,
	kMonsterPos
}PosType;
#define DEBUG_TEST 1
class TowerPosEditorScene : public Layer
{
private:
	//������е���������
	Vector<PosBase*> m_towerPosList;
	//��Ź������ߵ�����
	Vector<PosBase*> m_monsterPosList;
	//��ǰ�ؿ�
	int m_iCurLevel;
	std::string m_configFileName[2];
	PosType m_type;
	//����ͼƬ
	Sprite*m_pBG;
private:
	void onDraw(const kmMat4 &transform,bool transformUpdated);
	CustomCommand _customCommand;
public:
	TowerPosEditorScene();
	~TowerPosEditorScene();
	CREATE_FUNC(TowerPosEditorScene);
	virtual bool init();
	static Scene*createScene();
	//�༭������
	void editTowerPos(Point pos);
	//�༭��������
	void editMonsterPos(Point pos);
	//�ҵ����ڵ�����
	PosBase*findExistTowerPos(Point pos);
	PosBase*findExistMonsterPos(Point pos);
	//����������
	void createTowerPos(Point pos);
	//���ɹ�����������
	void createMonsterPos(Point pos);
	//ɾ��
	void deleteTowerPos(PosBase*existPos);
	void deleteMonsterPos(PosBase*existPos);
	//ɾ�������������
	void deleteAllPos();
	//���������ļ�
	void outputPosToPlistFile(Ref*);
	//���������ļ�
	void loadConfigFile();
	//����·������
	virtual void draw(Renderer*renderer,const kmMat4 &,uint32_t flags);
};
#endif