#ifndef __LevelLayer_H__
#define __LevelLayer_H__
#include<string>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
using namespace cocos2d::extension;

//ÿ�������еİ�ť��Ŀ
#define MAX_BTN_NUMBER 8
/*�ؿ�ѡ�����*/
class LevelLayer:public Layer
{
public:
	LevelLayer();
	~LevelLayer();
	static Scene*createScene();
	CREATE_FUNC(LevelLayer);
	bool init();
private:
	void btnCallback(Ref*sender,Control::EventType eventType);
	void returnToStartScene(Ref*sender);
};
#endif