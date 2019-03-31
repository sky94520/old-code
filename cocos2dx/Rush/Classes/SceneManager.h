#ifndef __SceneManager_H__
#define __SceneManager_H__
#include "cocos2d.h"
USING_NS_CC;
enum class EnumSceneType
{
	en_TollgateScene,//�ؿ�����
	en_TollgateEditorScene,//�ؿ��༭����
	en_WinScene,//ʤ������
	en_GameOverScene//ʧ�ܳ���
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