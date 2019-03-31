#ifndef __SceneManager_H__
#define __SceneManager_H__
#include "cocos2d.h"
USING_NS_CC;
enum class EnumSceneType
{
	en_TollgateScene,//关卡场景
	en_TollgateEditorScene,//关卡编辑界面
	en_WinScene,//胜利场景
	en_GameOverScene//失败场景
};
class SceneManager
{
private:
	static SceneManager*m_pInstance;
	SceneManager();
	~SceneManager();
public:
	static SceneManager*getInstance();
	void changeScene(EnumSceneType type);

};
#endif