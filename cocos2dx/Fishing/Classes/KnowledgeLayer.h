#ifndef __KnowledgeLayer_H__
#define __KnowledgeLayer_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class KnowledgeLayer:public Layer
{
public:
	KnowledgeLayer();
	~KnowledgeLayer();
	CREATE_FUNC(KnowledgeLayer);
	bool init();
private:
	void gameExit(Ref*sender);
};
#endif