#include "PanelLayer.h"
#include "GameScene.h"

PanelLayer::PanelLayer()
{
}

PanelLayer::~PanelLayer()
{
}

bool PanelLayer::init()
{
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scenes/panel_layer.xml");
	this->addChild(node);
	//��ȡ�������õĿؼ�
	auto goBtn = node->getChildByName<ui::Button*>("go_btn");
	goBtn->addClickEventListener(SDL_CALLBACK_1(PanelLayer::goBtnCallback,this));

	return true;
}

void PanelLayer::goBtnCallback(Object* sender)
{
	GameScene::getInstance()->goBtnCallback();
}