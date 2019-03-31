#include "SceneManager.h"
#include "TowerPosEditorScene.h"
#include "TollgateMapLayer.h"
SceneManager*SceneManager::m_pInstance = NULL;
SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}
SceneManager*SceneManager::getInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new SceneManager();
	return m_pInstance;
}
void SceneManager::changeScene(EnumSceneType type)
{
	Scene*pScene = NULL;
	switch(type)
	{
	case EnumSceneType::en_TollgateEditorScene:
		pScene = TowerPosEditorScene::createScene();
		break;
	case EnumSceneType::en_TollgateScene:
		pScene = TollgateMapLayer::createScene();
		break;
	default:
		;
	}
	if(pScene == NULL)
		return;
	Director::getInstance()->replaceScene(pScene);
}