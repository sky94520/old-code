#ifndef __TowerPosEditorScene_H__
#define __TowerPosEditorScene_H__
#include<string>
#include "cocos2d.h"
#include "TowerPos.h"
#include "MonsterPos.h"
USING_NS_CC;
/*坑的类型*/
typedef enum
{
	kTowerPos = 0,
	kMonsterPos
}PosType;
#define DEBUG_TEST 1
class TowerPosEditorScene : public Layer
{
private:
	//存放所有的塔的坐标
	Vector<PosBase*> m_towerPosList;
	//存放怪物行走的坐标
	Vector<PosBase*> m_monsterPosList;
	//当前关卡
	int m_iCurLevel;
	std::string m_configFileName[2];
	PosType m_type;
	//背景图片
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
	//编辑塔坐标
	void editTowerPos(Point pos);
	//编辑怪物坐标
	void editMonsterPos(Point pos);
	//找到存在的坐标
	PosBase*findExistTowerPos(Point pos);
	PosBase*findExistMonsterPos(Point pos);
	//生成塔坐标
	void createTowerPos(Point pos);
	//生成怪物行走坐标
	void createMonsterPos(Point pos);
	//删除
	void deleteTowerPos(PosBase*existPos);
	void deleteMonsterPos(PosBase*existPos);
	//删除所有坐标对象
	void deleteAllPos();
	//生成配置文件
	void outputPosToPlistFile(Ref*);
	//加载配置文件
	void loadConfigFile();
	//怪物路径连线
	virtual void draw(Renderer*renderer,const kmMat4 &,uint32_t flags);
};
#endif