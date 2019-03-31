#include "HelpLayer.h"

HelpLayer::HelpLayer()
	:m_pCloseBtn(nullptr),m_pDelegate(nullptr)
{
}

HelpLayer::~HelpLayer()
{
}

bool HelpLayer::init()
{
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/HelpLayer.xml");

	m_pCloseBtn = node->getChildByName<ui::Button*>("close_btn");
	m_pCloseBtn->addClickEventListener(SDL_CALLBACK_1(HelpLayer::closeBtnCallback,this));
	this->addChild(node);

	return true;
}

void HelpLayer::setDelegate(HelpLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void HelpLayer::closeBtnCallback(Object*sender)
{
	//printf("help layer\n");
	m_pDelegate->closeHelpLayer();
}