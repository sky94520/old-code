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
	//��ӻ�ɫ����
	LayerColor*bg = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(bg);
	Node*csb = CSLoader::createNode("DefeatLayer.csb");
	this->addChild(csb);
	//���¿�ʼ��ť
	Button*restartBtn = dynamic_cast<Button*>(csb->getChildByName("restart_btn"));
	restartBtn->addClickEventListener(CC_CALLBACK_1(DefeatLayer::gameRestart,this));
	//�ؿ�ѡ�����
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
	//ʧ�ܲ㲻�ɼ�
	this->setVisible(false);

	m_pDelegate->gameRestart();
}
void DefeatLayer::turnToLevelLayer(Ref*sender)
{
	m_pDelegate->turnToLevelLayer();
}