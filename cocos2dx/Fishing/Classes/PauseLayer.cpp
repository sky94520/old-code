#include "PauseLayer.h"
PauseLayer::PauseLayer()
	:m_pDelegate(nullptr)
{
}
PauseLayer::~PauseLayer()
{
}
bool PauseLayer::init()
{
	//��ӻ�ɫ����
	LayerColor*bg = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(bg);
	//��Ӱ�ť
	auto valueMap = FileUtils::getInstance()->getValueMapFromFile("strings.xml");

	Label*continueLabel = Label::create(valueMap.at("str5").asString(),"fonts/DroidSansFallback.ttf",30);
	MenuItemLabel*continueBtn = MenuItemLabel::create(continueLabel);
	continueBtn->setCallback(CC_CALLBACK_1(PauseLayer::gameResume,this));
	//�ؿ�ѡ����� ��ť
	Label*levelLabel = Label::create(valueMap.at("str6").asString(),"fonts/DroidSansFallback.ttf",30);
	MenuItemLabel*levelBtn = MenuItemLabel::create(levelLabel);
	levelBtn->setCallback(CC_CALLBACK_1(PauseLayer::turnToLevelLevel,this));

	Menu*menu = Menu::create(continueBtn,levelBtn,NULL);
	//ʹ�˵�����ֱ����
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}
void PauseLayer::gameResume(Ref*sender)
{
	m_pDelegate->gameResume();
}
void PauseLayer::turnToLevelLevel(Ref*sender)
{
	m_pDelegate->turnToLevelLayer();
}
void PauseLayer::setDelegate(PauseLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}