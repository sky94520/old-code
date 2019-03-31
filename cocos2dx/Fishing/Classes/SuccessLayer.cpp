#include "SuccessLayer.h"
SuccessLayer::SuccessLayer()
	:m_pDelegate(nullptr)
{
}
SuccessLayer::~SuccessLayer()
{
}
bool SuccessLayer::init()
{
	//添加成功界面
	Node*csb = CSLoader::createNode("SuccessLayer.csb");
	this->addChild(csb);
	//下一关按钮
	Widget*nextBtn = static_cast<Widget*>(csb->getChildByName("next_btn"));
	nextBtn->addClickEventListener(CC_CALLBACK_1(SuccessLayer::nextLevel,this));
	//重来按钮
	Widget*restartBtn = static_cast<Widget*>(csb->getChildByName("restart_btn"));
	restartBtn->addClickEventListener(CC_CALLBACK_1(SuccessLayer::gameRestart,this));
	//返回按钮
	Widget*backBtn = static_cast<Widget*>(csb->getChildByName("back_btn"));
	backBtn->addClickEventListener(CC_CALLBACK_1(SuccessLayer::turnToLevelLayer,this));
	//添加粒子特效
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	ParticleSnow*snow = ParticleSnow::create();

	snow->setSpeed(200);
	snow->setSpeedVar(100);
	snow->setEmitterMode(ParticleSystem::Mode::GRAVITY);

	snow->setTotalParticles(500);
	snow->setEmissionRate(60.f);//播放速率

	snow->setPosition(visibleSize.width/2,visibleSize.height);//设置发射器位置
	snow->setPosVar(Point(visibleSize.width/2,0));//设置位置紊乱值
	snow->setPositionType(ParticleSystem::PositionType::FREE);//设置粒子不围绕着发射器位置
	
	//snow->setRotationIsDir(
	snow->setLife(8.f);
	snow->setLifeVar(2.f);
	snow->setTangentialAccel(10.f);

	this->addChild(snow);*/

	return true;
}
void SuccessLayer::setDelegate(SuccessLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void SuccessLayer::gameRestart(Ref*sender)
{
	this->setVisible(false);
	m_pDelegate->gameRestart();
}
void SuccessLayer::turnToLevelLayer(Ref*sender)
{
	m_pDelegate->turnToLevelLayer();
}
void SuccessLayer::nextLevel(Ref*sender)
{
	this->setVisible(false);
	m_pDelegate->nextLevel();
}