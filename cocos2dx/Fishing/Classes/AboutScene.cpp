#include "AboutScene.h"
#include "StartScene.h"

AboutScene::AboutScene()
{
}
AboutScene::~AboutScene()
{
}
bool AboutScene::init()
{
	//����csb
	auto csb = CSLoader::createNode("AboutLayer.csb");
	this->addChild(csb);
	//���ذ�ť�ص�
	Widget*backBtn = static_cast<Widget*>(csb->getChildByName("back_btn"));
	backBtn->addClickEventListener(CC_CALLBACK_1(AboutScene::returnToStartScene,this));

	return true;
}
void AboutScene::returnToStartScene(Ref*sender)
{
	Director::getInstance()->replaceScene(StartScene::create());
}