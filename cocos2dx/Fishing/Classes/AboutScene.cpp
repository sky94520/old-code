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
	//加载csb
	auto csb = CSLoader::createNode("AboutLayer.csb");
	this->addChild(csb);
	//返回按钮回调
	Widget*backBtn = static_cast<Widget*>(csb->getChildByName("back_btn"));
	backBtn->addClickEventListener(CC_CALLBACK_1(AboutScene::returnToStartScene,this));

	return true;
}
void AboutScene::returnToStartScene(Ref*sender)
{
	Director::getInstance()->replaceScene(StartScene::create());
}