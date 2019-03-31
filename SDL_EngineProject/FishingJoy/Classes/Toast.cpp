#include "Toast.h"
namespace Toast
{
	void makeSprite(Node*parent,Sprite*sprite,float delay)
	{
		//��������
		FadeIn*fadeIn = FadeIn::create(0.2f);
		FadeOut*fadeOut = FadeOut::create(0.2f);
		DelayTime*delayTime = DelayTime::create(delay);
		RemoveSelf*removeSelf = RemoveSelf::create();
		//���ж���
		sprite->runAction(Sequence::create(fadeIn,delayTime,fadeOut,removeSelf,nullptr));
		//����λ��
		Size visibleSize = Director::getInstance()->getVisibleSize();
		sprite->setPosition(visibleSize.width/2,visibleSize.height/4*3);
		//��ӵ�parent���
		parent->addChild(sprite);
	}
}