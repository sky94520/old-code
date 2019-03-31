#ifndef __PosLoadUtil_H__
#define __PosLoadUtil_H__
#include "cocos2d.h"
#include "PosBase.h"
#include "TowerPosEditorScene.h"
class PosLoadUtil
{
private:
	static PosLoadUtil* m_pInstance;
	PosLoadUtil();
public:
	static PosLoadUtil*getInstance();
	Vector<PosBase*> loadPosWithFile(const char*sFilePath,PosType type,Node*container,int iLevel,bool isDebug);
};
#endif 