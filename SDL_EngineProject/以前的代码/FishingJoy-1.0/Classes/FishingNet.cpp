#include "FishingNet.h"
#include "Fish.h"
FishingNet::FishingNet()
	:m_pDelegate(nullptr)
{
}

FishingNet::~FishingNet()
{
	printf("Fishing net release\n");
}
bool FishingNet::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("fishing_net.png"));
	return true;
}
void FishingNet::setDelegate(FishingNetDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void FishingNet::showAt(const Point&pos)
{
	//����λ��
	Size size = getBoundingBox().size;
	setPosition(pos - Point(size.width/2,size.height/2));
	//������С�������������������� ���Ժ���չ
	auto cannonType = m_pDelegate->getCannonType();
	float scale = 1 + cannonType*0.15f;
	this->getSprite()->setScale(scale,scale);
	//������������
	this->setVisible(true);

	this->stopAllActions();
	getSprite()->stopAllActions();
	//��������
	ScaleBy*scaleMax = ScaleBy::create(0.2f,0.2f,0.2f);
	ScaleBy*scaleMin = ScaleBy::create(0.1f,-0.2f,-0.2f);
	auto*action = Sequence::create(scaleMax,scaleMin,nullptr);
	this->getSprite()->runAction(action);
	DelayTime*delay = DelayTime::create(action->getDuration());
	CallFunc*callfunc = CallFunc::create([&]()
	{
		setVisible(false);
		setPosition(0,0);
	});
	this->runAction(Sequence::create(delay,callfunc,nullptr));
}
Rect FishingNet::getFishingNetCollisionRect()const
{
	Rect rect = this->getSprite()->getBoundingBox();
	rect.origin = getWorldPosition();
	return rect;
}