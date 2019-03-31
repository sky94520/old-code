#include "DefeatLayer.h"
DefeatLayer::DefeatLayer()
	:m_pDelegate(nullptr)
{
}
DefeatLayer::~DefeatLayer()
{
}
bool DefeatLayer::init()
{
	//添加灰色背景
	LayerColor*bg = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(bg);
	Node*csb = CSLoader::createNode("DefeatLayer.csb");
	this->addChild(csb);
	//重新开始按钮
	Button*restartBtn = dynamic_cast<Button*>(csb->getChildByName("restart_btn"));
	restartBtn->addClickEventListener(CC_CALLBACK_1(DefeatLayer::gameRestart,this));
	//关卡选择界面
	Button*turnToLevelBtn = dynamic_cast<Button*>(csb->getChildByName("back_btn"));
	turnToLevelBtn->addClickEventListener(CC_CALLBACK_1(DefeatLayer::turnToLevelLayer,this));

	return true;
}
void DefeatLayer::setDelegate(DefeatLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void DefeatLayer::gameRestart(Ref*sender)
{
	//失败层不可见
	this->setVisible(false);

	m_pDelegate->gameRestart();
}
void DefeatLayer::turnToLevelLayer(Ref*sender)
{
	m_pDelegate->turnToLevelLayer();
}