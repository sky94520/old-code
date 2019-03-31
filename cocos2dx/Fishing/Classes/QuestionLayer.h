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
	CheckBox*m_pSelectedItem;//ѡ����
	CheckBox*m_pAnswers[4];//�ĸ�checkbox
	int m_nTrueIndex;//��ȷ��
public:
	QuestionLayer();
	~QuestionLayer();
	CREATE_FUNC(QuestionLayer);
	bool init();
private:
	void onBtnClick(Ref*sender);
	void okCallback(Ref*sender);//ȷ�����ص�����
	void backCallback(Ref*sender);//���ػص�����
};
#endif