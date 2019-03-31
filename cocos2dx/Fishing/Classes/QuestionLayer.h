#ifndef __QuestionLayer_H__
#define __QuestionLayer_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "sqlite3/sqlite3.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class QuestionLayer:public Layer
{
private:
	CheckBox*m_pSelectedItem;//选中项
	CheckBox*m_pAnswers[4];//四个checkbox
	int m_nTrueIndex;//正确答案
public:
	QuestionLayer();
	~QuestionLayer();
	CREATE_FUNC(QuestionLayer);
	bool init();
private:
	void onBtnClick(Ref*sender);
	void okCallback(Ref*sender);//确定键回调函数
	void backCallback(Ref*sender);//返回回调函数
};
#endif