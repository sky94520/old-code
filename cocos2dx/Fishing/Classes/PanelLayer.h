#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include<map>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class NeedfulFishCompent;

class PanelLayerDelegate
{
public:
	virtual ~PanelLayerDelegate(){}
	virtual void gamePause()=0;
	virtual void showQuestionLayer()=0;
};
/*面板层，只是显示当前剩余出手数
需要捕捉的鱼的种类与数量*/
/*更新功能:当捕捉到一条鱼时，如果需要此鱼，则显示出该鱼还剩下几条过关*/
class PanelLayer:public Layer
{
private:
	Label*m_pTimesLabel;//剩余步数
	PanelLayerDelegate*m_pDelegate;
	map<int,NeedfulFishCompent*> m_compents;
	bool m_bShowAllComp;//是否已经显示了所有的组件
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
	void clean();

	void setDelegate(PanelLayerDelegate*pDelegate);
	//显示本关卡所需要的全部的鱼
	void showAllNeedfulFishesComp();
	//隐藏
	void hideAllNeedfulFishesComp();
	//是否点击了组件
	bool isClickedComponents(const Point&pos)const;
	bool isShowAllComp()const;
	void setShowAllComp(bool c);

	bool initWithTimes();
	bool initWithNeedfulFishes();
private:
	void updateSelf(Ref*sender);
	//游戏暂停按钮回调函数
	void gamePause(Ref*obj);
	//显示问题界面
	void showQuestionLayer(Ref*sender);
};
#endif