/*
    �ļ�����    TollgateScene.h
    �衡����    �ؿ�����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
using namespace cocos2d;

class TollgateScene : public Layer {
public:
    static Scene* createScene();
    CREATE_FUNC(TollgateScene);
    virtual bool init();

private:
	void addPlayer(TMXTiledMap*map);
};
#endif