#include "KnowledgeLayer.h"
KnowledgeLayer::KnowledgeLayer()
{
}
KnowledgeLayer::~KnowledgeLayer()
{
}
bool KnowledgeLayer::init()
{
	Node*csb = CSLoader::createNode("KnowledgeLayer.csb");
	this->addChild(csb);
	//ÍË³ö°´Å¥
	auto exitBtn = static_cast<Widget*>(csb->getChildByName("exit_btn"));
	exitBtn->addClickEventListener(CC_CALLBACK_1(KnowledgeLayer::gameExit,this));

	return true;
}
void KnowledgeLayer::gameExit(Ref*sender)
{
	Director::getInstance()->end();
}